; ModuleID = 'mal.c'
source_filename = "mal.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.block_meta = type { i64, %struct.block_meta*, i32 }

@memory = common local_unnamed_addr global i32* null, align 8
@end = common local_unnamed_addr global i8* null, align 8
@global_base = common local_unnamed_addr global %struct.block_meta* null, align 8
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
@str = private unnamed_addr constant [36 x i8] c"\1B[38;5;226mSetting global_base\1B[0m.\00", align 1

; Function Attrs: nounwind ssp uwtable
define i32 @mem_init(i32) local_unnamed_addr #0 {
  %2 = sext i32 %0 to i64
  %3 = tail call i8* @calloc(i64 %2, i64 4) #7
  %4 = ptrtoint i8* %3 to i64
  %5 = srem i64 %4, 32
  %6 = icmp eq i64 %5, 0
  %7 = sub nsw i64 32, %5
  %8 = getelementptr inbounds i8, i8* %3, i64 %7
  %9 = select i1 %6, i8* %3, i8* %8
  store i8* %9, i8** bitcast (i32** @memory to i8**), align 8, !tbaa !42, !nontemporal !42
  %100 = ptrtoint i8* %9 to i64
  store i64 %10, i64* bitcast (i8** @end to i64*), align 8, !tbaa !4
  store %struct.block_meta* null, %struct.block_meta** @global_base, align 8, !tbaa !4
  %11 = icmp ne i8* %9, null
  %12 = zext i1 %11 to i32
  ret i32 %12
}

; Function Attrs: nounwind allocsize(0,1)
declare noalias i8* @calloc(i64, i64) local_unnamed_addr #1

; Function Attrs: norecurse nounwind ssp uwtable
define i8* @realign(i8** nocapture) local_unnamed_addr #2 {
  %2 = load i8*, i8** %0, align 8, !tbaa !4
  %3 = ptrtoint i8* %2 to i64
  %4 = srem i64 %3, 32
  %5 = icmp eq i64 %4, 0
  br i1 %5, label %9, label %6

; <label>:6:                                      ; preds = %1
  %7 = sub nsw i64 32, %4
  %8 = getelementptr inbounds i8, i8* %2, i64 %7
  store i8* %8, i8** %0, align 8, !tbaa !4
  br label %9

; <label>:9:                                      ; preds = %1, %6
  %10 = phi i8* [ %2, %1 ], [ %8, %6 ]
  ret i8* %10
}

; Function Attrs: norecurse nounwind ssp uwtable
define %struct.block_meta* @find_free_block(%struct.block_meta** nocapture, i64) local_unnamed_addr #2 {
  %3 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %4 = icmp eq %struct.block_meta* %3, null
  br i1 %4, label %18, label %5

; <label>:5:                                      ; preds = %2, %14
  %6 = phi %struct.block_meta* [ %16, %14 ], [ %3, %2 ]
  %7 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %6, i64 0, i32 2
  %8 = load i32, i32* %7, align 8, !tbaa !8
  %9 = icmp eq i32 %8, 0
  br i1 %9, label %14, label %10

; <label>:10:                                     ; preds = %5
  %11 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %6, i64 0, i32 0
  %12 = load i64, i64* %11, align 8, !tbaa !12
  %13 = icmp ult i64 %12, %1
  br i1 %13, label %14, label %18

; <label>:14:                                     ; preds = %5, %10
  store %struct.block_meta* %6, %struct.block_meta** %0, align 8, !tbaa !4
  %15 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %6, i64 0, i32 1
  %16 = load %struct.block_meta*, %struct.block_meta** %15, align 8, !tbaa !4
  %17 = icmp eq %struct.block_meta* %16, null
  br i1 %17, label %18, label %5

; <label>:18:                                     ; preds = %10, %14, %2
  %19 = phi %struct.block_meta* [ null, %2 ], [ null, %14 ], [ %6, %10 ]
  ret %struct.block_meta* %19
}

; Function Attrs: norecurse nounwind ssp uwtable
define %struct.block_meta* @request_space(%struct.block_meta*, i64) local_unnamed_addr #2 {
  %3 = load i8*, i8** @end, align 8, !tbaa !4
  %4 = ptrtoint i8* %3 to i64
  %5 = srem i64 %4, 32
  %6 = icmp eq i64 %5, 0
  br i1 %6, label %10, label %7

; <label>:7:                                      ; preds = %2
  %8 = sub nsw i64 32, %5
  %9 = getelementptr inbounds i8, i8* %3, i64 %8
  store i8* %9, i8** @end, align 8, !tbaa !4
  br label %10

; <label>:10:                                     ; preds = %2, %7
  %11 = phi i8* [ %3, %2 ], [ %9, %7 ]
  %12 = bitcast i8* %11 to %struct.block_meta*
  %13 = icmp eq %struct.block_meta* %0, null
  br i1 %13, label %17, label %14

; <label>:14:                                     ; preds = %10
  %15 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %0, i64 0, i32 1
  %16 = bitcast %struct.block_meta** %15 to i8**
  store i8* %11, i8** %16, align 8, !tbaa !13
  br label %17

; <label>:17:                                     ; preds = %10, %14
  %18 = bitcast i8* %11 to i64*
  store i64 %1, i64* %18, align 8, !tbaa !12
  %19 = getelementptr inbounds i8, i8* %11, i64 8
  %20 = bitcast i8* %19 to %struct.block_meta**
  store %struct.block_meta* null, %struct.block_meta** %20, align 8, !tbaa !13
  %21 = getelementptr inbounds i8, i8* %11, i64 16
  %22 = bitcast i8* %21 to i32*
  store i32 0, i32* %22, align 8, !tbaa !8
  %23 = getelementptr inbounds i8, i8* %11, i64 %1
  %24 = getelementptr inbounds i8, i8* %23, i64 24
  %25 = getelementptr inbounds i8, i8* %24, i64 1
  store i8* %25, i8** @end, align 8, !tbaa !4
  ret %struct.block_meta* %12
}

; Function Attrs: nounwind ssp uwtable
define i8* @mal(i64) local_unnamed_addr #0 {
  %2 = icmp eq i64 %0, 0
  br i1 %2, label %134, label %3

; <label>:3:                                      ; preds = %1
  %4 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %5 = icmp eq %struct.block_meta* %4, null
  br i1 %5, label %6, label %28

; <label>:6:                                      ; preds = %3
  %7 = load i8*, i8** @end, align 8, !tbaa !4
  %8 = ptrtoint i8* %7 to i64
  %9 = srem i64 %8, 32
  %10 = icmp eq i64 %9, 0
  br i1 %10, label %14, label %11

; <label>:11:                                     ; preds = %6
  %12 = sub nsw i64 32, %9
  %13 = getelementptr inbounds i8, i8* %7, i64 %12
  store i8* %13, i8** @end, align 8, !tbaa !4
  br label %14

; <label>:14:                                     ; preds = %6, %11
  %15 = phi i8* [ %7, %6 ], [ %13, %11 ]
  %16 = bitcast i8* %15 to i64*
  store i64 %0, i64* %16, align 8, !tbaa !12
  %17 = getelementptr inbounds i8, i8* %15, i64 8
  %18 = bitcast i8* %17 to %struct.block_meta**
  store %struct.block_meta* null, %struct.block_meta** %18, align 8, !tbaa !13
  %19 = getelementptr inbounds i8, i8* %15, i64 16
  %20 = bitcast i8* %19 to i32*
  store i32 0, i32* %20, align 8, !tbaa !8
  %21 = getelementptr inbounds i8, i8* %15, i64 %0
  %22 = getelementptr inbounds i8, i8* %21, i64 24
  %23 = getelementptr inbounds i8, i8* %22, i64 1
  store i8* %23, i8** @end, align 8, !tbaa !4
  %24 = icmp eq i8* %15, null
  br i1 %24, label %134, label %25

; <label>:25:                                     ; preds = %14
  %26 = bitcast i8* %15 to %struct.block_meta*
  %27 = tail call i32 @puts(i8* getelementptr inbounds ([36 x i8], [36 x i8]* @str, i64 0, i64 0))
  store i8* %15, i8** bitcast (%struct.block_meta** @global_base to i8**), align 8, !tbaa !4
  br label %130

; <label>:28:                                     ; preds = %3, %37
  %29 = phi %struct.block_meta* [ %39, %37 ], [ %4, %3 ]
  %30 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i64 0, i32 2
  %31 = load i32, i32* %30, align 8, !tbaa !8
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %37, label %33

; <label>:33:                                     ; preds = %28
  %34 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i64 0, i32 0
  %35 = load i64, i64* %34, align 8, !tbaa !12
  %36 = icmp ult i64 %35, %0
  br i1 %36, label %37, label %73

; <label>:37:                                     ; preds = %33, %28
  %38 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i64 0, i32 1
  %39 = load %struct.block_meta*, %struct.block_meta** %38, align 8, !tbaa !4
  %40 = icmp eq %struct.block_meta* %39, null
  br i1 %40, label %41, label %28

; <label>:41:                                     ; preds = %37
  %42 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i64 0, i32 1
  %43 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i64 1
  %44 = bitcast %struct.block_meta* %43 to i8*
  %45 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i64 0, i32 0
  %46 = load i64, i64* %45, align 8, !tbaa !12
  %47 = getelementptr inbounds i8, i8* %44, i64 %46
  %48 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %49 = sub i64 0, %48
  %50 = getelementptr inbounds i8, i8* %47, i64 %49
  %51 = ptrtoint i8* %50 to i64
  %52 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.1, i64 0, i64 0), i64 %51)
  %53 = load i8*, i8** @end, align 8, !tbaa !4
  %54 = ptrtoint i8* %53 to i64
  %55 = srem i64 %54, 32
  %56 = icmp eq i64 %55, 0
  br i1 %56, label %60, label %57

; <label>:57:                                     ; preds = %41
  %58 = sub nsw i64 32, %55
  %59 = getelementptr inbounds i8, i8* %53, i64 %58
  store i8* %59, i8** @end, align 8, !tbaa !4
  br label %60

; <label>:60:                                     ; preds = %57, %41
  %61 = phi i8* [ %53, %41 ], [ %59, %57 ]
  %62 = bitcast i8* %61 to %struct.block_meta*
  %63 = bitcast %struct.block_meta** %42 to i8**
  store i8* %61, i8** %63, align 8, !tbaa !13
  %64 = bitcast i8* %61 to i64*
  store i64 %0, i64* %64, align 8, !tbaa !12
  %65 = getelementptr inbounds i8, i8* %61, i64 8
  %66 = bitcast i8* %65 to %struct.block_meta**
  store %struct.block_meta* null, %struct.block_meta** %66, align 8, !tbaa !13
  %67 = getelementptr inbounds i8, i8* %61, i64 16
  %68 = bitcast i8* %67 to i32*
  store i32 0, i32* %68, align 8, !tbaa !8
  %69 = getelementptr inbounds i8, i8* %61, i64 %0
  %70 = getelementptr inbounds i8, i8* %69, i64 24
  %71 = getelementptr inbounds i8, i8* %70, i64 1
  store i8* %71, i8** @end, align 8, !tbaa !4
  %72 = icmp eq i8* %61, null
  br i1 %72, label %134, label %130

; <label>:73:                                     ; preds = %33
  %74 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i64 0, i32 2
  %75 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i64 0, i32 0
  %76 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %29, i64 0, i32 1
  %77 = load %struct.block_meta*, %struct.block_meta** %76, align 8, !tbaa !13
  %78 = icmp eq %struct.block_meta* %77, null
  %79 = select i1 %78, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.4, i64 0, i64 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.3, i64 0, i64 0)
  %80 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.2, i64 0, i64 0), i8* %79)
  %81 = load i64, i64* %75, align 8, !tbaa !12
  %82 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.5, i64 0, i64 0), i64 %81)
  %83 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.6, i64 0, i64 0), i64 %0)
  %84 = load i64, i64* %75, align 8, !tbaa !12
  %85 = add i64 %0, 24
  %86 = icmp ugt i64 %84, %85
  br i1 %86, label %87, label %129

; <label>:87:                                     ; preds = %73
  %88 = bitcast %struct.block_meta* %29 to i8*
  %89 = getelementptr inbounds i8, i8* %88, i64 %0
  %90 = getelementptr inbounds i8, i8* %89, i64 24
  %91 = getelementptr inbounds i8, i8* %90, i64 1
  %92 = ptrtoint i8* %91 to i64
  %93 = srem i64 %92, 32
  %94 = icmp eq i64 %93, 0
  %95 = sub nsw i64 32, %93
  %96 = getelementptr inbounds i8, i8* %91, i64 %95
  %97 = ptrtoint i8* %96 to i64
  %98 = select i1 %94, i64 %92, i64 %97
  %99 = load %struct.block_meta*, %struct.block_meta** %76, align 8, !tbaa !13
  %100 = icmp eq %struct.block_meta* %99, null
  %101 = ptrtoint %struct.block_meta* %99 to i64
  br i1 %100, label %115, label %102

; <label>:102:                                    ; preds = %87
  %103 = inttoptr i64 %98 to %struct.block_meta*
  %104 = sub i64 %101, %98
  %105 = trunc i64 %104 to i32
  %106 = add i32 %105, -24
  %107 = icmp sgt i32 %106, 0
  br i1 %107, label %108, label %129

; <label>:108:                                    ; preds = %102
  %109 = sext i32 %106 to i64
  %110 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %103, i64 0, i32 0
  store i64 %109, i64* %110, align 8, !tbaa !12
  %111 = bitcast %struct.block_meta** %76 to i64*
  %112 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %103, i64 0, i32 1
  %113 = bitcast %struct.block_meta** %112 to i64*
  store i64 %101, i64* %113, align 8, !tbaa !13
  %114 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %103, i64 0, i32 2
  store i32 1, i32* %114, align 8, !tbaa !8
  store i64 %98, i64* %111, align 8, !tbaa !13
  store i64 %0, i64* %75, align 8, !tbaa !12
  br label %129

; <label>:115:                                    ; preds = %87
  %116 = getelementptr inbounds i8, i8* %88, i64 %84
  %117 = inttoptr i64 %98 to %struct.block_meta*
  %118 = ptrtoint i8* %116 to i64
  %119 = sub i64 %118, %98
  %120 = trunc i64 %119 to i32
  %121 = icmp sgt i32 %120, 0
  br i1 %121, label %122, label %129

; <label>:122:                                    ; preds = %115
  %123 = shl i64 %119, 32
  %124 = ashr exact i64 %123, 32
  %125 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %117, i64 0, i32 0
  store i64 %124, i64* %125, align 8, !tbaa !12
  %126 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %117, i64 0, i32 2
  store i32 1, i32* %126, align 8, !tbaa !8
  %127 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %117, i64 0, i32 1
  store %struct.block_meta* null, %struct.block_meta** %127, align 8, !tbaa !13
  store i64 %0, i64* %75, align 8, !tbaa !12
  %128 = bitcast %struct.block_meta** %76 to i64*
  store i64 %98, i64* %128, align 8, !tbaa !13
  br label %129

; <label>:129:                                    ; preds = %73, %102, %108, %115, %122
  store i32 0, i32* %74, align 8, !tbaa !8
  br label %130

; <label>:130:                                    ; preds = %60, %129, %25
  %131 = phi %struct.block_meta* [ %26, %25 ], [ %29, %129 ], [ %62, %60 ]
  %132 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %131, i64 1
  %133 = bitcast %struct.block_meta* %132 to i8*
  br label %134

; <label>:134:                                    ; preds = %60, %14, %1, %130
  %135 = phi i8* [ %133, %130 ], [ null, %1 ], [ null, %14 ], [ null, %60 ]
  ret i8* %135
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #3

; Function Attrs: nounwind ssp uwtable
define void @memsplit(%struct.block_meta*, i64) local_unnamed_addr #0 {
  %3 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %0, i64 0, i32 0
  %4 = load i64, i64* %3, align 8, !tbaa !12
  %5 = add i64 %1, 24
  %6 = icmp ugt i64 %4, %5
  br i1 %6, label %7, label %50

; <label>:7:                                      ; preds = %2
  %8 = bitcast %struct.block_meta* %0 to i8*
  %9 = getelementptr inbounds i8, i8* %8, i64 %1
  %10 = getelementptr inbounds i8, i8* %9, i64 24
  %11 = getelementptr inbounds i8, i8* %10, i64 1
  %12 = ptrtoint i8* %11 to i64
  %13 = srem i64 %12, 32
  %14 = icmp eq i64 %13, 0
  %15 = sub nsw i64 32, %13
  %16 = getelementptr inbounds i8, i8* %11, i64 %15
  %17 = ptrtoint i8* %16 to i64
  %18 = select i1 %14, i64 %12, i64 %17
  %19 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %0, i64 0, i32 1
  %20 = load %struct.block_meta*, %struct.block_meta** %19, align 8, !tbaa !13
  %21 = icmp eq %struct.block_meta* %20, null
  %22 = ptrtoint %struct.block_meta* %20 to i64
  br i1 %21, label %36, label %23

; <label>:23:                                     ; preds = %7
  %24 = inttoptr i64 %18 to %struct.block_meta*
  %25 = sub i64 %22, %18
  %26 = trunc i64 %25 to i32
  %27 = add i32 %26, -24
  %28 = icmp sgt i32 %27, 0
  br i1 %28, label %29, label %50

; <label>:29:                                     ; preds = %23
  %30 = sext i32 %27 to i64
  %31 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %24, i64 0, i32 0
  store i64 %30, i64* %31, align 8, !tbaa !12
  %32 = bitcast %struct.block_meta** %19 to i64*
  %33 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %24, i64 0, i32 1
  %34 = bitcast %struct.block_meta** %33 to i64*
  store i64 %22, i64* %34, align 8, !tbaa !13
  %35 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %24, i64 0, i32 2
  store i32 1, i32* %35, align 8, !tbaa !8
  store i64 %18, i64* %32, align 8, !tbaa !13
  store i64 %1, i64* %3, align 8, !tbaa !12
  br label %50

; <label>:36:                                     ; preds = %7
  %37 = getelementptr inbounds i8, i8* %8, i64 %4
  %38 = inttoptr i64 %18 to %struct.block_meta*
  %39 = ptrtoint i8* %37 to i64
  %40 = sub i64 %39, %18
  %41 = trunc i64 %40 to i32
  %42 = icmp sgt i32 %41, 0
  br i1 %42, label %43, label %50

; <label>:43:                                     ; preds = %36
  %44 = shl i64 %40, 32
  %45 = ashr exact i64 %44, 32
  %46 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %38, i64 0, i32 0
  store i64 %45, i64* %46, align 8, !tbaa !12
  %47 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %38, i64 0, i32 2
  store i32 1, i32* %47, align 8, !tbaa !8
  %48 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %38, i64 0, i32 1
  store %struct.block_meta* null, %struct.block_meta** %48, align 8, !tbaa !13
  store i64 %1, i64* %3, align 8, !tbaa !12
  %49 = bitcast %struct.block_meta** %19 to i64*
  store i64 %18, i64* %49, align 8, !tbaa !13
  br label %50

; <label>:50:                                     ; preds = %29, %23, %43, %36, %2
  ret void
}

; Function Attrs: norecurse nounwind readnone ssp uwtable
define nonnull %struct.block_meta* @get_block_ptr(i8* readnone) local_unnamed_addr #4 {
  %2 = getelementptr inbounds i8, i8* %0, i64 -24
  %3 = bitcast i8* %2 to %struct.block_meta*
  ret %struct.block_meta* %3
}

; Function Attrs: nounwind ssp uwtable
define void @fr(i8*) local_unnamed_addr #0 {
  %2 = icmp eq i8* %0, null
  br i1 %2, label %52, label %3

; <label>:3:                                      ; preds = %1
  %4 = getelementptr inbounds i8, i8* %0, i64 -8
  %5 = bitcast i8* %4 to i32*
  %6 = load i32, i32* %5, align 8, !tbaa !8
  %7 = icmp eq i32 %6, 0
  br i1 %7, label %9, label %8, !prof !14

; <label>:8:                                      ; preds = %3
  tail call void @__assert_rtn(i8* getelementptr inbounds ([3 x i8], [3 x i8]* @__func__.fr, i64 0, i64 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.7, i64 0, i64 0), i32 125, i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.8, i64 0, i64 0)) #8
  unreachable

; <label>:9:                                      ; preds = %3
  store i32 1, i32* %5, align 8, !tbaa !8
  %10 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %11 = icmp eq %struct.block_meta* %10, null
  br i1 %11, label %52, label %12

; <label>:12:                                     ; preds = %9
  %13 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %10, i64 0, i32 1
  %14 = load %struct.block_meta*, %struct.block_meta** %13, align 8, !tbaa !13
  %15 = icmp eq %struct.block_meta* %14, null
  br i1 %15, label %52, label %16

; <label>:16:                                     ; preds = %12, %40
  %17 = phi %struct.block_meta* [ %44, %40 ], [ %14, %12 ]
  %18 = phi %struct.block_meta** [ %43, %40 ], [ %13, %12 ]
  %19 = phi i32 [ %41, %40 ], [ 0, %12 ]
  %20 = phi %struct.block_meta* [ %42, %40 ], [ %10, %12 ]
  %21 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %20, i64 0, i32 2
  %22 = load i32, i32* %21, align 8, !tbaa !8
  %23 = icmp eq i32 %22, 0
  br i1 %23, label %40, label %24

; <label>:24:                                     ; preds = %16
  %25 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %17, i64 0, i32 2
  %26 = load i32, i32* %25, align 8, !tbaa !8
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %40, label %28

; <label>:28:                                     ; preds = %24
  %29 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %17, i64 0, i32 0
  %30 = load i64, i64* %29, align 8, !tbaa !12
  %31 = add i64 %30, 24
  %32 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %20, i64 0, i32 0
  %33 = load i64, i64* %32, align 8, !tbaa !12
  %34 = add i64 %31, %33
  store i64 %34, i64* %32, align 8, !tbaa !12
  %35 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %17, i64 0, i32 1
  %36 = bitcast %struct.block_meta** %35 to i64*
  %37 = load i64, i64* %36, align 8, !tbaa !13
  %38 = bitcast %struct.block_meta** %18 to i64*
  store i64 %37, i64* %38, align 8, !tbaa !13
  %39 = add nsw i32 %19, 1
  br label %40

; <label>:40:                                     ; preds = %28, %24, %16
  %41 = phi i32 [ %39, %28 ], [ %19, %24 ], [ %19, %16 ]
  %42 = phi %struct.block_meta* [ %20, %28 ], [ %17, %24 ], [ %17, %16 ]
  %43 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %42, i64 0, i32 1
  %44 = load %struct.block_meta*, %struct.block_meta** %43, align 8, !tbaa !13
  %45 = icmp eq %struct.block_meta* %44, null
  br i1 %45, label %46, label %16

; <label>:46:                                     ; preds = %40
  %47 = icmp sgt i32 %41, 0
  br i1 %47, label %48, label %52

; <label>:48:                                     ; preds = %46
  %49 = icmp eq i32 %41, 1
  %50 = select i1 %49, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.10, i64 0, i64 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i64 0, i64 0)
  %51 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.9, i64 0, i64 0), i32 %41, i8* %50) #6
  br label %52

; <label>:52:                                     ; preds = %12, %48, %46, %9, %1
  ret void
}

; Function Attrs: cold noreturn
declare void @__assert_rtn(i8*, i8*, i32, i8*) local_unnamed_addr #5

; Function Attrs: nounwind ssp uwtable
define i32 @merge_blocks() local_unnamed_addr #0 {
  %1 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %2 = icmp eq %struct.block_meta* %1, null
  br i1 %2, label %44, label %3

; <label>:3:                                      ; preds = %0
  %4 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %1, i64 0, i32 1
  %5 = load %struct.block_meta*, %struct.block_meta** %4, align 8, !tbaa !13
  %6 = icmp eq %struct.block_meta* %5, null
  br i1 %6, label %37, label %7

; <label>:7:                                      ; preds = %3, %31
  %8 = phi %struct.block_meta* [ %35, %31 ], [ %5, %3 ]
  %9 = phi %struct.block_meta** [ %34, %31 ], [ %4, %3 ]
  %10 = phi i32 [ %32, %31 ], [ 0, %3 ]
  %11 = phi %struct.block_meta* [ %33, %31 ], [ %1, %3 ]
  %12 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %11, i64 0, i32 2
  %13 = load i32, i32* %12, align 8, !tbaa !8
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %31, label %15

; <label>:15:                                     ; preds = %7
  %16 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %8, i64 0, i32 2
  %17 = load i32, i32* %16, align 8, !tbaa !8
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %31, label %19

; <label>:19:                                     ; preds = %15
  %20 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %8, i64 0, i32 0
  %21 = load i64, i64* %20, align 8, !tbaa !12
  %22 = add i64 %21, 24
  %23 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %11, i64 0, i32 0
  %24 = load i64, i64* %23, align 8, !tbaa !12
  %25 = add i64 %22, %24
  store i64 %25, i64* %23, align 8, !tbaa !12
  %26 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %8, i64 0, i32 1
  %27 = bitcast %struct.block_meta** %26 to i64*
  %28 = load i64, i64* %27, align 8, !tbaa !13
  %29 = bitcast %struct.block_meta** %9 to i64*
  store i64 %28, i64* %29, align 8, !tbaa !13
  %30 = add nsw i32 %10, 1
  br label %31

; <label>:31:                                     ; preds = %7, %15, %19
  %32 = phi i32 [ %30, %19 ], [ %10, %15 ], [ %10, %7 ]
  %33 = phi %struct.block_meta* [ %11, %19 ], [ %8, %15 ], [ %8, %7 ]
  %34 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %33, i64 0, i32 1
  %35 = load %struct.block_meta*, %struct.block_meta** %34, align 8, !tbaa !13
  %36 = icmp eq %struct.block_meta* %35, null
  br i1 %36, label %37, label %7

; <label>:37:                                     ; preds = %31, %3
  %38 = phi i32 [ 0, %3 ], [ %32, %31 ]
  %39 = icmp sgt i32 %38, 0
  br i1 %39, label %40, label %44

; <label>:40:                                     ; preds = %37
  %41 = icmp eq i32 %38, 1
  %42 = select i1 %41, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.10, i64 0, i64 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i64 0, i64 0)
  %43 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.9, i64 0, i64 0), i32 %38, i8* %42)
  br label %44

; <label>:44:                                     ; preds = %0, %40, %37
  %45 = phi i32 [ %38, %40 ], [ %38, %37 ], [ 0, %0 ]
  ret i32 %45
}

; Function Attrs: nounwind
declare i32 @puts(i8* nocapture readonly) local_unnamed_addr #6

attributes #0 = { nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind allocsize(0,1) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { norecurse nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { norecurse nounwind readnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { cold noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="true" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind }
attributes #7 = { allocsize(0,1) }
attributes #8 = { cold noreturn nounwind }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
!4 = !{!5, !5, i64 0}
!5 = !{!"any pointer", !6, i64 0}
!6 = !{!"omnipotent char", !7, i64 0}
!7 = !{!"Simple C/C++ TBAA"}
!8 = !{!9, !11, i64 16}
!9 = !{!"block_meta", !10, i64 0, !5, i64 8, !11, i64 16}
!10 = !{!"long", !6, i64 0}
!11 = !{!"int", !6, i64 0}
!12 = !{!9, !10, i64 0}
!13 = !{!9, !5, i64 8}
!14 = !{!"branch_weights", i32 2000, i32 1}
