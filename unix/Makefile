
TARGETS=sigpmask
SIGNAL_H=/usr/include/sys/signal.h
CXXFLAGS=-std=c++11 -g -ggdb
LDFLAGS=

all: $(TARGETS)

sigpmask: signames.o sigpmask.o
	$(CXX) $? -o $@ $(LDFLAGS)

sigpmask.o: sigpmask.cxx errout.h

signames.o: signames.c signames.h
	$(CC) $(CFLAGS) -c signames.c

signames.h: $(SIGNAL_H) scripts/signames.awk
	awk -f scripts/signames.awk $(SIGNAL_H) >$@

clean:
	-rm -f signames.h $(TARGETS) *.o
