
INSTALLDIR=/usr/local/lib
LIBNAME=liblistmessage.so
VERSION=1
MINOR=0
COMPILER=g++
HEADERSDIR=../../../../include

help:
	@echo "Usage:" 
	@echo "make build		Builds the module $(LIBNAME).$(VERSION).$(MINOR)"
	@echo "make install		Builds and installs the module in $(INSTALLDIR)."
	@echo "			You needs root privileges for this."
	@echo "make uninstall		Removes the installed module and it's symlinks."
	@echo "			Also needs root privileges."
	@echo "make clean		Cleans up the files created at build-time."
	@echo "make distclean		Uninstalls the module and cleans this directory."
	@echo "			You need root for this."
	@echo "make test		Installs the module and builds a test executable."
	@echo "			This also needs root privileges."
	@echo "make help		Shows this message"
	@echo
	@echo "Dependencies:"
	@echo "libircconnection, libskaaruser, libskaartools"

build:
	$(COMPILER) -fPIC -g -c -Wall ListMessage.cpp -I$(HEADERSDIR)
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).$(VERSION) -lircconnection -lskaaruser -lskaartools -o $(LIBNAME).$(VERSION).$(MINOR) ListMessage.o -lc
#	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).$(VERSION) -o $(LIBNAME).$(VERSION).$(MINOR) QuitMessage.o -lc

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
	rm test

distclean: uninstall clean

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You need root privileges to run this program" ; \
	    exit 1 ; \
	fi

test: install
	$(COMPILER) -combine main.cpp -rdynamic -ldl -I$(HEADERSDIR) -llistmessage -o test -v

.PHONY: help build install uninstall clean distclean indeedroot test
