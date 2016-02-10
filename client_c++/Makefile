socket_boost: ./src/socket_boost.cpp packet_parser
	g++ -I /usr/lib/boost_1_60_0 -L /usr/lib/boost_1_60_0/lib -lboost_system -lboost_thread -lpthread -o ./built/socket_boost ./built/packet_parser ./src/socket_boost.cpp

packet_parser: ./src/packet_parser.cpp
	g++ -lglib-2.0 -o ./built/packet_parser ./src/packet_parser.cpp
