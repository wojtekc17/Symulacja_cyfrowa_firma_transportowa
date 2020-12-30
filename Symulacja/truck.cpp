#include "truck.h"



Truck::Truck(Event_list* list, TransportCompany* transportcompany, int id, double size, int phase) : Process(list, id, size, phase)
{
	transportcompany_ = transportcompany;
	size_ = size;
}

double Truck::ExponentialDistributionGenerator(const int average)
{
	static default_random_engine generator(kSeed);
	const exponential_distribution<double> distribution(average);
	return 1 / distribution(generator);
}

double Truck::NormalDistributionGenerator(const pair<const int, const int> p)
{
	static default_random_engine generator(kSeed);
	normal_distribution<double> distribution(p.first, p.second);
	return distribution(generator);
}

Truck::~Truck()
{
	
}



void Truck::execute(const double new_time)
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
				phase_ = 8;
			}
			else 
			{
				phase_ = 10;
			}
			

		}break;
		case 2:
		{
			// DO POPRAWYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYYY OD TEGO MOMENTU XD
			cerr << "\n--> Faza 3: Koniec obslugi w platform";
			transportcompany_->platform_->RemoveTruckFromHQ(this);
			transportcompany_->platform_->WakeUpQueueForPlatform(transportcompany_->platform_->Free(), time()); // wybudza zdarzenie jeœli jest wolne miejsce								
			phase_ = 3;
			//active = false;
		}
		break;
		case 3:
		{
			cerr << "\n--> Faza 4: Przejazd ciezarowki";
			activate(time() + ExponentialDistributionGenerator(20)); // czas przejazdu do RD
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
			activate(time() + ExponentialDistributionGenerator(20));  // czas roz³adunku
			phase_ = 9;
			active = false;
		}break;
		case 6:
		{
			cerr << "\n--> Faza 7: Koniec obslugi w depot";
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
			activate(time() + ExponentialDistributionGenerator(20)); // czas powrotu do HQ
			phase_ = 0;
			active = false;
		}break;
		case 8:
		{
			cerr << "\n--> Faza 2.1: Zaladunek";
			cerr << "\nSIZEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEEE" << transportcompany_->platform_->QueueSizePack(); //sprawdzanie ile paczek jest w kolejce
			//cerr << "\nSIZE PACK INDEX" << transportcompany_->platform_->ReturnPackIndex();
			//cerr << "\nSIZE PACK" << transportcompany_->platform_->ReturnPackSize(transportcompany_->platform_->ReturnPackIndex());
			//transportcompany_->platform_->ReturnPackSize(transportcompany_->platform_->ReturnPackIndex()) > 10;

			if(transportcompany_->platform_->AddPackToTrack(this))
			{
				phase_ = 2;
				activate(time() + ExponentialDistributionGenerator(200));
			}
			else
			{
				phase_ = 8;
				activate(time() + ExponentialDistributionGenerator(10));
			}			
			//transportcompany_->platform_->PrintLictPack(this);
			 //chyba czas za³adunku			
			active = false;
		}break;
		case 9:
		{
			cerr << "\n--> Faza 6.1: Zaladunek";
			if (idx_ == 1)
			{
				if (transportcompany_->regionaldepots1_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					activate(time() + ExponentialDistributionGenerator(200));
				}
				else
				{
					phase_ = 9;
					activate(time() + ExponentialDistributionGenerator(10));
				}
			}
			else if (idx_ == 2)
			{
				if (transportcompany_->regionaldepots2_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					activate(time() + ExponentialDistributionGenerator(200));
				}
				else
				{
					phase_ = 9;
					activate(time() + ExponentialDistributionGenerator(10));
				}
			}
			else if (idx_ == 3)
			{
				if (transportcompany_->regionaldepots3_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					activate(time() + ExponentialDistributionGenerator(200));
				}
				else
				{
					phase_ = 9;
					activate(time() + ExponentialDistributionGenerator(10));
				}
			}
			else if (idx_ == 4)
			{
				if (transportcompany_->regionaldepots4_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					activate(time() + ExponentialDistributionGenerator(200));
				}
				else
				{
					phase_ = 9;
					activate(time() + ExponentialDistributionGenerator(10));
				}
			}
			else if (idx_ == 5)
			{
				if (transportcompany_->regionaldepots5_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					activate(time() + ExponentialDistributionGenerator(200));
				}
				else
				{
					phase_ = 9;
					activate(time() + ExponentialDistributionGenerator(10));
				}
			}
			else if (idx_ == 6)
			{
				if (transportcompany_->regionaldepots6_->AddPackToTrackRD(this))
				{
					phase_ = 6;
					activate(time() + ExponentialDistributionGenerator(200));
				}
				else
				{
					phase_ = 9;
					activate(time() + ExponentialDistributionGenerator(10));
				}
			}
			active = false;
		}break;
		case 10:
		{
			cerr << "\n--> Faza 6.2: Rozladunek";
			transportcompany_->platform_->ClearTruckHQ(this);
			activate(time() + ExponentialDistributionGenerator(200)); //czas rozladunku HQ
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