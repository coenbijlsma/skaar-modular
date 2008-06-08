
all:
	g++ -fPIC -g -c -Wall -combine ../VirtualUI.h NCursesUI.cpp
	g++ -shared -Wl,-soname,libncursesui.so.1 -o libncursesui.so.1.0 NCursesUI.o -lc

clean:
	rm ../*.gch
	rm *.o
	rm *.so*

.PHONY: all clean
