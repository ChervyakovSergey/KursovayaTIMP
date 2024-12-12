CC=g++
CFLAGS=-Wall -std=c++17
LDFLAGS=-lcryptopp -lssl -lcrypto

all: client

client: main.o Communicator.o DataReader.o DataWriter.o UserInterface.o
	$(CC) $(CFLAGS) -o client $^ $(LDFLAGS)

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp

Communicator.o: Communicator.cpp
	$(CC) $(CFLAGS) -c Communicator.cpp

DataReader.o: DataReader.cpp
	$(CC) $(CFLAGS) -c DataReader.cpp

DataWriter.o: DataWriter.cpp
	$(CC) $(CFLAGS) -c DataWriter.cpp

UserInterface.o: UserInterface.cpp
	$(CC) $(CFLAGS) -c UserInterface.cpp

clean:
	rm -f *.o client










