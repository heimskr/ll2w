define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  %6 = alloca i32, align 4
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %7 = load i32, i32* %4, align 4
  %8 = icmp slt i32 %7, 2
  br i1 %8, label %9, label %12

; <label>:9:                                      ; preds = %2
  %10 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %11 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %10, i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str, i32 0, i32 0))
  call void @exit(i32 1) #3
  unreachable

; <label>:12:                                     ; preds = %2
  %13 = load i32, i32* %4, align 4
  %14 = sub nsw i32 %13, 1
  store i32 %14, i32* %6, align 4
  br label %15

; <label>:15:                                     ; preds = %24, %12
  %16 = load i32, i32* %6, align 4
  %17 = icmp slt i32 0, %16
  br i1 %17, label %18, label %27

; <label>:18:                                     ; preds = %15
  %19 = load i8**, i8*** %5, align 8
  %20 = load i32, i32* %6, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds i8*, i8** %19, i64 %21
  %23 = load i8*, i8** %22, align 8
  call void @reverse(i8* %23)
  br label %24

; <label>:24:                                     ; preds = %18
  %25 = load i32, i32* %6, align 4
  %26 = add nsw i32 %25, -1
  store i32 %26, i32* %6, align 4
  br label %15

; <label>:27:                                     ; preds = %15
  %28 = load i32, i32* %3, align 4
  ret i32 %28
}
