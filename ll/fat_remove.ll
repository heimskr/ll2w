%struct.pcache_t = type { [1024 x %struct.pathc_t], %struct.superblock_t, i32*, i64, %struct.dir_t, i32, %struct._opaque_pthread_mutex_t }
%struct.pathc_t = type { i8, [1025 x i8], %struct.dir_t, %struct.fdc_t*, i64, i64, %struct._opaque_pthread_mutex_t* }
%struct.fdc_t = type { i8, i64, %struct.pathc_t* }
%struct.superblock_t = type { i32, i32, i32, i32, i32 }
%struct.dir_t = type { %union.fname_u, %struct.times_t, i32, i32, i32, i32 }
%union.fname_u = type { [6 x i32] }
%struct.times_t = type { i64, i64, i64 }
%struct._opaque_pthread_mutex_t = type { i64, [56 x i8] }
%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }
%union.superblock_u = type { %struct.superblock_t }

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_remove(i32, i8*, i32) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca %struct.dir_t*, align 8
  %9 = alloca i64, align 8
  %10 = alloca i32, align 4
  store i32 %0, i32* %5, align 4
  store i8* %1, i8** %6, align 8
  store i32 %2, i32* %7, align 4
  %11 = load i32, i32* @debug_enable, align 4
  %12 = icmp eq i32 %11, 1
  br i1 %12, label %13, label %32

; <label>:13:                                     ; preds = %3
  %14 = load i32, i32* @debug_disable_method, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %32

; <label>:16:                                     ; preds = %13
  %17 = load i32, i32* @debug_disable_external, align 4
  %18 = icmp ne i32 %17, 1
  br i1 %18, label %19, label %32

; <label>:19:                                     ; preds = %16
  %20 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %21 = icmp ne %struct.__sFILE* %20, null
  br i1 %21, label %22, label %32

; <label>:22:                                     ; preds = %19
  %23 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %24 = load i8*, i8** %6, align 8
  %25 = load i32, i32* %7, align 4
  %26 = icmp ne i32 %25, 0
  %27 = zext i1 %26 to i64
  %28 = select i1 %26, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.155, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.156, i32 0, i32 0)
  %29 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %23, i8* getelementptr inbounds ([169 x i8], [169 x i8]* @.str.153, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1500, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.154, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %24, i8* %28)
  %30 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %31 = call i32 @fflush(%struct.__sFILE* %30)
  br label %32

; <label>:32:                                     ; preds = %22, %19, %16, %13, %3
  store i32 0, i32* @debug_enable, align 4
  %33 = load i32, i32* %5, align 4
  %34 = load i8*, i8** %6, align 8
  %35 = call i32 @fat_find(i32 %33, i64 -1, i8* %34, %struct.dir_t* null, %struct.dir_t** %8, i64* %9, i32 0, i8** null)
  store i32 %35, i32* %10, align 4
  store i32 1, i32* @debug_enable, align 4
  %36 = load i32, i32* %10, align 4
  %37 = icmp slt i32 %36, 0
  br i1 %37, label %38, label %68

; <label>:38:                                     ; preds = %32
  store i32 1, i32* @debug_enable, align 4
  %39 = load i32, i32* @debug_enable, align 4
  %40 = icmp eq i32 %39, 1
  br i1 %40, label %41, label %66

; <label>:41:                                     ; preds = %38
  %42 = load i32, i32* @debug_disable_method, align 4
  %43 = icmp eq i32 %42, 0
  br i1 %43, label %44, label %66

; <label>:44:                                     ; preds = %41
  %45 = load i32, i32* @debug_disable_external, align 4
  %46 = icmp ne i32 %45, 1
  br i1 %46, label %47, label %66

; <label>:47:                                     ; preds = %44
  %48 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %49 = icmp ne %struct.__sFILE* %48, null
  br i1 %49, label %50, label %66

; <label>:50:                                     ; preds = %47
  %51 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %52 = load i32, i32* %10, align 4
  %53 = load i32, i32* %10, align 4
  %54 = icmp slt i32 %53, 0
  br i1 %54, label %55, label %58

; <label>:55:                                     ; preds = %50
  %56 = load i32, i32* %10, align 4
  %57 = sub nsw i32 0, %56
  br label %60

; <label>:58:                                     ; preds = %50
  %59 = load i32, i32* %10, align 4
  br label %60

; <label>:60:                                     ; preds = %58, %55
  %61 = phi i32 [ %57, %55 ], [ %59, %58 ]
  %62 = call i8* @"\01_strerror"(i32 %61)
  %63 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %51, i8* getelementptr inbounds ([142 x i8], [142 x i8]* @.str.94, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1508, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.154, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %52, i8* %62)
  %64 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %65 = call i32 @fflush(%struct.__sFILE* %64)
  br label %66

; <label>:66:                                     ; preds = %60, %47, %44, %41, %38
  %67 = load i32, i32* %10, align 4
  store i32 %67, i32* %4, align 4
  br label %125

; <label>:68:                                     ; preds = %32
  %69 = load i32, i32* @debug_enable, align 4
  %70 = icmp eq i32 %69, 1
  br i1 %70, label %71, label %96

; <label>:71:                                     ; preds = %68
  %72 = load i32, i32* @debug_disable_method, align 4
  %73 = icmp eq i32 %72, 0
  br i1 %73, label %74, label %96

; <label>:74:                                     ; preds = %71
  %75 = load i32, i32* @debug_disable_external, align 4
  %76 = icmp ne i32 %75, 1
  br i1 %76, label %77, label %96

; <label>:77:                                     ; preds = %74
  %78 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %79 = icmp ne %struct.__sFILE* %78, null
  br i1 %79, label %80, label %96

; <label>:80:                                     ; preds = %77
  %81 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %82 = load i64, i64* %9, align 8
  %83 = load %struct.dir_t*, %struct.dir_t** %8, align 8
  %84 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %83, i32 0, i32 3
  %85 = load i32, i32* %84, align 4
  %86 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %87 = load %struct.dir_t*, %struct.dir_t** %8, align 8
  %88 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %87, i32 0, i32 3
  %89 = load i32, i32* %88, align 4
  %90 = sext i32 %89 to i64
  %91 = getelementptr inbounds i32, i32* %86, i64 %90
  %92 = load i32, i32* %91, align 4
  %93 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %81, i8* getelementptr inbounds ([207 x i8], [207 x i8]* @.str.157, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1511, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.154, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %82, i32 %85, i32 %92)
  %94 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %95 = call i32 @fflush(%struct.__sFILE* %94)
  br label %96

; <label>:96:                                     ; preds = %80, %77, %74, %71, %68
  %97 = load %struct.dir_t*, %struct.dir_t** %8, align 8
  %98 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %97, i32 0, i32 3
  %99 = load i32, i32* %98, align 4
  %100 = call i64 @fat_forget(i32 %99)
  %101 = load %struct.dir_t*, %struct.dir_t** %8, align 8
  %102 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %101, i32 0, i32 3
  store i32 0, i32* %102, align 4
  %103 = load i32, i32* %5, align 4
  %104 = load %struct.dir_t*, %struct.dir_t** %8, align 8
  %105 = load i64, i64* %9, align 8
  %106 = call i32 @fat_write_entry(i32 %103, %struct.dir_t* %104, i64 %105)
  %107 = load i32, i32* %5, align 4
  %108 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %107, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %108)
  %109 = load i32, i32* %7, align 4
  %110 = icmp ne i32 %109, 0
  br i1 %110, label %111, label %114

; <label>:111:                                    ; preds = %96
  %112 = load i8*, i8** %6, align 8
  %113 = call i32 @pathc_remove_path(i8* %112)
  br label %114

; <label>:114:                                    ; preds = %111, %96
  %115 = load i32, i32* %10, align 4
  %116 = icmp eq i32 %115, 1
  br i1 %116, label %117, label %124

; <label>:117:                                    ; preds = %114
  %118 = load %struct.dir_t*, %struct.dir_t** %8, align 8
  %119 = icmp ne %struct.dir_t* %118, null
  br i1 %119, label %120, label %123

; <label>:120:                                    ; preds = %117
  %121 = load %struct.dir_t*, %struct.dir_t** %8, align 8
  %122 = bitcast %struct.dir_t* %121 to i8*
  call void @free(i8* %122)
  store %struct.dir_t* null, %struct.dir_t** %8, align 8
  br label %123

; <label>:123:                                    ; preds = %120, %117
  br label %124

; <label>:124:                                    ; preds = %123, %114
  store i32 0, i32* %4, align 4
  br label %125

; <label>:125:                                    ; preds = %124, %66
  %126 = load i32, i32* %4, align 4
  ret i32 %126
}