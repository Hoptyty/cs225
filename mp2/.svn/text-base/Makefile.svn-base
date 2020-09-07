EXENAME= testimage
EXENAME2 = testscene
OBJS=  rgbapixel.o png.o image.o testimage.o
OBJS2= rgbapixel.o png.o image.o scene.o testscene.o
CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic 
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME) $(EXENAME2)

$(EXENAME) : $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

$(EXENAME2):$(OBJS2)
	$(LD) $(OBJS2) $(LDFLAGS) -o $(EXENAME2)

rgbapixel.o : rgbapixel.cpp rgbapixel.h
	$(CXX) $(CXXFLAGS) rgbapixel.cpp

png.o : png.cpp png.h rgbapixel.h
	$(CXX) $(CXXFLAGS) png.cpp

image.o : image.cpp image.h png.h
	$(CXX) $(CXXFLAGS) image.cpp

scene.o : scene.cpp scene.h image.h
	$(CXX) $(CXXFLAGS) scene.cpp

testimage.o: testimage.cpp image.h
	$(CXX) $(CXXFLAGS) testimage.cpp

testscene.o: testscene.cpp scene.h image.h
	$(CXX) $(CXXFLAGS) testscene.cpp
clean :
	-rm -f *.o $(EXENAME) $(EXENAME2)
