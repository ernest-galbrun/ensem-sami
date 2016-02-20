#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "Vehicle_Object.h"

Vehicle_Object::Vehicle_Object(char * name, GSList * float_32_data){

	this->name = name;
	this->float_32_data = float_32_data;

}

void Vehicle_Object::print_data(){

	int data_size = g_slist_length(float_32_data);
	int i = 0;
	char coord[] = "x";

	std::cout << "Object : " << name << std::endl;

	while(i < data_size){

		std::cout << "Coord " << coord << ": " << *(float *)g_slist_nth_data(float_32_data, i) << " ";	

		if(coord[0] == 'z'){
			coord[0] = 'x';
			std::cout << std::endl;
		}
		else{
			if(coord[0] == 'x'){
				coord[0]='y';
			}
			else{
				coord[0]='z';
			}
		}
		i++;

	}

}

GSList * Vehicle_Object::get_data(){
	
	return float_32_data;

}

char * Vehicle_Object::get_name(){

	return name;

}


