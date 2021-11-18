EXENAME = main
OBJS = data_frame.o main.o

CXX = clang++
CXXFLAGS = -std=c++1y -stdlib=libc++ -c -g -O0 -Wall -Wextra -pedantic
LD = clang++
LDFLAGS = -std=c++1y -stdlib=libc++ -lc++abi -lm

.PHONY: all test clean output_msg

all : $(EXENAME)

$(EXENAME): output_msg $(OBJS)
	$(LD) $(OBJS) $(LDFLAGS) -o $(EXENAME)

data_frame.o: core/data_frame.cpp core/data_frame.h
	$(CXX) $(CXXFLAGS) core/data_frame.cpp

# when you make a new file add two lines like the two above but change the filename/path

main.o: main.cpp core/data_frame.h
	$(CXX) $(CXXFLAGS) main.cpp

# if your main uses multiple files or different files, add it to line (main.o: main.cpp ..)
# delete my filename/path if not using it

clean:
	-rm -f *.o $(EXENAME) test