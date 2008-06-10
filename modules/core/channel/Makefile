
INSTALLDIR=/usr/local/lib
LIBNAME=libircchannel.so
COMPILER=g++

help:
	@echo "Usage:" 
	@echo "make build		Builds the module $(LIBNAME)1.0"
	@echo "make install		Builds and installs the module. Needs root privileges."
	@echo "make uninstall		Removes the installed module and it's symlinks."
	@echo "			Also needs root privileges."
	@echo "make clean		Cleans up the files created at build-time."
	@echo "			This option also requires root privileges."
	@echo "make help		Shows this message"
	@echo
	@echo "Dependencies:"
	@echo "none"

build:
	$(COMPILER) -fPIC -g -c -Wall -Wl,export-dynamic -combine Channel.h Channel.cpp
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).1 -o $(LIBNAME).1.0 Channel.o -lc

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
	    echo "You need root privileges to run this program" ; \
	    exit 1 ; \
	fi

.PHONY: help build install uninstall clean indeedroot
