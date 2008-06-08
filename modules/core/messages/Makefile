
all:
	g++ -fPIC -g -c -Wall -combine Message.h QuitMessage.cpp
	g++ -shared -Wl,-soname,libquitmessage.so.1 -o libquitmessage.so.1.0 QuitMessage.o -lc

clean:
	rm *.gch
	rm *.o
	rm *.so*

.PHONY: all clean
