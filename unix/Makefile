
TARGETS=sigpmask
SIGNAL_H=$(shell egrep -R "[\t ]*\#define[\t ]+SIGINT[\t ]+[0-9]+" /usr/include | head -n 1 | cut -d ':' -f 1)
CXXFLAGS+=-std=c++11 -g -ggdb -D_POSIX_C_SOURCE=200809L
LDFLAGS+=

all: $(TARGETS)

sigpmask: signames.c sigpmask.cxx signames.h
	$(CXX) $(CXXFLAGS) signames.c sigpmask.cxx -o $@ $(LDFLAGS)

signames.h: $(SIGNAL_H) scripts/signames.awk
	awk -f scripts/signames.awk $(SIGNAL_H) >$@

clean:
	-rm -f signames.h $(TARGETS) *.o

