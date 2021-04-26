#include <cstdint>

struct P0Wrapper {
	uint64_t *entries;

	P0Wrapper(uint64_t *entries_): entries(entries_) {}
	void set() { asm("setpt %0" :: "r"(entries)); }
	static unsigned char  p0Offset  (void *addr) { return (((uintptr_t) addr) >> 56) & 0xff;   }
	static unsigned char  p1Offset  (void *addr) { return (((uintptr_t) addr) >> 48) & 0xff;   }
	static unsigned char  p2Offset  (void *addr) { return (((uintptr_t) addr) >> 40) & 0xff;   }
	static unsigned char  p3Offset  (void *addr) { return (((uintptr_t) addr) >> 32) & 0xff;   }
	static unsigned char  p4Offset  (void *addr) { return (((uintptr_t) addr) >> 24) & 0xff;   }
	static unsigned char  p5Offset  (void *addr) { return (((uintptr_t) addr) >> 16) & 0xff;   }
	static unsigned short pageOffset(void *addr) { return  ((uintptr_t) addr)        & 0xffff; }

	static bool isPresent(uint64_t entry) { return (entry & 1) == 1; }

	uint64_t getP0E(void *addr) { return entries[p0Offset(addr)]; }
	bool getP1E(void *addr, uint64_t &out) {
		uint64_t p0e = getP0E(addr);
		if (!isPresent(p0e))
			return false;
		out = ((uint64_t *) (p0e & ~0xff))[p1Offset(addr)];
		return true;
	}
	bool getP2E(void *addr, uint64_t &out) {
		uint64_t p1e;
		if (!getP1E(addr, p1e))
			return false;
		if (!isPresent(p1e))
			return false;
		out = ((uint64_t *) (p1e & ~0xff))[p2Offset(addr)];
		return true;
	}
	bool getP3E(void *addr, uint64_t &out) {
		uint64_t p2e;
		if (!getP2E(addr, p2e))
			return false;
		if (!isPresent(p2e))
			return false;
		out = ((uint64_t *) (p2e & ~0xff))[p3Offset(addr)];
		return true;
	}
	bool getP4E(void *addr, uint64_t &out) {
		uint64_t p3e;
		if (!getP3E(addr, p3e))
			return false;
		if (!isPresent(p3e))
			return false;
		out = ((uint64_t *) (p3e & ~0xff))[p4Offset(addr)];
		return true;
	}
	bool getP5E(void *addr, uint64_t &out) {
		uint64_t p4e;
		if (!getP4E(addr, p4e))
			return false;
		if (!isPresent(p4e))
			return false;
		out = ((uint64_t *) (p4e & ~0xff))[p5Offset(addr)];
		return true;
	}
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

void __attribute__((naked)) prx(char x) {
	asm("<prx $a0>");
}

int main() {
	strprint("Hello, world!\n");
	asm("rit table");
	prd(*((volatile long *) 1));
	prc('\n');

	P0Wrapper wrapper((uint64_t *) 65536);
	prd((long) wrapper.entries);
	prc('\n');
	wrapper.set();
	uint64_t p5e;
	if (!wrapper.getP5E((void *) 65536, p5e)) {
		strprint("No\n");
	} else {
		strprint("P5E: ");
		prx(p5e);
		prc('\n');
	}

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
	     @_strprint_done; <>");
}
