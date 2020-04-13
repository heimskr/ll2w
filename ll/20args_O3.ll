; ModuleID = '20args.c'
source_filename = "20args.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00", align 1

; Function Attrs: noinline nounwind ssp uwtable
define void @prd(i32) local_unnamed_addr #0 {
  %2 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str, i64 0, i64 0), i32 %0)
  ret void
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #1

; Function Attrs: nounwind ssp uwtable
define void @fn(i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32) local_unnamed_addr #2 {
  %21 = mul nsw i32 %0, 20
  tail call void @prd(i32 %21)
  %22 = mul nsw i32 %1, 19
  tail call void @prd(i32 %22)
  %23 = mul nsw i32 %2, 18
  tail call void @prd(i32 %23)
  %24 = mul nsw i32 %3, 17
  tail call void @prd(i32 %24)
  %25 = shl nsw i32 %4, 4
  tail call void @prd(i32 %25)
  %26 = mul nsw i32 %5, 15
  tail call void @prd(i32 %26)
  %27 = mul nsw i32 %6, 14
  tail call void @prd(i32 %27)
  %28 = mul nsw i32 %7, 13
  tail call void @prd(i32 %28)
  %29 = mul nsw i32 %8, 12
  tail call void @prd(i32 %29)
  %30 = mul nsw i32 %9, 11
  tail call void @prd(i32 %30)
  %31 = mul nsw i32 %10, 10
  tail call void @prd(i32 %31)
  %32 = mul nsw i32 %11, 9
  tail call void @prd(i32 %32)
  %33 = shl nsw i32 %12, 3
  tail call void @prd(i32 %33)
  %34 = mul nsw i32 %13, 7
  tail call void @prd(i32 %34)
  %35 = mul nsw i32 %14, 6
  tail call void @prd(i32 %35)
  %36 = mul nsw i32 %15, 5
  tail call void @prd(i32 %36)
  %37 = shl nsw i32 %16, 2
  tail call void @prd(i32 %37)
  %38 = mul nsw i32 %17, 3
  tail call void @prd(i32 %38)
  %39 = shl nsw i32 %18, 1
  tail call void @prd(i32 %39)
  tail call void @prd(i32 %19)
  ret void
}

; Function Attrs: nounwind ssp uwtable
define i32 @main(i32, i8** nocapture readnone) local_unnamed_addr #2 {
  tail call void @fn(i32 10, i32 20, i32 30, i32 40, i32 50, i32 60, i32 70, i32 80, i32 90, i32 100, i32 110, i32 120, i32 130, i32 140, i32 150, i32 160, i32 170, i32 180, i32 190, i32 200)
  ret i32 0
}

attributes #0 = { noinline nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
