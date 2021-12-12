CXX = clang++
LDFLAGS = -std=c++14 -stdlib=libc++ -lc++abi

SRC_FILES = $(shell find src/ -name '*.cc')

CXXFLAGS = $(LDFLAGS)\
	-Wall -Wpedantic -Wconversion\
	-O2 -march=native -pipe -I src/

steamer: main.cc $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o steamer main.cc $(SRC_FILES)

test: tests.cc $(SRC_FILES)
	$(CXX) $(CXXFLAGS) -o test tests.cc $(SRC_FILES)
