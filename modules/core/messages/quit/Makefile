
INSTALLDIR=/usr/local/lib
LIBNAME=libmessage.so
VERSION=1
MINOR=0
COMPILER=g++

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
	@echo "make help		Shows this message"
	@echo
	@echo "Dependencies:"
	@echo "libircconnection, libskaaruser, libircchannel, libskaartools"

build:
	$(COMPILER) -fPIC -g -c -Wall -Wl,export-dynamic -combine ../../../tools/StringTokenizer.h QuitMessage.h QuitMessage.cpp
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).$(VERSION) -lircconnection -lskaaruser -lircchannel -lskaartools -o $(LIBNAME).$(VERSION).$(MINOR) QuitMessage.o -lc

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
	rm main

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You need root privileges to run this program" ; \
	    exit 1 ; \
	fi

test: install
	$(COMPILER) -combine QuitMessage.h main.cpp -rdynamic -ldl -lquitmessage -o main -v

.PHONY: help build install uninstall clean indeedroot test
