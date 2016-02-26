socket_boost: ./src/socket_boost.cpp packet_parser Vehicle Point Data
	g++ -I /usr/lib/boost_1_60_0 -L /usr/lib/boost_1_60_0/lib -lboost_system -lboost_thread -lpthread -o ./built/socket_boost ./src/socket_boost.cpp ./built/packet_parser ./built/Vehicle ./built/Point ./built/Data

packet_parser: ./src/packet_parser.cpp
	g++ -c ./src/packet_parser.cpp -o ./built/packet_parser

Vehicle: ./src/Vehicle.cpp
	g++ -c ./src/Vehicle.cpp -o ./built/Vehicle

Point: ./src/Point.cpp
	g++ -c ./src/Point.cpp -o ./built/Point

Data: ./src/data.cpp
	g++ -c ./src/data.cpp -o ./built/Data

clean:
	rm built/*
