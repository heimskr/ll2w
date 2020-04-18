; ModuleID = 'combined.c'
source_filename = "combined.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.block_meta = type { i64, %struct.block_meta*, i32 }

@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@memory = common global i32* null, align 8
@end = common global i8* null, align 8
@global_base = common global %struct.block_meta* null, align 8
@.str.4 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@__func__.fr = private unnamed_addr constant [3 x i8] c"fr\00", align 1
@.str.14 = private unnamed_addr constant [3 x i8] c".\0A\00", align 1
@.str.15 = private unnamed_addr constant [4 x i8] c"s.\0A\00", align 1
@.str.32 = private unnamed_addr constant [26 x i8] c"\0A\1B[35mAllocating\1B[0m \1B[1m\00", align 1
@.str.33 = private unnamed_addr constant [10 x i8] c"\1B[0m byte\00", align 1
@.str.34 = private unnamed_addr constant [3 x i8] c": \00", align 1
@.str.35 = private unnamed_addr constant [6 x i8] c"null\0A\00", align 1
@last_block = common global %struct.block_meta* null, align 8

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32* @allocate(i64, i8*) #0 {
  %3 = alloca i64, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32*, align 8
  store i64 %0, i64* %3, align 8
  store i8* %1, i8** %4, align 8
  call void @strprint(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.32, i32 0, i32 0))
  %6 = load i64, i64* %3, align 8
  %7 = trunc i64 %6 to i32
  call void @prd(i32 %7)
  call void @strprint(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.33, i32 0, i32 0))
  %8 = load i64, i64* %3, align 8
  %9 = icmp eq i64 %8, 1
  %10 = zext i1 %9 to i64
  %11 = select i1 %9, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.15, i32 0, i32 0)
  call void @strprint(i8* %11)
  %12 = load i64, i64* %3, align 8
  %13 = call i8* @mal(i64 %12)
  %14 = bitcast i8* %13 to i32*
  store i32* %14, i32** %5, align 8
  %15 = load i8*, i8** %4, align 8
  call void @strprint(i8* %15)
  call void @strprint(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.34, i32 0, i32 0))
  %16 = load i32*, i32** %5, align 8
  %17 = icmp eq i32* %16, null
  br i1 %17, label %18, label %19

; <label>:18:                                     ; preds = %2
  call void @strprint(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.35, i32 0, i32 0))
  br label %26

; <label>:19:                                     ; preds = %2
  %20 = load i32*, i32** %5, align 8
  %21 = ptrtoint i32* %20 to i64
  %22 = load i32*, i32** @memory, align 8
  %23 = ptrtoint i32* %22 to i64
  %24 = sub nsw i64 %21, %23
  %25 = trunc i64 %24 to i32
  call void @prd(i32 %25)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i32 0, i32 0))
  br label %26

; <label>:26:                                     ; preds = %19, %18
  %27 = load i32*, i32** %5, align 8
  ret i32* %27
}

; Function Attrs: noinline nounwind optnone ssp uwtable
declare void @prd(i32) #0

declare i32 @printf(i8*, ...) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
declare void @strprint(i8*) #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare i32 @mem_init(i32) #0

; Function Attrs: allocsize(0,1)
declare i8* @calloc(i64, i64) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
declare i8* @realign(i8**) #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare %struct.block_meta* @find_free_block(%struct.block_meta**, i64) #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare %struct.block_meta* @request_space(%struct.block_meta*, i64) #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare i8* @mal(i64) #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare void @memsplit(%struct.block_meta*, i64) #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare %struct.block_meta* @get_block_ptr(i8*) #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare void @fr(i8*) #0

; Function Attrs: cold noreturn
declare void @__assert_rtn(i8*, i8*, i32, i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
declare i32 @merge_blocks() #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare i32 @main(i32, i8**) #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare void @check_free(i64) #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare void @dbg() #0

; Function Attrs: noinline nounwind optnone ssp uwtable
declare void @dbg_blocks() #0

; Function Attrs: noreturn
declare void @exit(i32) #4

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { allocsize(0,1) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { cold noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="true" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { allocsize(0,1) }
attributes #6 = { cold noreturn }
attributes #7 = { noreturn }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
