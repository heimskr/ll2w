COMPILER	?= clang++
CFLAGS		:= -std=c++2a -O0 -g -Wall -Wextra
OUTPUT		?= ll2w
MAIN		:= main
MODULES		:= Node Graph DFSResult DTree
SOURCES		:= $(addsuffix .cpp,$(MODULES))
OBJECTS		:= $(addsuffix .o,$(MODULES))

.PHONY: all test clean

all: $(OUTPUT)

$(OUTPUT): $(MAIN).o $(OBJECTS)
	$(COMPILER) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

test: $(OUTPUT)
	./$< syntax.ll syntax.wasm

clean:
	rm -f $(OUTPUT) *.o

DEPFILE  = .dep
DEPTOKEN = "\# MAKEDEPENDS"
DEPFLAGS = -f $(DEPFILE) -s $(DEPTOKEN)

depend:
	@ echo $(DEPTOKEN) > $(DEPFILE)
	makedepend $(DEPFLAGS) -- $(COMPILER) $(CFLAGS) -- $(SOURCES) 2>/dev/null
	@ rm $(DEPFILE).bak

sinclude $(DEPFILE)
