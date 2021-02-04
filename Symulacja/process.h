#pragma once
#include "Event_list.h"
#include <iostream>
#include <list>

class Process
{
public:
	Process(Event_list*, int, double, int, int);
	~Process();
	void virtual execute(double) = 0;
	double time();
	void Info();
	void activate(double);
	int id_;
	int id_p_;
	int phase_=-1;
	double size_;
	int idx_;
	bool terminated_;

	double tim;
	vector<Process*> pack_list_;
	Event_list* event_list_;
	void TimeUpdate(double);
private:
	Event* my_event_;

};

