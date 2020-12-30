#pragma once
#include <queue>
#include "event.h"
using namespace std;

class Event_list
{

public:
    Event_list() = default;
    ~Event_list() = default;
    void AddNewEvent(Event* add_event);
    Event* RemoveFirst();
    //void DeleteEvent(int id);
    int AlarmDecimation(vector<int>*, bool&);
    double FirstEventTime();
    void TestingFunction() const;
private:
    Event* first_ = nullptr;
    Event* last_ = nullptr;
};
