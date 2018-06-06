
TARGETS=sigpmask
SIGNAL_H=/usr/include/sys/signal.h
CXXFLAGS=-std=c++11 -g -ggdb

all: $(TARGETS)

sigpmask: signames.o sigpmask.cxx errout.h
	$(CXX) $(CXXFLAGS) signames.o sigpmask.cxx -o $@

signames.o: signames.h

signames.h: $(SIGNAL_H)
	awk -f scripts/signames.awk $(SIGNAL_H) >$@

clean:
	-rm -f signames.h $(TARGETS) *.o
