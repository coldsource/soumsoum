#include <Submarine/Pump.h>

#include <float.h>

Pump::Pump(const Fluid &fluid, double flow, Tank *src, Tank *dst)
{
	this->fluid = fluid.clone();
	this->flow = flow;
	this->src = src;
	this->dst = dst;
}

Pump::~Pump()
{
	delete this->fluid;
}

void Pump::SetRate(double flow_rate)
{
	if(flow_rate<0)
		flow_rate = 0;
	if(flow_rate>1)
		flow_rate = 1;
	
	this->flow_rate = flow_rate;
}

void Pump::Transfer(double volume)
{
	volume_to_transfer = volume;
}

void Pump::On(void)
{
	Transfer(DBL_MAX);
}

void Pump::Off(void)
{
	Transfer(0);
}

void Pump::StepTime(double dt)
{
	if(volume_to_transfer==0)
		return;
	
	double v = flow * flow_rate * dt;
	if(v>=volume_to_transfer)
		v = volume_to_transfer;
	
	double rv;
	if(src)
		rv = src->Empty(*fluid, v);
	else
		rv = v;
	
	if(dst)
		dst->Fill(*fluid, rv);
	
	if(rv<v)
		volume_to_transfer = 0;
	else if(volume_to_transfer!=DBL_MAX)
		volume_to_transfer -= rv;
}

Pump &Pump::operator=(const Pump &p)
{
	delete fluid;
	fluid = p.fluid->clone();
	flow = p.flow;
	flow_rate = p.flow_rate;
	src = p.src;
	dst = p.dst;
	
	return *this;
}
