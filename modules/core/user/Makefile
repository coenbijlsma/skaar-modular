
INSTALLDIR=/usr/local/lib
LIBNAME=libuser.so
COMPILER=g++

help:
	@echo "Usage:"
	@echo "make build	Builds the module libuser.so.1.0"
	@echo "make install	Builds and installs the module."
	@echo "		You need root privileges for this."
	@echo "make uninstall	Removes the module and it's symlinks."
	@echo "		For this you also need root privileges."
	@echo "make clean	Cleans up this directory."
	@echo "make help	Displays this message."
	@echo

build: 
	$(COMPILER) -fPIC -g -c -Wall -combine User.h User.cpp
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).1 -o $(LIBNAME).1.0 User.o -lc

install: indeedroot build
	cp $(LIBNAME).1.0 $(INSTALLDIR)
	ldconfig $(INSTALLDIR)
	ln -sf $(INSTALLDIR)/$(LIBNAME).1 $(INSTALLDIR)/$(LIBNAME)

uninstall: indeedroot
	@rm $(INSTALLDIR)/$(LIBNAME)*
	ldconfig $(INSTALLDIR)

clean:
	rm *gch
	rm *o
	rm *.so*

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You need root privileges to run this program." ; \
	    exit 1 ; \
	fi
    
.PHONY: help build install uninstall clean indeedroot
