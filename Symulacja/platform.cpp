#include "platform.h"
#include <random>
#include <fstream>
#include <string>

void Platform::AddToQueue(Process* truck)
{
	queue_.push(truck);
}

void Platform::AddTruckToPlatform()
{
	if (queue_.empty() == false)
	{
		for (int i = 0; i < platform_number; i++)
		{
			if (platform_[i] == 0) //sptawdzenie pustej platformy
			{				
				platform_[i] = queue_.front()->id_;
				queue_.pop();
				return;
			}
		}

	}
	cerr << "ERROR Platform: There is no free platform!\n";
	cin.get();
}


void Platform::RemoveTruckFromHQ(Process* truck)
{
	cerr << "\ntest:" << truck->id_;
	for (int i = 0; i < platform_number; i++)
	{
		if (platform_[i] == truck->id_)
		{
			platform_[i] = 0;
			cerr << "\n+-------------";
			return;
		}
	}
	cerr << "ERROR Platform: There is no truck to remove!\n";
	cin.get();
}

void Platform::PlatformInfo()
{
	cerr << "\nPlatform info";
	cerr << "\nKolejka do platformy(wielkosc): " << queue_.size() << endl;
	int platform_size = 0;
	for (int i = 0; i < platform_number; i++)
	{
		if (platform_[i] != 0) platform_size++;
	}
	cerr << "Zajete stanowiska platform: " << platform_size << endl;
}

bool Platform::EnoughFreeSeats()
{
	int free = 0;
	for (int i = 0; i < platform_number; ++i)
	{
		if (platform_[i] != 0)
		{
			free++;
		}
	}
	if (queue_.empty() == false)
	{
		if (free > 0)
		{
			return true;
		}
	}
	return false;
}



int Platform::QueueSize() const
{
	return static_cast<int>(queue_.size());
}

void Platform::WakeUpQueueForPlatform(const bool platform, const double new_time)
{
	if (QueueSize() && EnoughFreeSeats() && platform)
	{
		queue_.front()->execute(new_time);
	}

}

void Platform::AverageQueuePack()
{
	average_counter_ += 1;
	average_queue_ += queue_pack_.size();
}

void Platform::PrintAverageQueue()
{
	cerr << "\n Avarage pack queue size: " << average_queue_ / average_counter_;
}

void Platform::PrintAverageTimePack()
{
	cerr << "\n Avarage time pack in queue: " << time_pack_ / cunter_pack_;
}

void Platform::ClearStatisticHQ()
{
	time_pack_ = 0;
	cunter_pack_ = 0;

	average_counter_ = 0;
	average_queue_ = 0;
}



void Platform::AddToQueuePack(Process* pack)
{
	queue_pack_.push_back(pack);
}

int Platform::QueueSizePack() const
{
	return static_cast<int>(queue_pack_.size());
}



double Platform::ReturnPackSize(int index)
{
	double size = 0;
	if (QueueSizePack())
	{
		
		for (int i = 0; i < queue_pack_.size(); i++)
		{
			if (queue_pack_[i]->id_ == index)
			{
				size += queue_pack_[i]->size_;
			}
		}
	}
	return size;
}

int Platform::ReturnPackIndex()
{
	if (QueueSizePack())
	{
		return queue_pack_.front()->id_;
	}
}


bool Platform::AddPackToTrack(Process* truck)
{	
	if (QueueSizePack())
	{		
		if (truck->idx_ == 0)
		{		
			truck->idx_ = queue_pack_.front()->id_;
		}		
		for (int i = 0; i < queue_pack_.size(); i++)
		{
			if (truck->size_ - queue_pack_[i]->size_ < 0)
			{
				truck->size_ -= queue_pack_[i]->size_;
				return true;
			}
			if (truck->idx_ == queue_pack_[i]->id_ && truck->size_ - queue_pack_[i]->size_ > 0)
			{
				if (truck->tim - queue_pack_[i]->tim >= 0)
				{
					time_pack_ += truck->tim - queue_pack_[i]->tim;
				}
				cunter_pack_ += 1;
				truck->pack_list_.push_back(queue_pack_[i]);
				truck->size_ -= queue_pack_[i]->size_;
				queue_pack_.erase(queue_pack_.begin() + i);
			}

		}
	}
	return false;
}

void Platform::ClearPackFromTrack(Process* truck)
{
	truck->pack_list_.clear();
}

void Platform::PrintLictPack(Process* truck)
{
	for (int i = 0; i < truck->pack_list_.size(); i++)
	{
		cerr << " " << truck->pack_list_[i]->id_;
	}
}

bool Platform::AmountPackOnTruck(Process* truck)
{
	if (truck->pack_list_.size() == 0)
	{
		return true;
	}
	return false;
}

double Platform::ActualTrackSize(Process* truck)
{
	return truck->size_;
}

void Platform::ClearTruckHQ(Process* truck)
{
	for (int i = 0; i < truck->pack_list_.size(); i++)
	{
		//truck->pack_list_[i]->terminated_ = true;
		delete truck->pack_list_[i];
	}
	
	truck->idx_ = 0;
	truck->pack_list_.clear();
	truck->size_ = 10;
	cerr << "    Pack DELETE";
}

int Platform::ReturnPackinTrack(Process* truck)
{
	return truck->pack_list_.size();
}

Platform::Platform()
{
	cerr << "Make platform\n";
	for (int i = 0; i < platform_number; i++)
	{
		platform_[i] = 0;
	}
}

Platform::~Platform()
{
	cerr << "Delete Platform\n";
}

bool Platform::Free()
{
	if (size() < 3) return true;
	return false;
}

int Platform::size()
{
	int counter = platform_number;
	for (int i = 0; i < platform_number; ++i)
	{
		if (platform_[i] == 0)--counter;
	}
	return counter;
}



