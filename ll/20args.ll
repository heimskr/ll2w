; ModuleID = '20args.c'
source_filename = "20args.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @prd(i32) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fn(i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32) #0 {
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  %24 = alloca i32, align 4
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  %27 = alloca i32, align 4
  %28 = alloca i32, align 4
  %29 = alloca i32, align 4
  %30 = alloca i32, align 4
  %31 = alloca i32, align 4
  %32 = alloca i32, align 4
  %33 = alloca i32, align 4
  %34 = alloca i32, align 4
  %35 = alloca i32, align 4
  %36 = alloca i32, align 4
  %37 = alloca i32, align 4
  %38 = alloca i32, align 4
  %39 = alloca i32, align 4
  %40 = alloca i32, align 4
  store i32 %0, i32* %21, align 4
  store i32 %1, i32* %22, align 4
  store i32 %2, i32* %23, align 4
  store i32 %3, i32* %24, align 4
  store i32 %4, i32* %25, align 4
  store i32 %5, i32* %26, align 4
  store i32 %6, i32* %27, align 4
  store i32 %7, i32* %28, align 4
  store i32 %8, i32* %29, align 4
  store i32 %9, i32* %30, align 4
  store i32 %10, i32* %31, align 4
  store i32 %11, i32* %32, align 4
  store i32 %12, i32* %33, align 4
  store i32 %13, i32* %34, align 4
  store i32 %14, i32* %35, align 4
  store i32 %15, i32* %36, align 4
  store i32 %16, i32* %37, align 4
  store i32 %17, i32* %38, align 4
  store i32 %18, i32* %39, align 4
  store i32 %19, i32* %40, align 4
  %41 = load i32, i32* %21, align 4
  %42 = mul nsw i32 %41, 20
  call void @prd(i32 %42)
  %43 = load i32, i32* %22, align 4
  %44 = mul nsw i32 %43, 19
  call void @prd(i32 %44)
  %45 = load i32, i32* %23, align 4
  %46 = mul nsw i32 %45, 18
  call void @prd(i32 %46)
  %47 = load i32, i32* %24, align 4
  %48 = mul nsw i32 %47, 17
  call void @prd(i32 %48)
  %49 = load i32, i32* %25, align 4
  %50 = mul nsw i32 %49, 16
  call void @prd(i32 %50)
  %51 = load i32, i32* %26, align 4
  %52 = mul nsw i32 %51, 15
  call void @prd(i32 %52)
  %53 = load i32, i32* %27, align 4
  %54 = mul nsw i32 %53, 14
  call void @prd(i32 %54)
  %55 = load i32, i32* %28, align 4
  %56 = mul nsw i32 %55, 13
  call void @prd(i32 %56)
  %57 = load i32, i32* %29, align 4
  %58 = mul nsw i32 %57, 12
  call void @prd(i32 %58)
  %59 = load i32, i32* %30, align 4
  %60 = mul nsw i32 %59, 11
  call void @prd(i32 %60)
  %61 = load i32, i32* %31, align 4
  %62 = mul nsw i32 %61, 10
  call void @prd(i32 %62)
  %63 = load i32, i32* %32, align 4
  %64 = mul nsw i32 %63, 9
  call void @prd(i32 %64)
  %65 = load i32, i32* %33, align 4
  %66 = mul nsw i32 %65, 8
  call void @prd(i32 %66)
  %67 = load i32, i32* %34, align 4
  %68 = mul nsw i32 %67, 7
  call void @prd(i32 %68)
  %69 = load i32, i32* %35, align 4
  %70 = mul nsw i32 %69, 6
  call void @prd(i32 %70)
  %71 = load i32, i32* %36, align 4
  %72 = mul nsw i32 %71, 5
  call void @prd(i32 %72)
  %73 = load i32, i32* %37, align 4
  %74 = mul nsw i32 %73, 4
  call void @prd(i32 %74)
  %75 = load i32, i32* %38, align 4
  %76 = mul nsw i32 %75, 3
  call void @prd(i32 %76)
  %77 = load i32, i32* %39, align 4
  %78 = mul nsw i32 %77, 2
  call void @prd(i32 %78)
  %79 = load i32, i32* %40, align 4
  call void @prd(i32 %79)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i8**, align 8
  store i32 %0, i32* %3, align 4
  store i8** %1, i8*** %4, align 8
  call void @fn(i32 10, i32 20, i32 30, i32 40, i32 50, i32 60, i32 70, i32 80, i32 90, i32 100, i32 110, i32 120, i32 130, i32 140, i32 150, i32 160, i32 170, i32 180, i32 190, i32 200)
  ret i32 0
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
