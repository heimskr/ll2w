define i8* @foo() {
	%1 = alloca i8, align 1
	%2 = alloca i1, align 1
	%3 = load i1, i1* %2, align 1
	br i1 %3, label %100, label %200

100: ; preds = %0
	%4 = alloca i8, align 1
	br i1 true, label %200, label %300

200: ; preds = %0, %100
	%5 = phi i8* [%1, %0], [%4, %100]
	store i8 64, i8* %5
	%6 = load i8, i8* %5, align 1
	%7 = inttoptr i8 %6 to i8*
	br i1 false, label %300, label %400

300: ; preds = %100, %200
	%8 = phi i8* [%4, %100], [%5, %200]
	br label %400

400: ; preds = %200, %300
	%9 = phi i8* [%7, %200], [%8, %300]
	store i8 107, i8* %7
	store i8 108, i8* %8
	store i8 109, i8* %9
	ret i8* %9
}