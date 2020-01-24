; ModuleID = 'fat.c'
source_filename = "fat.c"
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
%union.superblock_u = type { %struct.superblock_t }

@pcache = external global %struct.pcache_t, align 8
@logfile = external global %struct.__sFILE*, align 8
@.str = private unnamed_addr constant [131 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[31m%8s\1B[0m \1B[31m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[31m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %sInvalid offset: \1B[1m%d\1B[22m\1B[0m\0A\00", align 1
@.str.1 = private unnamed_addr constant [6 x i8] c"fat.c\00", align 1
@.str.2 = private unnamed_addr constant [36 x i8] c"\1B[0m\1B[38;5;153m   get_root\1B[39m\1B[2m\00", align 1
@indentation = external global [81 x i8], align 16
@debug_enable = external global i32, align 4
@debug_disable_method = external global i32, align 4
@debug_disable_external = external global i32, align 4
@.str.3 = private unnamed_addr constant [127 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mErrno before seek:\1B[0m\0A\00", align 1
@.str.4 = private unnamed_addr constant [209 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mCouldn't seek to \1B[1m%d\1B[22m in file descriptor \1B[1m%d\1B[22m after \1B[1m%d\1B[22m tr%s (\1B[1m%d\1B[22m, %s)\1B[0m\0A\00", align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"y\00", align 1
@.str.6 = private unnamed_addr constant [4 x i8] c"ies\00", align 1
@.str.7 = private unnamed_addr constant [156 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[32m%8s\1B[0m \1B[32m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[32m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[32mlseek()ed to \1B[1m%d\1B[22m after \1B[1m%d\1B[22m tr%s\1B[0m\0A\00", align 1
@.str.8 = private unnamed_addr constant [110 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[31m%8s\1B[0m \1B[31m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[31m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s%s: %s\1B[0m\0A\00", align 1
@.str.9 = private unnamed_addr constant [14 x i8] c"Couldn't read\00", align 1
@.str.10 = private unnamed_addr constant [3 x i8] c"..\00", align 1
@.str.11 = private unnamed_addr constant [119 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[31m%8s\1B[0m \1B[31m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[31m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s%s: \1B[1m%d\1B[22m\1B[0m\0A\00", align 1
@.str.12 = private unnamed_addr constant [9 x i8] c"file_rd \00", align 1
@.str.13 = private unnamed_addr constant [14 x i8] c"Invalid block\00", align 1
@.str.14 = private unnamed_addr constant [10 x i8] c"file_read\00", align 1
@.str.15 = private unnamed_addr constant [14 x i8] c"Couldn't seek\00", align 1
@.str.16 = private unnamed_addr constant [210 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33m%s \1B[1m%s\1B[22m has no bytes left, but the file allocation table says more blocks are allocated to it.\1B[0m\0A\00", align 1
@.str.17 = private unnamed_addr constant [5 x i8] c"File\00", align 1
@.str.18 = private unnamed_addr constant [10 x i8] c"Directory\00", align 1
@.str.19 = private unnamed_addr constant [220 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33m\1B[2m\E2\94\94\1B[22m remaining = \1B[1m%d\1B[22m\1B[2m,\1B[22m pcache.fat[\1B[1m%d\1B[22m] = \1B[1m%d\1B[22m\1B[2m,\1B[22m bs = \1B[1m%d\1B[22m\1B[0m\0A\00", align 1
@.str.20 = private unnamed_addr constant [155 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33m%s \1B[1m%s\1B[22m has extra FAT blocks; trimming.\1B[0m\0A\00", align 1
@.str.21 = private unnamed_addr constant [115 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s \1B[1m%d\1B[22m \E2\86\90 -2\0A\00", align 1
@.str.22 = private unnamed_addr constant [25 x i8] c"Finished shrinking (-2).\00", align 1
@.str.23 = private unnamed_addr constant [24 x i8] c"Finished shrinking (0).\00", align 1
@.str.24 = private unnamed_addr constant [177 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mFAT[\1B[1m%d\1B[22m] = \1B[1m%d\1B[22m, outside of FAT (\1B[1m%d\1B[22m block%s)\1B[0m\0A\00", align 1
@.str.25 = private unnamed_addr constant [1 x i8] zeroinitializer, align 1
@.str.26 = private unnamed_addr constant [2 x i8] c"s\00", align 1
@.str.27 = private unnamed_addr constant [223 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mFile still has \1B[1m%d\1B[22m byte%s left, but the file allocation table doesn't have a next block after \1B[1m%d\1B[22m.\1B[0m\0A\00", align 1
@.str.28 = private unnamed_addr constant [332 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Writing directory entry at offset \1B[1m%ld\1B[22m (\1B[1m%ld\1B[22m\1B[2m,\1B[22m \1B[1m%ld\1B[22m\1B[2m:\1B[22m\1B[1m%ld\1B[22m) with filename \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m\1B[2m,\1B[22m length \1B[1m%u\1B[22m\1B[2m,\1B[22m start block \1B[1m%d\1B[22m (next: \1B[1m%d\1B[22m)\0A\00", align 1
@.str.29 = private unnamed_addr constant [28 x i8] c"\1B[0m\1B[2mwrite_entry\1B[0m\1B[2m\00", align 1
@.str.30 = private unnamed_addr constant [138 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mInvalid offset:: \1B[1m%ld\1B[22m\1B[0m\0A\00", align 1
@.str.31 = private unnamed_addr constant [148 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mlseek() failed \1B[2m\E2\86\92\1B[22m \1B[2m%s\1B[22m\1B[0m\0A\00", align 1
@.str.32 = private unnamed_addr constant [148 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mwrite() failed \1B[2m\E2\86\92\1B[22m \1B[2m%s\1B[22m\1B[0m\0A\00", align 1
@.str.33 = private unnamed_addr constant [166 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Writing root (\1B[1m%d\1B[22m \1B[2m\E2\86\92\1B[22m \1B[1m%d\1B[22m); dir %c= rootptr.\0A\00", align 1
@.str.34 = private unnamed_addr constant [204 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Updating \1B[38;5;128mpcache\1B[39m entry length for \1B[1m%s\1B[22m\1B[2m:\1B[22m \1B[1m%d\1B[22m \1B[2m\E2\86\92\1B[22m \1B[1m%d\1B[22m\0A\00", align 1
@.str.35 = private unnamed_addr constant [202 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Freeing space for file at block \1B[1m%d\1B[22m\1B[2m;\1B[22m size\1B[2m:\1B[22m \1B[1m%d\1B[22m \1B[2m\E2\86\92\1B[22m \1B[1m%d\1B[22m\0A\00", align 1
@.str.36 = private unnamed_addr constant [12 x i8] c"zerooutfree\00", align 1
@.str.37 = private unnamed_addr constant [177 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mNew size isn't smaller than old size (diff = \1B[1m%d\1B[22m); skipping.\1B[0m\0A\00", align 1
@.str.38 = private unnamed_addr constant [141 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mlseek() failed: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.39 = private unnamed_addr constant [147 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s bs = \1B[1m%d\1B[22m\1B[2m,\1B[22m remaining = \1B[1m%u\1B[22m\0A\00", align 1
@.str.40 = private unnamed_addr constant [133 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s \1B[1m%d\1B[22m \1B[2m\E2\86\92\1B[22m \1B[1m%d\1B[22m\0A\00", align 1
@.str.41 = private unnamed_addr constant [22 x i8] c"Invalid block in loop\00", align 1
@.str.42 = private unnamed_addr constant [5 x i8] c"diff\00", align 1
@.str.43 = private unnamed_addr constant [141 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mwrite() failed: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.44 = private unnamed_addr constant [6 x i8] c"Done.\00", align 1
@.str.45 = private unnamed_addr constant [12 x i8] c"rsuperblock\00", align 1
@.str.46 = private unnamed_addr constant [28 x i8] c"Couldn't seek in superblock\00", align 1
@.str.47 = private unnamed_addr constant [25 x i8] c"Couldn't read superblock\00", align 1
@.str.48 = private unnamed_addr constant [11 x i8] c"read_table\00", align 1
@.str.49 = private unnamed_addr constant [36 x i8] c"Couldn't read file allocation table\00", align 1
@__stderrp = external global %struct.__sFILE*, align 8
@.str.50 = private unnamed_addr constant [37 x i8] c"%s \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m:\0A\00", align 1
@.str.51 = private unnamed_addr constant [31 x i8] c"\09  Length: \1B[1m%d\1B[22m byte%s\0A\00", align 1
@.str.52 = private unnamed_addr constant [31 x i8] c"\09  Length: \1B[1m%d\1B[22m entr%s\0A\00", align 1
@.str.53 = private unnamed_addr constant [25 x i8] c"\09    Time: \1B[1m%ld\1B[22m\0A\00", align 1
@.str.54 = private unnamed_addr constant [25 x i8] c"\09 Created: \1B[1m%ld\1B[22m\0A\00", align 1
@.str.55 = private unnamed_addr constant [25 x i8] c"\09Modified: \1B[1m%ld\1B[22m\0A\00", align 1
@.str.56 = private unnamed_addr constant [25 x i8] c"\09Accessed: \1B[1m%ld\1B[22m\0A\00", align 1
@.str.57 = private unnamed_addr constant [24 x i8] c"\09   Start: \1B[1m%d\1B[22m\0A\00", align 1
@.str.58 = private unnamed_addr constant [24 x i8] c"\09   Root?: \1B[1m%s\1B[22m\0A\00", align 1
@.str.59 = private unnamed_addr constant [4 x i8] c"Yes\00", align 1
@.str.60 = private unnamed_addr constant [3 x i8] c"No\00", align 1
@.str.61 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.62 = private unnamed_addr constant [111 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33m%s\1B[0m\0A\00", align 1
@.str.63 = private unnamed_addr constant [13 x i8] c"chain_length\00", align 1
@.str.64 = private unnamed_addr constant [21 x i8] c"Start block is free.\00", align 1
@.str.65 = private unnamed_addr constant [27 x i8] c"Chain ended on free block.\00", align 1
@.str.66 = private unnamed_addr constant [30 x i8] c"Chain ended on invalid block.\00", align 1
@.str.67 = private unnamed_addr constant [148 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[31m%8s\1B[0m \1B[31m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[31m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %sChain contains an invalid block: \1B[1m%d\1B[22m\1B[0m\0A\00", align 1
@.str.68 = private unnamed_addr constant [106 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[31m%8s\1B[0m \1B[31m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[31m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s%s\1B[0m\0A\00", align 1
@.str.69 = private unnamed_addr constant [9 x i8] c"fat_save\00", align 1
@.str.70 = private unnamed_addr constant [31 x i8] c"File allocation table is null.\00", align 1
@.str.71 = private unnamed_addr constant [37 x i8] c"Couldn't save file allocation table.\00", align 1
@.str.72 = private unnamed_addr constant [182 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mDirectory length \1B[1m%d\1B[22m isn't a multiple of dir_t size \1B[1m%ld\1B[22m.\1B[0m\0A\00", align 1
@.str.73 = private unnamed_addr constant [9 x i8] c"dir_read\00", align 1
@.str.74 = private unnamed_addr constant [2 x i8] c".\00", align 1
@.str.75 = private unnamed_addr constant [36 x i8] c"\1B[0m\1B[38;5;112m       find\1B[39m\1B[2m\00", align 1
@.str.76 = private unnamed_addr constant [28 x i8] c"Both search types are NULL.\00", align 1
@.str.77 = private unnamed_addr constant [49 x i8] c"Found from \1B[36mfdcache\1B[39m for file descriptor\00", align 1
@.str.78 = private unnamed_addr constant [201 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Found from \1B[38;5;128mpcache\1B[39m for path \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m\1B[2m,\1B[22m offset \1B[1m%ld\1B[22m\0A\00", align 1
@.str.79 = private unnamed_addr constant [67 x i8] c"\1B[2m\E2\94\94\1B[22m pitem\1B[2m->\1B[22mentry\1B[2m->\1B[22mfname: \1B[31mempty\1B[0m\00", align 1
@.str.80 = private unnamed_addr constant [22 x i8] c"Returning from cache.\00", align 1
@.str.81 = private unnamed_addr constant [2 x i8] c"/\00", align 1
@.str.82 = private unnamed_addr constant [20 x i8] c"Returning the root.\00", align 1
@.str.83 = private unnamed_addr constant [26 x i8] c"Returning path component.\00", align 1
@.str.84 = private unnamed_addr constant [158 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mCouldn't read directory. Status: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.85 = private unnamed_addr constant [27 x i8] c"Returning file at the end.\00", align 1
@.str.86 = private unnamed_addr constant [185 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s   Name\1B[2m:\1B[22m \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m\1B[2m,\1B[22m offset\1B[2m:\1B[22m \1B[1m%ld\1B[22m\0A\00", align 1
@.str.87 = private unnamed_addr constant [137 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mNot a directory: \1B[1m%s\1B[22m\1B[0m\0A\00", align 1
@.str.88 = private unnamed_addr constant [32 x i8] c"Returning directory at the end.\00", align 1
@.str.89 = private unnamed_addr constant [8 x i8] c"  Name:\00", align 1
@.str.90 = private unnamed_addr constant [19 x i8] c"Returning nothing.\00", align 1
@.str.91 = private unnamed_addr constant [58 x i8] c"Reached the end of the function \1B[2m\E2\86\92\1B[22m \1B[2mEIO\1B[22m\00", align 1
@.str.92 = private unnamed_addr constant [36 x i8] c"\1B[0m\1B[38;5;219m    newfile\1B[39m\1B[2m\00", align 1
@.str.93 = private unnamed_addr constant [29 x i8] c"Trying to create new file at\00", align 1
@.str.94 = private unnamed_addr constant [142 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mfat_find failed: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.95 = private unnamed_addr constant [170 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mName too long: \1B[1m%s\1B[22m \1B[2m\E2\86\92\1B[22m \1B[2mENAMETOOLONG\1B[22m\1B[0m\0A\00", align 1
@.str.96 = private unnamed_addr constant [43 x i8] c"No free block \1B[2m\E2\86\92\1B[22m \1B[2mENOSPC\1B[22m\00", align 1
@.str.97 = private unnamed_addr constant [152 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[32m%8s\1B[0m \1B[32m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[32m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[32mAllocated \1B[1m%s\1B[22m at block \1B[1m%d\1B[22m.\1B[0m\0A\00", align 1
@.str.98 = private unnamed_addr constant [160 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[32m%8s\1B[0m \1B[32m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[32m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[32m\1B[36mFound\1B[39m freed entry at offset \1B[1m%ld\1B[22m.\1B[0m\0A\00", align 1
@.str.99 = private unnamed_addr constant [119 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m\1B[36m%8s\1B[0m \1B[2m\1B[36m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[36m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[36m%s\1B[0m\0A\00", align 1
@.str.100 = private unnamed_addr constant [14 x i8] c"Scenario one.\00", align 1
@.str.101 = private unnamed_addr constant [165 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mCouldn't add entry to parent directory: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.102 = private unnamed_addr constant [264 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s [S1] parent->length \1B[2m=\1B[22m \1B[1m%u\1B[22m\1B[2m,\1B[22m offset_index \1B[2m=\1B[22m \1B[1m%lu\1B[22m\1B[2m,\1B[22m parent->length / sizeof(dir_t) \1B[2m=\1B[22m \1B[1m%lu\1B[22m\1B[2m,\1B[22m %s\0A\00", align 1
@.str.103 = private unnamed_addr constant [3 x i8] c"==\00", align 1
@.str.104 = private unnamed_addr constant [3 x i8] c"!=\00", align 1
@.str.105 = private unnamed_addr constant [14 x i8] c"Scenario two.\00", align 1
@.str.106 = private unnamed_addr constant [147 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mNo free block \1B[2m\E2\86\92\1B[22m \1B[2m%s\1B[22m\1B[0m\0A\00", align 1
@.str.107 = private unnamed_addr constant [7 x i8] c"ENOSPC\00", align 1
@.str.108 = private unnamed_addr constant [20 x i8] c"Parent start block:\00", align 1
@.str.109 = private unnamed_addr constant [14 x i8] c"  Skipping to\00", align 1
@.str.110 = private unnamed_addr constant [119 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s   \1B[2m... %d more\1B[22m\0A\00", align 1
@.str.111 = private unnamed_addr constant [228 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s bs - sizeof(dir_t) < remaining  \1B[2m\E2\9F\B7\1B[22m  \1B[1m%ld\1B[22m - \1B[1m%ld\1B[22m < \1B[1m%ld\1B[22m  \1B[2m\E2\9F\B7\1B[22m  \1B[1m%ld\1B[22m < \1B[1m%ld\1B[22m\0A\00", align 1
@.str.112 = private unnamed_addr constant [16 x i8] c"Scenario three.\00", align 1
@.str.113 = private unnamed_addr constant [167 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mNo free block (need \1B[1m%ld\1B[22m) \1B[2m\E2\86\92\1B[22m \1B[2m%s\1B[22m\1B[0m\0A\00", align 1
@.str.114 = private unnamed_addr constant [166 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mCouldn't add entry to parent directory.: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.115 = private unnamed_addr constant [15 x i8] c"Scenario four.\00", align 1
@.str.116 = private unnamed_addr constant [42 x i8] c"\1B[38;5;128mIncreasing parent length.\1B[39m\00", align 1
@.str.117 = private unnamed_addr constant [170 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mCouldn't write the parent directory to disk: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.118 = private unnamed_addr constant [222 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s About to insert into \1B[38;5;128mpcache\1B[39m\1B[2m:\1B[22m \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m\1B[2m,\1B[22m offset\1B[2m:\1B[22m \1B[1m%ld\1B[22m\0A\00", align 1
@.str.119 = private unnamed_addr constant [10 x i8] c"Inserted.\00", align 1
@.str.120 = private unnamed_addr constant [152 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[31m%8s\1B[0m \1B[31m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[31m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[38;5;128mpc_insert\1B[39m() failed (\1B[1m%d\1B[22m)\1B[0m\0A\00", align 1
@.str.121 = private unnamed_addr constant [196 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s \1B[33mSkipping\1B[39m resize for path \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m to size \1B[1m%ld\1B[22m (same size)\0A\00", align 1
@.str.122 = private unnamed_addr constant [30 x i8] c"\1B[0m\1B[36m     resize\1B[39m\1B[2m\00", align 1
@.str.123 = private unnamed_addr constant [67 x i8] c"Trying to resize a free file. Defaulting to apparent block length.\00", align 1
@.str.124 = private unnamed_addr constant [346 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s \1B[36mResizing\1B[39m for path \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m to new size \1B[1m%ld\1B[22m; file\1B[2m->\1B[22mlength\1B[2m:\1B[22m \1B[1m%d\1B[22m\1B[2m,\1B[22m blocks needed for old size\1B[2m:\1B[22m \1B[1m%ld\1B[22m\1B[2m,\1B[22m blocks needed for new size\1B[2m:\1B[22m \1B[1m%ld\1B[22m\0A\00", align 1
@.str.125 = private unnamed_addr constant [17 x i8] c"Truncating to 0.\00", align 1
@.str.126 = private unnamed_addr constant [136 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s No change in block count (\1B[1m%ld\1B[22m)\0A\00", align 1
@.str.127 = private unnamed_addr constant [151 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mfat_zero_out_free status: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.128 = private unnamed_addr constant [210 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s \1B[36mTrying to change file\1B[2m->\1B[22mlength\1B[39m at \1B[1m%ld\1B[22m from \1B[1m%d\1B[22m byte(s) to \1B[1m%ld\1B[22m byte(s)\0A\00", align 1
@.str.129 = private unnamed_addr constant [149 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mfat_write_entry status: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.130 = private unnamed_addr constant [152 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Reducing block count from \1B[1m%ld\1B[22m to \1B[1m%ld\1B[22m.\0A\00", align 1
@.str.131 = private unnamed_addr constant [36 x i8] c"\1B[38;5;128mNoting\1B[39m a FAT block:\00", align 1
@.str.132 = private unnamed_addr constant [31 x i8] c"\1B[34mFreeing\1B[39m a FAT block:\00", align 1
@.str.133 = private unnamed_addr constant [30 x i8] c"\1B[34mEnding\1B[39m a FAT block:\00", align 1
@.str.134 = private unnamed_addr constant [27 x i8] c"Setting new byte length to\00", align 1
@.str.135 = private unnamed_addr constant [149 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mfat_write_entry failed: \1B[1m%d\1B[22m (%s)\1B[0m\0A\00", align 1
@.str.136 = private unnamed_addr constant [154 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Increasing block count from \1B[1m%ld\1B[22m to \1B[1m%ld\1B[22m.\0A\00", align 1
@.str.137 = private unnamed_addr constant [131 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Trying to add \1B[1m%ld\1B[22m block%s\0A\00", align 1
@.str.138 = private unnamed_addr constant [47 x i8] c"Not enough blocks \1B[2m\E2\86\92\1B[22m \1B[2mENOSPC\1B[22m\00", align 1
@.str.139 = private unnamed_addr constant [42 x i8] c"Out of space \1B[2m\E2\86\92\1B[22m \1B[2mENOSPC\1B[22m\00", align 1
@.str.140 = private unnamed_addr constant [22 x i8] c"\1B[32mAdded\1B[39m block\00", align 1
@.str.141 = private unnamed_addr constant [192 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Trying to change file\1B[2m->\1B[22mlength at offset \1B[1m%ld\1B[22m from \1B[1m%d\1B[22m to \1B[1m%ld\1B[22m.\0A\00", align 1
@.str.142 = private unnamed_addr constant [111 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[32m%8s\1B[0m \1B[32m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[32m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[32m%s\1B[0m\0A\00", align 1
@.str.143 = private unnamed_addr constant [22 x i8] c"Successfully resized.\00", align 1
@.str.144 = private unnamed_addr constant [120 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Compacting \1B[1m%s\1B[22m.\0A\00", align 1
@.str.145 = private unnamed_addr constant [36 x i8] c"\1B[0m\1B[38;5;153m    compact\1B[39m\1B[2m\00", align 1
@.str.146 = private unnamed_addr constant [9 x i8] c"Alloc'd:\00", align 1
@.str.147 = private unnamed_addr constant [163 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s \1B[1m%s\1B[22m \1B[2m\E2\86\92\1B[22m (\1B[1m%d\1B[22m\1B[2m,\1B[22m \1B[1m%lu\1B[22m); %lu\0A\00", align 1
@.str.148 = private unnamed_addr constant [15 x i8] c"Couldn't write\00", align 1
@.str.149 = private unnamed_addr constant [139 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s   \1B[31m%ld\1B[39m \1B[2m\E2\86\90\1B[22m \1B[32m%lu\1B[39m\0A\00", align 1
@nothing = external constant [4096 x i8], align 16
@.str.150 = private unnamed_addr constant [165 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mInvalid next block: \1B[1m%d\1B[22m \1B[2m\E2\86\92\1B[22m \1B[1m%d\1B[22m\1B[0m\0A\00", align 1
@.str.151 = private unnamed_addr constant [25 x i8] c"Zeroing out after offset\00", align 1
@.str.152 = private unnamed_addr constant [38 x i8] c"Freeing directory blocks, starting at\00", align 1
@.str.153 = private unnamed_addr constant [169 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Removing \1B[1m%s\1B[22m from the filesystem %s from \1B[38;5;128mpcache\1B[39m.\0A\00", align 1
@.str.154 = private unnamed_addr constant [30 x i8] c"\1B[0m\1B[31m     remove\1B[39m\1B[2m\00", align 1
@.str.155 = private unnamed_addr constant [4 x i8] c"and\00", align 1
@.str.156 = private unnamed_addr constant [8 x i8] c"but not\00", align 1
@.str.157 = private unnamed_addr constant [207 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[2m%8s\1B[0m \1B[2m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[0m%11s\1B[0m \1B[2m\E2\94\82\1B[22m %s Offset\1B[2m:\1B[22m \1B[1m%ld\1B[22m\1B[2m,\1B[22m start\1B[2m:\1B[22m \1B[1m%d\1B[22m\1B[2m,\1B[22m next block\1B[2m:\1B[22m \1B[1m%d\1B[22m\0A\00", align 1
@.str.158 = private unnamed_addr constant [189 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[33m%8s\1B[0m \1B[33m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[33m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[33mDirectory length (\1B[1m%d\1B[22m) is not a multiple of sizeof(dir_t) (\1B[1m%lu\1B[22m)\1B[0m\0A\00", align 1
@.str.159 = private unnamed_addr constant [36 x i8] c"\1B[0m\1B[38;5;153mcount_alloc\1B[39m\1B[2m\00", align 1
@.str.160 = private unnamed_addr constant [23 x i8] c"Moved into free block.\00", align 1
@.str.161 = private unnamed_addr constant [228 x i8] c"\1B[2m\E2\94\82\1B[22m\1B[1m\1B[32m%8s\1B[0m \1B[32m%4d\1B[0m\1B[2m\E2\94\82\1B[22m  \1B[2m\E2\94\82 \1B[22m\1B[32m%11s\1B[0m \1B[2m\E2\94\82\1B[22m  %s\1B[32mFound \1B[1m%lu\1B[22m allocated entr%s out of \1B[1m%lu\1B[22m total for \1B[2m\22\1B[22m\1B[1m%s\1B[22m\1B[2m\22\1B[22m at block \1B[1m%d\1B[22m.\1B[0m\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fat_write_superblock(i32, %struct.superblock_t* byval align 8) #0 {
  %3 = alloca i32, align 4
  %4 = alloca %union.superblock_u, align 4
  store i32 %0, i32* %3, align 4
  %5 = load i32, i32* %3, align 4
  %6 = call i64 @lseek(i32 %5, i64 0, i32 0)
  %7 = load i32, i32* %3, align 4
  %8 = bitcast %union.superblock_u* %4 to %struct.superblock_t*
  %9 = bitcast %struct.superblock_t* %8 to i8*
  %10 = bitcast %struct.superblock_t* %1 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 4 %9, i8* align 8 %10, i64 20, i1 false)
  %11 = bitcast %union.superblock_u* %4 to [5 x i32]*
  %12 = getelementptr inbounds [5 x i32], [5 x i32]* %11, i32 0, i32 0
  %13 = getelementptr inbounds %struct.superblock_t, %struct.superblock_t* %1, i32 0, i32 3
  %14 = load i32, i32* %13, align 4
  %15 = call i64 @write_arr(i32 %7, i64 5, i32* %12, i32 %14)
  ret void
}

declare i64 @lseek(i32, i64, i32) #1

declare i64 @write_arr(i32, i64, i32*, i32) #1

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @fat_blocks_required(i64, i32) #0 {
  %3 = alloca i64, align 8
  %4 = alloca i32, align 4
  store i64 %0, i64* %3, align 8
  store i32 %1, i32* %4, align 4
  %5 = load i64, i64* %3, align 8
  %6 = load i32, i32* %4, align 4
  %7 = sext i32 %6 to i64
  %8 = call i64 @updiv(i64 %5, i64 %7)
  ret i64 %8
}

declare i64 @updiv(i64, i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fat_update_name(%struct.dir_t*, i8*) #0 {
  %3 = alloca %struct.dir_t*, align 8
  %4 = alloca i8*, align 8
  store %struct.dir_t* %0, %struct.dir_t** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %struct.dir_t*, %struct.dir_t** %3, align 8
  %6 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %5, i32 0, i32 0
  %7 = bitcast %union.fname_u* %6 to [24 x i8]*
  %8 = getelementptr inbounds [24 x i8], [24 x i8]* %7, i32 0, i32 0
  %9 = load %struct.dir_t*, %struct.dir_t** %3, align 8
  %10 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %9, i32 0, i32 0
  %11 = bitcast %union.fname_u* %10 to [24 x i8]*
  %12 = getelementptr inbounds [24 x i8], [24 x i8]* %11, i32 0, i32 0
  %13 = call i64 @llvm.objectsize.i64.p0i8(i8* %12, i1 false, i1 true)
  %14 = call i8* @__memset_chk(i8* %8, i32 0, i64 24, i64 %13) #7
  %15 = load %struct.dir_t*, %struct.dir_t** %3, align 8
  %16 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %15, i32 0, i32 0
  %17 = bitcast %union.fname_u* %16 to [24 x i8]*
  %18 = getelementptr inbounds [24 x i8], [24 x i8]* %17, i32 0, i32 0
  %19 = load i8*, i8** %4, align 8
  %20 = call i8* @__strcpy_chk(i8* %18, i8* %19, i64 24) #7
  ret void
}

; Function Attrs: nounwind
declare i8* @__memset_chk(i8*, i32, i64, i64) #3

; Function Attrs: nounwind readnone speculatable
declare i64 @llvm.objectsize.i64.p0i8(i8*, i1, i1) #4

; Function Attrs: nounwind
declare i8* @__strcpy_chk(i8*, i8*, i64) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fat_update_times(%struct.dir_t*, i64) #0 {
  %3 = alloca %struct.dir_t*, align 8
  %4 = alloca i64, align 8
  store %struct.dir_t* %0, %struct.dir_t** %3, align 8
  store i64 %1, i64* %4, align 8
  %5 = load i64, i64* %4, align 8
  %6 = load %struct.dir_t*, %struct.dir_t** %3, align 8
  %7 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %6, i32 0, i32 1
  %8 = getelementptr inbounds %struct.times_t, %struct.times_t* %7, i32 0, i32 2
  store i64 %5, i64* %8, align 8
  %9 = load %struct.dir_t*, %struct.dir_t** %3, align 8
  %10 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %9, i32 0, i32 1
  %11 = getelementptr inbounds %struct.times_t, %struct.times_t* %10, i32 0, i32 1
  store i64 %5, i64* %11, align 8
  %12 = load %struct.dir_t*, %struct.dir_t** %3, align 8
  %13 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %12, i32 0, i32 1
  %14 = getelementptr inbounds %struct.times_t, %struct.times_t* %13, i32 0, i32 0
  store i64 %5, i64* %14, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
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

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @fat_forget(i32) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  store i32 %0, i32* %2, align 4
  call void @indent(i32 1)
  %6 = load i32, i32* %2, align 4
  %7 = sext i32 %6 to i64
  store i64 %7, i64* %4, align 8
  store i64 0, i64* %5, align 8
  br label %8

; <label>:8:                                      ; preds = %34, %1
  %9 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %10 = load i64, i64* %4, align 8
  %11 = getelementptr inbounds i32, i32* %9, i64 %10
  %12 = load i32, i32* %11, align 4
  %13 = sext i32 %12 to i64
  store i64 %13, i64* %3, align 8
  %14 = load i64, i64* %3, align 8
  %15 = icmp eq i64 %14, -2
  br i1 %15, label %16, label %22

; <label>:16:                                     ; preds = %8
  %17 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %18 = load i64, i64* %4, align 8
  %19 = getelementptr inbounds i32, i32* %17, i64 %18
  store i32 0, i32* %19, align 4
  %20 = load i64, i64* %5, align 8
  %21 = add i64 %20, 1
  store i64 %21, i64* %5, align 8
  br label %35

; <label>:22:                                     ; preds = %8
  %23 = load i64, i64* %3, align 8
  %24 = icmp slt i64 0, %23
  br i1 %24, label %25, label %32

; <label>:25:                                     ; preds = %22
  %26 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %27 = load i64, i64* %4, align 8
  %28 = getelementptr inbounds i32, i32* %26, i64 %27
  store i32 0, i32* %28, align 4
  %29 = load i64, i64* %5, align 8
  %30 = add i64 %29, 1
  store i64 %30, i64* %5, align 8
  %31 = load i64, i64* %3, align 8
  store i64 %31, i64* %4, align 8
  br label %33

; <label>:32:                                     ; preds = %22
  br label %35

; <label>:33:                                     ; preds = %25
  br label %34

; <label>:34:                                     ; preds = %33
  br label %8

; <label>:35:                                     ; preds = %32, %16
  %36 = load i64, i64* %5, align 8
  %37 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %38 = add i64 %37, %36
  store i64 %38, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %39 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 5), align 8
  %40 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %39, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %40)
  call void @indent(i32 -1)
  %41 = load i64, i64* %5, align 8
  ret i64 %41
}

declare void @indent(i32) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fat_save(i32, %struct.superblock_t*, i32*) #0 {
  %4 = alloca i32, align 4
  %5 = alloca %struct.superblock_t*, align 8
  %6 = alloca i32*, align 8
  store i32 %0, i32* %4, align 4
  store %struct.superblock_t* %1, %struct.superblock_t** %5, align 8
  store i32* %2, i32** %6, align 8
  call void @indent(i32 1)
  %7 = load i32*, i32** %6, align 8
  %8 = icmp eq i32* %7, null
  br i1 %8, label %9, label %12

; <label>:9:                                      ; preds = %3
  %10 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %11 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %10, i8* getelementptr inbounds ([106 x i8], [106 x i8]* @.str.68, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 558, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.69, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.70, i32 0, i32 0))
  call void @quit(i32 1, i32 1)
  br label %12

; <label>:12:                                     ; preds = %9, %3
  %13 = load i32, i32* %4, align 4
  %14 = load %struct.superblock_t*, %struct.superblock_t** %5, align 8
  %15 = getelementptr inbounds %struct.superblock_t, %struct.superblock_t* %14, i32 0, i32 3
  %16 = load i32, i32* %15, align 4
  %17 = zext i32 %16 to i64
  %18 = call i64 @lseek(i32 %13, i64 %17, i32 0)
  %19 = load i32, i32* %4, align 4
  %20 = load i32*, i32** %6, align 8
  %21 = bitcast i32* %20 to i8*
  %22 = load %struct.superblock_t*, %struct.superblock_t** %5, align 8
  %23 = getelementptr inbounds %struct.superblock_t, %struct.superblock_t* %22, i32 0, i32 2
  %24 = load i32, i32* %23, align 4
  %25 = load %struct.superblock_t*, %struct.superblock_t** %5, align 8
  %26 = getelementptr inbounds %struct.superblock_t, %struct.superblock_t* %25, i32 0, i32 3
  %27 = load i32, i32* %26, align 4
  %28 = call i64 @blocks2bytes(i32 %24, i32 %27)
  %29 = call i64 @"\01_write"(i32 %19, i8* %21, i64 %28)
  %30 = call i32* @__error()
  %31 = load i32, i32* %30, align 4
  %32 = icmp ne i32 %31, 0
  br i1 %32, label %33, label %49

; <label>:33:                                     ; preds = %12
  call void @indent(i32 -1)
  %34 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %35 = call i32* @__error()
  %36 = load i32, i32* %35, align 4
  %37 = icmp slt i32 %36, 0
  br i1 %37, label %38, label %42

; <label>:38:                                     ; preds = %33
  %39 = call i32* @__error()
  %40 = load i32, i32* %39, align 4
  %41 = sub nsw i32 0, %40
  br label %45

; <label>:42:                                     ; preds = %33
  %43 = call i32* @__error()
  %44 = load i32, i32* %43, align 4
  br label %45

; <label>:45:                                     ; preds = %42, %38
  %46 = phi i32 [ %41, %38 ], [ %44, %42 ]
  %47 = call i8* @"\01_strerror"(i32 %46)
  %48 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %34, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 562, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.69, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.71, i32 0, i32 0), i8* %47)
  call void @quit(i32 1, i32 1)
  br label %49

; <label>:49:                                     ; preds = %45, %12
  call void @indent(i32 -1)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fat_save_caches(i32) #0 {
  %2 = alloca i32, align 4
  %3 = alloca %struct.pathc_t*, align 8
  %4 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  %5 = load i32, i32* %2, align 4
  call void @fat_write_superblock(i32 %5, %struct.superblock_t* byval align 8 getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1))
  %6 = load i32, i32* %2, align 4
  %7 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %6, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %7)
  store %struct.pathc_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 0, i32 0), %struct.pathc_t** %3, align 8
  %8 = call i32 (...) @pathc_alive_down()
  store i32 0, i32* %4, align 4
  br label %9

; <label>:9:                                      ; preds = %48, %1
  %10 = load i32, i32* %4, align 4
  %11 = icmp slt i32 %10, 1024
  br i1 %11, label %12, label %51

; <label>:12:                                     ; preds = %9
  %13 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %14 = load i32, i32* %4, align 4
  %15 = sext i32 %14 to i64
  %16 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %13, i64 %15
  %17 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %16, i32 0, i32 0
  %18 = load i8, i8* %17, align 8
  %19 = trunc i8 %18 to i1
  br i1 %19, label %20, label %47

; <label>:20:                                     ; preds = %12
  %21 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %22 = load i32, i32* %4, align 4
  %23 = sext i32 %22 to i64
  %24 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %21, i64 %23
  %25 = call i32 @pathc_down(%struct.pathc_t* %24)
  %26 = icmp ne i32 %25, 0
  br i1 %26, label %27, label %28

; <label>:27:                                     ; preds = %20
  br label %48

; <label>:28:                                     ; preds = %20
  %29 = load i32, i32* %2, align 4
  %30 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %31 = load i32, i32* %4, align 4
  %32 = sext i32 %31 to i64
  %33 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %30, i64 %32
  %34 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %33, i32 0, i32 2
  %35 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %36 = load i32, i32* %4, align 4
  %37 = sext i32 %36 to i64
  %38 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %35, i64 %37
  %39 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %38, i32 0, i32 4
  %40 = load i64, i64* %39, align 8
  %41 = call i32 @fat_write_entry(i32 %29, %struct.dir_t* %34, i64 %40)
  %42 = load %struct.pathc_t*, %struct.pathc_t** %3, align 8
  %43 = load i32, i32* %4, align 4
  %44 = sext i32 %43 to i64
  %45 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %42, i64 %44
  %46 = call i32 @pathc_up(%struct.pathc_t* %45)
  br label %47

; <label>:47:                                     ; preds = %28, %12
  br label %48

; <label>:48:                                     ; preds = %47, %27
  %49 = load i32, i32* %4, align 4
  %50 = add nsw i32 %49, 1
  store i32 %50, i32* %4, align 4
  br label %9

; <label>:51:                                     ; preds = %9
  %52 = call i32 (...) @pathc_alive_up()
  ret void
}

declare i32 @pathc_alive_down(...) #1

declare i32 @pathc_down(%struct.pathc_t*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_write_entry(i32, %struct.dir_t*, i64) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca %struct.dir_t*, align 8
  %7 = alloca i64, align 8
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca %struct.dir_t, align 8
  %11 = alloca i32, align 4
  %12 = alloca %struct.pathc_t*, align 8
  store i32 %0, i32* %5, align 4
  store %struct.dir_t* %1, %struct.dir_t** %6, align 8
  store i64 %2, i64* %7, align 8
  call void @indent(i32 1)
  %13 = load i32, i32* @debug_enable, align 4
  %14 = icmp eq i32 %13, 1
  br i1 %14, label %15, label %61

; <label>:15:                                     ; preds = %3
  %16 = load i32, i32* @debug_disable_method, align 4
  %17 = icmp eq i32 %16, 0
  br i1 %17, label %18, label %61

; <label>:18:                                     ; preds = %15
  %19 = load i32, i32* @debug_disable_external, align 4
  %20 = icmp ne i32 %19, 1
  br i1 %20, label %21, label %61

; <label>:21:                                     ; preds = %18
  %22 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %23 = icmp ne %struct.__sFILE* %22, null
  br i1 %23, label %24, label %61

; <label>:24:                                     ; preds = %21
  %25 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %26 = load i64, i64* %7, align 8
  %27 = load i64, i64* %7, align 8
  %28 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %29 = zext i32 %28 to i64
  %30 = sdiv i64 %27, %29
  %31 = load i64, i64* %7, align 8
  %32 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %33 = zext i32 %32 to i64
  %34 = srem i64 %31, %33
  %35 = udiv i64 %34, 64
  %36 = load i64, i64* %7, align 8
  %37 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %38 = zext i32 %37 to i64
  %39 = srem i64 %36, %38
  %40 = urem i64 %39, 64
  %41 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %42 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %41, i32 0, i32 0
  %43 = bitcast %union.fname_u* %42 to [24 x i8]*
  %44 = getelementptr inbounds [24 x i8], [24 x i8]* %43, i32 0, i32 0
  %45 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %46 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %45, i32 0, i32 2
  %47 = load i32, i32* %46, align 8
  %48 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %49 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %48, i32 0, i32 3
  %50 = load i32, i32* %49, align 4
  %51 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %52 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %53 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %52, i32 0, i32 3
  %54 = load i32, i32* %53, align 4
  %55 = sext i32 %54 to i64
  %56 = getelementptr inbounds i32, i32* %51, i64 %55
  %57 = load i32, i32* %56, align 4
  %58 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %25, i8* getelementptr inbounds ([332 x i8], [332 x i8]* @.str.28, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 353, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %26, i64 %30, i64 %35, i64 %40, i8* %44, i32 %47, i32 %50, i32 %57)
  %59 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %60 = call i32 @fflush(%struct.__sFILE* %59)
  br label %61

; <label>:61:                                     ; preds = %24, %21, %18, %15, %3
  %62 = load i64, i64* %7, align 8
  %63 = icmp slt i64 %62, 0
  br i1 %63, label %64, label %83

; <label>:64:                                     ; preds = %61
  %65 = load i32, i32* @debug_enable, align 4
  %66 = icmp eq i32 %65, 1
  br i1 %66, label %67, label %82

; <label>:67:                                     ; preds = %64
  %68 = load i32, i32* @debug_disable_method, align 4
  %69 = icmp eq i32 %68, 0
  br i1 %69, label %70, label %82

; <label>:70:                                     ; preds = %67
  %71 = load i32, i32* @debug_disable_external, align 4
  %72 = icmp ne i32 %71, 1
  br i1 %72, label %73, label %82

; <label>:73:                                     ; preds = %70
  %74 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %75 = icmp ne %struct.__sFILE* %74, null
  br i1 %75, label %76, label %82

; <label>:76:                                     ; preds = %73
  %77 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %78 = load i64, i64* %7, align 8
  %79 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %77, i8* getelementptr inbounds ([138 x i8], [138 x i8]* @.str.30, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 355, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %78)
  %80 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %81 = call i32 @fflush(%struct.__sFILE* %80)
  br label %82

; <label>:82:                                     ; preds = %76, %73, %70, %67, %64
  store i32 -29, i32* %4, align 4
  br label %286

; <label>:83:                                     ; preds = %61
  %84 = load i32, i32* %5, align 4
  %85 = load i64, i64* %7, align 8
  %86 = call i64 @lseek(i32 %84, i64 %85, i32 0)
  %87 = call i32* @__error()
  %88 = load i32, i32* %87, align 4
  %89 = icmp ne i32 %88, 0
  br i1 %89, label %90, label %116

; <label>:90:                                     ; preds = %83
  %91 = load i32, i32* @debug_enable, align 4
  %92 = icmp eq i32 %91, 1
  br i1 %92, label %93, label %110

; <label>:93:                                     ; preds = %90
  %94 = load i32, i32* @debug_disable_method, align 4
  %95 = icmp eq i32 %94, 0
  br i1 %95, label %96, label %110

; <label>:96:                                     ; preds = %93
  %97 = load i32, i32* @debug_disable_external, align 4
  %98 = icmp ne i32 %97, 1
  br i1 %98, label %99, label %110

; <label>:99:                                     ; preds = %96
  %100 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %101 = icmp ne %struct.__sFILE* %100, null
  br i1 %101, label %102, label %110

; <label>:102:                                    ; preds = %99
  %103 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %104 = call i32* @__error()
  %105 = load i32, i32* %104, align 4
  %106 = call i8* @"\01_strerror"(i32 %105)
  %107 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %103, i8* getelementptr inbounds ([148 x i8], [148 x i8]* @.str.31, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 357, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %106)
  %108 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %109 = call i32 @fflush(%struct.__sFILE* %108)
  br label %110

; <label>:110:                                    ; preds = %102, %99, %96, %93, %90
  call void @indent(i32 -1)
  %111 = call i32* @__error()
  %112 = load i32, i32* %111, align 4
  store i32 %112, i32* %8, align 4
  %113 = call i32* @__error()
  store i32 0, i32* %113, align 4
  %114 = load i32, i32* %8, align 4
  %115 = sub nsw i32 0, %114
  store i32 %115, i32* %4, align 4
  br label %286

; <label>:116:                                    ; preds = %83
  %117 = load i32, i32* %5, align 4
  %118 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %119 = bitcast %struct.dir_t* %118 to i8*
  %120 = call i64 @"\01_write"(i32 %117, i8* %119, i64 64)
  %121 = call i32* @__error()
  %122 = load i32, i32* %121, align 4
  %123 = icmp ne i32 %122, 0
  br i1 %123, label %124, label %150

; <label>:124:                                    ; preds = %116
  %125 = load i32, i32* @debug_enable, align 4
  %126 = icmp eq i32 %125, 1
  br i1 %126, label %127, label %144

; <label>:127:                                    ; preds = %124
  %128 = load i32, i32* @debug_disable_method, align 4
  %129 = icmp eq i32 %128, 0
  br i1 %129, label %130, label %144

; <label>:130:                                    ; preds = %127
  %131 = load i32, i32* @debug_disable_external, align 4
  %132 = icmp ne i32 %131, 1
  br i1 %132, label %133, label %144

; <label>:133:                                    ; preds = %130
  %134 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %135 = icmp ne %struct.__sFILE* %134, null
  br i1 %135, label %136, label %144

; <label>:136:                                    ; preds = %133
  %137 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %138 = call i32* @__error()
  %139 = load i32, i32* %138, align 4
  %140 = call i8* @"\01_strerror"(i32 %139)
  %141 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %137, i8* getelementptr inbounds ([148 x i8], [148 x i8]* @.str.32, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 361, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %140)
  %142 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %143 = call i32 @fflush(%struct.__sFILE* %142)
  br label %144

; <label>:144:                                    ; preds = %136, %133, %130, %127, %124
  call void @indent(i32 -1)
  %145 = call i32* @__error()
  %146 = load i32, i32* %145, align 4
  store i32 %146, i32* %9, align 4
  %147 = call i32* @__error()
  store i32 0, i32* %147, align 4
  %148 = load i32, i32* %9, align 4
  %149 = sub nsw i32 0, %148
  store i32 %149, i32* %4, align 4
  br label %286

; <label>:150:                                    ; preds = %116
  %151 = load i64, i64* %7, align 8
  %152 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 4), align 8
  %153 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %154 = mul i32 %152, %153
  %155 = zext i32 %154 to i64
  %156 = icmp eq i64 %151, %155
  br i1 %156, label %157, label %198

; <label>:157:                                    ; preds = %150
  %158 = bitcast %struct.dir_t* %10 to i8*
  %159 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %160 = bitcast %struct.dir_t* %159 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %158, i8* align 8 %160, i64 64, i1 false)
  %161 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %10, i32 0, i32 0
  %162 = bitcast %union.fname_u* %161 to [24 x i8]*
  %163 = getelementptr inbounds [24 x i8], [24 x i8]* %162, i32 0, i32 0
  %164 = call i8* @__strncpy_chk(i8* %163, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.10, i32 0, i32 0), i64 24, i64 24) #7
  %165 = load i32, i32* %5, align 4
  %166 = bitcast %struct.dir_t* %10 to i8*
  %167 = call i64 @"\01_write"(i32 %165, i8* %166, i64 64)
  %168 = call i32* @__error()
  %169 = load i32, i32* %168, align 4
  %170 = icmp ne i32 %169, 0
  br i1 %170, label %171, label %197

; <label>:171:                                    ; preds = %157
  %172 = load i32, i32* @debug_enable, align 4
  %173 = icmp eq i32 %172, 1
  br i1 %173, label %174, label %191

; <label>:174:                                    ; preds = %171
  %175 = load i32, i32* @debug_disable_method, align 4
  %176 = icmp eq i32 %175, 0
  br i1 %176, label %177, label %191

; <label>:177:                                    ; preds = %174
  %178 = load i32, i32* @debug_disable_external, align 4
  %179 = icmp ne i32 %178, 1
  br i1 %179, label %180, label %191

; <label>:180:                                    ; preds = %177
  %181 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %182 = icmp ne %struct.__sFILE* %181, null
  br i1 %182, label %183, label %191

; <label>:183:                                    ; preds = %180
  %184 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %185 = call i32* @__error()
  %186 = load i32, i32* %185, align 4
  %187 = call i8* @"\01_strerror"(i32 %186)
  %188 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %184, i8* getelementptr inbounds ([148 x i8], [148 x i8]* @.str.32, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 370, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %187)
  %189 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %190 = call i32 @fflush(%struct.__sFILE* %189)
  br label %191

; <label>:191:                                    ; preds = %183, %180, %177, %174, %171
  call void @indent(i32 -1)
  %192 = call i32* @__error()
  %193 = load i32, i32* %192, align 4
  store i32 %193, i32* %11, align 4
  %194 = call i32* @__error()
  store i32 0, i32* %194, align 4
  %195 = load i32, i32* %11, align 4
  %196 = sub nsw i32 0, %195
  store i32 %196, i32* %4, align 4
  br label %286

; <label>:197:                                    ; preds = %157
  br label %198

; <label>:198:                                    ; preds = %197, %150
  %199 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 4), align 8
  %200 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %201 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %200, i32 0, i32 3
  %202 = load i32, i32* %201, align 4
  %203 = icmp eq i32 %199, %202
  br i1 %203, label %204, label %237

; <label>:204:                                    ; preds = %198
  %205 = load i32, i32* @debug_enable, align 4
  %206 = icmp eq i32 %205, 1
  br i1 %206, label %207, label %229

; <label>:207:                                    ; preds = %204
  %208 = load i32, i32* @debug_disable_method, align 4
  %209 = icmp eq i32 %208, 0
  br i1 %209, label %210, label %229

; <label>:210:                                    ; preds = %207
  %211 = load i32, i32* @debug_disable_external, align 4
  %212 = icmp ne i32 %211, 1
  br i1 %212, label %213, label %229

; <label>:213:                                    ; preds = %210
  %214 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %215 = icmp ne %struct.__sFILE* %214, null
  br i1 %215, label %216, label %229

; <label>:216:                                    ; preds = %213
  %217 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %218 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4, i32 2), align 8
  %219 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %220 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %219, i32 0, i32 2
  %221 = load i32, i32* %220, align 8
  %222 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %223 = icmp eq %struct.dir_t* %222, getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4)
  %224 = zext i1 %223 to i64
  %225 = select i1 %223, i32 61, i32 33
  %226 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %217, i8* getelementptr inbounds ([166 x i8], [166 x i8]* @.str.33, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 375, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %218, i32 %221, i32 %225)
  %227 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %228 = call i32 @fflush(%struct.__sFILE* %227)
  br label %229

; <label>:229:                                    ; preds = %216, %213, %210, %207, %204
  %230 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %231 = icmp ne %struct.dir_t* %230, getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4)
  br i1 %231, label %232, label %236

; <label>:232:                                    ; preds = %229
  %233 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %234 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %233, i32 0, i32 2
  %235 = load i32, i32* %234, align 8
  store i32 %235, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4, i32 2), align 8
  br label %236

; <label>:236:                                    ; preds = %232, %229
  br label %237

; <label>:237:                                    ; preds = %236, %198
  %238 = load i64, i64* %7, align 8
  %239 = call %struct.pathc_t* @pathc_find_offset(i64 %238)
  store %struct.pathc_t* %239, %struct.pathc_t** %12, align 8
  %240 = load %struct.pathc_t*, %struct.pathc_t** %12, align 8
  %241 = icmp ne %struct.pathc_t* %240, null
  br i1 %241, label %242, label %285

; <label>:242:                                    ; preds = %237
  %243 = load %struct.pathc_t*, %struct.pathc_t** %12, align 8
  %244 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %243, i32 0, i32 2
  %245 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %244, i32 0, i32 2
  %246 = load i32, i32* %245, align 8
  %247 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %248 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %247, i32 0, i32 2
  %249 = load i32, i32* %248, align 8
  %250 = icmp ne i32 %246, %249
  br i1 %250, label %251, label %285

; <label>:251:                                    ; preds = %242
  %252 = load i32, i32* @debug_enable, align 4
  %253 = icmp eq i32 %252, 1
  br i1 %253, label %254, label %278

; <label>:254:                                    ; preds = %251
  %255 = load i32, i32* @debug_disable_method, align 4
  %256 = icmp eq i32 %255, 0
  br i1 %256, label %257, label %278

; <label>:257:                                    ; preds = %254
  %258 = load i32, i32* @debug_disable_external, align 4
  %259 = icmp ne i32 %258, 1
  br i1 %259, label %260, label %278

; <label>:260:                                    ; preds = %257
  %261 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %262 = icmp ne %struct.__sFILE* %261, null
  br i1 %262, label %263, label %278

; <label>:263:                                    ; preds = %260
  %264 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %265 = load %struct.pathc_t*, %struct.pathc_t** %12, align 8
  %266 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %265, i32 0, i32 1
  %267 = getelementptr inbounds [1025 x i8], [1025 x i8]* %266, i32 0, i32 0
  %268 = load %struct.pathc_t*, %struct.pathc_t** %12, align 8
  %269 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %268, i32 0, i32 2
  %270 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %269, i32 0, i32 2
  %271 = load i32, i32* %270, align 8
  %272 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %273 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %272, i32 0, i32 2
  %274 = load i32, i32* %273, align 8
  %275 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %264, i8* getelementptr inbounds ([204 x i8], [204 x i8]* @.str.34, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 387, i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.29, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %267, i32 %271, i32 %274)
  %276 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %277 = call i32 @fflush(%struct.__sFILE* %276)
  br label %278

; <label>:278:                                    ; preds = %263, %260, %257, %254, %251
  %279 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %280 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %279, i32 0, i32 2
  %281 = load i32, i32* %280, align 8
  %282 = load %struct.pathc_t*, %struct.pathc_t** %12, align 8
  %283 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %282, i32 0, i32 2
  %284 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %283, i32 0, i32 2
  store i32 %281, i32* %284, align 8
  br label %285

; <label>:285:                                    ; preds = %278, %242, %237
  call void @indent(i32 -1)
  store i32 0, i32* %4, align 4
  br label %286

; <label>:286:                                    ; preds = %285, %191, %144, %110, %82
  %287 = load i32, i32* %4, align 4
  ret i32 %287
}

declare i32 @pathc_up(%struct.pathc_t*) #1

declare i32 @pathc_alive_up(...) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define %struct.dir_t* @fat_get_root(i32, i64*) #0 {
  %3 = alloca %struct.dir_t*, align 8
  %4 = alloca i32, align 4
  %5 = alloca i64*, align 8
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  store i32 %0, i32* %4, align 4
  store i64* %1, i64** %5, align 8
  call void @indent(i32 1)
  %9 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4, i32 3), align 4
  %10 = icmp ne i32 %9, -1
  br i1 %10, label %11, label %12

; <label>:11:                                     ; preds = %2
  call void @indent(i32 -1)
  store %struct.dir_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4), %struct.dir_t** %3, align 8
  br label %153

; <label>:12:                                     ; preds = %2
  %13 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 4), align 8
  %14 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %15 = mul i32 %13, %14
  store i32 %15, i32* %6, align 4
  %16 = load i32, i32* %6, align 4
  %17 = icmp slt i32 %16, 0
  br i1 %17, label %18, label %22

; <label>:18:                                     ; preds = %12
  %19 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %20 = load i32, i32* %6, align 4
  %21 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %19, i8* getelementptr inbounds ([131 x i8], [131 x i8]* @.str, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 162, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %20)
  call void @quit(i32 1, i32 1)
  br label %22

; <label>:22:                                     ; preds = %18, %12
  %23 = call i32* @__error()
  %24 = load i32, i32* %23, align 4
  %25 = icmp ne i32 %24, 0
  br i1 %25, label %26, label %46

; <label>:26:                                     ; preds = %22
  %27 = load i32, i32* @debug_enable, align 4
  %28 = icmp eq i32 %27, 1
  br i1 %28, label %29, label %45

; <label>:29:                                     ; preds = %26
  %30 = load i32, i32* @debug_disable_method, align 4
  %31 = icmp eq i32 %30, 0
  br i1 %31, label %32, label %45

; <label>:32:                                     ; preds = %29
  %33 = load i32, i32* @debug_disable_external, align 4
  %34 = icmp ne i32 %33, 1
  br i1 %34, label %35, label %45

; <label>:35:                                     ; preds = %32
  %36 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %37 = icmp ne %struct.__sFILE* %36, null
  br i1 %37, label %38, label %45

; <label>:38:                                     ; preds = %35
  %39 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %40 = call i32* @__error()
  %41 = load i32, i32* %40, align 4
  %42 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %39, i8* getelementptr inbounds ([127 x i8], [127 x i8]* @.str.3, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 165, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %41)
  %43 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %44 = call i32 @fflush(%struct.__sFILE* %43)
  br label %45

; <label>:45:                                     ; preds = %38, %35, %32, %29, %26
  br label %46

; <label>:46:                                     ; preds = %45, %22
  store i32 1, i32* %7, align 4
  store i32 1, i32* %8, align 4
  br label %47

; <label>:47:                                     ; preds = %62, %46
  %48 = load i32, i32* %8, align 4
  %49 = icmp sle i32 %48, 3
  br i1 %49, label %50, label %65

; <label>:50:                                     ; preds = %47
  %51 = load i32, i32* %4, align 4
  %52 = load i32, i32* %6, align 4
  %53 = sext i32 %52 to i64
  %54 = call i64 @lseek(i32 %51, i64 %53, i32 0)
  %55 = call i32* @__error()
  %56 = load i32, i32* %55, align 4
  %57 = icmp eq i32 %56, 0
  br i1 %57, label %58, label %59

; <label>:58:                                     ; preds = %50
  br label %65

; <label>:59:                                     ; preds = %50
  %60 = call i32* @__error()
  store i32 0, i32* %60, align 4
  br label %61

; <label>:61:                                     ; preds = %59
  br label %62

; <label>:62:                                     ; preds = %61
  %63 = load i32, i32* %8, align 4
  %64 = add nsw i32 %63, 1
  store i32 %64, i32* %8, align 4
  br label %47

; <label>:65:                                     ; preds = %58, %47
  %66 = call i32* @__error()
  %67 = load i32, i32* %66, align 4
  %68 = icmp ne i32 %67, 0
  br i1 %68, label %69, label %99

; <label>:69:                                     ; preds = %65
  %70 = load i32, i32* @debug_enable, align 4
  %71 = icmp eq i32 %70, 1
  br i1 %71, label %72, label %98

; <label>:72:                                     ; preds = %69
  %73 = load i32, i32* @debug_disable_method, align 4
  %74 = icmp eq i32 %73, 0
  br i1 %74, label %75, label %98

; <label>:75:                                     ; preds = %72
  %76 = load i32, i32* @debug_disable_external, align 4
  %77 = icmp ne i32 %76, 1
  br i1 %77, label %78, label %98

; <label>:78:                                     ; preds = %75
  %79 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %80 = icmp ne %struct.__sFILE* %79, null
  br i1 %80, label %81, label %98

; <label>:81:                                     ; preds = %78
  %82 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %83 = load i32, i32* %6, align 4
  %84 = load i32, i32* %4, align 4
  %85 = load i32, i32* %7, align 4
  %86 = load i32, i32* %7, align 4
  %87 = icmp eq i32 %86, 1
  %88 = zext i1 %87 to i64
  %89 = select i1 %87, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0)
  %90 = call i32* @__error()
  %91 = load i32, i32* %90, align 4
  %92 = call i32* @__error()
  %93 = load i32, i32* %92, align 4
  %94 = call i8* @"\01_strerror"(i32 %93)
  %95 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %82, i8* getelementptr inbounds ([209 x i8], [209 x i8]* @.str.4, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 187, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %83, i32 %84, i32 %85, i8* %89, i32 %91, i8* %94)
  %96 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %97 = call i32 @fflush(%struct.__sFILE* %96)
  br label %98

; <label>:98:                                     ; preds = %81, %78, %75, %72, %69
  br label %123

; <label>:99:                                     ; preds = %65
  %100 = load i32, i32* @debug_enable, align 4
  %101 = icmp eq i32 %100, 1
  br i1 %101, label %102, label %122

; <label>:102:                                    ; preds = %99
  %103 = load i32, i32* @debug_disable_method, align 4
  %104 = icmp eq i32 %103, 0
  br i1 %104, label %105, label %122

; <label>:105:                                    ; preds = %102
  %106 = load i32, i32* @debug_disable_external, align 4
  %107 = icmp ne i32 %106, 1
  br i1 %107, label %108, label %122

; <label>:108:                                    ; preds = %105
  %109 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %110 = icmp ne %struct.__sFILE* %109, null
  br i1 %110, label %111, label %122

; <label>:111:                                    ; preds = %108
  %112 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %113 = load i32, i32* %6, align 4
  %114 = load i32, i32* %7, align 4
  %115 = load i32, i32* %7, align 4
  %116 = icmp eq i32 %115, 1
  %117 = zext i1 %116 to i64
  %118 = select i1 %116, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0)
  %119 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %112, i8* getelementptr inbounds ([156 x i8], [156 x i8]* @.str.7, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 189, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %113, i32 %114, i8* %118)
  %120 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %121 = call i32 @fflush(%struct.__sFILE* %120)
  br label %122

; <label>:122:                                    ; preds = %111, %108, %105, %102, %99
  br label %123

; <label>:123:                                    ; preds = %122, %98
  %124 = load i64*, i64** %5, align 8
  %125 = icmp ne i64* %124, null
  br i1 %125, label %126, label %130

; <label>:126:                                    ; preds = %123
  %127 = load i32, i32* %6, align 4
  %128 = sext i32 %127 to i64
  %129 = load i64*, i64** %5, align 8
  store i64 %128, i64* %129, align 8
  br label %130

; <label>:130:                                    ; preds = %126, %123
  %131 = load i32, i32* %4, align 4
  %132 = call i64 @"\01_read"(i32 %131, i8* bitcast (%struct.dir_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4) to i8*), i64 64)
  %133 = call i32* @__error()
  %134 = load i32, i32* %133, align 4
  %135 = icmp ne i32 %134, 0
  br i1 %135, label %136, label %152

; <label>:136:                                    ; preds = %130
  call void @indent(i32 -1)
  %137 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %138 = call i32* @__error()
  %139 = load i32, i32* %138, align 4
  %140 = icmp slt i32 %139, 0
  br i1 %140, label %141, label %145

; <label>:141:                                    ; preds = %136
  %142 = call i32* @__error()
  %143 = load i32, i32* %142, align 4
  %144 = sub nsw i32 0, %143
  br label %148

; <label>:145:                                    ; preds = %136
  %146 = call i32* @__error()
  %147 = load i32, i32* %146, align 4
  br label %148

; <label>:148:                                    ; preds = %145, %141
  %149 = phi i32 [ %144, %141 ], [ %147, %145 ]
  %150 = call i8* @"\01_strerror"(i32 %149)
  %151 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %137, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 195, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.2, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.9, i32 0, i32 0), i8* %150)
  call void @quit(i32 1, i32 1)
  br label %152

; <label>:152:                                    ; preds = %148, %130
  call void @indent(i32 -1)
  store %struct.dir_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4), %struct.dir_t** %3, align 8
  br label %153

; <label>:153:                                    ; preds = %152, %11
  %154 = load %struct.dir_t*, %struct.dir_t** %3, align 8
  ret %struct.dir_t* %154
}

declare i32 @fprintf(%struct.__sFILE*, i8*, ...) #1

declare void @quit(i32, i32) #1

declare i32* @__error() #1

declare i32 @fflush(%struct.__sFILE*) #1

declare i8* @"\01_strerror"(i32) #1

declare i64 @"\01_read"(i32, i8*, i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_dir_empty(i32, %struct.dir_t*) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca %struct.dir_t*, align 8
  %6 = alloca %struct.dir_t*, align 8
  %7 = alloca i64, align 8
  %8 = alloca i32, align 4
  %9 = alloca i64, align 8
  store i32 %0, i32* %4, align 4
  store %struct.dir_t* %1, %struct.dir_t** %5, align 8
  %10 = load %struct.dir_t*, %struct.dir_t** %5, align 8
  %11 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %10, i32 0, i32 4
  %12 = load i32, i32* %11, align 8
  %13 = icmp ne i32 %12, 1
  br i1 %13, label %14, label %15

; <label>:14:                                     ; preds = %2
  store i32 0, i32* %3, align 4
  br label %102

; <label>:15:                                     ; preds = %2
  %16 = load %struct.dir_t*, %struct.dir_t** %5, align 8
  %17 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %16, i32 0, i32 2
  %18 = load i32, i32* %17, align 8
  %19 = icmp eq i32 %18, 0
  br i1 %19, label %20, label %21

; <label>:20:                                     ; preds = %15
  store i32 1, i32* %3, align 4
  br label %102

; <label>:21:                                     ; preds = %15
  %22 = load i32, i32* %4, align 4
  %23 = load %struct.dir_t*, %struct.dir_t** %5, align 8
  %24 = call i32 @fat_read_dir(i32 %22, %struct.dir_t* %23, %struct.dir_t** %6, i64** null, i64* %7, i32* null)
  store i32 %24, i32* %8, align 4
  %25 = load i32, i32* %8, align 4
  %26 = icmp slt i32 %25, 0
  br i1 %26, label %27, label %31

; <label>:27:                                     ; preds = %21
  %28 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %29 = bitcast %struct.dir_t* %28 to i8*
  call void @free(i8* %29)
  %30 = load i32, i32* %8, align 4
  store i32 %30, i32* %3, align 4
  br label %102

; <label>:31:                                     ; preds = %21
  %32 = load i64, i64* %7, align 8
  %33 = icmp ule i64 %32, 1
  br i1 %33, label %34, label %37

; <label>:34:                                     ; preds = %31
  %35 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %36 = bitcast %struct.dir_t* %35 to i8*
  call void @free(i8* %36)
  store i32 1, i32* %3, align 4
  br label %102

; <label>:37:                                     ; preds = %31
  store i64 0, i64* %9, align 8
  br label %38

; <label>:38:                                     ; preds = %96, %37
  %39 = load i64, i64* %9, align 8
  %40 = load i64, i64* %7, align 8
  %41 = icmp ult i64 %39, %40
  br i1 %41, label %42, label %99

; <label>:42:                                     ; preds = %38
  %43 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %44 = load i64, i64* %9, align 8
  %45 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %43, i64 %44
  %46 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %45, i32 0, i32 4
  %47 = load i32, i32* %46, align 8
  %48 = and i32 %47, 1
  %49 = icmp eq i32 %48, 0
  br i1 %49, label %50, label %68

; <label>:50:                                     ; preds = %42
  %51 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %52 = load i64, i64* %9, align 8
  %53 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %51, i64 %52
  %54 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %53, i32 0, i32 3
  %55 = load i32, i32* %54, align 4
  %56 = icmp eq i32 %55, 0
  br i1 %56, label %68, label %57

; <label>:57:                                     ; preds = %50
  %58 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %59 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %60 = load i64, i64* %9, align 8
  %61 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %59, i64 %60
  %62 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %61, i32 0, i32 3
  %63 = load i32, i32* %62, align 4
  %64 = sext i32 %63 to i64
  %65 = getelementptr inbounds i32, i32* %58, i64 %64
  %66 = load i32, i32* %65, align 4
  %67 = icmp eq i32 %66, 0
  br i1 %67, label %68, label %92

; <label>:68:                                     ; preds = %57, %50, %42
  %69 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %70 = load i64, i64* %9, align 8
  %71 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %69, i64 %70
  %72 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %71, i32 0, i32 4
  %73 = load i32, i32* %72, align 8
  %74 = and i32 %73, 1
  %75 = icmp eq i32 %74, 1
  br i1 %75, label %76, label %95

; <label>:76:                                     ; preds = %68
  %77 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %78 = load i64, i64* %9, align 8
  %79 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %77, i64 %78
  %80 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %79, i32 0, i32 0
  %81 = bitcast %union.fname_u* %80 to [24 x i8]*
  %82 = getelementptr inbounds [24 x i8], [24 x i8]* %81, i32 0, i32 0
  %83 = call i32 @strcmp(i8* %82, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.10, i32 0, i32 0))
  %84 = icmp ne i32 %83, 0
  br i1 %84, label %85, label %95

; <label>:85:                                     ; preds = %76
  %86 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %87 = load i64, i64* %9, align 8
  %88 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %86, i64 %87
  %89 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %88, i32 0, i32 2
  %90 = load i32, i32* %89, align 8
  %91 = icmp ult i32 0, %90
  br i1 %91, label %92, label %95

; <label>:92:                                     ; preds = %85, %57
  %93 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %94 = bitcast %struct.dir_t* %93 to i8*
  call void @free(i8* %94)
  store i32 0, i32* %3, align 4
  br label %102

; <label>:95:                                     ; preds = %85, %76, %68
  br label %96

; <label>:96:                                     ; preds = %95
  %97 = load i64, i64* %9, align 8
  %98 = add i64 %97, 1
  store i64 %98, i64* %9, align 8
  br label %38

; <label>:99:                                     ; preds = %38
  %100 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %101 = bitcast %struct.dir_t* %100 to i8*
  call void @free(i8* %101)
  store i32 1, i32* %3, align 4
  br label %102

; <label>:102:                                    ; preds = %99, %92, %34, %27, %20, %14
  %103 = load i32, i32* %3, align 4
  ret i32 %103
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_read_dir(i32, %struct.dir_t*, %struct.dir_t**, i64**, i64*, i32*) #0 {
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca %struct.dir_t*, align 8
  %10 = alloca %struct.dir_t**, align 8
  %11 = alloca i64**, align 8
  %12 = alloca i64*, align 8
  %13 = alloca i32*, align 8
  %14 = alloca %struct.dir_t*, align 8
  %15 = alloca i8*, align 8
  %16 = alloca i64, align 8
  %17 = alloca i32, align 4
  %18 = alloca [25 x i8], align 16
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %21 = alloca i64, align 8
  store i32 %0, i32* %8, align 4
  store %struct.dir_t* %1, %struct.dir_t** %9, align 8
  store %struct.dir_t** %2, %struct.dir_t*** %10, align 8
  store i64** %3, i64*** %11, align 8
  store i64* %4, i64** %12, align 8
  store i32* %5, i32** %13, align 8
  %22 = load i32, i32* @debug_disable_method, align 4
  %23 = or i32 %22, 4
  store i32 %23, i32* @debug_disable_method, align 4
  call void @indent(i32 1)
  %24 = load %struct.dir_t*, %struct.dir_t** %9, align 8
  %25 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %24, i32 0, i32 2
  %26 = load i32, i32* %25, align 8
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %33, label %28

; <label>:28:                                     ; preds = %6
  %29 = load %struct.dir_t*, %struct.dir_t** %9, align 8
  %30 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %29, i32 0, i32 4
  %31 = load i32, i32* %30, align 8
  %32 = icmp ne i32 %31, 1
  br i1 %32, label %33, label %36

; <label>:33:                                     ; preds = %28, %6
  %34 = load i32, i32* @debug_disable_method, align 4
  %35 = and i32 %34, -5
  store i32 %35, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -20, i32* %7, align 4
  br label %186

; <label>:36:                                     ; preds = %28
  %37 = load %struct.dir_t*, %struct.dir_t** %9, align 8
  %38 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %37, i32 0, i32 2
  %39 = load i32, i32* %38, align 8
  %40 = zext i32 %39 to i64
  %41 = urem i64 %40, 64
  %42 = icmp ne i64 %41, 0
  br i1 %42, label %43, label %64

; <label>:43:                                     ; preds = %36
  %44 = load i32, i32* @debug_enable, align 4
  %45 = icmp eq i32 %44, 1
  br i1 %45, label %46, label %63

; <label>:46:                                     ; preds = %43
  %47 = load i32, i32* @debug_disable_method, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %49, label %63

; <label>:49:                                     ; preds = %46
  %50 = load i32, i32* @debug_disable_external, align 4
  %51 = icmp ne i32 %50, 1
  br i1 %51, label %52, label %63

; <label>:52:                                     ; preds = %49
  %53 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %54 = icmp ne %struct.__sFILE* %53, null
  br i1 %54, label %55, label %63

; <label>:55:                                     ; preds = %52
  %56 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %57 = load %struct.dir_t*, %struct.dir_t** %9, align 8
  %58 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %57, i32 0, i32 2
  %59 = load i32, i32* %58, align 8
  %60 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %56, i8* getelementptr inbounds ([182 x i8], [182 x i8]* @.str.72, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 593, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.73, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %59, i64 64)
  %61 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %62 = call i32 @fflush(%struct.__sFILE* %61)
  br label %63

; <label>:63:                                     ; preds = %55, %52, %49, %46, %43
  br label %64

; <label>:64:                                     ; preds = %63, %36
  %65 = load %struct.dir_t*, %struct.dir_t** %9, align 8
  %66 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %65, i32 0, i32 2
  %67 = load i32, i32* %66, align 8
  %68 = udiv i32 %67, 64
  %69 = zext i32 %68 to i64
  %70 = load i64*, i64** %12, align 8
  store i64 %69, i64* %70, align 8
  %71 = load i64*, i64** %12, align 8
  %72 = load i64, i64* %71, align 8
  %73 = call i8* @calloc(i64 %72, i64 64) #8
  %74 = bitcast i8* %73 to %struct.dir_t*
  store %struct.dir_t* %74, %struct.dir_t** %14, align 8
  %75 = load i64**, i64*** %11, align 8
  %76 = icmp ne i64** %75, null
  br i1 %76, label %77, label %83

; <label>:77:                                     ; preds = %64
  %78 = load i64*, i64** %12, align 8
  %79 = load i64, i64* %78, align 8
  %80 = call i8* @calloc(i64 %79, i64 8) #8
  %81 = bitcast i8* %80 to i64*
  %82 = load i64**, i64*** %11, align 8
  store i64* %81, i64** %82, align 8
  br label %83

; <label>:83:                                     ; preds = %77, %64
  %84 = load i32, i32* %8, align 4
  %85 = load %struct.dir_t*, %struct.dir_t** %9, align 8
  %86 = call i32 @fat_read_file(i32 %84, %struct.dir_t* %85, i8** %15, i64* %16)
  store i32 %86, i32* %17, align 4
  %87 = load i32, i32* %17, align 4
  %88 = icmp slt i32 %87, 0
  br i1 %88, label %89, label %94

; <label>:89:                                     ; preds = %83
  %90 = load i8*, i8** %15, align 8
  call void @free(i8* %90)
  %91 = load i32, i32* @debug_disable_method, align 4
  %92 = and i32 %91, -5
  store i32 %92, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  %93 = load i32, i32* %17, align 4
  store i32 %93, i32* %7, align 4
  br label %186

; <label>:94:                                     ; preds = %83
  %95 = getelementptr inbounds [25 x i8], [25 x i8]* %18, i32 0, i32 0
  %96 = load i8*, i8** %15, align 8
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 16 %95, i8* align 1 %96, i64 24, i1 false)
  %97 = getelementptr inbounds [25 x i8], [25 x i8]* %18, i32 0, i32 0
  %98 = call i32 @strcmp(i8* %97, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.74, i32 0, i32 0))
  %99 = icmp eq i32 %98, 0
  br i1 %99, label %100, label %106

; <label>:100:                                    ; preds = %94
  %101 = load i32*, i32** %13, align 8
  %102 = icmp ne i32* %101, null
  br i1 %102, label %103, label %105

; <label>:103:                                    ; preds = %100
  %104 = load i32*, i32** %13, align 8
  store i32 2, i32* %104, align 4
  br label %105

; <label>:105:                                    ; preds = %103, %100
  br label %117

; <label>:106:                                    ; preds = %94
  %107 = getelementptr inbounds [25 x i8], [25 x i8]* %18, i32 0, i32 0
  %108 = call i32 @strcmp(i8* %107, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.10, i32 0, i32 0))
  %109 = icmp eq i32 %108, 0
  br i1 %109, label %110, label %116

; <label>:110:                                    ; preds = %106
  %111 = load i32*, i32** %13, align 8
  %112 = icmp ne i32* %111, null
  br i1 %112, label %113, label %115

; <label>:113:                                    ; preds = %110
  %114 = load i32*, i32** %13, align 8
  store i32 1, i32* %114, align 4
  br label %115

; <label>:115:                                    ; preds = %113, %110
  br label %116

; <label>:116:                                    ; preds = %115, %106
  br label %117

; <label>:117:                                    ; preds = %116, %105
  %118 = load %struct.dir_t*, %struct.dir_t** %9, align 8
  %119 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %118, i32 0, i32 3
  %120 = load i32, i32* %119, align 4
  store i32 %120, i32* %19, align 4
  store i64 0, i64* %21, align 8
  br label %121

; <label>:121:                                    ; preds = %177, %117
  %122 = load i64, i64* %21, align 8
  %123 = load i64*, i64** %12, align 8
  %124 = load i64, i64* %123, align 8
  %125 = icmp ult i64 %122, %124
  br i1 %125, label %126, label %180

; <label>:126:                                    ; preds = %121
  %127 = load %struct.dir_t*, %struct.dir_t** %14, align 8
  %128 = load i64, i64* %21, align 8
  %129 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %127, i64 %128
  %130 = bitcast %struct.dir_t* %129 to i8*
  %131 = load i8*, i8** %15, align 8
  %132 = load i64, i64* %21, align 8
  %133 = mul i64 64, %132
  %134 = getelementptr inbounds i8, i8* %131, i64 %133
  %135 = load %struct.dir_t*, %struct.dir_t** %14, align 8
  %136 = load i64, i64* %21, align 8
  %137 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %135, i64 %136
  %138 = bitcast %struct.dir_t* %137 to i8*
  %139 = call i64 @llvm.objectsize.i64.p0i8(i8* %138, i1 false, i1 true)
  %140 = call i8* @__memcpy_chk(i8* %130, i8* %134, i64 64, i64 %139) #7
  %141 = load i64, i64* %21, align 8
  %142 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %143 = zext i32 %142 to i64
  %144 = udiv i64 %143, 64
  %145 = urem i64 %141, %144
  %146 = trunc i64 %145 to i32
  store i32 %146, i32* %20, align 4
  %147 = load i64**, i64*** %11, align 8
  %148 = icmp ne i64** %147, null
  br i1 %148, label %149, label %162

; <label>:149:                                    ; preds = %126
  %150 = load i32, i32* %19, align 4
  %151 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %152 = mul i32 %150, %151
  %153 = zext i32 %152 to i64
  %154 = load i32, i32* %20, align 4
  %155 = sext i32 %154 to i64
  %156 = mul i64 %155, 64
  %157 = add i64 %153, %156
  %158 = load i64**, i64*** %11, align 8
  %159 = load i64*, i64** %158, align 8
  %160 = load i64, i64* %21, align 8
  %161 = getelementptr inbounds i64, i64* %159, i64 %160
  store i64 %157, i64* %161, align 8
  br label %162

; <label>:162:                                    ; preds = %149, %126
  %163 = load i32, i32* %20, align 4
  %164 = sext i32 %163 to i64
  %165 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %166 = zext i32 %165 to i64
  %167 = udiv i64 %166, 64
  %168 = sub i64 %167, 1
  %169 = icmp eq i64 %164, %168
  br i1 %169, label %170, label %176

; <label>:170:                                    ; preds = %162
  %171 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %172 = load i32, i32* %19, align 4
  %173 = sext i32 %172 to i64
  %174 = getelementptr inbounds i32, i32* %171, i64 %173
  %175 = load i32, i32* %174, align 4
  store i32 %175, i32* %19, align 4
  br label %176

; <label>:176:                                    ; preds = %170, %162
  br label %177

; <label>:177:                                    ; preds = %176
  %178 = load i64, i64* %21, align 8
  %179 = add i64 %178, 1
  store i64 %179, i64* %21, align 8
  br label %121

; <label>:180:                                    ; preds = %121
  %181 = load i8*, i8** %15, align 8
  call void @free(i8* %181)
  %182 = load %struct.dir_t*, %struct.dir_t** %14, align 8
  %183 = load %struct.dir_t**, %struct.dir_t*** %10, align 8
  store %struct.dir_t* %182, %struct.dir_t** %183, align 8
  %184 = load i32, i32* @debug_disable_method, align 4
  %185 = and i32 %184, -5
  store i32 %185, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 0, i32* %7, align 4
  br label %186

; <label>:186:                                    ; preds = %180, %89, %33
  %187 = load i32, i32* %7, align 4
  ret i32 %187
}

declare void @free(i8*) #1

declare i32 @strcmp(i8*, i8*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_read_file(i32, %struct.dir_t*, i8**, i64*) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca %struct.dir_t*, align 8
  %8 = alloca i8**, align 8
  %9 = alloca i64*, align 8
  %10 = alloca i32, align 4
  %11 = alloca i8*, align 8
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  store i32 %0, i32* %6, align 4
  store %struct.dir_t* %1, %struct.dir_t** %7, align 8
  store i8** %2, i8*** %8, align 8
  store i64* %3, i64** %9, align 8
  call void @indent(i32 1)
  %17 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %18 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %17, i32 0, i32 2
  %19 = load i32, i32* %18, align 8
  %20 = icmp eq i32 %19, 0
  br i1 %20, label %21, label %27

; <label>:21:                                     ; preds = %4
  %22 = load i64*, i64** %9, align 8
  %23 = icmp ne i64* %22, null
  br i1 %23, label %24, label %26

; <label>:24:                                     ; preds = %21
  %25 = load i64*, i64** %9, align 8
  store i64 0, i64* %25, align 8
  br label %26

; <label>:26:                                     ; preds = %24, %21
  call void @indent(i32 -1)
  store i32 0, i32* %5, align 4
  br label %408

; <label>:27:                                     ; preds = %4
  %28 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  store i32 %28, i32* %10, align 4
  %29 = load i64*, i64** %9, align 8
  %30 = icmp ne i64* %29, null
  br i1 %30, label %31, label %37

; <label>:31:                                     ; preds = %27
  %32 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %33 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %32, i32 0, i32 2
  %34 = load i32, i32* %33, align 8
  %35 = zext i32 %34 to i64
  %36 = load i64*, i64** %9, align 8
  store i64 %35, i64* %36, align 8
  br label %37

; <label>:37:                                     ; preds = %31, %27
  %38 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %39 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %38, i32 0, i32 2
  %40 = load i32, i32* %39, align 8
  %41 = zext i32 %40 to i64
  %42 = call i8* @calloc(i64 %41, i64 1) #8
  %43 = load i8**, i8*** %8, align 8
  store i8* %42, i8** %43, align 8
  %44 = load i8**, i8*** %8, align 8
  %45 = load i8*, i8** %44, align 8
  store i8* %45, i8** %11, align 8
  %46 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %47 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %46, i32 0, i32 2
  %48 = load i32, i32* %47, align 8
  store i32 %48, i32* %12, align 4
  %49 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %50 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %49, i32 0, i32 3
  %51 = load i32, i32* %50, align 4
  store i32 %51, i32* %13, align 4
  br label %52

; <label>:52:                                     ; preds = %406, %37
  %53 = load i32, i32* %12, align 4
  %54 = icmp ult i32 0, %53
  br i1 %54, label %55, label %407

; <label>:55:                                     ; preds = %52
  %56 = load i32, i32* %12, align 4
  %57 = load i32, i32* %10, align 4
  %58 = icmp ule i32 %56, %57
  br i1 %58, label %59, label %303

; <label>:59:                                     ; preds = %55
  %60 = load i32, i32* %13, align 4
  %61 = icmp slt i32 %60, 1
  br i1 %61, label %62, label %66

; <label>:62:                                     ; preds = %59
  %63 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %64 = load i32, i32* %13, align 4
  %65 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %63, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 267, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.12, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.13, i32 0, i32 0), i32 %64)
  call void @quit(i32 1, i32 1)
  br label %66

; <label>:66:                                     ; preds = %62, %59
  %67 = load i32, i32* %6, align 4
  %68 = load i32, i32* %13, align 4
  %69 = load i32, i32* %10, align 4
  %70 = mul i32 %68, %69
  %71 = zext i32 %70 to i64
  %72 = call i64 @lseek(i32 %67, i64 %71, i32 0)
  %73 = call i32* @__error()
  %74 = load i32, i32* %73, align 4
  %75 = icmp ne i32 %74, 0
  br i1 %75, label %76, label %92

; <label>:76:                                     ; preds = %66
  call void @indent(i32 -1)
  %77 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %78 = call i32* @__error()
  %79 = load i32, i32* %78, align 4
  %80 = icmp slt i32 %79, 0
  br i1 %80, label %81, label %85

; <label>:81:                                     ; preds = %76
  %82 = call i32* @__error()
  %83 = load i32, i32* %82, align 4
  %84 = sub nsw i32 0, %83
  br label %88

; <label>:85:                                     ; preds = %76
  %86 = call i32* @__error()
  %87 = load i32, i32* %86, align 4
  br label %88

; <label>:88:                                     ; preds = %85, %81
  %89 = phi i32 [ %84, %81 ], [ %87, %85 ]
  %90 = call i8* @"\01_strerror"(i32 %89)
  %91 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %77, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 269, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %90)
  call void @quit(i32 1, i32 1)
  br label %92

; <label>:92:                                     ; preds = %88, %66
  %93 = load i32, i32* %6, align 4
  %94 = load i8*, i8** %11, align 8
  %95 = load i32, i32* %12, align 4
  %96 = zext i32 %95 to i64
  %97 = call i64 @"\01_read"(i32 %93, i8* %94, i64 %96)
  %98 = call i32* @__error()
  %99 = load i32, i32* %98, align 4
  %100 = icmp ne i32 %99, 0
  br i1 %100, label %101, label %117

; <label>:101:                                    ; preds = %92
  call void @indent(i32 -1)
  %102 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %103 = call i32* @__error()
  %104 = load i32, i32* %103, align 4
  %105 = icmp slt i32 %104, 0
  br i1 %105, label %106, label %110

; <label>:106:                                    ; preds = %101
  %107 = call i32* @__error()
  %108 = load i32, i32* %107, align 4
  %109 = sub nsw i32 0, %108
  br label %113

; <label>:110:                                    ; preds = %101
  %111 = call i32* @__error()
  %112 = load i32, i32* %111, align 4
  br label %113

; <label>:113:                                    ; preds = %110, %106
  %114 = phi i32 [ %109, %106 ], [ %112, %110 ]
  %115 = call i8* @"\01_strerror"(i32 %114)
  %116 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %102, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 271, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.9, i32 0, i32 0), i8* %115)
  call void @quit(i32 1, i32 1)
  br label %117

; <label>:117:                                    ; preds = %113, %92
  %118 = load i32, i32* %12, align 4
  %119 = load i8*, i8** %11, align 8
  %120 = zext i32 %118 to i64
  %121 = getelementptr inbounds i8, i8* %119, i64 %120
  store i8* %121, i8** %11, align 8
  store i32 0, i32* %12, align 4
  %122 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %123 = load i32, i32* %13, align 4
  %124 = sext i32 %123 to i64
  %125 = getelementptr inbounds i32, i32* %122, i64 %124
  %126 = load i32, i32* %125, align 4
  %127 = icmp ne i32 %126, -2
  br i1 %127, label %128, label %302

; <label>:128:                                    ; preds = %117
  store i32 1, i32* %14, align 4
  %129 = load i32, i32* %14, align 4
  %130 = icmp ne i32 %129, 0
  br i1 %130, label %131, label %137

; <label>:131:                                    ; preds = %128
  %132 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %133 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %132, i32 0, i32 4
  %134 = load i32, i32* %133, align 8
  %135 = and i32 %134, 1
  %136 = icmp eq i32 %135, 1
  br i1 %136, label %191, label %137

; <label>:137:                                    ; preds = %131, %128
  %138 = load i32, i32* @debug_enable, align 4
  %139 = icmp eq i32 %138, 1
  br i1 %139, label %140, label %165

; <label>:140:                                    ; preds = %137
  %141 = load i32, i32* @debug_disable_method, align 4
  %142 = icmp eq i32 %141, 0
  br i1 %142, label %143, label %165

; <label>:143:                                    ; preds = %140
  %144 = load i32, i32* @debug_disable_external, align 4
  %145 = icmp ne i32 %144, 1
  br i1 %145, label %146, label %165

; <label>:146:                                    ; preds = %143
  %147 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %148 = icmp ne %struct.__sFILE* %147, null
  br i1 %148, label %149, label %165

; <label>:149:                                    ; preds = %146
  %150 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %151 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %152 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %151, i32 0, i32 4
  %153 = load i32, i32* %152, align 8
  %154 = and i32 %153, 1
  %155 = icmp eq i32 %154, 0
  %156 = zext i1 %155 to i64
  %157 = select i1 %155, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.18, i32 0, i32 0)
  %158 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %159 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %158, i32 0, i32 0
  %160 = bitcast %union.fname_u* %159 to [24 x i8]*
  %161 = getelementptr inbounds [24 x i8], [24 x i8]* %160, i32 0, i32 0
  %162 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %150, i8* getelementptr inbounds ([210 x i8], [210 x i8]* @.str.16, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 285, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %157, i8* %161)
  %163 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %164 = call i32 @fflush(%struct.__sFILE* %163)
  br label %165

; <label>:165:                                    ; preds = %149, %146, %143, %140, %137
  %166 = load i32, i32* @debug_enable, align 4
  %167 = icmp eq i32 %166, 1
  br i1 %167, label %168, label %190

; <label>:168:                                    ; preds = %165
  %169 = load i32, i32* @debug_disable_method, align 4
  %170 = icmp eq i32 %169, 0
  br i1 %170, label %171, label %190

; <label>:171:                                    ; preds = %168
  %172 = load i32, i32* @debug_disable_external, align 4
  %173 = icmp ne i32 %172, 1
  br i1 %173, label %174, label %190

; <label>:174:                                    ; preds = %171
  %175 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %176 = icmp ne %struct.__sFILE* %175, null
  br i1 %176, label %177, label %190

; <label>:177:                                    ; preds = %174
  %178 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %179 = load i32, i32* %12, align 4
  %180 = load i32, i32* %13, align 4
  %181 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %182 = load i32, i32* %13, align 4
  %183 = sext i32 %182 to i64
  %184 = getelementptr inbounds i32, i32* %181, i64 %183
  %185 = load i32, i32* %184, align 4
  %186 = load i32, i32* %10, align 4
  %187 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %178, i8* getelementptr inbounds ([220 x i8], [220 x i8]* @.str.19, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 287, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %179, i32 %180, i32 %185, i32 %186)
  %188 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %189 = call i32 @fflush(%struct.__sFILE* %188)
  br label %190

; <label>:190:                                    ; preds = %177, %174, %171, %168, %165
  br label %301

; <label>:191:                                    ; preds = %131
  %192 = load i32, i32* @debug_enable, align 4
  %193 = icmp eq i32 %192, 1
  br i1 %193, label %194, label %219

; <label>:194:                                    ; preds = %191
  %195 = load i32, i32* @debug_disable_method, align 4
  %196 = icmp eq i32 %195, 0
  br i1 %196, label %197, label %219

; <label>:197:                                    ; preds = %194
  %198 = load i32, i32* @debug_disable_external, align 4
  %199 = icmp ne i32 %198, 1
  br i1 %199, label %200, label %219

; <label>:200:                                    ; preds = %197
  %201 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %202 = icmp ne %struct.__sFILE* %201, null
  br i1 %202, label %203, label %219

; <label>:203:                                    ; preds = %200
  %204 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %205 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %206 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %205, i32 0, i32 4
  %207 = load i32, i32* %206, align 8
  %208 = and i32 %207, 1
  %209 = icmp eq i32 %208, 0
  %210 = zext i1 %209 to i64
  %211 = select i1 %209, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.18, i32 0, i32 0)
  %212 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %213 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %212, i32 0, i32 0
  %214 = bitcast %union.fname_u* %213 to [24 x i8]*
  %215 = getelementptr inbounds [24 x i8], [24 x i8]* %214, i32 0, i32 0
  %216 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %204, i8* getelementptr inbounds ([155 x i8], [155 x i8]* @.str.20, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 290, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %211, i8* %215)
  %217 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %218 = call i32 @fflush(%struct.__sFILE* %217)
  br label %219

; <label>:219:                                    ; preds = %203, %200, %197, %194, %191
  %220 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %221 = load i32, i32* %13, align 4
  %222 = sext i32 %221 to i64
  %223 = getelementptr inbounds i32, i32* %220, i64 %222
  %224 = load i32, i32* %223, align 4
  store i32 %224, i32* %15, align 4
  %225 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %226 = load i32, i32* %13, align 4
  %227 = sext i32 %226 to i64
  %228 = getelementptr inbounds i32, i32* %225, i64 %227
  store i32 -2, i32* %228, align 4
  %229 = load i32, i32* @debug_enable, align 4
  %230 = icmp eq i32 %229, 1
  br i1 %230, label %231, label %246

; <label>:231:                                    ; preds = %219
  %232 = load i32, i32* @debug_disable_method, align 4
  %233 = icmp eq i32 %232, 0
  br i1 %233, label %234, label %246

; <label>:234:                                    ; preds = %231
  %235 = load i32, i32* @debug_disable_external, align 4
  %236 = icmp ne i32 %235, 1
  br i1 %236, label %237, label %246

; <label>:237:                                    ; preds = %234
  %238 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %239 = icmp ne %struct.__sFILE* %238, null
  br i1 %239, label %240, label %246

; <label>:240:                                    ; preds = %237
  %241 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %242 = load i32, i32* %13, align 4
  %243 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %241, i8* getelementptr inbounds ([115 x i8], [115 x i8]* @.str.21, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 293, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %242)
  %244 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %245 = call i32 @fflush(%struct.__sFILE* %244)
  br label %246

; <label>:246:                                    ; preds = %240, %237, %234, %231, %219
  %247 = load i32, i32* %15, align 4
  store i32 %247, i32* %16, align 4
  br label %248

; <label>:248:                                    ; preds = %292, %246
  %249 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %250 = load i32, i32* %16, align 4
  %251 = sext i32 %250 to i64
  %252 = getelementptr inbounds i32, i32* %249, i64 %251
  %253 = load i32, i32* %252, align 4
  store i32 %253, i32* %15, align 4
  %254 = load i32, i32* %15, align 4
  %255 = icmp eq i32 %254, -2
  br i1 %255, label %256, label %257

; <label>:256:                                    ; preds = %248
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 298, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.22, i32 0, i32 0))
  br label %300

; <label>:257:                                    ; preds = %248
  %258 = load i32, i32* %15, align 4
  %259 = icmp eq i32 %258, 0
  br i1 %259, label %260, label %261

; <label>:260:                                    ; preds = %257
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 301, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.23, i32 0, i32 0))
  br label %300

; <label>:261:                                    ; preds = %257
  %262 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 2), align 8
  %263 = load i32, i32* %15, align 4
  %264 = icmp sle i32 %262, %263
  br i1 %264, label %265, label %290

; <label>:265:                                    ; preds = %261
  %266 = load i32, i32* @debug_enable, align 4
  %267 = icmp eq i32 %266, 1
  br i1 %267, label %268, label %289

; <label>:268:                                    ; preds = %265
  %269 = load i32, i32* @debug_disable_method, align 4
  %270 = icmp eq i32 %269, 0
  br i1 %270, label %271, label %289

; <label>:271:                                    ; preds = %268
  %272 = load i32, i32* @debug_disable_external, align 4
  %273 = icmp ne i32 %272, 1
  br i1 %273, label %274, label %289

; <label>:274:                                    ; preds = %271
  %275 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %276 = icmp ne %struct.__sFILE* %275, null
  br i1 %276, label %277, label %289

; <label>:277:                                    ; preds = %274
  %278 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %279 = load i32, i32* %16, align 4
  %280 = load i32, i32* %15, align 4
  %281 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 2), align 8
  %282 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 2), align 8
  %283 = icmp eq i32 %282, 1
  %284 = zext i1 %283 to i64
  %285 = select i1 %283, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.26, i32 0, i32 0)
  %286 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %278, i8* getelementptr inbounds ([177 x i8], [177 x i8]* @.str.24, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 305, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %279, i32 %280, i32 %281, i8* %285)
  %287 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %288 = call i32 @fflush(%struct.__sFILE* %287)
  br label %289

; <label>:289:                                    ; preds = %277, %274, %271, %268, %265
  br label %300

; <label>:290:                                    ; preds = %261
  br label %291

; <label>:291:                                    ; preds = %290
  br label %292

; <label>:292:                                    ; preds = %291
  %293 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %294 = load i32, i32* %16, align 4
  %295 = sext i32 %294 to i64
  %296 = getelementptr inbounds i32, i32* %293, i64 %295
  store i32 0, i32* %296, align 4
  %297 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %298 = add nsw i64 %297, 1
  store i64 %298, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %299 = load i32, i32* %15, align 4
  store i32 %299, i32* %16, align 4
  br label %248

; <label>:300:                                    ; preds = %289, %260, %256
  br label %301

; <label>:301:                                    ; preds = %300, %190
  br label %302

; <label>:302:                                    ; preds = %301, %117
  br label %406

; <label>:303:                                    ; preds = %55
  %304 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %305 = load i32, i32* %13, align 4
  %306 = sext i32 %305 to i64
  %307 = getelementptr inbounds i32, i32* %304, i64 %306
  %308 = load i32, i32* %307, align 4
  %309 = icmp eq i32 %308, -2
  br i1 %309, label %310, label %334

; <label>:310:                                    ; preds = %303
  %311 = load i32, i32* @debug_enable, align 4
  %312 = icmp eq i32 %311, 1
  br i1 %312, label %313, label %333

; <label>:313:                                    ; preds = %310
  %314 = load i32, i32* @debug_disable_method, align 4
  %315 = icmp eq i32 %314, 0
  br i1 %315, label %316, label %333

; <label>:316:                                    ; preds = %313
  %317 = load i32, i32* @debug_disable_external, align 4
  %318 = icmp ne i32 %317, 1
  br i1 %318, label %319, label %333

; <label>:319:                                    ; preds = %316
  %320 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %321 = icmp ne %struct.__sFILE* %320, null
  br i1 %321, label %322, label %333

; <label>:322:                                    ; preds = %319
  %323 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %324 = load i32, i32* %12, align 4
  %325 = load i32, i32* %12, align 4
  %326 = icmp eq i32 %325, 1
  %327 = zext i1 %326 to i64
  %328 = select i1 %326, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.26, i32 0, i32 0)
  %329 = load i32, i32* %13, align 4
  %330 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %323, i8* getelementptr inbounds ([223 x i8], [223 x i8]* @.str.27, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 320, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %324, i8* %328, i32 %329)
  %331 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %332 = call i32 @fflush(%struct.__sFILE* %331)
  br label %333

; <label>:333:                                    ; preds = %322, %319, %316, %313, %310
  call void @indent(i32 -1)
  store i32 -22, i32* %5, align 4
  br label %408

; <label>:334:                                    ; preds = %303
  %335 = load i32, i32* %13, align 4
  %336 = icmp slt i32 %335, 1
  br i1 %336, label %337, label %341

; <label>:337:                                    ; preds = %334
  %338 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %339 = load i32, i32* %13, align 4
  %340 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %338, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 324, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.13, i32 0, i32 0), i32 %339)
  call void @quit(i32 1, i32 1)
  br label %341

; <label>:341:                                    ; preds = %337, %334
  %342 = load i32, i32* %6, align 4
  %343 = load i32, i32* %13, align 4
  %344 = load i32, i32* %10, align 4
  %345 = mul i32 %343, %344
  %346 = zext i32 %345 to i64
  %347 = call i64 @lseek(i32 %342, i64 %346, i32 0)
  %348 = call i32* @__error()
  %349 = load i32, i32* %348, align 4
  %350 = icmp ne i32 %349, 0
  br i1 %350, label %351, label %367

; <label>:351:                                    ; preds = %341
  call void @indent(i32 -1)
  %352 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %353 = call i32* @__error()
  %354 = load i32, i32* %353, align 4
  %355 = icmp slt i32 %354, 0
  br i1 %355, label %356, label %360

; <label>:356:                                    ; preds = %351
  %357 = call i32* @__error()
  %358 = load i32, i32* %357, align 4
  %359 = sub nsw i32 0, %358
  br label %363

; <label>:360:                                    ; preds = %351
  %361 = call i32* @__error()
  %362 = load i32, i32* %361, align 4
  br label %363

; <label>:363:                                    ; preds = %360, %356
  %364 = phi i32 [ %359, %356 ], [ %362, %360 ]
  %365 = call i8* @"\01_strerror"(i32 %364)
  %366 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %352, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 326, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %365)
  call void @quit(i32 1, i32 1)
  br label %367

; <label>:367:                                    ; preds = %363, %341
  %368 = load i32, i32* %6, align 4
  %369 = load i8*, i8** %11, align 8
  %370 = load i32, i32* %10, align 4
  %371 = zext i32 %370 to i64
  %372 = call i64 @"\01_read"(i32 %368, i8* %369, i64 %371)
  %373 = call i32* @__error()
  %374 = load i32, i32* %373, align 4
  %375 = icmp ne i32 %374, 0
  br i1 %375, label %376, label %392

; <label>:376:                                    ; preds = %367
  call void @indent(i32 -1)
  %377 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %378 = call i32* @__error()
  %379 = load i32, i32* %378, align 4
  %380 = icmp slt i32 %379, 0
  br i1 %380, label %381, label %385

; <label>:381:                                    ; preds = %376
  %382 = call i32* @__error()
  %383 = load i32, i32* %382, align 4
  %384 = sub nsw i32 0, %383
  br label %388

; <label>:385:                                    ; preds = %376
  %386 = call i32* @__error()
  %387 = load i32, i32* %386, align 4
  br label %388

; <label>:388:                                    ; preds = %385, %381
  %389 = phi i32 [ %384, %381 ], [ %387, %385 ]
  %390 = call i8* @"\01_strerror"(i32 %389)
  %391 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %377, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 328, i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.14, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.9, i32 0, i32 0), i8* %390)
  call void @quit(i32 1, i32 1)
  br label %392

; <label>:392:                                    ; preds = %388, %367
  %393 = load i32, i32* %10, align 4
  %394 = load i8*, i8** %11, align 8
  %395 = zext i32 %393 to i64
  %396 = getelementptr inbounds i8, i8* %394, i64 %395
  store i8* %396, i8** %11, align 8
  %397 = load i32, i32* %10, align 4
  %398 = load i32, i32* %12, align 4
  %399 = sub i32 %398, %397
  store i32 %399, i32* %12, align 4
  %400 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %401 = load i32, i32* %13, align 4
  %402 = sext i32 %401 to i64
  %403 = getelementptr inbounds i32, i32* %400, i64 %402
  %404 = load i32, i32* %403, align 4
  store i32 %404, i32* %13, align 4
  br label %405

; <label>:405:                                    ; preds = %392
  br label %406

; <label>:406:                                    ; preds = %405, %302
  br label %52

; <label>:407:                                    ; preds = %52
  call void @indent(i32 -1)
  store i32 0, i32* %5, align 4
  br label %408

; <label>:408:                                    ; preds = %407, %333, %26
  %409 = load i32, i32* %5, align 4
  ret i32 %409
}

; Function Attrs: allocsize(0,1)
declare i8* @calloc(i64, i64) #5

declare void @dbg(i8*, i32, i8*, i8*) #1

declare i64 @"\01_write"(i32, i8*, i64) #1

; Function Attrs: nounwind
declare i8* @__strncpy_chk(i8*, i8*, i64, i64) #3

declare %struct.pathc_t* @pathc_find_offset(i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_zero_out_free(i32, %struct.dir_t*, i32) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca %struct.dir_t*, align 8
  %7 = alloca i32, align 4
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i8*, align 8
  %16 = alloca i32, align 4
  store i32 %0, i32* %5, align 4
  store %struct.dir_t* %1, %struct.dir_t** %6, align 8
  store i32 %2, i32* %7, align 4
  call void @indent(i32 1)
  %17 = load i32, i32* @debug_enable, align 4
  %18 = icmp eq i32 %17, 1
  br i1 %18, label %19, label %40

; <label>:19:                                     ; preds = %3
  %20 = load i32, i32* @debug_disable_method, align 4
  %21 = icmp eq i32 %20, 0
  br i1 %21, label %22, label %40

; <label>:22:                                     ; preds = %19
  %23 = load i32, i32* @debug_disable_external, align 4
  %24 = icmp ne i32 %23, 1
  br i1 %24, label %25, label %40

; <label>:25:                                     ; preds = %22
  %26 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %27 = icmp ne %struct.__sFILE* %26, null
  br i1 %27, label %28, label %40

; <label>:28:                                     ; preds = %25
  %29 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %30 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %31 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %30, i32 0, i32 3
  %32 = load i32, i32* %31, align 4
  %33 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %34 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %33, i32 0, i32 2
  %35 = load i32, i32* %34, align 8
  %36 = load i32, i32* %7, align 4
  %37 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %29, i8* getelementptr inbounds ([202 x i8], [202 x i8]* @.str.35, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 405, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %32, i32 %35, i32 %36)
  %38 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %39 = call i32 @fflush(%struct.__sFILE* %38)
  br label %40

; <label>:40:                                     ; preds = %28, %25, %22, %19, %3
  %41 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  store i32 %41, i32* %8, align 4
  %42 = load i32, i32* %7, align 4
  %43 = load i32, i32* %8, align 4
  %44 = urem i32 %42, %43
  %45 = icmp eq i32 %44, 0
  br i1 %45, label %46, label %47

; <label>:46:                                     ; preds = %40
  call void @indent(i32 -1)
  store i32 0, i32* %4, align 4
  br label %344

; <label>:47:                                     ; preds = %40
  %48 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %49 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %48, i32 0, i32 2
  %50 = load i32, i32* %49, align 8
  %51 = load i32, i32* %7, align 4
  %52 = sub i32 %50, %51
  store i32 %52, i32* %9, align 4
  %53 = load i32, i32* %9, align 4
  %54 = icmp sle i32 %53, 0
  br i1 %54, label %55, label %74

; <label>:55:                                     ; preds = %47
  %56 = load i32, i32* @debug_enable, align 4
  %57 = icmp eq i32 %56, 1
  br i1 %57, label %58, label %73

; <label>:58:                                     ; preds = %55
  %59 = load i32, i32* @debug_disable_method, align 4
  %60 = icmp eq i32 %59, 0
  br i1 %60, label %61, label %73

; <label>:61:                                     ; preds = %58
  %62 = load i32, i32* @debug_disable_external, align 4
  %63 = icmp ne i32 %62, 1
  br i1 %63, label %64, label %73

; <label>:64:                                     ; preds = %61
  %65 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %66 = icmp ne %struct.__sFILE* %65, null
  br i1 %66, label %67, label %73

; <label>:67:                                     ; preds = %64
  %68 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %69 = load i32, i32* %9, align 4
  %70 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %68, i8* getelementptr inbounds ([177 x i8], [177 x i8]* @.str.37, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 415, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %69)
  %71 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %72 = call i32 @fflush(%struct.__sFILE* %71)
  br label %73

; <label>:73:                                     ; preds = %67, %64, %61, %58, %55
  call void @indent(i32 -1)
  store i32 0, i32* %4, align 4
  br label %344

; <label>:74:                                     ; preds = %47
  %75 = load i32, i32* %7, align 4
  store i32 %75, i32* %10, align 4
  %76 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %77 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %76, i32 0, i32 3
  %78 = load i32, i32* %77, align 4
  store i32 %78, i32* %11, align 4
  %79 = load i32, i32* %11, align 4
  %80 = icmp slt i32 %79, 1
  br i1 %80, label %81, label %85

; <label>:81:                                     ; preds = %74
  %82 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %83 = load i32, i32* %11, align 4
  %84 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %82, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 422, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.13, i32 0, i32 0), i32 %83)
  call void @quit(i32 1, i32 1)
  br label %85

; <label>:85:                                     ; preds = %81, %74
  %86 = load i32, i32* %5, align 4
  %87 = load i32, i32* %11, align 4
  %88 = load i32, i32* %8, align 4
  %89 = mul i32 %87, %88
  %90 = zext i32 %89 to i64
  %91 = call i64 @lseek(i32 %86, i64 %90, i32 0)
  %92 = call i32* @__error()
  %93 = load i32, i32* %92, align 4
  %94 = icmp ne i32 %93, 0
  br i1 %94, label %95, label %133

; <label>:95:                                     ; preds = %85
  store i32 1, i32* @debug_enable, align 4
  %96 = load i32, i32* @debug_enable, align 4
  %97 = icmp eq i32 %96, 1
  br i1 %97, label %98, label %127

; <label>:98:                                     ; preds = %95
  %99 = load i32, i32* @debug_disable_method, align 4
  %100 = icmp eq i32 %99, 0
  br i1 %100, label %101, label %127

; <label>:101:                                    ; preds = %98
  %102 = load i32, i32* @debug_disable_external, align 4
  %103 = icmp ne i32 %102, 1
  br i1 %103, label %104, label %127

; <label>:104:                                    ; preds = %101
  %105 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %106 = icmp ne %struct.__sFILE* %105, null
  br i1 %106, label %107, label %127

; <label>:107:                                    ; preds = %104
  %108 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %109 = call i32* @__error()
  %110 = load i32, i32* %109, align 4
  %111 = call i32* @__error()
  %112 = load i32, i32* %111, align 4
  %113 = icmp slt i32 %112, 0
  br i1 %113, label %114, label %118

; <label>:114:                                    ; preds = %107
  %115 = call i32* @__error()
  %116 = load i32, i32* %115, align 4
  %117 = sub nsw i32 0, %116
  br label %121

; <label>:118:                                    ; preds = %107
  %119 = call i32* @__error()
  %120 = load i32, i32* %119, align 4
  br label %121

; <label>:121:                                    ; preds = %118, %114
  %122 = phi i32 [ %117, %114 ], [ %120, %118 ]
  %123 = call i8* @"\01_strerror"(i32 %122)
  %124 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %108, i8* getelementptr inbounds ([141 x i8], [141 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 424, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %110, i8* %123)
  %125 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %126 = call i32 @fflush(%struct.__sFILE* %125)
  br label %127

; <label>:127:                                    ; preds = %121, %104, %101, %98, %95
  call void @indent(i32 -1)
  %128 = call i32* @__error()
  %129 = load i32, i32* %128, align 4
  store i32 %129, i32* %12, align 4
  %130 = call i32* @__error()
  store i32 0, i32* %130, align 4
  %131 = load i32, i32* %12, align 4
  %132 = sub nsw i32 0, %131
  store i32 %132, i32* %4, align 4
  br label %344

; <label>:133:                                    ; preds = %85
  %134 = load i32, i32* @debug_enable, align 4
  %135 = icmp eq i32 %134, 1
  br i1 %135, label %136, label %152

; <label>:136:                                    ; preds = %133
  %137 = load i32, i32* @debug_disable_method, align 4
  %138 = icmp eq i32 %137, 0
  br i1 %138, label %139, label %152

; <label>:139:                                    ; preds = %136
  %140 = load i32, i32* @debug_disable_external, align 4
  %141 = icmp ne i32 %140, 1
  br i1 %141, label %142, label %152

; <label>:142:                                    ; preds = %139
  %143 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %144 = icmp ne %struct.__sFILE* %143, null
  br i1 %144, label %145, label %152

; <label>:145:                                    ; preds = %142
  %146 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %147 = load i32, i32* %8, align 4
  %148 = load i32, i32* %10, align 4
  %149 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %146, i8* getelementptr inbounds ([147 x i8], [147 x i8]* @.str.39, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 425, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %147, i32 %148)
  %150 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %151 = call i32 @fflush(%struct.__sFILE* %150)
  br label %152

; <label>:152:                                    ; preds = %145, %142, %139, %136, %133
  br label %153

; <label>:153:                                    ; preds = %240, %152
  %154 = load i32, i32* %8, align 4
  %155 = load i32, i32* %10, align 4
  %156 = icmp ult i32 %154, %155
  br i1 %156, label %157, label %244

; <label>:157:                                    ; preds = %153
  %158 = load i32, i32* @debug_enable, align 4
  %159 = icmp eq i32 %158, 1
  br i1 %159, label %160, label %180

; <label>:160:                                    ; preds = %157
  %161 = load i32, i32* @debug_disable_method, align 4
  %162 = icmp eq i32 %161, 0
  br i1 %162, label %163, label %180

; <label>:163:                                    ; preds = %160
  %164 = load i32, i32* @debug_disable_external, align 4
  %165 = icmp ne i32 %164, 1
  br i1 %165, label %166, label %180

; <label>:166:                                    ; preds = %163
  %167 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %168 = icmp ne %struct.__sFILE* %167, null
  br i1 %168, label %169, label %180

; <label>:169:                                    ; preds = %166
  %170 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %171 = load i32, i32* %11, align 4
  %172 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %173 = load i32, i32* %11, align 4
  %174 = sext i32 %173 to i64
  %175 = getelementptr inbounds i32, i32* %172, i64 %174
  %176 = load i32, i32* %175, align 4
  %177 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %170, i8* getelementptr inbounds ([133 x i8], [133 x i8]* @.str.40, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 427, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %171, i32 %176)
  %178 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %179 = call i32 @fflush(%struct.__sFILE* %178)
  br label %180

; <label>:180:                                    ; preds = %169, %166, %163, %160, %157
  %181 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %182 = load i32, i32* %11, align 4
  %183 = sext i32 %182 to i64
  %184 = getelementptr inbounds i32, i32* %181, i64 %183
  %185 = load i32, i32* %184, align 4
  store i32 %185, i32* %11, align 4
  %186 = load i32, i32* %11, align 4
  %187 = icmp slt i32 %186, 1
  br i1 %187, label %188, label %192

; <label>:188:                                    ; preds = %180
  %189 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %190 = load i32, i32* %11, align 4
  %191 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %189, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.11, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 429, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.41, i32 0, i32 0), i32 %190)
  call void @quit(i32 1, i32 1)
  br label %192

; <label>:192:                                    ; preds = %188, %180
  %193 = load i32, i32* %5, align 4
  %194 = load i32, i32* %11, align 4
  %195 = load i32, i32* %8, align 4
  %196 = mul i32 %194, %195
  %197 = zext i32 %196 to i64
  %198 = call i64 @lseek(i32 %193, i64 %197, i32 0)
  %199 = call i32* @__error()
  %200 = load i32, i32* %199, align 4
  %201 = icmp ne i32 %200, 0
  br i1 %201, label %202, label %240

; <label>:202:                                    ; preds = %192
  store i32 1, i32* @debug_enable, align 4
  %203 = load i32, i32* @debug_enable, align 4
  %204 = icmp eq i32 %203, 1
  br i1 %204, label %205, label %234

; <label>:205:                                    ; preds = %202
  %206 = load i32, i32* @debug_disable_method, align 4
  %207 = icmp eq i32 %206, 0
  br i1 %207, label %208, label %234

; <label>:208:                                    ; preds = %205
  %209 = load i32, i32* @debug_disable_external, align 4
  %210 = icmp ne i32 %209, 1
  br i1 %210, label %211, label %234

; <label>:211:                                    ; preds = %208
  %212 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %213 = icmp ne %struct.__sFILE* %212, null
  br i1 %213, label %214, label %234

; <label>:214:                                    ; preds = %211
  %215 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %216 = call i32* @__error()
  %217 = load i32, i32* %216, align 4
  %218 = call i32* @__error()
  %219 = load i32, i32* %218, align 4
  %220 = icmp slt i32 %219, 0
  br i1 %220, label %221, label %225

; <label>:221:                                    ; preds = %214
  %222 = call i32* @__error()
  %223 = load i32, i32* %222, align 4
  %224 = sub nsw i32 0, %223
  br label %228

; <label>:225:                                    ; preds = %214
  %226 = call i32* @__error()
  %227 = load i32, i32* %226, align 4
  br label %228

; <label>:228:                                    ; preds = %225, %221
  %229 = phi i32 [ %224, %221 ], [ %227, %225 ]
  %230 = call i8* @"\01_strerror"(i32 %229)
  %231 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %215, i8* getelementptr inbounds ([141 x i8], [141 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 431, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %217, i8* %230)
  %232 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %233 = call i32 @fflush(%struct.__sFILE* %232)
  br label %234

; <label>:234:                                    ; preds = %228, %211, %208, %205, %202
  call void @indent(i32 -1)
  %235 = call i32* @__error()
  %236 = load i32, i32* %235, align 4
  store i32 %236, i32* %13, align 4
  %237 = call i32* @__error()
  store i32 0, i32* %237, align 4
  %238 = load i32, i32* %13, align 4
  %239 = sub nsw i32 0, %238
  store i32 %239, i32* %4, align 4
  br label %344

; <label>:240:                                    ; preds = %192
  %241 = load i32, i32* %8, align 4
  %242 = load i32, i32* %10, align 4
  %243 = sub i32 %242, %241
  store i32 %243, i32* %10, align 4
  br label %153

; <label>:244:                                    ; preds = %153
  %245 = load i32, i32* %5, align 4
  %246 = load i32, i32* %10, align 4
  %247 = zext i32 %246 to i64
  %248 = call i64 @lseek(i32 %245, i64 %247, i32 1)
  %249 = call i32* @__error()
  %250 = load i32, i32* %249, align 4
  %251 = icmp ne i32 %250, 0
  br i1 %251, label %252, label %290

; <label>:252:                                    ; preds = %244
  store i32 1, i32* @debug_enable, align 4
  %253 = load i32, i32* @debug_enable, align 4
  %254 = icmp eq i32 %253, 1
  br i1 %254, label %255, label %284

; <label>:255:                                    ; preds = %252
  %256 = load i32, i32* @debug_disable_method, align 4
  %257 = icmp eq i32 %256, 0
  br i1 %257, label %258, label %284

; <label>:258:                                    ; preds = %255
  %259 = load i32, i32* @debug_disable_external, align 4
  %260 = icmp ne i32 %259, 1
  br i1 %260, label %261, label %284

; <label>:261:                                    ; preds = %258
  %262 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %263 = icmp ne %struct.__sFILE* %262, null
  br i1 %263, label %264, label %284

; <label>:264:                                    ; preds = %261
  %265 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %266 = call i32* @__error()
  %267 = load i32, i32* %266, align 4
  %268 = call i32* @__error()
  %269 = load i32, i32* %268, align 4
  %270 = icmp slt i32 %269, 0
  br i1 %270, label %271, label %275

; <label>:271:                                    ; preds = %264
  %272 = call i32* @__error()
  %273 = load i32, i32* %272, align 4
  %274 = sub nsw i32 0, %273
  br label %278

; <label>:275:                                    ; preds = %264
  %276 = call i32* @__error()
  %277 = load i32, i32* %276, align 4
  br label %278

; <label>:278:                                    ; preds = %275, %271
  %279 = phi i32 [ %274, %271 ], [ %277, %275 ]
  %280 = call i8* @"\01_strerror"(i32 %279)
  %281 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %265, i8* getelementptr inbounds ([141 x i8], [141 x i8]* @.str.38, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 436, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %267, i8* %280)
  %282 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %283 = call i32 @fflush(%struct.__sFILE* %282)
  br label %284

; <label>:284:                                    ; preds = %278, %261, %258, %255, %252
  call void @indent(i32 -1)
  %285 = call i32* @__error()
  %286 = load i32, i32* %285, align 4
  store i32 %286, i32* %14, align 4
  %287 = call i32* @__error()
  store i32 0, i32* %287, align 4
  %288 = load i32, i32* %14, align 4
  %289 = sub nsw i32 0, %288
  store i32 %289, i32* %4, align 4
  br label %344

; <label>:290:                                    ; preds = %244
  %291 = load i32, i32* %9, align 4
  %292 = sext i32 %291 to i64
  %293 = call i8* @calloc(i64 %292, i64 1) #8
  store i8* %293, i8** %15, align 8
  %294 = load i32, i32* %5, align 4
  %295 = load i8*, i8** %15, align 8
  %296 = load i32, i32* %9, align 4
  %297 = sext i32 %296 to i64
  %298 = call i64 @"\01_write"(i32 %294, i8* %295, i64 %297)
  %299 = load i32, i32* %9, align 4
  %300 = sext i32 %299 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 439, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.42, i32 0, i32 0), i64 %300)
  %301 = call i32* @__error()
  %302 = load i32, i32* %301, align 4
  %303 = icmp ne i32 %302, 0
  br i1 %303, label %304, label %342

; <label>:304:                                    ; preds = %290
  store i32 1, i32* @debug_enable, align 4
  %305 = load i32, i32* @debug_enable, align 4
  %306 = icmp eq i32 %305, 1
  br i1 %306, label %307, label %336

; <label>:307:                                    ; preds = %304
  %308 = load i32, i32* @debug_disable_method, align 4
  %309 = icmp eq i32 %308, 0
  br i1 %309, label %310, label %336

; <label>:310:                                    ; preds = %307
  %311 = load i32, i32* @debug_disable_external, align 4
  %312 = icmp ne i32 %311, 1
  br i1 %312, label %313, label %336

; <label>:313:                                    ; preds = %310
  %314 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %315 = icmp ne %struct.__sFILE* %314, null
  br i1 %315, label %316, label %336

; <label>:316:                                    ; preds = %313
  %317 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %318 = call i32* @__error()
  %319 = load i32, i32* %318, align 4
  %320 = call i32* @__error()
  %321 = load i32, i32* %320, align 4
  %322 = icmp slt i32 %321, 0
  br i1 %322, label %323, label %327

; <label>:323:                                    ; preds = %316
  %324 = call i32* @__error()
  %325 = load i32, i32* %324, align 4
  %326 = sub nsw i32 0, %325
  br label %330

; <label>:327:                                    ; preds = %316
  %328 = call i32* @__error()
  %329 = load i32, i32* %328, align 4
  br label %330

; <label>:330:                                    ; preds = %327, %323
  %331 = phi i32 [ %326, %323 ], [ %329, %327 ]
  %332 = call i8* @"\01_strerror"(i32 %331)
  %333 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %317, i8* getelementptr inbounds ([141 x i8], [141 x i8]* @.str.43, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 440, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %319, i8* %332)
  %334 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %335 = call i32 @fflush(%struct.__sFILE* %334)
  br label %336

; <label>:336:                                    ; preds = %330, %313, %310, %307, %304
  call void @indent(i32 -1)
  %337 = call i32* @__error()
  %338 = load i32, i32* %337, align 4
  store i32 %338, i32* %16, align 4
  %339 = call i32* @__error()
  store i32 0, i32* %339, align 4
  %340 = load i32, i32* %16, align 4
  %341 = sub nsw i32 0, %340
  store i32 %341, i32* %4, align 4
  br label %344

; <label>:342:                                    ; preds = %290
  %343 = load i8*, i8** %15, align 8
  call void @free(i8* %343)
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 443, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.36, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.44, i32 0, i32 0))
  call void @indent(i32 -1)
  store i32 0, i32* %4, align 4
  br label %344

; <label>:344:                                    ; preds = %342, %336, %284, %234, %127, %73, %46
  %345 = load i32, i32* %4, align 4
  ret i32 %345
}

declare void @dbgn(i8*, i32, i8*, i8*, i64) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fat_read_superblock(i32, %struct.superblock_t*) #0 {
  %3 = alloca i32, align 4
  %4 = alloca %struct.superblock_t*, align 8
  store i32 %0, i32* %3, align 4
  store %struct.superblock_t* %1, %struct.superblock_t** %4, align 8
  %5 = load i32, i32* %3, align 4
  %6 = call i64 @lseek(i32 %5, i64 0, i32 0)
  %7 = call i32* @__error()
  %8 = load i32, i32* %7, align 4
  %9 = icmp ne i32 %8, 0
  br i1 %9, label %10, label %26

; <label>:10:                                     ; preds = %2
  call void @indent(i32 -1)
  %11 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %12 = call i32* @__error()
  %13 = load i32, i32* %12, align 4
  %14 = icmp slt i32 %13, 0
  br i1 %14, label %15, label %19

; <label>:15:                                     ; preds = %10
  %16 = call i32* @__error()
  %17 = load i32, i32* %16, align 4
  %18 = sub nsw i32 0, %17
  br label %22

; <label>:19:                                     ; preds = %10
  %20 = call i32* @__error()
  %21 = load i32, i32* %20, align 4
  br label %22

; <label>:22:                                     ; preds = %19, %15
  %23 = phi i32 [ %18, %15 ], [ %21, %19 ]
  %24 = call i8* @"\01_strerror"(i32 %23)
  %25 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %11, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 455, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.45, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.46, i32 0, i32 0), i8* %24)
  call void @quit(i32 1, i32 1)
  br label %26

; <label>:26:                                     ; preds = %22, %2
  %27 = load i32, i32* %3, align 4
  %28 = load %struct.superblock_t*, %struct.superblock_t** %4, align 8
  %29 = bitcast %struct.superblock_t* %28 to i8*
  %30 = call i64 @"\01_read"(i32 %27, i8* %29, i64 20)
  %31 = call i32* @__error()
  %32 = load i32, i32* %31, align 4
  %33 = icmp ne i32 %32, 0
  br i1 %33, label %34, label %50

; <label>:34:                                     ; preds = %26
  call void @indent(i32 -1)
  %35 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %36 = call i32* @__error()
  %37 = load i32, i32* %36, align 4
  %38 = icmp slt i32 %37, 0
  br i1 %38, label %39, label %43

; <label>:39:                                     ; preds = %34
  %40 = call i32* @__error()
  %41 = load i32, i32* %40, align 4
  %42 = sub nsw i32 0, %41
  br label %46

; <label>:43:                                     ; preds = %34
  %44 = call i32* @__error()
  %45 = load i32, i32* %44, align 4
  br label %46

; <label>:46:                                     ; preds = %43, %39
  %47 = phi i32 [ %42, %39 ], [ %45, %43 ]
  %48 = call i8* @"\01_strerror"(i32 %47)
  %49 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %35, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 457, i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.45, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.47, i32 0, i32 0), i8* %48)
  call void @quit(i32 1, i32 1)
  br label %50

; <label>:50:                                     ; preds = %46, %26
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @fat_read_table(i32, i32**) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i32**, align 8
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32** %1, i32*** %4, align 8
  call void @indent(i32 1)
  %8 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  store i32 %8, i32* %5, align 4
  %9 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 2), align 8
  store i32 %9, i32* %6, align 4
  %10 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 1), align 4
  store i32 %10, i32* %7, align 4
  %11 = load i32**, i32*** %4, align 8
  %12 = load i32*, i32** %11, align 8
  %13 = icmp ne i32* %12, null
  br i1 %13, label %14, label %18

; <label>:14:                                     ; preds = %2
  %15 = load i32**, i32*** %4, align 8
  %16 = load i32*, i32** %15, align 8
  %17 = bitcast i32* %16 to i8*
  call void @free(i8* %17)
  br label %18

; <label>:18:                                     ; preds = %14, %2
  %19 = load i32, i32* %6, align 4
  %20 = load i32, i32* %5, align 4
  %21 = mul i32 %19, %20
  %22 = zext i32 %21 to i64
  %23 = udiv i64 %22, 4
  %24 = call i8* @calloc(i64 %23, i64 4) #8
  %25 = bitcast i8* %24 to i32*
  %26 = load i32**, i32*** %4, align 8
  store i32* %25, i32** %26, align 8
  %27 = load i32, i32* %3, align 4
  %28 = load i32, i32* %5, align 4
  %29 = zext i32 %28 to i64
  %30 = call i64 @lseek(i32 %27, i64 %29, i32 0)
  %31 = load i32, i32* %3, align 4
  %32 = load i32**, i32*** %4, align 8
  %33 = load i32*, i32** %32, align 8
  %34 = bitcast i32* %33 to i8*
  %35 = load i32, i32* %6, align 4
  %36 = load i32, i32* %5, align 4
  %37 = mul i32 %35, %36
  %38 = zext i32 %37 to i64
  %39 = call i64 @"\01_read"(i32 %31, i8* %34, i64 %38)
  %40 = call i32* @__error()
  %41 = load i32, i32* %40, align 4
  %42 = icmp ne i32 %41, 0
  br i1 %42, label %43, label %59

; <label>:43:                                     ; preds = %18
  call void @indent(i32 -1)
  %44 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %45 = call i32* @__error()
  %46 = load i32, i32* %45, align 4
  %47 = icmp slt i32 %46, 0
  br i1 %47, label %48, label %52

; <label>:48:                                     ; preds = %43
  %49 = call i32* @__error()
  %50 = load i32, i32* %49, align 4
  %51 = sub nsw i32 0, %50
  br label %55

; <label>:52:                                     ; preds = %43
  %53 = call i32* @__error()
  %54 = load i32, i32* %53, align 4
  br label %55

; <label>:55:                                     ; preds = %52, %48
  %56 = phi i32 [ %51, %48 ], [ %54, %52 ]
  %57 = call i8* @"\01_strerror"(i32 %56)
  %58 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %44, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 480, i8* getelementptr inbounds ([11 x i8], [11 x i8]* @.str.48, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.49, i32 0, i32 0), i8* %57)
  call void @quit(i32 1, i32 1)
  br label %59

; <label>:59:                                     ; preds = %55, %18
  call void @indent(i32 -1)
  %60 = load i32, i32* %7, align 4
  %61 = load i32, i32* %5, align 4
  %62 = call i64 @blocks2words(i32 %60, i32 %61)
  ret i64 %62
}

declare i64 @blocks2words(i32, i32) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @fat_debug_dir_entry(%struct.dir_t*) #0 {
  %2 = alloca %struct.dir_t*, align 8
  %3 = alloca i64, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  store %struct.dir_t* %0, %struct.dir_t** %2, align 8
  %6 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %7 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %8 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %7, i32 0, i32 4
  %9 = load i32, i32* %8, align 8
  %10 = icmp eq i32 %9, 0
  %11 = zext i1 %10 to i64
  %12 = select i1 %10, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.17, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.18, i32 0, i32 0)
  %13 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %14 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %13, i32 0, i32 0
  %15 = bitcast %union.fname_u* %14 to [24 x i8]*
  %16 = getelementptr inbounds [24 x i8], [24 x i8]* %15, i32 0, i32 0
  %17 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %6, i8* getelementptr inbounds ([37 x i8], [37 x i8]* @.str.50, i32 0, i32 0), i8* %12, i8* %16)
  %18 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %19 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %18, i32 0, i32 4
  %20 = load i32, i32* %19, align 8
  %21 = and i32 %20, 1
  %22 = icmp eq i32 %21, 0
  br i1 %22, label %29, label %23

; <label>:23:                                     ; preds = %1
  %24 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %25 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %24, i32 0, i32 2
  %26 = load i32, i32* %25, align 8
  %27 = urem i32 %26, 64
  %28 = icmp ne i32 %27, 0
  br i1 %28, label %29, label %41

; <label>:29:                                     ; preds = %23, %1
  %30 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %31 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %32 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %31, i32 0, i32 2
  %33 = load i32, i32* %32, align 8
  %34 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %35 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %34, i32 0, i32 2
  %36 = load i32, i32* %35, align 8
  %37 = icmp eq i32 %36, 1
  %38 = zext i1 %37 to i64
  %39 = select i1 %37, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.26, i32 0, i32 0)
  %40 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %30, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.51, i32 0, i32 0), i32 %33, i8* %39)
  br label %54

; <label>:41:                                     ; preds = %23
  %42 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %43 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %44 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %43, i32 0, i32 2
  %45 = load i32, i32* %44, align 8
  %46 = udiv i32 %45, 64
  %47 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %48 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %47, i32 0, i32 2
  %49 = load i32, i32* %48, align 8
  %50 = icmp eq i32 %49, 64
  %51 = zext i1 %50 to i64
  %52 = select i1 %50, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0)
  %53 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %42, i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.52, i32 0, i32 0), i32 %46, i8* %52)
  br label %54

; <label>:54:                                     ; preds = %41, %29
  %55 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %56 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %55, i32 0, i32 1
  %57 = getelementptr inbounds %struct.times_t, %struct.times_t* %56, i32 0, i32 0
  %58 = load i64, i64* %57, align 8
  store i64 %58, i64* %3, align 8
  %59 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %60 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %59, i32 0, i32 1
  %61 = getelementptr inbounds %struct.times_t, %struct.times_t* %60, i32 0, i32 1
  %62 = load i64, i64* %61, align 8
  store i64 %62, i64* %4, align 8
  %63 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %64 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %63, i32 0, i32 1
  %65 = getelementptr inbounds %struct.times_t, %struct.times_t* %64, i32 0, i32 2
  %66 = load i64, i64* %65, align 8
  store i64 %66, i64* %5, align 8
  %67 = load i64, i64* %3, align 8
  %68 = load i64, i64* %4, align 8
  %69 = icmp eq i64 %67, %68
  br i1 %69, label %70, label %78

; <label>:70:                                     ; preds = %54
  %71 = load i64, i64* %4, align 8
  %72 = load i64, i64* %5, align 8
  %73 = icmp eq i64 %71, %72
  br i1 %73, label %74, label %78

; <label>:74:                                     ; preds = %70
  %75 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %76 = load i64, i64* %3, align 8
  %77 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %75, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.53, i32 0, i32 0), i64 %76)
  br label %88

; <label>:78:                                     ; preds = %70, %54
  %79 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %80 = load i64, i64* %3, align 8
  %81 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %79, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.54, i32 0, i32 0), i64 %80)
  %82 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %83 = load i64, i64* %4, align 8
  %84 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %82, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.55, i32 0, i32 0), i64 %83)
  %85 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %86 = load i64, i64* %5, align 8
  %87 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %85, i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.56, i32 0, i32 0), i64 %86)
  br label %88

; <label>:88:                                     ; preds = %78, %74
  %89 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %90 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %91 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %90, i32 0, i32 3
  %92 = load i32, i32* %91, align 4
  %93 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %89, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.57, i32 0, i32 0), i32 %92)
  %94 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %95 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 4), align 8
  %96 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %97 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %96, i32 0, i32 3
  %98 = load i32, i32* %97, align 4
  %99 = icmp eq i32 %95, %98
  %100 = zext i1 %99 to i64
  %101 = select i1 %99, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.59, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.60, i32 0, i32 0)
  %102 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %94, i8* getelementptr inbounds ([24 x i8], [24 x i8]* @.str.58, i32 0, i32 0), i8* %101)
  %103 = load %struct.__sFILE*, %struct.__sFILE** @__stderrp, align 8
  %104 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %103, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.61, i32 0, i32 0))
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @fat_chain_length(i32) #0 {
  %2 = alloca i32, align 4
  %3 = alloca i64, align 8
  %4 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @indent(i32 1)
  store i64 0, i64* %3, align 8
  %5 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %6 = load i32, i32* %2, align 4
  %7 = sext i32 %6 to i64
  %8 = getelementptr inbounds i32, i32* %5, i64 %7
  %9 = load i32, i32* %8, align 4
  %10 = icmp eq i32 %9, 0
  br i1 %10, label %11, label %29

; <label>:11:                                     ; preds = %1
  %12 = load i32, i32* @debug_enable, align 4
  %13 = icmp eq i32 %12, 1
  br i1 %13, label %14, label %28

; <label>:14:                                     ; preds = %11
  %15 = load i32, i32* @debug_disable_method, align 4
  %16 = icmp eq i32 %15, 0
  br i1 %16, label %17, label %28

; <label>:17:                                     ; preds = %14
  %18 = load i32, i32* @debug_disable_external, align 4
  %19 = icmp ne i32 %18, 1
  br i1 %19, label %20, label %28

; <label>:20:                                     ; preds = %17
  %21 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %22 = icmp ne %struct.__sFILE* %21, null
  br i1 %22, label %23, label %28

; <label>:23:                                     ; preds = %20
  %24 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %25 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %24, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 525, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.63, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([21 x i8], [21 x i8]* @.str.64, i32 0, i32 0))
  %26 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %27 = call i32 @fflush(%struct.__sFILE* %26)
  br label %28

; <label>:28:                                     ; preds = %23, %20, %17, %14, %11
  br label %96

; <label>:29:                                     ; preds = %1
  %30 = load i32, i32* %2, align 4
  store i32 %30, i32* %4, align 4
  br label %31

; <label>:31:                                     ; preds = %94, %29
  %32 = load i64, i64* %3, align 8
  %33 = add i64 %32, 1
  store i64 %33, i64* %3, align 8
  %34 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %35 = load i32, i32* %4, align 4
  %36 = sext i32 %35 to i64
  %37 = getelementptr inbounds i32, i32* %34, i64 %36
  %38 = load i32, i32* %37, align 4
  store i32 %38, i32* %4, align 4
  %39 = load i32, i32* %4, align 4
  %40 = icmp eq i32 %39, -2
  br i1 %40, label %41, label %42

; <label>:41:                                     ; preds = %31
  br label %95

; <label>:42:                                     ; preds = %31
  %43 = load i32, i32* %4, align 4
  %44 = icmp eq i32 %43, 0
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
  %59 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %58, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 534, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.63, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.65, i32 0, i32 0))
  %60 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %61 = call i32 @fflush(%struct.__sFILE* %60)
  br label %62

; <label>:62:                                     ; preds = %57, %54, %51, %48, %45
  br label %95

; <label>:63:                                     ; preds = %42
  %64 = load i32, i32* %4, align 4
  %65 = icmp eq i32 %64, -1
  br i1 %65, label %66, label %84

; <label>:66:                                     ; preds = %63
  %67 = load i32, i32* @debug_enable, align 4
  %68 = icmp eq i32 %67, 1
  br i1 %68, label %69, label %83

; <label>:69:                                     ; preds = %66
  %70 = load i32, i32* @debug_disable_method, align 4
  %71 = icmp eq i32 %70, 0
  br i1 %71, label %72, label %83

; <label>:72:                                     ; preds = %69
  %73 = load i32, i32* @debug_disable_external, align 4
  %74 = icmp ne i32 %73, 1
  br i1 %74, label %75, label %83

; <label>:75:                                     ; preds = %72
  %76 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %77 = icmp ne %struct.__sFILE* %76, null
  br i1 %77, label %78, label %83

; <label>:78:                                     ; preds = %75
  %79 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %80 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %79, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 537, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.63, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.66, i32 0, i32 0))
  %81 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %82 = call i32 @fflush(%struct.__sFILE* %81)
  br label %83

; <label>:83:                                     ; preds = %78, %75, %72, %69, %66
  br label %95

; <label>:84:                                     ; preds = %63
  %85 = load i32, i32* %4, align 4
  %86 = icmp slt i32 %85, -2
  br i1 %86, label %87, label %91

; <label>:87:                                     ; preds = %84
  %88 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %89 = load i32, i32* %4, align 4
  %90 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %88, i8* getelementptr inbounds ([148 x i8], [148 x i8]* @.str.67, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 540, i8* getelementptr inbounds ([13 x i8], [13 x i8]* @.str.63, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %89)
  call void @quit(i32 1, i32 1)
  br label %91

; <label>:91:                                     ; preds = %87, %84
  br label %92

; <label>:92:                                     ; preds = %91
  br label %93

; <label>:93:                                     ; preds = %92
  br label %94

; <label>:94:                                     ; preds = %93
  br label %31

; <label>:95:                                     ; preds = %83, %62, %41
  br label %96

; <label>:96:                                     ; preds = %95, %28
  call void @indent(i32 -1)
  %97 = load i64, i64* %3, align 8
  ret i64 %97
}

declare i64 @blocks2bytes(i32, i32) #1

; Function Attrs: nounwind
declare i8* @__memcpy_chk(i8*, i8*, i64, i64) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_find(i32, i64, i8*, %struct.dir_t*, %struct.dir_t**, i64*, i32, i8**) #0 {
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  %11 = alloca i64, align 8
  %12 = alloca i8*, align 8
  %13 = alloca %struct.dir_t*, align 8
  %14 = alloca %struct.dir_t**, align 8
  %15 = alloca i64*, align 8
  %16 = alloca i32, align 4
  %17 = alloca i8**, align 8
  %18 = alloca i32, align 4
  %19 = alloca %struct.pathc_t*, align 8
  %20 = alloca %struct.fdc_t*, align 8
  %21 = alloca i8*, align 8
  %22 = alloca %struct.dir_t*, align 8
  %23 = alloca i64, align 8
  %24 = alloca i64, align 8
  %25 = alloca i32, align 4
  %26 = alloca %struct.dir_t*, align 8
  %27 = alloca i64*, align 8
  %28 = alloca i8*, align 8
  %29 = alloca i8*, align 8
  %30 = alloca %struct.dir_t, align 8
  %31 = alloca i64, align 8
  %32 = alloca i32, align 4
  %33 = alloca i8*, align 8
  %34 = alloca i32, align 4
  %35 = alloca i32, align 4
  %36 = alloca %struct.dir_t*, align 8
  %37 = alloca i8*, align 8
  store i32 %0, i32* %10, align 4
  store i64 %1, i64* %11, align 8
  store i8* %2, i8** %12, align 8
  store %struct.dir_t* %3, %struct.dir_t** %13, align 8
  store %struct.dir_t** %4, %struct.dir_t*** %14, align 8
  store i64* %5, i64** %15, align 8
  store i32 %6, i32* %16, align 4
  store i8** %7, i8*** %17, align 8
  call void @indent(i32 1)
  %38 = load i64, i64* %11, align 8
  %39 = icmp ult i64 %38, 0
  br i1 %39, label %40, label %61

; <label>:40:                                     ; preds = %8
  %41 = load i8*, i8** %12, align 8
  %42 = icmp eq i8* %41, null
  br i1 %42, label %43, label %61

; <label>:43:                                     ; preds = %40
  %44 = load i32, i32* @debug_enable, align 4
  %45 = icmp eq i32 %44, 1
  br i1 %45, label %46, label %60

; <label>:46:                                     ; preds = %43
  %47 = load i32, i32* @debug_disable_method, align 4
  %48 = icmp eq i32 %47, 0
  br i1 %48, label %49, label %60

; <label>:49:                                     ; preds = %46
  %50 = load i32, i32* @debug_disable_external, align 4
  %51 = icmp ne i32 %50, 1
  br i1 %51, label %52, label %60

; <label>:52:                                     ; preds = %49
  %53 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %54 = icmp ne %struct.__sFILE* %53, null
  br i1 %54, label %55, label %60

; <label>:55:                                     ; preds = %52
  %56 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %57 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %56, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 665, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([28 x i8], [28 x i8]* @.str.76, i32 0, i32 0))
  %58 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %59 = call i32 @fflush(%struct.__sFILE* %58)
  br label %60

; <label>:60:                                     ; preds = %55, %52, %49, %46, %43
  call void @indent(i32 -1)
  store i32 -22, i32* %9, align 4
  br label %706

; <label>:61:                                     ; preds = %40, %8
  store i32 0, i32* %18, align 4
  %62 = load i32, i32* @debug_disable_method, align 4
  %63 = or i32 %62, 2
  store i32 %63, i32* @debug_disable_method, align 4
  %64 = load i32, i32* %16, align 4
  %65 = icmp ne i32 %64, 0
  br i1 %65, label %178, label %66

; <label>:66:                                     ; preds = %61
  store %struct.pathc_t* null, %struct.pathc_t** %19, align 8
  %67 = load i64, i64* %11, align 8
  %68 = icmp ule i64 0, %67
  br i1 %68, label %69, label %87

; <label>:69:                                     ; preds = %66
  %70 = load i64, i64* %11, align 8
  %71 = call %struct.fdc_t* @fdc_find(i64 %70)
  store %struct.fdc_t* %71, %struct.fdc_t** %20, align 8
  %72 = load %struct.fdc_t*, %struct.fdc_t** %20, align 8
  %73 = icmp ne %struct.fdc_t* %72, null
  br i1 %73, label %74, label %79

; <label>:74:                                     ; preds = %69
  %75 = load i64, i64* %11, align 8
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 687, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([49 x i8], [49 x i8]* @.str.77, i32 0, i32 0), i64 %75)
  %76 = load %struct.fdc_t*, %struct.fdc_t** %20, align 8
  %77 = getelementptr inbounds %struct.fdc_t, %struct.fdc_t* %76, i32 0, i32 2
  %78 = load %struct.pathc_t*, %struct.pathc_t** %77, align 8
  store %struct.pathc_t* %78, %struct.pathc_t** %19, align 8
  br label %86

; <label>:79:                                     ; preds = %69
  %80 = load i8*, i8** %12, align 8
  %81 = icmp eq i8* %80, null
  br i1 %81, label %82, label %85

; <label>:82:                                     ; preds = %79
  %83 = load i32, i32* @debug_disable_method, align 4
  %84 = and i32 %83, -3
  store i32 %84, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -2, i32* %9, align 4
  br label %706

; <label>:85:                                     ; preds = %79
  br label %86

; <label>:86:                                     ; preds = %85, %74
  br label %87

; <label>:87:                                     ; preds = %86, %66
  %88 = load %struct.pathc_t*, %struct.pathc_t** %19, align 8
  %89 = icmp eq %struct.pathc_t* %88, null
  br i1 %89, label %90, label %118

; <label>:90:                                     ; preds = %87
  %91 = load i8*, i8** %12, align 8
  %92 = call %struct.pathc_t* @pathc_find_path(i8* %91)
  store %struct.pathc_t* %92, %struct.pathc_t** %19, align 8
  %93 = load %struct.pathc_t*, %struct.pathc_t** %19, align 8
  %94 = icmp ne %struct.pathc_t* %93, null
  br i1 %94, label %95, label %117

; <label>:95:                                     ; preds = %90
  %96 = load i32, i32* @debug_enable, align 4
  %97 = icmp eq i32 %96, 1
  br i1 %97, label %98, label %116

; <label>:98:                                     ; preds = %95
  %99 = load i32, i32* @debug_disable_method, align 4
  %100 = icmp eq i32 %99, 0
  br i1 %100, label %101, label %116

; <label>:101:                                    ; preds = %98
  %102 = load i32, i32* @debug_disable_external, align 4
  %103 = icmp ne i32 %102, 1
  br i1 %103, label %104, label %116

; <label>:104:                                    ; preds = %101
  %105 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %106 = icmp ne %struct.__sFILE* %105, null
  br i1 %106, label %107, label %116

; <label>:107:                                    ; preds = %104
  %108 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %109 = load i8*, i8** %12, align 8
  %110 = load %struct.pathc_t*, %struct.pathc_t** %19, align 8
  %111 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %110, i32 0, i32 4
  %112 = load i64, i64* %111, align 8
  %113 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %108, i8* getelementptr inbounds ([201 x i8], [201 x i8]* @.str.78, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 699, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %109, i64 %112)
  %114 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %115 = call i32 @fflush(%struct.__sFILE* %114)
  br label %116

; <label>:116:                                    ; preds = %107, %104, %101, %98, %95
  br label %117

; <label>:117:                                    ; preds = %116, %90
  br label %118

; <label>:118:                                    ; preds = %117, %87
  %119 = load %struct.pathc_t*, %struct.pathc_t** %19, align 8
  %120 = icmp ne %struct.pathc_t* %119, null
  br i1 %120, label %121, label %177

; <label>:121:                                    ; preds = %118
  %122 = load %struct.pathc_t*, %struct.pathc_t** %19, align 8
  %123 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %122, i32 0, i32 2
  %124 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %123, i32 0, i32 0
  %125 = bitcast %union.fname_u* %124 to [24 x i8]*
  %126 = getelementptr inbounds [24 x i8], [24 x i8]* %125, i32 0, i32 0
  store i8* %126, i8** %21, align 8
  %127 = load i8*, i8** %21, align 8
  %128 = call i64 @strlen(i8* %127)
  %129 = icmp eq i64 %128, 0
  br i1 %129, label %130, label %148

; <label>:130:                                    ; preds = %121
  %131 = load i32, i32* @debug_enable, align 4
  %132 = icmp eq i32 %131, 1
  br i1 %132, label %133, label %147

; <label>:133:                                    ; preds = %130
  %134 = load i32, i32* @debug_disable_method, align 4
  %135 = icmp eq i32 %134, 0
  br i1 %135, label %136, label %147

; <label>:136:                                    ; preds = %133
  %137 = load i32, i32* @debug_disable_external, align 4
  %138 = icmp ne i32 %137, 1
  br i1 %138, label %139, label %147

; <label>:139:                                    ; preds = %136
  %140 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %141 = icmp ne %struct.__sFILE* %140, null
  br i1 %141, label %142, label %147

; <label>:142:                                    ; preds = %139
  %143 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %144 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %143, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 707, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.79, i32 0, i32 0))
  %145 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %146 = call i32 @fflush(%struct.__sFILE* %145)
  br label %147

; <label>:147:                                    ; preds = %142, %139, %136, %133, %130
  br label %148

; <label>:148:                                    ; preds = %147, %121
  %149 = load i64*, i64** %15, align 8
  %150 = icmp ne i64* %149, null
  br i1 %150, label %151, label %156

; <label>:151:                                    ; preds = %148
  %152 = load %struct.pathc_t*, %struct.pathc_t** %19, align 8
  %153 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %152, i32 0, i32 4
  %154 = load i64, i64* %153, align 8
  %155 = load i64*, i64** %15, align 8
  store i64 %154, i64* %155, align 8
  br label %156

; <label>:156:                                    ; preds = %151, %148
  %157 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %158 = icmp eq %struct.dir_t** %157, null
  br i1 %158, label %159, label %169

; <label>:159:                                    ; preds = %156
  %160 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %161 = icmp ne %struct.dir_t* %160, null
  br i1 %161, label %162, label %168

; <label>:162:                                    ; preds = %159
  %163 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %164 = load %struct.pathc_t*, %struct.pathc_t** %19, align 8
  %165 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %164, i32 0, i32 2
  %166 = bitcast %struct.dir_t* %163 to i8*
  %167 = bitcast %struct.dir_t* %165 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %166, i8* align 8 %167, i64 64, i1 false)
  br label %168

; <label>:168:                                    ; preds = %162, %159
  br label %173

; <label>:169:                                    ; preds = %156
  %170 = load %struct.pathc_t*, %struct.pathc_t** %19, align 8
  %171 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %170, i32 0, i32 2
  %172 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  store %struct.dir_t* %171, %struct.dir_t** %172, align 8
  br label %173

; <label>:173:                                    ; preds = %169, %168
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 717, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.80, i32 0, i32 0))
  %174 = load i32, i32* @debug_disable_method, align 4
  %175 = and i32 %174, -3
  store i32 %175, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  %176 = load i32, i32* %18, align 4
  store i32 %176, i32* %9, align 4
  br label %706

; <label>:177:                                    ; preds = %118
  br label %178

; <label>:178:                                    ; preds = %177, %61
  %179 = load i8*, i8** %12, align 8
  %180 = call i32 @strcmp(i8* %179, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.81, i32 0, i32 0))
  %181 = icmp eq i32 %180, 0
  br i1 %181, label %186, label %182

; <label>:182:                                    ; preds = %178
  %183 = load i8*, i8** %12, align 8
  %184 = call i64 @strlen(i8* %183)
  %185 = icmp eq i64 %184, 0
  br i1 %185, label %186, label %208

; <label>:186:                                    ; preds = %182, %178
  %187 = load i32, i32* %10, align 4
  %188 = load i64*, i64** %15, align 8
  %189 = call %struct.dir_t* @fat_get_root(i32 %187, i64* %188)
  store %struct.dir_t* %189, %struct.dir_t** %22, align 8
  %190 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %191 = icmp eq %struct.dir_t** %190, null
  br i1 %191, label %192, label %201

; <label>:192:                                    ; preds = %186
  %193 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %194 = icmp ne %struct.dir_t* %193, null
  br i1 %194, label %195, label %200

; <label>:195:                                    ; preds = %192
  %196 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %197 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %198 = bitcast %struct.dir_t* %196 to i8*
  %199 = bitcast %struct.dir_t* %197 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %198, i8* align 8 %199, i64 64, i1 false)
  br label %200

; <label>:200:                                    ; preds = %195, %192
  br label %204

; <label>:201:                                    ; preds = %186
  %202 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %203 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  store %struct.dir_t* %202, %struct.dir_t** %203, align 8
  br label %204

; <label>:204:                                    ; preds = %201, %200
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 731, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.82, i32 0, i32 0))
  %205 = load i32, i32* @debug_disable_method, align 4
  %206 = and i32 %205, -3
  store i32 %206, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  %207 = load i32, i32* %18, align 4
  store i32 %207, i32* %9, align 4
  br label %706

; <label>:208:                                    ; preds = %182
  store %struct.dir_t* null, %struct.dir_t** %26, align 8
  store i64* null, i64** %27, align 8
  %209 = load i8*, i8** %12, align 8
  %210 = call i8* @strdup(i8* %209)
  store i8* %210, i8** %29, align 8
  %211 = load i32, i32* %10, align 4
  %212 = call %struct.dir_t* @fat_get_root(i32 %211, i64* null)
  %213 = bitcast %struct.dir_t* %30 to i8*
  %214 = bitcast %struct.dir_t* %212 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %213, i8* align 8 %214, i64 64, i1 false)
  %215 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 4), align 8
  %216 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %217 = mul i32 %215, %216
  %218 = zext i32 %217 to i64
  store i64 %218, i64* %31, align 8
  store i32 0, i32* %32, align 4
  br label %219

; <label>:219:                                    ; preds = %676, %208
  %220 = load i8*, i8** %29, align 8
  %221 = call i8* @path_first(i8* %220, i8** %28)
  store i8* %221, i8** %33, align 8
  %222 = load i8*, i8** %29, align 8
  call void @free(i8* %222)
  %223 = load i8*, i8** %28, align 8
  store i8* %223, i8** %29, align 8
  %224 = load i8*, i8** %28, align 8
  %225 = icmp eq i8* %224, null
  br i1 %225, label %229, label %226

; <label>:226:                                    ; preds = %219
  %227 = load i8*, i8** %33, align 8
  %228 = icmp eq i8* %227, null
  br label %229

; <label>:229:                                    ; preds = %226, %219
  %230 = phi i1 [ true, %219 ], [ %228, %226 ]
  %231 = zext i1 %230 to i32
  store i32 %231, i32* %25, align 4
  %232 = load i32, i32* %25, align 4
  %233 = icmp ne i32 %232, 0
  br i1 %233, label %234, label %303

; <label>:234:                                    ; preds = %229
  %235 = load i32, i32* %16, align 4
  %236 = icmp ne i32 %235, 0
  br i1 %236, label %237, label %303

; <label>:237:                                    ; preds = %234
  %238 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %239 = icmp eq %struct.dir_t** %238, null
  br i1 %239, label %240, label %248

; <label>:240:                                    ; preds = %237
  %241 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %242 = icmp ne %struct.dir_t* %241, null
  br i1 %242, label %243, label %247

; <label>:243:                                    ; preds = %240
  %244 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %245 = bitcast %struct.dir_t* %244 to i8*
  %246 = bitcast %struct.dir_t* %30 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %245, i8* align 8 %246, i64 64, i1 false)
  br label %247

; <label>:247:                                    ; preds = %243, %240
  br label %265

; <label>:248:                                    ; preds = %237
  %249 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %250 = icmp ne %struct.dir_t** %249, null
  br i1 %250, label %251, label %264

; <label>:251:                                    ; preds = %248
  %252 = call i8* @malloc(i64 64) #9
  %253 = bitcast i8* %252 to %struct.dir_t*
  %254 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  store %struct.dir_t* %253, %struct.dir_t** %254, align 8
  %255 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %256 = load %struct.dir_t*, %struct.dir_t** %255, align 8
  %257 = bitcast %struct.dir_t* %256 to i8*
  %258 = bitcast %struct.dir_t* %30 to i8*
  %259 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %260 = load %struct.dir_t*, %struct.dir_t** %259, align 8
  %261 = bitcast %struct.dir_t* %260 to i8*
  %262 = call i64 @llvm.objectsize.i64.p0i8(i8* %261, i1 false, i1 true)
  %263 = call i8* @__memcpy_chk(i8* %257, i8* %258, i64 64, i64 %262) #7
  br label %264

; <label>:264:                                    ; preds = %251, %248
  store i32 1, i32* %18, align 4
  br label %265

; <label>:265:                                    ; preds = %264, %247
  %266 = load i64*, i64** %15, align 8
  %267 = icmp ne i64* %266, null
  br i1 %267, label %268, label %271

; <label>:268:                                    ; preds = %265
  %269 = load i64, i64* %31, align 8
  %270 = load i64*, i64** %15, align 8
  store i64 %269, i64* %270, align 8
  br label %271

; <label>:271:                                    ; preds = %268, %265
  %272 = load i32, i32* @debug_enable, align 4
  %273 = icmp eq i32 %272, 1
  br i1 %273, label %274, label %288

; <label>:274:                                    ; preds = %271
  %275 = load i32, i32* @debug_disable_method, align 4
  %276 = icmp eq i32 %275, 0
  br i1 %276, label %277, label %288

; <label>:277:                                    ; preds = %274
  %278 = load i32, i32* @debug_disable_external, align 4
  %279 = icmp ne i32 %278, 1
  br i1 %279, label %280, label %288

; <label>:280:                                    ; preds = %277
  %281 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %282 = icmp ne %struct.__sFILE* %281, null
  br i1 %282, label %283, label %288

; <label>:283:                                    ; preds = %280
  %284 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %285 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %284, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 765, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([26 x i8], [26 x i8]* @.str.83, i32 0, i32 0))
  %286 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %287 = call i32 @fflush(%struct.__sFILE* %286)
  br label %288

; <label>:288:                                    ; preds = %283, %280, %277, %274, %271
  %289 = load i8**, i8*** %17, align 8
  %290 = icmp ne i8** %289, null
  br i1 %290, label %291, label %294

; <label>:291:                                    ; preds = %288
  %292 = load i8*, i8** %33, align 8
  %293 = load i8**, i8*** %17, align 8
  store i8* %292, i8** %293, align 8
  br label %294

; <label>:294:                                    ; preds = %291, %288
  %295 = load i8*, i8** %29, align 8
  %296 = icmp ne i8* %295, null
  br i1 %296, label %297, label %299

; <label>:297:                                    ; preds = %294
  %298 = load i8*, i8** %29, align 8
  call void @free(i8* %298)
  store i8* null, i8** %29, align 8
  br label %299

; <label>:299:                                    ; preds = %297, %294
  %300 = load i32, i32* @debug_disable_method, align 4
  %301 = and i32 %300, -3
  store i32 %301, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  %302 = load i32, i32* %18, align 4
  store i32 %302, i32* %9, align 4
  br label %706

; <label>:303:                                    ; preds = %234, %229
  %304 = load i8*, i8** %33, align 8
  %305 = icmp eq i8* %304, null
  br i1 %305, label %306, label %314

; <label>:306:                                    ; preds = %303
  %307 = load i8*, i8** %29, align 8
  %308 = icmp ne i8* %307, null
  br i1 %308, label %309, label %311

; <label>:309:                                    ; preds = %306
  %310 = load i8*, i8** %29, align 8
  call void @free(i8* %310)
  store i8* null, i8** %29, align 8
  br label %311

; <label>:311:                                    ; preds = %309, %306
  %312 = load i32, i32* @debug_disable_method, align 4
  %313 = and i32 %312, -3
  store i32 %313, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -2, i32* %9, align 4
  br label %706

; <label>:314:                                    ; preds = %303
  %315 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %316 = icmp ne %struct.dir_t* %315, null
  br i1 %316, label %317, label %320

; <label>:317:                                    ; preds = %314
  %318 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %319 = bitcast %struct.dir_t* %318 to i8*
  call void @free(i8* %319)
  store %struct.dir_t* null, %struct.dir_t** %26, align 8
  br label %320

; <label>:320:                                    ; preds = %317, %314
  %321 = load i64*, i64** %27, align 8
  %322 = icmp ne i64* %321, null
  br i1 %322, label %323, label %326

; <label>:323:                                    ; preds = %320
  %324 = load i64*, i64** %27, align 8
  %325 = bitcast i64* %324 to i8*
  call void @free(i8* %325)
  store i64* null, i64** %27, align 8
  br label %326

; <label>:326:                                    ; preds = %323, %320
  %327 = load i32, i32* %10, align 4
  %328 = call i32 @fat_read_dir(i32 %327, %struct.dir_t* %30, %struct.dir_t** %26, i64** %27, i64* %23, i32* null)
  store i32 %328, i32* %34, align 4
  %329 = load i32, i32* %34, align 4
  %330 = icmp slt i32 %329, 0
  br i1 %330, label %331, label %385

; <label>:331:                                    ; preds = %326
  %332 = load i32, i32* @debug_enable, align 4
  %333 = icmp eq i32 %332, 1
  br i1 %333, label %334, label %359

; <label>:334:                                    ; preds = %331
  %335 = load i32, i32* @debug_disable_method, align 4
  %336 = icmp eq i32 %335, 0
  br i1 %336, label %337, label %359

; <label>:337:                                    ; preds = %334
  %338 = load i32, i32* @debug_disable_external, align 4
  %339 = icmp ne i32 %338, 1
  br i1 %339, label %340, label %359

; <label>:340:                                    ; preds = %337
  %341 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %342 = icmp ne %struct.__sFILE* %341, null
  br i1 %342, label %343, label %359

; <label>:343:                                    ; preds = %340
  %344 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %345 = load i32, i32* %34, align 4
  %346 = load i32, i32* %34, align 4
  %347 = icmp slt i32 %346, 0
  br i1 %347, label %348, label %351

; <label>:348:                                    ; preds = %343
  %349 = load i32, i32* %34, align 4
  %350 = sub nsw i32 0, %349
  br label %353

; <label>:351:                                    ; preds = %343
  %352 = load i32, i32* %34, align 4
  br label %353

; <label>:353:                                    ; preds = %351, %348
  %354 = phi i32 [ %350, %348 ], [ %352, %351 ]
  %355 = call i8* @"\01_strerror"(i32 %354)
  %356 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %344, i8* getelementptr inbounds ([158 x i8], [158 x i8]* @.str.84, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 781, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %345, i8* %355)
  %357 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %358 = call i32 @fflush(%struct.__sFILE* %357)
  br label %359

; <label>:359:                                    ; preds = %353, %340, %337, %334, %331
  %360 = load i8*, i8** %29, align 8
  %361 = icmp ne i8* %360, null
  br i1 %361, label %362, label %364

; <label>:362:                                    ; preds = %359
  %363 = load i8*, i8** %29, align 8
  call void @free(i8* %363)
  store i8* null, i8** %29, align 8
  br label %364

; <label>:364:                                    ; preds = %362, %359
  %365 = load i64*, i64** %27, align 8
  %366 = icmp ne i64* %365, null
  br i1 %366, label %367, label %370

; <label>:367:                                    ; preds = %364
  %368 = load i64*, i64** %27, align 8
  %369 = bitcast i64* %368 to i8*
  call void @free(i8* %369)
  store i64* null, i64** %27, align 8
  br label %370

; <label>:370:                                    ; preds = %367, %364
  %371 = load i8*, i8** %33, align 8
  %372 = icmp ne i8* %371, null
  br i1 %372, label %373, label %375

; <label>:373:                                    ; preds = %370
  %374 = load i8*, i8** %33, align 8
  call void @free(i8* %374)
  store i8* null, i8** %33, align 8
  br label %375

; <label>:375:                                    ; preds = %373, %370
  %376 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %377 = icmp ne %struct.dir_t* %376, null
  br i1 %377, label %378, label %381

; <label>:378:                                    ; preds = %375
  %379 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %380 = bitcast %struct.dir_t* %379 to i8*
  call void @free(i8* %380)
  store %struct.dir_t* null, %struct.dir_t** %26, align 8
  br label %381

; <label>:381:                                    ; preds = %378, %375
  %382 = load i32, i32* @debug_disable_method, align 4
  %383 = and i32 %382, -3
  store i32 %383, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  %384 = load i32, i32* %34, align 4
  store i32 %384, i32* %9, align 4
  br label %706

; <label>:385:                                    ; preds = %326
  store i32 0, i32* %35, align 4
  store i64 0, i64* %24, align 8
  br label %386

; <label>:386:                                    ; preds = %646, %385
  %387 = load i64, i64* %24, align 8
  %388 = load i64, i64* %23, align 8
  %389 = icmp ult i64 %387, %388
  br i1 %389, label %390, label %649

; <label>:390:                                    ; preds = %386
  %391 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %392 = load i64, i64* %24, align 8
  %393 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %391, i64 %392
  store %struct.dir_t* %393, %struct.dir_t** %36, align 8
  %394 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %395 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %394, i32 0, i32 0
  %396 = bitcast %union.fname_u* %395 to [24 x i8]*
  %397 = getelementptr inbounds [24 x i8], [24 x i8]* %396, i32 0, i32 0
  store i8* %397, i8** %37, align 8
  %398 = load i8*, i8** %37, align 8
  %399 = load i8*, i8** %33, align 8
  %400 = call i32 @strcmp(i8* %398, i8* %399)
  %401 = icmp eq i32 %400, 0
  br i1 %401, label %402, label %645

; <label>:402:                                    ; preds = %390
  %403 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %404 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %403, i32 0, i32 3
  %405 = load i32, i32* %404, align 4
  %406 = icmp eq i32 %405, 0
  br i1 %406, label %645, label %407

; <label>:407:                                    ; preds = %402
  %408 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %409 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %410 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %409, i32 0, i32 3
  %411 = load i32, i32* %410, align 4
  %412 = sext i32 %411 to i64
  %413 = getelementptr inbounds i32, i32* %408, i64 %412
  %414 = load i32, i32* %413, align 4
  %415 = icmp eq i32 %414, 0
  br i1 %415, label %645, label %416

; <label>:416:                                    ; preds = %407
  %417 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %418 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %417, i32 0, i32 4
  %419 = load i32, i32* %418, align 8
  %420 = and i32 %419, 1
  %421 = icmp eq i32 %420, 0
  br i1 %421, label %422, label %558

; <label>:422:                                    ; preds = %416
  %423 = load i32, i32* %25, align 4
  %424 = icmp ne i32 %423, 0
  br i1 %424, label %425, label %515

; <label>:425:                                    ; preds = %422
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 800, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.85, i32 0, i32 0))
  %426 = load i32, i32* @debug_enable, align 4
  %427 = icmp eq i32 %426, 1
  br i1 %427, label %428, label %450

; <label>:428:                                    ; preds = %425
  %429 = load i32, i32* @debug_disable_method, align 4
  %430 = icmp eq i32 %429, 0
  br i1 %430, label %431, label %450

; <label>:431:                                    ; preds = %428
  %432 = load i32, i32* @debug_disable_external, align 4
  %433 = icmp ne i32 %432, 1
  br i1 %433, label %434, label %450

; <label>:434:                                    ; preds = %431
  %435 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %436 = icmp ne %struct.__sFILE* %435, null
  br i1 %436, label %437, label %450

; <label>:437:                                    ; preds = %434
  %438 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %439 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %440 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %439, i32 0, i32 0
  %441 = bitcast %union.fname_u* %440 to [24 x i8]*
  %442 = getelementptr inbounds [24 x i8], [24 x i8]* %441, i32 0, i32 0
  %443 = load i64*, i64** %27, align 8
  %444 = load i64, i64* %24, align 8
  %445 = getelementptr inbounds i64, i64* %443, i64 %444
  %446 = load i64, i64* %445, align 8
  %447 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %438, i8* getelementptr inbounds ([185 x i8], [185 x i8]* @.str.86, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 801, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %442, i64 %446)
  %448 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %449 = call i32 @fflush(%struct.__sFILE* %448)
  br label %450

; <label>:450:                                    ; preds = %437, %434, %431, %428, %425
  %451 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %452 = icmp eq %struct.dir_t** %451, null
  br i1 %452, label %453, label %462

; <label>:453:                                    ; preds = %450
  %454 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %455 = icmp ne %struct.dir_t* %454, null
  br i1 %455, label %456, label %461

; <label>:456:                                    ; preds = %453
  %457 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %458 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %459 = bitcast %struct.dir_t* %457 to i8*
  %460 = bitcast %struct.dir_t* %458 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %459, i8* align 8 %460, i64 64, i1 false)
  br label %461

; <label>:461:                                    ; preds = %456, %453
  br label %480

; <label>:462:                                    ; preds = %450
  %463 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %464 = icmp ne %struct.dir_t** %463, null
  br i1 %464, label %465, label %479

; <label>:465:                                    ; preds = %462
  %466 = call i8* @malloc(i64 64) #9
  %467 = bitcast i8* %466 to %struct.dir_t*
  %468 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  store %struct.dir_t* %467, %struct.dir_t** %468, align 8
  %469 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %470 = load %struct.dir_t*, %struct.dir_t** %469, align 8
  %471 = bitcast %struct.dir_t* %470 to i8*
  %472 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %473 = bitcast %struct.dir_t* %472 to i8*
  %474 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %475 = load %struct.dir_t*, %struct.dir_t** %474, align 8
  %476 = bitcast %struct.dir_t* %475 to i8*
  %477 = call i64 @llvm.objectsize.i64.p0i8(i8* %476, i1 false, i1 true)
  %478 = call i8* @__memcpy_chk(i8* %471, i8* %473, i64 64, i64 %477) #7
  br label %479

; <label>:479:                                    ; preds = %465, %462
  store i32 1, i32* %18, align 4
  br label %480

; <label>:480:                                    ; preds = %479, %461
  %481 = load i64*, i64** %15, align 8
  %482 = icmp ne i64* %481, null
  br i1 %482, label %483, label %489

; <label>:483:                                    ; preds = %480
  %484 = load i64*, i64** %27, align 8
  %485 = load i64, i64* %24, align 8
  %486 = getelementptr inbounds i64, i64* %484, i64 %485
  %487 = load i64, i64* %486, align 8
  %488 = load i64*, i64** %15, align 8
  store i64 %487, i64* %488, align 8
  br label %489

; <label>:489:                                    ; preds = %483, %480
  %490 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %491 = icmp ne %struct.dir_t* %490, null
  br i1 %491, label %492, label %495

; <label>:492:                                    ; preds = %489
  %493 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %494 = bitcast %struct.dir_t* %493 to i8*
  call void @free(i8* %494)
  store %struct.dir_t* null, %struct.dir_t** %26, align 8
  br label %495

; <label>:495:                                    ; preds = %492, %489
  %496 = load i8*, i8** %29, align 8
  %497 = icmp ne i8* %496, null
  br i1 %497, label %498, label %500

; <label>:498:                                    ; preds = %495
  %499 = load i8*, i8** %29, align 8
  call void @free(i8* %499)
  store i8* null, i8** %29, align 8
  br label %500

; <label>:500:                                    ; preds = %498, %495
  %501 = load i64*, i64** %27, align 8
  %502 = icmp ne i64* %501, null
  br i1 %502, label %503, label %506

; <label>:503:                                    ; preds = %500
  %504 = load i64*, i64** %27, align 8
  %505 = bitcast i64* %504 to i8*
  call void @free(i8* %505)
  store i64* null, i64** %27, align 8
  br label %506

; <label>:506:                                    ; preds = %503, %500
  %507 = load i8*, i8** %33, align 8
  %508 = icmp ne i8* %507, null
  br i1 %508, label %509, label %511

; <label>:509:                                    ; preds = %506
  %510 = load i8*, i8** %33, align 8
  call void @free(i8* %510)
  store i8* null, i8** %33, align 8
  br label %511

; <label>:511:                                    ; preds = %509, %506
  %512 = load i32, i32* @debug_disable_method, align 4
  %513 = and i32 %512, -3
  store i32 %513, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  %514 = load i32, i32* %18, align 4
  store i32 %514, i32* %9, align 4
  br label %706

; <label>:515:                                    ; preds = %422
  %516 = load i32, i32* @debug_enable, align 4
  %517 = icmp eq i32 %516, 1
  br i1 %517, label %518, label %533

; <label>:518:                                    ; preds = %515
  %519 = load i32, i32* @debug_disable_method, align 4
  %520 = icmp eq i32 %519, 0
  br i1 %520, label %521, label %533

; <label>:521:                                    ; preds = %518
  %522 = load i32, i32* @debug_disable_external, align 4
  %523 = icmp ne i32 %522, 1
  br i1 %523, label %524, label %533

; <label>:524:                                    ; preds = %521
  %525 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %526 = icmp ne %struct.__sFILE* %525, null
  br i1 %526, label %527, label %533

; <label>:527:                                    ; preds = %524
  %528 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %529 = load i8*, i8** %37, align 8
  %530 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %528, i8* getelementptr inbounds ([137 x i8], [137 x i8]* @.str.87, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 820, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %529)
  %531 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %532 = call i32 @fflush(%struct.__sFILE* %531)
  br label %533

; <label>:533:                                    ; preds = %527, %524, %521, %518, %515
  %534 = load i8*, i8** %29, align 8
  %535 = icmp ne i8* %534, null
  br i1 %535, label %536, label %538

; <label>:536:                                    ; preds = %533
  %537 = load i8*, i8** %29, align 8
  call void @free(i8* %537)
  store i8* null, i8** %29, align 8
  br label %538

; <label>:538:                                    ; preds = %536, %533
  %539 = load i64*, i64** %27, align 8
  %540 = icmp ne i64* %539, null
  br i1 %540, label %541, label %544

; <label>:541:                                    ; preds = %538
  %542 = load i64*, i64** %27, align 8
  %543 = bitcast i64* %542 to i8*
  call void @free(i8* %543)
  store i64* null, i64** %27, align 8
  br label %544

; <label>:544:                                    ; preds = %541, %538
  %545 = load i8*, i8** %33, align 8
  %546 = icmp ne i8* %545, null
  br i1 %546, label %547, label %549

; <label>:547:                                    ; preds = %544
  %548 = load i8*, i8** %33, align 8
  call void @free(i8* %548)
  store i8* null, i8** %33, align 8
  br label %549

; <label>:549:                                    ; preds = %547, %544
  %550 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %551 = icmp ne %struct.dir_t* %550, null
  br i1 %551, label %552, label %555

; <label>:552:                                    ; preds = %549
  %553 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %554 = bitcast %struct.dir_t* %553 to i8*
  call void @free(i8* %554)
  store %struct.dir_t* null, %struct.dir_t** %26, align 8
  br label %555

; <label>:555:                                    ; preds = %552, %549
  %556 = load i32, i32* @debug_disable_method, align 4
  %557 = and i32 %556, -3
  store i32 %557, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -20, i32* %9, align 4
  br label %706

; <label>:558:                                    ; preds = %416
  %559 = load i32, i32* %25, align 4
  %560 = icmp ne i32 %559, 0
  br i1 %560, label %561, label %630

; <label>:561:                                    ; preds = %558
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 828, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([32 x i8], [32 x i8]* @.str.88, i32 0, i32 0))
  %562 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %563 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %562, i32 0, i32 0
  %564 = bitcast %union.fname_u* %563 to [24 x i8]*
  %565 = getelementptr inbounds [24 x i8], [24 x i8]* %564, i32 0, i32 0
  call void @dbg2(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 829, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str.89, i32 0, i32 0), i8* %565)
  %566 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %567 = icmp eq %struct.dir_t** %566, null
  br i1 %567, label %568, label %577

; <label>:568:                                    ; preds = %561
  %569 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %570 = icmp ne %struct.dir_t* %569, null
  br i1 %570, label %571, label %576

; <label>:571:                                    ; preds = %568
  %572 = load %struct.dir_t*, %struct.dir_t** %13, align 8
  %573 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %574 = bitcast %struct.dir_t* %572 to i8*
  %575 = bitcast %struct.dir_t* %573 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %574, i8* align 8 %575, i64 64, i1 false)
  br label %576

; <label>:576:                                    ; preds = %571, %568
  br label %595

; <label>:577:                                    ; preds = %561
  %578 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %579 = icmp ne %struct.dir_t** %578, null
  br i1 %579, label %580, label %594

; <label>:580:                                    ; preds = %577
  %581 = call i8* @malloc(i64 64) #9
  %582 = bitcast i8* %581 to %struct.dir_t*
  %583 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  store %struct.dir_t* %582, %struct.dir_t** %583, align 8
  %584 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %585 = load %struct.dir_t*, %struct.dir_t** %584, align 8
  %586 = bitcast %struct.dir_t* %585 to i8*
  %587 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %588 = bitcast %struct.dir_t* %587 to i8*
  %589 = load %struct.dir_t**, %struct.dir_t*** %14, align 8
  %590 = load %struct.dir_t*, %struct.dir_t** %589, align 8
  %591 = bitcast %struct.dir_t* %590 to i8*
  %592 = call i64 @llvm.objectsize.i64.p0i8(i8* %591, i1 false, i1 true)
  %593 = call i8* @__memcpy_chk(i8* %586, i8* %588, i64 64, i64 %592) #7
  br label %594

; <label>:594:                                    ; preds = %580, %577
  store i32 1, i32* %18, align 4
  br label %595

; <label>:595:                                    ; preds = %594, %576
  %596 = load i64*, i64** %15, align 8
  %597 = icmp ne i64* %596, null
  br i1 %597, label %598, label %604

; <label>:598:                                    ; preds = %595
  %599 = load i64*, i64** %27, align 8
  %600 = load i64, i64* %24, align 8
  %601 = getelementptr inbounds i64, i64* %599, i64 %600
  %602 = load i64, i64* %601, align 8
  %603 = load i64*, i64** %15, align 8
  store i64 %602, i64* %603, align 8
  br label %604

; <label>:604:                                    ; preds = %598, %595
  %605 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %606 = icmp ne %struct.dir_t* %605, null
  br i1 %606, label %607, label %610

; <label>:607:                                    ; preds = %604
  %608 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %609 = bitcast %struct.dir_t* %608 to i8*
  call void @free(i8* %609)
  store %struct.dir_t* null, %struct.dir_t** %26, align 8
  br label %610

; <label>:610:                                    ; preds = %607, %604
  %611 = load i8*, i8** %29, align 8
  %612 = icmp ne i8* %611, null
  br i1 %612, label %613, label %615

; <label>:613:                                    ; preds = %610
  %614 = load i8*, i8** %29, align 8
  call void @free(i8* %614)
  store i8* null, i8** %29, align 8
  br label %615

; <label>:615:                                    ; preds = %613, %610
  %616 = load i64*, i64** %27, align 8
  %617 = icmp ne i64* %616, null
  br i1 %617, label %618, label %621

; <label>:618:                                    ; preds = %615
  %619 = load i64*, i64** %27, align 8
  %620 = bitcast i64* %619 to i8*
  call void @free(i8* %620)
  store i64* null, i64** %27, align 8
  br label %621

; <label>:621:                                    ; preds = %618, %615
  %622 = load i8*, i8** %33, align 8
  %623 = icmp ne i8* %622, null
  br i1 %623, label %624, label %626

; <label>:624:                                    ; preds = %621
  %625 = load i8*, i8** %33, align 8
  call void @free(i8* %625)
  store i8* null, i8** %33, align 8
  br label %626

; <label>:626:                                    ; preds = %624, %621
  %627 = load i32, i32* @debug_disable_method, align 4
  %628 = and i32 %627, -3
  store i32 %628, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  %629 = load i32, i32* %18, align 4
  store i32 %629, i32* %9, align 4
  br label %706

; <label>:630:                                    ; preds = %558
  br label %631

; <label>:631:                                    ; preds = %630
  %632 = load %struct.dir_t*, %struct.dir_t** %36, align 8
  %633 = bitcast %struct.dir_t* %30 to i8*
  %634 = bitcast %struct.dir_t* %632 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %633, i8* align 8 %634, i64 64, i1 false)
  %635 = load i64*, i64** %27, align 8
  %636 = load i64, i64* %24, align 8
  %637 = getelementptr inbounds i64, i64* %635, i64 %636
  %638 = load i64, i64* %637, align 8
  store i64 %638, i64* %31, align 8
  store i32 1, i32* %35, align 4
  %639 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %640 = icmp ne %struct.dir_t* %639, null
  br i1 %640, label %641, label %644

; <label>:641:                                    ; preds = %631
  %642 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %643 = bitcast %struct.dir_t* %642 to i8*
  call void @free(i8* %643)
  store %struct.dir_t* null, %struct.dir_t** %26, align 8
  br label %644

; <label>:644:                                    ; preds = %641, %631
  br label %649

; <label>:645:                                    ; preds = %407, %402, %390
  br label %646

; <label>:646:                                    ; preds = %645
  %647 = load i64, i64* %24, align 8
  %648 = add i64 %647, 1
  store i64 %648, i64* %24, align 8
  br label %386

; <label>:649:                                    ; preds = %644, %386
  %650 = load i8*, i8** %29, align 8
  %651 = icmp eq i8* %650, null
  %652 = zext i1 %651 to i32
  store i32 %652, i32* %32, align 4
  %653 = load i64*, i64** %27, align 8
  %654 = icmp ne i64* %653, null
  br i1 %654, label %655, label %658

; <label>:655:                                    ; preds = %649
  %656 = load i64*, i64** %27, align 8
  %657 = bitcast i64* %656 to i8*
  call void @free(i8* %657)
  store i64* null, i64** %27, align 8
  br label %658

; <label>:658:                                    ; preds = %655, %649
  %659 = load i8*, i8** %33, align 8
  %660 = icmp ne i8* %659, null
  br i1 %660, label %661, label %663

; <label>:661:                                    ; preds = %658
  %662 = load i8*, i8** %33, align 8
  call void @free(i8* %662)
  store i8* null, i8** %33, align 8
  br label %663

; <label>:663:                                    ; preds = %661, %658
  %664 = load i32, i32* %35, align 4
  %665 = icmp ne i32 %664, 0
  br i1 %665, label %675, label %666

; <label>:666:                                    ; preds = %663
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 861, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.90, i32 0, i32 0))
  %667 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %668 = icmp ne %struct.dir_t* %667, null
  br i1 %668, label %669, label %672

; <label>:669:                                    ; preds = %666
  %670 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %671 = bitcast %struct.dir_t* %670 to i8*
  call void @free(i8* %671)
  store %struct.dir_t* null, %struct.dir_t** %26, align 8
  br label %672

; <label>:672:                                    ; preds = %669, %666
  %673 = load i32, i32* @debug_disable_method, align 4
  %674 = and i32 %673, -3
  store i32 %674, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -2, i32* %9, align 4
  br label %706

; <label>:675:                                    ; preds = %663
  br label %676

; <label>:676:                                    ; preds = %675
  %677 = load i32, i32* %32, align 4
  %678 = icmp ne i32 %677, 0
  %679 = xor i1 %678, true
  br i1 %679, label %219, label %680

; <label>:680:                                    ; preds = %676
  %681 = load i32, i32* @debug_enable, align 4
  %682 = icmp eq i32 %681, 1
  br i1 %682, label %683, label %697

; <label>:683:                                    ; preds = %680
  %684 = load i32, i32* @debug_disable_method, align 4
  %685 = icmp eq i32 %684, 0
  br i1 %685, label %686, label %697

; <label>:686:                                    ; preds = %683
  %687 = load i32, i32* @debug_disable_external, align 4
  %688 = icmp ne i32 %687, 1
  br i1 %688, label %689, label %697

; <label>:689:                                    ; preds = %686
  %690 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %691 = icmp ne %struct.__sFILE* %690, null
  br i1 %691, label %692, label %697

; <label>:692:                                    ; preds = %689
  %693 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %694 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %693, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 868, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.75, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([58 x i8], [58 x i8]* @.str.91, i32 0, i32 0))
  %695 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %696 = call i32 @fflush(%struct.__sFILE* %695)
  br label %697

; <label>:697:                                    ; preds = %692, %689, %686, %683, %680
  %698 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %699 = icmp ne %struct.dir_t* %698, null
  br i1 %699, label %700, label %703

; <label>:700:                                    ; preds = %697
  %701 = load %struct.dir_t*, %struct.dir_t** %26, align 8
  %702 = bitcast %struct.dir_t* %701 to i8*
  call void @free(i8* %702)
  store %struct.dir_t* null, %struct.dir_t** %26, align 8
  br label %703

; <label>:703:                                    ; preds = %700, %697
  %704 = load i32, i32* @debug_disable_method, align 4
  %705 = and i32 %704, -3
  store i32 %705, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -5, i32* %9, align 4
  br label %706

; <label>:706:                                    ; preds = %703, %672, %626, %555, %511, %381, %311, %299, %204, %173, %82, %60
  %707 = load i32, i32* %9, align 4
  ret i32 %707
}

declare %struct.fdc_t* @fdc_find(i64) #1

declare %struct.pathc_t* @pathc_find_path(i8*) #1

declare i64 @strlen(i8*) #1

declare i8* @strdup(i8*) #1

declare i8* @path_first(i8*, i8**) #1

; Function Attrs: allocsize(0)
declare i8* @malloc(i64) #6

declare void @dbg2(i8*, i32, i8*, i8*, i8*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_newfile(i32, i8*, i32, i32, %struct.times_t*, %struct.dir_t**, i64*, %struct.dir_t**, i64*, i32) #0 {
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i8*, align 8
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca %struct.times_t*, align 8
  %17 = alloca %struct.dir_t**, align 8
  %18 = alloca i64*, align 8
  %19 = alloca %struct.dir_t**, align 8
  %20 = alloca i64*, align 8
  %21 = alloca i32, align 4
  %22 = alloca %struct.dir_t*, align 8
  %23 = alloca i64, align 8
  %24 = alloca i8*, align 8
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  %27 = alloca i64, align 8
  %28 = alloca %struct.dir_t, align 8
  %29 = alloca i32, align 4
  %30 = alloca i32, align 4
  %31 = alloca %struct.dir_t*, align 8
  %32 = alloca i64*, align 8
  %33 = alloca i64, align 8
  %34 = alloca i32, align 4
  %35 = alloca i64, align 8
  %36 = alloca i64, align 8
  %37 = alloca i64, align 8
  %38 = alloca i64, align 8
  %39 = alloca i64, align 8
  %40 = alloca i32, align 4
  %41 = alloca i64, align 8
  %42 = alloca i32, align 4
  %43 = alloca i32, align 4
  %44 = alloca i32, align 4
  %45 = alloca i32, align 4
  %46 = alloca i32, align 4
  %47 = alloca i32, align 4
  %48 = alloca %struct.pathc_t*, align 8
  %49 = alloca %struct.dir_t*, align 8
  store i32 %0, i32* %12, align 4
  store i8* %1, i8** %13, align 8
  store i32 %2, i32* %14, align 4
  store i32 %3, i32* %15, align 4
  store %struct.times_t* %4, %struct.times_t** %16, align 8
  store %struct.dir_t** %5, %struct.dir_t*** %17, align 8
  store i64* %6, i64** %18, align 8
  store %struct.dir_t** %7, %struct.dir_t*** %19, align 8
  store i64* %8, i64** %20, align 8
  store i32 %9, i32* %21, align 4
  %50 = load i32, i32* @debug_disable_method, align 4
  %51 = or i32 %50, 16
  store i32 %51, i32* @debug_disable_method, align 4
  call void @indent(i32 1)
  %52 = load i8*, i8** %13, align 8
  call void @dbg2(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 900, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.93, i32 0, i32 0), i8* %52)
  store i64 0, i64* %23, align 8
  store i8* null, i8** %24, align 8
  %53 = load i32, i32* %12, align 4
  %54 = load i8*, i8** %13, align 8
  %55 = call i32 @fat_find(i32 %53, i64 -1, i8* %54, %struct.dir_t* null, %struct.dir_t** %22, i64* %23, i32 1, i8** %24)
  store i32 %55, i32* %25, align 4
  %56 = load i32, i32* %25, align 4
  %57 = icmp eq i32 %56, 1
  %58 = zext i1 %57 to i32
  store i32 %58, i32* %26, align 4
  %59 = load i32, i32* %25, align 4
  %60 = icmp slt i32 %59, 0
  br i1 %60, label %61, label %98

; <label>:61:                                     ; preds = %10
  %62 = load i32, i32* %25, align 4
  %63 = icmp ne i32 %62, -2
  br i1 %63, label %64, label %98

; <label>:64:                                     ; preds = %61
  %65 = load i32, i32* %25, align 4
  %66 = icmp slt i32 %65, 0
  br i1 %66, label %67, label %97

; <label>:67:                                     ; preds = %64
  store i32 1, i32* @debug_enable, align 4
  %68 = load i32, i32* @debug_enable, align 4
  %69 = icmp eq i32 %68, 1
  br i1 %69, label %70, label %95

; <label>:70:                                     ; preds = %67
  %71 = load i32, i32* @debug_disable_method, align 4
  %72 = icmp eq i32 %71, 0
  br i1 %72, label %73, label %95

; <label>:73:                                     ; preds = %70
  %74 = load i32, i32* @debug_disable_external, align 4
  %75 = icmp ne i32 %74, 1
  br i1 %75, label %76, label %95

; <label>:76:                                     ; preds = %73
  %77 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %78 = icmp ne %struct.__sFILE* %77, null
  br i1 %78, label %79, label %95

; <label>:79:                                     ; preds = %76
  %80 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %81 = load i32, i32* %25, align 4
  %82 = load i32, i32* %25, align 4
  %83 = icmp slt i32 %82, 0
  br i1 %83, label %84, label %87

; <label>:84:                                     ; preds = %79
  %85 = load i32, i32* %25, align 4
  %86 = sub nsw i32 0, %85
  br label %89

; <label>:87:                                     ; preds = %79
  %88 = load i32, i32* %25, align 4
  br label %89

; <label>:89:                                     ; preds = %87, %84
  %90 = phi i32 [ %86, %84 ], [ %88, %87 ]
  %91 = call i8* @"\01_strerror"(i32 %90)
  %92 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %80, i8* getelementptr inbounds ([142 x i8], [142 x i8]* @.str.94, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 910, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %81, i8* %91)
  %93 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %94 = call i32 @fflush(%struct.__sFILE* %93)
  br label %95

; <label>:95:                                     ; preds = %89, %76, %73, %70, %67
  %96 = load i32, i32* %25, align 4
  store i32 %96, i32* %11, align 4
  br label %1022

; <label>:97:                                     ; preds = %64
  br label %98

; <label>:98:                                     ; preds = %97, %61, %10
  %99 = load i8*, i8** %24, align 8
  %100 = call i64 @strlen(i8* %99)
  store i64 %100, i64* %27, align 8
  %101 = load i64, i64* %27, align 8
  %102 = icmp ugt i64 %101, 24
  br i1 %102, label %103, label %135

; <label>:103:                                    ; preds = %98
  %104 = load i32, i32* @debug_enable, align 4
  %105 = icmp eq i32 %104, 1
  br i1 %105, label %106, label %121

; <label>:106:                                    ; preds = %103
  %107 = load i32, i32* @debug_disable_method, align 4
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %109, label %121

; <label>:109:                                    ; preds = %106
  %110 = load i32, i32* @debug_disable_external, align 4
  %111 = icmp ne i32 %110, 1
  br i1 %111, label %112, label %121

; <label>:112:                                    ; preds = %109
  %113 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %114 = icmp ne %struct.__sFILE* %113, null
  br i1 %114, label %115, label %121

; <label>:115:                                    ; preds = %112
  %116 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %117 = load i8*, i8** %24, align 8
  %118 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %116, i8* getelementptr inbounds ([170 x i8], [170 x i8]* @.str.95, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 917, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %117)
  %119 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %120 = call i32 @fflush(%struct.__sFILE* %119)
  br label %121

; <label>:121:                                    ; preds = %115, %112, %109, %106, %103
  %122 = load i8*, i8** %24, align 8
  %123 = icmp ne i8* %122, null
  br i1 %123, label %124, label %126

; <label>:124:                                    ; preds = %121
  %125 = load i8*, i8** %24, align 8
  call void @free(i8* %125)
  store i8* null, i8** %24, align 8
  br label %126

; <label>:126:                                    ; preds = %124, %121
  %127 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %128 = icmp ne %struct.dir_t* %127, null
  br i1 %128, label %129, label %132

; <label>:129:                                    ; preds = %126
  %130 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %131 = bitcast %struct.dir_t* %130 to i8*
  call void @free(i8* %131)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %132

; <label>:132:                                    ; preds = %129, %126
  %133 = load i32, i32* @debug_disable_method, align 4
  %134 = and i32 %133, -17
  store i32 %134, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -63, i32* %11, align 4
  br label %1022

; <label>:135:                                    ; preds = %98
  %136 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 0
  %137 = bitcast %union.fname_u* %136 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %137, i8 0, i64 24, i1 false)
  %138 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 1
  %139 = load %struct.times_t*, %struct.times_t** %16, align 8
  %140 = icmp eq %struct.times_t* %139, null
  br i1 %140, label %141, label %142

; <label>:141:                                    ; preds = %135
  call void (%struct.times_t*, ...) @gettimes(%struct.times_t* sret %138)
  br label %146

; <label>:142:                                    ; preds = %135
  %143 = load %struct.times_t*, %struct.times_t** %16, align 8
  %144 = bitcast %struct.times_t* %138 to i8*
  %145 = bitcast %struct.times_t* %143 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %144, i8* align 8 %145, i64 24, i1 false)
  br label %146

; <label>:146:                                    ; preds = %142, %141
  %147 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 2
  %148 = load i32, i32* %14, align 4
  store i32 %148, i32* %147, align 8
  %149 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  store i32 0, i32* %149, align 4
  %150 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 4
  %151 = load i32, i32* %15, align 4
  store i32 %151, i32* %150, align 8
  %152 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 5
  store i32 0, i32* %152, align 4
  %153 = call i32 @fat_find_free_block()
  store i32 %153, i32* %29, align 4
  %154 = load i32, i32* %21, align 4
  %155 = icmp ne i32 %154, 0
  br i1 %155, label %156, label %158

; <label>:156:                                    ; preds = %146
  %157 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  store i32 0, i32* %157, align 4
  br label %226

; <label>:158:                                    ; preds = %146
  %159 = load i32, i32* %29, align 4
  %160 = icmp eq i32 %159, -1
  br i1 %160, label %161, label %192

; <label>:161:                                    ; preds = %158
  %162 = load i32, i32* @debug_enable, align 4
  %163 = icmp eq i32 %162, 1
  br i1 %163, label %164, label %178

; <label>:164:                                    ; preds = %161
  %165 = load i32, i32* @debug_disable_method, align 4
  %166 = icmp eq i32 %165, 0
  br i1 %166, label %167, label %178

; <label>:167:                                    ; preds = %164
  %168 = load i32, i32* @debug_disable_external, align 4
  %169 = icmp ne i32 %168, 1
  br i1 %169, label %170, label %178

; <label>:170:                                    ; preds = %167
  %171 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %172 = icmp ne %struct.__sFILE* %171, null
  br i1 %172, label %173, label %178

; <label>:173:                                    ; preds = %170
  %174 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %175 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %174, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 940, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.96, i32 0, i32 0))
  %176 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %177 = call i32 @fflush(%struct.__sFILE* %176)
  br label %178

; <label>:178:                                    ; preds = %173, %170, %167, %164, %161
  %179 = load i8*, i8** %24, align 8
  %180 = icmp ne i8* %179, null
  br i1 %180, label %181, label %183

; <label>:181:                                    ; preds = %178
  %182 = load i8*, i8** %24, align 8
  call void @free(i8* %182)
  store i8* null, i8** %24, align 8
  br label %183

; <label>:183:                                    ; preds = %181, %178
  %184 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %185 = icmp ne %struct.dir_t* %184, null
  br i1 %185, label %186, label %189

; <label>:186:                                    ; preds = %183
  %187 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %188 = bitcast %struct.dir_t* %187 to i8*
  call void @free(i8* %188)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %189

; <label>:189:                                    ; preds = %186, %183
  %190 = load i32, i32* @debug_disable_method, align 4
  %191 = and i32 %190, -17
  store i32 %191, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:192:                                    ; preds = %158
  %193 = load i32, i32* @debug_enable, align 4
  %194 = icmp eq i32 %193, 1
  br i1 %194, label %195, label %211

; <label>:195:                                    ; preds = %192
  %196 = load i32, i32* @debug_disable_method, align 4
  %197 = icmp eq i32 %196, 0
  br i1 %197, label %198, label %211

; <label>:198:                                    ; preds = %195
  %199 = load i32, i32* @debug_disable_external, align 4
  %200 = icmp ne i32 %199, 1
  br i1 %200, label %201, label %211

; <label>:201:                                    ; preds = %198
  %202 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %203 = icmp ne %struct.__sFILE* %202, null
  br i1 %203, label %204, label %211

; <label>:204:                                    ; preds = %201
  %205 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %206 = load i8*, i8** %13, align 8
  %207 = load i32, i32* %29, align 4
  %208 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %205, i8* getelementptr inbounds ([152 x i8], [152 x i8]* @.str.97, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 946, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %206, i32 %207)
  %209 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %210 = call i32 @fflush(%struct.__sFILE* %209)
  br label %211

; <label>:211:                                    ; preds = %204, %201, %198, %195, %192
  %212 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %213 = load i32, i32* %29, align 4
  %214 = sext i32 %213 to i64
  %215 = getelementptr inbounds i32, i32* %212, i64 %214
  store i32 -2, i32* %215, align 4
  %216 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %217 = add nsw i64 %216, -1
  store i64 %217, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %218 = load i32, i32* %29, align 4
  %219 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  store i32 %218, i32* %219, align 4
  %220 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 0
  %221 = bitcast %union.fname_u* %220 to [24 x i8]*
  %222 = getelementptr inbounds [24 x i8], [24 x i8]* %221, i32 0, i32 0
  %223 = load i8*, i8** %24, align 8
  %224 = load i64, i64* %27, align 8
  %225 = call i8* @__memcpy_chk(i8* %222, i8* %223, i64 %224, i64 64) #7
  br label %226

; <label>:226:                                    ; preds = %211, %156
  %227 = load i8*, i8** %24, align 8
  %228 = icmp ne i8* %227, null
  br i1 %228, label %229, label %231

; <label>:229:                                    ; preds = %226
  %230 = load i8*, i8** %24, align 8
  call void @free(i8* %230)
  store i8* null, i8** %24, align 8
  br label %231

; <label>:231:                                    ; preds = %229, %226
  %232 = load i32, i32* %29, align 4
  store i32 %232, i32* %30, align 4
  %233 = load i32, i32* %12, align 4
  %234 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %235 = call i32 @fat_read_dir(i32 %233, %struct.dir_t* %234, %struct.dir_t** %31, i64** %32, i64* %33, i32* %34)
  store i32 %235, i32* %25, align 4
  store i64 -1, i64* %35, align 8
  store i64 -1, i64* %36, align 8
  %236 = load i32, i32* %34, align 4
  %237 = sext i32 %236 to i64
  store i64 %237, i64* %37, align 8
  br label %238

; <label>:238:                                    ; preds = %285, %231
  %239 = load i64, i64* %37, align 8
  %240 = load i64, i64* %33, align 8
  %241 = icmp ult i64 %239, %240
  br i1 %241, label %242, label %288

; <label>:242:                                    ; preds = %238
  %243 = load %struct.dir_t*, %struct.dir_t** %31, align 8
  %244 = load i64, i64* %37, align 8
  %245 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %243, i64 %244
  %246 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %245, i32 0, i32 3
  %247 = load i32, i32* %246, align 4
  %248 = icmp eq i32 %247, 0
  br i1 %248, label %260, label %249

; <label>:249:                                    ; preds = %242
  %250 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %251 = load %struct.dir_t*, %struct.dir_t** %31, align 8
  %252 = load i64, i64* %37, align 8
  %253 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %251, i64 %252
  %254 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %253, i32 0, i32 3
  %255 = load i32, i32* %254, align 4
  %256 = sext i32 %255 to i64
  %257 = getelementptr inbounds i32, i32* %250, i64 %256
  %258 = load i32, i32* %257, align 4
  %259 = icmp eq i32 %258, 0
  br i1 %259, label %260, label %284

; <label>:260:                                    ; preds = %249, %242
  %261 = load i64*, i64** %32, align 8
  %262 = load i64, i64* %37, align 8
  %263 = getelementptr inbounds i64, i64* %261, i64 %262
  %264 = load i64, i64* %263, align 8
  store i64 %264, i64* %35, align 8
  %265 = load i64, i64* %37, align 8
  store i64 %265, i64* %36, align 8
  %266 = load i32, i32* @debug_enable, align 4
  %267 = icmp eq i32 %266, 1
  br i1 %267, label %268, label %283

; <label>:268:                                    ; preds = %260
  %269 = load i32, i32* @debug_disable_method, align 4
  %270 = icmp eq i32 %269, 0
  br i1 %270, label %271, label %283

; <label>:271:                                    ; preds = %268
  %272 = load i32, i32* @debug_disable_external, align 4
  %273 = icmp ne i32 %272, 1
  br i1 %273, label %274, label %283

; <label>:274:                                    ; preds = %271
  %275 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %276 = icmp ne %struct.__sFILE* %275, null
  br i1 %276, label %277, label %283

; <label>:277:                                    ; preds = %274
  %278 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %279 = load i64, i64* %35, align 8
  %280 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %278, i8* getelementptr inbounds ([160 x i8], [160 x i8]* @.str.98, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 976, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %279)
  %281 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %282 = call i32 @fflush(%struct.__sFILE* %281)
  br label %283

; <label>:283:                                    ; preds = %277, %274, %271, %268, %260
  br label %288

; <label>:284:                                    ; preds = %249
  br label %285

; <label>:285:                                    ; preds = %284
  %286 = load i64, i64* %37, align 8
  %287 = add i64 %286, 1
  store i64 %287, i64* %37, align 8
  br label %238

; <label>:288:                                    ; preds = %283, %238
  %289 = load %struct.dir_t*, %struct.dir_t** %31, align 8
  %290 = icmp ne %struct.dir_t* %289, null
  br i1 %290, label %291, label %294

; <label>:291:                                    ; preds = %288
  %292 = load %struct.dir_t*, %struct.dir_t** %31, align 8
  %293 = bitcast %struct.dir_t* %292 to i8*
  call void @free(i8* %293)
  store %struct.dir_t* null, %struct.dir_t** %31, align 8
  br label %294

; <label>:294:                                    ; preds = %291, %288
  %295 = load i64*, i64** %32, align 8
  %296 = icmp ne i64* %295, null
  br i1 %296, label %297, label %300

; <label>:297:                                    ; preds = %294
  %298 = load i64*, i64** %32, align 8
  %299 = bitcast i64* %298 to i8*
  call void @free(i8* %299)
  store i64* null, i64** %32, align 8
  br label %300

; <label>:300:                                    ; preds = %297, %294
  %301 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %302 = zext i32 %301 to i64
  store i64 %302, i64* %38, align 8
  %303 = load i32, i32* %14, align 4
  %304 = zext i32 %303 to i64
  %305 = load i64, i64* %38, align 8
  %306 = call i64 @updiv(i64 %304, i64 %305)
  store i64 %306, i64* %39, align 8
  store i32 1, i32* %40, align 4
  %307 = load i64, i64* %35, align 8
  %308 = icmp ne i64 %307, -1
  br i1 %308, label %309, label %402

; <label>:309:                                    ; preds = %300
  %310 = load i32, i32* @debug_enable, align 4
  %311 = icmp eq i32 %310, 1
  br i1 %311, label %312, label %326

; <label>:312:                                    ; preds = %309
  %313 = load i32, i32* @debug_disable_method, align 4
  %314 = icmp eq i32 %313, 0
  br i1 %314, label %315, label %326

; <label>:315:                                    ; preds = %312
  %316 = load i32, i32* @debug_disable_external, align 4
  %317 = icmp ne i32 %316, 1
  br i1 %317, label %318, label %326

; <label>:318:                                    ; preds = %315
  %319 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %320 = icmp ne %struct.__sFILE* %319, null
  br i1 %320, label %321, label %326

; <label>:321:                                    ; preds = %318
  %322 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %323 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %322, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 998, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.100, i32 0, i32 0))
  %324 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %325 = call i32 @fflush(%struct.__sFILE* %324)
  br label %326

; <label>:326:                                    ; preds = %321, %318, %315, %312, %309
  %327 = load i32, i32* %12, align 4
  %328 = load i64, i64* %35, align 8
  %329 = call i32 @fat_write_entry(i32 %327, %struct.dir_t* %28, i64 %328)
  store i32 %329, i32* %25, align 4
  %330 = load i32, i32* %25, align 4
  %331 = icmp slt i32 %330, 0
  br i1 %331, label %332, label %362

; <label>:332:                                    ; preds = %326
  store i32 1, i32* @debug_enable, align 4
  %333 = load i32, i32* @debug_enable, align 4
  %334 = icmp eq i32 %333, 1
  br i1 %334, label %335, label %360

; <label>:335:                                    ; preds = %332
  %336 = load i32, i32* @debug_disable_method, align 4
  %337 = icmp eq i32 %336, 0
  br i1 %337, label %338, label %360

; <label>:338:                                    ; preds = %335
  %339 = load i32, i32* @debug_disable_external, align 4
  %340 = icmp ne i32 %339, 1
  br i1 %340, label %341, label %360

; <label>:341:                                    ; preds = %338
  %342 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %343 = icmp ne %struct.__sFILE* %342, null
  br i1 %343, label %344, label %360

; <label>:344:                                    ; preds = %341
  %345 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %346 = load i32, i32* %25, align 4
  %347 = load i32, i32* %25, align 4
  %348 = icmp slt i32 %347, 0
  br i1 %348, label %349, label %352

; <label>:349:                                    ; preds = %344
  %350 = load i32, i32* %25, align 4
  %351 = sub nsw i32 0, %350
  br label %354

; <label>:352:                                    ; preds = %344
  %353 = load i32, i32* %25, align 4
  br label %354

; <label>:354:                                    ; preds = %352, %349
  %355 = phi i32 [ %351, %349 ], [ %353, %352 ]
  %356 = call i8* @"\01_strerror"(i32 %355)
  %357 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %345, i8* getelementptr inbounds ([165 x i8], [165 x i8]* @.str.101, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1000, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %346, i8* %356)
  %358 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %359 = call i32 @fflush(%struct.__sFILE* %358)
  br label %360

; <label>:360:                                    ; preds = %354, %341, %338, %335, %332
  %361 = load i32, i32* %25, align 4
  store i32 %361, i32* %11, align 4
  br label %1022

; <label>:362:                                    ; preds = %326
  %363 = load i32, i32* @debug_enable, align 4
  %364 = icmp eq i32 %363, 1
  br i1 %364, label %365, label %392

; <label>:365:                                    ; preds = %362
  %366 = load i32, i32* @debug_disable_method, align 4
  %367 = icmp eq i32 %366, 0
  br i1 %367, label %368, label %392

; <label>:368:                                    ; preds = %365
  %369 = load i32, i32* @debug_disable_external, align 4
  %370 = icmp ne i32 %369, 1
  br i1 %370, label %371, label %392

; <label>:371:                                    ; preds = %368
  %372 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %373 = icmp ne %struct.__sFILE* %372, null
  br i1 %373, label %374, label %392

; <label>:374:                                    ; preds = %371
  %375 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %376 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %377 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %376, i32 0, i32 2
  %378 = load i32, i32* %377, align 8
  %379 = load i64, i64* %36, align 8
  %380 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %381 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %380, i32 0, i32 2
  %382 = load i32, i32* %381, align 8
  %383 = zext i32 %382 to i64
  %384 = udiv i64 %383, 64
  %385 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %386 = icmp eq %struct.dir_t* %385, getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4)
  %387 = zext i1 %386 to i64
  %388 = select i1 %386, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.103, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.104, i32 0, i32 0)
  %389 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %375, i8* getelementptr inbounds ([264 x i8], [264 x i8]* @.str.102, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1003, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %378, i64 %379, i64 %384, i8* %388)
  %390 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %391 = call i32 @fflush(%struct.__sFILE* %390)
  br label %392

; <label>:392:                                    ; preds = %374, %371, %368, %365, %362
  %393 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %394 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %393, i32 0, i32 2
  %395 = load i32, i32* %394, align 8
  %396 = zext i32 %395 to i64
  %397 = udiv i64 %396, 64
  %398 = load i64, i64* %36, align 8
  %399 = icmp ugt i64 %397, %398
  br i1 %399, label %400, label %401

; <label>:400:                                    ; preds = %392
  store i32 0, i32* %40, align 4
  br label %401

; <label>:401:                                    ; preds = %400, %392
  br label %811

; <label>:402:                                    ; preds = %300
  %403 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %404 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %403, i32 0, i32 2
  %405 = load i32, i32* %404, align 8
  %406 = zext i32 %405 to i64
  %407 = load i64, i64* %38, align 8
  %408 = sub i64 %407, 64
  %409 = icmp ule i64 %406, %408
  br i1 %409, label %410, label %512

; <label>:410:                                    ; preds = %402
  %411 = load i32, i32* @debug_enable, align 4
  %412 = icmp eq i32 %411, 1
  br i1 %412, label %413, label %427

; <label>:413:                                    ; preds = %410
  %414 = load i32, i32* @debug_disable_method, align 4
  %415 = icmp eq i32 %414, 0
  br i1 %415, label %416, label %427

; <label>:416:                                    ; preds = %413
  %417 = load i32, i32* @debug_disable_external, align 4
  %418 = icmp ne i32 %417, 1
  br i1 %418, label %419, label %427

; <label>:419:                                    ; preds = %416
  %420 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %421 = icmp ne %struct.__sFILE* %420, null
  br i1 %421, label %422, label %427

; <label>:422:                                    ; preds = %419
  %423 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %424 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %423, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1010, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.105, i32 0, i32 0))
  %425 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %426 = call i32 @fflush(%struct.__sFILE* %425)
  br label %427

; <label>:427:                                    ; preds = %422, %419, %416, %413, %410
  %428 = load i32, i32* %21, align 4
  %429 = icmp ne i32 %428, 0
  br i1 %429, label %464, label %430

; <label>:430:                                    ; preds = %427
  %431 = load i64, i64* %39, align 8
  %432 = call i32 @fat_has_free(i64 %431)
  %433 = icmp ne i32 %432, 0
  br i1 %433, label %464, label %434

; <label>:434:                                    ; preds = %430
  %435 = load i32, i32* @debug_enable, align 4
  %436 = icmp eq i32 %435, 1
  br i1 %436, label %437, label %451

; <label>:437:                                    ; preds = %434
  %438 = load i32, i32* @debug_disable_method, align 4
  %439 = icmp eq i32 %438, 0
  br i1 %439, label %440, label %451

; <label>:440:                                    ; preds = %437
  %441 = load i32, i32* @debug_disable_external, align 4
  %442 = icmp ne i32 %441, 1
  br i1 %442, label %443, label %451

; <label>:443:                                    ; preds = %440
  %444 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %445 = icmp ne %struct.__sFILE* %444, null
  br i1 %445, label %446, label %451

; <label>:446:                                    ; preds = %443
  %447 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %448 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %447, i8* getelementptr inbounds ([147 x i8], [147 x i8]* @.str.106, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1015, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.107, i32 0, i32 0))
  %449 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %450 = call i32 @fflush(%struct.__sFILE* %449)
  br label %451

; <label>:451:                                    ; preds = %446, %443, %440, %437, %434
  %452 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %453 = load i32, i32* %30, align 4
  %454 = sext i32 %453 to i64
  %455 = getelementptr inbounds i32, i32* %452, i64 %454
  store i32 0, i32* %455, align 4
  %456 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %457 = icmp ne %struct.dir_t* %456, null
  br i1 %457, label %458, label %461

; <label>:458:                                    ; preds = %451
  %459 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %460 = bitcast %struct.dir_t* %459 to i8*
  call void @free(i8* %460)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %461

; <label>:461:                                    ; preds = %458, %451
  %462 = load i32, i32* @debug_disable_method, align 4
  %463 = and i32 %462, -17
  store i32 %463, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:464:                                    ; preds = %430, %427
  %465 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %466 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %465, i32 0, i32 3
  %467 = load i32, i32* %466, align 4
  %468 = sext i32 %467 to i64
  %469 = load i64, i64* %38, align 8
  %470 = mul i64 %468, %469
  %471 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %472 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %471, i32 0, i32 2
  %473 = load i32, i32* %472, align 8
  %474 = zext i32 %473 to i64
  %475 = add i64 %470, %474
  store i64 %475, i64* %35, align 8
  %476 = load i32, i32* %12, align 4
  %477 = load i64, i64* %35, align 8
  %478 = call i32 @fat_write_entry(i32 %476, %struct.dir_t* %28, i64 %477)
  store i32 %478, i32* %25, align 4
  %479 = load i32, i32* %25, align 4
  %480 = icmp slt i32 %479, 0
  br i1 %480, label %481, label %511

; <label>:481:                                    ; preds = %464
  store i32 1, i32* @debug_enable, align 4
  %482 = load i32, i32* @debug_enable, align 4
  %483 = icmp eq i32 %482, 1
  br i1 %483, label %484, label %509

; <label>:484:                                    ; preds = %481
  %485 = load i32, i32* @debug_disable_method, align 4
  %486 = icmp eq i32 %485, 0
  br i1 %486, label %487, label %509

; <label>:487:                                    ; preds = %484
  %488 = load i32, i32* @debug_disable_external, align 4
  %489 = icmp ne i32 %488, 1
  br i1 %489, label %490, label %509

; <label>:490:                                    ; preds = %487
  %491 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %492 = icmp ne %struct.__sFILE* %491, null
  br i1 %492, label %493, label %509

; <label>:493:                                    ; preds = %490
  %494 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %495 = load i32, i32* %25, align 4
  %496 = load i32, i32* %25, align 4
  %497 = icmp slt i32 %496, 0
  br i1 %497, label %498, label %501

; <label>:498:                                    ; preds = %493
  %499 = load i32, i32* %25, align 4
  %500 = sub nsw i32 0, %499
  br label %503

; <label>:501:                                    ; preds = %493
  %502 = load i32, i32* %25, align 4
  br label %503

; <label>:503:                                    ; preds = %501, %498
  %504 = phi i32 [ %500, %498 ], [ %502, %501 ]
  %505 = call i8* @"\01_strerror"(i32 %504)
  %506 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %494, i8* getelementptr inbounds ([165 x i8], [165 x i8]* @.str.101, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1025, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %495, i8* %505)
  %507 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %508 = call i32 @fflush(%struct.__sFILE* %507)
  br label %509

; <label>:509:                                    ; preds = %503, %490, %487, %484, %481
  %510 = load i32, i32* %25, align 4
  store i32 %510, i32* %11, align 4
  br label %1022

; <label>:511:                                    ; preds = %464
  br label %810

; <label>:512:                                    ; preds = %402
  %513 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %514 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %513, i32 0, i32 2
  %515 = load i32, i32* %514, align 8
  %516 = zext i32 %515 to i64
  store i64 %516, i64* %41, align 8
  %517 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %518 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %517, i32 0, i32 3
  %519 = load i32, i32* %518, align 4
  store i32 %519, i32* %42, align 4
  %520 = load i32, i32* %42, align 4
  %521 = sext i32 %520 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1033, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.108, i32 0, i32 0), i64 %521)
  store i32 0, i32* %43, align 4
  br label %522

; <label>:522:                                    ; preds = %541, %512
  %523 = load i64, i64* %38, align 8
  %524 = load i64, i64* %41, align 8
  %525 = icmp ult i64 %523, %524
  br i1 %525, label %526, label %542

; <label>:526:                                    ; preds = %522
  %527 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %528 = load i32, i32* %42, align 4
  %529 = sext i32 %528 to i64
  %530 = getelementptr inbounds i32, i32* %527, i64 %529
  %531 = load i32, i32* %530, align 4
  store i32 %531, i32* %42, align 4
  %532 = load i64, i64* %38, align 8
  %533 = load i64, i64* %41, align 8
  %534 = sub i64 %533, %532
  store i64 %534, i64* %41, align 8
  %535 = load i32, i32* %43, align 4
  %536 = add nsw i32 %535, 1
  store i32 %536, i32* %43, align 4
  %537 = icmp sle i32 %536, 4
  br i1 %537, label %538, label %541

; <label>:538:                                    ; preds = %526
  %539 = load i32, i32* %42, align 4
  %540 = sext i32 %539 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1039, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.109, i32 0, i32 0), i64 %540)
  br label %541

; <label>:541:                                    ; preds = %538, %526
  br label %522

; <label>:542:                                    ; preds = %522
  %543 = load i32, i32* %43, align 4
  %544 = icmp sgt i32 %543, 4
  br i1 %544, label %545, label %564

; <label>:545:                                    ; preds = %542
  %546 = load i32, i32* @debug_enable, align 4
  %547 = icmp eq i32 %546, 1
  br i1 %547, label %548, label %563

; <label>:548:                                    ; preds = %545
  %549 = load i32, i32* @debug_disable_method, align 4
  %550 = icmp eq i32 %549, 0
  br i1 %550, label %551, label %563

; <label>:551:                                    ; preds = %548
  %552 = load i32, i32* @debug_disable_external, align 4
  %553 = icmp ne i32 %552, 1
  br i1 %553, label %554, label %563

; <label>:554:                                    ; preds = %551
  %555 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %556 = icmp ne %struct.__sFILE* %555, null
  br i1 %556, label %557, label %563

; <label>:557:                                    ; preds = %554
  %558 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %559 = load i32, i32* %43, align 4
  %560 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %558, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.110, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1043, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %559)
  %561 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %562 = call i32 @fflush(%struct.__sFILE* %561)
  br label %563

; <label>:563:                                    ; preds = %557, %554, %551, %548, %545
  br label %564

; <label>:564:                                    ; preds = %563, %542
  %565 = load i32, i32* @debug_enable, align 4
  %566 = icmp eq i32 %565, 1
  br i1 %566, label %567, label %586

; <label>:567:                                    ; preds = %564
  %568 = load i32, i32* @debug_disable_method, align 4
  %569 = icmp eq i32 %568, 0
  br i1 %569, label %570, label %586

; <label>:570:                                    ; preds = %567
  %571 = load i32, i32* @debug_disable_external, align 4
  %572 = icmp ne i32 %571, 1
  br i1 %572, label %573, label %586

; <label>:573:                                    ; preds = %570
  %574 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %575 = icmp ne %struct.__sFILE* %574, null
  br i1 %575, label %576, label %586

; <label>:576:                                    ; preds = %573
  %577 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %578 = load i64, i64* %38, align 8
  %579 = load i64, i64* %41, align 8
  %580 = load i64, i64* %38, align 8
  %581 = sub i64 %580, 64
  %582 = load i64, i64* %41, align 8
  %583 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %577, i8* getelementptr inbounds ([228 x i8], [228 x i8]* @.str.111, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1047, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %578, i64 64, i64 %579, i64 %581, i64 %582)
  %584 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %585 = call i32 @fflush(%struct.__sFILE* %584)
  br label %586

; <label>:586:                                    ; preds = %576, %573, %570, %567, %564
  %587 = load i64, i64* %38, align 8
  %588 = sub i64 %587, 64
  %589 = load i64, i64* %41, align 8
  %590 = icmp ult i64 %588, %589
  br i1 %590, label %591, label %749

; <label>:591:                                    ; preds = %586
  %592 = load i32, i32* @debug_enable, align 4
  %593 = icmp eq i32 %592, 1
  br i1 %593, label %594, label %608

; <label>:594:                                    ; preds = %591
  %595 = load i32, i32* @debug_disable_method, align 4
  %596 = icmp eq i32 %595, 0
  br i1 %596, label %597, label %608

; <label>:597:                                    ; preds = %594
  %598 = load i32, i32* @debug_disable_external, align 4
  %599 = icmp ne i32 %598, 1
  br i1 %599, label %600, label %608

; <label>:600:                                    ; preds = %597
  %601 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %602 = icmp ne %struct.__sFILE* %601, null
  br i1 %602, label %603, label %608

; <label>:603:                                    ; preds = %600
  %604 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %605 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %604, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1052, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.112, i32 0, i32 0))
  %606 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %607 = call i32 @fflush(%struct.__sFILE* %606)
  br label %608

; <label>:608:                                    ; preds = %603, %600, %597, %594, %591
  store i32 0, i32* %44, align 4
  %609 = load i32, i32* %21, align 4
  %610 = icmp ne i32 %609, 0
  br i1 %610, label %621, label %611

; <label>:611:                                    ; preds = %608
  %612 = load i64, i64* %39, align 8
  %613 = add i64 2, %612
  %614 = call i32 @fat_has_free(i64 %613)
  %615 = icmp ne i32 %614, 0
  br i1 %615, label %621, label %616

; <label>:616:                                    ; preds = %611
  %617 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %618 = load i32, i32* %30, align 4
  %619 = sext i32 %618 to i64
  %620 = getelementptr inbounds i32, i32* %617, i64 %619
  store i32 0, i32* %620, align 4
  store i32 1, i32* %44, align 4
  br label %629

; <label>:621:                                    ; preds = %611, %608
  %622 = load i32, i32* %21, align 4
  %623 = icmp ne i32 %622, 0
  br i1 %623, label %624, label %628

; <label>:624:                                    ; preds = %621
  %625 = call i32 @fat_has_free(i64 1)
  %626 = icmp ne i32 %625, 0
  br i1 %626, label %628, label %627

; <label>:627:                                    ; preds = %624
  store i32 1, i32* %44, align 4
  br label %628

; <label>:628:                                    ; preds = %627, %624, %621
  br label %629

; <label>:629:                                    ; preds = %628, %616
  %630 = load i32, i32* %44, align 4
  %631 = icmp ne i32 %630, 0
  br i1 %631, label %632, label %660

; <label>:632:                                    ; preds = %629
  %633 = load i32, i32* @debug_enable, align 4
  %634 = icmp eq i32 %633, 1
  br i1 %634, label %635, label %651

; <label>:635:                                    ; preds = %632
  %636 = load i32, i32* @debug_disable_method, align 4
  %637 = icmp eq i32 %636, 0
  br i1 %637, label %638, label %651

; <label>:638:                                    ; preds = %635
  %639 = load i32, i32* @debug_disable_external, align 4
  %640 = icmp ne i32 %639, 1
  br i1 %640, label %641, label %651

; <label>:641:                                    ; preds = %638
  %642 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %643 = icmp ne %struct.__sFILE* %642, null
  br i1 %643, label %644, label %651

; <label>:644:                                    ; preds = %641
  %645 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %646 = load i64, i64* %39, align 8
  %647 = add i64 2, %646
  %648 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %645, i8* getelementptr inbounds ([167 x i8], [167 x i8]* @.str.113, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1071, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %647, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.107, i32 0, i32 0))
  %649 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %650 = call i32 @fflush(%struct.__sFILE* %649)
  br label %651

; <label>:651:                                    ; preds = %644, %641, %638, %635, %632
  %652 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %653 = icmp ne %struct.dir_t* %652, null
  br i1 %653, label %654, label %657

; <label>:654:                                    ; preds = %651
  %655 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %656 = bitcast %struct.dir_t* %655 to i8*
  call void @free(i8* %656)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %657

; <label>:657:                                    ; preds = %654, %651
  %658 = load i32, i32* @debug_disable_method, align 4
  %659 = and i32 %658, -17
  store i32 %659, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:660:                                    ; preds = %629
  %661 = load i32, i32* %30, align 4
  %662 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %663 = load i32, i32* %42, align 4
  %664 = sext i32 %663 to i64
  %665 = getelementptr inbounds i32, i32* %662, i64 %664
  store i32 %661, i32* %665, align 4
  %666 = load i32, i32* %30, align 4
  store i32 %666, i32* %42, align 4
  %667 = load i32, i32* %21, align 4
  %668 = icmp ne i32 %667, 0
  br i1 %668, label %708, label %669

; <label>:669:                                    ; preds = %660
  %670 = call i32 @fat_find_free_block()
  store i32 %670, i32* %29, align 4
  %671 = load i32, i32* %29, align 4
  %672 = icmp eq i32 %671, -1
  br i1 %672, label %673, label %703

; <label>:673:                                    ; preds = %669
  %674 = load i32, i32* @debug_enable, align 4
  %675 = icmp eq i32 %674, 1
  br i1 %675, label %676, label %690

; <label>:676:                                    ; preds = %673
  %677 = load i32, i32* @debug_disable_method, align 4
  %678 = icmp eq i32 %677, 0
  br i1 %678, label %679, label %690

; <label>:679:                                    ; preds = %676
  %680 = load i32, i32* @debug_disable_external, align 4
  %681 = icmp ne i32 %680, 1
  br i1 %681, label %682, label %690

; <label>:682:                                    ; preds = %679
  %683 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %684 = icmp ne %struct.__sFILE* %683, null
  br i1 %684, label %685, label %690

; <label>:685:                                    ; preds = %682
  %686 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %687 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %686, i8* getelementptr inbounds ([147 x i8], [147 x i8]* @.str.106, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1086, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.107, i32 0, i32 0))
  %688 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %689 = call i32 @fflush(%struct.__sFILE* %688)
  br label %690

; <label>:690:                                    ; preds = %685, %682, %679, %676, %673
  %691 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %692 = load i32, i32* %30, align 4
  %693 = sext i32 %692 to i64
  %694 = getelementptr inbounds i32, i32* %691, i64 %693
  store i32 0, i32* %694, align 4
  %695 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %696 = icmp ne %struct.dir_t* %695, null
  br i1 %696, label %697, label %700

; <label>:697:                                    ; preds = %690
  %698 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %699 = bitcast %struct.dir_t* %698 to i8*
  call void @free(i8* %699)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %700

; <label>:700:                                    ; preds = %697, %690
  %701 = load i32, i32* @debug_disable_method, align 4
  %702 = and i32 %701, -17
  store i32 %702, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:703:                                    ; preds = %669
  %704 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %705 = add nsw i64 %704, -1
  store i64 %705, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %706 = load i32, i32* %29, align 4
  %707 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  store i32 %706, i32* %707, align 4
  br label %708

; <label>:708:                                    ; preds = %703, %660
  %709 = load i32, i32* %42, align 4
  %710 = sext i32 %709 to i64
  %711 = load i64, i64* %38, align 8
  %712 = mul i64 %710, %711
  store i64 %712, i64* %35, align 8
  %713 = load i32, i32* %12, align 4
  %714 = load i64, i64* %35, align 8
  %715 = call i32 @fat_write_entry(i32 %713, %struct.dir_t* %28, i64 %714)
  store i32 %715, i32* %25, align 4
  %716 = load i32, i32* %25, align 4
  %717 = icmp slt i32 %716, 0
  br i1 %717, label %718, label %748

; <label>:718:                                    ; preds = %708
  store i32 1, i32* @debug_enable, align 4
  %719 = load i32, i32* @debug_enable, align 4
  %720 = icmp eq i32 %719, 1
  br i1 %720, label %721, label %746

; <label>:721:                                    ; preds = %718
  %722 = load i32, i32* @debug_disable_method, align 4
  %723 = icmp eq i32 %722, 0
  br i1 %723, label %724, label %746

; <label>:724:                                    ; preds = %721
  %725 = load i32, i32* @debug_disable_external, align 4
  %726 = icmp ne i32 %725, 1
  br i1 %726, label %727, label %746

; <label>:727:                                    ; preds = %724
  %728 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %729 = icmp ne %struct.__sFILE* %728, null
  br i1 %729, label %730, label %746

; <label>:730:                                    ; preds = %727
  %731 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %732 = load i32, i32* %25, align 4
  %733 = load i32, i32* %25, align 4
  %734 = icmp slt i32 %733, 0
  br i1 %734, label %735, label %738

; <label>:735:                                    ; preds = %730
  %736 = load i32, i32* %25, align 4
  %737 = sub nsw i32 0, %736
  br label %740

; <label>:738:                                    ; preds = %730
  %739 = load i32, i32* %25, align 4
  br label %740

; <label>:740:                                    ; preds = %738, %735
  %741 = phi i32 [ %737, %735 ], [ %739, %738 ]
  %742 = call i8* @"\01_strerror"(i32 %741)
  %743 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %731, i8* getelementptr inbounds ([166 x i8], [166 x i8]* @.str.114, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1100, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %732, i8* %742)
  %744 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %745 = call i32 @fflush(%struct.__sFILE* %744)
  br label %746

; <label>:746:                                    ; preds = %740, %727, %724, %721, %718
  %747 = load i32, i32* %25, align 4
  store i32 %747, i32* %11, align 4
  br label %1022

; <label>:748:                                    ; preds = %708
  br label %809

; <label>:749:                                    ; preds = %586
  %750 = load i32, i32* @debug_enable, align 4
  %751 = icmp eq i32 %750, 1
  br i1 %751, label %752, label %766

; <label>:752:                                    ; preds = %749
  %753 = load i32, i32* @debug_disable_method, align 4
  %754 = icmp eq i32 %753, 0
  br i1 %754, label %755, label %766

; <label>:755:                                    ; preds = %752
  %756 = load i32, i32* @debug_disable_external, align 4
  %757 = icmp ne i32 %756, 1
  br i1 %757, label %758, label %766

; <label>:758:                                    ; preds = %755
  %759 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %760 = icmp ne %struct.__sFILE* %759, null
  br i1 %760, label %761, label %766

; <label>:761:                                    ; preds = %758
  %762 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %763 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %762, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1103, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.115, i32 0, i32 0))
  %764 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %765 = call i32 @fflush(%struct.__sFILE* %764)
  br label %766

; <label>:766:                                    ; preds = %761, %758, %755, %752, %749
  %767 = load i32, i32* %42, align 4
  %768 = sext i32 %767 to i64
  %769 = load i64, i64* %38, align 8
  %770 = mul i64 %768, %769
  %771 = load i64, i64* %41, align 8
  %772 = add i64 %770, %771
  store i64 %772, i64* %35, align 8
  %773 = load i32, i32* %12, align 4
  %774 = load i64, i64* %35, align 8
  %775 = call i32 @fat_write_entry(i32 %773, %struct.dir_t* %28, i64 %774)
  store i32 %775, i32* %25, align 4
  %776 = load i32, i32* %25, align 4
  %777 = icmp slt i32 %776, 0
  br i1 %777, label %778, label %808

; <label>:778:                                    ; preds = %766
  store i32 1, i32* @debug_enable, align 4
  %779 = load i32, i32* @debug_enable, align 4
  %780 = icmp eq i32 %779, 1
  br i1 %780, label %781, label %806

; <label>:781:                                    ; preds = %778
  %782 = load i32, i32* @debug_disable_method, align 4
  %783 = icmp eq i32 %782, 0
  br i1 %783, label %784, label %806

; <label>:784:                                    ; preds = %781
  %785 = load i32, i32* @debug_disable_external, align 4
  %786 = icmp ne i32 %785, 1
  br i1 %786, label %787, label %806

; <label>:787:                                    ; preds = %784
  %788 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %789 = icmp ne %struct.__sFILE* %788, null
  br i1 %789, label %790, label %806

; <label>:790:                                    ; preds = %787
  %791 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %792 = load i32, i32* %25, align 4
  %793 = load i32, i32* %25, align 4
  %794 = icmp slt i32 %793, 0
  br i1 %794, label %795, label %798

; <label>:795:                                    ; preds = %790
  %796 = load i32, i32* %25, align 4
  %797 = sub nsw i32 0, %796
  br label %800

; <label>:798:                                    ; preds = %790
  %799 = load i32, i32* %25, align 4
  br label %800

; <label>:800:                                    ; preds = %798, %795
  %801 = phi i32 [ %797, %795 ], [ %799, %798 ]
  %802 = call i8* @"\01_strerror"(i32 %801)
  %803 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %791, i8* getelementptr inbounds ([166 x i8], [166 x i8]* @.str.114, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1107, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %792, i8* %802)
  %804 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %805 = call i32 @fflush(%struct.__sFILE* %804)
  br label %806

; <label>:806:                                    ; preds = %800, %787, %784, %781, %778
  %807 = load i32, i32* %25, align 4
  store i32 %807, i32* %11, align 4
  br label %1022

; <label>:808:                                    ; preds = %766
  br label %809

; <label>:809:                                    ; preds = %808, %748
  br label %810

; <label>:810:                                    ; preds = %809, %511
  br label %811

; <label>:811:                                    ; preds = %810, %401
  %812 = load i32, i32* %40, align 4
  %813 = icmp ne i32 %812, 0
  br i1 %813, label %814, label %858

; <label>:814:                                    ; preds = %811
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1113, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.116, i32 0, i32 0))
  %815 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %816 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %815, i32 0, i32 2
  %817 = load i32, i32* %816, align 8
  %818 = zext i32 %817 to i64
  %819 = add i64 %818, 64
  %820 = trunc i64 %819 to i32
  store i32 %820, i32* %816, align 8
  %821 = load i32, i32* %12, align 4
  %822 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %823 = load i64, i64* %23, align 8
  %824 = call i32 @fat_write_entry(i32 %821, %struct.dir_t* %822, i64 %823)
  store i32 %824, i32* %25, align 4
  %825 = load i32, i32* %25, align 4
  %826 = icmp slt i32 %825, 0
  br i1 %826, label %827, label %857

; <label>:827:                                    ; preds = %814
  store i32 1, i32* @debug_enable, align 4
  %828 = load i32, i32* @debug_enable, align 4
  %829 = icmp eq i32 %828, 1
  br i1 %829, label %830, label %855

; <label>:830:                                    ; preds = %827
  %831 = load i32, i32* @debug_disable_method, align 4
  %832 = icmp eq i32 %831, 0
  br i1 %832, label %833, label %855

; <label>:833:                                    ; preds = %830
  %834 = load i32, i32* @debug_disable_external, align 4
  %835 = icmp ne i32 %834, 1
  br i1 %835, label %836, label %855

; <label>:836:                                    ; preds = %833
  %837 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %838 = icmp ne %struct.__sFILE* %837, null
  br i1 %838, label %839, label %855

; <label>:839:                                    ; preds = %836
  %840 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %841 = load i32, i32* %25, align 4
  %842 = load i32, i32* %25, align 4
  %843 = icmp slt i32 %842, 0
  br i1 %843, label %844, label %847

; <label>:844:                                    ; preds = %839
  %845 = load i32, i32* %25, align 4
  %846 = sub nsw i32 0, %845
  br label %849

; <label>:847:                                    ; preds = %839
  %848 = load i32, i32* %25, align 4
  br label %849

; <label>:849:                                    ; preds = %847, %844
  %850 = phi i32 [ %846, %844 ], [ %848, %847 ]
  %851 = call i8* @"\01_strerror"(i32 %850)
  %852 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %840, i8* getelementptr inbounds ([170 x i8], [170 x i8]* @.str.117, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1117, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %841, i8* %851)
  %853 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %854 = call i32 @fflush(%struct.__sFILE* %853)
  br label %855

; <label>:855:                                    ; preds = %849, %836, %833, %830, %827
  %856 = load i32, i32* %25, align 4
  store i32 %856, i32* %11, align 4
  br label %1022

; <label>:857:                                    ; preds = %814
  br label %858

; <label>:858:                                    ; preds = %857, %811
  %859 = load i32, i32* %21, align 4
  %860 = icmp ne i32 %859, 0
  br i1 %860, label %978, label %861

; <label>:861:                                    ; preds = %858
  %862 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  %863 = load i32, i32* %862, align 4
  store i32 %863, i32* %45, align 4
  %864 = load i32, i32* %14, align 4
  store i32 %864, i32* %46, align 4
  br label %865

; <label>:865:                                    ; preds = %919, %861
  %866 = load i64, i64* %38, align 8
  %867 = load i32, i32* %46, align 4
  %868 = zext i32 %867 to i64
  %869 = icmp ult i64 %866, %868
  br i1 %869, label %870, label %925

; <label>:870:                                    ; preds = %865
  %871 = call i32 @fat_find_free_block()
  store i32 %871, i32* %47, align 4
  %872 = load i32, i32* %47, align 4
  %873 = icmp eq i32 %872, -1
  br i1 %873, label %874, label %911

; <label>:874:                                    ; preds = %870
  %875 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %876 = load i32, i32* %45, align 4
  %877 = sext i32 %876 to i64
  %878 = getelementptr inbounds i32, i32* %875, i64 %877
  store i32 -2, i32* %878, align 4
  store i64 -1, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %879 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %880 = load i32, i32* %30, align 4
  %881 = sext i32 %880 to i64
  %882 = getelementptr inbounds i32, i32* %879, i64 %881
  store i32 0, i32* %882, align 4
  %883 = load i32, i32* @debug_enable, align 4
  %884 = icmp eq i32 %883, 1
  br i1 %884, label %885, label %899

; <label>:885:                                    ; preds = %874
  %886 = load i32, i32* @debug_disable_method, align 4
  %887 = icmp eq i32 %886, 0
  br i1 %887, label %888, label %899

; <label>:888:                                    ; preds = %885
  %889 = load i32, i32* @debug_disable_external, align 4
  %890 = icmp ne i32 %889, 1
  br i1 %890, label %891, label %899

; <label>:891:                                    ; preds = %888
  %892 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %893 = icmp ne %struct.__sFILE* %892, null
  br i1 %893, label %894, label %899

; <label>:894:                                    ; preds = %891
  %895 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %896 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %895, i8* getelementptr inbounds ([147 x i8], [147 x i8]* @.str.106, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1129, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.107, i32 0, i32 0))
  %897 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %898 = call i32 @fflush(%struct.__sFILE* %897)
  br label %899

; <label>:899:                                    ; preds = %894, %891, %888, %885, %874
  %900 = call i64 (...) @pathc_count_free()
  %901 = load i32, i32* %12, align 4
  %902 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %901, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %902)
  %903 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %904 = icmp ne %struct.dir_t* %903, null
  br i1 %904, label %905, label %908

; <label>:905:                                    ; preds = %899
  %906 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %907 = bitcast %struct.dir_t* %906 to i8*
  call void @free(i8* %907)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %908

; <label>:908:                                    ; preds = %905, %899
  %909 = load i32, i32* @debug_disable_method, align 4
  %910 = and i32 %909, -17
  store i32 %910, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:911:                                    ; preds = %870
  %912 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %913 = add nsw i64 %912, -1
  store i64 %913, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %914 = load i32, i32* %47, align 4
  %915 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %916 = load i32, i32* %45, align 4
  %917 = sext i32 %916 to i64
  %918 = getelementptr inbounds i32, i32* %915, i64 %917
  store i32 %914, i32* %918, align 4
  store i32 %914, i32* %45, align 4
  br label %919

; <label>:919:                                    ; preds = %911
  %920 = load i64, i64* %38, align 8
  %921 = load i32, i32* %46, align 4
  %922 = zext i32 %921 to i64
  %923 = sub i64 %922, %920
  %924 = trunc i64 %923 to i32
  store i32 %924, i32* %46, align 4
  br label %865

; <label>:925:                                    ; preds = %865
  %926 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %927 = load i32, i32* %45, align 4
  %928 = sext i32 %927 to i64
  %929 = getelementptr inbounds i32, i32* %926, i64 %928
  store i32 -2, i32* %929, align 4
  %930 = load i32, i32* @debug_enable, align 4
  %931 = icmp eq i32 %930, 1
  br i1 %931, label %932, label %950

; <label>:932:                                    ; preds = %925
  %933 = load i32, i32* @debug_disable_method, align 4
  %934 = icmp eq i32 %933, 0
  br i1 %934, label %935, label %950

; <label>:935:                                    ; preds = %932
  %936 = load i32, i32* @debug_disable_external, align 4
  %937 = icmp ne i32 %936, 1
  br i1 %937, label %938, label %950

; <label>:938:                                    ; preds = %935
  %939 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %940 = icmp ne %struct.__sFILE* %939, null
  br i1 %940, label %941, label %950

; <label>:941:                                    ; preds = %938
  %942 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %943 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 0
  %944 = bitcast %union.fname_u* %943 to [24 x i8]*
  %945 = getelementptr inbounds [24 x i8], [24 x i8]* %944, i32 0, i32 0
  %946 = load i64, i64* %35, align 8
  %947 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %942, i8* getelementptr inbounds ([222 x i8], [222 x i8]* @.str.118, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1143, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %945, i64 %946)
  %948 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %949 = call i32 @fflush(%struct.__sFILE* %948)
  br label %950

; <label>:950:                                    ; preds = %941, %938, %935, %932, %925
  %951 = load i8*, i8** %13, align 8
  %952 = load i64, i64* %35, align 8
  %953 = call i32 @pathc_insert(i8* %951, %struct.dir_t* byval align 8 %28, i64 %952, %struct.pathc_t** %48)
  store i32 %953, i32* %25, align 4
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1146, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.119, i32 0, i32 0))
  %954 = load i32, i32* %25, align 4
  %955 = icmp ne i32 %954, 0
  br i1 %955, label %956, label %963

; <label>:956:                                    ; preds = %950
  %957 = load i32, i32* %25, align 4
  %958 = icmp ne i32 %957, 1
  br i1 %958, label %959, label %963

; <label>:959:                                    ; preds = %956
  %960 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %961 = load i32, i32* %25, align 4
  %962 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %960, i8* getelementptr inbounds ([152 x i8], [152 x i8]* @.str.120, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1149, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %961)
  call void @quit(i32 1, i32 1)
  br label %977

; <label>:963:                                    ; preds = %956, %950
  %964 = load i32, i32* %21, align 4
  %965 = icmp ne i32 %964, 0
  br i1 %965, label %966, label %969

; <label>:966:                                    ; preds = %963
  %967 = load %struct.pathc_t*, %struct.pathc_t** %48, align 8
  %968 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %967, i32 0, i32 0
  store i8 0, i8* %968, align 8
  br label %969

; <label>:969:                                    ; preds = %966, %963
  %970 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  %971 = icmp ne %struct.dir_t** %970, null
  br i1 %971, label %972, label %976

; <label>:972:                                    ; preds = %969
  %973 = load %struct.pathc_t*, %struct.pathc_t** %48, align 8
  %974 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %973, i32 0, i32 2
  %975 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  store %struct.dir_t* %974, %struct.dir_t** %975, align 8
  br label %976

; <label>:976:                                    ; preds = %972, %969
  br label %977

; <label>:977:                                    ; preds = %976, %959
  br label %998

; <label>:978:                                    ; preds = %858
  %979 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  %980 = icmp ne %struct.dir_t** %979, null
  br i1 %980, label %981, label %997

; <label>:981:                                    ; preds = %978
  %982 = call i8* @malloc(i64 64) #9
  %983 = bitcast i8* %982 to %struct.dir_t*
  store %struct.dir_t* %983, %struct.dir_t** %49, align 8
  %984 = load %struct.dir_t*, %struct.dir_t** %49, align 8
  %985 = bitcast %struct.dir_t* %984 to i8*
  %986 = bitcast %struct.dir_t* %28 to i8*
  %987 = load %struct.dir_t*, %struct.dir_t** %49, align 8
  %988 = bitcast %struct.dir_t* %987 to i8*
  %989 = call i64 @llvm.objectsize.i64.p0i8(i8* %988, i1 false, i1 true)
  %990 = call i8* @__memcpy_chk(i8* %985, i8* %986, i64 64, i64 %989) #7
  %991 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  %992 = icmp ne %struct.dir_t** %991, null
  br i1 %992, label %993, label %996

; <label>:993:                                    ; preds = %981
  %994 = load %struct.dir_t*, %struct.dir_t** %49, align 8
  %995 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  store %struct.dir_t* %994, %struct.dir_t** %995, align 8
  br label %996

; <label>:996:                                    ; preds = %993, %981
  br label %997

; <label>:997:                                    ; preds = %996, %978
  br label %998

; <label>:998:                                    ; preds = %997, %977
  %999 = load i32, i32* %12, align 4
  %1000 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %999, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %1000)
  %1001 = load i64*, i64** %18, align 8
  %1002 = icmp ne i64* %1001, null
  br i1 %1002, label %1003, label %1006

; <label>:1003:                                   ; preds = %998
  %1004 = load i64, i64* %35, align 8
  %1005 = load i64*, i64** %18, align 8
  store i64 %1004, i64* %1005, align 8
  br label %1006

; <label>:1006:                                   ; preds = %1003, %998
  %1007 = load %struct.dir_t**, %struct.dir_t*** %19, align 8
  %1008 = icmp ne %struct.dir_t** %1007, null
  br i1 %1008, label %1009, label %1012

; <label>:1009:                                   ; preds = %1006
  %1010 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %1011 = load %struct.dir_t**, %struct.dir_t*** %19, align 8
  store %struct.dir_t* %1010, %struct.dir_t** %1011, align 8
  br label %1012

; <label>:1012:                                   ; preds = %1009, %1006
  %1013 = load i64*, i64** %20, align 8
  %1014 = icmp ne i64* %1013, null
  br i1 %1014, label %1015, label %1018

; <label>:1015:                                   ; preds = %1012
  %1016 = load i64, i64* %23, align 8
  %1017 = load i64*, i64** %20, align 8
  store i64 %1016, i64* %1017, align 8
  br label %1018

; <label>:1018:                                   ; preds = %1015, %1012
  %1019 = load i32, i32* @debug_disable_method, align 4
  %1020 = and i32 %1019, -17
  store i32 %1020, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  %1021 = load i32, i32* %26, align 4
  store i32 %1021, i32* %11, align 4
  br label %1022

; <label>:1022:                                   ; preds = %1018, %908, %855, %806, %746, %700, %657, %509, %461, %360, %189, %132, %95
  %1023 = load i32, i32* %11, align 4
  ret i32 %1023
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1) #2

declare void @gettimes(%struct.times_t* sret, ...) #1

declare i64 @pathc_count_free(...) #1

declare i32 @pathc_insert(i8*, %struct.dir_t* byval align 8, i64, %struct.pathc_t**) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_resize(i32, %struct.dir_t*, i64, i64) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca %struct.dir_t*, align 8
  %8 = alloca i64, align 8
  %9 = alloca i64, align 8
  %10 = alloca i64, align 8
  %11 = alloca i64, align 8
  %12 = alloca i64, align 8
  %13 = alloca i64, align 8
  %14 = alloca i32, align 4
  %15 = alloca i8*, align 8
  %16 = alloca i64, align 8
  %17 = alloca i32, align 4
  %18 = alloca i64, align 8
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %21 = alloca i64, align 8
  %22 = alloca i64, align 8
  %23 = alloca i32, align 4
  %24 = alloca i32, align 4
  %25 = alloca i64, align 8
  %26 = alloca i64, align 8
  %27 = alloca i64, align 8
  store i32 %0, i32* %6, align 4
  store %struct.dir_t* %1, %struct.dir_t** %7, align 8
  store i64 %2, i64* %8, align 8
  store i64 %3, i64* %9, align 8
  call void @indent(i32 1)
  %28 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %29 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 2
  %30 = load i32, i32* %29, align 8
  %31 = zext i32 %30 to i64
  %32 = load i64, i64* %9, align 8
  %33 = icmp eq i64 %31, %32
  br i1 %33, label %34, label %57

; <label>:34:                                     ; preds = %4
  %35 = load i32, i32* @debug_enable, align 4
  %36 = icmp eq i32 %35, 1
  br i1 %36, label %37, label %56

; <label>:37:                                     ; preds = %34
  %38 = load i32, i32* @debug_disable_method, align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %40, label %56

; <label>:40:                                     ; preds = %37
  %41 = load i32, i32* @debug_disable_external, align 4
  %42 = icmp ne i32 %41, 1
  br i1 %42, label %43, label %56

; <label>:43:                                     ; preds = %40
  %44 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %45 = icmp ne %struct.__sFILE* %44, null
  br i1 %45, label %46, label %56

; <label>:46:                                     ; preds = %43
  %47 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %48 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %49 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %48, i32 0, i32 0
  %50 = bitcast %union.fname_u* %49 to [24 x i8]*
  %51 = getelementptr inbounds [24 x i8], [24 x i8]* %50, i32 0, i32 0
  %52 = load i64, i64* %9, align 8
  %53 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %47, i8* getelementptr inbounds ([196 x i8], [196 x i8]* @.str.121, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1190, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %51, i64 %52)
  %54 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %55 = call i32 @fflush(%struct.__sFILE* %54)
  br label %56

; <label>:56:                                     ; preds = %46, %43, %40, %37, %34
  call void @indent(i32 -1)
  store i32 0, i32* %5, align 4
  br label %646

; <label>:57:                                     ; preds = %4
  %58 = load i64, i64* %9, align 8
  %59 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %60 = call i64 @fat_blocks_required(i64 %58, i32 %59)
  store i64 %60, i64* %11, align 8
  %61 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %62 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %61, i32 0, i32 2
  %63 = load i32, i32* %62, align 8
  %64 = zext i32 %63 to i64
  %65 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %66 = call i64 @fat_blocks_required(i64 %64, i32 %65)
  store i64 %66, i64* %12, align 8
  %67 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %68 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %67, i32 0, i32 3
  %69 = load i32, i32* %68, align 4
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %71, label %90

; <label>:71:                                     ; preds = %57
  %72 = load i32, i32* @debug_enable, align 4
  %73 = icmp eq i32 %72, 1
  br i1 %73, label %74, label %88

; <label>:74:                                     ; preds = %71
  %75 = load i32, i32* @debug_disable_method, align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %77, label %88

; <label>:77:                                     ; preds = %74
  %78 = load i32, i32* @debug_disable_external, align 4
  %79 = icmp ne i32 %78, 1
  br i1 %79, label %80, label %88

; <label>:80:                                     ; preds = %77
  %81 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %82 = icmp ne %struct.__sFILE* %81, null
  br i1 %82, label %83, label %88

; <label>:83:                                     ; preds = %80
  %84 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %85 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %84, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1200, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.123, i32 0, i32 0))
  %86 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %87 = call i32 @fflush(%struct.__sFILE* %86)
  br label %88

; <label>:88:                                     ; preds = %83, %80, %77, %74, %71
  %89 = load i64, i64* %12, align 8
  store i64 %89, i64* %10, align 8
  br label %95

; <label>:90:                                     ; preds = %57
  %91 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %92 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %91, i32 0, i32 3
  %93 = load i32, i32* %92, align 4
  %94 = call i64 @fat_chain_length(i32 %93)
  store i64 %94, i64* %10, align 8
  br label %95

; <label>:95:                                     ; preds = %90, %88
  %96 = load i64, i64* %10, align 8
  store i64 %96, i64* %13, align 8
  %97 = load i32, i32* @debug_enable, align 4
  %98 = icmp eq i32 %97, 1
  br i1 %98, label %99, label %123

; <label>:99:                                     ; preds = %95
  %100 = load i32, i32* @debug_disable_method, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %102, label %123

; <label>:102:                                    ; preds = %99
  %103 = load i32, i32* @debug_disable_external, align 4
  %104 = icmp ne i32 %103, 1
  br i1 %104, label %105, label %123

; <label>:105:                                    ; preds = %102
  %106 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %107 = icmp ne %struct.__sFILE* %106, null
  br i1 %107, label %108, label %123

; <label>:108:                                    ; preds = %105
  %109 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %110 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %111 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %110, i32 0, i32 0
  %112 = bitcast %union.fname_u* %111 to [24 x i8]*
  %113 = getelementptr inbounds [24 x i8], [24 x i8]* %112, i32 0, i32 0
  %114 = load i64, i64* %9, align 8
  %115 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %116 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %115, i32 0, i32 2
  %117 = load i32, i32* %116, align 8
  %118 = load i64, i64* %13, align 8
  %119 = load i64, i64* %11, align 8
  %120 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %109, i8* getelementptr inbounds ([346 x i8], [346 x i8]* @.str.124, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1210, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %113, i64 %114, i32 %117, i64 %118, i64 %119)
  %121 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %122 = call i32 @fflush(%struct.__sFILE* %121)
  br label %123

; <label>:123:                                    ; preds = %108, %105, %102, %99, %95
  %124 = load i64, i64* %9, align 8
  %125 = icmp eq i64 %124, 0
  br i1 %125, label %126, label %145

; <label>:126:                                    ; preds = %123
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1213, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.125, i32 0, i32 0))
  %127 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %128 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %127, i32 0, i32 3
  %129 = load i32, i32* %128, align 4
  %130 = call i64 @fat_forget(i32 %129)
  %131 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %132 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %133 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %132, i32 0, i32 3
  %134 = load i32, i32* %133, align 4
  %135 = sext i32 %134 to i64
  %136 = getelementptr inbounds i32, i32* %131, i64 %135
  store i32 -2, i32* %136, align 4
  %137 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %138 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %137, i32 0, i32 2
  store i32 0, i32* %138, align 8
  %139 = load i32, i32* %6, align 4
  %140 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %141 = load i64, i64* %8, align 8
  %142 = call i32 @fat_write_entry(i32 %139, %struct.dir_t* %140, i64 %141)
  %143 = load i32, i32* %6, align 4
  %144 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %143, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %144)
  br label %628

; <label>:145:                                    ; preds = %123
  %146 = load i64, i64* %13, align 8
  %147 = load i64, i64* %11, align 8
  %148 = icmp eq i64 %146, %147
  br i1 %148, label %149, label %277

; <label>:149:                                    ; preds = %145
  %150 = load i32, i32* @debug_enable, align 4
  %151 = icmp eq i32 %150, 1
  br i1 %151, label %152, label %167

; <label>:152:                                    ; preds = %149
  %153 = load i32, i32* @debug_disable_method, align 4
  %154 = icmp eq i32 %153, 0
  br i1 %154, label %155, label %167

; <label>:155:                                    ; preds = %152
  %156 = load i32, i32* @debug_disable_external, align 4
  %157 = icmp ne i32 %156, 1
  br i1 %157, label %158, label %167

; <label>:158:                                    ; preds = %155
  %159 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %160 = icmp ne %struct.__sFILE* %159, null
  br i1 %160, label %161, label %167

; <label>:161:                                    ; preds = %158
  %162 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %163 = load i64, i64* %13, align 8
  %164 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %162, i8* getelementptr inbounds ([136 x i8], [136 x i8]* @.str.126, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1223, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %163)
  %165 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %166 = call i32 @fflush(%struct.__sFILE* %165)
  br label %167

; <label>:167:                                    ; preds = %161, %158, %155, %152, %149
  %168 = load i64, i64* %9, align 8
  %169 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %170 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %169, i32 0, i32 2
  %171 = load i32, i32* %170, align 8
  %172 = zext i32 %171 to i64
  %173 = icmp slt i64 %168, %172
  br i1 %173, label %174, label %213

; <label>:174:                                    ; preds = %167
  %175 = load i32, i32* %6, align 4
  %176 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %177 = load i64, i64* %9, align 8
  %178 = trunc i64 %177 to i32
  %179 = call i32 @fat_zero_out_free(i32 %175, %struct.dir_t* %176, i32 %178)
  store i32 %179, i32* %14, align 4
  %180 = load i32, i32* %14, align 4
  %181 = icmp slt i32 %180, 0
  br i1 %181, label %182, label %212

; <label>:182:                                    ; preds = %174
  store i32 1, i32* @debug_enable, align 4
  %183 = load i32, i32* @debug_enable, align 4
  %184 = icmp eq i32 %183, 1
  br i1 %184, label %185, label %210

; <label>:185:                                    ; preds = %182
  %186 = load i32, i32* @debug_disable_method, align 4
  %187 = icmp eq i32 %186, 0
  br i1 %187, label %188, label %210

; <label>:188:                                    ; preds = %185
  %189 = load i32, i32* @debug_disable_external, align 4
  %190 = icmp ne i32 %189, 1
  br i1 %190, label %191, label %210

; <label>:191:                                    ; preds = %188
  %192 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %193 = icmp ne %struct.__sFILE* %192, null
  br i1 %193, label %194, label %210

; <label>:194:                                    ; preds = %191
  %195 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %196 = load i32, i32* %14, align 4
  %197 = load i32, i32* %14, align 4
  %198 = icmp slt i32 %197, 0
  br i1 %198, label %199, label %202

; <label>:199:                                    ; preds = %194
  %200 = load i32, i32* %14, align 4
  %201 = sub nsw i32 0, %200
  br label %204

; <label>:202:                                    ; preds = %194
  %203 = load i32, i32* %14, align 4
  br label %204

; <label>:204:                                    ; preds = %202, %199
  %205 = phi i32 [ %201, %199 ], [ %203, %202 ]
  %206 = call i8* @"\01_strerror"(i32 %205)
  %207 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %195, i8* getelementptr inbounds ([151 x i8], [151 x i8]* @.str.127, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1230, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %196, i8* %206)
  %208 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %209 = call i32 @fflush(%struct.__sFILE* %208)
  br label %210

; <label>:210:                                    ; preds = %204, %191, %188, %185, %182
  call void @indent(i32 -1)
  %211 = load i32, i32* %14, align 4
  store i32 %211, i32* %5, align 4
  br label %646

; <label>:212:                                    ; preds = %174
  br label %213

; <label>:213:                                    ; preds = %212, %167
  %214 = load i32, i32* @debug_enable, align 4
  %215 = icmp eq i32 %214, 1
  br i1 %215, label %216, label %235

; <label>:216:                                    ; preds = %213
  %217 = load i32, i32* @debug_disable_method, align 4
  %218 = icmp eq i32 %217, 0
  br i1 %218, label %219, label %235

; <label>:219:                                    ; preds = %216
  %220 = load i32, i32* @debug_disable_external, align 4
  %221 = icmp ne i32 %220, 1
  br i1 %221, label %222, label %235

; <label>:222:                                    ; preds = %219
  %223 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %224 = icmp ne %struct.__sFILE* %223, null
  br i1 %224, label %225, label %235

; <label>:225:                                    ; preds = %222
  %226 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %227 = load i64, i64* %8, align 8
  %228 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %229 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %228, i32 0, i32 2
  %230 = load i32, i32* %229, align 8
  %231 = load i64, i64* %9, align 8
  %232 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %226, i8* getelementptr inbounds ([210 x i8], [210 x i8]* @.str.128, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1234, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %227, i32 %230, i64 %231)
  %233 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %234 = call i32 @fflush(%struct.__sFILE* %233)
  br label %235

; <label>:235:                                    ; preds = %225, %222, %219, %216, %213
  %236 = load i64, i64* %9, align 8
  %237 = trunc i64 %236 to i32
  %238 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %239 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %238, i32 0, i32 2
  store i32 %237, i32* %239, align 8
  %240 = load i32, i32* %6, align 4
  %241 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %242 = load i64, i64* %8, align 8
  %243 = call i32 @fat_write_entry(i32 %240, %struct.dir_t* %241, i64 %242)
  store i32 %243, i32* %14, align 4
  %244 = load i32, i32* %14, align 4
  %245 = icmp slt i32 %244, 0
  br i1 %245, label %246, label %276

; <label>:246:                                    ; preds = %235
  store i32 1, i32* @debug_enable, align 4
  %247 = load i32, i32* @debug_enable, align 4
  %248 = icmp eq i32 %247, 1
  br i1 %248, label %249, label %274

; <label>:249:                                    ; preds = %246
  %250 = load i32, i32* @debug_disable_method, align 4
  %251 = icmp eq i32 %250, 0
  br i1 %251, label %252, label %274

; <label>:252:                                    ; preds = %249
  %253 = load i32, i32* @debug_disable_external, align 4
  %254 = icmp ne i32 %253, 1
  br i1 %254, label %255, label %274

; <label>:255:                                    ; preds = %252
  %256 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %257 = icmp ne %struct.__sFILE* %256, null
  br i1 %257, label %258, label %274

; <label>:258:                                    ; preds = %255
  %259 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %260 = load i32, i32* %14, align 4
  %261 = load i32, i32* %14, align 4
  %262 = icmp slt i32 %261, 0
  br i1 %262, label %263, label %266

; <label>:263:                                    ; preds = %258
  %264 = load i32, i32* %14, align 4
  %265 = sub nsw i32 0, %264
  br label %268

; <label>:266:                                    ; preds = %258
  %267 = load i32, i32* %14, align 4
  br label %268

; <label>:268:                                    ; preds = %266, %263
  %269 = phi i32 [ %265, %263 ], [ %267, %266 ]
  %270 = call i8* @"\01_strerror"(i32 %269)
  %271 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %259, i8* getelementptr inbounds ([149 x i8], [149 x i8]* @.str.129, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1237, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %260, i8* %270)
  %272 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %273 = call i32 @fflush(%struct.__sFILE* %272)
  br label %274

; <label>:274:                                    ; preds = %268, %255, %252, %249, %246
  call void @indent(i32 -1)
  %275 = load i32, i32* %14, align 4
  store i32 %275, i32* %5, align 4
  br label %646

; <label>:276:                                    ; preds = %235
  br label %627

; <label>:277:                                    ; preds = %145
  %278 = load i64, i64* %11, align 8
  %279 = load i64, i64* %13, align 8
  %280 = icmp ult i64 %278, %279
  br i1 %280, label %281, label %452

; <label>:281:                                    ; preds = %277
  %282 = load i32, i32* @debug_enable, align 4
  %283 = icmp eq i32 %282, 1
  br i1 %283, label %284, label %300

; <label>:284:                                    ; preds = %281
  %285 = load i32, i32* @debug_disable_method, align 4
  %286 = icmp eq i32 %285, 0
  br i1 %286, label %287, label %300

; <label>:287:                                    ; preds = %284
  %288 = load i32, i32* @debug_disable_external, align 4
  %289 = icmp ne i32 %288, 1
  br i1 %289, label %290, label %300

; <label>:290:                                    ; preds = %287
  %291 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %292 = icmp ne %struct.__sFILE* %291, null
  br i1 %292, label %293, label %300

; <label>:293:                                    ; preds = %290
  %294 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %295 = load i64, i64* %13, align 8
  %296 = load i64, i64* %11, align 8
  %297 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %294, i8* getelementptr inbounds ([152 x i8], [152 x i8]* @.str.130, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1241, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %295, i64 %296)
  %298 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %299 = call i32 @fflush(%struct.__sFILE* %298)
  br label %300

; <label>:300:                                    ; preds = %293, %290, %287, %284, %281
  %301 = load i64, i64* %13, align 8
  %302 = call i8* @llvm.stacksave()
  store i8* %302, i8** %15, align 8
  %303 = alloca i32, i64 %301, align 16
  store i64 %301, i64* %16, align 8
  %304 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %305 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %304, i32 0, i32 3
  %306 = load i32, i32* %305, align 4
  store i32 %306, i32* %17, align 4
  store i64 0, i64* %18, align 8
  br label %307

; <label>:307:                                    ; preds = %324, %300
  %308 = load i64, i64* %18, align 8
  %309 = load i64, i64* %13, align 8
  %310 = icmp ult i64 %308, %309
  br i1 %310, label %311, label %327

; <label>:311:                                    ; preds = %307
  %312 = load i32, i32* %17, align 4
  %313 = load i64, i64* %18, align 8
  %314 = getelementptr inbounds i32, i32* %303, i64 %313
  store i32 %312, i32* %314, align 4
  %315 = load i64, i64* %18, align 8
  %316 = getelementptr inbounds i32, i32* %303, i64 %315
  %317 = load i32, i32* %316, align 4
  %318 = sext i32 %317 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1247, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.131, i32 0, i32 0), i64 %318)
  %319 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %320 = load i32, i32* %17, align 4
  %321 = sext i32 %320 to i64
  %322 = getelementptr inbounds i32, i32* %319, i64 %321
  %323 = load i32, i32* %322, align 4
  store i32 %323, i32* %17, align 4
  br label %324

; <label>:324:                                    ; preds = %311
  %325 = load i64, i64* %18, align 8
  %326 = add i64 %325, 1
  store i64 %326, i64* %18, align 8
  br label %307

; <label>:327:                                    ; preds = %307
  %328 = load i32, i32* %6, align 4
  %329 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %330 = load i64, i64* %9, align 8
  %331 = trunc i64 %330 to i32
  %332 = call i32 @fat_zero_out_free(i32 %328, %struct.dir_t* %329, i32 %331)
  store i32 %332, i32* %19, align 4
  %333 = load i32, i32* %19, align 4
  %334 = icmp slt i32 %333, 0
  br i1 %334, label %335, label %365

; <label>:335:                                    ; preds = %327
  store i32 1, i32* @debug_enable, align 4
  %336 = load i32, i32* @debug_enable, align 4
  %337 = icmp eq i32 %336, 1
  br i1 %337, label %338, label %363

; <label>:338:                                    ; preds = %335
  %339 = load i32, i32* @debug_disable_method, align 4
  %340 = icmp eq i32 %339, 0
  br i1 %340, label %341, label %363

; <label>:341:                                    ; preds = %338
  %342 = load i32, i32* @debug_disable_external, align 4
  %343 = icmp ne i32 %342, 1
  br i1 %343, label %344, label %363

; <label>:344:                                    ; preds = %341
  %345 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %346 = icmp ne %struct.__sFILE* %345, null
  br i1 %346, label %347, label %363

; <label>:347:                                    ; preds = %344
  %348 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %349 = load i32, i32* %19, align 4
  %350 = load i32, i32* %19, align 4
  %351 = icmp slt i32 %350, 0
  br i1 %351, label %352, label %355

; <label>:352:                                    ; preds = %347
  %353 = load i32, i32* %19, align 4
  %354 = sub nsw i32 0, %353
  br label %357

; <label>:355:                                    ; preds = %347
  %356 = load i32, i32* %19, align 4
  br label %357

; <label>:357:                                    ; preds = %355, %352
  %358 = phi i32 [ %354, %352 ], [ %356, %355 ]
  %359 = call i8* @"\01_strerror"(i32 %358)
  %360 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %348, i8* getelementptr inbounds ([151 x i8], [151 x i8]* @.str.127, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1253, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %349, i8* %359)
  %361 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %362 = call i32 @fflush(%struct.__sFILE* %361)
  br label %363

; <label>:363:                                    ; preds = %357, %344, %341, %338, %335
  call void @indent(i32 -1)
  %364 = load i32, i32* %19, align 4
  store i32 %364, i32* %5, align 4
  store i32 1, i32* %20, align 4
  br label %448

; <label>:365:                                    ; preds = %327
  %366 = load i64, i64* %11, align 8
  store i64 %366, i64* %21, align 8
  br label %367

; <label>:367:                                    ; preds = %384, %365
  %368 = load i64, i64* %21, align 8
  %369 = load i64, i64* %13, align 8
  %370 = icmp ult i64 %368, %369
  br i1 %370, label %371, label %387

; <label>:371:                                    ; preds = %367
  %372 = load i64, i64* %21, align 8
  %373 = getelementptr inbounds i32, i32* %303, i64 %372
  %374 = load i32, i32* %373, align 4
  %375 = sext i32 %374 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1256, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.132, i32 0, i32 0), i64 %375)
  %376 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %377 = load i64, i64* %21, align 8
  %378 = getelementptr inbounds i32, i32* %303, i64 %377
  %379 = load i32, i32* %378, align 4
  %380 = sext i32 %379 to i64
  %381 = getelementptr inbounds i32, i32* %376, i64 %380
  store i32 0, i32* %381, align 4
  %382 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %383 = add nsw i64 %382, 1
  store i64 %383, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  br label %384

; <label>:384:                                    ; preds = %371
  %385 = load i64, i64* %21, align 8
  %386 = add i64 %385, 1
  store i64 %386, i64* %21, align 8
  br label %367

; <label>:387:                                    ; preds = %367
  %388 = load i64, i64* %11, align 8
  %389 = icmp ult i64 0, %388
  br i1 %389, label %390, label %403

; <label>:390:                                    ; preds = %387
  %391 = load i64, i64* %11, align 8
  %392 = sub i64 %391, 1
  %393 = getelementptr inbounds i32, i32* %303, i64 %392
  %394 = load i32, i32* %393, align 4
  %395 = sext i32 %394 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1262, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.133, i32 0, i32 0), i64 %395)
  %396 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %397 = load i64, i64* %11, align 8
  %398 = sub i64 %397, 1
  %399 = getelementptr inbounds i32, i32* %303, i64 %398
  %400 = load i32, i32* %399, align 4
  %401 = sext i32 %400 to i64
  %402 = getelementptr inbounds i32, i32* %396, i64 %401
  store i32 -2, i32* %402, align 4
  br label %403

; <label>:403:                                    ; preds = %390, %387
  %404 = load i64, i64* %9, align 8
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1266, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.134, i32 0, i32 0), i64 %404)
  %405 = load i64, i64* %9, align 8
  %406 = trunc i64 %405 to i32
  %407 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %408 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %407, i32 0, i32 2
  store i32 %406, i32* %408, align 8
  %409 = load i32, i32* %6, align 4
  %410 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %411 = load i64, i64* %8, align 8
  %412 = call i32 @fat_write_entry(i32 %409, %struct.dir_t* %410, i64 %411)
  store i32 %412, i32* %19, align 4
  %413 = load i32, i32* %19, align 4
  %414 = icmp slt i32 %413, 0
  br i1 %414, label %415, label %445

; <label>:415:                                    ; preds = %403
  store i32 1, i32* @debug_enable, align 4
  %416 = load i32, i32* @debug_enable, align 4
  %417 = icmp eq i32 %416, 1
  br i1 %417, label %418, label %443

; <label>:418:                                    ; preds = %415
  %419 = load i32, i32* @debug_disable_method, align 4
  %420 = icmp eq i32 %419, 0
  br i1 %420, label %421, label %443

; <label>:421:                                    ; preds = %418
  %422 = load i32, i32* @debug_disable_external, align 4
  %423 = icmp ne i32 %422, 1
  br i1 %423, label %424, label %443

; <label>:424:                                    ; preds = %421
  %425 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %426 = icmp ne %struct.__sFILE* %425, null
  br i1 %426, label %427, label %443

; <label>:427:                                    ; preds = %424
  %428 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %429 = load i32, i32* %19, align 4
  %430 = load i32, i32* %19, align 4
  %431 = icmp slt i32 %430, 0
  br i1 %431, label %432, label %435

; <label>:432:                                    ; preds = %427
  %433 = load i32, i32* %19, align 4
  %434 = sub nsw i32 0, %433
  br label %437

; <label>:435:                                    ; preds = %427
  %436 = load i32, i32* %19, align 4
  br label %437

; <label>:437:                                    ; preds = %435, %432
  %438 = phi i32 [ %434, %432 ], [ %436, %435 ]
  %439 = call i8* @"\01_strerror"(i32 %438)
  %440 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %428, i8* getelementptr inbounds ([149 x i8], [149 x i8]* @.str.135, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1269, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %429, i8* %439)
  %441 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %442 = call i32 @fflush(%struct.__sFILE* %441)
  br label %443

; <label>:443:                                    ; preds = %437, %424, %421, %418, %415
  call void @indent(i32 -1)
  %444 = load i32, i32* %19, align 4
  store i32 %444, i32* %5, align 4
  store i32 1, i32* %20, align 4
  br label %448

; <label>:445:                                    ; preds = %403
  %446 = load i32, i32* %6, align 4
  %447 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %446, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %447)
  store i32 0, i32* %20, align 4
  br label %448

; <label>:448:                                    ; preds = %445, %443, %363
  %449 = load i8*, i8** %15, align 8
  call void @llvm.stackrestore(i8* %449)
  %450 = load i32, i32* %20, align 4
  switch i32 %450, label %648 [
    i32 0, label %451
    i32 1, label %646
  ]

; <label>:451:                                    ; preds = %448
  br label %626

; <label>:452:                                    ; preds = %277
  %453 = load i32, i32* @debug_enable, align 4
  %454 = icmp eq i32 %453, 1
  br i1 %454, label %455, label %471

; <label>:455:                                    ; preds = %452
  %456 = load i32, i32* @debug_disable_method, align 4
  %457 = icmp eq i32 %456, 0
  br i1 %457, label %458, label %471

; <label>:458:                                    ; preds = %455
  %459 = load i32, i32* @debug_disable_external, align 4
  %460 = icmp ne i32 %459, 1
  br i1 %460, label %461, label %471

; <label>:461:                                    ; preds = %458
  %462 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %463 = icmp ne %struct.__sFILE* %462, null
  br i1 %463, label %464, label %471

; <label>:464:                                    ; preds = %461
  %465 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %466 = load i64, i64* %13, align 8
  %467 = load i64, i64* %11, align 8
  %468 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %465, i8* getelementptr inbounds ([154 x i8], [154 x i8]* @.str.136, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1272, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %466, i64 %467)
  %469 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %470 = call i32 @fflush(%struct.__sFILE* %469)
  br label %471

; <label>:471:                                    ; preds = %464, %461, %458, %455, %452
  %472 = load i64, i64* %11, align 8
  %473 = load i64, i64* %13, align 8
  %474 = icmp ne i64 %473, 0
  br i1 %474, label %476, label %475

; <label>:475:                                    ; preds = %471
  br label %476

; <label>:476:                                    ; preds = %475, %471
  %477 = phi i1 [ true, %471 ], [ true, %475 ]
  %478 = zext i1 %477 to i32
  %479 = sext i32 %478 to i64
  %480 = sub i64 %472, %479
  store i64 %480, i64* %22, align 8
  %481 = load i32, i32* @debug_enable, align 4
  %482 = icmp eq i32 %481, 1
  br i1 %482, label %483, label %502

; <label>:483:                                    ; preds = %476
  %484 = load i32, i32* @debug_disable_method, align 4
  %485 = icmp eq i32 %484, 0
  br i1 %485, label %486, label %502

; <label>:486:                                    ; preds = %483
  %487 = load i32, i32* @debug_disable_external, align 4
  %488 = icmp ne i32 %487, 1
  br i1 %488, label %489, label %502

; <label>:489:                                    ; preds = %486
  %490 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %491 = icmp ne %struct.__sFILE* %490, null
  br i1 %491, label %492, label %502

; <label>:492:                                    ; preds = %489
  %493 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %494 = load i64, i64* %22, align 8
  %495 = load i64, i64* %22, align 8
  %496 = icmp eq i64 %495, 1
  %497 = zext i1 %496 to i64
  %498 = select i1 %496, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.26, i32 0, i32 0)
  %499 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %493, i8* getelementptr inbounds ([131 x i8], [131 x i8]* @.str.137, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1277, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %494, i8* %498)
  %500 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %501 = call i32 @fflush(%struct.__sFILE* %500)
  br label %502

; <label>:502:                                    ; preds = %492, %489, %486, %483, %476
  %503 = load i64, i64* %22, align 8
  %504 = call i32 @fat_has_free(i64 %503)
  %505 = icmp ne i32 %504, 0
  br i1 %505, label %524, label %506

; <label>:506:                                    ; preds = %502
  %507 = load i32, i32* @debug_enable, align 4
  %508 = icmp eq i32 %507, 1
  br i1 %508, label %509, label %523

; <label>:509:                                    ; preds = %506
  %510 = load i32, i32* @debug_disable_method, align 4
  %511 = icmp eq i32 %510, 0
  br i1 %511, label %512, label %523

; <label>:512:                                    ; preds = %509
  %513 = load i32, i32* @debug_disable_external, align 4
  %514 = icmp ne i32 %513, 1
  br i1 %514, label %515, label %523

; <label>:515:                                    ; preds = %512
  %516 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %517 = icmp ne %struct.__sFILE* %516, null
  br i1 %517, label %518, label %523

; <label>:518:                                    ; preds = %515
  %519 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %520 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %519, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1279, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.138, i32 0, i32 0))
  %521 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %522 = call i32 @fflush(%struct.__sFILE* %521)
  br label %523

; <label>:523:                                    ; preds = %518, %515, %512, %509, %506
  call void @indent(i32 -1)
  store i32 -28, i32* %5, align 4
  br label %646

; <label>:524:                                    ; preds = %502
  %525 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %526 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %525, i32 0, i32 3
  %527 = load i32, i32* %526, align 4
  store i32 %527, i32* %24, align 4
  store i64 0, i64* %25, align 8
  store i64 0, i64* %26, align 8
  br label %528

; <label>:528:                                    ; preds = %537, %524
  %529 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %530 = load i32, i32* %24, align 4
  %531 = sext i32 %530 to i64
  %532 = getelementptr inbounds i32, i32* %529, i64 %531
  %533 = load i32, i32* %532, align 4
  store i32 %533, i32* %23, align 4
  %534 = load i32, i32* %23, align 4
  %535 = icmp sle i32 %534, 0
  br i1 %535, label %536, label %537

; <label>:536:                                    ; preds = %528
  br label %545

; <label>:537:                                    ; preds = %528
  %538 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %539 = load i32, i32* %24, align 4
  %540 = sext i32 %539 to i64
  %541 = getelementptr inbounds i32, i32* %538, i64 %540
  %542 = load i32, i32* %541, align 4
  store i32 %542, i32* %24, align 4
  %543 = load i64, i64* %25, align 8
  %544 = add i64 %543, 1
  store i64 %544, i64* %25, align 8
  br label %528

; <label>:545:                                    ; preds = %536
  store i64 0, i64* %27, align 8
  br label %546

; <label>:546:                                    ; preds = %587, %545
  %547 = load i64, i64* %27, align 8
  %548 = load i64, i64* %22, align 8
  %549 = icmp ult i64 %547, %548
  br i1 %549, label %550, label %590

; <label>:550:                                    ; preds = %546
  %551 = call i32 @fat_find_free_block()
  store i32 %551, i32* %23, align 4
  %552 = load i32, i32* %23, align 4
  %553 = icmp eq i32 %552, -1
  br i1 %553, label %554, label %572

; <label>:554:                                    ; preds = %550
  %555 = load i32, i32* @debug_enable, align 4
  %556 = icmp eq i32 %555, 1
  br i1 %556, label %557, label %571

; <label>:557:                                    ; preds = %554
  %558 = load i32, i32* @debug_disable_method, align 4
  %559 = icmp eq i32 %558, 0
  br i1 %559, label %560, label %571

; <label>:560:                                    ; preds = %557
  %561 = load i32, i32* @debug_disable_external, align 4
  %562 = icmp ne i32 %561, 1
  br i1 %562, label %563, label %571

; <label>:563:                                    ; preds = %560
  %564 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %565 = icmp ne %struct.__sFILE* %564, null
  br i1 %565, label %566, label %571

; <label>:566:                                    ; preds = %563
  %567 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %568 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %567, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1301, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.139, i32 0, i32 0))
  %569 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %570 = call i32 @fflush(%struct.__sFILE* %569)
  br label %571

; <label>:571:                                    ; preds = %566, %563, %560, %557, %554
  call void @indent(i32 -1)
  store i32 -28, i32* %5, align 4
  br label %646

; <label>:572:                                    ; preds = %550
  %573 = load i32, i32* %23, align 4
  %574 = sext i32 %573 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1306, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.140, i32 0, i32 0), i64 %574)
  %575 = load i32, i32* %23, align 4
  %576 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %577 = load i32, i32* %24, align 4
  %578 = sext i32 %577 to i64
  %579 = getelementptr inbounds i32, i32* %576, i64 %578
  store i32 %575, i32* %579, align 4
  %580 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %581 = load i32, i32* %23, align 4
  %582 = sext i32 %581 to i64
  %583 = getelementptr inbounds i32, i32* %580, i64 %582
  store i32 -2, i32* %583, align 4
  %584 = load i32, i32* %23, align 4
  store i32 %584, i32* %24, align 4
  %585 = load i64, i64* %26, align 8
  %586 = add i64 %585, 1
  store i64 %586, i64* %26, align 8
  br label %587

; <label>:587:                                    ; preds = %572
  %588 = load i64, i64* %27, align 8
  %589 = add i64 %588, 1
  store i64 %589, i64* %27, align 8
  br label %546

; <label>:590:                                    ; preds = %546
  %591 = load i64, i64* %26, align 8
  %592 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %593 = sub i64 %592, %591
  store i64 %593, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %594 = load i32, i32* @debug_enable, align 4
  %595 = icmp eq i32 %594, 1
  br i1 %595, label %596, label %615

; <label>:596:                                    ; preds = %590
  %597 = load i32, i32* @debug_disable_method, align 4
  %598 = icmp eq i32 %597, 0
  br i1 %598, label %599, label %615

; <label>:599:                                    ; preds = %596
  %600 = load i32, i32* @debug_disable_external, align 4
  %601 = icmp ne i32 %600, 1
  br i1 %601, label %602, label %615

; <label>:602:                                    ; preds = %599
  %603 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %604 = icmp ne %struct.__sFILE* %603, null
  br i1 %604, label %605, label %615

; <label>:605:                                    ; preds = %602
  %606 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %607 = load i64, i64* %8, align 8
  %608 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %609 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %608, i32 0, i32 2
  %610 = load i32, i32* %609, align 8
  %611 = load i64, i64* %9, align 8
  %612 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %606, i8* getelementptr inbounds ([192 x i8], [192 x i8]* @.str.141, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1316, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %607, i32 %610, i64 %611)
  %613 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %614 = call i32 @fflush(%struct.__sFILE* %613)
  br label %615

; <label>:615:                                    ; preds = %605, %602, %599, %596, %590
  %616 = load i64, i64* %9, align 8
  %617 = trunc i64 %616 to i32
  %618 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %619 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %618, i32 0, i32 2
  store i32 %617, i32* %619, align 8
  %620 = load i32, i32* %6, align 4
  %621 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %622 = load i64, i64* %8, align 8
  %623 = call i32 @fat_write_entry(i32 %620, %struct.dir_t* %621, i64 %622)
  %624 = load i32, i32* %6, align 4
  %625 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %624, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %625)
  br label %626

; <label>:626:                                    ; preds = %615, %451
  br label %627

; <label>:627:                                    ; preds = %626, %276
  br label %628

; <label>:628:                                    ; preds = %627, %126
  %629 = load i32, i32* @debug_enable, align 4
  %630 = icmp eq i32 %629, 1
  br i1 %630, label %631, label %645

; <label>:631:                                    ; preds = %628
  %632 = load i32, i32* @debug_disable_method, align 4
  %633 = icmp eq i32 %632, 0
  br i1 %633, label %634, label %645

; <label>:634:                                    ; preds = %631
  %635 = load i32, i32* @debug_disable_external, align 4
  %636 = icmp ne i32 %635, 1
  br i1 %636, label %637, label %645

; <label>:637:                                    ; preds = %634
  %638 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %639 = icmp ne %struct.__sFILE* %638, null
  br i1 %639, label %640, label %645

; <label>:640:                                    ; preds = %637
  %641 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %642 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %641, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.142, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1322, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.143, i32 0, i32 0))
  %643 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %644 = call i32 @fflush(%struct.__sFILE* %643)
  br label %645

; <label>:645:                                    ; preds = %640, %637, %634, %631, %628
  call void @indent(i32 -1)
  store i32 0, i32* %5, align 4
  br label %646

; <label>:646:                                    ; preds = %645, %571, %523, %448, %274, %210, %56
  %647 = load i32, i32* %5, align 4
  ret i32 %647

; <label>:648:                                    ; preds = %448
  unreachable
}

; Function Attrs: nounwind
declare i8* @llvm.stacksave() #7

; Function Attrs: nounwind
declare void @llvm.stackrestore(i8*) #7

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_compact(i32, %struct.dir_t*, i64) #0 {
  %4 = alloca i32, align 4
  %5 = alloca i32, align 4
  %6 = alloca %struct.dir_t*, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  %9 = alloca i64, align 8
  %10 = alloca i64, align 8
  %11 = alloca i8*, align 8
  %12 = alloca i64, align 8
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca i64, align 8
  %17 = alloca i64, align 8
  %18 = alloca i64, align 8
  %19 = alloca i64, align 8
  %20 = alloca i64, align 8
  %21 = alloca i64, align 8
  %22 = alloca i64, align 8
  %23 = alloca %struct.pathc_t*, align 8
  %24 = alloca i32, align 4
  %25 = alloca i32, align 4
  store i32 %0, i32* %5, align 4
  store %struct.dir_t* %1, %struct.dir_t** %6, align 8
  store i64 %2, i64* %7, align 8
  %26 = load i32, i32* %5, align 4
  %27 = load i64, i64* %7, align 8
  call void @indent(i32 1)
  %28 = load i32, i32* @debug_enable, align 4
  %29 = icmp eq i32 %28, 1
  br i1 %29, label %30, label %48

; <label>:30:                                     ; preds = %3
  %31 = load i32, i32* @debug_disable_method, align 4
  %32 = icmp eq i32 %31, 0
  br i1 %32, label %33, label %48

; <label>:33:                                     ; preds = %30
  %34 = load i32, i32* @debug_disable_external, align 4
  %35 = icmp ne i32 %34, 1
  br i1 %35, label %36, label %48

; <label>:36:                                     ; preds = %33
  %37 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %38 = icmp ne %struct.__sFILE* %37, null
  br i1 %38, label %39, label %48

; <label>:39:                                     ; preds = %36
  %40 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %41 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %42 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %41, i32 0, i32 0
  %43 = bitcast %union.fname_u* %42 to [24 x i8]*
  %44 = getelementptr inbounds [24 x i8], [24 x i8]* %43, i32 0, i32 0
  %45 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %40, i8* getelementptr inbounds ([120 x i8], [120 x i8]* @.str.144, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1338, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %44)
  %46 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %47 = call i32 @fflush(%struct.__sFILE* %46)
  br label %48

; <label>:48:                                     ; preds = %39, %36, %33, %30, %3
  %49 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %50 = call i64 @fat_count_allocated_in_dir(%struct.dir_t* %49)
  store i64 %50, i64* %8, align 8
  %51 = load i64, i64* %8, align 8
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1342, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.146, i32 0, i32 0), i64 %51)
  %52 = load i64, i64* %8, align 8
  %53 = icmp eq i64 %52, 0
  br i1 %53, label %54, label %55

; <label>:54:                                     ; preds = %48
  store i32 0, i32* %4, align 4
  br label %715

; <label>:55:                                     ; preds = %48
  %56 = load i64, i64* %7, align 8
  %57 = call %struct.pathc_t* @pathc_find_offset(i64 %56)
  %58 = call i32 @pathc_remove_item(%struct.pathc_t* %57)
  %59 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %60 = zext i32 %59 to i64
  store i64 %60, i64* %9, align 8
  %61 = load i64, i64* %8, align 8
  store i64 %61, i64* %10, align 8
  %62 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %63 = zext i32 %62 to i64
  %64 = udiv i64 %63, 64
  %65 = call i8* @llvm.stacksave()
  store i8* %65, i8** %11, align 8
  %66 = alloca %struct.dir_t, i64 %64, align 16
  store i64 %64, i64* %12, align 8
  %67 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %68 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %67, i32 0, i32 3
  %69 = load i32, i32* %68, align 4
  store i32 %69, i32* %13, align 4
  %70 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %71 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %70, i32 0, i32 3
  %72 = load i32, i32* %71, align 4
  store i32 %72, i32* %15, align 4
  store i64 0, i64* %16, align 8
  store i64 0, i64* %17, align 8
  store i64 1, i64* %18, align 8
  store i64 0, i64* %19, align 8
  br label %73

; <label>:73:                                     ; preds = %506, %55
  store i64 0, i64* %17, align 8
  %74 = load i32, i32* %5, align 4
  %75 = load i32, i32* %13, align 4
  %76 = sext i32 %75 to i64
  %77 = load i64, i64* %9, align 8
  %78 = mul i64 %76, %77
  %79 = call i64 @lseek(i32 %74, i64 %78, i32 0)
  %80 = call i32* @__error()
  %81 = load i32, i32* %80, align 4
  %82 = icmp ne i32 %81, 0
  br i1 %82, label %83, label %99

; <label>:83:                                     ; preds = %73
  call void @indent(i32 -1)
  %84 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %85 = call i32* @__error()
  %86 = load i32, i32* %85, align 4
  %87 = icmp slt i32 %86, 0
  br i1 %87, label %88, label %92

; <label>:88:                                     ; preds = %83
  %89 = call i32* @__error()
  %90 = load i32, i32* %89, align 4
  %91 = sub nsw i32 0, %90
  br label %95

; <label>:92:                                     ; preds = %83
  %93 = call i32* @__error()
  %94 = load i32, i32* %93, align 4
  br label %95

; <label>:95:                                     ; preds = %92, %88
  %96 = phi i32 [ %91, %88 ], [ %94, %92 ]
  %97 = call i8* @"\01_strerror"(i32 %96)
  %98 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %84, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1372, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %97)
  call void @quit(i32 1, i32 1)
  br label %99

; <label>:99:                                     ; preds = %95, %73
  %100 = load i32, i32* %5, align 4
  %101 = bitcast %struct.dir_t* %66 to i8*
  %102 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %103 = zext i32 %102 to i64
  %104 = udiv i64 %103, 64
  %105 = mul i64 %104, 64
  %106 = call i64 @"\01_read"(i32 %100, i8* %101, i64 %105)
  %107 = call i32* @__error()
  %108 = load i32, i32* %107, align 4
  %109 = icmp ne i32 %108, 0
  br i1 %109, label %110, label %126

; <label>:110:                                    ; preds = %99
  call void @indent(i32 -1)
  %111 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %112 = call i32* @__error()
  %113 = load i32, i32* %112, align 4
  %114 = icmp slt i32 %113, 0
  br i1 %114, label %115, label %119

; <label>:115:                                    ; preds = %110
  %116 = call i32* @__error()
  %117 = load i32, i32* %116, align 4
  %118 = sub nsw i32 0, %117
  br label %122

; <label>:119:                                    ; preds = %110
  %120 = call i32* @__error()
  %121 = load i32, i32* %120, align 4
  br label %122

; <label>:122:                                    ; preds = %119, %115
  %123 = phi i32 [ %118, %115 ], [ %121, %119 ]
  %124 = call i8* @"\01_strerror"(i32 %123)
  %125 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %111, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1374, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.9, i32 0, i32 0), i8* %124)
  call void @quit(i32 1, i32 1)
  br label %126

; <label>:126:                                    ; preds = %122, %99
  %127 = load i64, i64* %19, align 8
  %128 = icmp eq i64 %127, 0
  br i1 %128, label %129, label %140

; <label>:129:                                    ; preds = %126
  %130 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 4), align 8
  %131 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 0
  %132 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %131, i32 0, i32 3
  %133 = load i32, i32* %132, align 4
  %134 = icmp eq i32 %130, %133
  br i1 %134, label %135, label %138

; <label>:135:                                    ; preds = %129
  %136 = load i64, i64* %18, align 8
  %137 = add i64 %136, 1
  store i64 %137, i64* %18, align 8
  br label %138

; <label>:138:                                    ; preds = %135, %129
  %139 = load i64, i64* %18, align 8
  store i64 %139, i64* %16, align 8
  store i64 %139, i64* %20, align 8
  br label %141

; <label>:140:                                    ; preds = %126
  store i64 0, i64* %20, align 8
  br label %141

; <label>:141:                                    ; preds = %140, %138
  %142 = load i32, i32* %5, align 4
  %143 = load i32, i32* %15, align 4
  %144 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %145 = mul i32 %143, %144
  %146 = zext i32 %145 to i64
  %147 = load i64, i64* %16, align 8
  %148 = mul i64 %147, 64
  %149 = add i64 %146, %148
  %150 = call i64 @lseek(i32 %142, i64 %149, i32 0)
  %151 = call i32* @__error()
  %152 = load i32, i32* %151, align 4
  %153 = icmp ne i32 %152, 0
  br i1 %153, label %154, label %170

; <label>:154:                                    ; preds = %141
  call void @indent(i32 -1)
  %155 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %156 = call i32* @__error()
  %157 = load i32, i32* %156, align 4
  %158 = icmp slt i32 %157, 0
  br i1 %158, label %159, label %163

; <label>:159:                                    ; preds = %154
  %160 = call i32* @__error()
  %161 = load i32, i32* %160, align 4
  %162 = sub nsw i32 0, %161
  br label %166

; <label>:163:                                    ; preds = %154
  %164 = call i32* @__error()
  %165 = load i32, i32* %164, align 4
  br label %166

; <label>:166:                                    ; preds = %163, %159
  %167 = phi i32 [ %162, %159 ], [ %165, %163 ]
  %168 = call i8* @"\01_strerror"(i32 %167)
  %169 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %155, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1389, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %168)
  call void @quit(i32 1, i32 1)
  br label %170

; <label>:170:                                    ; preds = %166, %141
  br label %171

; <label>:171:                                    ; preds = %465, %170
  %172 = load i64, i64* %20, align 8
  %173 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %174 = zext i32 %173 to i64
  %175 = udiv i64 %174, 64
  %176 = icmp ult i64 %172, %175
  br i1 %176, label %177, label %468

; <label>:177:                                    ; preds = %171
  %178 = load i32, i32* %13, align 4
  %179 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %180 = mul i32 %178, %179
  %181 = zext i32 %180 to i64
  %182 = load i64, i64* %20, align 8
  %183 = mul i64 %182, 64
  %184 = add i64 %181, %183
  store i64 %184, i64* %21, align 8
  %185 = load i32, i32* %15, align 4
  %186 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %187 = mul i32 %185, %186
  %188 = zext i32 %187 to i64
  %189 = load i64, i64* %16, align 8
  %190 = mul i64 %189, 64
  %191 = add i64 %188, %190
  store i64 %191, i64* %22, align 8
  %192 = load i64, i64* %20, align 8
  %193 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %192
  %194 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %193, i32 0, i32 0
  %195 = bitcast %union.fname_u* %194 to [6 x i32]*
  %196 = getelementptr inbounds [6 x i32], [6 x i32]* %195, i64 0, i64 0
  %197 = load i32, i32* %196, align 16
  %198 = icmp eq i32 %197, 0
  br i1 %198, label %199, label %261

; <label>:199:                                    ; preds = %177
  %200 = load i64, i64* %20, align 8
  %201 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %200
  %202 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %201, i32 0, i32 0
  %203 = bitcast %union.fname_u* %202 to [6 x i32]*
  %204 = getelementptr inbounds [6 x i32], [6 x i32]* %203, i64 0, i64 1
  %205 = load i32, i32* %204, align 4
  %206 = icmp eq i32 %205, 0
  br i1 %206, label %207, label %261

; <label>:207:                                    ; preds = %199
  %208 = load i64, i64* %20, align 8
  %209 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %208
  %210 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %209, i32 0, i32 0
  %211 = bitcast %union.fname_u* %210 to [6 x i32]*
  %212 = getelementptr inbounds [6 x i32], [6 x i32]* %211, i64 0, i64 2
  %213 = load i32, i32* %212, align 8
  %214 = icmp eq i32 %213, 0
  br i1 %214, label %215, label %261

; <label>:215:                                    ; preds = %207
  %216 = load i64, i64* %20, align 8
  %217 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %216
  %218 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %217, i32 0, i32 0
  %219 = bitcast %union.fname_u* %218 to [6 x i32]*
  %220 = getelementptr inbounds [6 x i32], [6 x i32]* %219, i64 0, i64 3
  %221 = load i32, i32* %220, align 4
  %222 = icmp eq i32 %221, 0
  br i1 %222, label %223, label %261

; <label>:223:                                    ; preds = %215
  %224 = load i64, i64* %20, align 8
  %225 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %224
  %226 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %225, i32 0, i32 0
  %227 = bitcast %union.fname_u* %226 to [6 x i32]*
  %228 = getelementptr inbounds [6 x i32], [6 x i32]* %227, i64 0, i64 4
  %229 = load i32, i32* %228, align 16
  %230 = icmp eq i32 %229, 0
  br i1 %230, label %231, label %261

; <label>:231:                                    ; preds = %223
  %232 = load i64, i64* %20, align 8
  %233 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %232
  %234 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %233, i32 0, i32 0
  %235 = bitcast %union.fname_u* %234 to [6 x i32]*
  %236 = getelementptr inbounds [6 x i32], [6 x i32]* %235, i64 0, i64 5
  %237 = load i32, i32* %236, align 4
  %238 = icmp eq i32 %237, 0
  br i1 %238, label %239, label %261

; <label>:239:                                    ; preds = %231
  %240 = load i64, i64* %20, align 8
  %241 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %240
  %242 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %241, i32 0, i32 1
  %243 = getelementptr inbounds %struct.times_t, %struct.times_t* %242, i32 0, i32 0
  %244 = load i64, i64* %243, align 8
  %245 = icmp eq i64 %244, 0
  br i1 %245, label %246, label %261

; <label>:246:                                    ; preds = %239
  %247 = load i64, i64* %20, align 8
  %248 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %247
  %249 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %248, i32 0, i32 1
  %250 = getelementptr inbounds %struct.times_t, %struct.times_t* %249, i32 0, i32 1
  %251 = load i64, i64* %250, align 8
  %252 = icmp eq i64 %251, 0
  br i1 %252, label %253, label %261

; <label>:253:                                    ; preds = %246
  %254 = load i64, i64* %20, align 8
  %255 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %254
  %256 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %255, i32 0, i32 1
  %257 = getelementptr inbounds %struct.times_t, %struct.times_t* %256, i32 0, i32 2
  %258 = load i64, i64* %257, align 8
  %259 = icmp eq i64 %258, 0
  br i1 %259, label %260, label %261

; <label>:260:                                    ; preds = %253
  br label %465

; <label>:261:                                    ; preds = %253, %246, %239, %231, %223, %215, %207, %199, %177
  %262 = load i64, i64* %20, align 8
  %263 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %262
  %264 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %263, i32 0, i32 3
  %265 = load i32, i32* %264, align 4
  %266 = icmp eq i32 %265, 0
  br i1 %266, label %282, label %267

; <label>:267:                                    ; preds = %261
  %268 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %269 = load i64, i64* %20, align 8
  %270 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %269
  %271 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %270, i32 0, i32 3
  %272 = load i32, i32* %271, align 4
  %273 = sext i32 %272 to i64
  %274 = getelementptr inbounds i32, i32* %268, i64 %273
  %275 = load i32, i32* %274, align 4
  %276 = icmp eq i32 %275, 0
  br i1 %276, label %282, label %277

; <label>:277:                                    ; preds = %267
  %278 = load i64, i64* %21, align 8
  %279 = load i64, i64* %22, align 8
  %280 = icmp eq i64 %278, %279
  br i1 %280, label %281, label %282

; <label>:281:                                    ; preds = %277
  br label %451

; <label>:282:                                    ; preds = %277, %267, %261
  %283 = load i64, i64* %20, align 8
  %284 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %283
  %285 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %284, i32 0, i32 3
  %286 = load i32, i32* %285, align 4
  %287 = icmp eq i32 %286, 0
  br i1 %287, label %449, label %288

; <label>:288:                                    ; preds = %282
  %289 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %290 = load i64, i64* %20, align 8
  %291 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %290
  %292 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %291, i32 0, i32 3
  %293 = load i32, i32* %292, align 4
  %294 = sext i32 %293 to i64
  %295 = getelementptr inbounds i32, i32* %289, i64 %294
  %296 = load i32, i32* %295, align 4
  %297 = icmp eq i32 %296, 0
  br i1 %297, label %449, label %298

; <label>:298:                                    ; preds = %288
  %299 = load i32, i32* @debug_enable, align 4
  %300 = icmp eq i32 %299, 1
  br i1 %300, label %301, label %323

; <label>:301:                                    ; preds = %298
  %302 = load i32, i32* @debug_disable_method, align 4
  %303 = icmp eq i32 %302, 0
  br i1 %303, label %304, label %323

; <label>:304:                                    ; preds = %301
  %305 = load i32, i32* @debug_disable_external, align 4
  %306 = icmp ne i32 %305, 1
  br i1 %306, label %307, label %323

; <label>:307:                                    ; preds = %304
  %308 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %309 = icmp ne %struct.__sFILE* %308, null
  br i1 %309, label %310, label %323

; <label>:310:                                    ; preds = %307
  %311 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %312 = load i64, i64* %20, align 8
  %313 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %312
  %314 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %313, i32 0, i32 0
  %315 = bitcast %union.fname_u* %314 to [24 x i8]*
  %316 = getelementptr inbounds [24 x i8], [24 x i8]* %315, i32 0, i32 0
  %317 = load i32, i32* %15, align 4
  %318 = load i64, i64* %16, align 8
  %319 = load i64, i64* %10, align 8
  %320 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %311, i8* getelementptr inbounds ([163 x i8], [163 x i8]* @.str.147, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1405, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %316, i32 %317, i64 %318, i64 %319)
  %321 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %322 = call i32 @fflush(%struct.__sFILE* %321)
  br label %323

; <label>:323:                                    ; preds = %310, %307, %304, %301, %298
  %324 = load i32, i32* %5, align 4
  %325 = load i64, i64* %22, align 8
  %326 = call i64 @lseek(i32 %324, i64 %325, i32 0)
  %327 = call i32* @__error()
  %328 = load i32, i32* %327, align 4
  %329 = icmp ne i32 %328, 0
  br i1 %329, label %330, label %346

; <label>:330:                                    ; preds = %323
  call void @indent(i32 -1)
  %331 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %332 = call i32* @__error()
  %333 = load i32, i32* %332, align 4
  %334 = icmp slt i32 %333, 0
  br i1 %334, label %335, label %339

; <label>:335:                                    ; preds = %330
  %336 = call i32* @__error()
  %337 = load i32, i32* %336, align 4
  %338 = sub nsw i32 0, %337
  br label %342

; <label>:339:                                    ; preds = %330
  %340 = call i32* @__error()
  %341 = load i32, i32* %340, align 4
  br label %342

; <label>:342:                                    ; preds = %339, %335
  %343 = phi i32 [ %338, %335 ], [ %341, %339 ]
  %344 = call i8* @"\01_strerror"(i32 %343)
  %345 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %331, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1408, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %344)
  call void @quit(i32 1, i32 1)
  br label %346

; <label>:346:                                    ; preds = %342, %323
  %347 = load i32, i32* %5, align 4
  %348 = load i64, i64* %20, align 8
  %349 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %66, i64 %348
  %350 = bitcast %struct.dir_t* %349 to i8*
  %351 = call i64 @"\01_write"(i32 %347, i8* %350, i64 64)
  %352 = call i32* @__error()
  %353 = load i32, i32* %352, align 4
  %354 = icmp ne i32 %353, 0
  br i1 %354, label %355, label %371

; <label>:355:                                    ; preds = %346
  call void @indent(i32 -1)
  %356 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %357 = call i32* @__error()
  %358 = load i32, i32* %357, align 4
  %359 = icmp slt i32 %358, 0
  br i1 %359, label %360, label %364

; <label>:360:                                    ; preds = %355
  %361 = call i32* @__error()
  %362 = load i32, i32* %361, align 4
  %363 = sub nsw i32 0, %362
  br label %367

; <label>:364:                                    ; preds = %355
  %365 = call i32* @__error()
  %366 = load i32, i32* %365, align 4
  br label %367

; <label>:367:                                    ; preds = %364, %360
  %368 = phi i32 [ %363, %360 ], [ %366, %364 ]
  %369 = call i8* @"\01_strerror"(i32 %368)
  %370 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %356, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1410, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.148, i32 0, i32 0), i8* %369)
  call void @quit(i32 1, i32 1)
  br label %371

; <label>:371:                                    ; preds = %367, %346
  %372 = load i64, i64* %21, align 8
  %373 = call %struct.pathc_t* @pathc_find_offset(i64 %372)
  store %struct.pathc_t* %373, %struct.pathc_t** %23, align 8
  %374 = load %struct.pathc_t*, %struct.pathc_t** %23, align 8
  %375 = icmp ne %struct.pathc_t* %374, null
  br i1 %375, label %376, label %401

; <label>:376:                                    ; preds = %371
  %377 = load i32, i32* @debug_enable, align 4
  %378 = icmp eq i32 %377, 1
  br i1 %378, label %379, label %397

; <label>:379:                                    ; preds = %376
  %380 = load i32, i32* @debug_disable_method, align 4
  %381 = icmp eq i32 %380, 0
  br i1 %381, label %382, label %397

; <label>:382:                                    ; preds = %379
  %383 = load i32, i32* @debug_disable_external, align 4
  %384 = icmp ne i32 %383, 1
  br i1 %384, label %385, label %397

; <label>:385:                                    ; preds = %382
  %386 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %387 = icmp ne %struct.__sFILE* %386, null
  br i1 %387, label %388, label %397

; <label>:388:                                    ; preds = %385
  %389 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %390 = load %struct.pathc_t*, %struct.pathc_t** %23, align 8
  %391 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %390, i32 0, i32 4
  %392 = load i64, i64* %391, align 8
  %393 = load i64, i64* %22, align 8
  %394 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %389, i8* getelementptr inbounds ([139 x i8], [139 x i8]* @.str.149, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1415, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %392, i64 %393)
  %395 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %396 = call i32 @fflush(%struct.__sFILE* %395)
  br label %397

; <label>:397:                                    ; preds = %388, %385, %382, %379, %376
  %398 = load i64, i64* %22, align 8
  %399 = load %struct.pathc_t*, %struct.pathc_t** %23, align 8
  %400 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %399, i32 0, i32 4
  store i64 %398, i64* %400, align 8
  br label %401

; <label>:401:                                    ; preds = %397, %371
  %402 = load i32, i32* %5, align 4
  %403 = load i64, i64* %21, align 8
  %404 = call i64 @lseek(i32 %402, i64 %403, i32 0)
  %405 = call i32* @__error()
  %406 = load i32, i32* %405, align 4
  %407 = icmp ne i32 %406, 0
  br i1 %407, label %408, label %424

; <label>:408:                                    ; preds = %401
  call void @indent(i32 -1)
  %409 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %410 = call i32* @__error()
  %411 = load i32, i32* %410, align 4
  %412 = icmp slt i32 %411, 0
  br i1 %412, label %413, label %417

; <label>:413:                                    ; preds = %408
  %414 = call i32* @__error()
  %415 = load i32, i32* %414, align 4
  %416 = sub nsw i32 0, %415
  br label %420

; <label>:417:                                    ; preds = %408
  %418 = call i32* @__error()
  %419 = load i32, i32* %418, align 4
  br label %420

; <label>:420:                                    ; preds = %417, %413
  %421 = phi i32 [ %416, %413 ], [ %419, %417 ]
  %422 = call i8* @"\01_strerror"(i32 %421)
  %423 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %409, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1421, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %422)
  call void @quit(i32 1, i32 1)
  br label %424

; <label>:424:                                    ; preds = %420, %401
  %425 = load i32, i32* %5, align 4
  %426 = call i64 @"\01_write"(i32 %425, i8* getelementptr inbounds ([4096 x i8], [4096 x i8]* @nothing, i32 0, i32 0), i64 64)
  %427 = call i32* @__error()
  %428 = load i32, i32* %427, align 4
  %429 = icmp ne i32 %428, 0
  br i1 %429, label %430, label %446

; <label>:430:                                    ; preds = %424
  call void @indent(i32 -1)
  %431 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %432 = call i32* @__error()
  %433 = load i32, i32* %432, align 4
  %434 = icmp slt i32 %433, 0
  br i1 %434, label %435, label %439

; <label>:435:                                    ; preds = %430
  %436 = call i32* @__error()
  %437 = load i32, i32* %436, align 4
  %438 = sub nsw i32 0, %437
  br label %442

; <label>:439:                                    ; preds = %430
  %440 = call i32* @__error()
  %441 = load i32, i32* %440, align 4
  br label %442

; <label>:442:                                    ; preds = %439, %435
  %443 = phi i32 [ %438, %435 ], [ %441, %439 ]
  %444 = call i8* @"\01_strerror"(i32 %443)
  %445 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %431, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1423, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.148, i32 0, i32 0), i8* %444)
  call void @quit(i32 1, i32 1)
  br label %446

; <label>:446:                                    ; preds = %442, %424
  %447 = load i64, i64* %17, align 8
  %448 = add i64 %447, 1
  store i64 %448, i64* %17, align 8
  br label %450

; <label>:449:                                    ; preds = %288, %282
  br label %465

; <label>:450:                                    ; preds = %446
  br label %451

; <label>:451:                                    ; preds = %450, %281
  %452 = load i64, i64* %16, align 8
  %453 = add i64 %452, 1
  store i64 %453, i64* %16, align 8
  %454 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %455 = zext i32 %454 to i64
  %456 = udiv i64 %455, 64
  %457 = icmp eq i64 %453, %456
  br i1 %457, label %458, label %464

; <label>:458:                                    ; preds = %451
  %459 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %460 = load i32, i32* %15, align 4
  %461 = sext i32 %460 to i64
  %462 = getelementptr inbounds i32, i32* %459, i64 %461
  %463 = load i32, i32* %462, align 4
  store i32 %463, i32* %15, align 4
  store i64 0, i64* %16, align 8
  br label %464

; <label>:464:                                    ; preds = %458, %451
  br label %465

; <label>:465:                                    ; preds = %464, %449, %260
  %466 = load i64, i64* %20, align 8
  %467 = add i64 %466, 1
  store i64 %467, i64* %20, align 8
  br label %171

; <label>:468:                                    ; preds = %171
  %469 = load i64, i64* %17, align 8
  %470 = load i64, i64* %10, align 8
  %471 = sub i64 %470, %469
  store i64 %471, i64* %10, align 8
  %472 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %473 = load i32, i32* %13, align 4
  %474 = sext i32 %473 to i64
  %475 = getelementptr inbounds i32, i32* %472, i64 %474
  %476 = load i32, i32* %475, align 4
  store i32 %476, i32* %14, align 4
  %477 = load i32, i32* %14, align 4
  %478 = icmp eq i32 %477, -2
  br i1 %478, label %479, label %480

; <label>:479:                                    ; preds = %468
  br label %509

; <label>:480:                                    ; preds = %468
  %481 = load i32, i32* %14, align 4
  %482 = icmp slt i32 %481, 1
  br i1 %482, label %483, label %503

; <label>:483:                                    ; preds = %480
  %484 = load i32, i32* @debug_enable, align 4
  %485 = icmp eq i32 %484, 1
  br i1 %485, label %486, label %502

; <label>:486:                                    ; preds = %483
  %487 = load i32, i32* @debug_disable_method, align 4
  %488 = icmp eq i32 %487, 0
  br i1 %488, label %489, label %502

; <label>:489:                                    ; preds = %486
  %490 = load i32, i32* @debug_disable_external, align 4
  %491 = icmp ne i32 %490, 1
  br i1 %491, label %492, label %502

; <label>:492:                                    ; preds = %489
  %493 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %494 = icmp ne %struct.__sFILE* %493, null
  br i1 %494, label %495, label %502

; <label>:495:                                    ; preds = %492
  %496 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %497 = load i32, i32* %13, align 4
  %498 = load i32, i32* %14, align 4
  %499 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %496, i8* getelementptr inbounds ([165 x i8], [165 x i8]* @.str.150, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1444, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %497, i32 %498)
  %500 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %501 = call i32 @fflush(%struct.__sFILE* %500)
  br label %502

; <label>:502:                                    ; preds = %495, %492, %489, %486, %483
  br label %509

; <label>:503:                                    ; preds = %480
  br label %504

; <label>:504:                                    ; preds = %503
  %505 = load i32, i32* %14, align 4
  store i32 %505, i32* %13, align 4
  br label %506

; <label>:506:                                    ; preds = %504
  %507 = load i64, i64* %19, align 8
  %508 = add i64 %507, 1
  store i64 %508, i64* %19, align 8
  br label %73

; <label>:509:                                    ; preds = %502, %479
  %510 = load i64, i64* %8, align 8
  %511 = mul i64 %510, 64
  %512 = trunc i64 %511 to i32
  store i32 %512, i32* %24, align 4
  %513 = load i32, i32* %24, align 4
  %514 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %515 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %514, i32 0, i32 2
  store i32 %513, i32* %515, align 8
  %516 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 4), align 8
  %517 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %518 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %517, i32 0, i32 3
  %519 = load i32, i32* %518, align 4
  %520 = icmp eq i32 %516, %519
  br i1 %520, label %521, label %586

; <label>:521:                                    ; preds = %509
  store i64 0, i64* %19, align 8
  br label %522

; <label>:522:                                    ; preds = %582, %521
  %523 = load i64, i64* %19, align 8
  %524 = load i64, i64* %18, align 8
  %525 = icmp ult i64 %523, %524
  br i1 %525, label %526, label %585

; <label>:526:                                    ; preds = %522
  %527 = load i32, i32* %5, align 4
  %528 = load %struct.dir_t*, %struct.dir_t** %6, align 8
  %529 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %528, i32 0, i32 3
  %530 = load i32, i32* %529, align 4
  %531 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %532 = mul i32 %530, %531
  %533 = zext i32 %532 to i64
  %534 = load i64, i64* %19, align 8
  %535 = mul i64 %534, 64
  %536 = add i64 %533, %535
  %537 = add i64 %536, 48
  %538 = call i64 @lseek(i32 %527, i64 %537, i32 0)
  %539 = call i32* @__error()
  %540 = load i32, i32* %539, align 4
  %541 = icmp ne i32 %540, 0
  br i1 %541, label %542, label %558

; <label>:542:                                    ; preds = %526
  call void @indent(i32 -1)
  %543 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %544 = call i32* @__error()
  %545 = load i32, i32* %544, align 4
  %546 = icmp slt i32 %545, 0
  br i1 %546, label %547, label %551

; <label>:547:                                    ; preds = %542
  %548 = call i32* @__error()
  %549 = load i32, i32* %548, align 4
  %550 = sub nsw i32 0, %549
  br label %554

; <label>:551:                                    ; preds = %542
  %552 = call i32* @__error()
  %553 = load i32, i32* %552, align 4
  br label %554

; <label>:554:                                    ; preds = %551, %547
  %555 = phi i32 [ %550, %547 ], [ %553, %551 ]
  %556 = call i8* @"\01_strerror"(i32 %555)
  %557 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %543, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1457, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %556)
  call void @quit(i32 1, i32 1)
  br label %558

; <label>:558:                                    ; preds = %554, %526
  %559 = load i32, i32* %5, align 4
  %560 = bitcast i32* %24 to i8*
  %561 = call i64 @"\01_write"(i32 %559, i8* %560, i64 4)
  %562 = call i32* @__error()
  %563 = load i32, i32* %562, align 4
  %564 = icmp ne i32 %563, 0
  br i1 %564, label %565, label %581

; <label>:565:                                    ; preds = %558
  call void @indent(i32 -1)
  %566 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %567 = call i32* @__error()
  %568 = load i32, i32* %567, align 4
  %569 = icmp slt i32 %568, 0
  br i1 %569, label %570, label %574

; <label>:570:                                    ; preds = %565
  %571 = call i32* @__error()
  %572 = load i32, i32* %571, align 4
  %573 = sub nsw i32 0, %572
  br label %577

; <label>:574:                                    ; preds = %565
  %575 = call i32* @__error()
  %576 = load i32, i32* %575, align 4
  br label %577

; <label>:577:                                    ; preds = %574, %570
  %578 = phi i32 [ %573, %570 ], [ %576, %574 ]
  %579 = call i8* @"\01_strerror"(i32 %578)
  %580 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %566, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1459, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.148, i32 0, i32 0), i8* %579)
  call void @quit(i32 1, i32 1)
  br label %581

; <label>:581:                                    ; preds = %577, %558
  br label %582

; <label>:582:                                    ; preds = %581
  %583 = load i64, i64* %19, align 8
  %584 = add i64 %583, 1
  store i64 %584, i64* %19, align 8
  br label %522

; <label>:585:                                    ; preds = %522
  br label %634

; <label>:586:                                    ; preds = %509
  %587 = load i32, i32* %5, align 4
  %588 = load i64, i64* %7, align 8
  %589 = add i64 %588, 48
  %590 = call i64 @lseek(i32 %587, i64 %589, i32 0)
  %591 = call i32* @__error()
  %592 = load i32, i32* %591, align 4
  %593 = icmp ne i32 %592, 0
  br i1 %593, label %594, label %610

; <label>:594:                                    ; preds = %586
  call void @indent(i32 -1)
  %595 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %596 = call i32* @__error()
  %597 = load i32, i32* %596, align 4
  %598 = icmp slt i32 %597, 0
  br i1 %598, label %599, label %603

; <label>:599:                                    ; preds = %594
  %600 = call i32* @__error()
  %601 = load i32, i32* %600, align 4
  %602 = sub nsw i32 0, %601
  br label %606

; <label>:603:                                    ; preds = %594
  %604 = call i32* @__error()
  %605 = load i32, i32* %604, align 4
  br label %606

; <label>:606:                                    ; preds = %603, %599
  %607 = phi i32 [ %602, %599 ], [ %605, %603 ]
  %608 = call i8* @"\01_strerror"(i32 %607)
  %609 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %595, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1464, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %608)
  call void @quit(i32 1, i32 1)
  br label %610

; <label>:610:                                    ; preds = %606, %586
  %611 = load i32, i32* %5, align 4
  %612 = bitcast i32* %24 to i8*
  %613 = call i64 @"\01_write"(i32 %611, i8* %612, i64 4)
  %614 = call i32* @__error()
  %615 = load i32, i32* %614, align 4
  %616 = icmp ne i32 %615, 0
  br i1 %616, label %617, label %633

; <label>:617:                                    ; preds = %610
  call void @indent(i32 -1)
  %618 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %619 = call i32* @__error()
  %620 = load i32, i32* %619, align 4
  %621 = icmp slt i32 %620, 0
  br i1 %621, label %622, label %626

; <label>:622:                                    ; preds = %617
  %623 = call i32* @__error()
  %624 = load i32, i32* %623, align 4
  %625 = sub nsw i32 0, %624
  br label %629

; <label>:626:                                    ; preds = %617
  %627 = call i32* @__error()
  %628 = load i32, i32* %627, align 4
  br label %629

; <label>:629:                                    ; preds = %626, %622
  %630 = phi i32 [ %625, %622 ], [ %628, %626 ]
  %631 = call i8* @"\01_strerror"(i32 %630)
  %632 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %618, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1466, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.148, i32 0, i32 0), i8* %631)
  call void @quit(i32 1, i32 1)
  br label %633

; <label>:633:                                    ; preds = %629, %610
  br label %634

; <label>:634:                                    ; preds = %633, %585
  %635 = load i64, i64* %16, align 8
  %636 = icmp ult i64 90, %635
  br i1 %636, label %637, label %675

; <label>:637:                                    ; preds = %634
  %638 = load i64, i64* %16, align 8
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1471, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([25 x i8], [25 x i8]* @.str.151, i32 0, i32 0), i64 %638)
  %639 = load i32, i32* %5, align 4
  %640 = load i32, i32* %15, align 4
  %641 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %642 = mul i32 %640, %641
  %643 = zext i32 %642 to i64
  %644 = load i64, i64* %16, align 8
  %645 = mul i64 %644, 64
  %646 = add i64 %643, %645
  %647 = call i64 @lseek(i32 %639, i64 %646, i32 0)
  %648 = call i32* @__error()
  %649 = load i32, i32* %648, align 4
  %650 = icmp ne i32 %649, 0
  br i1 %650, label %651, label %667

; <label>:651:                                    ; preds = %637
  call void @indent(i32 -1)
  %652 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %653 = call i32* @__error()
  %654 = load i32, i32* %653, align 4
  %655 = icmp slt i32 %654, 0
  br i1 %655, label %656, label %660

; <label>:656:                                    ; preds = %651
  %657 = call i32* @__error()
  %658 = load i32, i32* %657, align 4
  %659 = sub nsw i32 0, %658
  br label %663

; <label>:660:                                    ; preds = %651
  %661 = call i32* @__error()
  %662 = load i32, i32* %661, align 4
  br label %663

; <label>:663:                                    ; preds = %660, %656
  %664 = phi i32 [ %659, %656 ], [ %662, %660 ]
  %665 = call i8* @"\01_strerror"(i32 %664)
  %666 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %652, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1473, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %665)
  call void @quit(i32 1, i32 1)
  br label %667

; <label>:667:                                    ; preds = %663, %637
  %668 = load i32, i32* %5, align 4
  %669 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %670 = zext i32 %669 to i64
  %671 = udiv i64 %670, 64
  %672 = load i64, i64* %16, align 8
  %673 = sub i64 %671, %672
  %674 = call i64 @iwrite(i32 %668, i32 0, i64 %673)
  br label %675

; <label>:675:                                    ; preds = %667, %634
  %676 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %677 = load i32, i32* %15, align 4
  %678 = sext i32 %677 to i64
  %679 = getelementptr inbounds i32, i32* %676, i64 %678
  %680 = load i32, i32* %679, align 4
  store i32 %680, i32* %25, align 4
  %681 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %682 = load i32, i32* %15, align 4
  %683 = sext i32 %682 to i64
  %684 = getelementptr inbounds i32, i32* %681, i64 %683
  store i32 -2, i32* %684, align 4
  %685 = load i32, i32* %15, align 4
  %686 = load i32, i32* %13, align 4
  %687 = icmp ne i32 %685, %686
  br i1 %687, label %688, label %696

; <label>:688:                                    ; preds = %675
  %689 = load i32, i32* %25, align 4
  %690 = icmp slt i32 0, %689
  br i1 %690, label %691, label %696

; <label>:691:                                    ; preds = %688
  %692 = load i32, i32* %25, align 4
  %693 = sext i32 %692 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1481, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([38 x i8], [38 x i8]* @.str.152, i32 0, i32 0), i64 %693)
  %694 = load i32, i32* %25, align 4
  %695 = call i64 @fat_forget(i32 %694)
  br label %696

; <label>:696:                                    ; preds = %691, %688, %675
  %697 = load i32, i32* @debug_enable, align 4
  %698 = icmp eq i32 %697, 1
  br i1 %698, label %699, label %713

; <label>:699:                                    ; preds = %696
  %700 = load i32, i32* @debug_disable_method, align 4
  %701 = icmp eq i32 %700, 0
  br i1 %701, label %702, label %713

; <label>:702:                                    ; preds = %699
  %703 = load i32, i32* @debug_disable_external, align 4
  %704 = icmp ne i32 %703, 1
  br i1 %704, label %705, label %713

; <label>:705:                                    ; preds = %702
  %706 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %707 = icmp ne %struct.__sFILE* %706, null
  br i1 %707, label %708, label %713

; <label>:708:                                    ; preds = %705
  %709 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %710 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %709, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.142, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1485, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.145, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.44, i32 0, i32 0))
  %711 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %712 = call i32 @fflush(%struct.__sFILE* %711)
  br label %713

; <label>:713:                                    ; preds = %708, %705, %702, %699, %696
  call void @indent(i32 -1)
  store i32 0, i32* %4, align 4
  %714 = load i8*, i8** %11, align 8
  call void @llvm.stackrestore(i8* %714)
  br label %715

; <label>:715:                                    ; preds = %713, %54
  %716 = load i32, i32* %4, align 4
  ret i32 %716
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @fat_count_allocated_in_dir(%struct.dir_t*) #0 {
  %2 = alloca %struct.dir_t*, align 8
  %3 = alloca i32, align 4
  %4 = alloca i64, align 8
  %5 = alloca i32, align 4
  %6 = alloca i64, align 8
  %7 = alloca i32, align 4
  %8 = alloca i8*, align 8
  %9 = alloca i64, align 8
  %10 = alloca i32, align 4
  %11 = alloca i32, align 4
  store %struct.dir_t* %0, %struct.dir_t** %2, align 8
  call void @indent(i32 1)
  %12 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %13 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %12, i32 0, i32 3
  %14 = load i32, i32* %13, align 4
  store i32 %14, i32* %3, align 4
  store i64 0, i64* %4, align 8
  %15 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %16 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %15, i32 0, i32 2
  %17 = load i32, i32* %16, align 8
  store i32 %17, i32* %5, align 4
  %18 = load i32, i32* %5, align 4
  %19 = sext i32 %18 to i64
  %20 = urem i64 %19, 64
  %21 = icmp ne i64 %20, 0
  br i1 %21, label %22, label %41

; <label>:22:                                     ; preds = %1
  %23 = load i32, i32* @debug_enable, align 4
  %24 = icmp eq i32 %23, 1
  br i1 %24, label %25, label %40

; <label>:25:                                     ; preds = %22
  %26 = load i32, i32* @debug_disable_method, align 4
  %27 = icmp eq i32 %26, 0
  br i1 %27, label %28, label %40

; <label>:28:                                     ; preds = %25
  %29 = load i32, i32* @debug_disable_external, align 4
  %30 = icmp ne i32 %29, 1
  br i1 %30, label %31, label %40

; <label>:31:                                     ; preds = %28
  %32 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %33 = icmp ne %struct.__sFILE* %32, null
  br i1 %33, label %34, label %40

; <label>:34:                                     ; preds = %31
  %35 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %36 = load i32, i32* %5, align 4
  %37 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %35, i8* getelementptr inbounds ([189 x i8], [189 x i8]* @.str.158, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1545, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.159, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %36, i64 64)
  %38 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %39 = call i32 @fflush(%struct.__sFILE* %38)
  br label %40

; <label>:40:                                     ; preds = %34, %31, %28, %25, %22
  br label %41

; <label>:41:                                     ; preds = %40, %1
  %42 = load i32, i32* %5, align 4
  %43 = sext i32 %42 to i64
  %44 = udiv i64 %43, 64
  %45 = trunc i64 %44 to i32
  store i32 %45, i32* %5, align 4
  store i64 0, i64* %6, align 8
  %46 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  store i32 %46, i32* %7, align 4
  %47 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %48 = zext i32 %47 to i64
  %49 = udiv i64 %48, 64
  %50 = call i8* @llvm.stacksave()
  store i8* %50, i8** %8, align 8
  %51 = alloca %struct.dir_t, i64 %49, align 16
  store i64 %49, i64* %9, align 8
  br label %52

; <label>:52:                                     ; preds = %181, %41
  %53 = load i32, i32* %3, align 4
  %54 = icmp ne i32 %53, -2
  br i1 %54, label %55, label %182

; <label>:55:                                     ; preds = %52
  %56 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %57 = zext i32 %56 to i64
  %58 = udiv i64 %57, 64
  %59 = trunc i64 %58 to i32
  %60 = load i32, i32* %5, align 4
  %61 = icmp slt i32 %59, %60
  br i1 %61, label %62, label %67

; <label>:62:                                     ; preds = %55
  %63 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %64 = zext i32 %63 to i64
  %65 = udiv i64 %64, 64
  %66 = trunc i64 %65 to i32
  br label %69

; <label>:67:                                     ; preds = %55
  %68 = load i32, i32* %5, align 4
  br label %69

; <label>:69:                                     ; preds = %67, %62
  %70 = phi i32 [ %66, %62 ], [ %68, %67 ]
  store i32 %70, i32* %11, align 4
  %71 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 5), align 8
  %72 = load i32, i32* %3, align 4
  %73 = load i32, i32* %7, align 4
  %74 = mul i32 %72, %73
  %75 = zext i32 %74 to i64
  %76 = call i64 @lseek(i32 %71, i64 %75, i32 0)
  %77 = call i32* @__error()
  %78 = load i32, i32* %77, align 4
  %79 = icmp ne i32 %78, 0
  br i1 %79, label %80, label %96

; <label>:80:                                     ; preds = %69
  call void @indent(i32 -1)
  %81 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %82 = call i32* @__error()
  %83 = load i32, i32* %82, align 4
  %84 = icmp slt i32 %83, 0
  br i1 %84, label %85, label %89

; <label>:85:                                     ; preds = %80
  %86 = call i32* @__error()
  %87 = load i32, i32* %86, align 4
  %88 = sub nsw i32 0, %87
  br label %92

; <label>:89:                                     ; preds = %80
  %90 = call i32* @__error()
  %91 = load i32, i32* %90, align 4
  br label %92

; <label>:92:                                     ; preds = %89, %85
  %93 = phi i32 [ %88, %85 ], [ %91, %89 ]
  %94 = call i8* @"\01_strerror"(i32 %93)
  %95 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %81, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1567, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.159, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.15, i32 0, i32 0), i8* %94)
  call void @quit(i32 1, i32 1)
  br label %96

; <label>:96:                                     ; preds = %92, %69
  %97 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 5), align 8
  %98 = bitcast %struct.dir_t* %51 to i8*
  %99 = load i32, i32* %11, align 4
  %100 = sext i32 %99 to i64
  %101 = mul i64 %100, 64
  %102 = call i64 @"\01_read"(i32 %97, i8* %98, i64 %101)
  %103 = call i32* @__error()
  %104 = load i32, i32* %103, align 4
  %105 = icmp ne i32 %104, 0
  br i1 %105, label %106, label %122

; <label>:106:                                    ; preds = %96
  call void @indent(i32 -1)
  %107 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %108 = call i32* @__error()
  %109 = load i32, i32* %108, align 4
  %110 = icmp slt i32 %109, 0
  br i1 %110, label %111, label %115

; <label>:111:                                    ; preds = %106
  %112 = call i32* @__error()
  %113 = load i32, i32* %112, align 4
  %114 = sub nsw i32 0, %113
  br label %118

; <label>:115:                                    ; preds = %106
  %116 = call i32* @__error()
  %117 = load i32, i32* %116, align 4
  br label %118

; <label>:118:                                    ; preds = %115, %111
  %119 = phi i32 [ %114, %111 ], [ %117, %115 ]
  %120 = call i8* @"\01_strerror"(i32 %119)
  %121 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %107, i8* getelementptr inbounds ([110 x i8], [110 x i8]* @.str.8, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1569, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.159, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.9, i32 0, i32 0), i8* %120)
  call void @quit(i32 1, i32 1)
  br label %122

; <label>:122:                                    ; preds = %118, %96
  %123 = load i32, i32* %11, align 4
  %124 = sub nsw i32 %123, 1
  store i32 %124, i32* %10, align 4
  br label %125

; <label>:125:                                    ; preds = %152, %122
  %126 = load i32, i32* %10, align 4
  %127 = icmp sle i32 0, %126
  br i1 %127, label %128, label %155

; <label>:128:                                    ; preds = %125
  %129 = load i64, i64* %6, align 8
  %130 = add i64 %129, 1
  store i64 %130, i64* %6, align 8
  %131 = load i32, i32* %10, align 4
  %132 = sext i32 %131 to i64
  %133 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %51, i64 %132
  %134 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %133, i32 0, i32 3
  %135 = load i32, i32* %134, align 4
  %136 = icmp eq i32 %135, 0
  br i1 %136, label %151, label %137

; <label>:137:                                    ; preds = %128
  %138 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %139 = load i32, i32* %10, align 4
  %140 = sext i32 %139 to i64
  %141 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %51, i64 %140
  %142 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %141, i32 0, i32 3
  %143 = load i32, i32* %142, align 4
  %144 = sext i32 %143 to i64
  %145 = getelementptr inbounds i32, i32* %138, i64 %144
  %146 = load i32, i32* %145, align 4
  %147 = icmp eq i32 %146, 0
  br i1 %147, label %151, label %148

; <label>:148:                                    ; preds = %137
  %149 = load i64, i64* %4, align 8
  %150 = add i64 %149, 1
  store i64 %150, i64* %4, align 8
  br label %151

; <label>:151:                                    ; preds = %148, %137, %128
  br label %152

; <label>:152:                                    ; preds = %151
  %153 = load i32, i32* %10, align 4
  %154 = add nsw i32 %153, -1
  store i32 %154, i32* %10, align 4
  br label %125

; <label>:155:                                    ; preds = %125
  %156 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %157 = load i32, i32* %3, align 4
  %158 = sext i32 %157 to i64
  %159 = getelementptr inbounds i32, i32* %156, i64 %158
  %160 = load i32, i32* %159, align 4
  store i32 %160, i32* %3, align 4
  %161 = load i32, i32* %3, align 4
  %162 = icmp eq i32 %161, 0
  br i1 %162, label %163, label %181

; <label>:163:                                    ; preds = %155
  %164 = load i32, i32* @debug_enable, align 4
  %165 = icmp eq i32 %164, 1
  br i1 %165, label %166, label %180

; <label>:166:                                    ; preds = %163
  %167 = load i32, i32* @debug_disable_method, align 4
  %168 = icmp eq i32 %167, 0
  br i1 %168, label %169, label %180

; <label>:169:                                    ; preds = %166
  %170 = load i32, i32* @debug_disable_external, align 4
  %171 = icmp ne i32 %170, 1
  br i1 %171, label %172, label %180

; <label>:172:                                    ; preds = %169
  %173 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %174 = icmp ne %struct.__sFILE* %173, null
  br i1 %174, label %175, label %180

; <label>:175:                                    ; preds = %172
  %176 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %177 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %176, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1580, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.159, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([23 x i8], [23 x i8]* @.str.160, i32 0, i32 0))
  %178 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %179 = call i32 @fflush(%struct.__sFILE* %178)
  br label %180

; <label>:180:                                    ; preds = %175, %172, %169, %166, %163
  br label %181

; <label>:181:                                    ; preds = %180, %155
  br label %52

; <label>:182:                                    ; preds = %52
  %183 = load i32, i32* @debug_enable, align 4
  %184 = icmp eq i32 %183, 1
  br i1 %184, label %185, label %212

; <label>:185:                                    ; preds = %182
  %186 = load i32, i32* @debug_disable_method, align 4
  %187 = icmp eq i32 %186, 0
  br i1 %187, label %188, label %212

; <label>:188:                                    ; preds = %185
  %189 = load i32, i32* @debug_disable_external, align 4
  %190 = icmp ne i32 %189, 1
  br i1 %190, label %191, label %212

; <label>:191:                                    ; preds = %188
  %192 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %193 = icmp ne %struct.__sFILE* %192, null
  br i1 %193, label %194, label %212

; <label>:194:                                    ; preds = %191
  %195 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %196 = load i64, i64* %4, align 8
  %197 = load i64, i64* %4, align 8
  %198 = icmp eq i64 %197, 1
  %199 = zext i1 %198 to i64
  %200 = select i1 %198, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.5, i32 0, i32 0), i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.6, i32 0, i32 0)
  %201 = load i64, i64* %6, align 8
  %202 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %203 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %202, i32 0, i32 0
  %204 = bitcast %union.fname_u* %203 to [24 x i8]*
  %205 = getelementptr inbounds [24 x i8], [24 x i8]* %204, i32 0, i32 0
  %206 = load %struct.dir_t*, %struct.dir_t** %2, align 8
  %207 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %206, i32 0, i32 3
  %208 = load i32, i32* %207, align 4
  %209 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %195, i8* getelementptr inbounds ([228 x i8], [228 x i8]* @.str.161, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1585, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.159, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %196, i8* %200, i64 %201, i8* %205, i32 %208)
  %210 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %211 = call i32 @fflush(%struct.__sFILE* %210)
  br label %212

; <label>:212:                                    ; preds = %194, %191, %188, %185, %182
  call void @indent(i32 -1)
  %213 = load i64, i64* %4, align 8
  %214 = load i8*, i8** %8, align 8
  call void @llvm.stackrestore(i8* %214)
  ret i64 %213
}

declare i32 @pathc_remove_item(%struct.pathc_t*) #1

declare i64 @iwrite(i32, i32, i64) #1

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

declare i32 @pathc_remove_path(i8*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_find_free_block() #0 {
  %1 = alloca i32, align 4
  %2 = alloca i32, align 4
  %3 = alloca i64, align 8
  %4 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 1), align 4
  store i32 %4, i32* %2, align 4
  store i64 0, i64* %3, align 8
  br label %5

; <label>:5:                                      ; preds = %20, %0
  %6 = load i64, i64* %3, align 8
  %7 = load i32, i32* %2, align 4
  %8 = zext i32 %7 to i64
  %9 = icmp ult i64 %6, %8
  br i1 %9, label %10, label %23

; <label>:10:                                     ; preds = %5
  %11 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %12 = load i64, i64* %3, align 8
  %13 = getelementptr inbounds i32, i32* %11, i64 %12
  %14 = load i32, i32* %13, align 4
  %15 = icmp eq i32 %14, 0
  br i1 %15, label %16, label %19

; <label>:16:                                     ; preds = %10
  %17 = load i64, i64* %3, align 8
  %18 = trunc i64 %17 to i32
  store i32 %18, i32* %1, align 4
  br label %24

; <label>:19:                                     ; preds = %10
  br label %20

; <label>:20:                                     ; preds = %19
  %21 = load i64, i64* %3, align 8
  %22 = add i64 %21, 1
  store i64 %22, i64* %3, align 8
  br label %5

; <label>:23:                                     ; preds = %5
  store i32 -1, i32* %1, align 4
  br label %24

; <label>:24:                                     ; preds = %23, %16
  %25 = load i32, i32* %1, align 4
  ret i32 %25
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { argmemonly nounwind }
attributes #3 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind readnone speculatable }
attributes #5 = { allocsize(0,1) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #6 = { allocsize(0) "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #7 = { nounwind }
attributes #8 = { allocsize(0,1) }
attributes #9 = { allocsize(0) }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
