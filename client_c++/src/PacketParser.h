#include<vector>
#include"Data.h"

#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

using namespace std;

class Packet_Parser {

	private:

		char * packet_to_analyze;
		char * last_char;		
		char * current_cursor;
		vector<float> points_value;
		Data * data;

		int last_three_00_detect();//Position to the next char after detecting 00 00 00 hex. (VERIFIED)
		char * parsing_name();//Get the name of the first object. Must be executed after checking you are at the beginning of the name.
		int parsing_32bit_float(int triplet_number);//Collect 32bit float data position triplet
		void parsing_40bit_data();

	public:
		Packet_Parser(Data * data);
		void parse(char * packet_to_analyze, int size);

};

#endif

