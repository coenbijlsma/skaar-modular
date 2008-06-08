
all: 
	g++ -fPIC -g -c -Wall -combine User.h User.cpp
	g++ -shared -Wl,-soname,libuser.so.1 -o libuser.so.1.0 User.o -lc

clean:
	rm *gch
	rm *o
	rm *.so*

.PHONY: all clean
