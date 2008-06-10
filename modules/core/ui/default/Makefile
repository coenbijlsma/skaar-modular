
INSTALLDIR=/usr/local/lib
LIBNAME=libdefaultui.so
VERSION=1
MINOR=0
COMPILER=g++

help:
	@echo "Usage:"
	@echo "make build	Builds the module $(LIBNAME).$(VERSION).$(MINOR)."
	@echo "make install	Builds and installs the module in $(INSTALLDIR)."
	@echo "		You need root privileges for this."
	@echo "make uninstall	Removes the module and it's symlinks."
	@echo "		You need root privileges for this also."
	@echo "make clean	Cleans up this directory."
	@echo "make help	Displays this message."
	@echo

build:
	$(COMPILER) -fPIC -g -c -Wall -combine ../VirtualUI.h DefaultUI.cpp
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).$(VERSION) -o $(LIBNAME).$(VERSION).$(MINOR) DefaultUI.o -lc

install: indeedroot build
	cp $(LIBNAME).$(VERSION).$(MINOR) $(INSTALLDIR)
	ldconfig $(INSTALLDIR)
	ln -sf $(INSTALLDIR)/$(LIBNAME).$(VERSION) $(INSTALLDIR)/$(LIBNAME)

uninstall: indeedroot
	@rm $(INSTALLDIR)/$(LIBNAME)*
	ldconfig $(INSTALLDIR)

clean:
	rm ../*.gch
	rm *.o
	rm *.so*

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You need root privileges to run this program." ; \
	    exit 1 ; \
	fi

.PHONY: help build install uninstall clean indeedroot
