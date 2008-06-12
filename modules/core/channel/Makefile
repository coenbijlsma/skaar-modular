
INSTALLDIR=/usr/local/lib
LIBNAME=libircchannel.so
VERSION=1
MINOR=0
COMPILER=g++
HEADERSDIR=../../../include

help:
	@echo "Usage:" 
	@echo "make build		Builds the module $(LIBNAME).$(VERSION).$(MINOR)"
	@echo "make install		Builds and installs the module in $(INSTALLDIR)."
	@echo "			You need root privileges for this."
	@echo "make uninstall		Removes the installed module and it's symlinks."
	@echo "			Also needs root privileges."
	@echo "make clean		Cleans up the files created at build-time."
	@echo "			This option also requires root privileges."
	@echo "make distclean		Uninstalls and cleans. You need root for this."
	@echo "make help		Shows this message."
	@echo
	@echo "Dependencies:"
	@echo "none"

build:
	$(COMPILER) -fPIC -g -c -Wall -I$(HEADERSDIR) Channel.cpp
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).$(VERSION) -o $(LIBNAME).$(VERSION).$(MINOR) Channel.o -lc

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
	    echo "You need root privileges to run this program" ; \
	    exit 1 ; \
	fi

.PHONY: help build install uninstall clean distclean indeedroot
