define i8* @foo() {
	%1 = alloca i8, align 1
	%2 = alloca i1, align 1
	%3 = load i1, i1* %2, align 1
	br i1 %3, label %4, label %6

; <label>:4: ; preds = %0
	%5 = alloca i8, align 1
	br label %6

; <label>:6: ; preds = %0, %4
	%7 = phi i8* [%1, %0], [%5, %4]
	ret i8* %7
}