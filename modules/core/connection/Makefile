
INSTALLDIR=/usr/local/lib
LIBNAME=libircconnection.so
VERSION=1
MINOR=0
COMPILER=g++

help:
	@echo "Usage:"
	@echo "make build	Builds the library $(LIBNAME).$(VERSION).$(MINOR)"
	@echo "make install	Builds and installs the library in $(INSTALLDIR)."
	@echo "		Needs root privileges to run."
	@echo "make uninstall	Removes the library and it's symlinks."
	@echo "		Also needs root privileges."
	@echo "make clean	Cleans up this directory."
	@echo "make help	Displays this message"
	@echo

build:
	$(COMPILER) -fPIC -g -c -Wall -combine IRCConnection.h IRCConnection.cpp
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).$(VERSION) -o $(LIBNAME).$(VERSION).$(MINOR) IRCConnection.o -lc

install: indeedroot build
	cp $(LIBNAME).$(VERSION).$(MINOR) $(INSTALLDIR)
	ldconfig $(INSTALLDIR)
	ln -sf $(INSTALLDIR)/$(LIBNAME).$(VERSION) $(INSTALLDIR)/$(LIBNAME)

uninstall: indeedroot
	@rm $(INSTALLDIR)/$(LIBNAME)*
	ldconfig $(INSTALLDIR)

clean:
	rm *.gch
	rm *.o
	rm *.so*

indeedroot:
	@if [ `whoami` != "root" ]; then \
	    echo "You need root privileges to run this program." ; \
	    exit 1 ; \
	fi

.PHONY: help build install uninstall clean indeedroot
