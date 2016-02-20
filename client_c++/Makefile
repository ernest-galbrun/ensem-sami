socket_boost: ./src/socket_boost.cpp packet_parser Vehicle_Object
	g++ -I /usr/lib/boost_1_60_0 -L /usr/lib/boost_1_60_0/lib -lboost_system -lboost_thread -lpthread -o ./built/socket_boost ./src/socket_boost.cpp ./built/packet_parser ./built/Vehicle_Object -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lglib-2.0

packet_parser: ./src/packet_parser.cpp
	g++ -c ./src/packet_parser.cpp -o ./built/packet_parser -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -lglib-2.0

Vehicle_Object: ./src/Vehicle_Object.cpp
	g++ -c ./src/Vehicle_Object.cpp -o ./built/Vehicle_Object -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -lglib-2.0
