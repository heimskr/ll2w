define i32 @fn1(i32, i32) {
	%3 = xor i32 %0, -1     ; %3  = ~%0
	%4 = add i32 %3, %1     ; %4  = %3 + %1
	%5 = srem i32 %4, 2     ; %5  = %4 mod 2
	%13 = icmp eq i32 %5, 1 ; %13 = %5 == 0
	br i1 %13, label %6, label %7
; <label>:6: ; preds = %2
	%8 = add i32 %4, %1     ; %8  = %4 + %1
	br label %9
; <label>:7: ; preds = %2
	%10 = shl i32 %4, 2     ; %10 = %4 << 2
	br label %9
; <label>:9: ; preds = %6, %7
	%11 = phi i32 [%8, %6], [%10, %7]
	%12 = add i32 %11, %5   ; %12 = %11 + %5
	ret i32 %12
}
