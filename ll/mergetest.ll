define i32 @hello(i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32) {
	; Implicit entry block: %20
	%21 = and i32 %0,  %1
	%22 = and i32 %2,  %3
	%23 = and i32 %4,  %5
	%24 = and i32 %6,  %7
	%25 = and i32 %8,  %9
	%26 = and i32 %10, %11
	%27 = and i32 %12, %13
	%28 = and i32 %14, %15
	%29 = and i32 %16, %17
	%30 = and i32 %18, %19
	br label %31

; <label>:31:                                     ; preds = %20, %37
	%32 = and i32 %21, %22
	%33 = and i32 %23, %24
	%34 = and i32 %25, %26
	%35 = and i32 %27, %28
	%36 = and i32 %29, %30
	br label %37

; <label>:37:                                     ; preds = %31
	%38 = and i32 %32, %33
	%39 = and i32 %38, %34
	%40 = and i32 %39, %35
	%41 = and i32 %40, %36
	br i1 %41, label %31, label %42

; <label>:42:                                     ; preds = %37
	br label %20
	br label %31
	br label %37
	switch i32 %41, label %31 [ i32 1, label %20   i32 2, label   %31 i32 3, label %37   i32 4, label %42 ]
	ret i32 %41
}
