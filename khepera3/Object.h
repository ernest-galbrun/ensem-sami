#include <stdlib.h>
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
	virtual bool UpdatePosition();
public:
	void setPosition(double,double);
	void setOrientation(double);
	Object(void);
	~Object(void);
	void setId(int);
	int getId() const;
	boost::array<double,2> getPosition();
	double getOrientation();
	void InitLocalizationSystem(string myAddress, string hostAddress, string bodyName);
};
