GCC := g++
CXXFLAGS += -std=c++23

run: test_rt 
	./test_rt

test_rt: test_rt.cpp rt.h simtest.h
clean:
	rm -f test_rt.exe


