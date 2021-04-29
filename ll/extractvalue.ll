define void @main() {
	; Implicit block %0
	; %1 = alloca {i8*, i8, i32, {i16, i64}, i8*, i32}
	; %2 = load {i8*, i8, i32, {i16, i64}, i8*, i32}, {i8*, i8, i32, {i16, i64}, i8*, i32}* %1
	; %3 = extractvalue {i8*, i8, i32, {i16, i64}, i8*, i32} %2, 3
	; %4 = alloca {i8*, i8, i32, i32, {i8, i16}, i8*, i32}
	; %5 = load {i8*, i8, i32, i32, {i8, i16}, i8*, i32}, {i8*, i8, i32, i32, {i8, i16}, i8*, i32}* %4
	; %6 = extractvalue {i8*, i8, i32, i32, {i8, i16}, i8*, i32} %5, 4
	%7 = alloca {i32, {i64, i16, i64}, i32}
	%8 = load {i32, {i64, i16, i64}, i32}, {i32, {i64, i16, i64}, i32}* %7
	%9 = extractvalue {i32, {i64, i16, i64}, i32} %8, 1

	%10 = extractvalue {i64, i16, i64} %9, 0
	%11 = extractvalue {i64, i16, i64} %9, 1
	%12 = extractvalue {i64, i16, i64} %9, 2

	call void asm sideeffect "<prd $0>", "r,~{dirflag},~{fpsr},~{flags}"(i64 %10)
	call void asm sideeffect "<prd $0>", "r,~{dirflag},~{fpsr},~{flags}"(i16 %11)
	call void asm sideeffect "<prd $0>", "r,~{dirflag},~{fpsr},~{flags}"(i64 %12)
	ret i32 666
}