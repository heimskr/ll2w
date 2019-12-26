COMPILER	?= clang++
CFLAGS		?= -std=c++2a -O0 -g -Wall -Wextra
OUTPUT		?= ll2w
MAIN		:= main

.PHONY: all test clean

all: $(OUTPUT)

$(OUTPUT): $(MAIN).o
	$(COMPILER) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(COMPILER) $(CFLAGS) -c $< -o $@

test: $(OUTPUT)
	./$<

clean:
	rm -f $(OUTPUT) *.o
