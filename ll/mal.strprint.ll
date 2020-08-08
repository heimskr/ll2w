; ModuleID = 'combined.strprint.c'
source_filename = "combined.strprint.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.block_meta = type { i64, %struct.block_meta*, i32 }

@.str = private unnamed_addr constant [22 x i8] c"Initializing memory.\0A\00", align 1
@.str.1 = private unnamed_addr constant [22 x i8] c"sizeof(block_meta) = \00", align 1
@.str.2 = private unnamed_addr constant [19 x i8] c"Start (absolute): \00", align 1
@memory = common global i32* null, align 8
@.str.3 = private unnamed_addr constant [5 x i8] c"Ptr1\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"Ptr2\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"Ptr3\00", align 1
@.str.6 = private unnamed_addr constant [5 x i8] c"Ptr4\00", align 1
@.str.7 = private unnamed_addr constant [5 x i8] c"Ptr5\00", align 1
@.str.8 = private unnamed_addr constant [31 x i8] c"\0AFreeing 200 and 10 pointers.\0A\00", align 1
@.str.9 = private unnamed_addr constant [32 x i8] c"\0AFreeing 100 and 800 pointers.\0A\00", align 1
@.str.10 = private unnamed_addr constant [5 x i8] c"Ptr6\00", align 1
@.str.11 = private unnamed_addr constant [5 x i8] c"Ptr7\00", align 1
@.str.12 = private unnamed_addr constant [33 x i8] c"\0AFreeing 600 and 1000 pointers.\0A\00", align 1
@.str.13 = private unnamed_addr constant [5 x i8] c"Ptr8\00", align 1
@.str.14 = private unnamed_addr constant [5 x i8] c"Ptr9\00", align 1
@.str.15 = private unnamed_addr constant [6 x i8] c"Ptr10\00", align 1
@.str.16 = private unnamed_addr constant [26 x i8] c"\0A\1B[35mAllocating\1B[0m \1B[1m\00", align 1
@.str.17 = private unnamed_addr constant [10 x i8] c"\1B[0m byte\00", align 1
@.str.18 = private unnamed_addr constant [3 x i8] c".\0A\00", align 1
@.str.19 = private unnamed_addr constant [4 x i8] c"s.\0A\00", align 1
@.str.20 = private unnamed_addr constant [9 x i8] c" set to \00", align 1
@.str.21 = private unnamed_addr constant [7 x i8] c"null.\0A\00", align 1
@.str.22 = private unnamed_addr constant [8 x i8] c"\0AEnd:  \00", align 1
@end = common global i8* null, align 8
@.str.23 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@global_base = common global %struct.block_meta* null, align 8
@.str.24 = private unnamed_addr constant [12 x i8] c"Base: null\0A\00", align 1
@.str.25 = private unnamed_addr constant [7 x i8] c"Base: \00", align 1
@last_block = common global %struct.block_meta* null, align 8
@.str.26 = private unnamed_addr constant [15 x i8] c"Free block >= \00", align 1
@.str.27 = private unnamed_addr constant [8 x i8] c" byte: \00", align 1
@.str.28 = private unnamed_addr constant [9 x i8] c" bytes: \00", align 1
@.str.29 = private unnamed_addr constant [6 x i8] c"null\0A\00", align 1
@.str.30 = private unnamed_addr constant [28 x i8] c"\0A\1B[34mChecking blocks\1B[0m.\0A\00", align 1
@.str.31 = private unnamed_addr constant [12 x i8] c"    Found a\00", align 1
@.str.32 = private unnamed_addr constant [11 x i8] c" \1B[32mfree\00", align 1
@.str.33 = private unnamed_addr constant [17 x i8] c"n \1B[31mallocated\00", align 1
@.str.34 = private unnamed_addr constant [20 x i8] c"\1B[0m block of size \00", align 1
@.str.35 = private unnamed_addr constant [15 x i8] c" at position [\00", align 1
@.str.36 = private unnamed_addr constant [3 x i8] c", \00", align 1
@.str.37 = private unnamed_addr constant [11 x i8] c"]. next = \00", align 1
@.str.38 = private unnamed_addr constant [21 x i8] c"Loop took too long!\0A\00", align 1
@.str.39 = private unnamed_addr constant [11 x i8] c"Found \1B[1m\00", align 1
@.str.40 = private unnamed_addr constant [11 x i8] c"\1B[0m block\00", align 1
@.str.41 = private unnamed_addr constant [4 x i8] c"%lu\00", align 1
@.str.42 = private unnamed_addr constant [3 x i8] c"%s\00", align 1
@.str.43 = private unnamed_addr constant [12 x i8] c"Realigning \00", align 1
@.str.44 = private unnamed_addr constant [5 x i8] c" to \00", align 1
@.str.45 = private unnamed_addr constant [11 x i8] c"FFB: last[\00", align 1
@.str.46 = private unnamed_addr constant [3 x i8] c":s\00", align 1
@.str.47 = private unnamed_addr constant [17 x i8] c"] (size param = \00", align 1
@.str.48 = private unnamed_addr constant [6 x i8] c") -> \00", align 1
@.str.49 = private unnamed_addr constant [21 x i8] c"\1B[38;5;202m[3] last{\00", align 1
@.str.50 = private unnamed_addr constant [10 x i8] c"}->next: \00", align 1
@.str.51 = private unnamed_addr constant [6 x i8] c"\1B[0m\0A\00", align 1
@.str.52 = private unnamed_addr constant [39 x i8] c"\1B[38;5;226mSetting global_base\1B[0m to \00", align 1
@.str.53 = private unnamed_addr constant [12 x i8] c"\1B[32mlast: \00", align 1
@.str.54 = private unnamed_addr constant [3 x i8] c"~ \00", align 1
@.str.55 = private unnamed_addr constant [26 x i8] c"block was null; now it's \00", align 1
@.str.56 = private unnamed_addr constant [13 x i8] c"still null.\0A\00", align 1
@.str.57 = private unnamed_addr constant [8 x i8] c"block: \00", align 1
@.str.58 = private unnamed_addr constant [15 x i8] c"\0Ablock->next: \00", align 1
@.str.59 = private unnamed_addr constant [5 x i8] c"yes\0A\00", align 1
@.str.60 = private unnamed_addr constant [4 x i8] c"no\0A\00", align 1
@.str.61 = private unnamed_addr constant [14 x i8] c"block->size: \00", align 1
@.str.62 = private unnamed_addr constant [15 x i8] c"\0A       size: \00", align 1
@.str.63 = private unnamed_addr constant [22 x i8] c"\0AMemsplitting block.\0A\00", align 1
@.str.64 = private unnamed_addr constant [18 x i8] c"[1] block->next: \00", align 1
@.str.65 = private unnamed_addr constant [18 x i8] c"    block->size: \00", align 1
@.str.66 = private unnamed_addr constant [18 x i8] c"[2] block->next: \00", align 1
@.str.67 = private unnamed_addr constant [23 x i8] c"\1B[32mfree\1B[39;2m(\1B[22m\00", align 1
@.str.68 = private unnamed_addr constant [12 x i8] c"\1B[2m)\1B[22m\0A\00", align 1
@.str.69 = private unnamed_addr constant [24 x i8] c"    block_ptr->free == \00", align 1
@.str.70 = private unnamed_addr constant [3 x i8] c"\0A\0A\00", align 1
@__func__.fr = private unnamed_addr constant [3 x i8] c"fr\00", align 1
@.str.71 = private unnamed_addr constant [20 x i8] c"combined.strprint.c\00", align 1
@.str.72 = private unnamed_addr constant [21 x i8] c"block_ptr->free == 0\00", align 1
@.str.73 = private unnamed_addr constant [42 x i8] c"\0A\1B[38;5;202mmerge_blocks\1B[39m: current = \00", align 1
@.str.74 = private unnamed_addr constant [4 x i8] c" - \00", align 1
@.str.75 = private unnamed_addr constant [4 x i8] c" = \00", align 1
@.str.76 = private unnamed_addr constant [42 x i8] c"    current->free && current->next->free\0A\00", align 1
@.str.77 = private unnamed_addr constant [20 x i8] c"    current->size {\00", align 1
@.str.78 = private unnamed_addr constant [6 x i8] c"} += \00", align 1
@.str.79 = private unnamed_addr constant [4 x i8] c" + \00", align 1
@.str.80 = private unnamed_addr constant [20 x i8] c"    current->next {\00", align 1
@.str.81 = private unnamed_addr constant [26 x i8] c"} = current->next->next {\00", align 1
@.str.82 = private unnamed_addr constant [3 x i8] c"}\0A\00", align 1
@.str.83 = private unnamed_addr constant [44 x i8] c"    !current->free || !current->next->free\0A\00", align 1
@.str.84 = private unnamed_addr constant [22 x i8] c"\0A\1B[36mMerged\1B[0m \1B[1m\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main(i32 %0, i8** %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i8**, align 8
  %5 = alloca i32*, align 8
  %6 = alloca i32*, align 8
  %7 = alloca i32*, align 8
  %8 = alloca i32*, align 8
  %9 = alloca i32*, align 8
  %10 = alloca i32*, align 8
  %11 = alloca i32*, align 8
  store i32 %0, i32* %3, align 4
  store i8** %1, i8*** %4, align 8
  call void @strprint(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str, i64 0, i64 0))
  call void @strprint(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.1, i64 0, i64 0))
  call void @prd(i64 24)
  call void @prc(i8 signext 10)
  %12 = call i32 @mem_init(i32 1048576)
  call void @strprint(i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.2, i64 0, i64 0))
  %13 = load i32*, i32** @memory, align 8
  %14 = ptrtoint i32* %13 to i64
  call void @prd(i64 %14)
  call void @prc(i8 signext 10)
  call void @check_free(i64 0)
  call void @dbg()
  %15 = call i32* @allocate(i64 20, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0))
  store i32* %15, i32** %5, align 8
  call void @dbg()
  call void @check_free(i64 100)
  call void @dbg_blocks()
  %16 = call i32* @allocate(i64 150, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i64 0, i64 0))
  store i32* %16, i32** %6, align 8
  %17 = call i32* @allocate(i64 10, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i64 0, i64 0))
  store i32* %17, i32** %7, align 8
  call void @dbg_blocks()
  %18 = load i32*, i32** %6, align 8
  %19 = bitcast i32* %18 to i8*
  call void @fr(i8* %19)
  call void @dbg_blocks()
  call void @prc(i8 signext 10)
  call void @check_free(i64 5)
  call void @check_free(i64 100)
  call void @check_free(i64 200)
  call void @check_free(i64 601)
  call void @dbg()
  %20 = call i32* @allocate(i64 200, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.6, i64 0, i64 0))
  store i32* %20, i32** %8, align 8
  call void @dbg()
  call void @dbg_blocks()
  %21 = call i32* @allocate(i64 100, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i64 0, i64 0))
  store i32* %21, i32** %9, align 8
  call void @dbg_blocks()
  call void @strprint(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.8, i64 0, i64 0))
  %22 = load i32*, i32** %8, align 8
  %23 = bitcast i32* %22 to i8*
  call void @fr(i8* %23)
  %24 = load i32*, i32** %7, align 8
  %25 = bitcast i32* %24 to i8*
  call void @fr(i8* %25)
  call void @dbg_blocks()
  %26 = call i32 @merge_blocks()
  call void @dbg_blocks()
  call void @strprint(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.9, i64 0, i64 0))
  %27 = load i32*, i32** %9, align 8
  %28 = bitcast i32* %27 to i8*
  call void @fr(i8* %28)
  %29 = load i32*, i32** %5, align 8
  %30 = bitcast i32* %29 to i8*
  call void @fr(i8* %30)
  call void @dbg_blocks()
  %31 = call i32 @merge_blocks()
  call void @dbg_blocks()
  %32 = call i32* @allocate(i64 600, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.10, i64 0, i64 0))
  store i32* %32, i32** %10, align 8
  call void @dbg_blocks()
  %33 = call i32* @allocate(i64 1000, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.11, i64 0, i64 0))
  store i32* %33, i32** %11, align 8
  call void @dbg_blocks()
  call void @strprint(i8* getelementptr inbounds ([33 x i8], [33 x i8]* @.str.12, i64 0, i64 0))
  %34 = load i32*, i32** %10, align 8
  %35 = bitcast i32* %34 to i8*
  call void @fr(i8* %35)
  %36 = load i32*, i32** %11, align 8
  %37 = bitcast i32* %36 to i8*
  call void @fr(i8* %37)
  call void @dbg_blocks()
  %38 = call i32* @allocate(i64 300, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.13, i64 0, i64 0))
  call void @dbg_blocks()
  %39 = call i32* @allocate(i64 233, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.14, i64 0, i64 0))
  call void @dbg_blocks()
  %40 = call i32 @merge_blocks()
  call void @dbg_blocks()
  %41 = call i32* @allocate(i64 600, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.15, i64 0, i64 0))
  call void @dbg_blocks()
  ret i32 0
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @strprint(i8* %0) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.42, i64 0, i64 0), i8* %3)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @prd(i64 %0) #0 {
  %2 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  %3 = load i64, i64* %2, align 8
  %4 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.41, i64 0, i64 0), i64 %3)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @prc(i8 signext %0) #0 {
  %2 = alloca i8, align 1
  store i8 %0, i8* %2, align 1
  %3 = load i8, i8* %2, align 1
  %4 = sext i8 %3 to i32
  %5 = call i32 @putchar(i32 %4)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @mem_init(i32 %0) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %3 = load i32, i32* %2, align 4
  %4 = sext i32 %3 to i64
  %5 = call i8* @calloc(i64 %4, i64 4) #5
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

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @check_free(i64 %0) #0 {
  %2 = alloca i64, align 8
  %3 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  %4 = load i64, i64* %2, align 8
  %5 = call %struct.block_meta* @find_free_block(%struct.block_meta** @last_block, i64 %4)
  %6 = ptrtoint %struct.block_meta* %5 to i64
  store i64 %6, i64* %3, align 8
  call void @strprint(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.26, i64 0, i64 0))
  %7 = load i64, i64* %2, align 8
  call void @prd(i64 %7)
  %8 = load i64, i64* %2, align 8
  %9 = icmp eq i64 %8, 1
  %10 = zext i1 %9 to i64
  %11 = select i1 %9, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.27, i64 0, i64 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.28, i64 0, i64 0)
  call void @strprint(i8* %11)
  %12 = load i64, i64* %3, align 8
  %13 = icmp ne i64 %12, 0
  br i1 %13, label %14, label %19

14:                                               ; preds = %1
  %15 = load i64, i64* %3, align 8
  %16 = load i32*, i32** @memory, align 8
  %17 = ptrtoint i32* %16 to i64
  %18 = sub nsw i64 %15, %17
  call void @prd(i64 %18)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i64 0, i64 0))
  br label %20

19:                                               ; preds = %1
  call void @strprint(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.29, i64 0, i64 0))
  br label %20

20:                                               ; preds = %19, %14
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32* @allocate(i64 %0, i8* %1) #0 {
  %3 = alloca i64, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32*, align 8
  store i64 %0, i64* %3, align 8
  store i8* %1, i8** %4, align 8
  call void @strprint(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.16, i64 0, i64 0))
  %6 = load i64, i64* %3, align 8
  call void @prd(i64 %6)
  call void @strprint(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.17, i64 0, i64 0))
  %7 = load i64, i64* %3, align 8
  %8 = icmp eq i64 %7, 1
  %9 = zext i1 %8 to i64
  %10 = select i1 %8, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.18, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.19, i64 0, i64 0)
  call void @strprint(i8* %10)
  %11 = load i64, i64* %3, align 8
  %12 = call i8* @mal(i64 %11)
  %13 = bitcast i8* %12 to i32*
  store i32* %13, i32** %5, align 8
  %14 = load i8*, i8** %4, align 8
  call void @strprint(i8* %14)
  call void @strprint(i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.20, i64 0, i64 0))
  %15 = load i32*, i32** %5, align 8
  %16 = icmp eq i32* %15, null
  br i1 %16, label %17, label %18

17:                                               ; preds = %2
  call void @strprint(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.21, i64 0, i64 0))
  br label %24

18:                                               ; preds = %2
  %19 = load i32*, i32** %5, align 8
  %20 = ptrtoint i32* %19 to i64
  %21 = load i32*, i32** @memory, align 8
  %22 = ptrtoint i32* %21 to i64
  %23 = sub nsw i64 %20, %22
  call void @prd(i64 %23)
  call void @strprint(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.18, i64 0, i64 0))
  br label %24

24:                                               ; preds = %18, %17
  %25 = load i32*, i32** %5, align 8
  ret i32* %25
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fr(i8* %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca %struct.block_meta*, align 8
  store i8* %0, i8** %2, align 8
  %4 = load i8*, i8** %2, align 8
  %5 = icmp ne i8* %4, null
  br i1 %5, label %7, label %6

6:                                                ; preds = %1
  br label %34

7:                                                ; preds = %1
  call void @strprint(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.67, i64 0, i64 0))
  %8 = load i8*, i8** %2, align 8
  %9 = ptrtoint i8* %8 to i64
  %10 = load i32*, i32** @memory, align 8
  %11 = ptrtoint i32* %10 to i64
  %12 = sub nsw i64 %9, %11
  call void @prd(i64 %12)
  call void @strprint(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.68, i64 0, i64 0))
  %13 = load i8*, i8** %2, align 8
  %14 = call %struct.block_meta* @get_block_ptr(i8* %13)
  store %struct.block_meta* %14, %struct.block_meta** %3, align 8
  call void @strprint(i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.69, i64 0, i64 0))
  %15 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %16 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %15, i32 0, i32 2
  %17 = load i32, i32* %16, align 8
  %18 = sext i32 %17 to i64
  call void @prd(i64 %18)
  call void @strprint(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.70, i64 0, i64 0))
  %19 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %20 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %19, i32 0, i32 2
  %21 = load i32, i32* %20, align 8
  %22 = icmp eq i32 %21, 0
  %23 = xor i1 %22, true
  %24 = zext i1 %23 to i32
  %25 = sext i32 %24 to i64
  %26 = icmp ne i64 %25, 0
  br i1 %26, label %27, label %29

27:                                               ; preds = %7
  call void @__assert_rtn(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @__func__.fr, i64 0, i64 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.71, i64 0, i64 0), i32 336, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.72, i64 0, i64 0)) #6
  unreachable

28:                                               ; No predecessors!
  br label %30

29:                                               ; preds = %7
  br label %30

30:                                               ; preds = %29, %28
  %31 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %32 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %31, i32 0, i32 2
  store i32 1, i32* %32, align 8
  %33 = call i32 @merge_blocks()
  br label %34

34:                                               ; preds = %30, %6
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @mal(i64 %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i64, align 8
  %4 = alloca %struct.block_meta*, align 8
  %5 = alloca %struct.block_meta*, align 8
  %6 = alloca i64, align 8
  store i64 %0, i64* %3, align 8
  %7 = load i64, i64* %3, align 8
  %8 = icmp ule i64 %7, 0
  br i1 %8, label %9, label %10

9:                                                ; preds = %1
  store i8* null, i8** %2, align 8
  br label %90

10:                                               ; preds = %1
  %11 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  %12 = icmp ne %struct.block_meta* %11, null
  br i1 %12, label %23, label %13

13:                                               ; preds = %10
  %14 = load i64, i64* %3, align 8
  %15 = call %struct.block_meta* @request_space(%struct.block_meta* null, i64 %14)
  store %struct.block_meta* %15, %struct.block_meta** %4, align 8
  %16 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %17 = icmp ne %struct.block_meta* %16, null
  br i1 %17, label %19, label %18

18:                                               ; preds = %13
  store i8* null, i8** %2, align 8
  br label %90

19:                                               ; preds = %13
  call void @strprint(i8* getelementptr inbounds ([39 x i8], [39 x i8]* @.str.52, i64 0, i64 0))
  %20 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %21 = ptrtoint %struct.block_meta* %20 to i64
  call void @prd(i64 %21)
  call void @strprint(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.18, i64 0, i64 0))
  %22 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  store %struct.block_meta* %22, %struct.block_meta** @global_base, align 8
  br label %86

23:                                               ; preds = %10
  %24 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  store %struct.block_meta* %24, %struct.block_meta** %5, align 8
  %25 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %26 = ptrtoint %struct.block_meta* %25 to i64
  %27 = load i32*, i32** @memory, align 8
  %28 = ptrtoint i32* %27 to i64
  %29 = sub nsw i64 %26, %28
  store i64 %29, i64* %6, align 8
  %30 = load i64, i64* %3, align 8
  %31 = call %struct.block_meta* @find_free_block(%struct.block_meta** %5, i64 %30)
  store %struct.block_meta* %31, %struct.block_meta** %4, align 8
  call void @strprint(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.53, i64 0, i64 0))
  %32 = load i64, i64* %6, align 8
  call void @prd(i64 %32)
  call void @strprint(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.44, i64 0, i64 0))
  %33 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %34 = ptrtoint %struct.block_meta* %33 to i64
  %35 = load i32*, i32** @memory, align 8
  %36 = ptrtoint i32* %35 to i64
  %37 = sub nsw i64 %34, %36
  call void @prd(i64 %37)
  call void @strprint(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.51, i64 0, i64 0))
  %38 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %39 = icmp ne %struct.block_meta* %38, null
  br i1 %39, label %65, label %40

40:                                               ; preds = %23
  call void @strprint(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.54, i64 0, i64 0))
  %41 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %42 = bitcast %struct.block_meta* %41 to i8*
  %43 = getelementptr inbounds i8, i8* %42, i64 24
  %44 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %45 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %44, i32 0, i32 0
  %46 = load i64, i64* %45, align 8
  %47 = getelementptr inbounds i8, i8* %43, i64 %46
  %48 = load i32*, i32** @memory, align 8
  %49 = ptrtoint i32* %48 to i64
  %50 = sub i64 0, %49
  %51 = getelementptr inbounds i8, i8* %47, i64 %50
  %52 = ptrtoint i8* %51 to i64
  call void @prd(i64 %52)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i64 0, i64 0))
  %53 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %54 = load i64, i64* %3, align 8
  %55 = call %struct.block_meta* @request_space(%struct.block_meta* %53, i64 %54)
  store %struct.block_meta* %55, %struct.block_meta** %4, align 8
  call void @strprint(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.55, i64 0, i64 0))
  %56 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %57 = icmp ne %struct.block_meta* %56, null
  br i1 %57, label %59, label %58

58:                                               ; preds = %40
  call void @strprint(i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.56, i64 0, i64 0))
  store i8* null, i8** %2, align 8
  br label %90

59:                                               ; preds = %40
  %60 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %61 = ptrtoint %struct.block_meta* %60 to i64
  %62 = load i32*, i32** @memory, align 8
  %63 = ptrtoint i32* %62 to i64
  %64 = sub nsw i64 %61, %63
  call void @prd(i64 %64)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i64 0, i64 0))
  br label %85

65:                                               ; preds = %23
  call void @strprint(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.57, i64 0, i64 0))
  %66 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %67 = ptrtoint %struct.block_meta* %66 to i64
  %68 = load i32*, i32** @memory, align 8
  %69 = ptrtoint i32* %68 to i64
  %70 = sub nsw i64 %67, %69
  call void @prd(i64 %70)
  call void @strprint(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.58, i64 0, i64 0))
  %71 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %72 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %71, i32 0, i32 1
  %73 = load %struct.block_meta*, %struct.block_meta** %72, align 8
  %74 = icmp ne %struct.block_meta* %73, null
  %75 = zext i1 %74 to i64
  %76 = select i1 %74, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.59, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.60, i64 0, i64 0)
  call void @strprint(i8* %76)
  call void @strprint(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.61, i64 0, i64 0))
  %77 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %78 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %77, i32 0, i32 0
  %79 = load i64, i64* %78, align 8
  call void @prd(i64 %79)
  call void @strprint(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.62, i64 0, i64 0))
  %80 = load i64, i64* %3, align 8
  call void @prd(i64 %80)
  call void @strprint(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.63, i64 0, i64 0))
  %81 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %82 = load i64, i64* %3, align 8
  call void @memsplit(%struct.block_meta* %81, i64 %82)
  %83 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %84 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %83, i32 0, i32 2
  store i32 0, i32* %84, align 8
  br label %85

85:                                               ; preds = %65, %59
  br label %86

86:                                               ; preds = %85, %19
  %87 = load %struct.block_meta*, %struct.block_meta** %4, align 8
  %88 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %87, i64 1
  %89 = bitcast %struct.block_meta* %88 to i8*
  store i8* %89, i8** %2, align 8
  br label %90

90:                                               ; preds = %86, %58, %18, %9
  %91 = load i8*, i8** %2, align 8
  ret i8* %91
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @dbg() #0 {
  call void @strprint(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.22, i64 0, i64 0))
  %1 = load i8*, i8** @end, align 8
  %2 = ptrtoint i8* %1 to i64
  %3 = load i32*, i32** @memory, align 8
  %4 = ptrtoint i32* %3 to i64
  %5 = sub nsw i64 %2, %4
  call void @prd(i64 %5)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i64 0, i64 0))
  %6 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  %7 = icmp eq %struct.block_meta* %6, null
  br i1 %7, label %8, label %9

8:                                                ; preds = %0
  call void @strprint(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.24, i64 0, i64 0))
  br label %17

9:                                                ; preds = %0
  call void @strprint(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.25, i64 0, i64 0))
  %10 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  %11 = bitcast %struct.block_meta* %10 to i8*
  %12 = load i32*, i32** @memory, align 8
  %13 = bitcast i32* %12 to i8*
  %14 = ptrtoint i8* %11 to i64
  %15 = ptrtoint i8* %13 to i64
  %16 = sub i64 %14, %15
  call void @prd(i64 %16)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i64 0, i64 0))
  br label %17

17:                                               ; preds = %9, %8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.block_meta* @find_free_block(%struct.block_meta** %0, i64 %1) #0 {
  %3 = alloca %struct.block_meta**, align 8
  %4 = alloca i64, align 8
  %5 = alloca %struct.block_meta*, align 8
  store %struct.block_meta** %0, %struct.block_meta*** %3, align 8
  store i64 %1, i64* %4, align 8
  %6 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  store %struct.block_meta* %6, %struct.block_meta** %5, align 8
  br label %7

7:                                                ; preds = %26, %2
  %8 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %9 = icmp ne %struct.block_meta* %8, null
  br i1 %9, label %10, label %24

10:                                               ; preds = %7
  %11 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %12 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %11, i32 0, i32 2
  %13 = load i32, i32* %12, align 8
  %14 = icmp ne i32 %13, 0
  br i1 %14, label %15, label %21

15:                                               ; preds = %10
  %16 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %17 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %16, i32 0, i32 0
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
  %27 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %28 = load %struct.block_meta**, %struct.block_meta*** %3, align 8
  store %struct.block_meta* %27, %struct.block_meta** %28, align 8
  %29 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %30 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i32 0, i32 1
  %31 = load %struct.block_meta*, %struct.block_meta** %30, align 8
  store %struct.block_meta* %31, %struct.block_meta** %5, align 8
  br label %7

32:                                               ; preds = %24
  call void @strprint(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.45, i64 0, i64 0))
  %33 = load %struct.block_meta**, %struct.block_meta*** %3, align 8
  %34 = load %struct.block_meta*, %struct.block_meta** %33, align 8
  %35 = ptrtoint %struct.block_meta* %34 to i64
  call void @prd(i64 %35)
  call void @strprint(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.46, i64 0, i64 0))
  %36 = load %struct.block_meta**, %struct.block_meta*** %3, align 8
  %37 = load %struct.block_meta*, %struct.block_meta** %36, align 8
  %38 = icmp eq %struct.block_meta* %37, null
  br i1 %38, label %39, label %40

39:                                               ; preds = %32
  br label %45

40:                                               ; preds = %32
  %41 = load %struct.block_meta**, %struct.block_meta*** %3, align 8
  %42 = load %struct.block_meta*, %struct.block_meta** %41, align 8
  %43 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %42, i32 0, i32 0
  %44 = load i64, i64* %43, align 8
  br label %45

45:                                               ; preds = %40, %39
  %46 = phi i64 [ -1, %39 ], [ %44, %40 ]
  call void @prd(i64 %46)
  call void @strprint(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.47, i64 0, i64 0))
  %47 = load i64, i64* %4, align 8
  call void @prd(i64 %47)
  call void @strprint(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.48, i64 0, i64 0))
  %48 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %49 = ptrtoint %struct.block_meta* %48 to i64
  call void @prd(i64 %49)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i64 0, i64 0))
  %50 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  ret %struct.block_meta* %50
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @dbg_blocks() #0 {
  %1 = alloca %struct.block_meta*, align 8
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  store %struct.block_meta* %4, %struct.block_meta** %1, align 8
  store i32 0, i32* %2, align 4
  call void @strprint(i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.30, i64 0, i64 0))
  store i32 0, i32* %3, align 4
  br label %5

5:                                                ; preds = %46, %0
  %6 = load %struct.block_meta*, %struct.block_meta** %1, align 8
  %7 = icmp ne %struct.block_meta* %6, null
  br i1 %7, label %8, label %50

8:                                                ; preds = %5
  %9 = load i32, i32* %2, align 4
  %10 = add nsw i32 %9, 1
  store i32 %10, i32* %2, align 4
  call void @strprint(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.31, i64 0, i64 0))
  %11 = load %struct.block_meta*, %struct.block_meta** %1, align 8
  %12 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %11, i32 0, i32 2
  %13 = load i32, i32* %12, align 8
  %14 = icmp ne i32 %13, 0
  %15 = zext i1 %14 to i64
  %16 = select i1 %14, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.32, i64 0, i64 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.33, i64 0, i64 0)
  call void @strprint(i8* %16)
  call void @strprint(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.34, i64 0, i64 0))
  %17 = load %struct.block_meta*, %struct.block_meta** %1, align 8
  %18 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %17, i32 0, i32 0
  %19 = load i64, i64* %18, align 8
  call void @prd(i64 %19)
  call void @strprint(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.35, i64 0, i64 0))
  %20 = load %struct.block_meta*, %struct.block_meta** %1, align 8
  %21 = ptrtoint %struct.block_meta* %20 to i64
  %22 = load i32*, i32** @memory, align 8
  %23 = ptrtoint i32* %22 to i64
  %24 = sub nsw i64 %21, %23
  call void @prd(i64 %24)
  call void @strprint(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.36, i64 0, i64 0))
  %25 = load %struct.block_meta*, %struct.block_meta** %1, align 8
  %26 = ptrtoint %struct.block_meta* %25 to i64
  %27 = load i32*, i32** @memory, align 8
  %28 = ptrtoint i32* %27 to i64
  %29 = sub nsw i64 %26, %28
  %30 = add i64 %29, 24
  %31 = load %struct.block_meta*, %struct.block_meta** %1, align 8
  %32 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %31, i32 0, i32 0
  %33 = load i64, i64* %32, align 8
  %34 = add i64 %30, %33
  call void @prd(i64 %34)
  call void @strprint(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.37, i64 0, i64 0))
  %35 = load %struct.block_meta*, %struct.block_meta** %1, align 8
  %36 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %35, i32 0, i32 1
  %37 = load %struct.block_meta*, %struct.block_meta** %36, align 8
  %38 = ptrtoint %struct.block_meta* %37 to i64
  %39 = load i32*, i32** @memory, align 8
  %40 = ptrtoint i32* %39 to i64
  %41 = sub nsw i64 %38, %40
  call void @prd(i64 %41)
  call void @prc(i8 signext 10)
  %42 = load i32, i32* %3, align 4
  %43 = add nsw i32 %42, 2
  store i32 %43, i32* %3, align 4
  %44 = icmp eq i32 %43, 20
  br i1 %44, label %45, label %46

45:                                               ; preds = %8
  call void @strprint(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.38, i64 0, i64 0))
  call void @exit(i32 1) #7
  unreachable

46:                                               ; preds = %8
  %47 = load %struct.block_meta*, %struct.block_meta** %1, align 8
  %48 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %47, i32 0, i32 1
  %49 = load %struct.block_meta*, %struct.block_meta** %48, align 8
  store %struct.block_meta* %49, %struct.block_meta** %1, align 8
  br label %5

50:                                               ; preds = %5
  call void @strprint(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.39, i64 0, i64 0))
  %51 = load i32, i32* %2, align 4
  %52 = sext i32 %51 to i64
  call void @prd(i64 %52)
  call void @strprint(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.40, i64 0, i64 0))
  %53 = load i32, i32* %2, align 4
  %54 = icmp eq i32 %53, 1
  %55 = zext i1 %54 to i64
  %56 = select i1 %54, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.18, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.19, i64 0, i64 0)
  call void @strprint(i8* %56)
  ret void
}

; Function Attrs: noreturn
declare void @exit(i32) #1

declare i32 @printf(i8*, ...) #2

declare i32 @putchar(i32) #2

; Function Attrs: allocsize(0,1)
declare i8* @calloc(i64, i64) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @realign(i8** %0) #0 {
  %2 = alloca i8**, align 8
  store i8** %0, i8*** %2, align 8
  call void @strprint(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.43, i64 0, i64 0))
  %3 = load i8**, i8*** %2, align 8
  %4 = load i8*, i8** %3, align 8
  %5 = ptrtoint i8* %4 to i64
  %6 = load i32*, i32** @memory, align 8
  %7 = ptrtoint i32* %6 to i64
  %8 = sub nsw i64 %5, %7
  call void @prd(i64 %8)
  %9 = load i8**, i8*** %2, align 8
  %10 = load i8*, i8** %9, align 8
  %11 = ptrtoint i8* %10 to i64
  %12 = srem i64 %11, 32
  %13 = icmp ne i64 %12, 0
  br i1 %13, label %14, label %23

14:                                               ; preds = %1
  %15 = load i8**, i8*** %2, align 8
  %16 = load i8*, i8** %15, align 8
  %17 = ptrtoint i8* %16 to i64
  %18 = srem i64 %17, 32
  %19 = sub nsw i64 32, %18
  %20 = load i8**, i8*** %2, align 8
  %21 = load i8*, i8** %20, align 8
  %22 = getelementptr inbounds i8, i8* %21, i64 %19
  store i8* %22, i8** %20, align 8
  br label %23

23:                                               ; preds = %14, %1
  call void @strprint(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.44, i64 0, i64 0))
  %24 = load i8**, i8*** %2, align 8
  %25 = load i8*, i8** %24, align 8
  %26 = ptrtoint i8* %25 to i64
  %27 = load i32*, i32** @memory, align 8
  %28 = ptrtoint i32* %27 to i64
  %29 = sub nsw i64 %26, %28
  call void @prd(i64 %29)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i64 0, i64 0))
  %30 = load i8**, i8*** %2, align 8
  %31 = load i8*, i8** %30, align 8
  ret i8* %31
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.block_meta* @request_space(%struct.block_meta* %0, i64 %1) #0 {
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
  br i1 %9, label %10, label %31

10:                                               ; preds = %2
  call void @strprint(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.49, i64 0, i64 0))
  %11 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %12 = ptrtoint %struct.block_meta* %11 to i64
  %13 = load i32*, i32** @memory, align 8
  %14 = ptrtoint i32* %13 to i64
  %15 = sub nsw i64 %12, %14
  call void @prd(i64 %15)
  call void @strprint(i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.50, i64 0, i64 0))
  %16 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %17 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %16, i32 0, i32 1
  %18 = load %struct.block_meta*, %struct.block_meta** %17, align 8
  %19 = ptrtoint %struct.block_meta* %18 to i64
  %20 = load i32*, i32** @memory, align 8
  %21 = ptrtoint i32* %20 to i64
  %22 = sub nsw i64 %19, %21
  call void @prd(i64 %22)
  call void @strprint(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.44, i64 0, i64 0))
  %23 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %24 = ptrtoint %struct.block_meta* %23 to i64
  %25 = load i32*, i32** @memory, align 8
  %26 = ptrtoint i32* %25 to i64
  %27 = sub nsw i64 %24, %26
  call void @prd(i64 %27)
  call void @strprint(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.51, i64 0, i64 0))
  %28 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %29 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %30 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i32 0, i32 1
  store %struct.block_meta* %28, %struct.block_meta** %30, align 8
  br label %31

31:                                               ; preds = %10, %2
  %32 = load i64, i64* %4, align 8
  %33 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %34 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %33, i32 0, i32 0
  store i64 %32, i64* %34, align 8
  %35 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %36 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %35, i32 0, i32 1
  store %struct.block_meta* null, %struct.block_meta** %36, align 8
  %37 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %38 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %37, i32 0, i32 2
  store i32 0, i32* %38, align 8
  %39 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %40 = bitcast %struct.block_meta* %39 to i8*
  %41 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %42 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %41, i32 0, i32 0
  %43 = load i64, i64* %42, align 8
  %44 = getelementptr inbounds i8, i8* %40, i64 %43
  %45 = getelementptr inbounds i8, i8* %44, i64 24
  %46 = getelementptr inbounds i8, i8* %45, i64 1
  store i8* %46, i8** @end, align 8
  %47 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  ret %struct.block_meta* %47
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @memsplit(%struct.block_meta* %0, i64 %1) #0 {
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
  br i1 %13, label %14, label %123

14:                                               ; preds = %2
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
  br i1 %27, label %28, label %79

28:                                               ; preds = %14
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
  br i1 %41, label %42, label %78

42:                                               ; preds = %28
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
  call void @strprint(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.64, i64 0, i64 0))
  %54 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %55 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %54, i32 0, i32 1
  %56 = load %struct.block_meta*, %struct.block_meta** %55, align 8
  %57 = ptrtoint %struct.block_meta* %56 to i64
  %58 = load i32*, i32** @memory, align 8
  %59 = ptrtoint i32* %58 to i64
  %60 = sub nsw i64 %57, %59
  call void @prd(i64 %60)
  call void @strprint(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.44, i64 0, i64 0))
  %61 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %62 = ptrtoint %struct.block_meta* %61 to i64
  %63 = load i32*, i32** @memory, align 8
  %64 = ptrtoint i32* %63 to i64
  %65 = sub nsw i64 %62, %64
  call void @prd(i64 %65)
  call void @prc(i8 signext 10)
  %66 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %67 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %68 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %67, i32 0, i32 1
  store %struct.block_meta* %66, %struct.block_meta** %68, align 8
  call void @strprint(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.65, i64 0, i64 0))
  %69 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %70 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %69, i32 0, i32 0
  %71 = load i64, i64* %70, align 8
  call void @prd(i64 %71)
  call void @strprint(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.44, i64 0, i64 0))
  %72 = load i64, i64* %4, align 8
  %73 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %74 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %73, i32 0, i32 0
  store i64 %72, i64* %74, align 8
  %75 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %76 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %75, i32 0, i32 0
  %77 = load i64, i64* %76, align 8
  call void @prd(i64 %77)
  call void @prc(i8 signext 10)
  br label %78

78:                                               ; preds = %42, %28
  br label %122

79:                                               ; preds = %14
  %80 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %81 = bitcast %struct.block_meta* %80 to i8*
  %82 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %83 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %82, i32 0, i32 0
  %84 = load i64, i64* %83, align 8
  %85 = getelementptr inbounds i8, i8* %81, i64 %84
  %86 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %87 = bitcast %struct.block_meta* %86 to i8*
  %88 = ptrtoint i8* %85 to i64
  %89 = ptrtoint i8* %87 to i64
  %90 = sub i64 %88, %89
  %91 = trunc i64 %90 to i32
  store i32 %91, i32* %7, align 4
  %92 = load i32, i32* %7, align 4
  %93 = icmp sgt i32 %92, 0
  br i1 %93, label %94, label %121

94:                                               ; preds = %79
  %95 = load i32, i32* %7, align 4
  %96 = sext i32 %95 to i64
  %97 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %98 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %97, i32 0, i32 0
  store i64 %96, i64* %98, align 8
  %99 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %100 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %99, i32 0, i32 2
  store i32 1, i32* %100, align 8
  %101 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %102 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %101, i32 0, i32 1
  store %struct.block_meta* null, %struct.block_meta** %102, align 8
  %103 = load i64, i64* %4, align 8
  %104 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %105 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %104, i32 0, i32 0
  store i64 %103, i64* %105, align 8
  call void @strprint(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.66, i64 0, i64 0))
  %106 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %107 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %106, i32 0, i32 1
  %108 = load %struct.block_meta*, %struct.block_meta** %107, align 8
  %109 = ptrtoint %struct.block_meta* %108 to i64
  %110 = load i32*, i32** @memory, align 8
  %111 = ptrtoint i32* %110 to i64
  %112 = sub nsw i64 %109, %111
  call void @prd(i64 %112)
  call void @strprint(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.44, i64 0, i64 0))
  %113 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %114 = ptrtoint %struct.block_meta* %113 to i64
  %115 = load i32*, i32** @memory, align 8
  %116 = ptrtoint i32* %115 to i64
  %117 = sub nsw i64 %114, %116
  call void @prd(i64 %117)
  call void @prc(i8 signext 10)
  %118 = load %struct.block_meta*, %struct.block_meta** %5, align 8
  %119 = load %struct.block_meta*, %struct.block_meta** %3, align 8
  %120 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %119, i32 0, i32 1
  store %struct.block_meta* %118, %struct.block_meta** %120, align 8
  br label %121

121:                                              ; preds = %94, %79
  br label %122

122:                                              ; preds = %121, %78
  br label %123

123:                                              ; preds = %122, %2
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.block_meta* @get_block_ptr(i8* %0) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = bitcast i8* %3 to %struct.block_meta*
  %5 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %4, i64 -1
  ret %struct.block_meta* %5
}

; Function Attrs: cold noreturn
declare void @__assert_rtn(i8*, i8*, i32, i8*) #4

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @merge_blocks() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.block_meta*, align 8
  store i32 0, i32* %1, align 4
  %3 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  store %struct.block_meta* %3, %struct.block_meta** %2, align 8
  %4 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8
  %5 = ptrtoint %struct.block_meta* %4 to i64
  call void @prd(i64 %5)
  call void @prc(i8 signext 10)
  %6 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %7 = ptrtoint %struct.block_meta* %6 to i64
  call void @prd(i64 %7)
  call void @strprint(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.73, i64 0, i64 0))
  %8 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %9 = ptrtoint %struct.block_meta* %8 to i64
  call void @prd(i64 %9)
  call void @strprint(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.74, i64 0, i64 0))
  %10 = load i32*, i32** @memory, align 8
  %11 = ptrtoint i32* %10 to i64
  call void @prd(i64 %11)
  call void @strprint(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.75, i64 0, i64 0))
  %12 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %13 = ptrtoint %struct.block_meta* %12 to i64
  %14 = load i32*, i32** @memory, align 8
  %15 = ptrtoint i32* %14 to i64
  %16 = sub nsw i64 %13, %15
  call void @prd(i64 %16)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i64 0, i64 0))
  br label %17

17:                                               ; preds = %87, %0
  %18 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %19 = icmp ne %struct.block_meta* %18, null
  br i1 %19, label %20, label %25

20:                                               ; preds = %17
  %21 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %22 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %21, i32 0, i32 1
  %23 = load %struct.block_meta*, %struct.block_meta** %22, align 8
  %24 = icmp ne %struct.block_meta* %23, null
  br label %25

25:                                               ; preds = %20, %17
  %26 = phi i1 [ false, %17 ], [ %24, %20 ]
  br i1 %26, label %27, label %88

27:                                               ; preds = %25
  %28 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %29 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %28, i32 0, i32 2
  %30 = load i32, i32* %29, align 8
  %31 = icmp ne i32 %30, 0
  br i1 %31, label %32, label %83

32:                                               ; preds = %27
  %33 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %34 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %33, i32 0, i32 1
  %35 = load %struct.block_meta*, %struct.block_meta** %34, align 8
  %36 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %35, i32 0, i32 2
  %37 = load i32, i32* %36, align 8
  %38 = icmp ne i32 %37, 0
  br i1 %38, label %39, label %83

39:                                               ; preds = %32
  call void @strprint(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.76, i64 0, i64 0))
  call void @strprint(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.77, i64 0, i64 0))
  %40 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %41 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %40, i32 0, i32 0
  %42 = load i64, i64* %41, align 8
  call void @prd(i64 %42)
  call void @strprint(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.78, i64 0, i64 0))
  call void @prd(i64 24)
  call void @strprint(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.79, i64 0, i64 0))
  %43 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %44 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %43, i32 0, i32 1
  %45 = load %struct.block_meta*, %struct.block_meta** %44, align 8
  %46 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %45, i32 0, i32 0
  %47 = load i64, i64* %46, align 8
  call void @prd(i64 %47)
  call void @strprint(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i64 0, i64 0))
  %48 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %49 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %48, i32 0, i32 1
  %50 = load %struct.block_meta*, %struct.block_meta** %49, align 8
  %51 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %50, i32 0, i32 0
  %52 = load i64, i64* %51, align 8
  %53 = add i64 24, %52
  %54 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %55 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %54, i32 0, i32 0
  %56 = load i64, i64* %55, align 8
  %57 = add i64 %56, %53
  store i64 %57, i64* %55, align 8
  call void @strprint(i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.80, i64 0, i64 0))
  %58 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %59 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %58, i32 0, i32 1
  %60 = load %struct.block_meta*, %struct.block_meta** %59, align 8
  %61 = ptrtoint %struct.block_meta* %60 to i64
  %62 = load i32*, i32** @memory, align 8
  %63 = ptrtoint i32* %62 to i64
  %64 = sub nsw i64 %61, %63
  call void @prd(i64 %64)
  call void @strprint(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.81, i64 0, i64 0))
  %65 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %66 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %65, i32 0, i32 1
  %67 = load %struct.block_meta*, %struct.block_meta** %66, align 8
  %68 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %67, i32 0, i32 1
  %69 = load %struct.block_meta*, %struct.block_meta** %68, align 8
  %70 = ptrtoint %struct.block_meta* %69 to i64
  %71 = load i32*, i32** @memory, align 8
  %72 = ptrtoint i32* %71 to i64
  %73 = sub nsw i64 %70, %72
  call void @prd(i64 %73)
  call void @strprint(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.82, i64 0, i64 0))
  %74 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %75 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %74, i32 0, i32 1
  %76 = load %struct.block_meta*, %struct.block_meta** %75, align 8
  %77 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %76, i32 0, i32 1
  %78 = load %struct.block_meta*, %struct.block_meta** %77, align 8
  %79 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %80 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %79, i32 0, i32 1
  store %struct.block_meta* %78, %struct.block_meta** %80, align 8
  %81 = load i32, i32* %1, align 4
  %82 = add nsw i32 %81, 1
  store i32 %82, i32* %1, align 4
  br label %87

83:                                               ; preds = %32, %27
  call void @strprint(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.83, i64 0, i64 0))
  %84 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %85 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %84, i32 0, i32 1
  %86 = load %struct.block_meta*, %struct.block_meta** %85, align 8
  store %struct.block_meta* %86, %struct.block_meta** %2, align 8
  br label %87

87:                                               ; preds = %83, %39
  br label %17

88:                                               ; preds = %25
  %89 = load %struct.block_meta*, %struct.block_meta** %2, align 8
  %90 = ptrtoint %struct.block_meta* %89 to i64
  call void @prd(i64 %90)
  call void @prc(i8 signext 10)
  %91 = ptrtoint %struct.block_meta** %2 to i64
  call void @prd(i64 %91)
  %92 = load i32, i32* %1, align 4
  %93 = icmp sgt i32 %92, 0
  br i1 %93, label %94, label %102

94:                                               ; preds = %88
  call void @strprint(i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.84, i64 0, i64 0))
  %95 = load i32, i32* %1, align 4
  %96 = sext i32 %95 to i64
  call void @prd(i64 %96)
  call void @strprint(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.40, i64 0, i64 0))
  %97 = load i32, i32* %1, align 4
  %98 = icmp eq i32 %97, 1
  %99 = zext i1 %98 to i64
  %100 = select i1 %98, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.18, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.19, i64 0, i64 0)
  call void @strprint(i8* %100)
  %101 = ptrtoint i32* %1 to i64
  call void @prd(i64 %101)
  br label %102

102:                                              ; preds = %94, %88
  %103 = load i32, i32* %1, align 4
  ret i32 %103
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { allocsize(0,1) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { cold noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="true" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { allocsize(0,1) }
attributes #6 = { cold noreturn }
attributes #7 = { noreturn }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 10.0.0 "}
