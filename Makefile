objects = map_test.o FNVHashFunc.o Node.o
CPP = g++
FLAGS = -std=c++11

test : $(objects)
	$(CPP) $(FLAGS) $(objects) -o test

map_test.o : HashFunc.h FNVHashFunc.h Node.h
FNVHashFunc.o : HashFunc.h FNVHashFunc.h Node.h
Node.o : Node.h
.PHONY : clean
clean :
	-rm $(objects)
