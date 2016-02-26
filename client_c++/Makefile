SocketBoost: ./src/SocketBoost.cpp PacketParser Vehicle Point Data
	g++ -I /usr/lib/boost_1_60_0 -L /usr/lib/boost_1_60_0/lib -lboost_system -lboost_thread -lpthread -o ./built/SocketBoost ./src/SocketBoost.cpp ./built/PacketParser ./built/Vehicle ./built/Point ./built/Data

PacketParser: ./src/PacketParser.cpp
	g++ -c ./src/PacketParser.cpp -o ./built/PacketParser

Vehicle: ./src/Vehicle.cpp
	g++ -c ./src/Vehicle.cpp -o ./built/Vehicle

Point: ./src/Point.cpp
	g++ -c ./src/Point.cpp -o ./built/Point

Data: ./src/Data.cpp
	g++ -c ./src/Data.cpp -o ./built/Data

clean:
	rm built/*
