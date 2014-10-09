CCX 		= g++ -std=c++0x -Wall -Wextra
PROGS		= lab4
LIBS		= -lrt
OBJS		= Lab4.o ProcessManager.o SharedMem.o Queue.o


all: lab4

lab4: $(OBJS)
	$(CCX) -o $@ $(OBJS) $(LIBS)

clean:
	rm -f $(PROGS) $(OBJS)
