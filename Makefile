all: multi_threading_unix

multi_threading_unix.o: multi_threading_unix.cpp
	c++ multi_threading_unix.cpp -c
	
multi_threading_unix: multi_threading_unix.o
	g++ multi_threading_unix.o -o multi_threading_unix -pthread

clean:
	rm -vf multi_threading_unix multi_threading_unix.o
