#ifndef MODEL_HEADQUARTERS_H_
#define MODEL_HEADQUARTERS_H_
#include <queue>
#include <vector>
#include "process.h"

//#include 
using namespace std;

class Headquarters 
{
public:
	explicit Headquarters();
	~Headquarters();

private:
	vector<Process*> queue_;

};

#endif /* MODEL_HEADQUARTERS_H_ */
