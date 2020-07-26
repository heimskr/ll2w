COMPILER		?= clang++
DEBUGGER		?= lldb
OPTIMIZATION	?= -O0 -g
STANDARD		?= c++2a
WARNINGS		?= -Wall -Wextra
CFLAGS			:= -std=$(STANDARD) $(OPTIMIZATION) $(WARNINGS) -Iinclude
OUTPUT			?= ll2w
# TESTFILE		?= ~/src/mal/combined.9.ll
# TESTFILE		?= ~/src/ir_examples/varargs_simple.ll
TESTFILE		?= ll/fat.ll
MAIN			:= main
SOURCES			:= $(shell find src/**/*.cpp)
OBJECTS			:= $(SOURCES:.cpp=.o) src/parser/yylex.o src/parser/yyparse.o

LEXFLAGS		:= -Wno-sign-compare -Wno-register
LEXCPP			:= src/parser/yylex.cpp
PARSECPP		:= src/parser/yyparse.cpp
PARSEHDR		:= include/yyparse.h
FLEXSRC			:= src/parser/lexer.l
BISONSRC		:= src/parser/parser.y

CLOC_OPTIONS := --exclude-dir=.vscode --not-match-f='^yy(lex|parse)'

.PHONY: all clean count countbf declutter test

all: $(OUTPUT)

$(OUTPUT): src/$(MAIN).o $(OBJECTS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(LEXCPP): $(FLEXSRC) $(PARSEHDR)
	flex --outfile=$(LEXCPP) $(FLEXSRC)

$(PARSECPP) $(PARSEHDR): $(BISONSRC)
	bison --defines=$(PARSEHDR) --output=$(PARSECPP) $(BISONSRC)

$(LEXCPP:.cpp=.o): $(LEXCPP)
	$(COMPILER) $(CFLAGS) $(LEXFLAGS) -c $< -o $@

$(PARSECPP:.cpp=.o): $(PARSECPP) $(PARSEHDR)
	$(COMPILER) $(CFLAGS) $(LEXFLAGS) -c $< -o $@

%.o: %.cpp include/yyparse.h
	$(COMPILER) $(CFLAGS) -c $< -o $@

test: $(OUTPUT)
	./$< $(TESTFILE)

dbg: $(OUTPUT)
	$(DEBUGGER) $< -- $(TESTFILE)

clean:
	rm -f $(OUTPUT) src/*.o src/**/*.o graph_*.png $(PARSEHDR) $(PARSECPP) $(LEXCPP) $(PARSECPP:.c=.output) $(LEXCPP) $(PARSECPP) PVS-Studio.log report.tasks strace_out

declutter:
	rm -f graph_*.png

grind: $(OUTPUT)
	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --show-reachable=no ./$<

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
