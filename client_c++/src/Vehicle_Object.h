#ifndef VEHICLE_OBJECT_H
#define VEHICLE_OBJECT_H

class Vehicle_Object{

	private:
		char * name;
		GSList * float_32_data;

	public:
		Vehicle_Object(char * name, GSList * float_32_data);
		void print_data();
		GSList * get_data();
		char * get_name();

};	

#endif
