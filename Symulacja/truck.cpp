#include "truck.h"
#include <fstream>
#include <string>


Truck::Truck(Event_list* list, TransportCompany* transportcompany, int id, double size, int phase, int id_p) : Process(list, id, size, phase, id_p)
{
	transportcompany_ = transportcompany;
	size_ = size;
}


Truck::~Truck()
{
	
}


void Truck::execute(const double new_time)
{
	cerr << "\n ********************************************************************************************************";
	TimeUpdate(new_time);
	Info();
	auto active = true;
	while (active)
	{
		switch (phase_)
		{
		case 0:
		{

			cerr << "\n--> Faza 1: Dodanie samochodu do kolejki HQ";
			transportcompany_->platform_->AddToQueue(this);
			if (transportcompany_->platform_->Free() == false)
			{
				active = false;
			}
			phase_ = 1;
		}break;
		case 1:
		{
			cerr << "\n--> Faza 2: Poczatek obslugi w Platform";
			transportcompany_->platform_->AddTruckToPlatform(); // dodaje samochód do platformy					
			if (transportcompany_->platform_->ReturnPackinTrack(this) == 0)
			{
				this->tim = time();
				phase_ = 8; // Je¿eli jest pusty Zaladunek
			}
			else 
			{
				phase_ = 10; // Je¿eli jest pe³ny Rozladunek
			}		
		}break;
		case 2:
		{
			cerr << "\n--> Faza 3: Koniec obslugi w platform";
			transportcompany_->platform_->RemoveTruckFromHQ(this);
			//transportcompany_->platform_->RemovePendingProcess(this);
			transportcompany_->platform_->WakeUpQueueForPlatform(transportcompany_->platform_->Free(), time()); // wybudza zdarzenie jeœli jest wolne miejsce								
			phase_ = 3;
		}
		break;
		case 3:
		{
			cerr << "\n--> Faza 4: Przejazd ciezarowki";
			double timee = Generators::NormalDistributionGenerator(make_pair(20.0, 1.6 * 1.6)); // czas przejazdu do RD ut = 20, ni^2= 1,6^2 
			transportcompany_->AvarageTimePack(timee);
			transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
			activate(time() + timee); 
			phase_ = 4;
			active = false;
		}break;
		case 4:
		{
			cerr << "\n--> Faza 5: Ustawienie sie w kolejce do regional depot";
			if (idx_ == 1)
			{
				transportcompany_->regionaldepots1_->AddToQueueRegional(this); // dodanie do kolejki regional depot			
				if (transportcompany_->regionaldepots1_->Free() == false) // sprawdzenie czy jest pusty regional depot jezeli nie(false) to czekaj
				{
					active = false;
				}
			}
			else if (idx_ == 2)
			{
				transportcompany_->regionaldepots2_->AddToQueueRegional(this); // dodanie do kolejki regional depot			
				if (transportcompany_->regionaldepots2_->Free() == false) // sprawdzenie czy jest pusty regional depot jezeli nie(false) to czekaj
				{
					active = false;
				}
			}
			else if (idx_ == 3)
			{
				transportcompany_->regionaldepots3_->AddToQueueRegional(this); // dodanie do kolejki regional depot			
				if (transportcompany_->regionaldepots3_->Free() == false) // sprawdzenie czy jest pusty regional depot jezeli nie(false) to czekaj
				{
					active = false;
				}
			}
			else if (idx_ == 4)
			{
				transportcompany_->regionaldepots4_->AddToQueueRegional(this); // dodanie do kolejki regional depot			
				if (transportcompany_->regionaldepots4_->Free() == false) // sprawdzenie czy jest pusty regional depot jezeli nie(false) to czekaj
				{
					active = false;
				}
			}
			else if (idx_ == 5)
			{
				transportcompany_->regionaldepots5_->AddToQueueRegional(this); // dodanie do kolejki regional depot			
				if (transportcompany_->regionaldepots5_->Free() == false) // sprawdzenie czy jest pusty regional depot jezeli nie(false) to czekaj
				{
					active = false;
				}
			}
			else if (idx_ == 6)
			{
				transportcompany_->regionaldepots6_->AddToQueueRegional(this); // dodanie do kolejki regional depot			
				if (transportcompany_->regionaldepots6_->Free() == false) // sprawdzenie czy jest pusty regional depot jezeli nie(false) to czekaj
				{
					active = false;
				}
			}
			phase_ = 5;
		}break;
		case 5:
		{
			cerr << "\n--> Faza 6: Rozpoczecie obslugi przy regional Depot\n";
			double timee = 0;
			for (size_t i = 0; i < this->pack_list_.size(); i++)
			{
				timee += this->pack_list_[i]->size_ * 0.7; // size_pack * Tu
			}
			transportcompany_->AvarageTimePack(timee);
			transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
			if (idx_ == 1)
			{
				transportcompany_->regionaldepots1_->AddTruckToRegionalDepot(); // dodanie do regional depot trucka
				transportcompany_->regionaldepots1_->ClearTruck(this); // rozladunek
			}
			else if (idx_ == 2)
			{
				transportcompany_->regionaldepots2_->AddTruckToRegionalDepot(); // dodanie do regional depot trucka
				transportcompany_->regionaldepots2_->ClearTruck(this); // rozladunek
			}
			else if (idx_ == 3)
			{
				transportcompany_->regionaldepots3_->AddTruckToRegionalDepot(); // dodanie do regional depot trucka
				transportcompany_->regionaldepots3_->ClearTruck(this); // rozladunek
			}
			else if (idx_ == 4)
			{
				transportcompany_->regionaldepots4_->AddTruckToRegionalDepot(); // dodanie do regional depot trucka
				transportcompany_->regionaldepots4_->ClearTruck(this); // rozladunek
			}
			else if (idx_ == 5)
			{
				transportcompany_->regionaldepots5_->AddTruckToRegionalDepot(); // dodanie do regional depot trucka
				transportcompany_->regionaldepots5_->ClearTruck(this); // rozladunek
			}
			else if (idx_ == 6)
			{
				transportcompany_->regionaldepots6_->AddTruckToRegionalDepot(); // dodanie do regional depot trucka
				transportcompany_->regionaldepots6_->ClearTruck(this); // rozladunek
			}
			cerr << "\n--> Faza 2.2: Rozladunek\n";
			this->tim = time() + timee;
			activate(time() + timee);  // czas roz³adunku
			phase_ = 9;
			active = false;
		}break;
		case 6:
		{
			cerr << "\n--> Faza 7: Koniec obslugi w depot";
			/*
			ofstream f;
			f.open("excel/RD_RemoveFromPlatform.csv", ios::app);
			f << std::to_string(this->id_) + "," + std::to_string(time()) << endl;
			f.close();
			*/
			if (idx_ == 1)
			{
				transportcompany_->regionaldepots1_->RemoveTruckFromRegionalDepot(this); // usuniecie trucka z regional depot
				transportcompany_->regionaldepots1_->WakeUpQueueForHQ(transportcompany_->regionaldepots1_->Free(), time()); // obudzenie kolejki do regional depot jesli zwolnilo sie miejsce			

			}
			else if (idx_ == 2)
			{
				transportcompany_->regionaldepots2_->RemoveTruckFromRegionalDepot(this); // usuniecie trucka z regional depot
				transportcompany_->regionaldepots2_->WakeUpQueueForHQ(transportcompany_->regionaldepots2_->Free(), time()); // obudzenie kolejki do regional depot jesli zwolnilo sie miejsce			

			}
			else if (idx_ == 3)
			{
				transportcompany_->regionaldepots3_->RemoveTruckFromRegionalDepot(this); // usuniecie trucka z regional depot
				transportcompany_->regionaldepots3_->WakeUpQueueForHQ(transportcompany_->regionaldepots3_->Free(), time()); // obudzenie kolejki do regional depot jesli zwolnilo sie miejsce			

			}
			else if (idx_ == 4)
			{
				transportcompany_->regionaldepots4_->RemoveTruckFromRegionalDepot(this); // usuniecie trucka z regional depot
				transportcompany_->regionaldepots4_->WakeUpQueueForHQ(transportcompany_->regionaldepots4_->Free(), time()); // obudzenie kolejki do regional depot jesli zwolnilo sie miejsce			

			}
			else if (idx_ == 5)
			{
				transportcompany_->regionaldepots5_->RemoveTruckFromRegionalDepot(this); // usuniecie trucka z regional depot
				transportcompany_->regionaldepots5_->WakeUpQueueForHQ(transportcompany_->regionaldepots5_->Free(), time()); // obudzenie kolejki do regional depot jesli zwolnilo sie miejsce			

			}
			else if (idx_ == 6)
			{
				transportcompany_->regionaldepots6_->RemoveTruckFromRegionalDepot(this); // usuniecie trucka z regional depot
				transportcompany_->regionaldepots6_->WakeUpQueueForHQ(transportcompany_->regionaldepots6_->Free(), time()); // obudzenie kolejki do regional depot jesli zwolnilo sie miejsce			

			}
			phase_ = 7;

			//active = false;
		}break;
		case 7:
		{
			cerr << "\n--> Faza 8: Powrot ciezarowki do HQ";
			double timee = Generators::NormalDistributionGenerator(make_pair(20.0, 1.6 * 1.6)); // czas przejazdu do RD ut = 20, ni^2= 1,6^2 
			transportcompany_->AvarageTimePack(timee);
			transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
			activate(time() + timee);
			phase_ = 0;
			active = false;
		}break;
		case 8:
		{
			cerr << "\n--> Faza 2.1: Zaladunek";
			//cerr << "\nHQpack -------->" << transportcompany_->platform_->QueueSizePack(); //sprawdzanie ile paczek jest w kolejce
			
			if(transportcompany_->platform_->AddPackToTrack(this))
			{			
				transportcompany_->avarage_licznik_ += 1;
				//transportcompany_->platform_->RemovePendingProcess(this);
				double timee = 0;				
				for (size_t i = 0; i < this->pack_list_.size(); i++)
				{
					timee += this->pack_list_[i]->size_ * 0.5; // size_pack * Ti
				}
				transportcompany_->AvarageTimePack(timee);
				transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
				activate(time() + timee);
				phase_ = 2;
			}
			else
			{
				phase_ = 8;
				activate(time() + 5);
			}					
			active = false;
		}break;
		case 9:
		{
			cerr << "\n--> Faza 6.1: Zaladunek";
			double timee = 0;
			if (idx_ == 1)
			{
				if (transportcompany_->regionaldepots1_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					for (size_t i = 0; i < this->pack_list_.size(); i++)
					{
						timee += this->pack_list_[i]->size_ * 0.5; // size_pack * Ti
					}
					transportcompany_->AvarageTimePack(timee);
					transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
					activate(time() + timee);
				}
				else
				{
					phase_ = 9;
					activate(time() + 25);
				}
			}
			else if (idx_ == 2)
			{
				if (transportcompany_->regionaldepots2_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					for (size_t i = 0; i < this->pack_list_.size(); i++)
					{
						timee += this->pack_list_[i]->size_ * 0.5; // size_pack * Ti
					}
					transportcompany_->AvarageTimePack(timee);
					transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
					activate(time() + timee);
				}
				else
				{
					phase_ = 9;
					activate(time() + 25);
				}
			}
			else if (idx_ == 3)
			{
				if (transportcompany_->regionaldepots3_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					for (size_t i = 0; i < this->pack_list_.size(); i++)
					{
						timee += this->pack_list_[i]->size_ * 0.5; // size_pack * Ti
					}
					transportcompany_->AvarageTimePack(timee);
					transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
					activate(time() + timee);
				}
				else
				{
					phase_ = 9;
					activate(time() + 25);
				}
			}
			else if (idx_ == 4)
			{
				if (transportcompany_->regionaldepots4_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					for (size_t i = 0; i < this->pack_list_.size(); i++)
					{
						timee += this->pack_list_[i]->size_ * 0.5; // size_pack * Ti
					}
					transportcompany_->AvarageTimePack(timee);
					transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
					activate(time() + timee);
				}
				else
				{
					phase_ = 9;
					activate(time() + 25);
				}
			}
			else if (idx_ == 5)
			{
				if (transportcompany_->regionaldepots5_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					for (size_t i = 0; i < this->pack_list_.size(); i++)
					{
						timee += this->pack_list_[i]->size_ * 0.5; // size_pack * Ti
					}
					transportcompany_->AvarageTimePack(timee);
					transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
					activate(time() + timee);
				}
				else
				{
					phase_ = 9;
					activate(time() + 25);
				}
			}
			else if (idx_ == 6)
			{
				if (transportcompany_->regionaldepots6_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					for (size_t i = 0; i < this->pack_list_.size(); i++)
					{
						timee += this->pack_list_[i]->size_ * 0.5; // size_pack * Ti
					}
					transportcompany_->AvarageTimePack(timee);
					transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
					activate(time() + timee);
				}
				else
				{
					phase_ = 9;
					activate(time() + 25);
				}
			}
			active = false;
		}break;
		case 10:
		{
			cerr << "\n--> Faza 6.2: Rozladunek";		
			//transportcompany_->platform_->AddToQueuePendingProces(this);
			double timee = 0;
			for (size_t i = 0; i < this->pack_list_.size(); i++)
			{
				timee += this->pack_list_[i]->size_ * 0.7; // size_pack * Ti
			}
			transportcompany_->AvarageTimePack(timee);
			transportcompany_->WriteToExcel(time() + timee, transportcompany_->avarage_time_truck_, "excel/AvarageTimeTrack.csv");
			transportcompany_->platform_->ClearTruckHQ(this);
			activate(time() + timee);
			this->tim = time() + timee;
			phase_ = 8;
			active = false;
		}break;
		}
	}
	
	transportcompany_->platform_->PlatformInfo(); //info aktualne o platformie
	transportcompany_->regionaldepots1_->RegionalInfo(); // info aktualne o regional depot
	transportcompany_->regionaldepots2_->RegionalInfo();
	transportcompany_->regionaldepots3_->RegionalInfo();
	transportcompany_->regionaldepots4_->RegionalInfo();
	transportcompany_->regionaldepots5_->RegionalInfo();
	transportcompany_->regionaldepots6_->RegionalInfo();
}
