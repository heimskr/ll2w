; ModuleID = 'retstruct2.c'
source_filename = "retstruct2.c"
target datalayout = "e-m:o-p:32:32-f64:32:64-v64:32:64-v128:32:128-a:0:32-n32-S32"
target triple = "armv4t-apple-macosx10.15.0"

%struct.Foo = type { i64, i64, i64, i64 }

@__const.wow.out = private unnamed_addr constant %struct.Foo { i64 10, i64 20, i64 30, i64 40 }, align 4

; Function Attrs: noinline nounwind optnone ssp
define void @wow(%struct.Foo* noalias sret) #0 {
  %2 = bitcast %struct.Foo* %0 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i32(i8* align 4 %2, i8* align 4 bitcast (%struct.Foo* @__const.wow.out to i8*), i32 32, i1 false)
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i32(i8* nocapture writeonly, i8* nocapture readonly, i32, i1) #1

; Function Attrs: noinline nounwind optnone ssp
define i32 @main(i32, i8**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i8**, align 4
  %5 = alloca %struct.Foo, align 4
  store i32 %0, i32* %3, align 4
  store i8** %1, i8*** %4, align 4
  call void @wow(%struct.Foo* sret %5)
  %6 = getelementptr inbounds %struct.Foo, %struct.Foo* %5, i32 0, i32 0
  store i64 42, i64* %6, align 4
  %7 = getelementptr inbounds %struct.Foo, %struct.Foo* %5, i32 0, i32 1
  store i64 64, i64* %7, align 4
  %8 = getelementptr inbounds %struct.Foo, %struct.Foo* %5, i32 0, i32 2
  store i64 69, i64* %8, align 4
  %9 = getelementptr inbounds %struct.Foo, %struct.Foo* %5, i32 0, i32 3
  store i64 100, i64* %9, align 4
  ret i32 0
}

attributes #0 = { noinline nounwind optnone ssp "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="arm7tdmi" "target-features"="+armv4t,+soft-float,+strict-align,-crypto,-d16,-fp-armv8,-fp-only-sp,-fp16,-neon,-thumb-mode,-vfp2,-vfp3,-vfp4" "unsafe-fp-math"="false" "use-soft-float"="true" }
attributes #1 = { argmemonly nounwind }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 1, !"min_enum_size", i32 4}
!3 = !{i32 7, !"PIC Level", i32 2}
!4 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
