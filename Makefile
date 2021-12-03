steamer: main.cc lib/*.h src/*.cc
	$(CXX) $(CXXFLAGS) -o steamer -I lib/ main.cc src/*.cc

test: tests.cc lib/*.h src/*.cc
	$(CXX) $(CXXFLAGS) -o test -I lib/ tests.cc src/*.cc