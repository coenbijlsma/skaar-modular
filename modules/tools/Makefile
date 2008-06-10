
INSTALLDIR=/usr/local/lib
LIBNAME=libskaartools.so
COMPILER=g++

help:
	@echo "Usage:"
	@echo "make build	Builds the module libskaartools.so.1.0"
	@echo "make install	Builds and installs the module. Needs root privileges."
	@echo "make uninstall	Removes the module and its symlinks. This"
	@echo "		also needs root privileges."
	@echo "make clean	Cleans up this directory."
	@echo "make help	Shows this message."
	@echo
	@echo "Dependencies:"
	@echo "none"

build:
	$(COMPILER) -fPIC -g -c -Wall -combine StringTokenizer.h StringTokenizer.cpp
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).1 -o $(LIBNAME).1.0 StringTokenizer.o -lc

install: indeedroot build
	cp $(LIBNAME).1.0 $(INSTALLDIR)
	ldconfig $(INSTALLDIR)
	ln -sf $(INSTALLDIR)/$(LIBNAME).1 $(INSTALLDIR)/$(LIBNAME)

uninstall: indeedroot
	@rm $(INSTALLDIR)/$(LIBNAME)*
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
