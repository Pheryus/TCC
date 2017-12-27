CXX=g++
RM=rm
CXXFLAGS=-std=c++11
LDFLAGS=$(CXXFLAGS)
LDLIBS=-lpthread
 
SRCS=ClientSocket.cpp Socket.cpp client_main.cpp Position.cpp Player.cpp GameObject.cpp Game.cpp Bullet.cpp Enemy.cpp
OBJS=$(subst .cpp,.o,$(SRCS))
 
all:client
 
client:$(OBJS)
	$(CXX) $(LDFLAGS) -o client $(OBJS) $(LDLIBS)
 
Connection.o: Connection.cpp Connection.h
GameObject.o: GameObject.cpp GameObject.h
Game.o: Game.cpp Game.h
Bullet.o: Bullet.cpp Bullet.h
ClientSocket.o: ClientSocket.cpp ClientSocket.h
Position.o: Position.cpp Position.h
Player.o: Player.cpp Player.h
client_main.o: client_main.cpp
Enemy.o: Enemy.cpp Enemy.h
 
clean:
	$(RM) $(OBJS)
 
distclean: clean
	$(RM) client

