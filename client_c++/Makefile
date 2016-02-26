socket_boost: ./src/socket_boost.cpp packet_parser Vehicle
	g++ -I /usr/lib/boost_1_60_0 -L /usr/lib/boost_1_60_0/lib -lboost_system -lboost_thread -lpthread -o ./built/socket_boost ./src/socket_boost.cpp ./built/packet_parser ./built/Vehicle -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lglib-2.0

packet_parser: ./src/packet_parser.cpp
	g++ -c ./src/packet_parser.cpp -o ./built/packet_parser -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -lglib-2.0

Vehicle: ./src/Vehicle.cpp
	g++ -c ./src/Vehicle.cpp -o ./built/Vehicle -I/usr/include/glib-2.0 -I/usr/lib/x86_64-linux-gnu/glib-2.0/include/ -lglib-2.0
