#include <cstdlib>
#include <iostream>
#include <stdio.h>
#include <glib.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "packet_parser.h"
#include "Vehicle_Object.h"

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

char * Packet_Parser::parsing_name(){ //Get the name of the first object. Must be executed after checking you are at the beginning of the name.

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

	object_name[i+1] = 0x00; //Ending the char by \o

	return object_name;

}

GSList * Packet_Parser::parsing_32bit_float(int triplet_number){ //Collect 32bit float data position triplet

	float * float_32bit = (float *)current_cursor;
	GSList * chained_list = NULL;
	float * current_storage;
	int i;

	for(i = 0; i < 3 * triplet_number; i++){

		current_storage = (float *)malloc(sizeof(float));
		*current_storage = *float_32bit;
		chained_list = g_slist_append(chained_list,(gpointer *)current_storage);
		float_32bit++;

	}
	current_cursor = (char *)float_32bit;
	return chained_list;

}
	
void Packet_Parser::parsing_40bit_data(){

	current_cursor+=59; //Arbritrary Jump

}


GSList * Packet_Parser::parse(char * packet_to_analyze, int size){

	this->packet_to_analyze = packet_to_analyze;
	last_char = packet_to_analyze + size;
	current_cursor = packet_to_analyze;
	
	int i;

	for(;;){

		if(last_three_00_detect() == -1){

			break;

		}
		if(*current_cursor == 0x02){
			
			break;			

		}
		char * name = parsing_name();
		current_cursor++;
		int triplet_number = *(int*)current_cursor;
		last_three_00_detect();
		Vehicle_Object v(name,parsing_32bit_float(triplet_number));
		v.print_data();
		if(*(int *)current_cursor == 1){
			parsing_40bit_data();
		}

	}

}

/*int main(){

	//Faking test opening file instead of received data
	FILE * myfile = fopen("socket_data", "r");

	fseek (myfile , 0 , SEEK_END);
  	int fileSize = ftell (myfile);
	rewind (myfile);

	char * buffer = (char*) malloc (sizeof(char)*fileSize);
	if (buffer == NULL) {fputs ("Memory error",stderr); exit (2);}

	int result = fread (buffer,1,fileSize,myfile);
	if (result != fileSize) {fputs ("Reading error",stderr); exit (3);}
	printf("File size : %d \n", fileSize);
	//END

	Packet_Parser * parser = new Packet_Parser();
	parser->parse(buffer,fileSize);

	free(buffer);
	buffer = NULL;

}
