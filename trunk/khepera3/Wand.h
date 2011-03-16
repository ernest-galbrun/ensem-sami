#include "LocalizationSystem.h"

using namespace std;


class Wand : public LocalizationSystem
{
public:
	virtual bool UpdatePosition(boost::array<double,2>* position, double* orientation);
	virtual void init(string myAddress, string hostAddress, string bodyName,boost::array<double,2>* position, double* orientation);
};