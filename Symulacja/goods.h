#ifndef MODEL_GOODS_H_
#define MODEL_GOODS_H_
#include "process.h"
#include "transportCompany.h"


struct Goods : public Process
{
public:
	//Goods(int id);
	explicit Goods(Event_list*, TransportCompany*, int, double, int);
	void execute(double) override;
	TransportCompany* transportcompany_;

	~Goods();
	static const int kSeed = 123456;
	static double NormalDistributionGenerator(const pair<const double, const double> p);
	static double ExponentialDistributionGenerator(const int average);
private:
	
	double size_;
	int id_;

	//Truck* served_truck_; //pointer on Truck
};
#endif /*MODEL_GOODS_H_*/