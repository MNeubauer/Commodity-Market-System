CC = g++
LD = g++

CFLAGS = -c -pedantic -std=c++11 -Wall -g
LFLAGS = -pedantic -Wall

OBJS = main1.o Engine.o EngineInput.o Utility.o
PROG = cms

default: $(PROG)


$(PROG): $(OBJS)
	$(LD) $(LFLAGS) $(OBJS) -o $(PROG)

main1.o: main1.cpp Engine.h EngineInput.h Utility.h
	$(CC) $(CFLAGS) main1.cpp

Engine.o: Engine.cpp Engine.h Utility.h
	$(CC) $(CFLAGS) Engine.cpp

EngineInput.o: EngineInput.cpp EngineInput.h Utility.h
	$(CC) $(CFLAGS) EngineInput.cpp

Utility.o: Utility.cpp Utility.h
	$(CC) $(CFLAGS) Utility.cpp

clean:
	rm -f *.o

real_clean:
	rm -f *.o
	rm -f *exe
