GCC := g++
CXXFLAGS += -std=c++23

run: test_rt 
	./test_rt

clean:
	rm -f test_rt.exe


