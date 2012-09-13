#include <stdlib.h>
#include <vector>
//#include <boost/array.hpp>

#include "LocalizationSystem.h"


#pragma once

class Object
{
private:
	LocalizationSystem localizationSystem;
	int id;
	std::tr1::array<double,2> position;
	double orientation;
protected:
	string GetOwnIP(){return localizationSystem.GetOwnIP();};
	string GetOwnIP_wifi(){return localizationSystem.GetOwnIP_wifi();};
public:
	virtual void UpdatePosition();
	void setPosition(double,double);
	void setOrientation(double);
	Object::Object(std::vector<double> p, double orientation);
	Object(void);
	~Object(void);
	void setId(int);
	int getId() const;
	std::tr1::array<double,2> getPosition();
	double getOrientation();
	void InitLocalizationSystem(string bodyName);
};
