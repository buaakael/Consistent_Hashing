objects = map_test.o FNVHashFunc.o 
CPP = g++
FLAGS = -std=c++11

test : $(objects)
	$(CPP) $(FLAGS) $(objects) -o test

map_test.o : HashFunc.h FNVHashFunc.h
FNVHashFunc.o : HashFunc.h FNVHashFunc.h

.PHONY : clean
clean :
	-rm $(objects)
