EXENAME= sorting
OBJS = main.o sorting.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lpng -lc++abi

all : $(EXENAME)

$(EXENAME) : $(OBJS)
		 $(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

main.o : main.cpp sorting.h
		$(CXX) $(CXXFLAGS) main.cpp

sorting.o : sorting.cpp sorting.h
		$(CXX) $(CXXFLAGS) sorting.cpp

clean :
		  -rm -f *.o $(EXENAME)

