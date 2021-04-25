#include <cstdint>

struct P0Wrapper {
	uint64_t *entries;

	P0Wrapper(uint64_t *entries_): entries(entries_) {}
};

void pagefault();

void (*table[])() = {0, 0, 0, 0, pagefault, 0};

void strprint(const char *str);

void __attribute__((naked)) prd(long x) {
	asm("<prd $a0>");
}

void __attribute__((naked)) prc(char x) {
	asm("<prc $a0>");
}

int main() {
	strprint("Hello, world!\n");
	asm("rit table");
	prd(*((volatile long *) 1));
	prc('\n');

	P0Wrapper wrapper((uint64_t *) 65536);
	prd((long) wrapper.entries);
	prc('\n');

	asm("page on");
	prd(*((volatile long *) 1));
	prc('\n');
}

void pagefault() {
	strprint("Page fault!");
	asm(": $e0");
}

void __attribute__((naked)) strprint(const char *str) {
	asm("<>; @_strprint_loop      \
	     [$a0] -> $ma /b          \
	     : _strprint_print if $ma \
	     : _strprint_done         \
	     @_strprint_print         \
	     <prc $ma>                \
	     $a0 + 1 -> $a0           \
	     : _strprint_loop         \
	     @_strprint_done");
}
