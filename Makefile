
INSTALLDIR=/usr/bin
VERSION=0
MINOR=1
COMPILER=g++
HEADERSDIR=include
EXECNAME=skaar

help:
	@echo "Usage:" 
	@echo "make build		Builds the executable $(EXECNAME) version $(VERSION).$(MINOR)"
	@echo "make install		Builds and installs the executable in $(INSTALLDIR)."
	@echo "			You needs root privileges for this."
	@echo "make uninstall		Removes $(EXECNAME)."
	@echo "			Also needs root privileges."
	@echo "make clean		Cleans up the files created at build-time."
	@echo "make distclean		Uninstalls the module and cleans this directory."
	@echo "			You need root for this."
	@echo "make help		Shows this message"
	@echo
	@echo "Dependencies:"
	@echo "libskaarlog, libircconnection, libircchannel, libskaartools, libskaarconfig -libskaaruser, lib*ui, lib*message"

build:
	$(COMPILER) -I$(HEADERSDIR) -combine main.cpp Skaar.cpp -ldl -lskaarlog -lircconnection -lircchannel -lskaartools -lskaarconfig -lskaaruser -ldefaultui -lpassmessage -lnickmessage -lusermessage -lgenericmessage -o $(EXECNAME) -v

install: indeedroot build
# XXX INSTALL LIBRARIES
	cp $(EXECNAME) $(INSTALLDIR)

uninstall: indeedroot
	@rm $(INSTALLDIR)/$(EXECNAME)
# XXX UNINSTALL LIBRARIES

clean:
	rm skaar

distclean: uninstall clean

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You need root privileges to run this program" ; \
	    exit 1 ; \
	fi

.PHONY: help build install uninstall clean distclean indeedroot
