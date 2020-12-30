#include <iostream>
#include <random>
#include "transportCompany.h"
#include "truck.h"
#include "event_list.h"
#include "goods.h"
#include "logger.h"
using namespace std;

static const int kSeed = 123456;
const int WspQ = 127773;
const int WspR = 2836;
const int Range = 2147483647;
double _time = 6000000;

// Rozklad jednosyajny
static double Distribution()
{
	auto h = (int)((_time) / WspQ);                                              //H =ziarno / 127773
	(_time) = 16807 * ((_time)-WspQ * h) - WspR * h;                      //X = 16807 * ((ziarno - (127773 *H)) - (2836*H)
	if ((_time) < 0) (_time) += Range;                                       // (ziarno<0) ziarno+2147483647
	return (double)_time / (double)Range;                                       // ziarno/Range
}

// Rozklad normalny
static double NormalDistributionGenerator(const pair<const double, const double> p)
{
	static default_random_engine generator(kSeed);
	normal_distribution<double> distribution(p.first, p.second);
	return distribution(generator);
}

// Rozklad wykladniczy
static double ExponentialDistributionGenerator(const int average)
{
	static default_random_engine generator(kSeed);
	const exponential_distribution<double> distribution(average);
	return 1 / distribution(generator);
}

int main()
{
	printf("------------------------------------------------------------------------\n");
	printf("                           INITIALIZATION\n");
	printf("------------------------------------------------------------------------\n");

	int step_mode = 1;
	do
	{
		cerr << "Wpisz dobra liczbe(1 - krokowy, 0 - ciagly)";
		cin >> step_mode;
	} while (step_mode > 1 || step_mode < 0);
	int logger_verb;
	do
	{
		printf("Poziom wyœwietlaia danych (1-4): ");
		std::cin >> logger_verb;
	} while (logger_verb < 1 || logger_verb > 4);
	Logger::GetInstance()->SetLogVerbosity(static_cast<Logger::LogVerbosity>(logger_verb));


	TransportCompany* transportcompany = new TransportCompany;
	const auto event_list = new Event_list;
	auto clock = 0.0;
	Process* current_process;
	for (int i = 0; i < 8; i++)
	{
		current_process = new Truck(event_list, transportcompany, i, 10, 0);
		current_process->activate(0);
		current_process->Info();
	}
	
	for (int i = 0; i < 7; i++)
	{
		current_process = new Goods(event_list, transportcompany, (rand() % 6), NormalDistributionGenerator(make_pair(2.00, 0.36)), i);
		current_process->activate(0);
		current_process->Info();
	}

	current_process = nullptr;
	
	double prev_clock = -1;
	int terminated_counter = 0;

	while(clock < 100000)
	{
		auto current_event = event_list->RemoveFirst();

		current_process = current_event->proc_;
		clock = current_event->event_time_;
		cerr << "Current clock: " << clock << endl;
		current_event = nullptr;
		current_process->execute(clock);

		if (prev_clock > clock)
		{
			cerr << "ERROR! TIME TRAVEL!\n";
			cin.get();
		}		
		if (current_process->terminated_)
		{
			cerr << "\nPROCES TERMINATED!\n";
			terminated_counter++;
			delete current_process;
		}		
		prev_clock = clock;

		if (step_mode)
		{
			cerr << "Press ENTER to continue...";
			cin.get();
		}
	}	
	system("Pause");
}