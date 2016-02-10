socket_boost: ./src/socket_boost.cpp packet_parser
	g++ -I /usr/lib/boost_1_60_0 -L /usr/lib/boost_1_60_0/lib -lboost_system -lboost_thread -lpthread -o ./built/socket_boost ./src/socket_boost.cpp ./built/packet_parser -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lglib-2.0

packet_parser: ./src/packet_parser.cpp
	g++ -c ./src/packet_parser.cpp -o ./built/packet_parser -I/usr/include/glib-2.0 -I/usr/lib/glib-2.0/include -lglib-2.0

