CC=g++
TARGET=sample
OBJS=sample.o
MYLOG_PATH=../output/

INCS=\
	-I$(MYLOG_PATH)include

LIBS=\
	-L$(MYLOG_PATH)lib \
	-Wl,-whole-archive -lmylog -Wl,-no-whole-archive \
	-lpthread

CPPFLAGS=$(INCS)  -Wall -W -pipe -Wno-unused-parameter -g -O2
LDFLAGS=$(LIBS) -O2 

all: $(TARGET)

$(TAEGET) : $(OBJS)
	$(CC) -o $@ $^ $(LDFLAGS)

$(OBJS) :%.o : %.cpp
	$(CC) -c $(CPPFLAGS) $< 

clean:
	rm -rf $(OBJS) $(TARGET)
