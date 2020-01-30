COMPILER	?= clang++
CFLAGS		:= -std=c++2a -O0 -g -Wall -Wextra -Iinclude
OUTPUT		?= ll2w
MAIN		:= main
SOURCES		:= $(shell find *.cpp **/*.cpp)
OBJECTS		:= $(SOURCES:.cpp=.o) parser/yylex.o parser/yyparse.o

LEXFLAGS	:= -Wno-sign-compare -Wno-register
LEXCPP		:= parser/yylex.cpp
PARSECPP	:= parser/yyparse.cpp
PARSEHDR	:= include/yyparse.h
FLEXSRC		:= parser/lexer.l
BISONSRC	:= parser/parser.y

CLOC_OPTIONS := --exclude-dir=.vscode --not-match-f='^yy(lex|parse)'

.PHONY: all test clean count countbf

all: $(OUTPUT)

$(OUTPUT): $(MAIN).o $(OBJECTS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(LEXCPP): $(FLEXSRC) $(PARSEHDR)
	flex --outfile=$(LEXCPP) $(FLEXSRC)

$(PARSECPP) $(PARSEHDR): $(BISONSRC)
	bison --defines=$(PARSEHDR) --output=$(PARSECPP) $(BISONSRC)

$(LEXCPP:.cpp=.o): $(LEXCPP)
	$(COMPILER) $(CFLAGS) $(LEXFLAGS) -c $< -o $@

$(PARSECPP:.cpp=.o): $(PARSECPP)
	$(COMPILER) $(CFLAGS) $(LEXFLAGS) -c $< -o $@

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

test: $(OUTPUT)
	./$< syntax.ll syntax.wasm

clean:
	rm -f $(OUTPUT) *.o parser/*.o graph_*.png $(PARSEHDR) $(PARSECPP) $(LEXCPP) parser/yyparse.output $(LEXCPP) $(PARSECPP)

count:
	cloc . parser $(CLOC_OPTIONS)

countbf:
	cloc --by-file . parser $(CLOC_OPTIONS)

DEPFILE  = .dep
DEPTOKEN = "\# MAKEDEPENDS"
DEPFLAGS = -f $(DEPFILE) -s $(DEPTOKEN)

depend:
	@ echo $(DEPTOKEN) > $(DEPFILE)
	makedepend $(DEPFLAGS) -- $(COMPILER) $(CFLAGS) -- $(SOURCES) 2>/dev/null
	@ rm $(DEPFILE).bak

sinclude $(DEPFILE)
