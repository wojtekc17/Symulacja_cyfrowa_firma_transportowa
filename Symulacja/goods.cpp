#include "goods.h"
#include <iostream>


Goods::Goods(Event_list* list, TransportCompany* transportcompany, int id, double size, int phase) : Process(list, id, size, phase)
{
	transportcompany_ = transportcompany;
	size_ = size; //zmieniæ rozklad normalny
	id_ = rand()%6;
}

void Goods::execute(const double new_time)
{
	TimeUpdate(new_time);
	Info();
	auto active = true;
	while (active)
	{
		switch (phase_)
		{
		case 0:
		{
			cerr << "Nowa paczka HQ";
			Process* process = new Goods(event_list_, transportcompany_, id_, NormalDistributionGenerator(make_pair(2.0, 0.36)), 0);
			process->activate(time() + ExponentialDistributionGenerator(10));
			process = nullptr;
			transportcompany_->platform_->AddToQueuePack(this);
			//cerr << "SIZEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << transportcompany_->headquarters_->QueueSizePack();
			//phase_ = 1;
			active = false;
		}break;
		case 1:
		{
			cerr << "Nowa paczka RD---------------->"<< phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, NormalDistributionGenerator(make_pair(2.0, 0.36)), 1);
			process->activate(time() + ExponentialDistributionGenerator(100));
			process = nullptr;		
			transportcompany_->regionaldepots1_->AddToQueuePack(this);
			//cerr << "SIZEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << transportcompany_->headquarters_->QueueSizePack();
			//phase_ = 1;
			active = false;
		}break;
		case 2:
		{
			cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, NormalDistributionGenerator(make_pair(2.0, 0.36)), 2);
			process->activate(time() + ExponentialDistributionGenerator(70));
			process = nullptr;
			transportcompany_->regionaldepots2_->AddToQueuePack(this);
			active = false;
		}break;
		case 3:
		{
			cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, NormalDistributionGenerator(make_pair(2.0, 0.36)), 3);
			process->activate(time() + ExponentialDistributionGenerator(80));
			process = nullptr;
			transportcompany_->regionaldepots3_->AddToQueuePack(this);
			active = false;
		}break;
		case 4:
		{
			cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, NormalDistributionGenerator(make_pair(2.0, 0.36)), 4);
			process->activate(time() + ExponentialDistributionGenerator(90));
			process = nullptr;
			transportcompany_->regionaldepots4_->AddToQueuePack(this);
			active = false;
		}break;
		case 5:
		{
			cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, NormalDistributionGenerator(make_pair(2.0, 0.36)), 5);
			process->activate(time() + ExponentialDistributionGenerator(110));
			process = nullptr;
			transportcompany_->regionaldepots5_->AddToQueuePack(this);
			active = false;
		}break;
		case 6:
		{
			cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, NormalDistributionGenerator(make_pair(2.0, 0.36)), 6);
			process->activate(time() + ExponentialDistributionGenerator(50));
			process = nullptr;
			transportcompany_->regionaldepots6_->AddToQueuePack(this);
			active = false;
		}break;
		}
	}
}


Goods::~Goods()
{

}



double Goods::ExponentialDistributionGenerator(const int average)
{
	static default_random_engine generator(kSeed);
	const exponential_distribution<double> distribution(average);
	return 1 / distribution(generator);
}

double Goods::NormalDistributionGenerator(const pair<const double, const double> p)
{
	static default_random_engine generator(kSeed);
	normal_distribution<double> distribution(p.first, p.second);
	return distribution(generator);
}