#include "LocalizationSystem.h"
#include <array>

class Parrot : public LocalizationSystem
{
public:
	virtual std::array<double,5> GetOwnPosition_Cortex(); //{Ack,X,Y,Z,theta}
	bool UpdatePosition(double * frontX, double* frontY, double* frontZ, double* backX, double * backY, double* backZ);
	Parrot();
};

