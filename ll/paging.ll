; ModuleID = 'paging.c'
source_filename = "paging.c"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

@table = dso_local global [1 x void (...)*] [void (...)* bitcast (void ()* @pagefault to void (...)*)], align 8
@.str = private unnamed_addr constant [12 x i8] c"Page fault!\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @pagefault() #0 {
  call void @strprint(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str, i64 0, i64 0))
  call void asm sideeffect ": $$e0", "~{dirflag},~{fpsr},~{flags}"() #1, !srcloc !2
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @strprint(i8* %0) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  call void asm sideeffect "                        @_strprint_loop          [$0] -> $$ma /b           : _strprint_print if $$ma : $$rt                    @_strprint_print         <prc $$ma>                $0 + 1 -> $0             : _strprint_loop", "r,~{dirflag},~{fpsr},~{flags}"(i8* %3) #1, !srcloc !3
  ret void
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }

!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 11.0.0-2"}
!2 = !{i32 139}
!3 = !{i32 190}