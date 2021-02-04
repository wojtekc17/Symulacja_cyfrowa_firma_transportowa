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

	void AverageQueuePack();
	void PrintAverageQueue();
	void PrintAverageTimePack();
	void ClearStatisticRD();


	
private:
	queue<Process*> queue_;
	vector<Process*> queue_pack_;
	int regional_depot_[1];
	int size();
	const int regional_depot_number_ = 1;
	double time_pack_ = 0;
	int cunter_pack_ = 0;

	int average_counter_ = 0;
	int average_queue_ = 0;

};
#endif /*MODEL_REGIONALDEPOTS_H_*/