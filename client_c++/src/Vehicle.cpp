
class Vehicle {

	private:
		char * name;
		GSList * float_32_data;

	public:
		Vehicle(char * name, GSList * float_32_data){

			this->name = name;
			this->float_32_data = float_32_data;

		}

		void print_data(){

			int data_size = g_slist_length(this->float_32_data);
			int i = 0;
			char coord[] = "x";

			std::cout << "Object : " << name << std::endl;

			while(i < data_size){

				std::cout << "Coord " << coord << ": " << *(float *)g_slist_nth_data(this->float_32_data, i) << " ";

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

		GSList * get_data(){

			return this->float_32_data;

		}

};
