#include "transportCompany.h"
#include <iostream>
#include <fstream>
#include <string>

TransportCompany::TransportCompany()
{
	platform_ = new Platform;
	regionaldepots1_ = new RegionalDepots();
	regionaldepots2_ = new RegionalDepots();
	regionaldepots3_ = new RegionalDepots();
	regionaldepots4_ = new RegionalDepots();
	regionaldepots5_ = new RegionalDepots();
	regionaldepots6_ = new RegionalDepots();
}

TransportCompany::~TransportCompany()
{
	delete platform_;
	platform_ = nullptr;
	regionaldepots1_ = nullptr;
	regionaldepots2_ = nullptr;
	regionaldepots3_ = nullptr;
	regionaldepots4_ = nullptr;
	regionaldepots5_ = nullptr;
	regionaldepots6_ = nullptr;
}

void TransportCompany::AvarageTimePack(double time)
{
	avarage_time_truck_ += time;	
}

void TransportCompany::PrintTimeAvaragePercentage(double clock)
{
	//double avarage_time = avarage_time_truck;
	cerr << "\n Avarage percentage truck time use: " << (((avarage_time_truck_) / clock)/8) * 100 << "\n";
}

void TransportCompany::PrintTimeAvarage()
{
	//double avarage_time = avarage_time_truck;
	cerr << "\n Avarage truck time use: " << (avarage_time_truck_) / avarage_licznik_ << "\n";
}

void TransportCompany::WriteToExcel(double time_all, double time_truck, string excel_name)
{
	ofstream f;
	f.open(excel_name, ios::app);
	f << std::to_string((((time_truck / time_all))/8) * 100) + "," + std::to_string(time_truck) + "," + std::to_string(time_all) << endl;
	f.close();
}

void TransportCompany::ClearExcel()
{
	fstream f;
	f.open("excel/AvarageTimeTrack.csv", ofstream::out | ofstream::trunc);
	f.close();
}

void TransportCompany::PrintStatistic(double clock)
{
	cerr << "\n **************************Statistic*********************************************";
	PrintTimeAvaragePercentage(clock - 1000);
	PrintTimeAvarage();
	cerr << "\n *****************************HQ*************************************************";
	platform_->PrintAverageQueue();
	platform_->PrintAverageTimePack();
	cerr << "\n *****************************RD*************************************************";
	cerr << "\n RD1";
	regionaldepots1_->PrintAverageQueue();
	regionaldepots1_->PrintAverageTimePack();
	cerr << "\n RD2";
	regionaldepots2_->PrintAverageQueue();
	regionaldepots2_->PrintAverageTimePack();
	cerr << "\n RD3";
	regionaldepots3_->PrintAverageQueue();
	regionaldepots3_->PrintAverageTimePack();
	cerr << "\n RD4";
	regionaldepots4_->PrintAverageQueue();
	regionaldepots4_->PrintAverageTimePack();
	cerr << "\n RD5";
	regionaldepots5_->PrintAverageQueue();
	regionaldepots5_->PrintAverageTimePack();
	cerr << "\n RD6";
	regionaldepots6_->PrintAverageQueue();
	regionaldepots6_->PrintAverageTimePack();
	cerr << "\n";
}

void TransportCompany::ClearStatistic()
{
	avarage_time_truck_ = 0;
	avarage_licznik_ = 0;
	platform_->ClearStatisticHQ();
	regionaldepots1_->ClearStatisticRD();
	regionaldepots2_->ClearStatisticRD();
	regionaldepots3_->ClearStatisticRD();
	regionaldepots4_->ClearStatisticRD();
	regionaldepots5_->ClearStatisticRD();
	regionaldepots6_->ClearStatisticRD();
}
