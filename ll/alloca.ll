define i32 @fn1() {
	%1 = alloca i32
	%2 = alloca i8, align 1
	%3 = load i8, i8* %2
	%4 = zext i8 %3 to i32
	%5 = load i32, i32* %1
	%6 = add i32 %4, %5
	ret i32 %6
}