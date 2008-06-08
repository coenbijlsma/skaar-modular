
all:
	g++ -fPIC -g -c -Wall -combine ../VirtualUI.h DefaultUI.cpp
	g++ -shared -Wl,-soname,libdefaultui.so.1 -o libdefaultui.so.1.0 DefaultUI.o -lc

clean:
	rm ../*.gch
	rm *.o
	rm *.so*

.PHONY: all clean
