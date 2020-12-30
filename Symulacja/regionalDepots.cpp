#include <iostream>
#include "regionalDepots.h"
#include "truck.h"
#include "headquarters.h"


RegionalDepots::RegionalDepots()
{
	cerr << "\nMake Regional Depot";
	regional_depot_[0] = 0;
	
}
RegionalDepots::~RegionalDepots()
{

}

void RegionalDepots::AddToQueuePack(Process* pack)
{
	queue_pack_.push_back(pack);
}


void RegionalDepots::AddToQueueRegional(Process* truck)
{
	queue_.push(truck);
}

int RegionalDepots::Queuesize() const
{
	return static_cast<int>(queue_.size());
}

bool RegionalDepots::Free()
{
	if (size() < regional_depot_number_) return true;
	return false;
}

bool RegionalDepots::EnoughFreeSeats()
{
	int free = 0;
	if (regional_depot_[0] == 0)
	{
		free++;
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

void RegionalDepots::AddTruckToRegionalDepot()
{
	if (regional_depot_[0] == 0)
	{
		regional_depot_[0] = queue_.front()->id_;
		queue_.pop();
		return;
	}
	cerr << "ERROR RegionalDepots.cpp: There is no free RD desk!\n";
	cin.get();
}

void RegionalDepots::RemoveTruckFromRegionalDepot(Process* truck)
{
	if (regional_depot_[0] == truck->id_)
	{
		regional_depot_[0] = 0;
		return;
	}
	cerr << "ERROR RegionalDepots.cpp: There is no truck to remove!\n";
	cin.get();
}

void RegionalDepots::WakeUpQueueForHQ(const bool regional_depot, const double new_time)
{
	if (Queuesize()  && EnoughFreeSeats() && regional_depot)
	{
		queue_.front()->execute(new_time);
	}
}

void RegionalDepots::RegionalInfo()
{
	cerr << "\nRegional info";
	cerr << "\nKolejka do RD(wielkosc): " << queue_.size() << endl;
	int regional_size = 0;
	if (regional_depot_[0] != 0) regional_size++;
	cerr << "Zajêtosc RD(1-Tak, 0-Nie): " << regional_size << endl;
}

void RegionalDepots::ClearTruck(Process* truck)
{
	for (int i = 0; i < truck->pack_list_.size(); i++)
	{
		//truck->pack_list_[i]->terminated_ = true;
		delete truck->pack_list_[i];		
	}	
	//truck->idx_ = 0;
	truck->pack_list_.clear();
	truck->size_ = 10;
	cerr << "    Pack DELETE";
}

bool RegionalDepots::AddPackToTrackRD(Process* truck)
{
	int idx;
	if (QueueSizePack())
	{
		for (int i = 0; i < queue_pack_.size(); i++)
		{
			if (truck->size_ - queue_pack_[i]->size_ < 0)
			{
				truck->size_ -= queue_pack_[i]->size_;
				return true;
			}
			if (truck->size_ - queue_pack_[i]->size_ > 0)
			{
				truck->pack_list_.push_back(queue_pack_[i]);
				truck->size_ -= queue_pack_[i]->size_;
				queue_pack_.erase(queue_pack_.begin() + i);
			}

		}
	}
	return false;
}

int RegionalDepots::QueueSizePack() const
{
	return static_cast<int>(queue_pack_.size());
}

int RegionalDepots::size()
{
	int counter = regional_depot_number_;
	for (int i = 0; i < regional_depot_number_; ++i)
	{
		if (regional_depot_[0] == 0)--counter;
	}
	return counter;
}

