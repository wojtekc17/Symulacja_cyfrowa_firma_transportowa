#include "transportCompany.h"
#include <iostream>


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
}

void TransportCompany::WakeUp(double)
{

}

int TransportCompany::GetIDGoods()
{
	//generuj id od 1 do 6 
	return  rand() % 6 + 1;
}

void TransportCompany::IncIDGoods()
{
	id_goods_++;
}
