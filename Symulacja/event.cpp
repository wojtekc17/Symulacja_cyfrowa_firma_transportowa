#include "event.h"

Event::Event(Process* ptr) : event_time_(-1.0), proc_(ptr), next_(nullptr), prev_(nullptr)
{
}

Event::~Event()
{
}
