; ModuleID = 'mal.c'
source_filename = "mal.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.block_meta = type { i64, %struct.block_meta*, i32 }

@memory = common global i32* null, align 8
@end = common global i8* null, align 8
@global_base = common global %struct.block_meta* null, align 8
@.str = private unnamed_addr constant [37 x i8] c"\1B[38;5;226mSetting global_base\1B[0m.\0A\00", align 1
@.str.1 = private unnamed_addr constant [7 x i8] c"~ %lu\0A\00", align 1
@.str.2 = private unnamed_addr constant [17 x i8] c"block->next: %s\0A\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"yes\00", align 1
@.str.4 = private unnamed_addr constant [3 x i8] c"no\00", align 1
@.str.5 = private unnamed_addr constant [18 x i8] c"block->size: %lu\0A\00", align 1
@.str.6 = private unnamed_addr constant [18 x i8] c"       size: %lu\0A\00", align 1
@__func__.fr = private unnamed_addr constant [3 x i8] c"fr\00", align 1
@.str.7 = private unnamed_addr constant [6 x i8] c"mal.c\00", align 1
@.str.8 = private unnamed_addr constant [21 x i8] c"block_ptr->free == 0\00", align 1
@.str.9 = private unnamed_addr constant [38 x i8] c"\0A\1B[36mMerged\1B[0m \1B[1m%d\1B[0m block%s.\0A\00", align 1
@.str.10 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.11 = private unnamed_addr constant [2 x i8] c"s\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @mem_init(i32) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = sext i32 %3 to i64
  %5 = call i8* @calloc(i64 %4, i64 4) #4
  %6 = bitcast i8* %5 to i32*
  store i32* %6, i32** @memory, align 8
  %7 = call i8* @realign(i8** bitcast (i32** @memory to i8**))
  %8 = load i32*, i32** @memory, align 8
  %9 = bitcast i32* %8 to i8*
  store i8* %9, i8** @end, align 8
  store %struct.block_meta* null, %struct.block_meta** @global_base, align 8
  %10 = load i32*, i32** @memory, align 8
  %11 = icmp ne i32* %10, null
  %12 = xor i1 %11, true
  %13 = xor i1 %12, true
  %14 = zext i1 %13 to i32
  ret i32 %14
}

; Function Attrs: allocsize(0,1)
declare i8* @calloc(i64, i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @realign(i8**) #0 {
  %2 = alloca i8**, align 8
  store i8** %0, i8*** %2, align 8
  %3 = load i8**, i8*** %2, align 8
  %4 = load i8*, i8** %3, align 8
  %5 = ptrtoint i8* %4 to i64
  %6 = srem i64 %5, 32
  %7 = icmp ne i64 %6, 0
  br i1 %7, label %8, label %17

; <label>:8:                                      ; preds = %1
  %9 = load i8**, i8*** %2, align 8
  %10 = load i8*, i8** %9, align 8
  %11 = ptrtoint i8* %10 to i64
  %12 = srem i64 %11, 32
  %13 = sub nsw i64 32, %12
  %14 = load i8**, i8*** %2, align 8
  %15 = load i8*, i8** %14, align 8
  %16 = getelementptr inbounds i8, i8* %15, i64 %13
  store i8* %16, i8** %14, align 8
  br label %17

; <label>:17:                                     ; preds = %8, %1
  %18 = load i8**, i8*** %2, align 8
  %19 = load i8*, i8** %18, align 8
  ret i8* %19
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.block_meta* @find_free_block(%struct.block_meta**, i64) #0 {
  %3 = alloca %struct.block_meta**, align 8
  %4 = alloca i64, align 8
  %5 = alloca %struct.block_meta*, align 8
  store %struct.block_meta** %0, %struct.block_meta*** %3, align 8
  store i64 %1, i64* %4, align 8
  %6 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  store %struct.block_meta* %6, %struct.block_meta** %5, align 8
  br label %7

; <label>:7:                                      ; preds = %26, %2
  %8 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %9 = icmp ne %struct.block_meta* %8, null
  br i1 %9, label %10, label %24

; <label>:10:                                     ; preds = %7
  %11 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %12 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %11, i32 0, i32 2
  %13 = load i32, i32* %12, align 8
  %14 = icmp ne i32 %13, 0
  br i1 %14, label %15, label %21

; <label>:15:                                     ; preds = %10
  %16 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %17 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %16, i32 0, i32 0
  %18 = load i64, i64* %17, align 8
  %19 = load i64, i64* %4, align 8
  %20 = icmp uge i64 %18, %19
  br label %21

; <label>:21:                                     ; preds = %15, %10
  %22 = phi i1 [ false, %10 ], [ %20, %15 ]
  %23 = xor i1 %22, true
  br label %24

; <label>:24:                                     ; preds = %21, %7
  %25 = phi i1 [ false, %7 ], [ %23, %21 ]
  br i1 %25, label %26, label %32

; <label>:26:                                     ; preds = %24
  %27 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %28 = load %struct.block_meta**, %struct.block_meta*** %3, align 8
  store %struct.block_meta* %27, %struct.block_meta** %28, align 8
  %29 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %30 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i32 0, i32 1
  %31 = load %struct.block_meta*, %struct.block_meta** %30, align 8
  store %struct.block_meta* %31, %struct.block_meta** %5, align 8
  br label %7

; <label>:32:                                     ; preds = %24
  %33 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  ret %struct.block_meta* %33
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.block_meta* @request_space(%struct.block_meta*, i64) #0 {
  %3 = alloca %struct.block_meta*, align 8
  %4 = alloca i64, align 8
  %5 = alloca %struct.block_meta*, align 8
  store %struct.block_meta* %0, %struct.block_meta** %3, align 8
  store i64 %1, i64* %4, align 8
  %6 = call i8* @realign(i8** @end)
  %7 = bitcast i8* %6 to %struct.block_meta*
  store %struct.block_meta* %7, %struct.block_meta** %5, align 8
  %8 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %9 = icmp ne %struct.block_meta* %8, null
  br i1 %9, label %10, label %14

; <label>:10:                                     ; preds = %2
  %11 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %12 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %13 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %12, i32 0, i32 1
  store %struct.block_meta* %11, %struct.block_meta** %13, align 8
  br label %14

; <label>:14:                                     ; preds = %10, %2
  %15 = load i64, i64* %4, align 8
  %16 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %17 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %16, i32 0, i32 0
  store i64 %15, i64* %17, align 8
  %18 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %19 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %18, i32 0, i32 1
  store %struct.block_meta* null, %struct.block_meta** %19, align 8
  %20 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %21 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %20, i32 0, i32 2
  store i32 0, i32* %21, align 8
  %22 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %23 = bitcast %struct.block_meta* %22 to i8*
  %24 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %25 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %24, i32 0, i32 0
  %26 = load i64, i64* %25, align 8
  %27 = getelementptr inbounds i8, i8* %23, i64 %26
  %28 = getelementptr inbounds i8, i8* %27, i64 24
  %29 = getelementptr inbounds i8, i8* %28, i64 1
  store i8* %29, i8** @end, align 8
  %30 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  ret %struct.block_meta* %30
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @mal(i64) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i64, align 8
  %4 = alloca %struct.block_meta*, align 8
  %5 = alloca %struct.block_meta*, align 8
  store i64 %0, i64* %3, align 8
  %6 = load i64, i64* %3, align 8
  %7 = icmp ule i64 %6, 0
  br i1 %7, label %8, label %9

; <label>:8:                                      ; preds = %1
  store i8* null, i8** %2, align 8
  br label %71

; <label>:9:                                      ; preds = %1
  %10 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  %11 = icmp ne %struct.block_meta* %10, null
  br i1 %11, label %21, label %12

; <label>:12:                                     ; preds = %9
  %13 = load i64, i64* %3, align 8
  %14 = call %struct.block_meta* @request_space(%struct.block_meta* null, i64 %13)
  store %struct.block_meta* %14, %struct.block_meta** %4, align 8
  %15 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %16 = icmp ne %struct.block_meta* %15, null
  br i1 %16, label %18, label %17

; <label>:17:                                     ; preds = %12
  store i8* null, i8** %2, align 8
  br label %71

; <label>:18:                                     ; preds = %12
  %19 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str, i32 0, i32 0))
  %20 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  store %struct.block_meta* %20, %struct.block_meta** @global_base, align 8
  br label %67

; <label>:21:                                     ; preds = %9
  %22 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  store %struct.block_meta* %22, %struct.block_meta** %5, align 8
  %23 = load i64, i64* %3, align 8
  %24 = call %struct.block_meta* @find_free_block(%struct.block_meta** %5, i64 %23)
  store %struct.block_meta* %24, %struct.block_meta** %4, align 8
  %25 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %26 = icmp ne %struct.block_meta* %25, null
  br i1 %26, label %48, label %27

; <label>:27:                                     ; preds = %21
  %28 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %29 = bitcast %struct.block_meta* %28 to i8*
  %30 = getelementptr inbounds i8, i8* %29, i64 24
  %31 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %32 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %31, i32 0, i32 0
  %33 = load i64, i64* %32, align 8
  %34 = getelementptr inbounds i8, i8* %30, i64 %33
  %35 = load i32*, i32** @memory, align 8
  %36 = ptrtoint i32* %35 to i64
  %37 = sub i64 0, %36
  %38 = getelementptr inbounds i8, i8* %34, i64 %37
  %39 = ptrtoint i8* %38 to i64
  %40 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i32 0, i32 0), i64 %39)
  %41 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %42 = load i64, i64* %3, align 8
  %43 = call %struct.block_meta* @request_space(%struct.block_meta* %41, i64 %42)
  store %struct.block_meta* %43, %struct.block_meta** %4, align 8
  %44 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %45 = icmp ne %struct.block_meta* %44, null
  br i1 %45, label %47, label %46

; <label>:46:                                     ; preds = %27
  store i8* null, i8** %2, align 8
  br label %71

; <label>:47:                                     ; preds = %27
  br label %66

; <label>:48:                                     ; preds = %21
  %49 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %50 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %49, i32 0, i32 1
  %51 = load %struct.block_meta*, %struct.block_meta** %50, align 8
  %52 = icmp ne %struct.block_meta* %51, null
  %53 = zext i1 %52 to i64
  %54 = select i1 %52, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i32 0, i32 0)
  %55 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2, i32 0, i32 0), i8* %54)
  %56 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %57 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %56, i32 0, i32 0
  %58 = load i64, i64* %57, align 8
  %59 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.5, i32 0, i32 0), i64 %58)
  %60 = load i64, i64* %3, align 8
  %61 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.6, i32 0, i32 0), i64 %60)
  %62 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %63 = load i64, i64* %3, align 8
  call void @memsplit(%struct.block_meta* %62, i64 %63)
  %64 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %65 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %64, i32 0, i32 2
  store i32 0, i32* %65, align 8
  br label %66

; <label>:66:                                     ; preds = %48, %47
  br label %67

; <label>:67:                                     ; preds = %66, %18
  %68 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %69 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %68, i64 1
  %70 = bitcast %struct.block_meta* %69 to i8*
  store i8* %70, i8** %2, align 8
  br label %71

; <label>:71:                                     ; preds = %67, %46, %17, %8
  %72 = load i8*, i8** %2, align 8
  ret i8* %72
}

declare i32 @printf(i8*, ...) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @memsplit(%struct.block_meta*, i64) #0 {
  %3 = alloca %struct.block_meta*, align 8
  %4 = alloca i64, align 8
  %5 = alloca %struct.block_meta*, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store %struct.block_meta* %0, %struct.block_meta** %3, align 8
  store i64 %1, i64* %4, align 8
  %8 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %9 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %8, i32 0, i32 0
  %10 = load i64, i64* %9, align 8
  %11 = load i64, i64* %4, align 8
  %12 = add i64 %11, 24
  %13 = icmp ugt i64 %10, %12
  br i1 %13, label %14, label %93

; <label>:14:                                     ; preds = %2
  %15 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %16 = bitcast %struct.block_meta* %15 to i8*
  %17 = load i64, i64* %4, align 8
  %18 = getelementptr inbounds i8, i8* %16, i64 %17
  %19 = getelementptr inbounds i8, i8* %18, i64 24
  %20 = getelementptr inbounds i8, i8* %19, i64 1
  %21 = bitcast i8* %20 to %struct.block_meta*
  store %struct.block_meta* %21, %struct.block_meta** %5, align 8
  %22 = bitcast %struct.block_meta** %5 to i8**
  %23 = call i8* @realign(i8** %22)
  %24 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %25 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %24, i32 0, i32 1
  %26 = load %struct.block_meta*, %struct.block_meta** %25, align 8
  %27 = icmp ne %struct.block_meta* %26, null
  br i1 %27, label %28, label %61

; <label>:28:                                     ; preds = %14
  %29 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %30 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i32 0, i32 1
  %31 = load %struct.block_meta*, %struct.block_meta** %30, align 8
  %32 = bitcast %struct.block_meta* %31 to i8*
  %33 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %34 = bitcast %struct.block_meta* %33 to i8*
  %35 = ptrtoint i8* %32 to i64
  %36 = ptrtoint i8* %34 to i64
  %37 = sub i64 %35, %36
  %38 = sub i64 %37, 24
  %39 = trunc i64 %38 to i32
  store i32 %39, i32* %6, align 4
  %40 = load i32, i32* %6, align 4
  %41 = icmp sgt i32 %40, 0
  br i1 %41, label %42, label %60

; <label>:42:                                     ; preds = %28
  %43 = load i32, i32* %6, align 4
  %44 = sext i32 %43 to i64
  %45 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %46 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %45, i32 0, i32 0
  store i64 %44, i64* %46, align 8
  %47 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %48 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %47, i32 0, i32 1
  %49 = load %struct.block_meta*, %struct.block_meta** %48, align 8
  %50 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %51 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %50, i32 0, i32 1
  store %struct.block_meta* %49, %struct.block_meta** %51, align 8
  %52 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %53 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %52, i32 0, i32 2
  store i32 1, i32* %53, align 8
  %54 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %55 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %56 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %55, i32 0, i32 1
  store %struct.block_meta* %54, %struct.block_meta** %56, align 8
  %57 = load i64, i64* %4, align 8
  %58 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %59 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %58, i32 0, i32 0
  store i64 %57, i64* %59, align 8
  br label %60

; <label>:60:                                     ; preds = %42, %28
  br label %92

; <label>:61:                                     ; preds = %14
  %62 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %63 = bitcast %struct.block_meta* %62 to i8*
  %64 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %65 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %64, i32 0, i32 0
  %66 = load i64, i64* %65, align 8
  %67 = getelementptr inbounds i8, i8* %63, i64 %66
  %68 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %69 = bitcast %struct.block_meta* %68 to i8*
  %70 = ptrtoint i8* %67 to i64
  %71 = ptrtoint i8* %69 to i64
  %72 = sub i64 %70, %71
  %73 = trunc i64 %72 to i32
  store i32 %73, i32* %7, align 4
  %74 = load i32, i32* %7, align 4
  %75 = icmp sgt i32 %74, 0
  br i1 %75, label %76, label %91

; <label>:76:                                     ; preds = %61
  %77 = load i32, i32* %7, align 4
  %78 = sext i32 %77 to i64
  %79 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %80 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %79, i32 0, i32 0
  store i64 %78, i64* %80, align 8
  %81 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %82 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %81, i32 0, i32 2
  store i32 1, i32* %82, align 8
  %83 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %84 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %83, i32 0, i32 1
  store %struct.block_meta* null, %struct.block_meta** %84, align 8
  %85 = load i64, i64* %4, align 8
  %86 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %87 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %86, i32 0, i32 0
  store i64 %85, i64* %87, align 8
  %88 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %89 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %90 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %89, i32 0, i32 1
  store %struct.block_meta* %88, %struct.block_meta** %90, align 8
  br label %91

; <label>:91:                                     ; preds = %76, %61
  br label %92

; <label>:92:                                     ; preds = %91, %60
  br label %93

; <label>:93:                                     ; preds = %92, %2
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.block_meta* @get_block_ptr(i8*) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = bitcast i8* %3 to %struct.block_meta*
  %5 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %4, i64 -1
  ret %struct.block_meta* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fr(i8*) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct.block_meta*, align 8
  store i8* %0, i8** %2, align 8
  %4 = load i8*, i8** %2, align 8
  %5 = icmp ne i8* %4, null
  br i1 %5, label %7, label %6

; <label>:6:                                      ; preds = %1
  br label %25

; <label>:7:                                      ; preds = %1
  %8 = load i8*, i8** %2, align 8
  %9 = call %struct.block_meta* @get_block_ptr(i8* %8)
  store %struct.block_meta* %9, %struct.block_meta** %3, align 8
  %10 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %11 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %10, i32 0, i32 2
  %12 = load i32, i32* %11, align 8
  %13 = icmp eq i32 %12, 0
  %14 = xor i1 %13, true
  %15 = zext i1 %14 to i32
  %16 = sext i32 %15 to i64
  %17 = icmp ne i64 %16, 0
  br i1 %17, label %18, label %20

; <label>:18:                                     ; preds = %7
  call void @__assert_rtn(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @__func__.fr, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.7, i32 0, i32 0), i32 125, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.8, i32 0, i32 0)) #5
  unreachable
                                                  ; No predecessors!
  br label %21

; <label>:20:                                     ; preds = %7
  br label %21

; <label>:21:                                     ; preds = %20, %19
  %22 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %23 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %22, i32 0, i32 2
  store i32 1, i32* %23, align 8
  %24 = call i32 @merge_blocks()
  br label %25

; <label>:25:                                     ; preds = %21, %6
  ret void
}

; Function Attrs: cold noreturn
declare void @__assert_rtn(i8*, i8*, i32, i8*) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @merge_blocks() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.block_meta*, align 8
  store i32 0, i32* %1, align 4
  %3 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  store %struct.block_meta* %3, %struct.block_meta** %2, align 8
  br label %4

; <label>:4:                                      ; preds = %50, %0
  %5 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %6 = icmp ne %struct.block_meta* %5, null
  br i1 %6, label %7, label %12

; <label>:7:                                      ; preds = %4
  %8 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %9 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %8, i32 0, i32 1
  %10 = load %struct.block_meta*, %struct.block_meta** %9, align 8
  %11 = icmp ne %struct.block_meta* %10, null
  br label %12

; <label>:12:                                     ; preds = %7, %4
  %13 = phi i1 [ false, %4 ], [ %11, %7 ]
  br i1 %13, label %14, label %51

; <label>:14:                                     ; preds = %12
  %15 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %16 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %15, i32 0, i32 2
  %17 = load i32, i32* %16, align 8
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %19, label %46

; <label>:19:                                     ; preds = %14
  %20 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %21 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %20, i32 0, i32 1
  %22 = load %struct.block_meta*, %struct.block_meta** %21, align 8
  %23 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %22, i32 0, i32 2
  %24 = load i32, i32* %23, align 8
  %25 = icmp ne i32 %24, 0
  br i1 %25, label %26, label %46

; <label>:26:                                     ; preds = %19
  %27 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %28 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %27, i32 0, i32 1
  %29 = load %struct.block_meta*, %struct.block_meta** %28, align 8
  %30 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i32 0, i32 0
  %31 = load i64, i64* %30, align 8
  %32 = add i64 24, %31
  %33 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %34 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %33, i32 0, i32 0
  %35 = load i64, i64* %34, align 8
  %36 = add i64 %35, %32
  store i64 %36, i64* %34, align 8
  %37 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %38 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %37, i32 0, i32 1
  %39 = load %struct.block_meta*, %struct.block_meta** %38, align 8
  %40 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %39, i32 0, i32 1
  %41 = load %struct.block_meta*, %struct.block_meta** %40, align 8
  %42 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %43 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %42, i32 0, i32 1
  store %struct.block_meta* %41, %struct.block_meta** %43, align 8
  %44 = load i32, i32* %1, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, i32* %1, align 4
  br label %50

; <label>:46:                                     ; preds = %19, %14
  %47 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %48 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %47, i32 0, i32 1
  %49 = load %struct.block_meta*, %struct.block_meta** %48, align 8
  store %struct.block_meta* %49, %struct.block_meta** %2, align 8
  br label %50

; <label>:50:                                     ; preds = %46, %26
  br label %4

; <label>:51:                                     ; preds = %12
  %52 = load i32, i32* %1, align 4
  %53 = icmp sgt i32 %52, 0
  br i1 %53, label %54, label %61

; <label>:54:                                     ; preds = %51
  %55 = load i32, i32* %1, align 4
  %56 = load i32, i32* %1, align 4
  %57 = icmp eq i32 %56, 1
  %58 = zext i1 %57 to i64
  %59 = select i1 %57, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i32 0, i32 0)
  %60 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.9, i32 0, i32 0), i32 %55, i8* %59)
  br label %61

; <label>:61:                                     ; preds = %54, %51
  %62 = load i32, i32* %1, align 4
  ret i32 %62
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { allocsize(0,1) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { cold noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="true" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { allocsize(0,1) }
attributes #5 = { cold noreturn }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
