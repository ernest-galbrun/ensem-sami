#include "LocalizationSystem.h"
#include <array>

using namespace std;


class Wand : public LocalizationSystem
{
public:
	virtual std::array<double,5> GetOwnPosition_Cortex(); //{Ack,X,Y,Z,theta}
	Wand();
};