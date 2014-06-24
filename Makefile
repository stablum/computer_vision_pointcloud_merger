all: multi_threading_unix

multi_threading_unix.o: multi_threading_unix.cpp
	c++ multi_threading_unix.cpp -c
	
multi_threading_unix: multi_threading_unix.o
	g++ multi_threading_unix.o -o multi_threading_unix -pthread

clean:
	rm -vf multi_threading_unix multi_threading_unix.o

openni_test.o: openni_test.cpp
	c++ openni_test.cpp \
		-I/usr/include/qt4/QtCore/ \
		-I/usr/include/qt4/ \
		-I/usr/include/qt4/QtGui/ \
		-I/usr/include/qt4/QtNetwork/ \
		-I/usr/include/pcl-1.7/ \
		-I/usr/include/vtk-5.8/ \
		-I/usr/include/eigen3/ \
		-I/usr/include/ni/ \
		-c

openni_test: openni_test.o
	g++ openni_test.o -o openni_test -L/usr/lib \
		-lboost_system \
		-lboost_thread \
		-lOpenNI \
		-lpcl_visualization \
		-lpcl_io
		
