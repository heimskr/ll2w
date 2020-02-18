define void @foo() {
	%1 = alloca i32, align 4
	store i32 123456, i32* %1, align 4
	%2 = load i32, i32* %1, align 4
	br label %3

; <label>:3:                                      ; preds = %0, %3
	%4 = icmp eq i32 %2, 0
	br i1 %4, label %5, label %3

; <label>:5:                                      ; preds = %3
	ret void
}
