COMPILER	?= clang++
CFLAGS		:= -std=c++2a -O0 -g -Wall -Wextra
OUTPUT		?= ll2w
MAIN		:= main
MODULES		:= Node Graph
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
