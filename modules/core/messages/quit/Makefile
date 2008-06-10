
INSTALLDIR=/usr/local/lib
LIBNAME=libquitmessage.so
COMPILER=g++

help:
	@echo "Usage:" 
	@echo "make build		Builds the module libquitmessage.so.1.0"
	@echo "make install		Builds and installs the module. Needs root privileges."
	@echo "make uninstall		Removes the installed module and it's symlinks."
	@echo "			Also needs root privileges."
	@echo "make clean		Cleans up the files created at build-time."
	@echo "make test		Installs the module and compiles main.cpp."
	@echo "			Then run ./main to test the module."
	@echo "			This option also requires root privileges."
	@echo "make help		Shows this message"
	@echo
	@echo "Dependencies:"
	@echo "libircconnection, libskaartools"

build:
	$(COMPILER) -fPIC -g -c -Wall -Wl,export-dynamic -combine ../../../tools/StringTokenizer.h QuitMessage.h QuitMessage.cpp
	$(COMPILER) -shared -Wl,-soname,$(LIBNAME).1 -lircconnection -lskaartools -o $(LIBNAME).1.0 QuitMessage.o -lc

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
	rm main

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You need root privileges to run this program" ; \
	    exit 1 ; \
	fi

test: install
	g++ -combine QuitMessage.h main.cpp -rdynamic -ldl -lquitmessage -o main -v

.PHONY: help build install uninstall clean indeedroot test
