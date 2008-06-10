
all:
	g++ -rdynamic -fPIC -shared -g -c -Wall -combine ../../../tools/StringTokenizer.h ../../../tools/StringTokenizer.cpp Message.h QuitMessage.cpp
	g++ -rdynamic -shared -Wl,-soname,libquitmessage.so.1 -o libquitmessage.so.1.0 QuitMessage.o StringTokenizer.o -lc

clean:
	rm *.gch
	rm *.o
	rm *.so*

.PHONY: all clean
