; ModuleID = 'main.c'
source_filename = "main.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.block_meta = type { i64, %struct.block_meta*, i32 }
%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }

@.str.1 = private unnamed_addr constant [26 x i8] c"sizeof(block_meta) = %lu\0A\00", align 1
@.str.2 = private unnamed_addr constant [23 x i8] c"Start (absolute): %ld\0A\00", align 1
@memory = common local_unnamed_addr global i32* null, align 8
@.str.3 = private unnamed_addr constant [5 x i8] c"Ptr1\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"Ptr2\00", align 1
@.str.5 = private unnamed_addr constant [5 x i8] c"Ptr3\00", align 1
@.str.7 = private unnamed_addr constant [5 x i8] c"Ptr4\00", align 1
@.str.8 = private unnamed_addr constant [5 x i8] c"Ptr5\00", align 1
@.str.11 = private unnamed_addr constant [5 x i8] c"Ptr6\00", align 1
@.str.12 = private unnamed_addr constant [5 x i8] c"Ptr7\00", align 1
@.str.14 = private unnamed_addr constant [5 x i8] c"Ptr8\00", align 1
@.str.15 = private unnamed_addr constant [5 x i8] c"Ptr9\00", align 1
@.str.16 = private unnamed_addr constant [6 x i8] c"Ptr10\00", align 1
@.str.17 = private unnamed_addr constant [42 x i8] c"\0A\1B[35mAllocating\1B[0m \1B[1m%lu\1B[0m byte%s.\0A\00", align 1
@.str.18 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.19 = private unnamed_addr constant [2 x i8] c"s\00", align 1
@.str.20 = private unnamed_addr constant [5 x i8] c"%s: \00", align 1
@.str.22 = private unnamed_addr constant [5 x i8] c"%ld\0A\00", align 1
@.str.23 = private unnamed_addr constant [11 x i8] c" End: %ld\0A\00", align 1
@end = common local_unnamed_addr global i8* null, align 8
@global_base = common local_unnamed_addr global %struct.block_meta* null, align 8
@.str.25 = private unnamed_addr constant [11 x i8] c"Base: %ld\0A\00", align 1
@last_block = common global %struct.block_meta* null, align 8
@.str.26 = private unnamed_addr constant [27 x i8] c"Free block >= %ld byte%s: \00", align 1
@.str.28 = private unnamed_addr constant [60 x i8] c"    Found a%s\1B[0m block of size %lu at position [%lu, %lu]\0A\00", align 1
@.str.29 = private unnamed_addr constant [11 x i8] c" \1B[32mfree\00", align 1
@.str.30 = private unnamed_addr constant [17 x i8] c"n \1B[31mallocated\00", align 1
@__stderrp = external local_unnamed_addr global %struct.__sFILE*, align 8
@.str.31 = private unnamed_addr constant [21 x i8] c"Loop took too long!\0A\00", align 1
@.str.32 = private unnamed_addr constant [27 x i8] c"Found \1B[1m%d\1B[0m block%s.\0A\00", align 1
@str = private unnamed_addr constant [21 x i8] c"Initializing memory.\00", align 1
@str.33 = private unnamed_addr constant [30 x i8] c"\0AFreeing 200 and 10 pointers.\00", align 1
@str.34 = private unnamed_addr constant [31 x i8] c"\0AFreeing 100 and 800 pointers.\00", align 1
@str.35 = private unnamed_addr constant [32 x i8] c"\0AFreeing 600 and 1000 pointers.\00", align 1
@str.37 = private unnamed_addr constant [5 x i8] c"null\00", align 1
@str.38 = private unnamed_addr constant [11 x i8] c"Base: null\00", align 1
@str.39 = private unnamed_addr constant [27 x i8] c"\0A\1B[34mChecking blocks\1B[0m.\00", align 1

; Function Attrs: nounwind ssp uwtable
define i32 @main(i32, i8** nocapture readnone) local_unnamed_addr #0 {
  %3 = tail call i32 @puts(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @str, i64 0, i64 0))
  %4 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.1, i64 0, i64 0), i64 24)
  %5 = tail call i32 @mem_init(i32 1048576) #4
  %6 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %7 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.2, i64 0, i64 0), i64 %6)
  %8 = tail call %struct.block_meta* @find_free_block(%struct.block_meta** nonnull @last_block, i64 0) #4
  %9 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.26, i64 0, i64 0), i64 0, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %10 = icmp eq %struct.block_meta* %8, null
  br i1 %10, label %16, label %11

; <label>:11:                                     ; preds = %2
  %12 = ptrtoint %struct.block_meta* %8 to i64
  %13 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %14 = sub nsw i64 %12, %13
  %15 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %14) #4
  br label %18

; <label>:16:                                     ; preds = %2
  %17 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %18

; <label>:18:                                     ; preds = %11, %16
  %19 = tail call i32 @putchar(i32 10) #4
  %20 = load i64, i64* bitcast (i8** @end to i64*), align 8, !tbaa !4
  %21 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %22 = sub nsw i64 %20, %21
  %23 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.23, i64 0, i64 0), i64 %22) #4
  %24 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %25 = icmp eq %struct.block_meta* %24, null
  br i1 %25, label %26, label %28

; <label>:26:                                     ; preds = %18
  %27 = tail call i32 @puts(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @str.38, i64 0, i64 0)) #4
  br label %33

; <label>:28:                                     ; preds = %18
  %29 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %30 = ptrtoint %struct.block_meta* %24 to i64
  %31 = sub i64 %30, %29
  %32 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.25, i64 0, i64 0), i64 %31) #4
  br label %33

; <label>:33:                                     ; preds = %26, %28
  %34 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 800, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %35 = tail call i8* @mal(i64 800) #4
  %36 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.3, i64 0, i64 0)) #4
  %37 = icmp eq i8* %35, null
  br i1 %37, label %38, label %40

; <label>:38:                                     ; preds = %33
  %39 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %45

; <label>:40:                                     ; preds = %33
  %41 = ptrtoint i8* %35 to i64
  %42 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %43 = sub nsw i64 %41, %42
  %44 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %43) #4
  br label %45

; <label>:45:                                     ; preds = %38, %40
  %46 = tail call i32 @putchar(i32 10) #4
  %47 = load i64, i64* bitcast (i8** @end to i64*), align 8, !tbaa !4
  %48 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %49 = sub nsw i64 %47, %48
  %50 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.23, i64 0, i64 0), i64 %49) #4
  %51 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %52 = icmp eq %struct.block_meta* %51, null
  br i1 %52, label %53, label %55

; <label>:53:                                     ; preds = %45
  %54 = tail call i32 @puts(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @str.38, i64 0, i64 0)) #4
  br label %60

; <label>:55:                                     ; preds = %45
  %56 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %57 = ptrtoint %struct.block_meta* %51 to i64
  %58 = sub i64 %57, %56
  %59 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.25, i64 0, i64 0), i64 %58) #4
  br label %60

; <label>:60:                                     ; preds = %53, %55
  %61 = tail call %struct.block_meta* @find_free_block(%struct.block_meta** nonnull @last_block, i64 100) #4
  %62 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.26, i64 0, i64 0), i64 100, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %63 = icmp eq %struct.block_meta* %61, null
  br i1 %63, label %69, label %64

; <label>:64:                                     ; preds = %60
  %65 = ptrtoint %struct.block_meta* %61 to i64
  %66 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %67 = sub nsw i64 %65, %66
  %68 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %67) #4
  br label %71

; <label>:69:                                     ; preds = %60
  %70 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %71

; <label>:71:                                     ; preds = %64, %69
  tail call void @dbg_blocks()
  %72 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 150, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %73 = tail call i8* @mal(i64 150) #4
  %74 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.4, i64 0, i64 0)) #4
  %75 = icmp eq i8* %73, null
  br i1 %75, label %76, label %78

; <label>:76:                                     ; preds = %71
  %77 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %83

; <label>:78:                                     ; preds = %71
  %79 = ptrtoint i8* %73 to i64
  %80 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %81 = sub nsw i64 %79, %80
  %82 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %81) #4
  br label %83

; <label>:83:                                     ; preds = %76, %78
  %84 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 10, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %85 = tail call i8* @mal(i64 10) #4
  %86 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.5, i64 0, i64 0)) #4
  %87 = icmp eq i8* %85, null
  br i1 %87, label %88, label %90

; <label>:88:                                     ; preds = %83
  %89 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %95

; <label>:90:                                     ; preds = %83
  %91 = ptrtoint i8* %85 to i64
  %92 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %93 = sub nsw i64 %91, %92
  %94 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %93) #4
  br label %95

; <label>:95:                                     ; preds = %88, %90
  tail call void @dbg_blocks()
  tail call void @fr(i8* %73) #4
  tail call void @dbg_blocks()
  %96 = tail call i32 @putchar(i32 10)
  %97 = tail call %struct.block_meta* @find_free_block(%struct.block_meta** nonnull @last_block, i64 5) #4
  %98 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.26, i64 0, i64 0), i64 5, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %99 = icmp eq %struct.block_meta* %97, null
  br i1 %99, label %105, label %100

; <label>:100:                                    ; preds = %95
  %101 = ptrtoint %struct.block_meta* %97 to i64
  %102 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %103 = sub nsw i64 %101, %102
  %104 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %103) #4
  br label %107

; <label>:105:                                    ; preds = %95
  %106 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %107

; <label>:107:                                    ; preds = %100, %105
  %108 = tail call %struct.block_meta* @find_free_block(%struct.block_meta** nonnull @last_block, i64 100) #4
  %109 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.26, i64 0, i64 0), i64 100, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %110 = icmp eq %struct.block_meta* %108, null
  br i1 %110, label %116, label %111

; <label>:111:                                    ; preds = %107
  %112 = ptrtoint %struct.block_meta* %108 to i64
  %113 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %114 = sub nsw i64 %112, %113
  %115 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %114) #4
  br label %118

; <label>:116:                                    ; preds = %107
  %117 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %118

; <label>:118:                                    ; preds = %111, %116
  %119 = tail call %struct.block_meta* @find_free_block(%struct.block_meta** nonnull @last_block, i64 200) #4
  %120 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.26, i64 0, i64 0), i64 200, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %121 = icmp eq %struct.block_meta* %119, null
  br i1 %121, label %127, label %122

; <label>:122:                                    ; preds = %118
  %123 = ptrtoint %struct.block_meta* %119 to i64
  %124 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %125 = sub nsw i64 %123, %124
  %126 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %125) #4
  br label %129

; <label>:127:                                    ; preds = %118
  %128 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %129

; <label>:129:                                    ; preds = %122, %127
  %130 = tail call %struct.block_meta* @find_free_block(%struct.block_meta** nonnull @last_block, i64 601) #4
  %131 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.26, i64 0, i64 0), i64 601, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %132 = icmp eq %struct.block_meta* %130, null
  br i1 %132, label %138, label %133

; <label>:133:                                    ; preds = %129
  %134 = ptrtoint %struct.block_meta* %130 to i64
  %135 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %136 = sub nsw i64 %134, %135
  %137 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %136) #4
  br label %140

; <label>:138:                                    ; preds = %129
  %139 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %140

; <label>:140:                                    ; preds = %133, %138
  %141 = tail call i32 @putchar(i32 10) #4
  %142 = load i64, i64* bitcast (i8** @end to i64*), align 8, !tbaa !4
  %143 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %144 = sub nsw i64 %142, %143
  %145 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.23, i64 0, i64 0), i64 %144) #4
  %146 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %147 = icmp eq %struct.block_meta* %146, null
  br i1 %147, label %148, label %150

; <label>:148:                                    ; preds = %140
  %149 = tail call i32 @puts(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @str.38, i64 0, i64 0)) #4
  br label %155

; <label>:150:                                    ; preds = %140
  %151 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %152 = ptrtoint %struct.block_meta* %146 to i64
  %153 = sub i64 %152, %151
  %154 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.25, i64 0, i64 0), i64 %153) #4
  br label %155

; <label>:155:                                    ; preds = %148, %150
  %156 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 200, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %157 = tail call i8* @mal(i64 200) #4
  %158 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.7, i64 0, i64 0)) #4
  %159 = icmp eq i8* %157, null
  br i1 %159, label %160, label %162

; <label>:160:                                    ; preds = %155
  %161 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %167

; <label>:162:                                    ; preds = %155
  %163 = ptrtoint i8* %157 to i64
  %164 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %165 = sub nsw i64 %163, %164
  %166 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %165) #4
  br label %167

; <label>:167:                                    ; preds = %160, %162
  %168 = tail call i32 @putchar(i32 10) #4
  %169 = load i64, i64* bitcast (i8** @end to i64*), align 8, !tbaa !4
  %170 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %171 = sub nsw i64 %169, %170
  %172 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.23, i64 0, i64 0), i64 %171) #4
  %173 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %174 = icmp eq %struct.block_meta* %173, null
  br i1 %174, label %175, label %177

; <label>:175:                                    ; preds = %167
  %176 = tail call i32 @puts(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @str.38, i64 0, i64 0)) #4
  br label %182

; <label>:177:                                    ; preds = %167
  %178 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %179 = ptrtoint %struct.block_meta* %173 to i64
  %180 = sub i64 %179, %178
  %181 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.25, i64 0, i64 0), i64 %180) #4
  br label %182

; <label>:182:                                    ; preds = %175, %177
  tail call void @dbg_blocks()
  %183 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 100, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %184 = tail call i8* @mal(i64 100) #4
  %185 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.8, i64 0, i64 0)) #4
  %186 = icmp eq i8* %184, null
  br i1 %186, label %187, label %189

; <label>:187:                                    ; preds = %182
  %188 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %194

; <label>:189:                                    ; preds = %182
  %190 = ptrtoint i8* %184 to i64
  %191 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %192 = sub nsw i64 %190, %191
  %193 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %192) #4
  br label %194

; <label>:194:                                    ; preds = %187, %189
  tail call void @dbg_blocks()
  %195 = tail call i32 @puts(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @str.33, i64 0, i64 0))
  tail call void @fr(i8* %157) #4
  tail call void @fr(i8* %85) #4
  tail call void @dbg_blocks()
  %196 = tail call i32 (...) @merge_blocks() #4
  tail call void @dbg_blocks()
  %197 = tail call i32 @puts(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @str.34, i64 0, i64 0))
  tail call void @fr(i8* %184) #4
  tail call void @fr(i8* %35) #4
  tail call void @dbg_blocks()
  %198 = tail call i32 (...) @merge_blocks() #4
  tail call void @dbg_blocks()
  %199 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 600, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %200 = tail call i8* @mal(i64 600) #4
  %201 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.11, i64 0, i64 0)) #4
  %202 = icmp eq i8* %200, null
  br i1 %202, label %203, label %205

; <label>:203:                                    ; preds = %194
  %204 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %210

; <label>:205:                                    ; preds = %194
  %206 = ptrtoint i8* %200 to i64
  %207 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %208 = sub nsw i64 %206, %207
  %209 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %208) #4
  br label %210

; <label>:210:                                    ; preds = %203, %205
  tail call void @dbg_blocks()
  %211 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 1000, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %212 = tail call i8* @mal(i64 1000) #4
  %213 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.12, i64 0, i64 0)) #4
  %214 = icmp eq i8* %212, null
  br i1 %214, label %215, label %217

; <label>:215:                                    ; preds = %210
  %216 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %222

; <label>:217:                                    ; preds = %210
  %218 = ptrtoint i8* %212 to i64
  %219 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %220 = sub nsw i64 %218, %219
  %221 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %220) #4
  br label %222

; <label>:222:                                    ; preds = %215, %217
  tail call void @dbg_blocks()
  %223 = tail call i32 @puts(i8* getelementptr inbounds ([32 x i8], [32 x i8]* @str.35, i64 0, i64 0))
  tail call void @fr(i8* %200) #4
  tail call void @fr(i8* %212) #4
  tail call void @dbg_blocks()
  %224 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 300, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %225 = tail call i8* @mal(i64 300) #4
  %226 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.14, i64 0, i64 0)) #4
  %227 = icmp eq i8* %225, null
  br i1 %227, label %228, label %230

; <label>:228:                                    ; preds = %222
  %229 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %235

; <label>:230:                                    ; preds = %222
  %231 = ptrtoint i8* %225 to i64
  %232 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %233 = sub nsw i64 %231, %232
  %234 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %233) #4
  br label %235

; <label>:235:                                    ; preds = %228, %230
  tail call void @dbg_blocks()
  %236 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 233, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %237 = tail call i8* @mal(i64 233) #4
  %238 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.15, i64 0, i64 0)) #4
  %239 = icmp eq i8* %237, null
  br i1 %239, label %240, label %242

; <label>:240:                                    ; preds = %235
  %241 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %247

; <label>:242:                                    ; preds = %235
  %243 = ptrtoint i8* %237 to i64
  %244 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %245 = sub nsw i64 %243, %244
  %246 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %245) #4
  br label %247

; <label>:247:                                    ; preds = %240, %242
  tail call void @dbg_blocks()
  %248 = tail call i32 (...) @merge_blocks() #4
  tail call void @dbg_blocks()
  %249 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 600, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)) #4
  %250 = tail call i8* @mal(i64 600) #4
  %251 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.16, i64 0, i64 0)) #4
  %252 = icmp eq i8* %250, null
  br i1 %252, label %253, label %255

; <label>:253:                                    ; preds = %247
  %254 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0)) #4
  br label %260

; <label>:255:                                    ; preds = %247
  %256 = ptrtoint i8* %250 to i64
  %257 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %258 = sub nsw i64 %256, %257
  %259 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %258) #4
  br label %260

; <label>:260:                                    ; preds = %253, %255
  tail call void @dbg_blocks()
  ret i32 0
}

; Function Attrs: nounwind
declare i32 @printf(i8* nocapture readonly, ...) local_unnamed_addr #1

declare i32 @mem_init(i32) local_unnamed_addr #2

; Function Attrs: nounwind ssp uwtable
define void @check_free(i64) local_unnamed_addr #0 {
  %2 = tail call %struct.block_meta* @find_free_block(%struct.block_meta** nonnull @last_block, i64 %0) #4
  %3 = icmp eq i64 %0, 1
  %4 = select i1 %3, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.18, i64 0, i64 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)
  %5 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.26, i64 0, i64 0), i64 %0, i8* %4)
  %6 = icmp eq %struct.block_meta* %2, null
  br i1 %6, label %12, label %7

; <label>:7:                                      ; preds = %1
  %8 = ptrtoint %struct.block_meta* %2 to i64
  %9 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %10 = sub nsw i64 %8, %9
  %11 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %10)
  br label %14

; <label>:12:                                     ; preds = %1
  %13 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0))
  br label %14

; <label>:14:                                     ; preds = %12, %7
  ret void
}

; Function Attrs: nounwind ssp uwtable
define i32* @allocate(i64, i8*) local_unnamed_addr #0 {
  %3 = icmp eq i64 %0, 1
  %4 = select i1 %3, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.18, i64 0, i64 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)
  %5 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.17, i64 0, i64 0), i64 %0, i8* %4)
  %6 = tail call i8* @mal(i64 %0) #4
  %7 = bitcast i8* %6 to i32*
  %8 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.20, i64 0, i64 0), i8* %1)
  %9 = icmp eq i8* %6, null
  br i1 %9, label %10, label %12

; <label>:10:                                     ; preds = %2
  %11 = tail call i32 @puts(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @str.37, i64 0, i64 0))
  br label %17

; <label>:12:                                     ; preds = %2
  %13 = ptrtoint i8* %6 to i64
  %14 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %15 = sub nsw i64 %13, %14
  %16 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.22, i64 0, i64 0), i64 %15)
  br label %17

; <label>:17:                                     ; preds = %12, %10
  ret i32* %7
}

declare void @fr(i8*) local_unnamed_addr #2

declare i32 @merge_blocks(...) local_unnamed_addr #2

declare i8* @mal(i64) local_unnamed_addr #2

; Function Attrs: nounwind ssp uwtable
define void @dbg() local_unnamed_addr #0 {
  %1 = tail call i32 @putchar(i32 10)
  %2 = load i64, i64* bitcast (i8** @end to i64*), align 8, !tbaa !4
  %3 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %4 = sub nsw i64 %2, %3
  %5 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.23, i64 0, i64 0), i64 %4)
  %6 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %7 = icmp eq %struct.block_meta* %6, null
  br i1 %7, label %8, label %10

; <label>:8:                                      ; preds = %0
  %9 = tail call i32 @puts(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @str.38, i64 0, i64 0))
  br label %15

; <label>:10:                                     ; preds = %0
  %11 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %12 = ptrtoint %struct.block_meta* %6 to i64
  %13 = sub i64 %12, %11
  %14 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.25, i64 0, i64 0), i64 %13)
  br label %15

; <label>:15:                                     ; preds = %10, %8
  ret void
}

declare %struct.block_meta* @find_free_block(%struct.block_meta**, i64) local_unnamed_addr #2

; Function Attrs: nounwind ssp uwtable
define void @dbg_blocks() local_unnamed_addr #0 {
  %1 = load %struct.block_meta*, %struct.block_meta** @global_base, align 8, !tbaa !4
  %2 = tail call i32 @puts(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @str.39, i64 0, i64 0))
  %3 = icmp eq %struct.block_meta* %1, null
  br i1 %3, label %32, label %4

; <label>:4:                                      ; preds = %0, %23
  %5 = phi i32 [ %24, %23 ], [ 0, %0 ]
  %6 = phi %struct.block_meta* [ %26, %23 ], [ %1, %0 ]
  %7 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %6, i64 0, i32 2
  %8 = load i32, i32* %7, align 8, !tbaa !8
  %9 = icmp eq i32 %8, 0
  %10 = select i1 %9, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.30, i64 0, i64 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.29, i64 0, i64 0)
  %11 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %6, i64 0, i32 0
  %12 = load i64, i64* %11, align 8, !tbaa !12
  %13 = ptrtoint %struct.block_meta* %6 to i64
  %14 = load i64, i64* bitcast (i32** @memory to i64*), align 8, !tbaa !4
  %15 = sub nsw i64 %13, %14
  %16 = add i64 %12, 24
  %17 = add i64 %16, %15
  %18 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([60 x i8], [60 x i8]* @.str.28, i64 0, i64 0), i8* %10, i64 %12, i64 %15, i64 %17)
  %19 = icmp eq i32 %5, 20
  br i1 %19, label %20, label %23

; <label>:20:                                     ; preds = %4
  %21 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8, !tbaa !4
  %22 = tail call i64 @fwrite(i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.31, i64 0, i64 0), i64 20, i64 1, %struct.__sFILE* %21)
  tail call void @exit(i32 1) #5
  unreachable

; <label>:23:                                     ; preds = %4
  %24 = add nuw nsw i32 %5, 1
  %25 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %6, i64 0, i32 1
  %26 = load %struct.block_meta*, %struct.block_meta** %25, align 8, !tbaa !13
  %27 = icmp eq %struct.block_meta* %26, null
  br i1 %27, label %28, label %4

; <label>:28:                                     ; preds = %23
  %29 = icmp eq i32 %5, 0
  %30 = select i1 %29, i32 1, i32 %24
  %31 = select i1 %29, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.18, i64 0, i64 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0)
  br label %32

; <label>:32:                                     ; preds = %28, %0
  %33 = phi i32 [ 0, %0 ], [ %30, %28 ]
  %34 = phi i8* [ getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i64 0, i64 0), %0 ], [ %31, %28 ]
  %35 = tail call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.32, i64 0, i64 0), i32 %33, i8* nonnull %34)
  ret void
}

; Function Attrs: noreturn
declare void @exit(i32) local_unnamed_addr #3

; Function Attrs: nounwind
declare i32 @puts(i8* nocapture readonly) local_unnamed_addr #4

; Function Attrs: nounwind
declare i32 @putchar(i32) local_unnamed_addr #4

; Function Attrs: nounwind
declare i64 @fwrite(i8* nocapture, i64, i64, %struct.__sFILE* nocapture) local_unnamed_addr #4

attributes #0 = { nounwind ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }
attributes #5 = { noreturn nounwind }

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
