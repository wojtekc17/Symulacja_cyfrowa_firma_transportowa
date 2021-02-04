#include "goods.h"
#include <iostream>
#include <fstream>
#include <string>


Goods::Goods(Event_list* list, TransportCompany* transportcompany, int id, double size, int phase, int id_p) : Process(list, id, size, phase, id_p)
{
	transportcompany_ = transportcompany;
	size_ = size; //zmieniæ rozklad normalny
	id_ = Generators::Distribution(); // losowe id rozk³ad równomierny
}

void Goods::execute(const double new_time)
{
	TimeUpdate(new_time);
	//Info();
	auto active = true;
	while (active)
	{
		switch (phase_)
		{
		case 0:
		{
			//cerr << "Nowa paczka HQ";
			Process* process = new Goods(event_list_, transportcompany_, id_, Generators::NormalDistributionGenerator(make_pair(2.0, 0.36)), 0, id_p_);
			this->tim = time();
			process->activate(time() + Generators::ExponentialDistributionGenerator(2.2));
			process = nullptr;	
			transportcompany_->platform_->AddToQueuePack(this);
			transportcompany_->platform_->AverageQueuePack();
			active = false;
		}break;
		case 1:
		{
			//cerr << "Nowa paczka RD---------------->"<< phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, Generators::NormalDistributionGenerator(make_pair(2.0, 0.36)), 1, id_p_);
			this->tim = time();
			process->activate(time() + Generators::ExponentialDistributionGenerator(12.3));
			process = nullptr;		
			transportcompany_->regionaldepots1_->AddToQueuePack(this);
			transportcompany_->regionaldepots1_->AverageQueuePack();
			active = false;
		}break;
		case 2:
		{
			//cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, Generators::NormalDistributionGenerator(make_pair(2.0, 0.36)), 2, id_p_);
			this->tim = time();
			process->activate(time() + Generators::ExponentialDistributionGenerator(12.3));
			process = nullptr;			
			transportcompany_->regionaldepots2_->AddToQueuePack(this);
			transportcompany_->regionaldepots2_->AverageQueuePack();
			active = false;
		}break;
		case 3:
		{
			//cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, Generators::NormalDistributionGenerator(make_pair(2.0, 0.36)), 3, id_p_);
			this->tim = time();
			process->activate(time() + Generators::ExponentialDistributionGenerator(12.3));
			process = nullptr;		
			transportcompany_->regionaldepots3_->AddToQueuePack(this);
			transportcompany_->regionaldepots3_->AverageQueuePack();
			active = false;
		}break;
		case 4:
		{
			//cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, Generators::NormalDistributionGenerator(make_pair(2.0, 0.36)), 4, id_p_);
			this->tim = time();
			process->activate(time() + Generators::ExponentialDistributionGenerator(12.3));
			process = nullptr;
			transportcompany_->regionaldepots4_->AddToQueuePack(this);
			transportcompany_->regionaldepots4_->AverageQueuePack();
			active = false;
		}break;
		case 5:
		{
			//cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, Generators::NormalDistributionGenerator(make_pair(2.0, 0.36)), 5, id_p_);
			this->tim = time();
			process->activate(time() + Generators::ExponentialDistributionGenerator(12.3));
			process = nullptr;
			transportcompany_->regionaldepots5_->AddToQueuePack(this);
			transportcompany_->regionaldepots5_->AverageQueuePack();
			active = false;
		}break;
		case 6:
		{
			//cerr << "Nowa paczka RD---------------->" << phase_;
			Process* process = new Goods(event_list_, transportcompany_, id_, Generators::NormalDistributionGenerator(make_pair(2.0, 0.36)), 6, id_p_);
			this->tim = time();
			process->activate(time() + Generators::ExponentialDistributionGenerator(12.3));
			process = nullptr;
			transportcompany_->regionaldepots6_->AddToQueuePack(this);
			transportcompany_->regionaldepots6_->AverageQueuePack();
			active = false;
		}break;
		}
	}
}

Goods::~Goods()
{
}

