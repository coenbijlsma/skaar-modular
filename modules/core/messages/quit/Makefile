
INSTALLDIR=/usr/local/lib
LIBNAME=libquitmessage.so
VERSION=1
MINOR=0
COMPILER=g++
HEADERSDIR=../../../../headers

help:
	@echo "Usage:" 
	@echo "make build		Builds the module $(LIBNAME).$(VERSION).$(MINOR)"
	@echo "make install		Builds and installs the module in $(INSTALLDIR)."
	@echo "			You needs root privileges for this."
	@echo "make uninstall		Removes the installed module and it's symlinks."
	@echo "			Also needs root privileges."
	@echo "make clean		Cleans up the files created at build-time."
	@echo "make test		Installs the module and compiles main.cpp."
	@echo "			Then run ./main to test the module."
	@echo "			This option also requires root privileges."
	@echo "make distclean		Uninstalls the module and cleans this directory."
	@echo "			You need root for this."
	@echo "make help		Shows this message"
	@echo
	@echo "Dependencies:"
	@echo "libircconnection, libskaaruser, libircchannel, libskaartools"

build:
	$(COMPILER) -fPIC -g -c -Wall QuitMessage.cpp -I$(HEADERSDIR)
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).$(VERSION) -lircconnection -lskaaruser -lircchannel -lskaartools -o $(LIBNAME).$(VERSION).$(MINOR) QuitMessage.o -lc
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
	rm main

distclean: uninstall clean

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You need root privileges to run this program" ; \
	    exit 1 ; \
	fi

test: install
	$(COMPILER) -combine main.cpp -rdynamic -ldl -I$(HEADERSDIR) -lquitmessage -o main -v

.PHONY: help build install uninstall clean distclean indeedroot test
