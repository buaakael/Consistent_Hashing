objects = main.o FNVHashFunc.o Node.o ConsistentHash.o
CPP = g++
FLAGS = -std=c++11

test : $(objects)
	$(CPP) $(FLAGS) $(objects) -o test

main.o : ConsistentHash.h
FNVHashFunc.o : HashFunc.h FNVHashFunc.h Node.h
Node.o : Node.h
ConsistentHash.o : ConsistentHash.h Node.h HashFunc.h FNVHashFunc.h
.PHONY : clean
clean :
	-rm $(objects)
