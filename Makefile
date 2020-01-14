COMPILER	?= clang++
CFLAGS		:= $(strip $(shell llvm-config --cxxflags)) -std=c++2a -O0 -g -Wall -Wextra
LDFLAGS		:= $(shell llvm-config --ldflags --libs --system-libs)
OUTPUT		?= ll2w
MAIN		:= main
MODULES		:= Node Graph DFSResult DTree DJGraph parser/ASTNode parser/Lexer parser/yylex parser/yyparse \
			   parser/StringSet parser/Parser
SOURCES		:= $(addsuffix .cpp,$(MODULES))
OBJECTS		:= $(addsuffix .o,$(MODULES)) parser/yylex.o

LEXFLAGS	:= -Wno-sign-compare -Wno-register
LEXCPP		:= parser/yylex.cpp
PARSECPP	:= parser/yyparse.cpp
PARSEHDR	:= parser/yyparse.h
FLEXSRC		:= parser/lexer.l
BISONSRC	:= parser/parser.y

.PHONY: all test clean

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

DEPFILE  = .dep
DEPTOKEN = "\# MAKEDEPENDS"
DEPFLAGS = -f $(DEPFILE) -s $(DEPTOKEN)

depend:
	@ echo $(DEPTOKEN) > $(DEPFILE)
	makedepend $(DEPFLAGS) -- $(COMPILER) $(CFLAGS) -- $(SOURCES) 2>/dev/null
	@ rm $(DEPFILE).bak

sinclude $(DEPFILE)
