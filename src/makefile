CC 			= g++
CCFLAGS		= -std=c++0x -Wall -Wextra
PROGS		= lab4
LIBS		= -lrt
FILES		= Lab4.cpp ProcessManager.cpp SharedMem.cc Queue.cpp
OBJS		= Lab4.o ProcessManager.o SharedMem.o Queue.o


all: compile lab4

lab4: $(OBJS)
	$(CC) -o $@ $(CCFLAGS) $(OBJS) $(LIBS)

compile: $(FILES)
	$(CC) -c $(CCFLAGS) $(FILES)

clean:
	rm -f $(PROGS) $(OBJS)
