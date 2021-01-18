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

struct lws_context *ws_context;

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
	std::thread simulation_thread;
	Submarine *submarine;
	volatile bool exit = false;
};

void simulation(struct lws *wsi, per_session_data *context)
{
	context->submarine = new Submarine();
	
	double cur_time = GetDtime();
	while(true)
	{
		usleep(100000);
		
		if(context->exit)
			break;
		
		double dt = GetDtime()-cur_time;
		
		SimulationObject::StepSimulation(dt);
		
		lws_callback_on_writable(wsi);
		lws_cancel_service(ws_context);
		
		cur_time += dt;
	}
	
	delete context->submarine;
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
	
	switch(reason)
	{
		case LWS_CALLBACK_PROTOCOL_INIT:
			break;
		
		case LWS_CALLBACK_PROTOCOL_DESTROY:
			break;
		
		case LWS_CALLBACK_ESTABLISHED:
		{
			context->simulation_thread = std::thread(simulation, wsi, context);
			break;
		}
		
		case LWS_CALLBACK_CLOSED:
		{
			context->exit = true;
			context->simulation_thread.join();
			break;
		}
		
		case LWS_CALLBACK_RECEIVE:
		{
			string input_json_str((char *)in,len);
			
			printf("%s\n",input_json_str.c_str());
			json command = json::parse(input_json_str);
			
			context->submarine->HandleCommand(command);
			break;
		}
		
		case LWS_CALLBACK_SERVER_WRITEABLE:
		{
			json j = context->submarine->ToJson();
			string json_str = j.dump();
			
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
