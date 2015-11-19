CC=g++ -std=c++11
LX=flex
BS=bison --yacc --defines

all:	avm/avm.cpp avm/parseABC.cpp
	$(CC) -g --output=The_Machine avm/avm.cpp avm/parseABC.cpp avm/execution.cpp avm/arithm_exe.cpp avm/rel_exe.cpp avm/libfuncs.cpp avm/tables.cpp avm/parseBin.cpp avm/functorcall.cpp

parser:	phase4/al.cpp phase4/parser.cpp phase4/hash.cpp phase4/intermediate.cpp phase4/target.cpp
	$(CC) -g --output=ggs phase4/al.cpp phase4/parser.cpp phase4/hash.cpp phase4/intermediate.cpp phase4/target.cpp

phase4/al.cpp:	phase4/lexi.l
	$(LX) --outfile=phase4/al.cpp phase4/lexi.l

phase4/parser.cpp:	phase4/parser.yy 
	$(BS) -v --output=phase4/parser.cpp phase4/parser.yy

clean: 
	rm -rf phase4/parser.cpp ggs phase4/al.cpp *.output avm/*.output phase4/*.output phase4/parser.hpp The_Machine
