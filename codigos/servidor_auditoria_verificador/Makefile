CXX=g++
RM=rm
CXXFLAGS=-std=c++11
LDFLAGS=$(CXXFLAGS)
LDLIBS=-lpthread
 
SRCS= Game.cpp Position.cpp server_main.cpp 
OBJS=$(subst .cpp,.o,$(SRCS))
 
all:server
 
server:$(OBJS)
	$(CXX) $(LDFLAGS) -o server $(OBJS) $(LDLIBS)
 
Game.o: Game.cpp Game.h
server_main.o: server_main.o
Position.o: Position.cpp Position.h 


clean:
	$(RM) $(OBJS) server
 
distclean: clean
	$(RM) server
