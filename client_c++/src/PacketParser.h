#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

#include<vector>
#include"Data.h"

#define NAME_PACKET 11
#define DATA_PACKET 13


using namespace std;

class Packet_Parser {

	private:
		struct packet_header{
			uint16_t packet_type;
			uint16_t packet_size;
		};

		struct packet_header * current_header;
		uint64_t packet_number;
		char * packet_to_analyze;
		char * last_char;
		char * current_cursor;
		vector<float> points_value;
		Data * data;

		int last_three_00_detect();//Position to the next char after detecting 00 00 00 hex. (VERIFIED)
		string parsing_name();//Get the name of the first object. Must be executed after checking you are at the beginning of the name.
		int parsing_32bit_float(int triplet_number);//Collect 32bit float data position triplet
		void parsing_64bit_data();
		void parse_name();
		void parse_data();

	public:
		Packet_Parser(Data & data);
		void parse(char * packet_to_analyze, int size);

};

#endif
