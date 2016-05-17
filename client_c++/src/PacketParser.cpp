#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "PacketParser.h"
#include "Vehicle.h"

#define DEBUG 0

using namespace std;

Packet_Parser::Packet_Parser(Data & data):data(&data){}

int Packet_Parser::last_three_00_detect(){ //Position to the next char after detecting 00 00 00 hex. (VERIFIED)

	while((current_cursor + 3) <= last_char){

		if(*current_cursor == 0x00 && *(current_cursor + 1) == 0x00 && *(current_cursor + 2) == 0x00 && *(current_cursor + 3) != 0x00){ //Checking that there is no 00 character after the one analyzed

			current_cursor+=3;
			return 0;

		}
		else{

			current_cursor++; //Move to the next XX

		}

	}

	return -1;

}

string Packet_Parser::parsing_name(){ //Get the name of the first object. Must be executed after checking you are at the beginning of the name.

	char * limit_cursor = current_cursor;
	int name_size = 1;

	while(*limit_cursor != 0x00){

		limit_cursor++;
		name_size++;

	}

	char * object_name = (char *)malloc(sizeof(char) * name_size);
	int i;
	for(i = 0; i < name_size - 1; i++){ //Copy the object name from the packet to the variable

		object_name[i] = *current_cursor;
		current_cursor++;
	}

	object_name[i] = 0x00; //Ending the char by \o

	return string(object_name);

}

int Packet_Parser::parsing_32bit_float(int triplet_number){ //Collect 32bit float data position triplet

	float * float_32bit = (float *)current_cursor;
	points_value.clear();

	int i, j;
	for(i = 0; i < triplet_number * 3; i++){

		if(((char *)float_32bit) > last_char){

			return -1;

		}
		points_value.push_back(*float_32bit);
		float_32bit++;

	}
	current_cursor = (char *)float_32bit;
	return 0;
}

void Packet_Parser::parsing_40bit_data(){

	current_cursor+=59; //Arbritrary Jump

}

void Packet_Parser::parse_name(){
	if(DEBUG == 1)cout << "UPDATING DATA NAME" << endl;
	vector<string> names;
	vector<int> pos;
	int curr_pos;

	uint8_t number_vehicle = (uint8_t)*current_cursor;
	int i;
	if(DEBUG == 1)cout << "NUMBER VEHICLE " << (int)number_vehicle << endl;
	for(i = 0; i < number_vehicle; i++){

		if(last_three_00_detect() == -1){
			if(DEBUG == 1)std::cerr << "ERROR THREE 00 DETECT" << std::endl;
			break;
		}
		names.push_back(parsing_name());
		curr_pos = names.size()-1;
		pos.push_back(curr_pos);
		current_cursor++;
		uint8_t points_number = *(uint8_t*)current_cursor;
		if(DEBUG == 1)cout << "NUMBER POINTS " << (int)points_number << endl;
		current_cursor+=4;
		int i;
		for(i = 0; i < points_number; i++){
			names.push_back(parsing_name());
			current_cursor++;
		}
		uint8_t squeleton_number = *(uint8_t*)current_cursor;
		if(squeleton_number > 0){
			current_cursor+=4;
			parsing_name();
		}
	}
	data->setPointsNames(names, pos);
}

void Packet_Parser::parse_data(){
	vector<Vehicle> vehicle_list;

	packet_number = (uint32_t)*current_cursor; //Currently unused
	current_cursor+=sizeof(uint32_t);

	uint8_t number_vehicle = (uint8_t)*current_cursor;
	if(DEBUG == 1)cout << "Number_vehicle " << (int)number_vehicle << endl;
	int i;

	for(uint8_t i = 0; i < number_vehicle; i++){

		if(last_three_00_detect() == -1){
			if(DEBUG == 1)std::cerr << "ERROR THREE 00 DETECT" << std::endl;
			break;
		}

		string name = parsing_name();
		current_cursor++;
		int triplet_number = *(int*)current_cursor;

		if(last_three_00_detect() == -1){
			if(DEBUG == 1)std::cerr << "ERROR THREE 00 DETECT" << std::endl;
			break;
		}

		if(parsing_32bit_float(triplet_number) == -1){
			if(DEBUG == 1)std::cerr << "ERROR PARSING 32 BIT FLOAT COORD" << std::endl;
			break;
		}

		vehicle_list.push_back(Vehicle(name,points_value));
		if(*(int *)current_cursor == 1){
			parsing_40bit_data();
		}

	}
	data->setAll(vehicle_list);
}

void Packet_Parser::parse(char * packet_to_analyze, int size){

	this->packet_to_analyze = packet_to_analyze;
	current_header = (struct packet_header *)packet_to_analyze;
	last_char = packet_to_analyze + size;
	current_cursor = packet_to_analyze + sizeof(struct packet_header);

	if(size > sizeof(struct packet_header) && current_header->packet_type == NAME_PACKET){
		parse_name();
	}
	else if(size > sizeof(struct packet_header) && current_header->packet_type == DATA_PACKET){
		parse_data();
	}
	else{
		if(DEBUG == 1)cerr << "UNSUPPORTED PACKET RECEIVED" << endl;
	}

}
