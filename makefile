OBJS	= getChar.o Screen.o Worm.o main.o
SOURCE	= getChar.cpp Screen.cpp Worm.cpp main.cpp
HEADER	= getChar.hpp Screen.hpp Worm.hpp
OUT	= Worm.x
CC	 = g++
FLAGS	 = -g -c -Wall
LFLAGS	 = 

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT) $(LFLAGS) -lcurses -ltermcap
Main.o: main.cpp
	$(CC) $(FLAGS) main.cpp

getChar.o: getChar.cpp
	$(CC) $(FLAGS) getChar.cpp 

Screen.o: Screen.cpp
	$(CC) $(FLAGS) Screen.cpp 

Worm.o: Worm.cpp
	$(CC) $(FLAGS) Worm.cpp 


clean:
	rm -f $(OBJS) $(OUT)
