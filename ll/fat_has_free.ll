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

@debug_disable_method = external global i32, align 4
@debug_enable = external global i32, align 4

declare void @indent(i32) #1
declare void @dbg2(i8*, i32, i8*, i8*, i8*) #1
declare i32 @fat_find(i32, i64, i8*, %struct.dir_t*, %struct.dir_t**, i64*, i32, i8**) #0
declare i8* @"\01_strerror"(i32) #1
declare i32 @fflush(%struct.__sFILE*) #1
declare i64 @strlen(i8*) #1
declare void @free(i8*) #1
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1) #2
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #2
declare i32 @fat_find_free_block() #0
declare i8* @__memcpy_chk(i8*, i8*, i64, i64) #3
declare i32 @fat_read_dir(i32, %struct.dir_t*, %struct.dir_t**, i64**, i64*, i32*) #0
declare i64 @updiv(i64, i64) #1
declare i32 @fat_write_entry(i32, %struct.dir_t*, i64) #0
declare i32 @fat_has_free(i64) #0
declare void @dbgn(i8*, i32, i8*, i8*, i64) #1
declare void @dbg(i8*, i32, i8*, i8*) #1
declare void @fat_save(i32, %struct.superblock_t*, i32*) #0
declare i32 @pathc_insert(i8*, %struct.dir_t* byval align 8, i64, %struct.pathc_t**) #1
declare void @quit(i32, i32) #1
declare i8* @malloc(i64) #6

define i32 @fat_has_free(i64) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  store i64 %0, i64* %3, align 8
  store i64 0, i64* %4, align 8
  %7 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 1), align 4
  %8 = zext i32 %7 to i64
  store i64 %8, i64* %5, align 8
  store i64 0, i64* %6, align 8
  br label %9

; <label>:9:                                      ; preds = %26, %1
  %10 = load i64, i64* %6, align 8
  %11 = load i64, i64* %5, align 8
  %12 = icmp ult i64 %10, %11
  br i1 %12, label %13, label %29

; <label>:13:                                     ; preds = %9
  %14 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %15 = load i64, i64* %6, align 8
  %16 = getelementptr inbounds i32, i32* %14, i64 %15
  %17 = load i32, i32* %16, align 4
  %18 = icmp eq i32 %17, 0
  br i1 %18, label %19, label %25

; <label>:19:                                     ; preds = %13
  %20 = load i64, i64* %3, align 8
  %21 = load i64, i64* %4, align 8
  %22 = add i64 %21, 1
  store i64 %22, i64* %4, align 8
  %23 = icmp ule i64 %20, %22
  br i1 %23, label %24, label %25

; <label>:24:                                     ; preds = %19
  store i32 1, i32* %2, align 4
  br label %30

; <label>:25:                                     ; preds = %19, %13
  br label %26

; <label>:26:                                     ; preds = %25
  %27 = load i64, i64* %6, align 8
  %28 = add i64 %27, 1
  store i64 %28, i64* %6, align 8
  br label %9

; <label>:29:                                     ; preds = %9
  store i32 0, i32* %2, align 4
  br label %30

; <label>:30:                                     ; preds = %29, %24
  %31 = load i32, i32* %2, align 4
  ret i32 %31
}
