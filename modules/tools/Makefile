
INSTALLDIR=/usr/local/lib

help:
	@echo "Usage:"
	@echo "make build	Build the module libskaartools.so.1.0"
	@echo "make install	Builds and installs the module. Needs root privileges."
	@echo "make uninstall	Removes the module and its symlinks. This"
	@echo "		also needs root privileges."
	@echo "make clean	Cleans up this directory."
	@echo "make help	Shows this message."
	@echo
	@echo "Dependencies:"
	@echo "none"

build:
	g++ -fPIC -g -c -Wall -combine StringTokenizer.h StringTokenizer.cpp
	g++ -shared -Wl,-soname,libskaartools.so.1 -o libskaartools.so.1.0 StringTokenizer.o -lc

install: indeedroot build
	cp libskaartools.so.1.0 $(INSTALLDIR)
	ldconfig $(INSTALLDIR)
	ln -sf $(INSTALLDIR)/libskaartools.so.1 $(INSTALLDIR)/libskaartools.so

uninstall: indeedroot
	@rm $(INSTALLDIR)/libskaartools.so*
	ldconfig $(INSTALLDIR)

clean:
	rm *.gch
	rm *.o
	rm *.so*

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You must be root to run this program!" ; \
	    exit 1 ; \
	fi	    

.PHONY: help build install uninstall clean indeedroot
