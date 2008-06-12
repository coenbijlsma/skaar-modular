
INSTALLDIR=/usr/local/lib
LIBNAME=libskaartools.so
VERSION=1
MINOR=0
COMPILER=g++
HEADERSDIR=../../headers

help:
	@echo "Usage:"
	@echo "make build	Builds the module $(LIBNAME).$(VERSION).$(MINOR)"
	@echo "make install	Builds and installs the module in $(INSTALLDIR)."
	@echo "		You need root privileges to do this."
	@echo "make uninstall	Removes the module and its symlinks."
	@echo "		This also needs root privileges."
	@echo "make clean	Cleans up this directory."
	@echo "make distclean	Uninstalls and cleans the directory."
	@echo "		You need root for this."
	@echo "make help	Shows this message."
	@echo
	@echo "Dependencies:"
	@echo "none"

build:
	$(COMPILER) -fPIC -g -c -Wall -I$(HEADERSDIR) StringTokenizer.cpp
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).$(VERSION) -o $(LIBNAME).$(VERSION).$(MINOR) StringTokenizer.o -lc

install: indeedroot build
	cp $(LIBNAME).$(VERSION).$(MINOR) $(INSTALLDIR)
	ldconfig $(INSTALLDIR)
	ln -sf $(INSTALLDIR)/$(LIBNAME).$(VERSION) $(INSTALLDIR)/$(LIBNAME)

uninstall: indeedroot
	@rm $(INSTALLDIR)/$(LIBNAME)*
	ldconfig $(INSTALLDIR)

clean:
	rm *.o
	rm *.so*

distclean: uninstall clean

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You must be root to run this program!" ; \
	    exit 1 ; \
	fi	    

.PHONY: help build install uninstall clean distclean indeedroot
