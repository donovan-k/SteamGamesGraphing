EXENAME = main
OBJS = data_frame.o main.o

CXX = clang++
CXXFLAGS = $(CS225) -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

.PHONY: all test clean output_msg

all : $(EXENAME)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

data_frame.o: core/data_frame.cpp core/data_frame.h
	$(CXX) $(CXXFLAGS) core/data_frame.cpp

main.o: main.cpp core/data_frame.h
	$(CXX) $(CXXFLAGS) main.cpp

clean:
	-rm -f *.o $(EXENAME) test