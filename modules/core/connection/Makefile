
all:
	g++ -fPIC -g -c -Wall -combine IRCConnection.h IRCConnection.cpp
	g++ -shared -Wl,-soname,libircconnection.so.1 -o libircconnection.so.1.0 IRCConnection.o -lc

clean:
	rm *.gch
	rm *.o
	rm *.so*

.PHONY: all clean
