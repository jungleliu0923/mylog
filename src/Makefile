CC=g++
TARGET=libmylog.a
OBJS= log.o mylog.o

LIBS=-lpthread
CPPFLAGS=-Wall -W -pipe -Wno-unused-parameter -g -O2
LDFLAGS=$(LIBS) -O2

.PHONY : all

all:$(TARGET)
	mkdir -p ../output/include
	cp *h ../output/include
	mkdir -p ../output/lib
	cp *a ../output/lib

$(TARGET): $(OBJS)
	ar -r $(TARGET) $(OBJS)

$(OBJS) : %.o : %.cpp %.h
	$(CC) -g -c $(CPPFLAGS) $< 

.PHONY : clean

clean:
	rm -rf $(OBJS)
	rm -rf $(TARGET)
	rm -rf ../output/lib
	rm -rf ../output/include
