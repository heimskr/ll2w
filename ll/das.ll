define i32 @das(i32) {
	%101 = alloca i1
	br label %2

2: ; preds = %1, %7
	br i1 %101, label %3, label %11

3: ; preds = %2
	br i1 %101, label %4, label %8

4: ; preds = %3
	br label %5

5: ; preds = %4
	br label %6

6: ; preds = %5, %9
	br i1 %101, label %5, label %7

7: ; preds = %6
	br label %2

8: ; preds = %3, %10
	br label %9

9: ; preds = %8
	br i1 %101, label %6, label %10

10: ; preds = %9
	br label %8

11: ; preds = %2
	ret i32 -1
}
