test: ./src/test.cpp CortexClient SocketBoost PacketParser Vehicle Point Data
	g++ -I /usr/lib/boost_1_60_0 -L /usr/lib/boost_1_60_0/lib -lboost_system -lboost_thread -lpthread ./src/test.cpp -o ./built/test ./built/CortexClient ./built/SocketBoost ./built/PacketParser ./built/Vehicle ./built/Point ./built/Data

CortexClient: ./src/CortexClient.cpp
	g++ -c -I /usr/lib/boost_1_60_0 ./src/CortexClient.cpp -o ./built/CortexClient

SocketBoost: ./src/SocketBoost.cpp
	g++ -c -I /usr/lib/boost_1_60_0 ./src/SocketBoost.cpp -o ./built/SocketBoost

PacketParser: ./src/PacketParser.cpp
	g++ -c -I /usr/lib/boost_1_60_0 ./src/PacketParser.cpp -o ./built/PacketParser

Vehicle: ./src/Vehicle.cpp
	g++ -c ./src/Vehicle.cpp -o ./built/Vehicle

Point: ./src/Point.cpp
	g++ -c ./src/Point.cpp -o ./built/Point

Data: ./src/Data.cpp
	g++ -c -I /usr/lib/boost_1_60_0 ./src/Data.cpp -o ./built/Data

clean:
	rm built/*
