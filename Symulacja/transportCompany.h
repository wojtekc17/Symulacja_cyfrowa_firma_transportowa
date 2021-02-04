#ifndef MODEL_TransportCompany_H_
#define MODEL_TransportCompany_H_

//#include "truck.h"
#include <queue>
#include <random>
#include "platform.h"
#include "regionalDepots.h"

class TransportCompany
{
public:
	TransportCompany();
	~TransportCompany();

	//Headquarters* headquarters_;
	Platform* platform_;
	RegionalDepots* regionaldepots1_;
	RegionalDepots* regionaldepots2_;
	RegionalDepots* regionaldepots3_;
	RegionalDepots* regionaldepots4_;
	RegionalDepots* regionaldepots5_;
	RegionalDepots* regionaldepots6_;

	void AvarageTimePack(double);
	void PrintTimeAvarage();
	void PrintTimeAvaragePercentage(double);
	void WriteToExcel(double, double, string);
	void ClearExcel();

	void PrintStatistic(double);
	void ClearStatistic();

	double avarage_time_truck_ = 0;
	int avarage_licznik_ = 0;

private:
	int id_goods_ = 0;	
	//std::vector<TruckRegionalD*> //vector on regional depots
	
};

#endif /*MODEL_TransportCompany_H_*/