#include "Event_list.h"
#include <iostream>
#include "process.h"    //used for avoid warnings
using namespace std;

void Event_list::AddNewEvent(Event* add_event)
{
    if (first_ == nullptr) //If list is empty add event on first
    {
        first_ = last_ = add_event;
    }
    else if (add_event->event_time_ <= first_->event_time_) //Add event on beginning
    {
        first_->prev_ = add_event;
        add_event->next_ = first_;
        first_ = add_event;
    }
    else if (add_event->event_time_ >= last_->event_time_) //Add event on end
    {
        add_event->prev_ = last_;
        last_->next_ = add_event;
        last_ = add_event;
    }
    else {
        Event* search = first_;
        while (search->event_time_ <= add_event->event_time_)
        {
            search = search->next_;
        }
        add_event->next_ = search;
        add_event->prev_ = search->prev_;
        search->prev_->next_ = add_event;
        search->prev_ = add_event;
        search = nullptr;
    }
}

double Event_list::FirstEventTime()
{
    if (first_ != nullptr)
        return first_->event_time_;
    return -1;
}

void Event_list::TestingFunction() const
{
    cout << "Event_list: Testing function:\n";
    if (first_ == nullptr || first_ == last_)
    {
        cout << "Nothing to test :(\n";
    }
    else
    {
        Event* temp = first_;
        while (temp != nullptr)       //a bit risky, consider (temp!=last_) with extra cout
        {
            cout << temp->event_time_ << "  ";
            temp = temp->next_;
        }
    }
    cin.get();
}

Event* Event_list::RemoveFirst()
{
    if (first_ != nullptr) {
        Event* first_event_from_list = first_;
        first_ = first_->next_;
        first_event_from_list->next_ = nullptr;
        first_event_from_list->prev_ = nullptr;
        return first_event_from_list;
    }
    cerr << "ERROR Event_list: There is no event to remove!\n";
    cin.get();
    return nullptr;
}