CXX = g++
CXXFLAGS = -Wall -std=c++11

OBJECTS = sixdegreesss.o wrapper.o Graphs.o

sixdegrees : $(OBJECTS)
	$(CXX) -g $(CXXFLAGS) -o sixdegrees $(OBJECTS)

wrapper.o: wrapper.cpp 
	$(CXX) -g $(CXXFLAGS) -c wrapper.cpp

sixdegrees.o: sixdegreesss.cpp sixdegrees.h
	$(CXX) -g $(CXXFLAGS) -c sixdegreesss.cpp

Graphs.o: Graphs.cpp Graphs.h
	$(CXX) -g $(CXXFLAGS) -c Graphs.cpp

clean:
	rm -f *.o
	rm sixdegrees
