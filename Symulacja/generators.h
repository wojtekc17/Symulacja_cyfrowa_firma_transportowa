#pragma once
//#include "transportCompany.h"
#include <random>

using namespace std;

class Generators
{
public:
	static const int kSeed = 123456;
	static double NormalDistributionGenerator(const pair<const double, const double>);
	static double ExponentialDistributionGenerator(double);
	static int Distribution();

};

