CC=g++ -std=c++11
LX=flex
BS=bison --yacc --defines

all:	al.cpp parser.cpp hash.cpp intermediate.cpp target.cpp
	$(CC) -g --output=ggs al.cpp parser.cpp hash.cpp intermediate.cpp target.cpp

al.cpp:	lexi.l
	$(LX) --outfile=al.cpp lexi.l

parser.cpp:	parser.yy 
	$(BS) -v --output=parser.cpp parser.yy

avm:	avm/avm.cpp avm/parseABC.cpp
	g++ -std=c++11 -g -o The_Machine avm/avm.cpp avm/parseABC.cpp avm/execution.cpp avm/arithm_exe.cpp avm/rel_exe.cpp avm/libfuncs.cpp avm/tables.cpp avm/parseBin.cpp avm/functorcall.cpp

clean: 
	rm -rf parser.cpp ggs al.cpp *.output parser.hpp avm/The_Machine
