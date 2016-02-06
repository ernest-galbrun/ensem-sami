#include <stdio.h>
#include <glib.h>

class Packet_Parser {

	private:

		char * packet_to_analyze;
		char * last_char;		
		char * current_cursor;

		object create_object(){



		}

		char * last_three_00_detect(char * start_char){ //Give the next char after detecting 00 00 00 hex.

			while( (current_cursor + 3) <= start_char){ 

				if(*current_cursor == 0x00 && *(current_cursor + 1) == 0x00 && *(current_cursor + 2) == 0x00 && *(current_cursor + 3) != 0x00){ //Checking that there is no 00 character after the one analyzed

					return current_cursor + 3;
	
				}
				else{

					current_cursor++; //Move to the next XX

				}

			}
		
			return NULL;

		}

		char * parsing_name(){

			char * limit_cursor = current_cursor;
			int name_size = 1;			

			while(*limit_cursor != 00){

				name_size++;

			}
			
			char * object_name = malloc(sizeof(char) * name_size);
			int i;

			for(i = 0; i < name_size - 1; i++){

				object_name[i] = *current_cursor;
				current_cursor++;
			}

			object_name[i+1] = NULL;

		}

		GSList * parsing_32bit_float(){ //Collect 32bit float data position triplet

			Float32 * 32bit_float = (Float32 *)current_cursor;
			GSList * glib_list chained_list = g_slist_alloc();

			while((Int32)32bit_float != 224){

				g_slist_append (chained_list,*32bit_float);
				32bit_float++;

			}
			curent_cursor = (char *)32bit_float;

			return chained_list;

		}

	public:

		GSList * parse(char * packet_to_analyze, int size){

			this->packet_to_analyze = packet_to_analyze;

		}

		

	typedef struct{

	}

}
