; ModuleID = 'paging.cpp'
source_filename = "paging.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.P0Wrapper = type { i64* }

$_ZN9P0WrapperC2EPm = comdat any

@table = dso_local global [6 x void ()*] [void ()* null, void ()* null, void ()* null, void ()* null, void ()* @_Z9pagefaultv, void ()* null], align 16
@.str = private unnamed_addr constant [15 x i8] c"Hello, world!\0A\00", align 1
@.str.1 = private unnamed_addr constant [12 x i8] c"Page fault!\00", align 1

; Function Attrs: noinline optnone uwtable
define dso_local void @_Z9pagefaultv() #0 {
  call void @_Z8strprintPKc(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i64 0, i64 0))
  call void asm sideeffect ": $$e0", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !2
  ret void
}

; Function Attrs: naked noinline nounwind optnone uwtable
define dso_local void @_Z3prdl(i64 %0) #1 {
  call void asm sideeffect "<prd $$a0>", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !3
  unreachable
}

; Function Attrs: naked noinline nounwind optnone uwtable
define dso_local void @_Z3prcc(i8 signext %0) #1 {
  call void asm sideeffect "<prc $$a0>", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !4
  unreachable
}

; Function Attrs: noinline norecurse optnone uwtable
define dso_local i32 @main() #2 {
  %1 = alloca %struct.P0Wrapper, align 8
  call void @_Z8strprintPKc(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i64 0, i64 0))
  call void asm sideeffect "rit table", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !5
  %2 = load volatile i64, i64* inttoptr (i64 1 to i64*), align 8
  call void @_Z3prdl(i64 %2)
  call void @_Z3prcc(i8 signext 10)
  call void @_ZN9P0WrapperC2EPm(%struct.P0Wrapper* %1, i64* inttoptr (i64 65536 to i64*))
  %3 = getelementptr inbounds %struct.P0Wrapper, %struct.P0Wrapper* %1, i32 0, i32 0
  %4 = load i64*, i64** %3, align 8
  %5 = ptrtoint i64* %4 to i64
  call void @_Z3prdl(i64 %5)
  call void @_Z3prcc(i8 signext 10)
  call void asm sideeffect "page on", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !6
  %6 = load volatile i64, i64* inttoptr (i64 1 to i64*), align 8
  call void @_Z3prdl(i64 %6)
  call void @_Z3prcc(i8 signext 10)
  ret i32 0
}

; Function Attrs: naked noinline nounwind optnone uwtable
define dso_local void @_Z8strprintPKc(i8* %0) #1 {
  call void asm sideeffect "@_strprint_loop          \09     [$$a0] -> $$ma /b          \09     : _strprint_print if $$ma \09     : _strprint_done         \09     @_strprint_print         \09     <prc $$ma>                \09     $$a0 + 1 -> $$a0           \09     : _strprint_loop         \09     @_strprint_done", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !7
  unreachable
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN9P0WrapperC2EPm(%struct.P0Wrapper* %0, i64* %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %struct.P0Wrapper*, align 8
  %4 = alloca i64*, align 8
  store %struct.P0Wrapper* %0, %struct.P0Wrapper** %3, align 8
  store i64* %1, i64** %4, align 8
  %5 = load %struct.P0Wrapper*, %struct.P0Wrapper** %3, align 8
  %6 = getelementptr inbounds %struct.P0Wrapper, %struct.P0Wrapper* %5, i32 0, i32 0
  %7 = load i64*, i64** %4, align 8
  store i64* %7, i64** %6, align 8
  ret void
}

attributes #0 = { noinline optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { naked noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noinline norecurse optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.linker.options = !{}
!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 11.0.0-2"}
!2 = !{i32 648}
!3 = !{i32 267}
!4 = !{i32 331}
!5 = !{i32 396}
!6 = !{i32 541}
!7 = !{i32 722}
