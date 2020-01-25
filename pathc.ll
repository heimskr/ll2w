; ModuleID = 'pathc.c'
source_filename = "pathc.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

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
%struct._opaque_pthread_mutexattr_t = type { i64, [8 x i8] }

@pathc_overflow_index = global i32 0, align 4
@pcache = common global %struct.pcache_t zeroinitializer, align 8
@.str = private unnamed_addr constant [8 x i8] c"pathc.c\00", align 1
@.str.1 = private unnamed_addr constant [47 x i8] c"\1B[0m\1B[38;5;128m pc_\1B[38;5;112mfind_fd\1B[39m\1B[2m\00", align 1
@.str.2 = private unnamed_addr constant [137 x i8] c"\1B[1;31mX\1B[0m  If you're trying to use a file descriptor that doesn't fit in 32 bits, you're going to have a bad time. Please reconsider.\00", align 1
@.str.3 = private unnamed_addr constant [35 x i8] c"Found from \1B[38;5;128mpcache\1B[39m:\00", align 1
@.str.4 = private unnamed_addr constant [47 x i8] c"\1B[0m\1B[38;5;128mpc_\1B[38;5;112mfind_off\1B[39m\1B[2m\00", align 1
@debug_enable = external global i32, align 4
@debug_disable_method = external global i32, align 4
@debug_disable_external = external global i32, align 4
@logfile = external global %struct.__sFILE*, align 8
@.str.5 = private unnamed_addr constant [213 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Linked \1B[38;5;128mpcache\1B[39m item (offset \1B[1m%ld\1B[22m) with \1B[36mfdcache\1B[39m item (file descriptor \1B[1m%ld\1B[22m).\0A\00", align 1
@.str.6 = private unnamed_addr constant [36 x i8] c"\1B[0m\1B[38;5;128m    pc_link\1B[39m\1B[2m\00", align 1
@indentation = external global [81 x i8], align 16
@.str.7 = private unnamed_addr constant [187 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Linked \1B[38;5;128mpcache\1B[39m item (offset \1B[1m%ld\1B[22m) with null \1B[36mfdcache\1B[39m item.\0A\00", align 1
@.str.8 = private unnamed_addr constant [196 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Linked \1B[36mfdcache\1B[39m item (file descriptor \1B[1m%ld\1B[22m) with null \1B[38;5;128mpcache\1B[39m item.\0A\00", align 1
@.str.9 = private unnamed_addr constant [147 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[31m%8s\1B[0m \1B[31m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[31m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %sMutex initialization failed for \1B[1m%s\1B[22m\1B[0m\0A\00", align 1
@.str.10 = private unnamed_addr constant [47 x i8] c"\1B[0m\1B[38;5;128m     pc_\1B[38;5;219mnew\1B[39m\1B[2m\00", align 1
@.str.11 = private unnamed_addr constant [226 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[32m%8s\1B[0m \1B[32m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[32m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[32mFound a free \1B[38;5;128m\1B[1mpcache slot\1B[22m\1B[39m\1B[32m for \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m at index \1B[1m%d\1B[22m.\1B[39m\1B[0m\0A\00", align 1
@.str.12 = private unnamed_addr constant [47 x i8] c"\1B[0m\1B[38;5;128m  pc_\1B[38;5;219minsert\1B[39m\1B[2m\00", align 1
@.str.13 = private unnamed_addr constant [111 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33m%s\1B[0m\0A\00", align 1
@.str.14 = private unnamed_addr constant [11 x i8] c"Giving up.\00", align 1
@.str.15 = private unnamed_addr constant [171 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mOverwrote a \1B[38;5;128mpcache\1B[39m entry at index \1B[1m%d\1B[22m.\1B[0m\0A\00", align 1
@.str.16 = private unnamed_addr constant [47 x i8] c"\1B[0m\1B[38;5;128m    pc_\1B[38;5;208mdown\1B[39m\1B[2m\00", align 1
@.str.17 = private unnamed_addr constant [27 x i8] c"Item is NULL; not locking.\00", align 1
@.str.18 = private unnamed_addr constant [27 x i8] c"Lock is NULL; not locking.\00", align 1
@.str.19 = private unnamed_addr constant [47 x i8] c"\1B[0m\1B[38;5;128m      pc_\1B[38;5;208mup\1B[39m\1B[2m\00", align 1
@.str.20 = private unnamed_addr constant [211 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s \1B[31mRemoved\1B[39m \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m (\1B[1m%ld\1B[22m) from \1B[38;5;128mpcache\1B[39m at index \1B[1m%d\1B[22m.\0A\00", align 1
@.str.21 = private unnamed_addr constant [41 x i8] c"\1B[0m\1B[38;5;128mpc_\1B[31mrmv_item\1B[39m\1B[2m\00", align 1
@.str.22 = private unnamed_addr constant [41 x i8] c"\1B[0m\1B[38;5;128m  pc_\1B[31mrmv_fd\1B[39m\1B[2m\00", align 1
@.str.23 = private unnamed_addr constant [145 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mpathc_down failed.: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.24 = private unnamed_addr constant [36 x i8] c"\1B[0m\1B[38;5;128m    pc_save\1B[39m\1B[2m\00", align 1
@.str.25 = private unnamed_addr constant [145 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mwrite_entry failed: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.26 = private unnamed_addr constant [137 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mup failed.: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @pathc_init(i32) #0 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.memset.p0i8.i64(i8* align 8 getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 0, i32 0, i32 0), i8 0, i64 1155072, i1 false)
  store i32 -1, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4, i32 3), align 4
  store i64 -1, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %3 = load i32, i32* %2, align 4
  store i32 %3, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 5), align 8
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @pathc_destroy() #0 {
  %1 = alloca %struct.pathc_t*, align 8
  %2 = alloca i32, align 4
  store %struct.pathc_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 0, i32 0), %struct.pathc_t** %1, align 8
  %3 = call i32 @pathc_alive_down()
  store i32 0, i32* %2, align 4
  br label %4

; <label>:4:                                      ; preds = %31, %0
  %5 = load i32, i32* %2, align 4
  %6 = icmp slt i32 %5, 1024
  br i1 %6, label %7, label %34

; <label>:7:                                      ; preds = %4
  %8 = load %struct.pathc_t*, %struct.pathc_t** %1, align 8
  %9 = load i32, i32* %2, align 4
  %10 = sext i32 %9 to i64
  %11 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %8, i64 %10
  %12 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %11, i32 0, i32 0
  %13 = load i8, i8* %12, align 8
  %14 = trunc i8 %13 to i1
  br i1 %14, label %15, label %30

; <label>:15:                                     ; preds = %7
  %16 = load %struct.pathc_t*, %struct.pathc_t** %1, align 8
  %17 = load i32, i32* %2, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %16, i64 %18
  %20 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %19, i32 0, i32 6
  %21 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %20, align 8
  %22 = call i32 @pthread_mutex_destroy(%struct._opaque_pthread_mutex_t* %21)
  %23 = load %struct.pathc_t*, %struct.pathc_t** %1, align 8
  %24 = load i32, i32* %2, align 4
  %25 = sext i32 %24 to i64
  %26 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %23, i64 %25
  %27 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %26, i32 0, i32 6
  %28 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %27, align 8
  %29 = bitcast %struct._opaque_pthread_mutex_t* %28 to i8*
  call void @free(i8* %29)
  br label %30

; <label>:30:                                     ; preds = %15, %7
  br label %31

; <label>:31:                                     ; preds = %30
  %32 = load i32, i32* %2, align 4
  %33 = add nsw i32 %32, 1
  store i32 %33, i32* %2, align 4
  br label %4

; <label>:34:                                     ; preds = %4
  %35 = call i32 @pathc_alive_up()
  ret void
}

declare i32 @pthread_mutex_destroy(%struct._opaque_pthread_mutex_t*) #2

declare void @free(i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.pathc_t* @pathc_find_path(i8*) #0 {
  %2 = alloca %struct.pathc_t*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca %struct.pathc_t*, align 8
  %5 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  call void @indent(i32 1)
  store %struct.pathc_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 0, i32 0), %struct.pathc_t** %4, align 8
  %6 = call i32 @pathc_alive_down()
  store i32 0, i32* %5, align 4
  br label %7

; <label>:7:                                      ; preds = %35, %1
  %8 = load i32, i32* %5, align 4
  %9 = icmp slt i32 %8, 1024
  br i1 %9, label %10, label %38

; <label>:10:                                     ; preds = %7
  %11 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %12 = load i32, i32* %5, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %11, i64 %13
  %15 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %14, i32 0, i32 0
  %16 = load i8, i8* %15, align 8
  %17 = trunc i8 %16 to i1
  br i1 %17, label %18, label %34

; <label>:18:                                     ; preds = %10
  %19 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %20 = load i32, i32* %5, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %19, i64 %21
  %23 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %22, i32 0, i32 1
  %24 = getelementptr inbounds [1025 x i8], [1025 x i8]* %23, i32 0, i32 0
  %25 = load i8*, i8** %3, align 8
  %26 = call i32 @strcmp(i8* %24, i8* %25)
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %28, label %34

; <label>:28:                                     ; preds = %18
  call void @indent(i32 -1)
  %29 = call i32 @pathc_alive_up()
  %30 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %31 = load i32, i32* %5, align 4
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %30, i64 %32
  store %struct.pathc_t* %33, %struct.pathc_t** %2, align 8
  br label %40

; <label>:34:                                     ; preds = %18, %10
  br label %35

; <label>:35:                                     ; preds = %34
  %36 = load i32, i32* %5, align 4
  %37 = add nsw i32 %36, 1
  store i32 %37, i32* %5, align 4
  br label %7

; <label>:38:                                     ; preds = %7
  %39 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  store %struct.pathc_t* null, %struct.pathc_t** %2, align 8
  br label %40

; <label>:40:                                     ; preds = %38, %28
  %41 = load %struct.pathc_t*, %struct.pathc_t** %2, align 8
  ret %struct.pathc_t* %41
}

declare void @indent(i32) #2

declare i32 @strcmp(i8*, i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.pathc_t* @pathc_find_fd(i64) #0 {
  %2 = alloca i64, align 8
  %3 = alloca %struct.pathc_t*, align 8
  %4 = alloca %struct.pathc_t*, align 8
  %5 = alloca i32, align 4
  store i64 %0, i64* %2, align 8
  call void @indent(i32 1)
  store %struct.pathc_t* null, %struct.pathc_t** %3, align 8
  store %struct.pathc_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 0, i32 0), %struct.pathc_t** %4, align 8
  %6 = load i64, i64* %2, align 8
  %7 = lshr i64 %6, 4
  %8 = icmp ne i64 0, %7
  br i1 %8, label %9, label %10

; <label>:9:                                      ; preds = %1
  call void @dbg(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 77, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([137 x i8], [137 x i8]* @.str.2, i32 0, i32 0))
  br label %10

; <label>:10:                                     ; preds = %9, %1
  %11 = call i32 @pathc_alive_down()
  store i32 0, i32* %5, align 4
  br label %12

; <label>:12:                                     ; preds = %46, %10
  %13 = load i32, i32* %5, align 4
  %14 = icmp slt i32 %13, 1024
  br i1 %14, label %15, label %49

; <label>:15:                                     ; preds = %12
  %16 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %17 = load i32, i32* %5, align 4
  %18 = sext i32 %17 to i64
  %19 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %16, i64 %18
  %20 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %19, i32 0, i32 0
  %21 = load i8, i8* %20, align 8
  %22 = trunc i8 %21 to i1
  br i1 %22, label %23, label %45

; <label>:23:                                     ; preds = %15
  %24 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %25 = load i32, i32* %5, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %24, i64 %26
  %28 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %27, i32 0, i32 5
  %29 = load i64, i64* %28, align 8
  %30 = load i64, i64* %2, align 8
  %31 = icmp eq i64 %29, %30
  br i1 %31, label %32, label %45

; <label>:32:                                     ; preds = %23
  %33 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %34 = load i32, i32* %5, align 4
  %35 = sext i32 %34 to i64
  %36 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %33, i64 %35
  %37 = load i64, i64* %2, align 8
  %38 = call %struct.fdc_t* @fdc_find(i64 %37)
  %39 = call i32 @pathc_link(%struct.pathc_t* %36, %struct.fdc_t* %38)
  %40 = load i64, i64* %2, align 8
  call void @dbgn(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 83, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.3, i32 0, i32 0), i64 %40)
  %41 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %42 = load i32, i32* %5, align 4
  %43 = sext i32 %42 to i64
  %44 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %41, i64 %43
  store %struct.pathc_t* %44, %struct.pathc_t** %3, align 8
  br label %49

; <label>:45:                                     ; preds = %23, %15
  br label %46

; <label>:46:                                     ; preds = %45
  %47 = load i32, i32* %5, align 4
  %48 = add nsw i32 %47, 1
  store i32 %48, i32* %5, align 4
  br label %12

; <label>:49:                                     ; preds = %32, %12
  %50 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  %51 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  ret %struct.pathc_t* %51
}

declare void @dbg(i8*, i32, i8*, i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_link(%struct.pathc_t*, %struct.fdc_t*) #0 {
  %3 = alloca %struct.pathc_t*, align 8
  %4 = alloca %struct.fdc_t*, align 8
  store %struct.pathc_t* %0, %struct.pathc_t** %3, align 8
  store %struct.fdc_t* %1, %struct.fdc_t** %4, align 8
  call void @indent(i32 1)
  %5 = load %struct.fdc_t*, %struct.fdc_t** %4, align 8
  %6 = icmp ne %struct.fdc_t* %5, null
  br i1 %6, label %7, label %11

; <label>:7:                                      ; preds = %2
  %8 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %9 = load %struct.fdc_t*, %struct.fdc_t** %4, align 8
  %10 = getelementptr inbounds %struct.fdc_t, %struct.fdc_t* %9, i32 0, i32 2
  store %struct.pathc_t* %8, %struct.pathc_t** %10, align 8
  br label %11

; <label>:11:                                     ; preds = %7, %2
  %12 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %13 = icmp ne %struct.pathc_t* %12, null
  br i1 %13, label %14, label %71

; <label>:14:                                     ; preds = %11
  %15 = load %struct.fdc_t*, %struct.fdc_t** %4, align 8
  %16 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %17 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %16, i32 0, i32 3
  store %struct.fdc_t* %15, %struct.fdc_t** %17, align 8
  %18 = load %struct.fdc_t*, %struct.fdc_t** %4, align 8
  %19 = icmp ne %struct.fdc_t* %18, null
  br i1 %19, label %20, label %49

; <label>:20:                                     ; preds = %14
  %21 = load %struct.fdc_t*, %struct.fdc_t** %4, align 8
  %22 = getelementptr inbounds %struct.fdc_t, %struct.fdc_t* %21, i32 0, i32 1
  %23 = load i64, i64* %22, align 8
  %24 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %25 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %24, i32 0, i32 5
  store i64 %23, i64* %25, align 8
  %26 = load i32, i32* @debug_enable, align 4
  %27 = icmp eq i32 %26, 1
  br i1 %27, label %28, label %48

; <label>:28:                                     ; preds = %20
  %29 = load i32, i32* @debug_disable_method, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %31, label %48

; <label>:31:                                     ; preds = %28
  %32 = load i32, i32* @debug_disable_external, align 4
  %33 = icmp ne i32 %32, 1
  br i1 %33, label %34, label %48

; <label>:34:                                     ; preds = %31
  %35 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %36 = icmp ne %struct.__sFILE* %35, null
  br i1 %36, label %37, label %48

; <label>:37:                                     ; preds = %34
  %38 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %39 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %40 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %39, i32 0, i32 4
  %41 = load i64, i64* %40, align 8
  %42 = load %struct.fdc_t*, %struct.fdc_t** %4, align 8
  %43 = getelementptr inbounds %struct.fdc_t, %struct.fdc_t* %42, i32 0, i32 1
  %44 = load i64, i64* %43, align 8
  %45 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %38, i8* getelementptr inbounds ([213 x i8], [213 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 135, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %41, i64 %44)
  %46 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %47 = call i32 @fflush(%struct.__sFILE* %46)
  br label %48

; <label>:48:                                     ; preds = %37, %34, %31, %28, %20
  br label %70

; <label>:49:                                     ; preds = %14
  %50 = load i32, i32* @debug_enable, align 4
  %51 = icmp eq i32 %50, 1
  br i1 %51, label %52, label %69

; <label>:52:                                     ; preds = %49
  %53 = load i32, i32* @debug_disable_method, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %55, label %69

; <label>:55:                                     ; preds = %52
  %56 = load i32, i32* @debug_disable_external, align 4
  %57 = icmp ne i32 %56, 1
  br i1 %57, label %58, label %69

; <label>:58:                                     ; preds = %55
  %59 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %60 = icmp ne %struct.__sFILE* %59, null
  br i1 %60, label %61, label %69

; <label>:61:                                     ; preds = %58
  %62 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %63 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %64 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %63, i32 0, i32 4
  %65 = load i64, i64* %64, align 8
  %66 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %62, i8* getelementptr inbounds ([187 x i8], [187 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 138, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %65)
  %67 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %68 = call i32 @fflush(%struct.__sFILE* %67)
  br label %69

; <label>:69:                                     ; preds = %61, %58, %55, %52, %49
  br label %70

; <label>:70:                                     ; preds = %69, %48
  br label %96

; <label>:71:                                     ; preds = %11
  %72 = load %struct.fdc_t*, %struct.fdc_t** %4, align 8
  %73 = icmp ne %struct.fdc_t* %72, null
  br i1 %73, label %74, label %95

; <label>:74:                                     ; preds = %71
  %75 = load i32, i32* @debug_enable, align 4
  %76 = icmp eq i32 %75, 1
  br i1 %76, label %77, label %94

; <label>:77:                                     ; preds = %74
  %78 = load i32, i32* @debug_disable_method, align 4
  %79 = icmp eq i32 %78, 0
  br i1 %79, label %80, label %94

; <label>:80:                                     ; preds = %77
  %81 = load i32, i32* @debug_disable_external, align 4
  %82 = icmp ne i32 %81, 1
  br i1 %82, label %83, label %94

; <label>:83:                                     ; preds = %80
  %84 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %85 = icmp ne %struct.__sFILE* %84, null
  br i1 %85, label %86, label %94

; <label>:86:                                     ; preds = %83
  %87 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %88 = load %struct.fdc_t*, %struct.fdc_t** %4, align 8
  %89 = getelementptr inbounds %struct.fdc_t, %struct.fdc_t* %88, i32 0, i32 1
  %90 = load i64, i64* %89, align 8
  %91 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %87, i8* getelementptr inbounds ([196 x i8], [196 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 142, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %90)
  %92 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %93 = call i32 @fflush(%struct.__sFILE* %92)
  br label %94

; <label>:94:                                     ; preds = %86, %83, %80, %77, %74
  br label %95

; <label>:95:                                     ; preds = %94, %71
  br label %96

; <label>:96:                                     ; preds = %95, %70
  call void @indent(i32 -1)
  %97 = load %struct.fdc_t*, %struct.fdc_t** %4, align 8
  %98 = icmp ne %struct.fdc_t* %97, null
  %99 = zext i1 %98 to i32
  ret i32 %99
}

declare %struct.fdc_t* @fdc_find(i64) #2

declare void @dbgn(i8*, i32, i8*, i8*, i64) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.pathc_t* @pathc_find_offset(i64) #0 {
  %2 = alloca i64, align 8
  %3 = alloca %struct.pathc_t*, align 8
  %4 = alloca %struct.pathc_t*, align 8
  %5 = alloca i32, align 4
  store i64 %0, i64* %2, align 8
  call void @indent(i32 1)
  store %struct.pathc_t* null, %struct.pathc_t** %3, align 8
  store %struct.pathc_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 0, i32 0), %struct.pathc_t** %4, align 8
  %6 = call i32 @pathc_alive_down()
  store i32 0, i32* %5, align 4
  br label %7

; <label>:7:                                      ; preds = %34, %1
  %8 = load i32, i32* %5, align 4
  %9 = icmp slt i32 %8, 1024
  br i1 %9, label %10, label %37

; <label>:10:                                     ; preds = %7
  %11 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %12 = load i32, i32* %5, align 4
  %13 = sext i32 %12 to i64
  %14 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %11, i64 %13
  %15 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %14, i32 0, i32 0
  %16 = load i8, i8* %15, align 8
  %17 = trunc i8 %16 to i1
  br i1 %17, label %18, label %33

; <label>:18:                                     ; preds = %10
  %19 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %20 = load i32, i32* %5, align 4
  %21 = sext i32 %20 to i64
  %22 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %19, i64 %21
  %23 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %22, i32 0, i32 4
  %24 = load i64, i64* %23, align 8
  %25 = load i64, i64* %2, align 8
  %26 = icmp eq i64 %24, %25
  br i1 %26, label %27, label %33

; <label>:27:                                     ; preds = %18
  %28 = load i64, i64* %2, align 8
  call void @dbgn(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 103, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([35 x i8], [35 x i8]* @.str.3, i32 0, i32 0), i64 %28)
  %29 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %30 = load i32, i32* %5, align 4
  %31 = sext i32 %30 to i64
  %32 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %29, i64 %31
  store %struct.pathc_t* %32, %struct.pathc_t** %3, align 8
  br label %37

; <label>:33:                                     ; preds = %18, %10
  br label %34

; <label>:34:                                     ; preds = %33
  %35 = load i32, i32* %5, align 4
  %36 = add nsw i32 %35, 1
  store i32 %36, i32* %5, align 4
  br label %7

; <label>:37:                                     ; preds = %27, %7
  %38 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  %39 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  ret %struct.pathc_t* %39
}

declare i32 @fprintf(%struct.__sFILE*, i8*, ...) #2

declare i32 @fflush(%struct.__sFILE*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @pathc_new(%struct.pathc_t* noalias sret, i8*, %struct.dir_t* byval align 8, i64) #0 {
  %5 = alloca i8*, align 8
  %6 = alloca i64, align 8
  %7 = alloca i32, align 4
  store i8* %1, i8** %5, align 8
  store i64 %3, i64* %6, align 8
  %8 = bitcast %struct.pathc_t* %0 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %8, i8 0, i64 1128, i1 false)
  %9 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %0, i32 0, i32 0
  store i8 0, i8* %9, align 8
  %10 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %0, i32 0, i32 2
  %11 = bitcast %struct.dir_t* %10 to i8*
  %12 = bitcast %struct.dir_t* %2 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %11, i8* align 8 %12, i64 64, i1 false)
  %13 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %0, i32 0, i32 4
  %14 = load i64, i64* %6, align 8
  store i64 %14, i64* %13, align 8
  %15 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %0, i32 0, i32 5
  store i64 1025, i64* %15, align 8
  %16 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %0, i32 0, i32 6
  %17 = call i8* @malloc(i64 64) #5
  %18 = bitcast i8* %17 to %struct._opaque_pthread_mutex_t*
  store %struct._opaque_pthread_mutex_t* %18, %struct._opaque_pthread_mutex_t** %16, align 8
  %19 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %0, i32 0, i32 6
  %20 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %19, align 8
  %21 = call i32 @pthread_mutex_init(%struct._opaque_pthread_mutex_t* %20, %struct._opaque_pthread_mutexattr_t* null)
  store i32 %21, i32* %7, align 4
  %22 = load i32, i32* %7, align 4
  %23 = icmp ne i32 %22, 0
  br i1 %23, label %24, label %28

; <label>:24:                                     ; preds = %4
  %25 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %26 = load i8*, i8** %5, align 8
  %27 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %25, i8* getelementptr inbounds ([147 x i8], [147 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 173, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %26)
  call void @quit(i32 1, i32 1)
  br label %28

; <label>:28:                                     ; preds = %24, %4
  %29 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %0, i32 0, i32 1
  %30 = getelementptr inbounds [1025 x i8], [1025 x i8]* %29, i32 0, i32 0
  %31 = load i8*, i8** %5, align 8
  %32 = call i8* @__strncpy_chk(i8* %30, i8* %31, i64 1025, i64 1025) #6
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #1

; Function Attrs: allocsize(0)
declare i8* @malloc(i64) #3

declare i32 @pthread_mutex_init(%struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutexattr_t*) #2

declare void @quit(i32, i32) #2

; Function Attrs: nounwind
declare i8* @__strncpy_chk(i8*, i8*, i64, i64) #4

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_insert(i8*, %struct.dir_t* byval align 8, i64, %struct.pathc_t**) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i8*, align 8
  %7 = alloca i64, align 8
  %8 = alloca %struct.pathc_t**, align 8
  %9 = alloca %struct.pathc_t*, align 8
  %10 = alloca i32, align 4
  %11 = alloca %struct.pathc_t, align 8
  %12 = alloca i32, align 4
  %13 = alloca %struct._opaque_pthread_mutex_t*, align 8
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca %struct.pathc_t*, align 8
  %19 = alloca %struct.pathc_t*, align 8
  %20 = alloca i32, align 4
  store i8* %0, i8** %6, align 8
  store i64 %2, i64* %7, align 8
  store %struct.pathc_t** %3, %struct.pathc_t*** %8, align 8
  call void @indent(i32 1)
  store %struct.pathc_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 0, i32 0), %struct.pathc_t** %9, align 8
  %21 = call i32 @pathc_alive_down()
  store i32 0, i32* %10, align 4
  br label %22

; <label>:22:                                     ; preds = %116, %4
  %23 = load i32, i32* %10, align 4
  %24 = icmp slt i32 %23, 1024
  br i1 %24, label %25, label %119

; <label>:25:                                     ; preds = %22
  %26 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %27 = load i32, i32* %10, align 4
  %28 = sext i32 %27 to i64
  %29 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %26, i64 %28
  %30 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %29, i32 0, i32 0
  %31 = load i8, i8* %30, align 8
  %32 = trunc i8 %31 to i1
  br i1 %32, label %33, label %115

; <label>:33:                                     ; preds = %25
  %34 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %35 = load i32, i32* %10, align 4
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %34, i64 %36
  %38 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %37, i32 0, i32 1
  %39 = getelementptr inbounds [1025 x i8], [1025 x i8]* %38, i32 0, i32 0
  %40 = load i8*, i8** %6, align 8
  %41 = call i32 @strcmp(i8* %39, i8* %40)
  %42 = icmp eq i32 %41, 0
  br i1 %42, label %43, label %115

; <label>:43:                                     ; preds = %33
  %44 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %45 = load i32, i32* %10, align 4
  %46 = sext i32 %45 to i64
  %47 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %44, i64 %46
  %48 = call i32 @pathc_trylock(%struct.pathc_t* %47)
  %49 = icmp ne i32 %48, 0
  br i1 %49, label %114, label %50

; <label>:50:                                     ; preds = %43
  %51 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %52 = load i32, i32* %10, align 4
  %53 = sext i32 %52 to i64
  %54 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %51, i64 %53
  %55 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %54, i32 0, i32 2
  %56 = bitcast %struct.dir_t* %55 to i8*
  %57 = bitcast %struct.dir_t* %1 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %56, i8* align 8 %57, i64 64, i1 false)
  %58 = load i64, i64* %7, align 8
  %59 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %60 = load i32, i32* %10, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %59, i64 %61
  %63 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %62, i32 0, i32 4
  store i64 %58, i64* %63, align 8
  %64 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %65 = load i32, i32* %10, align 4
  %66 = sext i32 %65 to i64
  %67 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %64, i64 %66
  %68 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %67, i32 0, i32 0
  store i8 1, i8* %68, align 8
  %69 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %70 = load i32, i32* %10, align 4
  %71 = sext i32 %70 to i64
  %72 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %69, i64 %71
  %73 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %72, i32 0, i32 3
  %74 = load %struct.fdc_t*, %struct.fdc_t** %73, align 8
  %75 = icmp ne %struct.fdc_t* %74, null
  br i1 %75, label %76, label %98

; <label>:76:                                     ; preds = %50
  %77 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %78 = load i32, i32* %10, align 4
  %79 = sext i32 %78 to i64
  %80 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %77, i64 %79
  %81 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %80, i32 0, i32 3
  %82 = load %struct.fdc_t*, %struct.fdc_t** %81, align 8
  %83 = getelementptr inbounds %struct.fdc_t, %struct.fdc_t* %82, i32 0, i32 0
  store i8 0, i8* %83, align 8
  %84 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %85 = load i32, i32* %10, align 4
  %86 = sext i32 %85 to i64
  %87 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %84, i64 %86
  %88 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %87, i32 0, i32 3
  %89 = load %struct.fdc_t*, %struct.fdc_t** %88, align 8
  %90 = getelementptr inbounds %struct.fdc_t, %struct.fdc_t* %89, i32 0, i32 1
  %91 = load i64, i64* %90, align 8
  %92 = call i32 @fdc_release(i64 %91)
  %93 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %94 = load i32, i32* %10, align 4
  %95 = sext i32 %94 to i64
  %96 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %93, i64 %95
  %97 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %96, i32 0, i32 5
  store i64 0, i64* %97, align 8
  br label %98

; <label>:98:                                     ; preds = %76, %50
  %99 = load %struct.pathc_t**, %struct.pathc_t*** %8, align 8
  %100 = icmp ne %struct.pathc_t** %99, null
  br i1 %100, label %101, label %107

; <label>:101:                                    ; preds = %98
  %102 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %103 = load i32, i32* %10, align 4
  %104 = sext i32 %103 to i64
  %105 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %102, i64 %104
  %106 = load %struct.pathc_t**, %struct.pathc_t*** %8, align 8
  store %struct.pathc_t* %105, %struct.pathc_t** %106, align 8
  br label %107

; <label>:107:                                    ; preds = %101, %98
  %108 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %109 = load i32, i32* %10, align 4
  %110 = sext i32 %109 to i64
  %111 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %108, i64 %110
  %112 = call i32 @pathc_up(%struct.pathc_t* %111)
  %113 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  store i32 0, i32* %5, align 4
  br label %353

; <label>:114:                                    ; preds = %43
  br label %115

; <label>:115:                                    ; preds = %114, %33, %25
  br label %116

; <label>:116:                                    ; preds = %115
  %117 = load i32, i32* %10, align 4
  %118 = add nsw i32 %117, 1
  store i32 %118, i32* %10, align 4
  br label %22

; <label>:119:                                    ; preds = %22
  %120 = call i32 @pathc_alive_up()
  %121 = load i8*, i8** %6, align 8
  %122 = load i64, i64* %7, align 8
  call void @pathc_new(%struct.pathc_t* sret %11, i8* %121, %struct.dir_t* byval align 8 %1, i64 %122)
  %123 = call i32 @pathc_alive_down()
  store i32 0, i32* %12, align 4
  br label %124

; <label>:124:                                    ; preds = %233, %119
  %125 = load i32, i32* %12, align 4
  %126 = icmp slt i32 %125, 1024
  br i1 %126, label %127, label %236

; <label>:127:                                    ; preds = %124
  %128 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %129 = load i32, i32* %12, align 4
  %130 = sext i32 %129 to i64
  %131 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %128, i64 %130
  %132 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %131, i32 0, i32 0
  %133 = load i8, i8* %132, align 8
  %134 = trunc i8 %133 to i1
  br i1 %134, label %232, label %135

; <label>:135:                                    ; preds = %127
  %136 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %137 = load i32, i32* %12, align 4
  %138 = sext i32 %137 to i64
  %139 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %136, i64 %138
  %140 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %139, i32 0, i32 6
  %141 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %140, align 8
  store %struct._opaque_pthread_mutex_t* %141, %struct._opaque_pthread_mutex_t** %13, align 8
  %142 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %13, align 8
  %143 = icmp ne %struct._opaque_pthread_mutex_t* %142, null
  br i1 %143, label %144, label %155

; <label>:144:                                    ; preds = %135
  %145 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %146 = load i32, i32* %12, align 4
  %147 = sext i32 %146 to i64
  %148 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %145, i64 %147
  %149 = call i32 @pathc_down(%struct.pathc_t* %148)
  store i32 %149, i32* %14, align 4
  %150 = load i32, i32* %14, align 4
  %151 = icmp ne i32 %150, 0
  br i1 %151, label %152, label %154

; <label>:152:                                    ; preds = %144
  call void @indent(i32 -1)
  %153 = call i32 @pathc_alive_up()
  store i32 -1, i32* %5, align 4
  br label %353

; <label>:154:                                    ; preds = %144
  br label %155

; <label>:155:                                    ; preds = %154, %135
  %156 = load i32, i32* @debug_enable, align 4
  %157 = icmp eq i32 %156, 1
  br i1 %157, label %158, label %174

; <label>:158:                                    ; preds = %155
  %159 = load i32, i32* @debug_disable_method, align 4
  %160 = icmp eq i32 %159, 0
  br i1 %160, label %161, label %174

; <label>:161:                                    ; preds = %158
  %162 = load i32, i32* @debug_disable_external, align 4
  %163 = icmp ne i32 %162, 1
  br i1 %163, label %164, label %174

; <label>:164:                                    ; preds = %161
  %165 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %166 = icmp ne %struct.__sFILE* %165, null
  br i1 %166, label %167, label %174

; <label>:167:                                    ; preds = %164
  %168 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %169 = load i8*, i8** %6, align 8
  %170 = load i32, i32* %12, align 4
  %171 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %168, i8* getelementptr inbounds ([226 x i8], [226 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 232, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %169, i32 %170)
  %172 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %173 = call i32 @fflush(%struct.__sFILE* %172)
  br label %174

; <label>:174:                                    ; preds = %167, %164, %161, %158, %155
  %175 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %176 = load i32, i32* %12, align 4
  %177 = sext i32 %176 to i64
  %178 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %175, i64 %177
  %179 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %178, i32 0, i32 6
  %180 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %179, align 8
  %181 = icmp ne %struct._opaque_pthread_mutex_t* %180, null
  br i1 %181, label %182, label %196

; <label>:182:                                    ; preds = %174
  %183 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %11, i32 0, i32 6
  %184 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %183, align 8
  %185 = call i32 @pthread_mutex_destroy(%struct._opaque_pthread_mutex_t* %184)
  %186 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %11, i32 0, i32 6
  %187 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %186, align 8
  %188 = bitcast %struct._opaque_pthread_mutex_t* %187 to i8*
  call void @free(i8* %188)
  %189 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %190 = load i32, i32* %12, align 4
  %191 = sext i32 %190 to i64
  %192 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %189, i64 %191
  %193 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %192, i32 0, i32 6
  %194 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %193, align 8
  %195 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %11, i32 0, i32 6
  store %struct._opaque_pthread_mutex_t* %194, %struct._opaque_pthread_mutex_t** %195, align 8
  br label %196

; <label>:196:                                    ; preds = %182, %174
  %197 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %198 = load i32, i32* %12, align 4
  %199 = sext i32 %198 to i64
  %200 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %197, i64 %199
  %201 = bitcast %struct.pathc_t* %200 to i8*
  %202 = bitcast %struct.pathc_t* %11 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %201, i8* align 8 %202, i64 1128, i1 false)
  %203 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %204 = load i32, i32* %12, align 4
  %205 = sext i32 %204 to i64
  %206 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %203, i64 %205
  %207 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %206, i32 0, i32 0
  store i8 1, i8* %207, align 8
  %208 = load %struct.pathc_t**, %struct.pathc_t*** %8, align 8
  %209 = icmp ne %struct.pathc_t** %208, null
  br i1 %209, label %210, label %216

; <label>:210:                                    ; preds = %196
  %211 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %212 = load i32, i32* %12, align 4
  %213 = sext i32 %212 to i64
  %214 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %211, i64 %213
  %215 = load %struct.pathc_t**, %struct.pathc_t*** %8, align 8
  store %struct.pathc_t* %214, %struct.pathc_t** %215, align 8
  br label %216

; <label>:216:                                    ; preds = %210, %196
  %217 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %13, align 8
  %218 = icmp ne %struct._opaque_pthread_mutex_t* %217, null
  br i1 %218, label %219, label %230

; <label>:219:                                    ; preds = %216
  %220 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %221 = load i32, i32* %12, align 4
  %222 = sext i32 %221 to i64
  %223 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %220, i64 %222
  %224 = call i32 @pathc_up(%struct.pathc_t* %223)
  store i32 %224, i32* %15, align 4
  %225 = load i32, i32* %15, align 4
  %226 = icmp ne i32 %225, 0
  br i1 %226, label %227, label %229

; <label>:227:                                    ; preds = %219
  call void @indent(i32 -1)
  %228 = call i32 @pathc_alive_up()
  store i32 -2, i32* %5, align 4
  br label %353

; <label>:229:                                    ; preds = %219
  br label %230

; <label>:230:                                    ; preds = %229, %216
  %231 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  store i32 0, i32* %5, align 4
  br label %353

; <label>:232:                                    ; preds = %127
  br label %233

; <label>:233:                                    ; preds = %232
  %234 = load i32, i32* %12, align 4
  %235 = add nsw i32 %234, 1
  store i32 %235, i32* %12, align 4
  br label %124

; <label>:236:                                    ; preds = %124
  %237 = call i32 @pathc_alive_up()
  %238 = call i32 @pathc_alive_down()
  %239 = icmp ne i32 %238, 0
  br i1 %239, label %240, label %241

; <label>:240:                                    ; preds = %236
  call void @indent(i32 -1)
  store i32 -4, i32* %5, align 4
  br label %353

; <label>:241:                                    ; preds = %236
  store i32 0, i32* %16, align 4
  store %struct.pathc_t* null, %struct.pathc_t** %18, align 8
  br label %242

; <label>:242:                                    ; preds = %281, %241
  %243 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %244 = load i32, i32* @pathc_overflow_index, align 4
  %245 = sext i32 %244 to i64
  %246 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %243, i64 %245
  %247 = call i32 @pathc_trylock(%struct.pathc_t* %246)
  store i32 %247, i32* %17, align 4
  %248 = load i32, i32* %17, align 4
  %249 = icmp ne i32 %248, 0
  br i1 %249, label %250, label %254

; <label>:250:                                    ; preds = %242
  %251 = load i32, i32* @pathc_overflow_index, align 4
  %252 = add nsw i32 %251, 1
  %253 = srem i32 %252, 1024
  store i32 %253, i32* @pathc_overflow_index, align 4
  br label %259

; <label>:254:                                    ; preds = %242
  %255 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %256 = load i32, i32* @pathc_overflow_index, align 4
  %257 = sext i32 %256 to i64
  %258 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %255, i64 %257
  store %struct.pathc_t* %258, %struct.pathc_t** %18, align 8
  br label %282

; <label>:259:                                    ; preds = %250
  %260 = load i32, i32* %16, align 4
  %261 = add nsw i32 %260, 1
  store i32 %261, i32* %16, align 4
  %262 = icmp eq i32 %261, 1024
  br i1 %262, label %263, label %281

; <label>:263:                                    ; preds = %259
  %264 = load i32, i32* @debug_enable, align 4
  %265 = icmp eq i32 %264, 1
  br i1 %265, label %266, label %280

; <label>:266:                                    ; preds = %263
  %267 = load i32, i32* @debug_disable_method, align 4
  %268 = icmp eq i32 %267, 0
  br i1 %268, label %269, label %280

; <label>:269:                                    ; preds = %266
  %270 = load i32, i32* @debug_disable_external, align 4
  %271 = icmp ne i32 %270, 1
  br i1 %271, label %272, label %280

; <label>:272:                                    ; preds = %269
  %273 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %274 = icmp ne %struct.__sFILE* %273, null
  br i1 %274, label %275, label %280

; <label>:275:                                    ; preds = %272
  %276 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %277 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %276, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 277, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.14, i32 0, i32 0))
  %278 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %279 = call i32 @fflush(%struct.__sFILE* %278)
  br label %280

; <label>:280:                                    ; preds = %275, %272, %269, %266, %263
  store i32 -3, i32* %5, align 4
  br label %353

; <label>:281:                                    ; preds = %259
  br label %242

; <label>:282:                                    ; preds = %254
  %283 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %284 = load i32, i32* @pathc_overflow_index, align 4
  %285 = sext i32 %284 to i64
  %286 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %283, i64 %285
  store %struct.pathc_t* %286, %struct.pathc_t** %19, align 8
  %287 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %11, i32 0, i32 6
  %288 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %287, align 8
  %289 = call i32 @pthread_mutex_destroy(%struct._opaque_pthread_mutex_t* %288)
  %290 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %11, i32 0, i32 6
  %291 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %290, align 8
  %292 = bitcast %struct._opaque_pthread_mutex_t* %291 to i8*
  call void @free(i8* %292)
  %293 = load %struct.pathc_t*, %struct.pathc_t** %19, align 8
  %294 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %293, i32 0, i32 6
  %295 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %294, align 8
  %296 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %11, i32 0, i32 6
  store %struct._opaque_pthread_mutex_t* %295, %struct._opaque_pthread_mutex_t** %296, align 8
  %297 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %298 = load i32, i32* @pathc_overflow_index, align 4
  %299 = sext i32 %298 to i64
  %300 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %297, i64 %299
  %301 = bitcast %struct.pathc_t* %300 to i8*
  %302 = bitcast %struct.pathc_t* %11 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %301, i8* align 8 %302, i64 1128, i1 false)
  %303 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %304 = load i32, i32* @pathc_overflow_index, align 4
  %305 = sext i32 %304 to i64
  %306 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %303, i64 %305
  %307 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %306, i32 0, i32 0
  store i8 1, i8* %307, align 8
  %308 = load %struct.pathc_t**, %struct.pathc_t*** %8, align 8
  %309 = icmp ne %struct.pathc_t** %308, null
  br i1 %309, label %310, label %316

; <label>:310:                                    ; preds = %282
  %311 = load %struct.pathc_t*, %struct.pathc_t** %9, align 8
  %312 = load i32, i32* @pathc_overflow_index, align 4
  %313 = sext i32 %312 to i64
  %314 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %311, i64 %313
  %315 = load %struct.pathc_t**, %struct.pathc_t*** %8, align 8
  store %struct.pathc_t* %314, %struct.pathc_t** %315, align 8
  br label %316

; <label>:316:                                    ; preds = %310, %282
  %317 = load i32, i32* @debug_enable, align 4
  %318 = icmp eq i32 %317, 1
  br i1 %318, label %319, label %334

; <label>:319:                                    ; preds = %316
  %320 = load i32, i32* @debug_disable_method, align 4
  %321 = icmp eq i32 %320, 0
  br i1 %321, label %322, label %334

; <label>:322:                                    ; preds = %319
  %323 = load i32, i32* @debug_disable_external, align 4
  %324 = icmp ne i32 %323, 1
  br i1 %324, label %325, label %334

; <label>:325:                                    ; preds = %322
  %326 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %327 = icmp ne %struct.__sFILE* %326, null
  br i1 %327, label %328, label %334

; <label>:328:                                    ; preds = %325
  %329 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %330 = load i32, i32* @pathc_overflow_index, align 4
  %331 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %329, i8* getelementptr inbounds ([171 x i8], [171 x i8]* @.str.15, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 289, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %330)
  %332 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %333 = call i32 @fflush(%struct.__sFILE* %332)
  br label %334

; <label>:334:                                    ; preds = %328, %325, %322, %319, %316
  %335 = load i32, i32* @pathc_overflow_index, align 4
  %336 = add nsw i32 %335, 1
  %337 = srem i32 %336, 1024
  store i32 %337, i32* @pathc_overflow_index, align 4
  %338 = load %struct.pathc_t*, %struct.pathc_t** %18, align 8
  %339 = icmp ne %struct.pathc_t* %338, null
  br i1 %339, label %340, label %348

; <label>:340:                                    ; preds = %334
  %341 = load %struct.pathc_t*, %struct.pathc_t** %18, align 8
  %342 = call i32 @pathc_up(%struct.pathc_t* %341)
  store i32 %342, i32* %20, align 4
  %343 = load i32, i32* %20, align 4
  %344 = icmp ne i32 %343, 0
  br i1 %344, label %345, label %347

; <label>:345:                                    ; preds = %340
  call void @indent(i32 -1)
  %346 = call i32 @pathc_alive_up()
  store i32 -5, i32* %5, align 4
  br label %353

; <label>:347:                                    ; preds = %340
  br label %348

; <label>:348:                                    ; preds = %347, %334
  %349 = call i32 @pathc_alive_up()
  %350 = icmp ne i32 %349, 0
  br i1 %350, label %351, label %352

; <label>:351:                                    ; preds = %348
  call void @indent(i32 -1)
  store i32 -4, i32* %5, align 4
  br label %353

; <label>:352:                                    ; preds = %348
  call void @indent(i32 -1)
  store i32 1, i32* %5, align 4
  br label %353

; <label>:353:                                    ; preds = %352, %351, %345, %280, %240, %230, %227, %152, %107
  %354 = load i32, i32* %5, align 4
  ret i32 %354
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_trylock(%struct.pathc_t*) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.pathc_t*, align 8
  %4 = alloca i32, align 4
  store %struct.pathc_t* %0, %struct.pathc_t** %3, align 8
  %5 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %6 = icmp eq %struct.pathc_t* %5, null
  br i1 %6, label %7, label %8

; <label>:7:                                      ; preds = %1
  store i32 1, i32* %2, align 4
  br label %14

; <label>:8:                                      ; preds = %1
  %9 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %10 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %9, i32 0, i32 6
  %11 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %10, align 8
  %12 = call i32 @pthread_mutex_trylock(%struct._opaque_pthread_mutex_t* %11)
  store i32 %12, i32* %4, align 4
  %13 = load i32, i32* %4, align 4
  store i32 %13, i32* %2, align 4
  br label %14

; <label>:14:                                     ; preds = %8, %7
  %15 = load i32, i32* %2, align 4
  ret i32 %15
}

declare i32 @fdc_release(i64) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_up(%struct.pathc_t*) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.pathc_t*, align 8
  store %struct.pathc_t* %0, %struct.pathc_t** %3, align 8
  %4 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %5 = icmp eq %struct.pathc_t* %4, null
  br i1 %5, label %6, label %24

; <label>:6:                                      ; preds = %1
  %7 = load i32, i32* @debug_enable, align 4
  %8 = icmp eq i32 %7, 1
  br i1 %8, label %9, label %23

; <label>:9:                                      ; preds = %6
  %10 = load i32, i32* @debug_disable_method, align 4
  %11 = icmp eq i32 %10, 0
  br i1 %11, label %12, label %23

; <label>:12:                                     ; preds = %9
  %13 = load i32, i32* @debug_disable_external, align 4
  %14 = icmp ne i32 %13, 1
  br i1 %14, label %15, label %23

; <label>:15:                                     ; preds = %12
  %16 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %17 = icmp ne %struct.__sFILE* %16, null
  br i1 %17, label %18, label %23

; <label>:18:                                     ; preds = %15
  %19 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %20 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %19, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 333, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.19, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.17, i32 0, i32 0))
  %21 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %22 = call i32 @fflush(%struct.__sFILE* %21)
  br label %23

; <label>:23:                                     ; preds = %18, %15, %12, %9, %6
  store i32 1, i32* %2, align 4
  br label %53

; <label>:24:                                     ; preds = %1
  %25 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %26 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %25, i32 0, i32 6
  %27 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %26, align 8
  %28 = icmp eq %struct._opaque_pthread_mutex_t* %27, null
  br i1 %28, label %29, label %47

; <label>:29:                                     ; preds = %24
  %30 = load i32, i32* @debug_enable, align 4
  %31 = icmp eq i32 %30, 1
  br i1 %31, label %32, label %46

; <label>:32:                                     ; preds = %29
  %33 = load i32, i32* @debug_disable_method, align 4
  %34 = icmp eq i32 %33, 0
  br i1 %34, label %35, label %46

; <label>:35:                                     ; preds = %32
  %36 = load i32, i32* @debug_disable_external, align 4
  %37 = icmp ne i32 %36, 1
  br i1 %37, label %38, label %46

; <label>:38:                                     ; preds = %35
  %39 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %40 = icmp ne %struct.__sFILE* %39, null
  br i1 %40, label %41, label %46

; <label>:41:                                     ; preds = %38
  %42 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %43 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %42, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 336, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.19, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.18, i32 0, i32 0))
  %44 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %45 = call i32 @fflush(%struct.__sFILE* %44)
  br label %46

; <label>:46:                                     ; preds = %41, %38, %35, %32, %29
  store i32 2, i32* %2, align 4
  br label %53

; <label>:47:                                     ; preds = %24
  br label %48

; <label>:48:                                     ; preds = %47
  %49 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %50 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %49, i32 0, i32 6
  %51 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %50, align 8
  %52 = call i32 @pthread_mutex_unlock(%struct._opaque_pthread_mutex_t* %51)
  store i32 %52, i32* %2, align 4
  br label %53

; <label>:53:                                     ; preds = %48, %46, %23
  %54 = load i32, i32* %2, align 4
  ret i32 %54
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_down(%struct.pathc_t*) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.pathc_t*, align 8
  %4 = alloca i32, align 4
  store %struct.pathc_t* %0, %struct.pathc_t** %3, align 8
  %5 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %6 = icmp eq %struct.pathc_t* %5, null
  br i1 %6, label %7, label %25

; <label>:7:                                      ; preds = %1
  %8 = load i32, i32* @debug_enable, align 4
  %9 = icmp eq i32 %8, 1
  br i1 %9, label %10, label %24

; <label>:10:                                     ; preds = %7
  %11 = load i32, i32* @debug_disable_method, align 4
  %12 = icmp eq i32 %11, 0
  br i1 %12, label %13, label %24

; <label>:13:                                     ; preds = %10
  %14 = load i32, i32* @debug_disable_external, align 4
  %15 = icmp ne i32 %14, 1
  br i1 %15, label %16, label %24

; <label>:16:                                     ; preds = %13
  %17 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %18 = icmp ne %struct.__sFILE* %17, null
  br i1 %18, label %19, label %24

; <label>:19:                                     ; preds = %16
  %20 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %21 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %20, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 308, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.17, i32 0, i32 0))
  %22 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %23 = call i32 @fflush(%struct.__sFILE* %22)
  br label %24

; <label>:24:                                     ; preds = %19, %16, %13, %10, %7
  store i32 1, i32* %2, align 4
  br label %55

; <label>:25:                                     ; preds = %1
  %26 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %27 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %26, i32 0, i32 6
  %28 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %27, align 8
  %29 = icmp eq %struct._opaque_pthread_mutex_t* %28, null
  br i1 %29, label %30, label %48

; <label>:30:                                     ; preds = %25
  %31 = load i32, i32* @debug_enable, align 4
  %32 = icmp eq i32 %31, 1
  br i1 %32, label %33, label %47

; <label>:33:                                     ; preds = %30
  %34 = load i32, i32* @debug_disable_method, align 4
  %35 = icmp eq i32 %34, 0
  br i1 %35, label %36, label %47

; <label>:36:                                     ; preds = %33
  %37 = load i32, i32* @debug_disable_external, align 4
  %38 = icmp ne i32 %37, 1
  br i1 %38, label %39, label %47

; <label>:39:                                     ; preds = %36
  %40 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %41 = icmp ne %struct.__sFILE* %40, null
  br i1 %41, label %42, label %47

; <label>:42:                                     ; preds = %39
  %43 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %44 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %43, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.13, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 311, i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.18, i32 0, i32 0))
  %45 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %46 = call i32 @fflush(%struct.__sFILE* %45)
  br label %47

; <label>:47:                                     ; preds = %42, %39, %36, %33, %30
  store i32 2, i32* %2, align 4
  br label %55

; <label>:48:                                     ; preds = %25
  br label %49

; <label>:49:                                     ; preds = %48
  %50 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %51 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %50, i32 0, i32 6
  %52 = load %struct._opaque_pthread_mutex_t*, %struct._opaque_pthread_mutex_t** %51, align 8
  %53 = call i32 @pthread_mutex_lock(%struct._opaque_pthread_mutex_t* %52)
  store i32 %53, i32* %4, align 4
  %54 = load i32, i32* %4, align 4
  store i32 %54, i32* %2, align 4
  br label %55

; <label>:55:                                     ; preds = %49, %47, %24
  %56 = load i32, i32* %2, align 4
  ret i32 %56
}

declare i32 @pthread_mutex_lock(%struct._opaque_pthread_mutex_t*) #2

declare i32 @pthread_mutex_unlock(%struct._opaque_pthread_mutex_t*) #2

declare i32 @pthread_mutex_trylock(%struct._opaque_pthread_mutex_t*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_alive_down() #0 {
  %1 = call i32 @pthread_mutex_lock(%struct._opaque_pthread_mutex_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 6))
  ret i32 %1
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_alive_up() #0 {
  %1 = call i32 @pthread_mutex_unlock(%struct._opaque_pthread_mutex_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 6))
  ret i32 %1
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_remove_item(%struct.pathc_t*) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.pathc_t*, align 8
  %4 = alloca %struct.pathc_t*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store %struct.pathc_t* %0, %struct.pathc_t** %3, align 8
  %7 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %8 = icmp eq %struct.pathc_t* %7, null
  br i1 %8, label %9, label %10

; <label>:9:                                      ; preds = %1
  store i32 0, i32* %2, align 4
  br label %80

; <label>:10:                                     ; preds = %1
  call void @indent(i32 1)
  %11 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %12 = call i32 @pathc_down(%struct.pathc_t* %11)
  %13 = icmp ne i32 %12, 0
  br i1 %13, label %14, label %15

; <label>:14:                                     ; preds = %10
  store i32 0, i32* %2, align 4
  br label %80

; <label>:15:                                     ; preds = %10
  store %struct.pathc_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 0, i32 0), %struct.pathc_t** %4, align 8
  store i32 0, i32* %5, align 4
  %16 = call i32 @pathc_alive_down()
  store i32 0, i32* %6, align 4
  br label %17

; <label>:17:                                     ; preds = %72, %15
  %18 = load i32, i32* %6, align 4
  %19 = icmp slt i32 %18, 1024
  br i1 %19, label %20, label %75

; <label>:20:                                     ; preds = %17
  %21 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %22 = load i32, i32* %6, align 4
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %21, i64 %23
  %25 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %26 = icmp eq %struct.pathc_t* %24, %25
  br i1 %26, label %27, label %71

; <label>:27:                                     ; preds = %20
  %28 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %29 = load i32, i32* %6, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %28, i64 %30
  %32 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %31, i32 0, i32 0
  %33 = load i8, i8* %32, align 8
  %34 = trunc i8 %33 to i1
  br i1 %34, label %35, label %71

; <label>:35:                                     ; preds = %27
  %36 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %37 = load i32, i32* %6, align 4
  %38 = sext i32 %37 to i64
  %39 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %36, i64 %38
  %40 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %39, i32 0, i32 0
  store i8 0, i8* %40, align 8
  %41 = load i32, i32* @debug_enable, align 4
  %42 = icmp eq i32 %41, 1
  br i1 %42, label %43, label %70

; <label>:43:                                     ; preds = %35
  %44 = load i32, i32* @debug_disable_method, align 4
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %46, label %70

; <label>:46:                                     ; preds = %43
  %47 = load i32, i32* @debug_disable_external, align 4
  %48 = icmp ne i32 %47, 1
  br i1 %48, label %49, label %70

; <label>:49:                                     ; preds = %46
  %50 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %51 = icmp ne %struct.__sFILE* %50, null
  br i1 %51, label %52, label %70

; <label>:52:                                     ; preds = %49
  %53 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %54 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %55 = load i32, i32* %6, align 4
  %56 = sext i32 %55 to i64
  %57 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %54, i64 %56
  %58 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %57, i32 0, i32 1
  %59 = getelementptr inbounds [1025 x i8], [1025 x i8]* %58, i32 0, i32 0
  %60 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %61 = load i32, i32* %6, align 4
  %62 = sext i32 %61 to i64
  %63 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %60, i64 %62
  %64 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %63, i32 0, i32 5
  %65 = load i64, i64* %64, align 8
  %66 = load i32, i32* %6, align 4
  %67 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %53, i8* getelementptr inbounds ([211 x i8], [211 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 432, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %59, i64 %65, i32 %66)
  %68 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %69 = call i32 @fflush(%struct.__sFILE* %68)
  br label %70

; <label>:70:                                     ; preds = %52, %49, %46, %43, %35
  store i32 1, i32* %5, align 4
  br label %75

; <label>:71:                                     ; preds = %27, %20
  br label %72

; <label>:72:                                     ; preds = %71
  %73 = load i32, i32* %6, align 4
  %74 = add nsw i32 %73, 1
  store i32 %74, i32* %6, align 4
  br label %17

; <label>:75:                                     ; preds = %70, %17
  %76 = call i32 @pathc_alive_up()
  %77 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %78 = call i32 @pathc_up(%struct.pathc_t* %77)
  call void @indent(i32 -1)
  %79 = load i32, i32* %5, align 4
  store i32 %79, i32* %2, align 4
  br label %80

; <label>:80:                                     ; preds = %75, %14, %9
  %81 = load i32, i32* %2, align 4
  ret i32 %81
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_remove_path(i8*) #0 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = call %struct.pathc_t* @pathc_find_path(i8* %3)
  %5 = call i32 @pathc_remove_item(%struct.pathc_t* %4)
  ret i32 %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_remove_fd(i64) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i64, align 8
  %4 = alloca %struct.pathc_t*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  store i64 %0, i64* %3, align 8
  call void @indent(i32 1)
  %7 = load i64, i64* %3, align 8
  %8 = lshr i64 %7, 4
  %9 = icmp ne i64 0, %8
  br i1 %9, label %10, label %11

; <label>:10:                                     ; preds = %1
  call void @dbg(i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 460, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.22, i32 0, i32 0), i8* getelementptr inbounds ([137 x i8], [137 x i8]* @.str.2, i32 0, i32 0))
  br label %11

; <label>:11:                                     ; preds = %10, %1
  store %struct.pathc_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 0, i32 0), %struct.pathc_t** %4, align 8
  store i32 2, i32* %5, align 4
  %12 = call i32 @pathc_alive_down()
  store i32 0, i32* %6, align 4
  br label %13

; <label>:13:                                     ; preds = %105, %11
  %14 = load i32, i32* %6, align 4
  %15 = icmp slt i32 %14, 1024
  br i1 %15, label %16, label %108

; <label>:16:                                     ; preds = %13
  %17 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %18 = load i32, i32* %6, align 4
  %19 = sext i32 %18 to i64
  %20 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %17, i64 %19
  %21 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %20, i32 0, i32 0
  %22 = load i8, i8* %21, align 8
  %23 = trunc i8 %22 to i1
  br i1 %23, label %24, label %104

; <label>:24:                                     ; preds = %16
  %25 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %26 = load i32, i32* %6, align 4
  %27 = sext i32 %26 to i64
  %28 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %25, i64 %27
  %29 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %28, i32 0, i32 5
  %30 = load i64, i64* %29, align 8
  %31 = load i64, i64* %3, align 8
  %32 = icmp eq i64 %30, %31
  br i1 %32, label %33, label %104

; <label>:33:                                     ; preds = %24
  %34 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %35 = load i32, i32* %6, align 4
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %34, i64 %36
  %38 = call i32 @pathc_down(%struct.pathc_t* %37)
  %39 = icmp ne i32 %38, 0
  br i1 %39, label %40, label %42

; <label>:40:                                     ; preds = %33
  %41 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  store i32 0, i32* %2, align 4
  br label %110

; <label>:42:                                     ; preds = %33
  %43 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %44 = load i32, i32* %6, align 4
  %45 = sext i32 %44 to i64
  %46 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %43, i64 %45
  %47 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %46, i32 0, i32 5
  %48 = load i64, i64* %47, align 8
  %49 = load i64, i64* %3, align 8
  %50 = icmp eq i64 %48, %49
  br i1 %50, label %51, label %88

; <label>:51:                                     ; preds = %42
  %52 = load i32, i32* @debug_enable, align 4
  %53 = icmp eq i32 %52, 1
  br i1 %53, label %54, label %76

; <label>:54:                                     ; preds = %51
  %55 = load i32, i32* @debug_disable_method, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %57, label %76

; <label>:57:                                     ; preds = %54
  %58 = load i32, i32* @debug_disable_external, align 4
  %59 = icmp ne i32 %58, 1
  br i1 %59, label %60, label %76

; <label>:60:                                     ; preds = %57
  %61 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %62 = icmp ne %struct.__sFILE* %61, null
  br i1 %62, label %63, label %76

; <label>:63:                                     ; preds = %60
  %64 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %65 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %66 = load i32, i32* %6, align 4
  %67 = sext i32 %66 to i64
  %68 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %65, i64 %67
  %69 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %68, i32 0, i32 1
  %70 = getelementptr inbounds [1025 x i8], [1025 x i8]* %69, i32 0, i32 0
  %71 = load i64, i64* %3, align 8
  %72 = load i32, i32* %6, align 4
  %73 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %64, i8* getelementptr inbounds ([211 x i8], [211 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 477, i8* getelementptr inbounds ([41 x i8], [41 x i8]* @.str.22, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %70, i64 %71, i32 %72)
  %74 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %75 = call i32 @fflush(%struct.__sFILE* %74)
  br label %76

; <label>:76:                                     ; preds = %63, %60, %57, %54, %51
  %77 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %78 = load i32, i32* %6, align 4
  %79 = sext i32 %78 to i64
  %80 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %77, i64 %79
  %81 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %80, i32 0, i32 0
  store i8 0, i8* %81, align 8
  %82 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  %83 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %84 = load i32, i32* %6, align 4
  %85 = sext i32 %84 to i64
  %86 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %83, i64 %85
  %87 = call i32 @pathc_up(%struct.pathc_t* %86)
  store i32 %87, i32* %2, align 4
  br label %110

; <label>:88:                                     ; preds = %42
  %89 = load %struct.pathc_t*, %struct.pathc_t** %4, align 8
  %90 = load i32, i32* %6, align 4
  %91 = sext i32 %90 to i64
  %92 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %89, i64 %91
  %93 = call i32 @pathc_up(%struct.pathc_t* %92)
  %94 = icmp ne i32 %93, 0
  br i1 %94, label %95, label %97

; <label>:95:                                     ; preds = %88
  %96 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  store i32 0, i32* %2, align 4
  br label %110

; <label>:97:                                     ; preds = %88
  %98 = load i32, i32* %5, align 4
  %99 = add nsw i32 %98, -1
  store i32 %99, i32* %5, align 4
  %100 = icmp sge i32 %99, 0
  br i1 %100, label %101, label %102

; <label>:101:                                    ; preds = %97
  store i32 0, i32* %6, align 4
  br label %105

; <label>:102:                                    ; preds = %97
  %103 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  store i32 0, i32* %2, align 4
  br label %110

; <label>:104:                                    ; preds = %24, %16
  br label %105

; <label>:105:                                    ; preds = %104, %101
  %106 = load i32, i32* %6, align 4
  %107 = add nsw i32 %106, 1
  store i32 %107, i32* %6, align 4
  br label %13

; <label>:108:                                    ; preds = %13
  %109 = call i32 @pathc_alive_up()
  call void @indent(i32 -1)
  store i32 0, i32* %2, align 4
  br label %110

; <label>:110:                                    ; preds = %108, %102, %95, %76, %40
  %111 = load i32, i32* %2, align 4
  ret i32 %111
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_remove_offset(i64) #0 {
  %2 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  %3 = load i64, i64* %2, align 8
  %4 = call %struct.pathc_t* @pathc_find_offset(i64 %3)
  %5 = call i32 @pathc_remove_item(%struct.pathc_t* %4)
  ret i32 %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @pathc_save_item(%struct.pathc_t*) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.pathc_t*, align 8
  %4 = alloca i32, align 4
  store %struct.pathc_t* %0, %struct.pathc_t** %3, align 8
  %5 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %6 = call i32 @pathc_down(%struct.pathc_t* %5)
  store i32 %6, i32* %4, align 4
  %7 = load i32, i32* %4, align 4
  %8 = icmp slt i32 %7, 0
  br i1 %8, label %9, label %39

; <label>:9:                                      ; preds = %1
  store i32 1, i32* @debug_enable, align 4
  %10 = load i32, i32* @debug_enable, align 4
  %11 = icmp eq i32 %10, 1
  br i1 %11, label %12, label %37

; <label>:12:                                     ; preds = %9
  %13 = load i32, i32* @debug_disable_method, align 4
  %14 = icmp eq i32 %13, 0
  br i1 %14, label %15, label %37

; <label>:15:                                     ; preds = %12
  %16 = load i32, i32* @debug_disable_external, align 4
  %17 = icmp ne i32 %16, 1
  br i1 %17, label %18, label %37

; <label>:18:                                     ; preds = %15
  %19 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %20 = icmp ne %struct.__sFILE* %19, null
  br i1 %20, label %21, label %37

; <label>:21:                                     ; preds = %18
  %22 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %23 = load i32, i32* %4, align 4
  %24 = load i32, i32* %4, align 4
  %25 = icmp slt i32 %24, 0
  br i1 %25, label %26, label %29

; <label>:26:                                     ; preds = %21
  %27 = load i32, i32* %4, align 4
  %28 = sub nsw i32 0, %27
  br label %31

; <label>:29:                                     ; preds = %21
  %30 = load i32, i32* %4, align 4
  br label %31

; <label>:31:                                     ; preds = %29, %26
  %32 = phi i32 [ %28, %26 ], [ %30, %29 ]
  %33 = call i8* @"\01_strerror"(i32 %32)
  %34 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %22, i8* getelementptr inbounds ([145 x i8], [145 x i8]* @.str.23, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 516, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.24, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %23, i8* %33)
  %35 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %36 = call i32 @fflush(%struct.__sFILE* %35)
  br label %37

; <label>:37:                                     ; preds = %31, %18, %15, %12, %9
  %38 = load i32, i32* %4, align 4
  store i32 %38, i32* %2, align 4
  br label %115

; <label>:39:                                     ; preds = %1
  %40 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 5), align 8
  %41 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %42 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %41, i32 0, i32 2
  %43 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %44 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %43, i32 0, i32 4
  %45 = load i64, i64* %44, align 8
  %46 = call i32 @fat_write_entry(i32 %40, %struct.dir_t* %42, i64 %45)
  store i32 %46, i32* %4, align 4
  %47 = load i32, i32* %4, align 4
  %48 = icmp slt i32 %47, 0
  br i1 %48, label %49, label %79

; <label>:49:                                     ; preds = %39
  store i32 1, i32* @debug_enable, align 4
  %50 = load i32, i32* @debug_enable, align 4
  %51 = icmp eq i32 %50, 1
  br i1 %51, label %52, label %77

; <label>:52:                                     ; preds = %49
  %53 = load i32, i32* @debug_disable_method, align 4
  %54 = icmp eq i32 %53, 0
  br i1 %54, label %55, label %77

; <label>:55:                                     ; preds = %52
  %56 = load i32, i32* @debug_disable_external, align 4
  %57 = icmp ne i32 %56, 1
  br i1 %57, label %58, label %77

; <label>:58:                                     ; preds = %55
  %59 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %60 = icmp ne %struct.__sFILE* %59, null
  br i1 %60, label %61, label %77

; <label>:61:                                     ; preds = %58
  %62 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %63 = load i32, i32* %4, align 4
  %64 = load i32, i32* %4, align 4
  %65 = icmp slt i32 %64, 0
  br i1 %65, label %66, label %69

; <label>:66:                                     ; preds = %61
  %67 = load i32, i32* %4, align 4
  %68 = sub nsw i32 0, %67
  br label %71

; <label>:69:                                     ; preds = %61
  %70 = load i32, i32* %4, align 4
  br label %71

; <label>:71:                                     ; preds = %69, %66
  %72 = phi i32 [ %68, %66 ], [ %70, %69 ]
  %73 = call i8* @"\01_strerror"(i32 %72)
  %74 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %62, i8* getelementptr inbounds ([145 x i8], [145 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 519, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.24, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %63, i8* %73)
  %75 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %76 = call i32 @fflush(%struct.__sFILE* %75)
  br label %77

; <label>:77:                                     ; preds = %71, %58, %55, %52, %49
  %78 = load i32, i32* %4, align 4
  store i32 %78, i32* %2, align 4
  br label %115

; <label>:79:                                     ; preds = %39
  %80 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %81 = call i32 @pathc_up(%struct.pathc_t* %80)
  store i32 %81, i32* %4, align 4
  %82 = load i32, i32* %4, align 4
  %83 = icmp slt i32 %82, 0
  br i1 %83, label %84, label %114

; <label>:84:                                     ; preds = %79
  store i32 1, i32* @debug_enable, align 4
  %85 = load i32, i32* @debug_enable, align 4
  %86 = icmp eq i32 %85, 1
  br i1 %86, label %87, label %112

; <label>:87:                                     ; preds = %84
  %88 = load i32, i32* @debug_disable_method, align 4
  %89 = icmp eq i32 %88, 0
  br i1 %89, label %90, label %112

; <label>:90:                                     ; preds = %87
  %91 = load i32, i32* @debug_disable_external, align 4
  %92 = icmp ne i32 %91, 1
  br i1 %92, label %93, label %112

; <label>:93:                                     ; preds = %90
  %94 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %95 = icmp ne %struct.__sFILE* %94, null
  br i1 %95, label %96, label %112

; <label>:96:                                     ; preds = %93
  %97 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %98 = load i32, i32* %4, align 4
  %99 = load i32, i32* %4, align 4
  %100 = icmp slt i32 %99, 0
  br i1 %100, label %101, label %104

; <label>:101:                                    ; preds = %96
  %102 = load i32, i32* %4, align 4
  %103 = sub nsw i32 0, %102
  br label %106

; <label>:104:                                    ; preds = %96
  %105 = load i32, i32* %4, align 4
  br label %106

; <label>:106:                                    ; preds = %104, %101
  %107 = phi i32 [ %103, %101 ], [ %105, %104 ]
  %108 = call i8* @"\01_strerror"(i32 %107)
  %109 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %97, i8* getelementptr inbounds ([137 x i8], [137 x i8]* @.str.26, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0), i32 522, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.24, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %98, i8* %108)
  %110 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %111 = call i32 @fflush(%struct.__sFILE* %110)
  br label %112

; <label>:112:                                    ; preds = %106, %93, %90, %87, %84
  %113 = load i32, i32* %4, align 4
  store i32 %113, i32* %2, align 4
  br label %115

; <label>:114:                                    ; preds = %79
  store i32 0, i32* %2, align 4
  br label %115

; <label>:115:                                    ; preds = %114, %112, %77, %37
  %116 = load i32, i32* %2, align 4
  ret i32 %116
}

declare i8* @"\01_strerror"(i32) #2

declare i32 @fat_write_entry(i32, %struct.dir_t*, i64) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @pathc_count_free() #0 {
  %1 = alloca i64, align 8
  %2 = alloca i64, align 8
  %3 = alloca i32, align 4
  %4 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %5 = icmp sle i64 0, %4
  br i1 %5, label %6, label %8

; <label>:6:                                      ; preds = %0
  %7 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  store i64 %7, i64* %1, align 8
  br label %31

; <label>:8:                                      ; preds = %0
  store i64 0, i64* %2, align 8
  %9 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 1), align 4
  %10 = sub i32 %9, 1
  store i32 %10, i32* %3, align 4
  br label %11

; <label>:11:                                     ; preds = %25, %8
  %12 = load i32, i32* %3, align 4
  %13 = icmp sle i32 0, %12
  br i1 %13, label %14, label %28

; <label>:14:                                     ; preds = %11
  %15 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %16 = load i32, i32* %3, align 4
  %17 = sext i32 %16 to i64
  %18 = getelementptr inbounds i32, i32* %15, i64 %17
  %19 = load i32, i32* %18, align 4
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %21, label %24

; <label>:21:                                     ; preds = %14
  %22 = load i64, i64* %2, align 8
  %23 = add i64 %22, 1
  store i64 %23, i64* %2, align 8
  br label %24

; <label>:24:                                     ; preds = %21, %14
  br label %25

; <label>:25:                                     ; preds = %24
  %26 = load i32, i32* %3, align 4
  %27 = add nsw i32 %26, -1
  store i32 %27, i32* %3, align 4
  br label %11

; <label>:28:                                     ; preds = %11
  %29 = load i64, i64* %2, align 8
  store i64 %29, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %30 = load i64, i64* %2, align 8
  store i64 %30, i64* %1, align 8
  br label %31

; <label>:31:                                     ; preds = %28, %6
  %32 = load i64, i64* %1, align 8
  ret i64 %32
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { argmemonly nounwind }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { allocsize(0) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { allocsize(0) }
attributes #6 = { nounwind }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
