; ModuleID = 'util.c'
source_filename = "util.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.__sFILEX = type opaque
%struct.__sbuf = type { i8*, i32 }
%struct.timespec = type { i64, i64 }
%struct.times_t = type { i64, i64, i64 }

@logfile = global %struct.__sFILE* null, align 8
@safe_exit = global i32 0, align 4
@safe_exit_code = global i32 0, align 4
@safe_exit_crash = global i32 0, align 4
@debug_enable = global i32 1, align 4
@debug_disable_method = global i32 0, align 4
@debug_disable_external = global i32 0, align 4
@nothing = constant [4096 x i8] zeroinitializer, align 16
@total_written = global i32 0, align 4
@.str = private unnamed_addr constant [3 x i8] c"%d\00", align 1
@.str.1 = private unnamed_addr constant [18 x i8] c"./tests/readblock\00", align 1
@.str.2 = private unnamed_addr constant [7 x i8] c"fs.dat\00", align 1
@.str.3 = private unnamed_addr constant [82 x i8] c"\0A\1B[33mPausing execution.\1B[39m Use ^Z to return to the terminal and fg to resume.\0A\00", align 1
@.str.4 = private unnamed_addr constant [70 x i8] c"\1B[2m\E2\94\82\1B[22m%8s     \1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m%11s\1B[0m \1B[2m\E2\94\82\1B[22m\0A\00", align 1
@.str.5 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.6 = private unnamed_addr constant [162 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s \1B[33mPausing execution.\1B[39m Check the terminal for instructions.\0A\00", align 1
@.str.7 = private unnamed_addr constant [7 x i8] c"util.c\00", align 1
@.str.8 = private unnamed_addr constant [99 x i8] c"\1B[2m~\1B[22m\1B[31ms\1B[38;5;208mo\1B[33mm\1B[38;5;112me\1B[32mw\1B[36mh\1B[34me\1B[38;5;128mr\1B[38;5;219me\1B[2m~\1B[22m\00", align 1
@indentation = common global [81 x i8] zeroinitializer, align 16
@indent.indent_level = internal global i32 -1, align 4
@quit_cleanup = common global void ()* null, align 8
@.str.9 = private unnamed_addr constant [119 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m\1B[31m%8s\1B[0m \1B[2m\1B[31m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[31m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[31m%s\1B[0m\0A\00", align 1
@.str.10 = private unnamed_addr constant [7 x i8] c"atexit\00", align 1
@.str.11 = private unnamed_addr constant [37 x i8] c"Segfault detected\E2\80\94not cleaning up.\00", align 1
@.str.12 = private unnamed_addr constant [46 x i8] c"Improper shutdown detected\E2\80\94not cleaning up.\00", align 1
@.str.13 = private unnamed_addr constant [34 x i8] c"Crash detected\E2\80\94not cleaning up.\00", align 1
@.str.14 = private unnamed_addr constant [111 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33m%s\1B[0m\0A\00", align 1
@.str.15 = private unnamed_addr constant [5 x i8] c"quit\00", align 1
@.str.16 = private unnamed_addr constant [10 x i8] c"Goodbye.\0A\00", align 1
@BigSegfault = internal constant [1324 x i8] c"  \E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88 \E2\96\93\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88   \E2\96\84\E2\96\88\E2\96\88\E2\96\88\E2\96\88   \E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\92\E2\96\84\E2\96\84\E2\96\84       \E2\96\88    \E2\96\88\E2\96\88  \E2\96\88\E2\96\88\E2\96\93  \E2\96\84\E2\96\84\E2\96\84\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\93\0A\E2\96\92\E2\96\88\E2\96\88    \E2\96\92 \E2\96\93\E2\96\88   \E2\96\80  \E2\96\88\E2\96\88\E2\96\92 \E2\96\80\E2\96\88\E2\96\92\E2\96\93\E2\96\88\E2\96\88   \E2\96\92\E2\96\92\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\84     \E2\96\88\E2\96\88  \E2\96\93\E2\96\88\E2\96\88\E2\96\92\E2\96\93\E2\96\88\E2\96\88\E2\96\92  \E2\96\93  \E2\96\88\E2\96\88\E2\96\92 \E2\96\93\E2\96\92\0A\E2\96\91 \E2\96\93\E2\96\88\E2\96\88\E2\96\84   \E2\96\92\E2\96\88\E2\96\88\E2\96\88   \E2\96\92\E2\96\88\E2\96\88\E2\96\91\E2\96\84\E2\96\84\E2\96\84\E2\96\91\E2\96\92\E2\96\88\E2\96\88\E2\96\88\E2\96\88 \E2\96\91\E2\96\92\E2\96\88\E2\96\88  \E2\96\80\E2\96\88\E2\96\84  \E2\96\93\E2\96\88\E2\96\88  \E2\96\92\E2\96\88\E2\96\88\E2\96\91\E2\96\92\E2\96\88\E2\96\88\E2\96\91  \E2\96\92 \E2\96\93\E2\96\88\E2\96\88\E2\96\91 \E2\96\92\E2\96\91\0A  \E2\96\92   \E2\96\88\E2\96\88\E2\96\92\E2\96\92\E2\96\93\E2\96\88  \E2\96\84 \E2\96\91\E2\96\93\E2\96\88  \E2\96\88\E2\96\88\E2\96\93\E2\96\91\E2\96\93\E2\96\88\E2\96\92  \E2\96\91\E2\96\91\E2\96\88\E2\96\88\E2\96\84\E2\96\84\E2\96\84\E2\96\84\E2\96\88\E2\96\88 \E2\96\93\E2\96\93\E2\96\88  \E2\96\91\E2\96\88\E2\96\88\E2\96\91\E2\96\92\E2\96\88\E2\96\88\E2\96\91  \E2\96\91 \E2\96\93\E2\96\88\E2\96\88\E2\96\93 \E2\96\91 \0A\E2\96\92\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\92\E2\96\92\E2\96\91\E2\96\92\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\92\E2\96\91\E2\96\92\E2\96\93\E2\96\88\E2\96\88\E2\96\88\E2\96\80\E2\96\92\E2\96\91\E2\96\92\E2\96\88\E2\96\91    \E2\96\93\E2\96\88   \E2\96\93\E2\96\88\E2\96\88\E2\96\92\E2\96\92\E2\96\92\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\93 \E2\96\91\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\88\E2\96\92\E2\96\92\E2\96\88\E2\96\88\E2\96\92 \E2\96\91 \0A\E2\96\92 \E2\96\92\E2\96\93\E2\96\92 \E2\96\92 \E2\96\91\E2\96\91\E2\96\91 \E2\96\92\E2\96\91 \E2\96\91 \E2\96\91\E2\96\92   \E2\96\92  \E2\96\92 \E2\96\91    \E2\96\92\E2\96\92   \E2\96\93\E2\96\92\E2\96\88\E2\96\91\E2\96\91\E2\96\92\E2\96\93\E2\96\92 \E2\96\92 \E2\96\92 \E2\96\91 \E2\96\92\E2\96\91\E2\96\93  \E2\96\91\E2\96\92 \E2\96\91\E2\96\91   \0A\E2\96\91 \E2\96\91\E2\96\92  \E2\96\91 \E2\96\91 \E2\96\91 \E2\96\91  \E2\96\91  \E2\96\91   \E2\96\91  \E2\96\91       \E2\96\92   \E2\96\92\E2\96\92 \E2\96\91\E2\96\91\E2\96\91\E2\96\92\E2\96\91 \E2\96\91 \E2\96\91 \E2\96\91 \E2\96\91 \E2\96\92  \E2\96\91  \E2\96\91    \0A\E2\96\91  \E2\96\91  \E2\96\91     \E2\96\91   \E2\96\91 \E2\96\91   \E2\96\91  \E2\96\91 \E2\96\91     \E2\96\91   \E2\96\92    \E2\96\91\E2\96\91\E2\96\91 \E2\96\91 \E2\96\91   \E2\96\91 \E2\96\91   \E2\96\91      \0A      \E2\96\91     \E2\96\91  \E2\96\91      \E2\96\91              \E2\96\91  \E2\96\91   \E2\96\91         \E2\96\91  \E2\96\91       \1B[0m\1B[B\0A\1B[14C\1B[sWatch out for those tricky segfaults.\0A\1B[u\1B[B\1B[8C\1B[34;4mhttps://xkcd.com/371/\1B[0m\00", align 16
@BigSkull = internal constant [911 x i8] c"\1B[38;5;88;1m    ..............\0A\1B[38;5;196;1m   ::::::::::::::::::\0A\1B[38;5;202;1m  :::::::::::::::\0A\1B[38;5;208;1m :::`::::::: :::     :    \1B[0m\1B[1m\1B[3mYIKES!\1B[0m That's a crash!\1B[0m\1B[38;5;208;1m\0A\1B[38;5;142;1m :::: ::::: :::::    :    \1B[0mLooks like you're having some trouble writing code.\1B[0m\1B[38;5;142;1m\0A\1B[38;5;40;1m :`   :::::;     :..~~    \1B[0mTry again and do it right this time. \1B[2m:~)\1B[0m\1B[38;5;40;1m\0A\1B[38;5;44;1m :   ::  :::.     :::.\0A\1B[38;5;39;1m :...`:, :::::...:::\0A\1B[38;5;27;1m::::::.  :::::::::'      \1B[0mWatch out for memleaks too. \1B[2m;P\1B[0m\1B[38;5;27;1m\0A\1B[38;5;92;1m ::::::::|::::::::  !\0A\1B[38;5;88;1m :;;;;;;;;;;;;;;;;']}\0A\1B[38;5;196;1m ;--.--.--.--.--.-\0A\1B[38;5;202;1m  \5C/ \5C/ \5C/ \5C/ \5C/ \5C/\0A\1B[38;5;208;1m     :::       ::::\0A\1B[38;5;142;1m      :::      ::\0A\1B[38;5;40;1m     :\5C:      ::\0A\1B[38;5;44;1m   /\5C::    /\5C:::    \0A\1B[38;5;39;1m ^.:^:.^^^::`::\0A\1B[38;5;27;1m ::::::::.::::\0A\1B[38;5;92;1m  .::::::::::\1B[0m\00", align 16
@.str.17 = private unnamed_addr constant [7 x i8] c"\0A%s%s\0A\00", align 1
@.str.18 = private unnamed_addr constant [11 x i8] c"\1B[38;5;88m\00", align 1
@.str.19 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.20 = private unnamed_addr constant [110 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[31m%8s\1B[0m \1B[31m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[31m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s%s: %s\1B[0m\0A\00", align 1
@.str.21 = private unnamed_addr constant [5 x i8] c"mkfs\00", align 1
@.str.22 = private unnamed_addr constant [23 x i8] c"Couldn't write to file\00", align 1
@.str.23 = private unnamed_addr constant [103 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s %s\1B[0m\0A\00", align 1
@.str.24 = private unnamed_addr constant [135 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s %s \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m\1B[0m\0A\00", align 1
@.str.25 = private unnamed_addr constant [116 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s %s \1B[1m%ld\1B[22m\1B[0m\0A\00", align 1
@.str.26 = private unnamed_addr constant [118 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s %s \1B[1m0x%lx\1B[22m\1B[0m\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @run_readblock(i32) #0 {
  %2 = alloca i32, align 4
  %3 = alloca [64 x i8], align 16
  store i32 %0, i32* %2, align 4
  %4 = call i32 @fork()
  %5 = icmp eq i32 %4, 0
  br i1 %5, label %6, label %12

; <label>:6:                                      ; preds = %1
  %7 = getelementptr inbounds [64 x i8], [64 x i8]* %3, i32 0, i32 0
  %8 = load i32, i32* %2, align 4
  %9 = call i32 (i8*, i64, i32, i64, i8*, ...) @__snprintf_chk(i8* %7, i64 64, i32 0, i64 64, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str, i32 0, i32 0), i32 %8)
  %10 = getelementptr inbounds [64 x i8], [64 x i8]* %3, i32 0, i32 0
  %11 = call i32 (i8*, i8*, ...) @execl(i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.1, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.2, i32 0, i32 0), i8* %10, i8* null)
  br label %12

; <label>:12:                                     ; preds = %6, %1
  ret void
}

declare i32 @fork() #1

declare i32 @__snprintf_chk(i8*, i64, i32, i64, i8*, ...) #1

declare i32 @execl(i8*, i8*, ...) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @sigstop() #0 {
  %1 = call i32 (i8*, ...) @printf(i8* getelementptr inbounds ([82 x i8], [82 x i8]* @.str.3, i32 0, i32 0))
  %2 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %3 = icmp ne %struct.__sFILE* %2, null
  br i1 %3, label %4, label %11

; <label>:4:                                      ; preds = %0
  %5 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %6 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %5, i8* getelementptr inbounds ([70 x i8], [70 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.5, i32 0, i32 0))
  %7 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %8 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %7, i8* getelementptr inbounds ([162 x i8], [162 x i8]* @.str.6, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i32 45, i8* getelementptr inbounds ([99 x i8], [99 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0))
  %9 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %10 = call i32 @fflush(%struct.__sFILE* %9)
  br label %11

; <label>:11:                                     ; preds = %4, %0
  %12 = call i32 @raise(i32 17)
  ret void
}

declare i32 @printf(i8*, ...) #1

declare i32 @fprintf(%struct.__sFILE*, i8*, ...) #1

declare i32 @fflush(%struct.__sFILE*) #1

declare i32 @raise(i32) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @indent(i32) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %4 = load i32, i32* @indent.indent_level, align 4
  %5 = icmp eq i32 %4, -1
  br i1 %5, label %6, label %7

; <label>:6:                                      ; preds = %1
  call void @llvm.memset.p0i8.i64(i8* align 16 getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8 32, i64 80, i1 false)
  store i8 0, i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i64 0, i64 80), align 16
  store i32 0, i32* @indent.indent_level, align 4
  br label %7

; <label>:7:                                      ; preds = %6, %1
  %8 = load i32, i32* @indent.indent_level, align 4
  store i32 %8, i32* %3, align 4
  %9 = load i32, i32* %2, align 4
  %10 = mul nsw i32 %9, 2
  %11 = load i32, i32* @indent.indent_level, align 4
  %12 = add nsw i32 %11, %10
  store i32 %12, i32* @indent.indent_level, align 4
  %13 = load i32, i32* @indent.indent_level, align 4
  %14 = icmp slt i32 %13, 0
  br i1 %14, label %15, label %16

; <label>:15:                                     ; preds = %7
  store i32 0, i32* @indent.indent_level, align 4
  br label %21

; <label>:16:                                     ; preds = %7
  %17 = load i32, i32* @indent.indent_level, align 4
  %18 = icmp slt i32 80, %17
  br i1 %18, label %19, label %20

; <label>:19:                                     ; preds = %16
  store i32 80, i32* @indent.indent_level, align 4
  br label %20

; <label>:20:                                     ; preds = %19, %16
  br label %21

; <label>:21:                                     ; preds = %20, %15
  %22 = load i32, i32* %3, align 4
  %23 = icmp slt i32 -1, %22
  br i1 %23, label %24, label %28

; <label>:24:                                     ; preds = %21
  %25 = load i32, i32* %3, align 4
  %26 = sext i32 %25 to i64
  %27 = getelementptr inbounds [81 x i8], [81 x i8]* @indentation, i64 0, i64 %26
  store i8 32, i8* %27, align 1
  br label %28

; <label>:28:                                     ; preds = %24, %21
  %29 = load i32, i32* @indent.indent_level, align 4
  %30 = sext i32 %29 to i64
  %31 = getelementptr inbounds [81 x i8], [81 x i8]* @indentation, i64 0, i64 %30
  store i8 0, i8* %31, align 1
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @set_cleanup(void ()*) #0 {
  %2 = alloca void ()*, align 8
  store void ()* %0, void ()** %2, align 8
  %3 = load void ()*, void ()** %2, align 8
  store void ()* %3, void ()** @quit_cleanup, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @atexit_handler() #0 {
  %1 = load i32, i32* @safe_exit_crash, align 4
  %2 = icmp eq i32 %1, 2
  br i1 %2, label %3, label %21

; <label>:3:                                      ; preds = %0
  %4 = load i32, i32* @debug_enable, align 4
  %5 = icmp eq i32 %4, 1
  br i1 %5, label %6, label %20

; <label>:6:                                      ; preds = %3
  %7 = load i32, i32* @debug_disable_method, align 4
  %8 = icmp eq i32 %7, 0
  br i1 %8, label %9, label %20

; <label>:9:                                      ; preds = %6
  %10 = load i32, i32* @debug_disable_external, align 4
  %11 = icmp ne i32 %10, 1
  br i1 %11, label %12, label %20

; <label>:12:                                     ; preds = %9
  %13 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %14 = icmp ne %struct.__sFILE* %13, null
  br i1 %14, label %15, label %20

; <label>:15:                                     ; preds = %12
  %16 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %17 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %16, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i32 83, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.11, i32 0, i32 0))
  %18 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %19 = call i32 @fflush(%struct.__sFILE* %18)
  br label %20

; <label>:20:                                     ; preds = %15, %12, %9, %6, %3
  br label %65

; <label>:21:                                     ; preds = %0
  %22 = load i32, i32* @safe_exit, align 4
  %23 = icmp ne i32 %22, 0
  br i1 %23, label %42, label %24

; <label>:24:                                     ; preds = %21
  %25 = load i32, i32* @debug_enable, align 4
  %26 = icmp eq i32 %25, 1
  br i1 %26, label %27, label %41

; <label>:27:                                     ; preds = %24
  %28 = load i32, i32* @debug_disable_method, align 4
  %29 = icmp eq i32 %28, 0
  br i1 %29, label %30, label %41

; <label>:30:                                     ; preds = %27
  %31 = load i32, i32* @debug_disable_external, align 4
  %32 = icmp ne i32 %31, 1
  br i1 %32, label %33, label %41

; <label>:33:                                     ; preds = %30
  %34 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %35 = icmp ne %struct.__sFILE* %34, null
  br i1 %35, label %36, label %41

; <label>:36:                                     ; preds = %33
  %37 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %38 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %37, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i32 85, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([46 x i8], [46 x i8]* @.str.12, i32 0, i32 0))
  %39 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %40 = call i32 @fflush(%struct.__sFILE* %39)
  br label %41

; <label>:41:                                     ; preds = %36, %33, %30, %27, %24
  br label %64

; <label>:42:                                     ; preds = %21
  %43 = load i32, i32* @safe_exit_crash, align 4
  %44 = icmp ne i32 %43, 0
  br i1 %44, label %45, label %63

; <label>:45:                                     ; preds = %42
  %46 = load i32, i32* @debug_enable, align 4
  %47 = icmp eq i32 %46, 1
  br i1 %47, label %48, label %62

; <label>:48:                                     ; preds = %45
  %49 = load i32, i32* @debug_disable_method, align 4
  %50 = icmp eq i32 %49, 0
  br i1 %50, label %51, label %62

; <label>:51:                                     ; preds = %48
  %52 = load i32, i32* @debug_disable_external, align 4
  %53 = icmp ne i32 %52, 1
  br i1 %53, label %54, label %62

; <label>:54:                                     ; preds = %51
  %55 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %56 = icmp ne %struct.__sFILE* %55, null
  br i1 %56, label %57, label %62

; <label>:57:                                     ; preds = %54
  %58 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %59 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %58, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.9, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i32 87, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.10, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([34 x i8], [34 x i8]* @.str.13, i32 0, i32 0))
  %60 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %61 = call i32 @fflush(%struct.__sFILE* %60)
  br label %62

; <label>:62:                                     ; preds = %57, %54, %51, %48, %45
  br label %63

; <label>:63:                                     ; preds = %62, %42
  br label %64

; <label>:64:                                     ; preds = %63, %41
  br label %65

; <label>:65:                                     ; preds = %64, %20
  %66 = load i32, i32* @safe_exit, align 4
  %67 = icmp ne i32 %66, 0
  br i1 %67, label %68, label %71

; <label>:68:                                     ; preds = %65
  %69 = load i32, i32* @safe_exit_crash, align 4
  %70 = icmp ne i32 %69, 0
  br i1 %70, label %71, label %75

; <label>:71:                                     ; preds = %68, %65
  %72 = load i32, i32* @safe_exit_crash, align 4
  %73 = icmp eq i32 %72, 2
  %74 = zext i1 %73 to i32
  call void @printspook(i32 %74)
  br label %75

; <label>:75:                                     ; preds = %71, %68
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @printspook(i32) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i8*, align 8
  store i32 %0, i32* %2, align 4
  %4 = load i32, i32* %2, align 4
  %5 = load i32, i32* %2, align 4
  %6 = icmp ne i32 %5, 0
  %7 = zext i1 %6 to i64
  %8 = select i1 %6, i8* getelementptr inbounds ([1324 x i8], [1324 x i8]* @BigSegfault, i32 0, i32 0), i8* getelementptr inbounds ([911 x i8], [911 x i8]* @BigSkull, i32 0, i32 0)
  %9 = call i8* @indent_str(i8* %8, i32 12)
  store i8* %9, i8** %3, align 8
  %10 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %11 = icmp ne %struct.__sFILE* %10, null
  br i1 %11, label %12, label %20

; <label>:12:                                     ; preds = %1
  %13 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %14 = load i32, i32* %2, align 4
  %15 = icmp ne i32 %14, 0
  %16 = zext i1 %15 to i64
  %17 = select i1 %15, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.18, i32 0, i32 0), i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.5, i32 0, i32 0)
  %18 = load i8*, i8** %3, align 8
  %19 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %13, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.17, i32 0, i32 0), i8* %17, i8* %18)
  br label %20

; <label>:20:                                     ; preds = %12, %1
  %21 = load i8*, i8** %3, align 8
  call void @free(i8* %21)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @quit(i32, i32) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  store i32 1, i32* @safe_exit, align 4
  %5 = load i32, i32* %3, align 4
  store i32 %5, i32* @safe_exit_code, align 4
  %6 = load i32, i32* %4, align 4
  store i32 %6, i32* @safe_exit_crash, align 4
  %7 = load i32, i32* %4, align 4
  %8 = icmp ne i32 %7, 0
  br i1 %8, label %35, label %9

; <label>:9:                                      ; preds = %2
  %10 = load void ()*, void ()** @quit_cleanup, align 8
  %11 = icmp ne void ()* %10, null
  br i1 %11, label %12, label %17

; <label>:12:                                     ; preds = %9
  %13 = load void ()*, void ()** @quit_cleanup, align 8
  %14 = ptrtoint void ()* %13 to i64
  %15 = and i64 %14, 281474976710655
  %16 = inttoptr i64 %15 to void ()*
  call void %16()
  br label %17

; <label>:17:                                     ; preds = %12, %9
  %18 = load i32, i32* @debug_enable, align 4
  %19 = icmp eq i32 %18, 1
  br i1 %19, label %20, label %34

; <label>:20:                                     ; preds = %17
  %21 = load i32, i32* @debug_disable_method, align 4
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %23, label %34

; <label>:23:                                     ; preds = %20
  %24 = load i32, i32* @debug_disable_external, align 4
  %25 = icmp ne i32 %24, 1
  br i1 %25, label %26, label %34

; <label>:26:                                     ; preds = %23
  %27 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %28 = icmp ne %struct.__sFILE* %27, null
  br i1 %28, label %29, label %34

; <label>:29:                                     ; preds = %26
  %30 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %31 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %30, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i32 111, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.15, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.16, i32 0, i32 0))
  %32 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %33 = call i32 @fflush(%struct.__sFILE* %32)
  br label %34

; <label>:34:                                     ; preds = %29, %26, %23, %20, %17
  br label %35

; <label>:35:                                     ; preds = %34, %2
  %36 = load i32, i32* %3, align 4
  call void @exit(i32 %36) #7
  unreachable
                                                  ; No predecessors!
  ret void
}

; Function Attrs: noreturn
declare void @exit(i32) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @indent_str(i8*, i32) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i8, align 1
  %11 = alloca i32, align 4
  %12 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  store i32 %1, i32* %4, align 4
  %13 = load i8*, i8** %3, align 8
  %14 = call i64 @strlen(i8* %13)
  %15 = trunc i64 %14 to i32
  store i32 %15, i32* %5, align 4
  store i32 0, i32* %7, align 4
  store i32 1, i32* %9, align 4
  store i32 0, i32* %6, align 4
  br label %16

; <label>:16:                                     ; preds = %32, %2
  %17 = load i32, i32* %6, align 4
  %18 = load i32, i32* %5, align 4
  %19 = icmp slt i32 %17, %18
  br i1 %19, label %20, label %35

; <label>:20:                                     ; preds = %16
  %21 = load i8*, i8** %3, align 8
  %22 = load i32, i32* %6, align 4
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds i8, i8* %21, i64 %23
  %25 = load i8, i8* %24, align 1
  %26 = sext i8 %25 to i32
  %27 = icmp eq i32 %26, 10
  br i1 %27, label %28, label %31

; <label>:28:                                     ; preds = %20
  %29 = load i32, i32* %9, align 4
  %30 = add nsw i32 %29, 1
  store i32 %30, i32* %9, align 4
  br label %31

; <label>:31:                                     ; preds = %28, %20
  br label %32

; <label>:32:                                     ; preds = %31
  %33 = load i32, i32* %6, align 4
  %34 = add nsw i32 %33, 1
  store i32 %34, i32* %6, align 4
  br label %16

; <label>:35:                                     ; preds = %16
  %36 = load i32, i32* %5, align 4
  %37 = load i32, i32* %4, align 4
  %38 = load i32, i32* %9, align 4
  %39 = mul nsw i32 %37, %38
  %40 = add nsw i32 %36, %39
  store i32 %40, i32* %11, align 4
  %41 = load i32, i32* %11, align 4
  %42 = add nsw i32 %41, 1
  %43 = sext i32 %42 to i64
  %44 = call i8* @calloc(i64 %43, i64 1) #8
  store i8* %44, i8** %12, align 8
  store i32 0, i32* %6, align 4
  br label %45

; <label>:45:                                     ; preds = %55, %35
  %46 = load i32, i32* %6, align 4
  %47 = load i32, i32* %4, align 4
  %48 = icmp slt i32 %46, %47
  br i1 %48, label %49, label %58

; <label>:49:                                     ; preds = %45
  %50 = load i8*, i8** %12, align 8
  %51 = load i32, i32* %7, align 4
  %52 = add nsw i32 %51, 1
  store i32 %52, i32* %7, align 4
  %53 = sext i32 %51 to i64
  %54 = getelementptr inbounds i8, i8* %50, i64 %53
  store i8 32, i8* %54, align 1
  br label %55

; <label>:55:                                     ; preds = %49
  %56 = load i32, i32* %6, align 4
  %57 = add nsw i32 %56, 1
  store i32 %57, i32* %6, align 4
  br label %45

; <label>:58:                                     ; preds = %45
  store i32 0, i32* %6, align 4
  br label %59

; <label>:59:                                     ; preds = %94, %58
  %60 = load i32, i32* %6, align 4
  %61 = load i32, i32* %5, align 4
  %62 = icmp slt i32 %60, %61
  br i1 %62, label %63, label %97

; <label>:63:                                     ; preds = %59
  %64 = load i8*, i8** %3, align 8
  %65 = load i32, i32* %6, align 4
  %66 = sext i32 %65 to i64
  %67 = getelementptr inbounds i8, i8* %64, i64 %66
  %68 = load i8, i8* %67, align 1
  store i8 %68, i8* %10, align 1
  %69 = load i8, i8* %10, align 1
  %70 = load i8*, i8** %12, align 8
  %71 = load i32, i32* %7, align 4
  %72 = add nsw i32 %71, 1
  store i32 %72, i32* %7, align 4
  %73 = sext i32 %71 to i64
  %74 = getelementptr inbounds i8, i8* %70, i64 %73
  store i8 %69, i8* %74, align 1
  %75 = load i8, i8* %10, align 1
  %76 = sext i8 %75 to i32
  %77 = icmp eq i32 %76, 10
  br i1 %77, label %78, label %93

; <label>:78:                                     ; preds = %63
  store i32 0, i32* %8, align 4
  br label %79

; <label>:79:                                     ; preds = %89, %78
  %80 = load i32, i32* %8, align 4
  %81 = load i32, i32* %4, align 4
  %82 = icmp slt i32 %80, %81
  br i1 %82, label %83, label %92

; <label>:83:                                     ; preds = %79
  %84 = load i8*, i8** %12, align 8
  %85 = load i32, i32* %7, align 4
  %86 = add nsw i32 %85, 1
  store i32 %86, i32* %7, align 4
  %87 = sext i32 %85 to i64
  %88 = getelementptr inbounds i8, i8* %84, i64 %87
  store i8 32, i8* %88, align 1
  br label %89

; <label>:89:                                     ; preds = %83
  %90 = load i32, i32* %8, align 4
  %91 = add nsw i32 %90, 1
  store i32 %91, i32* %8, align 4
  br label %79

; <label>:92:                                     ; preds = %79
  br label %93

; <label>:93:                                     ; preds = %92, %63
  br label %94

; <label>:94:                                     ; preds = %93
  %95 = load i32, i32* %6, align 4
  %96 = add nsw i32 %95, 1
  store i32 %96, i32* %6, align 4
  br label %59

; <label>:97:                                     ; preds = %59
  %98 = load i8*, i8** %12, align 8
  ret i8* %98
}

declare void @free(i8*) #1

declare i64 @strlen(i8*) #1

; Function Attrs: allocsize(0,1)
declare i8* @calloc(i64, i64) #4

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @ntime() #0 {
  %1 = alloca %struct.timespec, align 8
  %2 = call i32 @clock_gettime(i32 0, %struct.timespec* %1)
  %3 = getelementptr inbounds %struct.timespec, %struct.timespec* %1, i32 0, i32 0
  %4 = load i64, i64* %3, align 8
  %5 = sitofp i64 %4 to double
  %6 = fmul double %5, 1.000000e+09
  %7 = getelementptr inbounds %struct.timespec, %struct.timespec* %1, i32 0, i32 1
  %8 = load i64, i64* %7, align 8
  %9 = sitofp i64 %8 to double
  %10 = fadd double %6, %9
  %11 = fptosi double %10 to i64
  ret i64 %11
}

declare i32 @clock_gettime(i32, %struct.timespec*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @gettimes(%struct.times_t* noalias sret) #0 {
  %2 = alloca i64, align 8
  %3 = call i64 @time(i64* null)
  store i64 %3, i64* %2, align 8
  %4 = getelementptr inbounds %struct.times_t, %struct.times_t* %0, i32 0, i32 0
  %5 = load i64, i64* %2, align 8
  store i64 %5, i64* %4, align 8
  %6 = getelementptr inbounds %struct.times_t, %struct.times_t* %0, i32 0, i32 1
  %7 = load i64, i64* %2, align 8
  store i64 %7, i64* %6, align 8
  %8 = getelementptr inbounds %struct.times_t, %struct.times_t* %0, i32 0, i32 2
  %9 = load i64, i64* %2, align 8
  store i64 %9, i64* %8, align 8
  ret void
}

declare i64 @time(i64*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @path_first(i8*, i8**) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca i8**, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  %8 = alloca i8*, align 8
  store i8* %0, i8** %4, align 8
  store i8** %1, i8*** %5, align 8
  %9 = load i8*, i8** %4, align 8
  %10 = icmp eq i8* %9, null
  br i1 %10, label %11, label %13

; <label>:11:                                     ; preds = %2
  %12 = load i8**, i8*** %5, align 8
  store i8* null, i8** %12, align 8
  store i8* null, i8** %3, align 8
  br label %72

; <label>:13:                                     ; preds = %2
  %14 = load i8*, i8** %4, align 8
  %15 = getelementptr inbounds i8, i8* %14, i64 0
  %16 = load i8, i8* %15, align 1
  %17 = sext i8 %16 to i32
  %18 = icmp eq i32 %17, 47
  br i1 %18, label %19, label %22

; <label>:19:                                     ; preds = %13
  %20 = load i8*, i8** %4, align 8
  %21 = getelementptr inbounds i8, i8* %20, i32 1
  store i8* %21, i8** %4, align 8
  br label %22

; <label>:22:                                     ; preds = %19, %13
  %23 = load i8*, i8** %4, align 8
  %24 = call i64 @strlen(i8* %23)
  store i64 %24, i64* %7, align 8
  store i64 0, i64* %6, align 8
  br label %25

; <label>:25:                                     ; preds = %39, %22
  %26 = load i64, i64* %6, align 8
  %27 = load i64, i64* %7, align 8
  %28 = icmp ult i64 %26, %27
  br i1 %28, label %29, label %36

; <label>:29:                                     ; preds = %25
  %30 = load i8*, i8** %4, align 8
  %31 = load i64, i64* %6, align 8
  %32 = getelementptr inbounds i8, i8* %30, i64 %31
  %33 = load i8, i8* %32, align 1
  %34 = sext i8 %33 to i32
  %35 = icmp ne i32 %34, 47
  br label %36

; <label>:36:                                     ; preds = %29, %25
  %37 = phi i1 [ false, %25 ], [ %35, %29 ]
  br i1 %37, label %38, label %42

; <label>:38:                                     ; preds = %36
  br label %39

; <label>:39:                                     ; preds = %38
  %40 = load i64, i64* %6, align 8
  %41 = add i64 %40, 1
  store i64 %41, i64* %6, align 8
  br label %25

; <label>:42:                                     ; preds = %36
  %43 = load i64, i64* %6, align 8
  %44 = add i64 %43, 1
  %45 = call i8* @calloc(i64 %44, i64 1) #8
  store i8* %45, i8** %8, align 8
  %46 = load i8*, i8** %8, align 8
  %47 = load i8*, i8** %4, align 8
  %48 = load i64, i64* %6, align 8
  %49 = load i8*, i8** %8, align 8
  %50 = call i64 @llvm.objectsize.i64.p0i8(i8* %49, i1 false, i1 true)
  %51 = call i8* @__memcpy_chk(i8* %46, i8* %47, i64 %48, i64 %50) #9
  %52 = load i64, i64* %6, align 8
  %53 = load i8*, i8** %4, align 8
  %54 = call i64 @strlen(i8* %53)
  %55 = icmp eq i64 %52, %54
  br i1 %55, label %62, label %56

; <label>:56:                                     ; preds = %42
  %57 = load i8*, i8** %4, align 8
  %58 = load i64, i64* %6, align 8
  %59 = getelementptr inbounds i8, i8* %57, i64 %58
  %60 = call i32 @strcmp(i8* %59, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i32 0, i32 0))
  %61 = icmp eq i32 %60, 0
  br i1 %61, label %62, label %64

; <label>:62:                                     ; preds = %56, %42
  %63 = load i8**, i8*** %5, align 8
  store i8* null, i8** %63, align 8
  br label %70

; <label>:64:                                     ; preds = %56
  %65 = load i8*, i8** %4, align 8
  %66 = load i64, i64* %6, align 8
  %67 = getelementptr inbounds i8, i8* %65, i64 %66
  %68 = call i8* @strdup(i8* %67)
  %69 = load i8**, i8*** %5, align 8
  store i8* %68, i8** %69, align 8
  br label %70

; <label>:70:                                     ; preds = %64, %62
  %71 = load i8*, i8** %8, align 8
  store i8* %71, i8** %3, align 8
  br label %72

; <label>:72:                                     ; preds = %70, %11
  %73 = load i8*, i8** %3, align 8
  ret i8* %73
}

; Function Attrs: nounwind
declare i8* @__memcpy_chk(i8*, i8*, i64, i64) #5

; Function Attrs: nounwind readnone speculatable
declare i64 @llvm.objectsize.i64.p0i8(i8*, i1, i1) #6

declare i32 @strcmp(i8*, i8*) #1

declare i8* @strdup(i8*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @path_last(i8*) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i64, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i64, align 8
  %10 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  %11 = load i8*, i8** %3, align 8
  %12 = icmp eq i8* %11, null
  br i1 %12, label %13, label %14

; <label>:13:                                     ; preds = %1
  store i8* null, i8** %2, align 8
  br label %101

; <label>:14:                                     ; preds = %1
  %15 = load i8*, i8** %3, align 8
  %16 = call i64 @strlen(i8* %15)
  store i64 %16, i64* %4, align 8
  %17 = load i64, i64* %4, align 8
  %18 = icmp eq i64 %17, 0
  br i1 %18, label %19, label %21

; <label>:19:                                     ; preds = %14
  %20 = call i8* @strdup(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.5, i32 0, i32 0))
  store i8* %20, i8** %2, align 8
  br label %101

; <label>:21:                                     ; preds = %14
  store i32 -1, i32* %5, align 4
  %22 = load i8*, i8** %3, align 8
  %23 = load i64, i64* %4, align 8
  %24 = sub i64 %23, 1
  %25 = getelementptr inbounds i8, i8* %22, i64 %24
  %26 = load i8, i8* %25, align 1
  %27 = sext i8 %26 to i32
  %28 = icmp eq i32 %27, 47
  %29 = zext i1 %28 to i32
  store i32 %29, i32* %6, align 4
  %30 = load i64, i64* %4, align 8
  %31 = icmp eq i64 %30, 1
  br i1 %31, label %32, label %37

; <label>:32:                                     ; preds = %21
  %33 = load i32, i32* %6, align 4
  %34 = icmp ne i32 %33, 0
  br i1 %34, label %35, label %37

; <label>:35:                                     ; preds = %32
  %36 = call i8* @strdup(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.5, i32 0, i32 0))
  store i8* %36, i8** %2, align 8
  br label %101

; <label>:37:                                     ; preds = %32, %21
  %38 = load i64, i64* %4, align 8
  %39 = sub i64 %38, 2
  %40 = trunc i64 %39 to i32
  store i32 %40, i32* %7, align 4
  br label %41

; <label>:41:                                     ; preds = %55, %37
  %42 = load i32, i32* %7, align 4
  %43 = icmp sle i32 0, %42
  br i1 %43, label %44, label %58

; <label>:44:                                     ; preds = %41
  %45 = load i8*, i8** %3, align 8
  %46 = load i32, i32* %7, align 4
  %47 = sext i32 %46 to i64
  %48 = getelementptr inbounds i8, i8* %45, i64 %47
  %49 = load i8, i8* %48, align 1
  %50 = sext i8 %49 to i32
  %51 = icmp eq i32 %50, 47
  br i1 %51, label %52, label %54

; <label>:52:                                     ; preds = %44
  %53 = load i32, i32* %7, align 4
  store i32 %53, i32* %5, align 4
  br label %58

; <label>:54:                                     ; preds = %44
  br label %55

; <label>:55:                                     ; preds = %54
  %56 = load i32, i32* %7, align 4
  %57 = add nsw i32 %56, -1
  store i32 %57, i32* %7, align 4
  br label %41

; <label>:58:                                     ; preds = %52, %41
  %59 = load i32, i32* %5, align 4
  %60 = icmp eq i32 %59, -1
  br i1 %60, label %61, label %78

; <label>:61:                                     ; preds = %58
  %62 = load i32, i32* %6, align 4
  %63 = icmp ne i32 %62, 0
  br i1 %63, label %67, label %64

; <label>:64:                                     ; preds = %61
  %65 = load i8*, i8** %3, align 8
  %66 = call i8* @strdup(i8* %65)
  store i8* %66, i8** %2, align 8
  br label %101

; <label>:67:                                     ; preds = %61
  %68 = load i64, i64* %4, align 8
  %69 = call i8* @calloc(i64 %68, i64 1) #8
  store i8* %69, i8** %8, align 8
  %70 = load i8*, i8** %8, align 8
  %71 = load i8*, i8** %3, align 8
  %72 = load i64, i64* %4, align 8
  %73 = sub i64 %72, 1
  %74 = load i8*, i8** %8, align 8
  %75 = call i64 @llvm.objectsize.i64.p0i8(i8* %74, i1 false, i1 true)
  %76 = call i8* @__memcpy_chk(i8* %70, i8* %71, i64 %73, i64 %75) #9
  %77 = load i8*, i8** %8, align 8
  store i8* %77, i8** %2, align 8
  br label %101

; <label>:78:                                     ; preds = %58
  %79 = load i64, i64* %4, align 8
  %80 = load i32, i32* %5, align 4
  %81 = sext i32 %80 to i64
  %82 = sub i64 %79, %81
  %83 = sub i64 %82, 1
  %84 = load i32, i32* %6, align 4
  %85 = sext i32 %84 to i64
  %86 = sub i64 %83, %85
  store i64 %86, i64* %9, align 8
  %87 = load i64, i64* %9, align 8
  %88 = add i64 %87, 1
  %89 = call i8* @calloc(i64 %88, i64 1) #8
  store i8* %89, i8** %10, align 8
  %90 = load i8*, i8** %10, align 8
  %91 = load i8*, i8** %3, align 8
  %92 = load i32, i32* %5, align 4
  %93 = sext i32 %92 to i64
  %94 = getelementptr inbounds i8, i8* %91, i64 %93
  %95 = getelementptr inbounds i8, i8* %94, i64 1
  %96 = load i64, i64* %9, align 8
  %97 = load i8*, i8** %10, align 8
  %98 = call i64 @llvm.objectsize.i64.p0i8(i8* %97, i1 false, i1 true)
  %99 = call i8* @__memcpy_chk(i8* %90, i8* %95, i64 %96, i64 %98) #9
  %100 = load i8*, i8** %10, align 8
  store i8* %100, i8** %2, align 8
  br label %101

; <label>:101:                                    ; preds = %78, %67, %64, %35, %19, %13
  %102 = load i8*, i8** %2, align 8
  ret i8* %102
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i8* @path_parent(i8*) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i8*, align 8
  %4 = alloca i64, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  %8 = load i8*, i8** %3, align 8
  %9 = icmp eq i8* %8, null
  br i1 %9, label %10, label %11

; <label>:10:                                     ; preds = %1
  store i8* null, i8** %2, align 8
  br label %70

; <label>:11:                                     ; preds = %1
  %12 = load i8*, i8** %3, align 8
  %13 = call i64 @strlen(i8* %12)
  store i64 %13, i64* %4, align 8
  %14 = load i64, i64* %4, align 8
  %15 = icmp eq i64 %14, 0
  br i1 %15, label %16, label %18

; <label>:16:                                     ; preds = %11
  %17 = call i8* @strdup(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i32 0, i32 0))
  store i8* %17, i8** %2, align 8
  br label %70

; <label>:18:                                     ; preds = %11
  store i32 -1, i32* %5, align 4
  %19 = load i8*, i8** %3, align 8
  %20 = load i64, i64* %4, align 8
  %21 = sub i64 %20, 1
  %22 = getelementptr inbounds i8, i8* %19, i64 %21
  %23 = load i8, i8* %22, align 1
  %24 = sext i8 %23 to i32
  %25 = icmp eq i32 %24, 47
  %26 = zext i1 %25 to i32
  store i32 %26, i32* %6, align 4
  %27 = load i64, i64* %4, align 8
  %28 = icmp eq i64 %27, 1
  br i1 %28, label %29, label %34

; <label>:29:                                     ; preds = %18
  %30 = load i32, i32* %6, align 4
  %31 = icmp ne i32 %30, 0
  br i1 %31, label %32, label %34

; <label>:32:                                     ; preds = %29
  %33 = call i8* @strdup(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i32 0, i32 0))
  store i8* %33, i8** %2, align 8
  br label %70

; <label>:34:                                     ; preds = %29, %18
  %35 = load i64, i64* %4, align 8
  %36 = sub i64 %35, 2
  %37 = trunc i64 %36 to i32
  store i32 %37, i32* %7, align 4
  br label %38

; <label>:38:                                     ; preds = %52, %34
  %39 = load i32, i32* %7, align 4
  %40 = icmp sle i32 0, %39
  br i1 %40, label %41, label %55

; <label>:41:                                     ; preds = %38
  %42 = load i8*, i8** %3, align 8
  %43 = load i32, i32* %7, align 4
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds i8, i8* %42, i64 %44
  %46 = load i8, i8* %45, align 1
  %47 = sext i8 %46 to i32
  %48 = icmp eq i32 %47, 47
  br i1 %48, label %49, label %51

; <label>:49:                                     ; preds = %41
  %50 = load i32, i32* %7, align 4
  store i32 %50, i32* %5, align 4
  br label %55

; <label>:51:                                     ; preds = %41
  br label %52

; <label>:52:                                     ; preds = %51
  %53 = load i32, i32* %7, align 4
  %54 = add nsw i32 %53, -1
  store i32 %54, i32* %7, align 4
  br label %38

; <label>:55:                                     ; preds = %49, %38
  %56 = load i32, i32* %5, align 4
  %57 = icmp eq i32 %56, -1
  br i1 %57, label %58, label %60

; <label>:58:                                     ; preds = %55
  %59 = call i8* @strdup(i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.5, i32 0, i32 0))
  store i8* %59, i8** %2, align 8
  br label %70

; <label>:60:                                     ; preds = %55
  %61 = load i32, i32* %5, align 4
  %62 = icmp eq i32 %61, 0
  br i1 %62, label %63, label %65

; <label>:63:                                     ; preds = %60
  %64 = call i8* @strdup(i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.19, i32 0, i32 0))
  store i8* %64, i8** %2, align 8
  br label %70

; <label>:65:                                     ; preds = %60
  %66 = load i8*, i8** %3, align 8
  %67 = load i32, i32* %5, align 4
  %68 = sext i32 %67 to i64
  %69 = call i8* @strndup(i8* %66, i64 %68)
  store i8* %69, i8** %2, align 8
  br label %70

; <label>:70:                                     ; preds = %65, %63, %58, %32, %16, %10
  %71 = load i8*, i8** %2, align 8
  ret i8* %71
}

declare i8* @strndup(i8*, i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @iwrite(i32, i32, i64) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i64 %2, i64* %6, align 8
  store i64 0, i64* %7, align 8
  store i64 0, i64* %8, align 8
  br label %9

; <label>:9:                                      ; preds = %39, %3
  %10 = load i64, i64* %8, align 8
  %11 = load i64, i64* %6, align 8
  %12 = icmp ult i64 %10, %11
  br i1 %12, label %13, label %42

; <label>:13:                                     ; preds = %9
  %14 = load i32, i32* %4, align 4
  %15 = bitcast i32* %5 to i8*
  %16 = call i64 @"\01_write"(i32 %14, i8* %15, i64 4)
  %17 = call i32* @__error()
  %18 = load i32, i32* %17, align 4
  %19 = icmp ne i32 %18, 0
  br i1 %19, label %20, label %36

; <label>:20:                                     ; preds = %13
  call void @indent(i32 -1)
  %21 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %22 = call i32* @__error()
  %23 = load i32, i32* %22, align 4
  %24 = icmp slt i32 %23, 0
  br i1 %24, label %25, label %29

; <label>:25:                                     ; preds = %20
  %26 = call i32* @__error()
  %27 = load i32, i32* %26, align 4
  %28 = sub nsw i32 0, %27
  br label %32

; <label>:29:                                     ; preds = %20
  %30 = call i32* @__error()
  %31 = load i32, i32* %30, align 4
  br label %32

; <label>:32:                                     ; preds = %29, %25
  %33 = phi i32 [ %28, %25 ], [ %31, %29 ]
  %34 = call i8* @"\01_strerror"(i32 %33)
  %35 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %21, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i32 337, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.22, i32 0, i32 0), i8* %34)
  call void @quit(i32 1, i32 1)
  br label %36

; <label>:36:                                     ; preds = %32, %13
  %37 = load i64, i64* %7, align 8
  %38 = add i64 %37, 1
  store i64 %38, i64* %7, align 8
  br label %39

; <label>:39:                                     ; preds = %36
  %40 = load i64, i64* %8, align 8
  %41 = add i64 %40, 1
  store i64 %41, i64* %8, align 8
  br label %9

; <label>:42:                                     ; preds = %9
  %43 = load i64, i64* %7, align 8
  %44 = load i32, i32* @total_written, align 4
  %45 = sext i32 %44 to i64
  %46 = add i64 %45, %43
  %47 = trunc i64 %46 to i32
  store i32 %47, i32* @total_written, align 4
  %48 = load i64, i64* %7, align 8
  ret i64 %48
}

declare i64 @"\01_write"(i32, i8*, i64) #1

declare i32* @__error() #1

declare i8* @"\01_strerror"(i32) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @lwrite(i32, i64, i64) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  store i32 %0, i32* %4, align 4
  store i64 %1, i64* %5, align 8
  store i64 %2, i64* %6, align 8
  store i64 0, i64* %7, align 8
  %9 = load i64, i64* %6, align 8
  %10 = mul i64 8, %9
  store i64 %10, i64* %8, align 8
  br label %11

; <label>:11:                                     ; preds = %39, %3
  %12 = load i64, i64* %8, align 8
  %13 = icmp ult i64 0, %12
  br i1 %13, label %14, label %42

; <label>:14:                                     ; preds = %11
  %15 = load i32, i32* %4, align 4
  %16 = bitcast i64* %5 to i8*
  %17 = call i64 @"\01_write"(i32 %15, i8* %16, i64 8)
  %18 = load i64, i64* %8, align 8
  %19 = sub i64 %18, %17
  store i64 %19, i64* %8, align 8
  %20 = call i32* @__error()
  %21 = load i32, i32* %20, align 4
  %22 = icmp ne i32 %21, 0
  br i1 %22, label %23, label %39

; <label>:23:                                     ; preds = %14
  call void @indent(i32 -1)
  %24 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %25 = call i32* @__error()
  %26 = load i32, i32* %25, align 4
  %27 = icmp slt i32 %26, 0
  br i1 %27, label %28, label %32

; <label>:28:                                     ; preds = %23
  %29 = call i32* @__error()
  %30 = load i32, i32* %29, align 4
  %31 = sub nsw i32 0, %30
  br label %35

; <label>:32:                                     ; preds = %23
  %33 = call i32* @__error()
  %34 = load i32, i32* %33, align 4
  br label %35

; <label>:35:                                     ; preds = %32, %28
  %36 = phi i32 [ %31, %28 ], [ %34, %32 ]
  %37 = call i8* @"\01_strerror"(i32 %36)
  %38 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %24, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.7, i32 0, i32 0), i32 360, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.22, i32 0, i32 0), i8* %37)
  call void @quit(i32 1, i32 1)
  br label %39

; <label>:39:                                     ; preds = %35, %14
  %40 = load i64, i64* %7, align 8
  %41 = add i64 %40, 2
  store i64 %41, i64* %7, align 8
  br label %11

; <label>:42:                                     ; preds = %11
  %43 = load i64, i64* %7, align 8
  %44 = load i32, i32* @total_written, align 4
  %45 = sext i32 %44 to i64
  %46 = add i64 %45, %43
  %47 = trunc i64 %46 to i32
  store i32 %47, i32* @total_written, align 4
  %48 = load i64, i64* %7, align 8
  ret i64 %48
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @write_arr(i32, i64, i32*, i32) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i64, align 8
  %7 = alloca i32*, align 8
  %8 = alloca i32, align 4
  %9 = alloca i64, align 8
  store i32 %0, i32* %5, align 4
  store i64 %1, i64* %6, align 8
  store i32* %2, i32** %7, align 8
  store i32 %3, i32* %8, align 4
  store i64 0, i64* %9, align 8
  br label %10

; <label>:10:                                     ; preds = %21, %4
  %11 = load i64, i64* %9, align 8
  %12 = load i64, i64* %6, align 8
  %13 = icmp ult i64 %11, %12
  br i1 %13, label %14, label %24

; <label>:14:                                     ; preds = %10
  %15 = load i32, i32* %5, align 4
  %16 = load i32*, i32** %7, align 8
  %17 = load i64, i64* %9, align 8
  %18 = getelementptr inbounds i32, i32* %16, i64 %17
  %19 = load i32, i32* %18, align 4
  %20 = call i64 @iwrite(i32 %15, i32 %19, i64 1)
  br label %21

; <label>:21:                                     ; preds = %14
  %22 = load i64, i64* %9, align 8
  %23 = add i64 %22, 1
  store i64 %23, i64* %9, align 8
  br label %10

; <label>:24:                                     ; preds = %10
  %25 = load i32, i32* %5, align 4
  %26 = load i64, i64* %6, align 8
  %27 = trunc i64 %26 to i32
  %28 = load i32, i32* %8, align 4
  %29 = call i64 @pad_block(i32 %25, i32 %27, i32 %28)
  ret i64 %29
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @pad_block(i32, i32, i32) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  store i32 %0, i32* %4, align 4
  store i32 %1, i32* %5, align 4
  store i32 %2, i32* %6, align 4
  store i64 0, i64* %7, align 8
  %9 = load i32, i32* %5, align 4
  %10 = sext i32 %9 to i64
  store i64 %10, i64* %8, align 8
  br label %11

; <label>:11:                                     ; preds = %21, %3
  %12 = load i64, i64* %8, align 8
  %13 = load i32, i32* %6, align 4
  %14 = sdiv i32 %13, 4
  %15 = sext i32 %14 to i64
  %16 = urem i64 %12, %15
  %17 = icmp ne i64 %16, 0
  br i1 %17, label %18, label %26

; <label>:18:                                     ; preds = %11
  %19 = load i32, i32* %4, align 4
  %20 = call i64 @iwrite(i32 %19, i32 0, i64 1)
  br label %21

; <label>:21:                                     ; preds = %18
  %22 = load i64, i64* %8, align 8
  %23 = add i64 %22, 1
  store i64 %23, i64* %8, align 8
  %24 = load i64, i64* %7, align 8
  %25 = add i64 %24, 1
  store i64 %25, i64* %7, align 8
  br label %11

; <label>:26:                                     ; preds = %11
  %27 = load i64, i64* %7, align 8
  ret i64 %27
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @blocks2words(i32, i32) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = sext i32 %5 to i64
  %7 = load i32, i32* %4, align 4
  %8 = sext i32 %7 to i64
  %9 = mul i64 %8, 1
  %10 = udiv i64 %9, 4
  %11 = mul i64 %6, %10
  ret i64 %11
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @blocks2bytes(i32, i32) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = sext i32 %5 to i64
  %7 = load i32, i32* %4, align 4
  %8 = sext i32 %7 to i64
  %9 = mul i64 %8, 1
  %10 = mul i64 %6, %9
  ret i64 %10
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @updiv(i64, i64) #0 {
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  store i64 %0, i64* %3, align 8
  store i64 %1, i64* %4, align 8
  %5 = load i64, i64* %3, align 8
  %6 = load i64, i64* %4, align 8
  %7 = udiv i64 %5, %6
  %8 = load i64, i64* %3, align 8
  %9 = load i64, i64* %4, align 8
  %10 = urem i64 %8, %9
  %11 = icmp ne i64 %10, 0
  %12 = zext i1 %11 to i64
  %13 = select i1 %11, i32 1, i32 0
  %14 = sext i32 %13 to i64
  %15 = add i64 %7, %14
  ret i64 %15
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @intmax(i64, i64) #0 {
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  store i64 %0, i64* %3, align 8
  store i64 %1, i64* %4, align 8
  %5 = load i64, i64* %3, align 8
  %6 = load i64, i64* %4, align 8
  %7 = icmp sgt i64 %5, %6
  br i1 %7, label %8, label %10

; <label>:8:                                      ; preds = %2
  %9 = load i64, i64* %3, align 8
  br label %12

; <label>:10:                                     ; preds = %2
  %11 = load i64, i64* %4, align 8
  br label %12

; <label>:12:                                     ; preds = %10, %8
  %13 = phi i64 [ %9, %8 ], [ %11, %10 ]
  ret i64 %13
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @intmin(i64, i64) #0 {
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  store i64 %0, i64* %3, align 8
  store i64 %1, i64* %4, align 8
  %5 = load i64, i64* %3, align 8
  %6 = load i64, i64* %4, align 8
  %7 = icmp slt i64 %5, %6
  br i1 %7, label %8, label %10

; <label>:8:                                      ; preds = %2
  %9 = load i64, i64* %3, align 8
  br label %12

; <label>:10:                                     ; preds = %2
  %11 = load i64, i64* %4, align 8
  br label %12

; <label>:12:                                     ; preds = %10, %8
  %13 = phi i64 [ %9, %8 ], [ %11, %10 ]
  ret i64 %13
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @dbg(i8*, i32, i8*, i8*) #0 {
  %5 = alloca i8*, align 8
  %6 = alloca i32, align 4
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  store i8* %0, i8** %5, align 8
  store i32 %1, i32* %6, align 4
  store i8* %2, i8** %7, align 8
  store i8* %3, i8** %8, align 8
  %9 = load i32, i32* @debug_enable, align 4
  %10 = icmp eq i32 %9, 1
  br i1 %10, label %11, label %32

; <label>:11:                                     ; preds = %4
  %12 = load i32, i32* @debug_disable_method, align 4
  %13 = icmp eq i32 %12, 0
  br i1 %13, label %14, label %32

; <label>:14:                                     ; preds = %11
  %15 = load i32, i32* @debug_disable_external, align 4
  %16 = icmp ne i32 %15, 1
  br i1 %16, label %17, label %32

; <label>:17:                                     ; preds = %14
  %18 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %19 = icmp ne %struct.__sFILE* %18, null
  br i1 %19, label %20, label %32

; <label>:20:                                     ; preds = %17
  %21 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %22 = icmp ne %struct.__sFILE* %21, null
  br i1 %22, label %23, label %32

; <label>:23:                                     ; preds = %20
  %24 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %25 = load i8*, i8** %5, align 8
  %26 = load i32, i32* %6, align 4
  %27 = load i8*, i8** %7, align 8
  %28 = load i8*, i8** %8, align 8
  %29 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %24, i8* getelementptr inbounds ([103 x i8], [103 x i8]* @.str.23, i32 0, i32 0), i8* %25, i32 %26, i8* %27, i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %28)
  %30 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %31 = call i32 @fflush(%struct.__sFILE* %30)
  br label %32

; <label>:32:                                     ; preds = %23, %20, %17, %14, %11, %4
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @dbg2(i8*, i32, i8*, i8*, i8*) #0 {
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8*, align 8
  store i8* %0, i8** %6, align 8
  store i32 %1, i32* %7, align 4
  store i8* %2, i8** %8, align 8
  store i8* %3, i8** %9, align 8
  store i8* %4, i8** %10, align 8
  %11 = load i32, i32* @debug_enable, align 4
  %12 = icmp eq i32 %11, 1
  br i1 %12, label %13, label %35

; <label>:13:                                     ; preds = %5
  %14 = load i32, i32* @debug_disable_method, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %35

; <label>:16:                                     ; preds = %13
  %17 = load i32, i32* @debug_disable_external, align 4
  %18 = icmp ne i32 %17, 1
  br i1 %18, label %19, label %35

; <label>:19:                                     ; preds = %16
  %20 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %21 = icmp ne %struct.__sFILE* %20, null
  br i1 %21, label %22, label %35

; <label>:22:                                     ; preds = %19
  %23 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %24 = icmp ne %struct.__sFILE* %23, null
  br i1 %24, label %25, label %35

; <label>:25:                                     ; preds = %22
  %26 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %27 = load i8*, i8** %6, align 8
  %28 = load i32, i32* %7, align 4
  %29 = load i8*, i8** %8, align 8
  %30 = load i8*, i8** %9, align 8
  %31 = load i8*, i8** %10, align 8
  %32 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %26, i8* getelementptr inbounds ([135 x i8], [135 x i8]* @.str.24, i32 0, i32 0), i8* %27, i32 %28, i8* %29, i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %30, i8* %31)
  %33 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %34 = call i32 @fflush(%struct.__sFILE* %33)
  br label %35

; <label>:35:                                     ; preds = %25, %22, %19, %16, %13, %5
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @dbgn(i8*, i32, i8*, i8*, i64) #0 {
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i64, align 8
  store i8* %0, i8** %6, align 8
  store i32 %1, i32* %7, align 4
  store i8* %2, i8** %8, align 8
  store i8* %3, i8** %9, align 8
  store i64 %4, i64* %10, align 8
  %11 = load i32, i32* @debug_enable, align 4
  %12 = icmp eq i32 %11, 1
  br i1 %12, label %13, label %35

; <label>:13:                                     ; preds = %5
  %14 = load i32, i32* @debug_disable_method, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %35

; <label>:16:                                     ; preds = %13
  %17 = load i32, i32* @debug_disable_external, align 4
  %18 = icmp ne i32 %17, 1
  br i1 %18, label %19, label %35

; <label>:19:                                     ; preds = %16
  %20 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %21 = icmp ne %struct.__sFILE* %20, null
  br i1 %21, label %22, label %35

; <label>:22:                                     ; preds = %19
  %23 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %24 = icmp ne %struct.__sFILE* %23, null
  br i1 %24, label %25, label %35

; <label>:25:                                     ; preds = %22
  %26 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %27 = load i8*, i8** %6, align 8
  %28 = load i32, i32* %7, align 4
  %29 = load i8*, i8** %8, align 8
  %30 = load i8*, i8** %9, align 8
  %31 = load i64, i64* %10, align 8
  %32 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %26, i8* getelementptr inbounds ([116 x i8], [116 x i8]* @.str.25, i32 0, i32 0), i8* %27, i32 %28, i8* %29, i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %30, i64 %31)
  %33 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %34 = call i32 @fflush(%struct.__sFILE* %33)
  br label %35

; <label>:35:                                     ; preds = %25, %22, %19, %16, %13, %5
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @dbgh(i8*, i32, i8*, i8*, i64) #0 {
  %6 = alloca i8*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i64, align 8
  store i8* %0, i8** %6, align 8
  store i32 %1, i32* %7, align 4
  store i8* %2, i8** %8, align 8
  store i8* %3, i8** %9, align 8
  store i64 %4, i64* %10, align 8
  %11 = load i32, i32* @debug_enable, align 4
  %12 = icmp eq i32 %11, 1
  br i1 %12, label %13, label %35

; <label>:13:                                     ; preds = %5
  %14 = load i32, i32* @debug_disable_method, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %35

; <label>:16:                                     ; preds = %13
  %17 = load i32, i32* @debug_disable_external, align 4
  %18 = icmp ne i32 %17, 1
  br i1 %18, label %19, label %35

; <label>:19:                                     ; preds = %16
  %20 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %21 = icmp ne %struct.__sFILE* %20, null
  br i1 %21, label %22, label %35

; <label>:22:                                     ; preds = %19
  %23 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %24 = icmp ne %struct.__sFILE* %23, null
  br i1 %24, label %25, label %35

; <label>:25:                                     ; preds = %22
  %26 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %27 = load i8*, i8** %6, align 8
  %28 = load i32, i32* %7, align 4
  %29 = load i8*, i8** %8, align 8
  %30 = load i8*, i8** %9, align 8
  %31 = load i64, i64* %10, align 8
  %32 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %26, i8* getelementptr inbounds ([118 x i8], [118 x i8]* @.str.26, i32 0, i32 0), i8* %27, i32 %28, i8* %29, i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %30, i64 %31)
  %33 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %34 = call i32 @fflush(%struct.__sFILE* %33)
  br label %35

; <label>:35:                                     ; preds = %25, %22, %19, %16, %13, %5
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @dbgtrace(i8*, i32, i8*) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca i32, align 4
  %6 = alloca i8*, align 8
  store i8* %0, i8** %4, align 8
  store i32 %1, i32* %5, align 4
  store i8* %2, i8** %6, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = load i32, i32* %5, align 4
  %9 = load i8*, i8** %6, align 8
  ret void
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { argmemonly nounwind }
attributes #3 = { noreturn "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { allocsize(0,1) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { nounwind readnone speculatable }
attributes #7 = { noreturn }
attributes #8 = { allocsize(0,1) }
attributes #9 = { nounwind }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
