#ifndef MODEL_REGIONALDEPOTS_H_
#define MODEL_REGIONALDEPOTS_H_

#include <queue>
#include "process.h"



class RegionalDepots
{
public:
	RegionalDepots();
	~RegionalDepots();
	void AddToQueuePack(Process*);
	void AddToQueueRegional(Process*);
	int Queuesize() const;
	bool Free();
	bool EnoughFreeSeats();
	void AddTruckToRegionalDepot();
	void RemoveTruckFromRegionalDepot(Process*);
	void WakeUpQueueForHQ(bool, double);
	void RegionalInfo();

	void ClearTruck(Process*);

	bool AddPackToTrackRD(Process*);
	int QueueSizePack() const;
	
private:
	queue<Process*> queue_;
	vector<Process*> queue_pack_;
	int regional_depot_[1];
	int size();
	const int regional_depot_number_ = 1;
	//const int nPlatformD_; //number of platform in regional depots
	//Truck* served_truck_;
	//std::queue<Truck*>
	//std::queue<Goods*>
};
#endif /*MODEL_REGIONALDEPOTS_H_*/