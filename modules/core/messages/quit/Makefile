
INSTALLDIR=/usr/local/lib

build:
	g++ -fPIC -g -c -Wall -Wl,export-dynamic -combine ../../tools/StringTokenizer.h ../../tools/StringTokenizer.cpp QuitMessage.h QuitMessage.cpp
	g++ -shared -Wl,-soname,libquitmessage.so.1 -o libquitmessage.so.1.0 QuitMessage.o StringTokenizer.o -lc

install: indeedroot build
	cp libquitmessage.so.1.0 $(INSTALLDIR)
	ldconfig $(INSTALLDIR)
	ln -sf $(INSTALLDIR)/libquitmessage.so.1 $(INSTALLDIR)/libquitmessage.so

uninstall: indeedroot
	@rm $(INSTALLDIR)/libquitmessage.so*
	ldconfig $(INSTALLDIR)

clean:
	rm *.gch
	rm *.o
	rm *.so*

indeedroot:
	@if [ `whoami` != "root" ] ; then \
	    echo "You need root privileges to run this program" ; \
	    exit 1 ; \
	fi

.PHONY: build install uninstall clean indeedroot
