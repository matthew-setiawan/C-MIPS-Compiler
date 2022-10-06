targetloc = src/parser.tab.cpp src/lexer.yy.cpp bin/c_compiler compiler src/parser.tab.hpp
parser = src/parser.y -o src/parser.tab.cpp
GPP = g++

CPPFLAGS += -std=c++11 -W -Wall -g -Wno-unused-variable -Wno-unused-function -Wno-unused-parameter
CPPFLAGS +=  -I src -I include
 
all : $(targetloc)

src/parser.tab.cpp: src/parser.y
	bison -v -d $(parser)
	mkdir -p bin

src/parser.tab.hpp:
	bison -v -d $(parser)

src/lexer.yy.cpp: src/lexer.flex src/parser.tab.hpp
	flex -o src/lexer.yy.cpp  src/lexer.flex

bin/c_compiler: src/compiler.o src/parser.tab.o src/lexer.yy.o src/parser.tab.o
	$(GPP) $(CPPFLAGS) -o bin/c_compiler $^

compiler : bin/c_compiler.output

.PHONY: clean
clean :
	rm -f src/*.tab.cpp
	rm -f src/*.yy.cpp
	rm -f src/*.output
	rm -f src/*.o
	rm -f bin/* 
	

