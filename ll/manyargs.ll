%struct.pcache_t = type { [1024 x %struct.pathc_t], %struct.superblock_t, i32*, i64, %struct.dir_t, i32, %struct._opaque_pthread_mutex_t }
%struct.pathc_t = type { i8, [1025 x i8], %struct.dir_t, %struct.fdc_t*, i64, i64, %struct._opaque_pthread_mutex_t* }
%struct.fdc_t = type { i8, i64, %struct.pathc_t* }
%struct.superblock_t = type { i32, i32, i32, i32, i32 }
%struct.dir_t = type { %union.fname_u, %struct.times_t, i32, i32, i32, i32 }
%union.fname_u = type { [6 x i32] }
%struct.times_t = type { i64, i64, i64 }
%struct._opaque_pthread_mutex_t = type { i64, [56 x i8] }

@pcache = external global %struct.pcache_t, align 8

define i32 @hello(i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32, i32) {
	; Implicit entry block: %20
	%44 = alloca i64, align 8
	%21 = and i32 %0,  %1
	%22 = and i32 %2,  %3
	%23 = and i32 %4,  %5
	%24 = and i32 %6,  %7
	%25 = and i32 %8,  %9
	%26 = and i32 %10, %11
	%27 = and i32 %12, %13
	%28 = and i32 %14, %15
	%29 = and i32 %16, %17
	%30 = and i32 %18, %19
	br label %31

; <label>:31:                                     ; preds = %20
	%32 = and i32 %21, %22
	%33 = and i32 %23, %24
	%34 = and i32 %25, %26
	%35 = and i32 %27, %28
	%36 = and i32 %29, %30
	br label %42

; <label>:42:                                     ; preds = %31
	%43 = call i32 @hello(i32 %21, i32 %22, i32 %23, i32 %24, i32 %25, i32 %26, i32 %27, i32 %28, i32 %29, i32 %30,
	                      i32 1, %struct.superblock_t* byval align 8 getelementptr inbounds (%struct.pcache_t,
	                      %struct.pcache_t* @pcache, i32 0, i32 1), i1 true, i1 false, i32 -1, i32 %32, i32 %33,
	                      i32 %34, i32 %35, i32 %36)
	br label %37

; <label>:37:                                     ; preds = %42
	%38 = and i32 %32, %33
	%39 = and i32 %38, %34
	%40 = and i32 %39, %35
	%41 = and i32 %40, %36
	ret i32 %41
}
