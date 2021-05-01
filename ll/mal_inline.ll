; ModuleID = 'src/mal.cpp'
source_filename = "src/mal.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.BlockMeta = type { i64, %struct.BlockMeta*, i32 }

@memory = dso_local global i32* null, align 8
@end = dso_local global i8* null, align 8
@global_base = dso_local global %struct.BlockMeta* null, align 8
@.str = private unnamed_addr constant [21 x i8] c"block_ptr->free == 0\00", align 1
@.str.1 = private unnamed_addr constant [12 x i8] c"src/mal.cpp\00", align 1
@__func__._Z2frPv = private unnamed_addr constant [3 x i8] c"fr\00", align 1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @_Z8mem_initi(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = call i32* asm "$$g -> $0", "=r,~{dirflag},~{fpsr},~{flags}"() #2, !srcloc !2
  store i32* %3, i32** @memory, align 8
  %4 = call i8* @_Z7realignPPc(i8** bitcast (i32** @memory to i8**)) #3
  %5 = load i32*, i32** @memory, align 8
  %6 = bitcast i32* %5 to i8*
  store i8* %6, i8** @end, align 8
  store %struct.BlockMeta* null, %struct.BlockMeta** @global_base, align 8
  %7 = load i32*, i32** @memory, align 8
  %8 = icmp ne i32* %7, null
  %9 = xor i1 %8, true
  %10 = xor i1 %9, true
  %11 = zext i1 %10 to i32
  ret i32 %11
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @_Z7realignPPc(i8** %0) #0 {
  %2 = alloca i8**, align 8
  store i8** %0, i8*** %2, align 8
  %3 = load i8**, i8*** %2, align 8
  %4 = load i8*, i8** %3, align 8
  %5 = ptrtoint i8* %4 to i64
  %6 = srem i64 %5, 32
  %7 = icmp ne i64 %6, 0
  br i1 %7, label %8, label %17

8:                                                ; preds = %1
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

17:                                               ; preds = %8, %1
  %18 = load i8**, i8*** %2, align 8
  %19 = load i8*, i8** %18, align 8
  ret i8* %19
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.BlockMeta* @_Z15find_free_blockPP9BlockMetam(%struct.BlockMeta** %0, i64 %1) #0 {
  %3 = alloca %struct.BlockMeta**, align 8
  %4 = alloca i64, align 8
  %5 = alloca %struct.BlockMeta*, align 8
  store %struct.BlockMeta** %0, %struct.BlockMeta*** %3, align 8
  store i64 %1, i64* %4, align 8
  %6 = load %struct.BlockMeta*, %struct.BlockMeta** @global_base, align 8
  store %struct.BlockMeta* %6, %struct.BlockMeta** %5, align 8
  br label %7

7:                                                ; preds = %26, %2
  %8 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %9 = icmp ne %struct.BlockMeta* %8, null
  br i1 %9, label %10, label %24

10:                                               ; preds = %7
  %11 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %12 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %11, i32 0, i32 2
  %13 = load i32, i32* %12, align 8
  %14 = icmp ne i32 %13, 0
  br i1 %14, label %15, label %21

15:                                               ; preds = %10
  %16 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %17 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %16, i32 0, i32 0
  %18 = load i64, i64* %17, align 8
  %19 = load i64, i64* %4, align 8
  %20 = icmp uge i64 %18, %19
  br label %21

21:                                               ; preds = %15, %10
  %22 = phi i1 [ false, %10 ], [ %20, %15 ]
  %23 = xor i1 %22, true
  br label %24

24:                                               ; preds = %21, %7
  %25 = phi i1 [ false, %7 ], [ %23, %21 ]
  br i1 %25, label %26, label %32

26:                                               ; preds = %24
  %27 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %28 = load %struct.BlockMeta**, %struct.BlockMeta*** %3, align 8
  store %struct.BlockMeta* %27, %struct.BlockMeta** %28, align 8
  %29 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %30 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %29, i32 0, i32 1
  %31 = load %struct.BlockMeta*, %struct.BlockMeta** %30, align 8
  store %struct.BlockMeta* %31, %struct.BlockMeta** %5, align 8
  br label %7

32:                                               ; preds = %24
  %33 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  ret %struct.BlockMeta* %33
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.BlockMeta* @_Z13request_spaceP9BlockMetam(%struct.BlockMeta* %0, i64 %1) #0 {
  %3 = alloca %struct.BlockMeta*, align 8
  %4 = alloca i64, align 8
  %5 = alloca %struct.BlockMeta*, align 8
  store %struct.BlockMeta* %0, %struct.BlockMeta** %3, align 8
  store i64 %1, i64* %4, align 8
  %6 = call i8* @_Z7realignPPc(i8** @end) #3
  %7 = bitcast i8* %6 to %struct.BlockMeta*
  store %struct.BlockMeta* %7, %struct.BlockMeta** %5, align 8
  %8 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %9 = icmp ne %struct.BlockMeta* %8, null
  br i1 %9, label %10, label %14

10:                                               ; preds = %2
  %11 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %12 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %13 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %12, i32 0, i32 1
  store %struct.BlockMeta* %11, %struct.BlockMeta** %13, align 8
  br label %14

14:                                               ; preds = %10, %2
  %15 = load i64, i64* %4, align 8
  %16 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %17 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %16, i32 0, i32 0
  store i64 %15, i64* %17, align 8
  %18 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %19 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %18, i32 0, i32 1
  store %struct.BlockMeta* null, %struct.BlockMeta** %19, align 8
  %20 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %21 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %20, i32 0, i32 2
  store i32 0, i32* %21, align 8
  %22 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %23 = bitcast %struct.BlockMeta* %22 to i8*
  %24 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %25 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %24, i32 0, i32 0
  %26 = load i64, i64* %25, align 8
  %27 = getelementptr inbounds i8, i8* %23, i64 %26
  %28 = getelementptr inbounds i8, i8* %27, i64 24
  %29 = getelementptr inbounds i8, i8* %28, i64 1
  store i8* %29, i8** @end, align 8
  %30 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  ret %struct.BlockMeta* %30
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i8* @_Z3malm(i64 %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i64, align 8
  %4 = alloca %struct.BlockMeta*, align 8
  %5 = alloca %struct.BlockMeta*, align 8
  %6 = alloca i64, align 8
  store i64 %0, i64* %3, align 8
  %7 = load i64, i64* %3, align 8
  %8 = icmp ule i64 %7, 0
  br i1 %8, label %9, label %10

9:                                                ; preds = %1
  store i8* null, i8** %2, align 8
  br label %50

10:                                               ; preds = %1
  %11 = load %struct.BlockMeta*, %struct.BlockMeta** @global_base, align 8
  %12 = icmp ne %struct.BlockMeta* %11, null
  br i1 %12, label %21, label %13

13:                                               ; preds = %10
  %14 = load i64, i64* %3, align 8
  %15 = call %struct.BlockMeta* @_Z13request_spaceP9BlockMetam(%struct.BlockMeta* null, i64 %14) #3
  store %struct.BlockMeta* %15, %struct.BlockMeta** %4, align 8
  %16 = load %struct.BlockMeta*, %struct.BlockMeta** %4, align 8
  %17 = icmp ne %struct.BlockMeta* %16, null
  br i1 %17, label %19, label %18

18:                                               ; preds = %13
  store i8* null, i8** %2, align 8
  br label %50

19:                                               ; preds = %13
  %20 = load %struct.BlockMeta*, %struct.BlockMeta** %4, align 8
  store %struct.BlockMeta* %20, %struct.BlockMeta** @global_base, align 8
  br label %46

21:                                               ; preds = %10
  %22 = load %struct.BlockMeta*, %struct.BlockMeta** @global_base, align 8
  store %struct.BlockMeta* %22, %struct.BlockMeta** %5, align 8
  %23 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %24 = ptrtoint %struct.BlockMeta* %23 to i64
  %25 = load i32*, i32** @memory, align 8
  %26 = ptrtoint i32* %25 to i64
  %27 = sub nsw i64 %24, %26
  store i64 %27, i64* %6, align 8
  %28 = load i64, i64* %3, align 8
  %29 = call %struct.BlockMeta* @_Z15find_free_blockPP9BlockMetam(%struct.BlockMeta** %5, i64 %28) #3
  store %struct.BlockMeta* %29, %struct.BlockMeta** %4, align 8
  %30 = load %struct.BlockMeta*, %struct.BlockMeta** %4, align 8
  %31 = icmp ne %struct.BlockMeta* %30, null
  br i1 %31, label %40, label %32

32:                                               ; preds = %21
  %33 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %34 = load i64, i64* %3, align 8
  %35 = call %struct.BlockMeta* @_Z13request_spaceP9BlockMetam(%struct.BlockMeta* %33, i64 %34) #3
  store %struct.BlockMeta* %35, %struct.BlockMeta** %4, align 8
  %36 = load %struct.BlockMeta*, %struct.BlockMeta** %4, align 8
  %37 = icmp ne %struct.BlockMeta* %36, null
  br i1 %37, label %39, label %38

38:                                               ; preds = %32
  store i8* null, i8** %2, align 8
  br label %50

39:                                               ; preds = %32
  br label %45

40:                                               ; preds = %21
  %41 = load %struct.BlockMeta*, %struct.BlockMeta** %4, align 8
  %42 = load i64, i64* %3, align 8
  call void @_Z8memsplitP9BlockMetam(%struct.BlockMeta* %41, i64 %42) #3
  %43 = load %struct.BlockMeta*, %struct.BlockMeta** %4, align 8
  %44 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %43, i32 0, i32 2
  store i32 0, i32* %44, align 8
  br label %45

45:                                               ; preds = %40, %39
  br label %46

46:                                               ; preds = %45, %19
  %47 = load %struct.BlockMeta*, %struct.BlockMeta** %4, align 8
  %48 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %47, i64 1
  %49 = bitcast %struct.BlockMeta* %48 to i8*
  store i8* %49, i8** %2, align 8
  br label %50

50:                                               ; preds = %46, %38, %18, %9
  %51 = load i8*, i8** %2, align 8
  ret i8* %51
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_Z8memsplitP9BlockMetam(%struct.BlockMeta* %0, i64 %1) #0 {
  %3 = alloca %struct.BlockMeta*, align 8
  %4 = alloca i64, align 8
  %5 = alloca %struct.BlockMeta*, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store %struct.BlockMeta* %0, %struct.BlockMeta** %3, align 8
  store i64 %1, i64* %4, align 8
  %8 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %9 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %8, i32 0, i32 0
  %10 = load i64, i64* %9, align 8
  %11 = load i64, i64* %4, align 8
  %12 = add i64 %11, 24
  %13 = icmp ugt i64 %10, %12
  br i1 %13, label %14, label %93

14:                                               ; preds = %2
  %15 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %16 = bitcast %struct.BlockMeta* %15 to i8*
  %17 = load i64, i64* %4, align 8
  %18 = getelementptr inbounds i8, i8* %16, i64 %17
  %19 = getelementptr inbounds i8, i8* %18, i64 24
  %20 = getelementptr inbounds i8, i8* %19, i64 1
  %21 = bitcast i8* %20 to %struct.BlockMeta*
  store %struct.BlockMeta* %21, %struct.BlockMeta** %5, align 8
  %22 = bitcast %struct.BlockMeta** %5 to i8**
  %23 = call i8* @_Z7realignPPc(i8** %22) #3
  %24 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %25 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %24, i32 0, i32 1
  %26 = load %struct.BlockMeta*, %struct.BlockMeta** %25, align 8
  %27 = icmp ne %struct.BlockMeta* %26, null
  br i1 %27, label %28, label %61

28:                                               ; preds = %14
  %29 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %30 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %29, i32 0, i32 1
  %31 = load %struct.BlockMeta*, %struct.BlockMeta** %30, align 8
  %32 = bitcast %struct.BlockMeta* %31 to i8*
  %33 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %34 = bitcast %struct.BlockMeta* %33 to i8*
  %35 = ptrtoint i8* %32 to i64
  %36 = ptrtoint i8* %34 to i64
  %37 = sub i64 %35, %36
  %38 = sub i64 %37, 24
  %39 = trunc i64 %38 to i32
  store i32 %39, i32* %6, align 4
  %40 = load i32, i32* %6, align 4
  %41 = icmp sgt i32 %40, 0
  br i1 %41, label %42, label %60

42:                                               ; preds = %28
  %43 = load i32, i32* %6, align 4
  %44 = sext i32 %43 to i64
  %45 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %46 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %45, i32 0, i32 0
  store i64 %44, i64* %46, align 8
  %47 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %48 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %47, i32 0, i32 1
  %49 = load %struct.BlockMeta*, %struct.BlockMeta** %48, align 8
  %50 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %51 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %50, i32 0, i32 1
  store %struct.BlockMeta* %49, %struct.BlockMeta** %51, align 8
  %52 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %53 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %52, i32 0, i32 2
  store i32 1, i32* %53, align 8
  %54 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %55 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %56 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %55, i32 0, i32 1
  store %struct.BlockMeta* %54, %struct.BlockMeta** %56, align 8
  %57 = load i64, i64* %4, align 8
  %58 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %59 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %58, i32 0, i32 0
  store i64 %57, i64* %59, align 8
  br label %60

60:                                               ; preds = %42, %28
  br label %92

61:                                               ; preds = %14
  %62 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %63 = bitcast %struct.BlockMeta* %62 to i8*
  %64 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %65 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %64, i32 0, i32 0
  %66 = load i64, i64* %65, align 8
  %67 = getelementptr inbounds i8, i8* %63, i64 %66
  %68 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %69 = bitcast %struct.BlockMeta* %68 to i8*
  %70 = ptrtoint i8* %67 to i64
  %71 = ptrtoint i8* %69 to i64
  %72 = sub i64 %70, %71
  %73 = trunc i64 %72 to i32
  store i32 %73, i32* %7, align 4
  %74 = load i32, i32* %7, align 4
  %75 = icmp sgt i32 %74, 0
  br i1 %75, label %76, label %91

76:                                               ; preds = %61
  %77 = load i32, i32* %7, align 4
  %78 = sext i32 %77 to i64
  %79 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %80 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %79, i32 0, i32 0
  store i64 %78, i64* %80, align 8
  %81 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %82 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %81, i32 0, i32 2
  store i32 1, i32* %82, align 8
  %83 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %84 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %83, i32 0, i32 1
  store %struct.BlockMeta* null, %struct.BlockMeta** %84, align 8
  %85 = load i64, i64* %4, align 8
  %86 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %87 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %86, i32 0, i32 0
  store i64 %85, i64* %87, align 8
  %88 = load %struct.BlockMeta*, %struct.BlockMeta** %5, align 8
  %89 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %90 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %89, i32 0, i32 1
  store %struct.BlockMeta* %88, %struct.BlockMeta** %90, align 8
  br label %91

91:                                               ; preds = %76, %61
  br label %92

92:                                               ; preds = %91, %60
  br label %93

93:                                               ; preds = %92, %2
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local %struct.BlockMeta* @_Z13get_block_ptrPv(i8* %0) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = bitcast i8* %3 to %struct.BlockMeta*
  %5 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %4, i64 -1
  ret %struct.BlockMeta* %5
}

; Function Attrs: noinline nounwind optnone uwtable
define dso_local void @_Z2frPv(i8* %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct.BlockMeta*, align 8
  store i8* %0, i8** %2, align 8
  %4 = load i8*, i8** %2, align 8
  %5 = icmp ne i8* %4, null
  br i1 %5, label %7, label %6

6:                                                ; preds = %1
  br label %21

7:                                                ; preds = %1
  %8 = load i8*, i8** %2, align 8
  %9 = call %struct.BlockMeta* @_Z13get_block_ptrPv(i8* %8) #3
  store %struct.BlockMeta* %9, %struct.BlockMeta** %3, align 8
  %10 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %11 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %10, i32 0, i32 2
  %12 = load i32, i32* %11, align 8
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %16, label %14

14:                                               ; preds = %7
  call void @__assert_fail(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str, i64 0, i64 0), i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.1, i64 0, i64 0), i32 108, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @__func__._Z2frPv, i64 0, i64 0)) #4
  unreachable

15:                                               ; No predecessors!
  br label %16

16:                                               ; preds = %15, %7
  %17 = phi i1 [ true, %7 ], [ false, %15 ]
  %18 = load %struct.BlockMeta*, %struct.BlockMeta** %3, align 8
  %19 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %18, i32 0, i32 2
  store i32 1, i32* %19, align 8
  %20 = call i32 @_Z12merge_blocksv() #3
  br label %21

21:                                               ; preds = %16, %6
  ret void
}

; Function Attrs: noreturn
declare dso_local void @__assert_fail(i8*, i8*, i32, i8*) #1

; Function Attrs: noinline nounwind optnone uwtable
define dso_local i32 @_Z12merge_blocksv() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.BlockMeta*, align 8
  store i32 0, i32* %1, align 4
  %3 = load %struct.BlockMeta*, %struct.BlockMeta** @global_base, align 8
  store %struct.BlockMeta* %3, %struct.BlockMeta** %2, align 8
  br label %4

4:                                                ; preds = %50, %0
  %5 = load %struct.BlockMeta*, %struct.BlockMeta** %2, align 8
  %6 = icmp ne %struct.BlockMeta* %5, null
  br i1 %6, label %7, label %12

7:                                                ; preds = %4
  %8 = load %struct.BlockMeta*, %struct.BlockMeta** %2, align 8
  %9 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %8, i32 0, i32 1
  %10 = load %struct.BlockMeta*, %struct.BlockMeta** %9, align 8
  %11 = icmp ne %struct.BlockMeta* %10, null
  br label %12

12:                                               ; preds = %7, %4
  %13 = phi i1 [ false, %4 ], [ %11, %7 ]
  br i1 %13, label %14, label %51

14:                                               ; preds = %12
  %15 = load %struct.BlockMeta*, %struct.BlockMeta** %2, align 8
  %16 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %15, i32 0, i32 2
  %17 = load i32, i32* %16, align 8
  %18 = icmp ne i32 %17, 0
  br i1 %18, label %19, label %46

19:                                               ; preds = %14
  %20 = load %struct.BlockMeta*, %struct.BlockMeta** %2, align 8
  %21 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %20, i32 0, i32 1
  %22 = load %struct.BlockMeta*, %struct.BlockMeta** %21, align 8
  %23 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %22, i32 0, i32 2
  %24 = load i32, i32* %23, align 8
  %25 = icmp ne i32 %24, 0
  br i1 %25, label %26, label %46

26:                                               ; preds = %19
  %27 = load %struct.BlockMeta*, %struct.BlockMeta** %2, align 8
  %28 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %27, i32 0, i32 1
  %29 = load %struct.BlockMeta*, %struct.BlockMeta** %28, align 8
  %30 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %29, i32 0, i32 0
  %31 = load i64, i64* %30, align 8
  %32 = add i64 24, %31
  %33 = load %struct.BlockMeta*, %struct.BlockMeta** %2, align 8
  %34 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %33, i32 0, i32 0
  %35 = load i64, i64* %34, align 8
  %36 = add i64 %35, %32
  store i64 %36, i64* %34, align 8
  %37 = load %struct.BlockMeta*, %struct.BlockMeta** %2, align 8
  %38 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %37, i32 0, i32 1
  %39 = load %struct.BlockMeta*, %struct.BlockMeta** %38, align 8
  %40 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %39, i32 0, i32 1
  %41 = load %struct.BlockMeta*, %struct.BlockMeta** %40, align 8
  %42 = load %struct.BlockMeta*, %struct.BlockMeta** %2, align 8
  %43 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %42, i32 0, i32 1
  store %struct.BlockMeta* %41, %struct.BlockMeta** %43, align 8
  %44 = load i32, i32* %1, align 4
  %45 = add nsw i32 %44, 1
  store i32 %45, i32* %1, align 4
  br label %50

46:                                               ; preds = %19, %14
  %47 = load %struct.BlockMeta*, %struct.BlockMeta** %2, align 8
  %48 = getelementptr inbounds %struct.BlockMeta, %struct.BlockMeta* %47, i32 0, i32 1
  %49 = load %struct.BlockMeta*, %struct.BlockMeta** %48, align 8
  store %struct.BlockMeta* %49, %struct.BlockMeta** %2, align 8
  br label %50

50:                                               ; preds = %46, %26
  br label %4

51:                                               ; preds = %12
  %52 = load i32, i32* %1, align 4
  ret i32 %52
}

attributes #0 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-builtins" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-builtins" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind readnone }
attributes #3 = { nobuiltin "no-builtins" }
attributes #4 = { nobuiltin noreturn "no-builtins" }

!llvm.linker.options = !{}
!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 11.0.0-2"}
!2 = !{i32 50}
