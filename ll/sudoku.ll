; ModuleID = 'sudoku.c'
source_filename = "sudoku.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }
%struct.sdaux_t = type { [324 x [9 x i16]], [729 x [4 x i16]] }

@__stdinp = external global %struct.__sFILE*, align 8

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.sdaux_t* @sd_genmat() #0 {
  %1 = alloca %struct.sdaux_t*, align 8
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca [324 x i8], align 16
  %10 = call i8* @calloc(i64 1, i64 11664) #3
  %11 = bitcast i8* %10 to %struct.sdaux_t*
  store %struct.sdaux_t* %11, %struct.sdaux_t** %1, align 8
  store i32 0, i32* %5, align 4
  store i32 0, i32* %2, align 4
  br label %12

; <label>:12:                                     ; preds = %86, %0
  %13 = load i32, i32* %2, align 4
  %14 = icmp slt i32 %13, 9
  br i1 %14, label %15, label %89

; <label>:15:                                     ; preds = %12
  store i32 0, i32* %3, align 4
  br label %16

; <label>:16:                                     ; preds = %82, %15
  %17 = load i32, i32* %3, align 4
  %18 = icmp slt i32 %17, 9
  br i1 %18, label %19, label %85

; <label>:19:                                     ; preds = %16
  store i32 0, i32* %4, align 4
  br label %20

; <label>:20:                                     ; preds = %78, %19
  %21 = load i32, i32* %4, align 4
  %22 = icmp slt i32 %21, 9
  br i1 %22, label %23, label %81

; <label>:23:                                     ; preds = %20
  %24 = load i32, i32* %2, align 4
  %25 = mul nsw i32 9, %24
  %26 = load i32, i32* %3, align 4
  %27 = add nsw i32 %25, %26
  %28 = trunc i32 %27 to i16
  %29 = load %struct.sdaux_t*, %struct.sdaux_t** %1, align 8
  %30 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %29, i32 0, i32 1
  %31 = load i32, i32* %5, align 4
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds [729 x [4 x i16]], [729 x [4 x i16]]* %30, i64 0, i64 %32
  %34 = getelementptr inbounds [4 x i16], [4 x i16]* %33, i64 0, i64 0
  store i16 %28, i16* %34, align 2
  %35 = load i32, i32* %2, align 4
  %36 = sdiv i32 %35, 3
  %37 = mul nsw i32 %36, 3
  %38 = load i32, i32* %3, align 4
  %39 = sdiv i32 %38, 3
  %40 = add nsw i32 %37, %39
  %41 = mul nsw i32 %40, 9
  %42 = load i32, i32* %4, align 4
  %43 = add nsw i32 %41, %42
  %44 = add nsw i32 %43, 81
  %45 = trunc i32 %44 to i16
  %46 = load %struct.sdaux_t*, %struct.sdaux_t** %1, align 8
  %47 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %46, i32 0, i32 1
  %48 = load i32, i32* %5, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds [729 x [4 x i16]], [729 x [4 x i16]]* %47, i64 0, i64 %49
  %51 = getelementptr inbounds [4 x i16], [4 x i16]* %50, i64 0, i64 1
  store i16 %45, i16* %51, align 2
  %52 = load i32, i32* %2, align 4
  %53 = mul nsw i32 9, %52
  %54 = load i32, i32* %4, align 4
  %55 = add nsw i32 %53, %54
  %56 = add nsw i32 %55, 162
  %57 = trunc i32 %56 to i16
  %58 = load %struct.sdaux_t*, %struct.sdaux_t** %1, align 8
  %59 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %58, i32 0, i32 1
  %60 = load i32, i32* %5, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds [729 x [4 x i16]], [729 x [4 x i16]]* %59, i64 0, i64 %61
  %63 = getelementptr inbounds [4 x i16], [4 x i16]* %62, i64 0, i64 2
  store i16 %57, i16* %63, align 2
  %64 = load i32, i32* %3, align 4
  %65 = mul nsw i32 9, %64
  %66 = load i32, i32* %4, align 4
  %67 = add nsw i32 %65, %66
  %68 = add nsw i32 %67, 243
  %69 = trunc i32 %68 to i16
  %70 = load %struct.sdaux_t*, %struct.sdaux_t** %1, align 8
  %71 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %70, i32 0, i32 1
  %72 = load i32, i32* %5, align 4
  %73 = sext i32 %72 to i64
  %74 = getelementptr inbounds [729 x [4 x i16]], [729 x [4 x i16]]* %71, i64 0, i64 %73
  %75 = getelementptr inbounds [4 x i16], [4 x i16]* %74, i64 0, i64 3
  store i16 %69, i16* %75, align 2
  %76 = load i32, i32* %5, align 4
  %77 = add nsw i32 %76, 1
  store i32 %77, i32* %5, align 4
  br label %78

; <label>:78:                                     ; preds = %23
  %79 = load i32, i32* %4, align 4
  %80 = add nsw i32 %79, 1
  store i32 %80, i32* %4, align 4
  br label %20

; <label>:81:                                     ; preds = %20
  br label %82

; <label>:82:                                     ; preds = %81
  %83 = load i32, i32* %3, align 4
  %84 = add nsw i32 %83, 1
  store i32 %84, i32* %3, align 4
  br label %16

; <label>:85:                                     ; preds = %16
  br label %86

; <label>:86:                                     ; preds = %85
  %87 = load i32, i32* %2, align 4
  %88 = add nsw i32 %87, 1
  store i32 %88, i32* %2, align 4
  br label %12

; <label>:89:                                     ; preds = %12
  store i32 0, i32* %6, align 4
  br label %90

; <label>:90:                                     ; preds = %97, %89
  %91 = load i32, i32* %6, align 4
  %92 = icmp slt i32 %91, 324
  br i1 %92, label %93, label %100

; <label>:93:                                     ; preds = %90
  %94 = load i32, i32* %6, align 4
  %95 = sext i32 %94 to i64
  %96 = getelementptr inbounds [324 x i8], [324 x i8]* %9, i64 0, i64 %95
  store i8 0, i8* %96, align 1
  br label %97

; <label>:97:                                     ; preds = %93
  %98 = load i32, i32* %6, align 4
  %99 = add nsw i32 %98, 1
  store i32 %99, i32* %6, align 4
  br label %90

; <label>:100:                                    ; preds = %90
  store i32 0, i32* %5, align 4
  br label %101

; <label>:101:                                    ; preds = %137, %100
  %102 = load i32, i32* %5, align 4
  %103 = icmp slt i32 %102, 729
  br i1 %103, label %104, label %140

; <label>:104:                                    ; preds = %101
  store i32 0, i32* %7, align 4
  br label %105

; <label>:105:                                    ; preds = %133, %104
  %106 = load i32, i32* %7, align 4
  %107 = icmp slt i32 %106, 4
  br i1 %107, label %108, label %136

; <label>:108:                                    ; preds = %105
  %109 = load %struct.sdaux_t*, %struct.sdaux_t** %1, align 8
  %110 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %109, i32 0, i32 1
  %111 = load i32, i32* %5, align 4
  %112 = sext i32 %111 to i64
  %113 = getelementptr inbounds [729 x [4 x i16]], [729 x [4 x i16]]* %110, i64 0, i64 %112
  %114 = load i32, i32* %7, align 4
  %115 = sext i32 %114 to i64
  %116 = getelementptr inbounds [4 x i16], [4 x i16]* %113, i64 0, i64 %115
  %117 = load i16, i16* %116, align 2
  %118 = zext i16 %117 to i32
  store i32 %118, i32* %4, align 4
  %119 = load i32, i32* %5, align 4
  %120 = trunc i32 %119 to i16
  %121 = load %struct.sdaux_t*, %struct.sdaux_t** %1, align 8
  %122 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %121, i32 0, i32 0
  %123 = load i32, i32* %4, align 4
  %124 = sext i32 %123 to i64
  %125 = getelementptr inbounds [324 x [9 x i16]], [324 x [9 x i16]]* %122, i64 0, i64 %124
  %126 = load i32, i32* %4, align 4
  %127 = sext i32 %126 to i64
  %128 = getelementptr inbounds [324 x i8], [324 x i8]* %9, i64 0, i64 %127
  %129 = load i8, i8* %128, align 1
  %130 = add i8 %129, 1
  store i8 %130, i8* %128, align 1
  %131 = sext i8 %129 to i64
  %132 = getelementptr inbounds [9 x i16], [9 x i16]* %125, i64 0, i64 %131
  store i16 %120, i16* %132, align 2
  br label %133

; <label>:133:                                    ; preds = %108
  %134 = load i32, i32* %7, align 4
  %135 = add nsw i32 %134, 1
  store i32 %135, i32* %7, align 4
  br label %105

; <label>:136:                                    ; preds = %105
  br label %137

; <label>:137:                                    ; preds = %136
  %138 = load i32, i32* %5, align 4
  %139 = add nsw i32 %138, 1
  store i32 %139, i32* %5, align 4
  br label %101

; <label>:140:                                    ; preds = %101
  %141 = load %struct.sdaux_t*, %struct.sdaux_t** %1, align 8
  ret %struct.sdaux_t* %141
}

; Function Attrs: allocsize(0,1)
declare i8* @calloc(i64, i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @sd_solve(%struct.sdaux_t*, i8*) #0 {
  %3 = alloca %struct.sdaux_t*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca [729 x i8], align 16
  %16 = alloca [81 x i8], align 16
  %17 = alloca [324 x i8], align 16
  %18 = alloca [81 x i16], align 16
  %19 = alloca [82 x i8], align 16
  %20 = alloca i32, align 4
  store %struct.sdaux_t* %0, %struct.sdaux_t** %3, align 8
  store i8* %1, i8** %4, align 8
  store i32 0, i32* %12, align 4
  store i32 0, i32* %14, align 4
  store i32 0, i32* %7, align 4
  br label %21

; <label>:21:                                     ; preds = %28, %2
  %22 = load i32, i32* %7, align 4
  %23 = icmp slt i32 %22, 729
  br i1 %23, label %24, label %31

; <label>:24:                                     ; preds = %21
  %25 = load i32, i32* %7, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [729 x i8], [729 x i8]* %15, i64 0, i64 %26
  store i8 0, i8* %27, align 1
  br label %28

; <label>:28:                                     ; preds = %24
  %29 = load i32, i32* %7, align 4
  %30 = add nsw i32 %29, 1
  store i32 %30, i32* %7, align 4
  br label %21

; <label>:31:                                     ; preds = %21
  store i32 0, i32* %8, align 4
  br label %32

; <label>:32:                                     ; preds = %39, %31
  %33 = load i32, i32* %8, align 4
  %34 = icmp slt i32 %33, 324
  br i1 %34, label %35, label %42

; <label>:35:                                     ; preds = %32
  %36 = load i32, i32* %8, align 4
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds [324 x i8], [324 x i8]* %17, i64 0, i64 %37
  store i8 9, i8* %38, align 1
  br label %39

; <label>:39:                                     ; preds = %35
  %40 = load i32, i32* %8, align 4
  %41 = add nsw i32 %40, 1
  store i32 %41, i32* %8, align 4
  br label %32

; <label>:42:                                     ; preds = %32
  store i32 0, i32* %5, align 4
  br label %43

; <label>:43:                                     ; preds = %105, %42
  %44 = load i32, i32* %5, align 4
  %45 = icmp slt i32 %44, 81
  br i1 %45, label %46, label %108

; <label>:46:                                     ; preds = %43
  %47 = load i8*, i8** %4, align 8
  %48 = load i32, i32* %5, align 4
  %49 = sext i32 %48 to i64
  %50 = getelementptr inbounds i8, i8* %47, i64 %49
  %51 = load i8, i8* %50, align 1
  %52 = sext i8 %51 to i32
  %53 = icmp sge i32 %52, 49
  br i1 %53, label %54, label %70

; <label>:54:                                     ; preds = %46
  %55 = load i8*, i8** %4, align 8
  %56 = load i32, i32* %5, align 4
  %57 = sext i32 %56 to i64
  %58 = getelementptr inbounds i8, i8* %55, i64 %57
  %59 = load i8, i8* %58, align 1
  %60 = sext i8 %59 to i32
  %61 = icmp sle i32 %60, 57
  br i1 %61, label %62, label %70

; <label>:62:                                     ; preds = %54
  %63 = load i8*, i8** %4, align 8
  %64 = load i32, i32* %5, align 4
  %65 = sext i32 %64 to i64
  %66 = getelementptr inbounds i8, i8* %63, i64 %65
  %67 = load i8, i8* %66, align 1
  %68 = sext i8 %67 to i32
  %69 = sub nsw i32 %68, 49
  br label %71

; <label>:70:                                     ; preds = %54, %46
  br label %71

; <label>:71:                                     ; preds = %70, %62
  %72 = phi i32 [ %69, %62 ], [ -1, %70 ]
  store i32 %72, i32* %20, align 4
  %73 = load i32, i32* %20, align 4
  %74 = icmp sge i32 %73, 0
  br i1 %74, label %75, label %84

; <label>:75:                                     ; preds = %71
  %76 = load %struct.sdaux_t*, %struct.sdaux_t** %3, align 8
  %77 = getelementptr inbounds [729 x i8], [729 x i8]* %15, i32 0, i32 0
  %78 = getelementptr inbounds [324 x i8], [324 x i8]* %17, i32 0, i32 0
  %79 = load i32, i32* %5, align 4
  %80 = mul nsw i32 %79, 9
  %81 = load i32, i32* %20, align 4
  %82 = add nsw i32 %80, %81
  %83 = call i32 @sd_update(%struct.sdaux_t* %76, i8* %77, i8* %78, i32 %82, i32 1)
  br label %84

; <label>:84:                                     ; preds = %75, %71
  %85 = load i32, i32* %20, align 4
  %86 = icmp sge i32 %85, 0
  br i1 %86, label %87, label %90

; <label>:87:                                     ; preds = %84
  %88 = load i32, i32* %14, align 4
  %89 = add nsw i32 %88, 1
  store i32 %89, i32* %14, align 4
  br label %90

; <label>:90:                                     ; preds = %87, %84
  %91 = load i32, i32* %5, align 4
  %92 = sext i32 %91 to i64
  %93 = getelementptr inbounds [81 x i16], [81 x i16]* %18, i64 0, i64 %92
  store i16 -1, i16* %93, align 2
  %94 = load i32, i32* %5, align 4
  %95 = sext i32 %94 to i64
  %96 = getelementptr inbounds [81 x i8], [81 x i8]* %16, i64 0, i64 %95
  store i8 -1, i8* %96, align 1
  %97 = load i8*, i8** %4, align 8
  %98 = load i32, i32* %5, align 4
  %99 = sext i32 %98 to i64
  %100 = getelementptr inbounds i8, i8* %97, i64 %99
  %101 = load i8, i8* %100, align 1
  %102 = load i32, i32* %5, align 4
  %103 = sext i32 %102 to i64
  %104 = getelementptr inbounds [82 x i8], [82 x i8]* %19, i64 0, i64 %103
  store i8 %101, i8* %104, align 1
  br label %105

; <label>:105:                                    ; preds = %90
  %106 = load i32, i32* %5, align 4
  %107 = add nsw i32 %106, 1
  store i32 %107, i32* %5, align 4
  br label %43

; <label>:108:                                    ; preds = %43
  store i32 0, i32* %5, align 4
  store i32 1, i32* %10, align 4
  store i32 655360, i32* %11, align 4
  %109 = getelementptr inbounds [82 x i8], [82 x i8]* %19, i64 0, i64 81
  store i8 0, i8* %109, align 1
  br label %110

; <label>:110:                                    ; preds = %309, %108
  br label %111

; <label>:111:                                    ; preds = %271, %110
  %112 = load i32, i32* %5, align 4
  %113 = icmp sge i32 %112, 0
  br i1 %113, label %114, label %119

; <label>:114:                                    ; preds = %111
  %115 = load i32, i32* %5, align 4
  %116 = load i32, i32* %14, align 4
  %117 = sub nsw i32 81, %116
  %118 = icmp slt i32 %115, %117
  br label %119

; <label>:119:                                    ; preds = %114, %111
  %120 = phi i1 [ false, %111 ], [ %118, %114 ]
  br i1 %120, label %121, label %272

; <label>:121:                                    ; preds = %119
  %122 = load i32, i32* %10, align 4
  %123 = icmp eq i32 %122, 1
  br i1 %123, label %124, label %179

; <label>:124:                                    ; preds = %121
  %125 = load i32, i32* %11, align 4
  %126 = ashr i32 %125, 16
  store i32 %126, i32* %13, align 4
  %127 = load i32, i32* %11, align 4
  %128 = and i32 %127, 65535
  %129 = trunc i32 %128 to i16
  %130 = load i32, i32* %5, align 4
  %131 = sext i32 %130 to i64
  %132 = getelementptr inbounds [81 x i16], [81 x i16]* %18, i64 0, i64 %131
  store i16 %129, i16* %132, align 2
  %133 = load i32, i32* %13, align 4
  %134 = icmp sgt i32 %133, 1
  br i1 %134, label %135, label %167

; <label>:135:                                    ; preds = %124
  store i32 0, i32* %8, align 4
  br label %136

; <label>:136:                                    ; preds = %163, %135
  %137 = load i32, i32* %8, align 4
  %138 = icmp slt i32 %137, 324
  br i1 %138, label %139, label %166

; <label>:139:                                    ; preds = %136
  %140 = load i32, i32* %8, align 4
  %141 = sext i32 %140 to i64
  %142 = getelementptr inbounds [324 x i8], [324 x i8]* %17, i64 0, i64 %141
  %143 = load i8, i8* %142, align 1
  %144 = zext i8 %143 to i32
  %145 = load i32, i32* %13, align 4
  %146 = icmp slt i32 %144, %145
  br i1 %146, label %147, label %162

; <label>:147:                                    ; preds = %139
  %148 = load i32, i32* %8, align 4
  %149 = sext i32 %148 to i64
  %150 = getelementptr inbounds [324 x i8], [324 x i8]* %17, i64 0, i64 %149
  %151 = load i8, i8* %150, align 1
  %152 = zext i8 %151 to i32
  store i32 %152, i32* %13, align 4
  %153 = load i32, i32* %8, align 4
  %154 = trunc i32 %153 to i16
  %155 = load i32, i32* %5, align 4
  %156 = sext i32 %155 to i64
  %157 = getelementptr inbounds [81 x i16], [81 x i16]* %18, i64 0, i64 %156
  store i16 %154, i16* %157, align 2
  %158 = load i32, i32* %13, align 4
  %159 = icmp sle i32 %158, 1
  br i1 %159, label %160, label %161

; <label>:160:                                    ; preds = %147
  br label %166

; <label>:161:                                    ; preds = %147
  br label %162

; <label>:162:                                    ; preds = %161, %139
  br label %163

; <label>:163:                                    ; preds = %162
  %164 = load i32, i32* %8, align 4
  %165 = add nsw i32 %164, 1
  store i32 %165, i32* %8, align 4
  br label %136

; <label>:166:                                    ; preds = %160, %136
  br label %167

; <label>:167:                                    ; preds = %166, %124
  %168 = load i32, i32* %13, align 4
  %169 = icmp eq i32 %168, 0
  br i1 %169, label %173, label %170

; <label>:170:                                    ; preds = %167
  %171 = load i32, i32* %13, align 4
  %172 = icmp eq i32 %171, 10
  br i1 %172, label %173, label %178

; <label>:173:                                    ; preds = %170, %167
  store i32 -1, i32* %10, align 4
  %174 = load i32, i32* %5, align 4
  %175 = add nsw i32 %174, -1
  store i32 %175, i32* %5, align 4
  %176 = sext i32 %174 to i64
  %177 = getelementptr inbounds [81 x i8], [81 x i8]* %16, i64 0, i64 %176
  store i8 -1, i8* %177, align 1
  br label %178

; <label>:178:                                    ; preds = %173, %170
  br label %179

; <label>:179:                                    ; preds = %178, %121
  %180 = load i32, i32* %5, align 4
  %181 = sext i32 %180 to i64
  %182 = getelementptr inbounds [81 x i16], [81 x i16]* %18, i64 0, i64 %181
  %183 = load i16, i16* %182, align 2
  %184 = sext i16 %183 to i32
  store i32 %184, i32* %8, align 4
  %185 = load i32, i32* %10, align 4
  %186 = icmp eq i32 %185, -1
  br i1 %186, label %187, label %212

; <label>:187:                                    ; preds = %179
  %188 = load i32, i32* %5, align 4
  %189 = sext i32 %188 to i64
  %190 = getelementptr inbounds [81 x i8], [81 x i8]* %16, i64 0, i64 %189
  %191 = load i8, i8* %190, align 1
  %192 = sext i8 %191 to i32
  %193 = icmp sge i32 %192, 0
  br i1 %193, label %194, label %212

; <label>:194:                                    ; preds = %187
  %195 = load %struct.sdaux_t*, %struct.sdaux_t** %3, align 8
  %196 = getelementptr inbounds [729 x i8], [729 x i8]* %15, i32 0, i32 0
  %197 = getelementptr inbounds [324 x i8], [324 x i8]* %17, i32 0, i32 0
  %198 = load %struct.sdaux_t*, %struct.sdaux_t** %3, align 8
  %199 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %198, i32 0, i32 0
  %200 = load i32, i32* %8, align 4
  %201 = sext i32 %200 to i64
  %202 = getelementptr inbounds [324 x [9 x i16]], [324 x [9 x i16]]* %199, i64 0, i64 %201
  %203 = load i32, i32* %5, align 4
  %204 = sext i32 %203 to i64
  %205 = getelementptr inbounds [81 x i8], [81 x i8]* %16, i64 0, i64 %204
  %206 = load i8, i8* %205, align 1
  %207 = sext i8 %206 to i64
  %208 = getelementptr inbounds [9 x i16], [9 x i16]* %202, i64 0, i64 %207
  %209 = load i16, i16* %208, align 2
  %210 = zext i16 %209 to i32
  %211 = call i32 @sd_update(%struct.sdaux_t* %195, i8* %196, i8* %197, i32 %210, i32 -1)
  br label %212

; <label>:212:                                    ; preds = %194, %187, %179
  %213 = load i32, i32* %5, align 4
  %214 = sext i32 %213 to i64
  %215 = getelementptr inbounds [81 x i8], [81 x i8]* %16, i64 0, i64 %214
  %216 = load i8, i8* %215, align 1
  %217 = sext i8 %216 to i32
  %218 = add nsw i32 %217, 1
  store i32 %218, i32* %9, align 4
  br label %219

; <label>:219:                                    ; preds = %239, %212
  %220 = load i32, i32* %9, align 4
  %221 = icmp slt i32 %220, 9
  br i1 %221, label %222, label %242

; <label>:222:                                    ; preds = %219
  %223 = load %struct.sdaux_t*, %struct.sdaux_t** %3, align 8
  %224 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %223, i32 0, i32 0
  %225 = load i32, i32* %8, align 4
  %226 = sext i32 %225 to i64
  %227 = getelementptr inbounds [324 x [9 x i16]], [324 x [9 x i16]]* %224, i64 0, i64 %226
  %228 = load i32, i32* %9, align 4
  %229 = sext i32 %228 to i64
  %230 = getelementptr inbounds [9 x i16], [9 x i16]* %227, i64 0, i64 %229
  %231 = load i16, i16* %230, align 2
  %232 = zext i16 %231 to i64
  %233 = getelementptr inbounds [729 x i8], [729 x i8]* %15, i64 0, i64 %232
  %234 = load i8, i8* %233, align 1
  %235 = sext i8 %234 to i32
  %236 = icmp eq i32 %235, 0
  br i1 %236, label %237, label %238

; <label>:237:                                    ; preds = %222
  br label %242

; <label>:238:                                    ; preds = %222
  br label %239

; <label>:239:                                    ; preds = %238
  %240 = load i32, i32* %9, align 4
  %241 = add nsw i32 %240, 1
  store i32 %241, i32* %9, align 4
  br label %219

; <label>:242:                                    ; preds = %237, %219
  %243 = load i32, i32* %9, align 4
  %244 = icmp slt i32 %243, 9
  br i1 %244, label %245, label %266

; <label>:245:                                    ; preds = %242
  %246 = load %struct.sdaux_t*, %struct.sdaux_t** %3, align 8
  %247 = getelementptr inbounds [729 x i8], [729 x i8]* %15, i32 0, i32 0
  %248 = getelementptr inbounds [324 x i8], [324 x i8]* %17, i32 0, i32 0
  %249 = load %struct.sdaux_t*, %struct.sdaux_t** %3, align 8
  %250 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %249, i32 0, i32 0
  %251 = load i32, i32* %8, align 4
  %252 = sext i32 %251 to i64
  %253 = getelementptr inbounds [324 x [9 x i16]], [324 x [9 x i16]]* %250, i64 0, i64 %252
  %254 = load i32, i32* %9, align 4
  %255 = sext i32 %254 to i64
  %256 = getelementptr inbounds [9 x i16], [9 x i16]* %253, i64 0, i64 %255
  %257 = load i16, i16* %256, align 2
  %258 = zext i16 %257 to i32
  %259 = call i32 @sd_update(%struct.sdaux_t* %246, i8* %247, i8* %248, i32 %258, i32 1)
  store i32 %259, i32* %11, align 4
  %260 = load i32, i32* %9, align 4
  %261 = trunc i32 %260 to i8
  %262 = load i32, i32* %5, align 4
  %263 = add nsw i32 %262, 1
  store i32 %263, i32* %5, align 4
  %264 = sext i32 %262 to i64
  %265 = getelementptr inbounds [81 x i8], [81 x i8]* %16, i64 0, i64 %264
  store i8 %261, i8* %265, align 1
  store i32 1, i32* %10, align 4
  br label %271

; <label>:266:                                    ; preds = %242
  store i32 -1, i32* %10, align 4
  %267 = load i32, i32* %5, align 4
  %268 = add nsw i32 %267, -1
  store i32 %268, i32* %5, align 4
  %269 = sext i32 %267 to i64
  %270 = getelementptr inbounds [81 x i8], [81 x i8]* %16, i64 0, i64 %269
  store i8 -1, i8* %270, align 1
  br label %271

; <label>:271:                                    ; preds = %266, %245
  br label %111

; <label>:272:                                    ; preds = %119
  %273 = load i32, i32* %5, align 4
  %274 = icmp slt i32 %273, 0
  br i1 %274, label %275, label %276

; <label>:275:                                    ; preds = %272
  br label %316

; <label>:276:                                    ; preds = %272
  store i32 0, i32* %6, align 4
  br label %277

; <label>:277:                                    ; preds = %306, %276
  %278 = load i32, i32* %6, align 4
  %279 = load i32, i32* %5, align 4
  %280 = icmp slt i32 %278, %279
  br i1 %280, label %281, label %309

; <label>:281:                                    ; preds = %277
  %282 = load %struct.sdaux_t*, %struct.sdaux_t** %3, align 8
  %283 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %282, i32 0, i32 0
  %284 = load i32, i32* %6, align 4
  %285 = sext i32 %284 to i64
  %286 = getelementptr inbounds [81 x i16], [81 x i16]* %18, i64 0, i64 %285
  %287 = load i16, i16* %286, align 2
  %288 = sext i16 %287 to i64
  %289 = getelementptr inbounds [324 x [9 x i16]], [324 x [9 x i16]]* %283, i64 0, i64 %288
  %290 = load i32, i32* %6, align 4
  %291 = sext i32 %290 to i64
  %292 = getelementptr inbounds [81 x i8], [81 x i8]* %16, i64 0, i64 %291
  %293 = load i8, i8* %292, align 1
  %294 = sext i8 %293 to i64
  %295 = getelementptr inbounds [9 x i16], [9 x i16]* %289, i64 0, i64 %294
  %296 = load i16, i16* %295, align 2
  %297 = zext i16 %296 to i32
  store i32 %297, i32* %7, align 4
  %298 = load i32, i32* %7, align 4
  %299 = srem i32 %298, 9
  %300 = add nsw i32 %299, 49
  %301 = trunc i32 %300 to i8
  %302 = load i32, i32* %7, align 4
  %303 = sdiv i32 %302, 9
  %304 = sext i32 %303 to i64
  %305 = getelementptr inbounds [82 x i8], [82 x i8]* %19, i64 0, i64 %304
  store i8 %301, i8* %305, align 1
  br label %306

; <label>:306:                                    ; preds = %281
  %307 = load i32, i32* %6, align 4
  %308 = add nsw i32 %307, 1
  store i32 %308, i32* %6, align 4
  br label %277

; <label>:309:                                    ; preds = %277
  %310 = getelementptr inbounds [82 x i8], [82 x i8]* %19, i32 0, i32 0
  %311 = call i32 @puts(i8* %310)
  %312 = load i32, i32* %12, align 4
  %313 = add nsw i32 %312, 1
  store i32 %313, i32* %12, align 4
  %314 = load i32, i32* %5, align 4
  %315 = add nsw i32 %314, -1
  store i32 %315, i32* %5, align 4
  store i32 -1, i32* %10, align 4
  br label %110

; <label>:316:                                    ; preds = %275
  %317 = load i32, i32* %12, align 4
  ret i32 %317
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal i32 @sd_update(%struct.sdaux_t*, i8*, i8*, i32, i32) #0 {
  %6 = alloca %struct.sdaux_t*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %19 = alloca i16*, align 8
  store %struct.sdaux_t* %0, %struct.sdaux_t** %6, align 8
  store i8* %1, i8** %7, align 8
  store i8* %2, i8** %8, align 8
  store i32 %3, i32* %9, align 4
  store i32 %4, i32* %10, align 4
  store i32 10, i32* %12, align 4
  store i32 0, i32* %13, align 4
  store i32 0, i32* %11, align 4
  br label %20

; <label>:20:                                     ; preds = %42, %5
  %21 = load i32, i32* %11, align 4
  %22 = icmp slt i32 %21, 4
  br i1 %22, label %23, label %45

; <label>:23:                                     ; preds = %20
  %24 = load i32, i32* %10, align 4
  %25 = shl i32 %24, 7
  %26 = load i8*, i8** %8, align 8
  %27 = load %struct.sdaux_t*, %struct.sdaux_t** %6, align 8
  %28 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %27, i32 0, i32 1
  %29 = load i32, i32* %9, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [729 x [4 x i16]], [729 x [4 x i16]]* %28, i64 0, i64 %30
  %32 = load i32, i32* %11, align 4
  %33 = sext i32 %32 to i64
  %34 = getelementptr inbounds [4 x i16], [4 x i16]* %31, i64 0, i64 %33
  %35 = load i16, i16* %34, align 2
  %36 = zext i16 %35 to i64
  %37 = getelementptr inbounds i8, i8* %26, i64 %36
  %38 = load i8, i8* %37, align 1
  %39 = zext i8 %38 to i32
  %40 = add nsw i32 %39, %25
  %41 = trunc i32 %40 to i8
  store i8 %41, i8* %37, align 1
  br label %42

; <label>:42:                                     ; preds = %23
  %43 = load i32, i32* %11, align 4
  %44 = add nsw i32 %43, 1
  store i32 %44, i32* %11, align 4
  br label %20

; <label>:45:                                     ; preds = %20
  store i32 0, i32* %11, align 4
  br label %46

; <label>:46:                                     ; preds = %193, %45
  %47 = load i32, i32* %11, align 4
  %48 = icmp slt i32 %47, 4
  br i1 %48, label %49, label %196

; <label>:49:                                     ; preds = %46
  %50 = load %struct.sdaux_t*, %struct.sdaux_t** %6, align 8
  %51 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %50, i32 0, i32 1
  %52 = load i32, i32* %9, align 4
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds [729 x [4 x i16]], [729 x [4 x i16]]* %51, i64 0, i64 %53
  %55 = load i32, i32* %11, align 4
  %56 = sext i32 %55 to i64
  %57 = getelementptr inbounds [4 x i16], [4 x i16]* %54, i64 0, i64 %56
  %58 = load i16, i16* %57, align 2
  %59 = zext i16 %58 to i32
  store i32 %59, i32* %17, align 4
  %60 = load i32, i32* %10, align 4
  %61 = icmp sgt i32 %60, 0
  br i1 %61, label %62, label %126

; <label>:62:                                     ; preds = %49
  store i32 0, i32* %14, align 4
  br label %63

; <label>:63:                                     ; preds = %122, %62
  %64 = load i32, i32* %14, align 4
  %65 = icmp slt i32 %64, 9
  br i1 %65, label %66, label %125

; <label>:66:                                     ; preds = %63
  %67 = load i8*, i8** %7, align 8
  %68 = load %struct.sdaux_t*, %struct.sdaux_t** %6, align 8
  %69 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %68, i32 0, i32 0
  %70 = load i32, i32* %17, align 4
  %71 = sext i32 %70 to i64
  %72 = getelementptr inbounds [324 x [9 x i16]], [324 x [9 x i16]]* %69, i64 0, i64 %71
  %73 = load i32, i32* %14, align 4
  %74 = sext i32 %73 to i64
  %75 = getelementptr inbounds [9 x i16], [9 x i16]* %72, i64 0, i64 %74
  %76 = load i16, i16* %75, align 2
  %77 = zext i16 %76 to i32
  store i32 %77, i32* %15, align 4
  %78 = sext i32 %77 to i64
  %79 = getelementptr inbounds i8, i8* %67, i64 %78
  %80 = load i8, i8* %79, align 1
  %81 = add i8 %80, 1
  store i8 %81, i8* %79, align 1
  %82 = sext i8 %80 to i32
  %83 = icmp ne i32 %82, 0
  br i1 %83, label %84, label %85

; <label>:84:                                     ; preds = %66
  br label %122

; <label>:85:                                     ; preds = %66
  store i32 0, i32* %16, align 4
  br label %86

; <label>:86:                                     ; preds = %118, %85
  %87 = load i32, i32* %16, align 4
  %88 = icmp slt i32 %87, 4
  br i1 %88, label %89, label %121

; <label>:89:                                     ; preds = %86
  %90 = load %struct.sdaux_t*, %struct.sdaux_t** %6, align 8
  %91 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %90, i32 0, i32 1
  %92 = load i32, i32* %15, align 4
  %93 = sext i32 %92 to i64
  %94 = getelementptr inbounds [729 x [4 x i16]], [729 x [4 x i16]]* %91, i64 0, i64 %93
  %95 = load i32, i32* %16, align 4
  %96 = sext i32 %95 to i64
  %97 = getelementptr inbounds [4 x i16], [4 x i16]* %94, i64 0, i64 %96
  %98 = load i16, i16* %97, align 2
  %99 = zext i16 %98 to i32
  store i32 %99, i32* %18, align 4
  %100 = load i8*, i8** %8, align 8
  %101 = load i32, i32* %18, align 4
  %102 = sext i32 %101 to i64
  %103 = getelementptr inbounds i8, i8* %100, i64 %102
  %104 = load i8, i8* %103, align 1
  %105 = add i8 %104, -1
  store i8 %105, i8* %103, align 1
  %106 = zext i8 %105 to i32
  %107 = load i32, i32* %12, align 4
  %108 = icmp slt i32 %106, %107
  br i1 %108, label %109, label %117

; <label>:109:                                    ; preds = %89
  %110 = load i8*, i8** %8, align 8
  %111 = load i32, i32* %18, align 4
  %112 = sext i32 %111 to i64
  %113 = getelementptr inbounds i8, i8* %110, i64 %112
  %114 = load i8, i8* %113, align 1
  %115 = zext i8 %114 to i32
  store i32 %115, i32* %12, align 4
  %116 = load i32, i32* %18, align 4
  store i32 %116, i32* %13, align 4
  br label %117

; <label>:117:                                    ; preds = %109, %89
  br label %118

; <label>:118:                                    ; preds = %117
  %119 = load i32, i32* %16, align 4
  %120 = add nsw i32 %119, 1
  store i32 %120, i32* %16, align 4
  br label %86

; <label>:121:                                    ; preds = %86
  br label %122

; <label>:122:                                    ; preds = %121, %84
  %123 = load i32, i32* %14, align 4
  %124 = add nsw i32 %123, 1
  store i32 %124, i32* %14, align 4
  br label %63

; <label>:125:                                    ; preds = %63
  br label %192

; <label>:126:                                    ; preds = %49
  store i32 0, i32* %14, align 4
  br label %127

; <label>:127:                                    ; preds = %188, %126
  %128 = load i32, i32* %14, align 4
  %129 = icmp slt i32 %128, 9
  br i1 %129, label %130, label %191

; <label>:130:                                    ; preds = %127
  %131 = load i8*, i8** %7, align 8
  %132 = load %struct.sdaux_t*, %struct.sdaux_t** %6, align 8
  %133 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %132, i32 0, i32 0
  %134 = load i32, i32* %17, align 4
  %135 = sext i32 %134 to i64
  %136 = getelementptr inbounds [324 x [9 x i16]], [324 x [9 x i16]]* %133, i64 0, i64 %135
  %137 = load i32, i32* %14, align 4
  %138 = sext i32 %137 to i64
  %139 = getelementptr inbounds [9 x i16], [9 x i16]* %136, i64 0, i64 %138
  %140 = load i16, i16* %139, align 2
  %141 = zext i16 %140 to i32
  store i32 %141, i32* %15, align 4
  %142 = sext i32 %141 to i64
  %143 = getelementptr inbounds i8, i8* %131, i64 %142
  %144 = load i8, i8* %143, align 1
  %145 = add i8 %144, -1
  store i8 %145, i8* %143, align 1
  %146 = sext i8 %145 to i32
  %147 = icmp ne i32 %146, 0
  br i1 %147, label %148, label %149

; <label>:148:                                    ; preds = %130
  br label %188

; <label>:149:                                    ; preds = %130
  %150 = load %struct.sdaux_t*, %struct.sdaux_t** %6, align 8
  %151 = getelementptr inbounds %struct.sdaux_t, %struct.sdaux_t* %150, i32 0, i32 1
  %152 = load i32, i32* %15, align 4
  %153 = sext i32 %152 to i64
  %154 = getelementptr inbounds [729 x [4 x i16]], [729 x [4 x i16]]* %151, i64 0, i64 %153
  %155 = getelementptr inbounds [4 x i16], [4 x i16]* %154, i32 0, i32 0
  store i16* %155, i16** %19, align 8
  %156 = load i8*, i8** %8, align 8
  %157 = load i16*, i16** %19, align 8
  %158 = getelementptr inbounds i16, i16* %157, i64 0
  %159 = load i16, i16* %158, align 2
  %160 = zext i16 %159 to i64
  %161 = getelementptr inbounds i8, i8* %156, i64 %160
  %162 = load i8, i8* %161, align 1
  %163 = add i8 %162, 1
  store i8 %163, i8* %161, align 1
  %164 = load i8*, i8** %8, align 8
  %165 = load i16*, i16** %19, align 8
  %166 = getelementptr inbounds i16, i16* %165, i64 1
  %167 = load i16, i16* %166, align 2
  %168 = zext i16 %167 to i64
  %169 = getelementptr inbounds i8, i8* %164, i64 %168
  %170 = load i8, i8* %169, align 1
  %171 = add i8 %170, 1
  store i8 %171, i8* %169, align 1
  %172 = load i8*, i8** %8, align 8
  %173 = load i16*, i16** %19, align 8
  %174 = getelementptr inbounds i16, i16* %173, i64 2
  %175 = load i16, i16* %174, align 2
  %176 = zext i16 %175 to i64
  %177 = getelementptr inbounds i8, i8* %172, i64 %176
  %178 = load i8, i8* %177, align 1
  %179 = add i8 %178, 1
  store i8 %179, i8* %177, align 1
  %180 = load i8*, i8** %8, align 8
  %181 = load i16*, i16** %19, align 8
  %182 = getelementptr inbounds i16, i16* %181, i64 3
  %183 = load i16, i16* %182, align 2
  %184 = zext i16 %183 to i64
  %185 = getelementptr inbounds i8, i8* %180, i64 %184
  %186 = load i8, i8* %185, align 1
  %187 = add i8 %186, 1
  store i8 %187, i8* %185, align 1
  br label %188

; <label>:188:                                    ; preds = %149, %148
  %189 = load i32, i32* %14, align 4
  %190 = add nsw i32 %189, 1
  store i32 %190, i32* %14, align 4
  br label %127

; <label>:191:                                    ; preds = %127
  br label %192

; <label>:192:                                    ; preds = %191, %125
  br label %193

; <label>:193:                                    ; preds = %192
  %194 = load i32, i32* %11, align 4
  %195 = add nsw i32 %194, 1
  store i32 %195, i32* %11, align 4
  br label %46

; <label>:196:                                    ; preds = %46
  %197 = load i32, i32* %12, align 4
  %198 = shl i32 %197, 16
  %199 = load i32, i32* %13, align 4
  %200 = or i32 %198, %199
  ret i32 %200
}

declare i32 @puts(i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main() #0 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.sdaux_t*, align 8
  %3 = alloca [1024 x i8], align 16
  store i32 0, i32* %1, align 4
  %4 = call %struct.sdaux_t* @sd_genmat()
  store %struct.sdaux_t* %4, %struct.sdaux_t** %2, align 8
  br label %5

; <label>:5:                                      ; preds = %15, %14, %0
  %6 = getelementptr inbounds [1024 x i8], [1024 x i8]* %3, i32 0, i32 0
  %7 = load %struct.__sFILE*, %struct.__sFILE** @__stdinp, align 8
  %8 = call i8* @fgets(i8* %6, i32 1024, %struct.__sFILE* %7)
  %9 = icmp ne i8* %8, null
  br i1 %9, label %10, label %20

; <label>:10:                                     ; preds = %5
  %11 = getelementptr inbounds [1024 x i8], [1024 x i8]* %3, i32 0, i32 0
  %12 = call i64 @strlen(i8* %11)
  %13 = icmp ult i64 %12, 81
  br i1 %13, label %14, label %15

; <label>:14:                                     ; preds = %10
  br label %5

; <label>:15:                                     ; preds = %10
  %16 = load %struct.sdaux_t*, %struct.sdaux_t** %2, align 8
  %17 = getelementptr inbounds [1024 x i8], [1024 x i8]* %3, i32 0, i32 0
  %18 = call i32 @sd_solve(%struct.sdaux_t* %16, i8* %17)
  %19 = call i32 @putchar(i32 10)
  br label %5

; <label>:20:                                     ; preds = %5
  %21 = load %struct.sdaux_t*, %struct.sdaux_t** %2, align 8
  %22 = bitcast %struct.sdaux_t* %21 to i8*
  call void @free(i8* %22)
  ret i32 0
}

declare i8* @fgets(i8*, i32, %struct.__sFILE*) #2

declare i64 @strlen(i8*) #2

declare i32 @putchar(i32) #2

declare void @free(i8*) #2

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { allocsize(0,1) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { allocsize(0,1) }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
