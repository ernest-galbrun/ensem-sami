#include <stdlib.h>
#include <vector>
#include <boost/array.hpp>

#include "LocalizationSystem.h"


#pragma once

class Object
{
private:
	LocalizationSystem localizationSystem;
	int id;
	boost::array<double,2> position;
	double orientation;
protected:
public:
	virtual bool UpdatePosition();
	void setPosition(double,double);
	void setOrientation(double);
	Object::Object(std::vector<double> p, double orientation);
	Object(void);
	~Object(void);
	void setId(int);
	int getId() const;
	boost::array<double,2> getPosition();
	double getOrientation();
	void InitLocalizationSystem(string bodyName);
};
