define void @main() {
	; Implicit block %0
	; %1 = alloca {i8*, i8, i32, {i16, i64}, i8*, i32}
	; %2 = load {i8*, i8, i32, {i16, i64}, i8*, i32}, {i8*, i8, i32, {i16, i64}, i8*, i32}* %1
	; %3 = extractvalue {i8*, i8, i32, {i16, i64}, i8*, i32} %2, 3
	%4 = alloca {i8*, i8, i32, i32, {i8, i16}, i8*, i32}
	%5 = load {i8*, i8, i32, i32, {i8, i16}, i8*, i32}, {i8*, i8, i32, i32, {i8, i16}, i8*, i32}* %4
	%6 = extractvalue {i8*, i8, i32, i32, {i8, i16}, i8*, i32} %5, 4
	ret i32 666
}