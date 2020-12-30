#include "process.h"

Process::Process(Event_list* listt, int id, double size, int phase) : terminated_(false), event_list_(listt), id_(++id), size_(size), phase_(phase)
{
	cerr << "\nProcess: New process created!";
	my_event_ = new Event(this);
	idx_ = 0;
	
}

Process::~Process()
{
	cout << "Process destruktor\n";
	delete my_event_;
}

double Process::time()
{
	return my_event_->event_time_;
}

void Process::Info()
{
	cout << "\nID: " << id_ << "  FAZA: " << phase_<<"   CZAS: " << time() << endl;
}

void Process::activate(const double time)
{

		cout << "\nscheduled time: " << time << endl;
		my_event_->event_time_ = time;
		event_list_->AddNewEvent(my_event_);
}

void Process::TimeUpdate(const double new_time)
{
	my_event_->event_time_ = new_time;
}


