#include "generators.h"


double Generators::ExponentialDistributionGenerator(double average)
{
	static default_random_engine generator(kSeed);
	const exponential_distribution<double> distribution(1/average);
	return distribution(generator);
}

double Generators::NormalDistributionGenerator(const pair<const double, const double> p)
{
	static default_random_engine generator(kSeed);
	normal_distribution<double> distribution(p.first, p.second);
	return distribution(generator);
}

int Generators::Distribution()
{
	static::default_random_engine generator(kSeed);
	uniform_int_distribution<int>distribution(1, 6);
	return distribution(generator);
}

