COMPILER		?= clang++
DEBUGGER		?= lldb
OPTIMIZATION	?= -O3
STANDARD		?= c++2a
WARNINGS		?= -Wall -Wextra
CFLAGS			:= -std=$(STANDARD) $(OPTIMIZATION) $(WARNINGS) -Iinclude
OUTPUT			?= ll2w
# TESTFILE		?= ~/src/mal/combined.strprint.ll
# TESTFILE		?= ~/src/ir_examples/varargs_simple.ll
# TESTFILE		?= ll/mal.ll
# TESTFILE		?= ll/mintf.ll
# TESTFILE		?= ll/inline_asm.ll
# TESTFILE		?= ll/paging.ll
# TESTFILE		?= ~/ll2w.wasm
# TESTFILE		?= ll/extractvalue.ll
# TESTFILE		?= ll/mal_inline.ll
# TESTFILE		?= ~/src/thurisaz/main.ll
# TESTFILE		?= ll/doublephi.ll
TESTFILE		?= ll/20args.ll

LEXFLAGS		:= -Wno-sign-compare -Wno-register
LLVMLEXCPP		:= src/parser/yylex.cpp
LLVMPARSECPP	:= src/parser/yyparse.cpp
LLVMPARSEHDR	:= include/yyparse.h
LLVMFLEXSRC		:= src/parser/lexer.l
LLVMBISONSRC	:= src/parser/parser.y

WASMLEXCPP		:= src/parser/wasmlex.cpp
WASMPARSECPP	:= src/parser/wasmparse.cpp
WASMPARSEHDR	:= include/wasmparse.h
WASMFLEXSRC		:= src/parser/wasm.l
WASMBISONSRC	:= src/parser/wasm.y

CLOC_OPTIONS	:= --exclude-dir=.vscode --not-match-f='^yy(lex|parse)'
BISON_OPTIONS	:= --color=always
SOURCES			:= $(shell find src/**/*.cpp src/*.cpp)
OBJECTS			:= $(SOURCES:.cpp=.o) $(LLVMLEXCPP:.cpp=.o) $(LLVMPARSECPP:.cpp=.o) $(WASMLEXCPP:.cpp=.o) $(WASMPARSECPP:.cpp=.o)

.PHONY: all clean count countbf declutter test

all: $(OUTPUT)

$(OUTPUT): $(OBJECTS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

$(LLVMLEXCPP): $(LLVMFLEXSRC) $(LLVMPARSEHDR)
	flex --prefix=llvm --outfile=$(LLVMLEXCPP) $(LLVMFLEXSRC)

$(LLVMPARSECPP) $(LLVMPARSEHDR): $(LLVMBISONSRC)
	bison $(BISON_OPTIONS) --defines=$(LLVMPARSEHDR) --output=$(LLVMPARSECPP) $(LLVMBISONSRC)

$(LLVMLEXCPP:.cpp=.o): $(LLVMLEXCPP)
	$(COMPILER) $(CFLAGS) $(LEXFLAGS) -c $< -o $@

$(LLVMPARSECPP:.cpp=.o): $(LLVMPARSECPP) $(LLVMPARSEHDR)
	$(COMPILER) $(CFLAGS) $(LEXFLAGS) -c $< -o $@

$(WASMLEXCPP): $(WASMFLEXSRC) $(WASMPARSEHDR)
	flex --prefix=wasm --outfile=$(WASMLEXCPP) $(WASMFLEXSRC)

$(WASMPARSECPP) $(WASMPARSEHDR): $(WASMBISONSRC)
	bison $(BISON_OPTIONS) --defines=$(WASMPARSEHDR) --output=$(WASMPARSECPP) $(WASMBISONSRC)

$(WASMLEXCPP:.cpp=.o): $(WASMLEXCPP)
	$(COMPILER) $(CFLAGS) $(LEXFLAGS) -c $< -o $@

$(WASMPARSECPP:.cpp=.o): $(WASMPARSECPP) $(WASMPARSEHDR)
	$(COMPILER) $(CFLAGS) $(LEXFLAGS) -c $< -o $@

%.o: %.cpp include/yyparse.h include/wasmparse.h
	$(COMPILER) $(CFLAGS) -c $< -o $@

test: $(OUTPUT)
	./$< $(TESTFILE)

dbg: $(OUTPUT)
	$(DEBUGGER) $< -- $(TESTFILE)

clean:
	rm -f $(OUTPUT) src/*.o src/**/*.o graph_*.png \
		$(LLVMPARSEHDR) $(LLVMPARSECPP) $(LLVMLEXCPP) $(LLVMPARSECPP:.c=.output) $(LLVMLEXCPP) $(LLVMPARSECPP) \
		$(WASMPARSEHDR) $(WASMPARSECPP) $(WASMLEXCPP) $(WASMPARSECPP:.c=.output) $(WASMLEXCPP) $(WASMPARSECPP) \
		PVS-Studio.log report.tasks strace_out

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
