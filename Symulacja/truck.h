
#ifndef MODEL_TRUCK_H_
#define MODEL_TRUCK_H_
#include "transportCompany.h"
#include "process.h"
#include "event_list.h"
#include "generators.h"
#include <random>
#include <list>
#include <string>

class Truck : public Process
{
public:
	~Truck();
	explicit Truck(Event_list*, TransportCompany*, int, double, int, int);
	void execute(double) override;
	TransportCompany* transportcompany_;

private:	
	int temp_ = 0;

};

#endif /*MODEL_TRUCK_H_*/