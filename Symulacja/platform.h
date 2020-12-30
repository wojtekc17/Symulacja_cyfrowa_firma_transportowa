#pragma once
#include "process.h"
#include <list>

class Platform
{
public:
	Platform();
	~Platform();
	bool Free(); // czy jest wolne miejsce
	void AddToQueue(Process*);
	void AddTruckToPlatform();
	void RemoveTruckFromHQ(Process*);
	void PlatformInfo();
	bool EnoughFreeSeats();
	int QueueSize() const;
	void WakeUpQueueForPlatform(bool, double);

	void AddToQueuePack(Process*);
	int QueueSizePack() const;
	double ReturnPackSize(int);
	int ReturnPackIndex();

	bool AddPackToTrack(Process*);
	void ClearPackFromTrack(Process*);
	void PrintLictPack(Process*);
	bool AmountPackOnTruck(Process*);
	double ActualTrackSize(Process*);
	void ClearTruckHQ(Process*);
	int ReturnPackinTrack(Process*);


	void LoadTruck(Process*, queue<Process*>);
private:
	queue<Process*> queue_;
	vector<Process*> queue_pack_;
	queue<Process*> pending_processes_;

	//bool is_free_;
	//list<Platform*> platform_;
	const int platform_number = 3; //iloœæ platform
	int platform_[3];
	int size(); // zwraca iloœæ wolnych platform
	//bool status_;
};



