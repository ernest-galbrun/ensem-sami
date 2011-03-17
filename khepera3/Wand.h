#include "LocalizationSystem.h"

using namespace std;


class Wand : public LocalizationSystem
{
public:
	virtual boost::array<double,5> GetOwnPosition_Cortex(); //{Ack,X,Y,Z,theta}
};