
void pagefault();

void (*table[])() = {pagefault};

void strprint(const char *str);

void prd(long x) {
	asm("<prd $0>" :: "r"(x));
}

int main() {
	strprint("Hello, world!\n");
	prd(*((volatile long *) 1));
	strprint("\n");
}

void pagefault() {
	strprint("Page fault!");
	asm(": $e0");
}

void strprint(const char *str) {
	asm("                        \
		@_strprint_loop          \
		[%0] -> $ma /b           \
		: _strprint_print if $ma \
		: $rt                    \
		@_strprint_print         \
		<prc $ma>                \
		%0 + 1 -> %0             \
		: _strprint_loop" :: "r"(str));

	// 	@_strprint_loop
	// 		[$a0] -> $ma /b
	// 		: _strprint_print if $ma
	// 		!done
	// 		@_strprint_print
	// 		<prc $ma>
	// 		$a0++
	// 		: _strprint_loop
}