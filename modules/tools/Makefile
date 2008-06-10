
INSTALLDIR=/usr/local/lib

build:
	g++ -fPIC -g -c -Wall -combine StringTokenizer.h StringTokenizer.cpp
	g++ -shared -Wl,-soname,libskaartools.so.1 -o libskaartools.so.1.0 StringTokenizer.o -lc

install: indeedroot build
	cp libskaartools.so.1.0 $(INSTALLDIR)
	ldconfig $(INSTALLDIR)
	ln -sf $(INSTALLDIR)/libskaartools.so.1 $(INSTALLDIR)/libskaartools.so

uninstall: indeedroot
	@rm $(INSTALLDIR)/libskaartools.so*
	ldconfig $(INSTALLDIR)

clean:
	rm *.gch
	rm *.o
	rm *.so*

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You must be root to run this program!" ; \
	    exit 1 ; \
	fi	    

.PHONY: install uninstall build clean indeedroot
