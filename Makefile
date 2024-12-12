CXX=g++
CXXFLAGS=-std=c++11 -Wall -Wextra -I/usr/include -L/usr/lib
LDLIBS=-lssl -lcryptopp -lboost_program_options

TARGET=client
OBJS=Authenticator.o Client.o FileManager.o ServerConnection.o

all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(OBJS) $(LDLIBS)

Authenticator.o: Authenticator.cpp Authenticator.h
	$(CXX) $(CXXFLAGS) -c Authenticator.cpp

Client.o: Client.cpp Authenticator.h FileManager.h ServerConnection.h
	$(CXX) $(CXXFLAGS) -c Client.cpp

FileManager.o: FileManager.cpp FileManager.h Vector.h
	$(CXX) $(CXXFLAGS) -c FileManager.cpp

ServerConnection.o: ServerConnection.cpp ServerConnection.h Vector.h
	$(CXX) $(CXXFLAGS) -c ServerConnection.cpp

clean:
	rm -f $(TARGET) $(OBJS)
