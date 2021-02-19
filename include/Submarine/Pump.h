#ifndef _PUMP_H_
#define _PUMP_H_

#include <Simulation/SimulationObject.h>
#include <Submarine/Tank.h>
#include <Fluid/Fluid.h>

class Pump: public SimulationObject
{
	Fluid *fluid;
	double flow;
	double flow_rate = 1;
	Tank *src;
	Tank *dst;
	
	double volume_to_transfer = 0;
	double volume_transferred = 0;
	
public:
	Pump(const Fluid &fluid, double flow, Tank *src, Tank *dst);
	~Pump();
	
	void SetRate(double flow_rate);
	double GetRate() const { return flow_rate; }
	
	void Transfer(double volume);
	void On(void);
	void Off(void);
	
	void StepTime(double dt);
	
	Pump &operator=(const Pump &p);
};

#endif
