CXX=g++
RM=rm
CXXFLAGS=-std=c++11
LDFLAGS=$(CXXFLAGS)
LDLIBS=-lpthread
 
SRCS=Socket.cpp Game.cpp Connection.cpp ServerSocket.cpp Position.cpp server_main.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
 
all:server
 
server:$(OBJS)
	$(CXX) $(LDFLAGS) -o server $(OBJS) $(LDLIBS)
 
Socket.o: Socket.cpp Socket.h
Game.o: Game.cpp Game.h
Connection.o: Connection.cpp Connection.h
ServerSocket.o: ServerSocket.cpp ServerSocket.h
Position.o: Position.cpp Position.h
server_main.o: server_main.o
 
clean:
	$(RM) $(OBJS) server
 
distclean: clean
	$(RM) server
