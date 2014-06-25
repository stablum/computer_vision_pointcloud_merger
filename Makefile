all: multi_threading_unix

multi_threading_unix.o: multi_threading_unix.cpp
	c++ multi_threading_unix.cpp -c
	
multi_threading_unix: multi_threading_unix.o
	g++ multi_threading_unix.o -o multi_threading_unix -pthread

clean:
	rm -vf multi_threading_unix reader *.o

openni_test.o: openni_test.cpp definitions.h
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
	g++ reader.o -o openni_test -L/usr/lib \
		-lboost_system \
		-lboost_thread \
		-lOpenNI \
		-lpcl_visualization \
		-lpcl_io
		
reader.o: reader.cpp definitions.h
	c++ reader.cpp \
		-I/usr/include/pcl-1.7/ \
		-I/usr/include/vtk-5.8/ \
		-I/usr/include/eigen3/ \
		-I/usr/include/ni/ \
		-c

keypoints_detector.o: keypoints_detector.cpp definitions.h
	c++ keypoints_detector.cpp \
		-I/usr/include/pcl-1.7/ \
		-I/usr/include/vtk-5.8/ \
		-I/usr/include/eigen3/ \
		-I/usr/include/ni/ \
		-c

viewer.o: viewer.cpp definitions.h
	c++ viewer.cpp \
		-I/usr/include/pcl-1.7/ \
		-I/usr/include/vtk-5.8/ \
		-I/usr/include/eigen3/ \
		-I/usr/include/ni/ \
		-c

downsampling.o: downsampling.cpp definitions.h
	c++ downsampling.cpp \
		-I/usr/include/pcl-1.7/ \
		-I/usr/include/vtk-5.8/ \
		-I/usr/include/eigen3/ \
		-I/usr/include/ni/ \
		-c

reader: reader.o keypoints_detector.o viewer.o downsampling.o
	g++ $^ -o reader -L/usr/lib \
		-lboost_system \
		-lboost_thread \
		-lpcl_visualization \
		-lpcl_io \
		-lpcl_common \
		-lpcl_surface \
		-lpcl_io_ply \
		-lpcl_kdtree \
		-lpcl_keypoints \
		-lpcl_registration \
		-lpcl_octree \
		-lpcl_search \
		-lpcl_features \
		-lpcl_filters \
		-lQVTK \
		-lvtkCharts \
		-lvtkCommon \
		-lvtkFiltering \
		-lvtkGeovis \
		-lvtkRendering
		
