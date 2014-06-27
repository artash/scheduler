CXXFLAGS =	-O2 -g -Wall -fmessage-length=0

OBJS =		fcfs_scheduler.o sjf_scheduler.o simulator.o scheduler.o main.o

LIBS =

TARGET =	scheduler

$(TARGET):	$(OBJS)
	$(CXX) -o $(TARGET) $(OBJS) $(LIBS)

all:	$(TARGET)

clean:
	rm -f $(OBJS) $(TARGET)
