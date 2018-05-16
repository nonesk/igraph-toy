CXXFLAGS=-Wall -std=c++14 -I/usr/include/igraph
LDFLAGS=-ligraph

all: main.cpp
	$(CXX) $(CXXFLAGS) main.cpp -o main $(LDFLAGS)
