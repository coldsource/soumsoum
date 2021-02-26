#include <stdio.h>
#include <sys/time.h>
#include <unistd.h>

#include <Vector/Vector3D.h>
#include <Dynamic/MovingBody.h>
#include <Submarine/Submarine.h>
#include <Simulation/SimulationObject.h>

#include <libwebsockets.h>

#include <nlohmann/json.hpp>

#include <thread>
#include <map>
#include <mutex>

struct lws_context *ws_context;
std::mutex ws_mutex;

using json = nlohmann::json;
using namespace std;

double GetDtime()
{
	struct timeval tv;
	gettimeofday(&tv, 0);
	return (double)tv.tv_sec + (double)tv.tv_usec/1000000;
}

struct per_session_data
{
	unsigned int session_id;
	string status;
};

struct st_client
{
	struct lws *wsi;
	per_session_data *context;
};

struct st_session
{
	thread simulation_thread;
	volatile bool exit = false;
	Submarine *submarine;
	vector<st_client> clients;
};

map<unsigned int, st_session *> sessions;

void simulation(struct lws *wsi, per_session_data *context)
{
	st_session *session = sessions[context->session_id];
	
	session->submarine = new Submarine();
	
	double cur_time = GetDtime();
	
	double t0 = cur_time;
	int nsim = 0;
	while(true)
	{
		usleep(100000);
		
		if(session->exit)
			break;
		
		double t = GetDtime();
		double dt = t-cur_time;
		
		nsim++;
		if(t-t0>=1)
		{
			printf("%d sim / s\n", nsim);
			nsim = 0;
			t0 = t;
		}
		
		SimulationObject::StepSimulation(dt);
		
		cur_time += dt;
		
		string status = SimulationStatus::GetStatus(t).dump();
		if(status=="null")
			continue; // No new status to send due to throttling
		
		ws_mutex.lock();
		
		for(auto it = session->clients.begin(); it!=session->clients.end(); ++it)
		{
			it->context->status = status;
			lws_callback_on_writable(it->wsi);
		}
		
		ws_mutex.unlock();
		
		lws_cancel_service(ws_context);
	}
	
	delete session->submarine;
}

int callback_http(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len )
{
	switch( reason )
	{
		case LWS_CALLBACK_HTTP:
			lws_write(wsi, (unsigned char *)"HTTP/1.0 403 Forbidden\nContent-type: text/plain\n\nForbidden", 58, LWS_WRITE_HTTP);
			return -1;
		default:
			break;
	}

	return 0;
}
 
int callback_ws(struct lws *wsi, enum lws_callback_reasons reason, void *user, void *in, size_t len)
{
	per_session_data *context = (per_session_data *)user;
	const lws_protocols *protocol = lws_get_protocol(wsi);
	
	unsigned int session_id = 1;
	
	switch(reason)
	{
		case LWS_CALLBACK_PROTOCOL_INIT:
			break;
		
		case LWS_CALLBACK_PROTOCOL_DESTROY:
			break;
		
		case LWS_CALLBACK_ESTABLISHED:
		{
			ws_mutex.lock();
			
			context->session_id = session_id;
			
			if(sessions.find(context->session_id)==sessions.end())
			{
				st_session *session = new st_session();
				sessions[context->session_id] = session;
				
				session->clients.push_back({wsi, context});
				session->simulation_thread = std::thread(simulation, wsi, context);
				
			}
			else
			{
				auto it = sessions.begin();
				st_session *session = it->second;
				
				session->clients.push_back({wsi, context});
				
			}
			
			ws_mutex.unlock();
			
			break;
		}
		
		case LWS_CALLBACK_CLOSED:
		{
			ws_mutex.lock();
			
			auto it = sessions.find(context->session_id);
			st_session *session = it->second;
			if(session->clients.size()==1)
			{
				session->exit = true;
				session->simulation_thread.join();
				sessions.erase(context->session_id);
				delete session;
			}
			else
			{
				for(auto it2 = session->clients.begin(); it2!=session->clients.end(); ++it2)
				{
					if(it2->wsi==wsi)
					{
						session->clients.erase(it2);
						break;
					}
				}
			}
			
			ws_mutex.unlock();
			
			break;
		}
		
		case LWS_CALLBACK_RECEIVE:
		{
			string input_json_str((char *)in,len);
			
			json command = json::parse(input_json_str);
			
			auto it = sessions.find(context->session_id);
			st_session *session = it->second;
			
			session->submarine->HandleCommand(command);
			
			break;
		}
		
		case LWS_CALLBACK_SERVER_WRITEABLE:
		{
			string json_str = context->status;
			
			json_str.insert(0,LWS_PRE,' ');
			lws_write(wsi, (unsigned char *)json_str.c_str() + LWS_PRE, json_str.length()-LWS_PRE, LWS_WRITE_TEXT);
			break;
		}
		
		default:
			return 0;
	}
	
	return 0;
}

const struct lws_protocols protocols[] =
{
	{"http-only", callback_http, 0, 0},
	{
		"api",
		callback_ws,
		sizeof(per_session_data),
		32768,
		0
	},
	{0,0,0,0,0}
};

#include <Volume/Cylinder.h>
#include <Vector/Matrix3D.h>
#include <Map/Map.h>

int main(void)
{
	lws_set_log_level(LLL_ERR | LLL_WARN, 0);
	
	struct lws_context_creation_info info;
	memset( &info, 0, sizeof(info) );
	info.keepalive_timeout = 1;
	info.timeout_secs = 30;
	info.port = 7000;
	info.protocols = protocols;
	info.gid = -1;
	info.uid = -1;
	info.count_threads = 1;
	info.server_string = "evQueue websockets server";
	info.vhost_name = "default";

	ws_context = lws_create_context(&info);
	
	while( 1 )
	{
		lws_service(ws_context,10000);
	}
	
	return 0;
}
