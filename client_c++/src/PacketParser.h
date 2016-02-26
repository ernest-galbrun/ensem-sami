#ifndef PACKET_PARSER_H
#define PACKET_PARSER_H

class Packet_Parser {

	private:

		char * packet_to_analyze;
		char * last_char;		
		char * current_cursor;
		float ** points_value;

		int last_three_00_detect(); //Position to the next char after detecting 00 00 00 hex. (VERIFIED)
		char * parsing_name();//Get the name of the first object. Must be executed after checking you are at the beginning of the name.
		void parsing_32bit_float(int triplet_number);//Collect 32bit float data position triplet
		void parsing_40bit_data();

	public:

		void parse(char * packet_to_analyze, int size);

};

#endif

