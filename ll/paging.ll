; ModuleID = 'paging.cpp'
source_filename = "paging.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

%struct.P0Wrapper = type { i64* }

$_ZN9P0WrapperC2EPm = comdat any

$_ZN9P0Wrapper3setEv = comdat any

$_ZN9P0Wrapper6getP5EEPvRm = comdat any

$_ZN9P0Wrapper6getP4EEPvRm = comdat any

$_ZN9P0Wrapper9isPresentEm = comdat any

$_ZN9P0Wrapper8p5OffsetEPv = comdat any

$_ZN9P0Wrapper6getP3EEPvRm = comdat any

$_ZN9P0Wrapper8p4OffsetEPv = comdat any

$_ZN9P0Wrapper6getP2EEPvRm = comdat any

$_ZN9P0Wrapper8p3OffsetEPv = comdat any

$_ZN9P0Wrapper6getP1EEPvRm = comdat any

$_ZN9P0Wrapper8p2OffsetEPv = comdat any

$_ZN9P0Wrapper6getP0EEPv = comdat any

$_ZN9P0Wrapper8p1OffsetEPv = comdat any

$_ZN9P0Wrapper8p0OffsetEPv = comdat any

@table = dso_local global [6 x void ()*] [void ()* null, void ()* null, void ()* null, void ()* null, void ()* @_Z9pagefaultv, void ()* null], align 16
@.str = private unnamed_addr constant [15 x i8] c"Hello, world!\0A\00", align 1
@.str.1 = private unnamed_addr constant [4 x i8] c"No\0A\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"P5E: \00", align 1
@.str.3 = private unnamed_addr constant [12 x i8] c"Page fault!\00", align 1

; Function Attrs: noinline optnone uwtable
define dso_local void @_Z9pagefaultv() #0 {
  call void @_Z8strprintPKc(i8* getelementptr inbounds ([12 x i8], [12 x i8]* @.str.3, i64 0, i64 0))
  call void asm sideeffect ": $$e0", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !2
  ret void
}

; Function Attrs: naked noinline nounwind optnone uwtable
define dso_local void @_Z3prdl(i64 %0) #1 {
  call void asm sideeffect "<prd $$a0>", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !3
  unreachable
}

; Function Attrs: naked noinline nounwind optnone uwtable
define dso_local void @_Z3prcc(i8 signext %0) #1 {
  call void asm sideeffect "<prc $$a0>", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !4
  unreachable
}

; Function Attrs: naked noinline nounwind optnone uwtable
define dso_local void @_Z3prxc(i8 signext %0) #1 {
  call void asm sideeffect "<prx $$a0>", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !5
  unreachable
}

; Function Attrs: noinline norecurse optnone uwtable
define dso_local i32 @main() #2 {
  %1 = alloca i32, align 4
  %2 = alloca %struct.P0Wrapper, align 8
  %3 = alloca i64, align 8
  store i32 0, i32* %1, align 4
  call void @_Z8strprintPKc(i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str, i64 0, i64 0))
  call void asm sideeffect "rit table", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !6
  %4 = load volatile i64, i64* inttoptr (i64 1 to i64*), align 8
  call void @_Z3prdl(i64 %4)
  call void @_Z3prcc(i8 signext 10)
  call void @_ZN9P0WrapperC2EPm(%struct.P0Wrapper* %2, i64* inttoptr (i64 65536 to i64*))
  %5 = getelementptr inbounds %struct.P0Wrapper, %struct.P0Wrapper* %2, i32 0, i32 0
  %6 = load i64*, i64** %5, align 8
  %7 = ptrtoint i64* %6 to i64
  call void @_Z3prdl(i64 %7)
  call void @_Z3prcc(i8 signext 10)
  call void @_ZN9P0Wrapper3setEv(%struct.P0Wrapper* %2)
  %8 = call zeroext i1 @_ZN9P0Wrapper6getP5EEPvRm(%struct.P0Wrapper* %2, i8* inttoptr (i64 65536 to i8*), i64* nonnull align 8 dereferenceable(8) %3)
  br i1 %8, label %10, label %9

9:                                                ; preds = %0
  call void @_Z8strprintPKc(i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.1, i64 0, i64 0))
  br label %13

10:                                               ; preds = %0
  call void @_Z8strprintPKc(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.2, i64 0, i64 0))
  %11 = load i64, i64* %3, align 8
  %12 = trunc i64 %11 to i8
  call void @_Z3prxc(i8 signext %12)
  call void @_Z3prcc(i8 signext 10)
  br label %13

13:                                               ; preds = %10, %9
  call void asm sideeffect "page on", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !7
  %14 = load volatile i64, i64* inttoptr (i64 1 to i64*), align 8
  call void @_Z3prdl(i64 %14)
  call void @_Z3prcc(i8 signext 10)
  %15 = load i32, i32* %1, align 4
  ret i32 %15
}

; Function Attrs: naked noinline nounwind optnone uwtable
define dso_local void @_Z8strprintPKc(i8* %0) #1 {
  call void asm sideeffect "<>; @_strprint_loop      \09     [$$a0] -> $$ma /b          \09     : _strprint_print if $$ma \09     : _strprint_done         \09     @_strprint_print         \09     <prc $$ma>                \09     $$a0 + 1 -> $$a0           \09     : _strprint_loop         \09     @_strprint_done; <>", "~{dirflag},~{fpsr},~{flags}"() #4, !srcloc !8
  unreachable
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN9P0WrapperC2EPm(%struct.P0Wrapper* %0, i64* %1) unnamed_addr #3 comdat align 2 {
  %3 = alloca %struct.P0Wrapper*, align 8
  %4 = alloca i64*, align 8
  store %struct.P0Wrapper* %0, %struct.P0Wrapper** %3, align 8
  store i64* %1, i64** %4, align 8
  %5 = load %struct.P0Wrapper*, %struct.P0Wrapper** %3, align 8
  %6 = getelementptr inbounds %struct.P0Wrapper, %struct.P0Wrapper* %5, i32 0, i32 0
  %7 = load i64*, i64** %4, align 8
  store i64* %7, i64** %6, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local void @_ZN9P0Wrapper3setEv(%struct.P0Wrapper* %0) #3 comdat align 2 {
  %2 = alloca %struct.P0Wrapper*, align 8
  store %struct.P0Wrapper* %0, %struct.P0Wrapper** %2, align 8
  %3 = load %struct.P0Wrapper*, %struct.P0Wrapper** %2, align 8
  %4 = getelementptr inbounds %struct.P0Wrapper, %struct.P0Wrapper* %3, i32 0, i32 0
  %5 = load i64*, i64** %4, align 8
  call void asm sideeffect "setpt $0", "r,~{dirflag},~{fpsr},~{flags}"(i64* %5) #4, !srcloc !9
  ret void
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local zeroext i1 @_ZN9P0Wrapper6getP5EEPvRm(%struct.P0Wrapper* %0, i8* %1, i64* nonnull align 8 dereferenceable(8) %2) #0 comdat align 2 {
  %4 = alloca i1, align 1
  %5 = alloca %struct.P0Wrapper*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i64*, align 8
  %8 = alloca i64, align 8
  store %struct.P0Wrapper* %0, %struct.P0Wrapper** %5, align 8
  store i8* %1, i8** %6, align 8
  store i64* %2, i64** %7, align 8
  %9 = load %struct.P0Wrapper*, %struct.P0Wrapper** %5, align 8
  %10 = load i8*, i8** %6, align 8
  %11 = call zeroext i1 @_ZN9P0Wrapper6getP4EEPvRm(%struct.P0Wrapper* %9, i8* %10, i64* nonnull align 8 dereferenceable(8) %8)
  br i1 %11, label %13, label %12

12:                                               ; preds = %3
  store i1 false, i1* %4, align 1
  br label %27

13:                                               ; preds = %3
  %14 = load i64, i64* %8, align 8
  %15 = call zeroext i1 @_ZN9P0Wrapper9isPresentEm(i64 %14)
  br i1 %15, label %17, label %16

16:                                               ; preds = %13
  store i1 false, i1* %4, align 1
  br label %27

17:                                               ; preds = %13
  %18 = load i64, i64* %8, align 8
  %19 = and i64 %18, -256
  %20 = inttoptr i64 %19 to i64*
  %21 = load i8*, i8** %6, align 8
  %22 = call zeroext i8 @_ZN9P0Wrapper8p5OffsetEPv(i8* %21)
  %23 = zext i8 %22 to i64
  %24 = getelementptr inbounds i64, i64* %20, i64 %23
  %25 = load i64, i64* %24, align 8
  %26 = load i64*, i64** %7, align 8
  store i64 %25, i64* %26, align 8
  store i1 true, i1* %4, align 1
  br label %27

27:                                               ; preds = %17, %16, %12
  %28 = load i1, i1* %4, align 1
  ret i1 %28
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local zeroext i1 @_ZN9P0Wrapper6getP4EEPvRm(%struct.P0Wrapper* %0, i8* %1, i64* nonnull align 8 dereferenceable(8) %2) #0 comdat align 2 {
  %4 = alloca i1, align 1
  %5 = alloca %struct.P0Wrapper*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i64*, align 8
  %8 = alloca i64, align 8
  store %struct.P0Wrapper* %0, %struct.P0Wrapper** %5, align 8
  store i8* %1, i8** %6, align 8
  store i64* %2, i64** %7, align 8
  %9 = load %struct.P0Wrapper*, %struct.P0Wrapper** %5, align 8
  %10 = load i8*, i8** %6, align 8
  %11 = call zeroext i1 @_ZN9P0Wrapper6getP3EEPvRm(%struct.P0Wrapper* %9, i8* %10, i64* nonnull align 8 dereferenceable(8) %8)
  br i1 %11, label %13, label %12

12:                                               ; preds = %3
  store i1 false, i1* %4, align 1
  br label %27

13:                                               ; preds = %3
  %14 = load i64, i64* %8, align 8
  %15 = call zeroext i1 @_ZN9P0Wrapper9isPresentEm(i64 %14)
  br i1 %15, label %17, label %16

16:                                               ; preds = %13
  store i1 false, i1* %4, align 1
  br label %27

17:                                               ; preds = %13
  %18 = load i64, i64* %8, align 8
  %19 = and i64 %18, -256
  %20 = inttoptr i64 %19 to i64*
  %21 = load i8*, i8** %6, align 8
  %22 = call zeroext i8 @_ZN9P0Wrapper8p4OffsetEPv(i8* %21)
  %23 = zext i8 %22 to i64
  %24 = getelementptr inbounds i64, i64* %20, i64 %23
  %25 = load i64, i64* %24, align 8
  %26 = load i64*, i64** %7, align 8
  store i64 %25, i64* %26, align 8
  store i1 true, i1* %4, align 1
  br label %27

27:                                               ; preds = %17, %16, %12
  %28 = load i1, i1* %4, align 1
  ret i1 %28
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local zeroext i1 @_ZN9P0Wrapper9isPresentEm(i64 %0) #3 comdat align 2 {
  %2 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  %3 = load i64, i64* %2, align 8
  %4 = and i64 %3, 1
  %5 = icmp eq i64 %4, 1
  ret i1 %5
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local zeroext i8 @_ZN9P0Wrapper8p5OffsetEPv(i8* %0) #3 comdat align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = ptrtoint i8* %3 to i64
  %5 = lshr i64 %4, 16
  %6 = and i64 %5, 255
  %7 = trunc i64 %6 to i8
  ret i8 %7
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local zeroext i1 @_ZN9P0Wrapper6getP3EEPvRm(%struct.P0Wrapper* %0, i8* %1, i64* nonnull align 8 dereferenceable(8) %2) #0 comdat align 2 {
  %4 = alloca i1, align 1
  %5 = alloca %struct.P0Wrapper*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i64*, align 8
  %8 = alloca i64, align 8
  store %struct.P0Wrapper* %0, %struct.P0Wrapper** %5, align 8
  store i8* %1, i8** %6, align 8
  store i64* %2, i64** %7, align 8
  %9 = load %struct.P0Wrapper*, %struct.P0Wrapper** %5, align 8
  %10 = load i8*, i8** %6, align 8
  %11 = call zeroext i1 @_ZN9P0Wrapper6getP2EEPvRm(%struct.P0Wrapper* %9, i8* %10, i64* nonnull align 8 dereferenceable(8) %8)
  br i1 %11, label %13, label %12

12:                                               ; preds = %3
  store i1 false, i1* %4, align 1
  br label %27

13:                                               ; preds = %3
  %14 = load i64, i64* %8, align 8
  %15 = call zeroext i1 @_ZN9P0Wrapper9isPresentEm(i64 %14)
  br i1 %15, label %17, label %16

16:                                               ; preds = %13
  store i1 false, i1* %4, align 1
  br label %27

17:                                               ; preds = %13
  %18 = load i64, i64* %8, align 8
  %19 = and i64 %18, -256
  %20 = inttoptr i64 %19 to i64*
  %21 = load i8*, i8** %6, align 8
  %22 = call zeroext i8 @_ZN9P0Wrapper8p3OffsetEPv(i8* %21)
  %23 = zext i8 %22 to i64
  %24 = getelementptr inbounds i64, i64* %20, i64 %23
  %25 = load i64, i64* %24, align 8
  %26 = load i64*, i64** %7, align 8
  store i64 %25, i64* %26, align 8
  store i1 true, i1* %4, align 1
  br label %27

27:                                               ; preds = %17, %16, %12
  %28 = load i1, i1* %4, align 1
  ret i1 %28
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local zeroext i8 @_ZN9P0Wrapper8p4OffsetEPv(i8* %0) #3 comdat align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = ptrtoint i8* %3 to i64
  %5 = lshr i64 %4, 24
  %6 = and i64 %5, 255
  %7 = trunc i64 %6 to i8
  ret i8 %7
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local zeroext i1 @_ZN9P0Wrapper6getP2EEPvRm(%struct.P0Wrapper* %0, i8* %1, i64* nonnull align 8 dereferenceable(8) %2) #0 comdat align 2 {
  %4 = alloca i1, align 1
  %5 = alloca %struct.P0Wrapper*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i64*, align 8
  %8 = alloca i64, align 8
  store %struct.P0Wrapper* %0, %struct.P0Wrapper** %5, align 8
  store i8* %1, i8** %6, align 8
  store i64* %2, i64** %7, align 8
  %9 = load %struct.P0Wrapper*, %struct.P0Wrapper** %5, align 8
  %10 = load i8*, i8** %6, align 8
  %11 = call zeroext i1 @_ZN9P0Wrapper6getP1EEPvRm(%struct.P0Wrapper* %9, i8* %10, i64* nonnull align 8 dereferenceable(8) %8)
  br i1 %11, label %13, label %12

12:                                               ; preds = %3
  store i1 false, i1* %4, align 1
  br label %27

13:                                               ; preds = %3
  %14 = load i64, i64* %8, align 8
  %15 = call zeroext i1 @_ZN9P0Wrapper9isPresentEm(i64 %14)
  br i1 %15, label %17, label %16

16:                                               ; preds = %13
  store i1 false, i1* %4, align 1
  br label %27

17:                                               ; preds = %13
  %18 = load i64, i64* %8, align 8
  %19 = and i64 %18, -256
  %20 = inttoptr i64 %19 to i64*
  %21 = load i8*, i8** %6, align 8
  %22 = call zeroext i8 @_ZN9P0Wrapper8p2OffsetEPv(i8* %21)
  %23 = zext i8 %22 to i64
  %24 = getelementptr inbounds i64, i64* %20, i64 %23
  %25 = load i64, i64* %24, align 8
  %26 = load i64*, i64** %7, align 8
  store i64 %25, i64* %26, align 8
  store i1 true, i1* %4, align 1
  br label %27

27:                                               ; preds = %17, %16, %12
  %28 = load i1, i1* %4, align 1
  ret i1 %28
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local zeroext i8 @_ZN9P0Wrapper8p3OffsetEPv(i8* %0) #3 comdat align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = ptrtoint i8* %3 to i64
  %5 = lshr i64 %4, 32
  %6 = and i64 %5, 255
  %7 = trunc i64 %6 to i8
  ret i8 %7
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local zeroext i1 @_ZN9P0Wrapper6getP1EEPvRm(%struct.P0Wrapper* %0, i8* %1, i64* nonnull align 8 dereferenceable(8) %2) #0 comdat align 2 {
  %4 = alloca i1, align 1
  %5 = alloca %struct.P0Wrapper*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca i64*, align 8
  %8 = alloca i64, align 8
  store %struct.P0Wrapper* %0, %struct.P0Wrapper** %5, align 8
  store i8* %1, i8** %6, align 8
  store i64* %2, i64** %7, align 8
  %9 = load %struct.P0Wrapper*, %struct.P0Wrapper** %5, align 8
  %10 = load i8*, i8** %6, align 8
  %11 = call i64 @_ZN9P0Wrapper6getP0EEPv(%struct.P0Wrapper* %9, i8* %10)
  store i64 %11, i64* %8, align 8
  %12 = load i64, i64* %8, align 8
  %13 = call zeroext i1 @_ZN9P0Wrapper9isPresentEm(i64 %12)
  br i1 %13, label %15, label %14

14:                                               ; preds = %3
  store i1 false, i1* %4, align 1
  br label %25

15:                                               ; preds = %3
  %16 = load i64, i64* %8, align 8
  %17 = and i64 %16, -256
  %18 = inttoptr i64 %17 to i64*
  %19 = load i8*, i8** %6, align 8
  %20 = call zeroext i8 @_ZN9P0Wrapper8p1OffsetEPv(i8* %19)
  %21 = zext i8 %20 to i64
  %22 = getelementptr inbounds i64, i64* %18, i64 %21
  %23 = load i64, i64* %22, align 8
  %24 = load i64*, i64** %7, align 8
  store i64 %23, i64* %24, align 8
  store i1 true, i1* %4, align 1
  br label %25

25:                                               ; preds = %15, %14
  %26 = load i1, i1* %4, align 1
  ret i1 %26
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local zeroext i8 @_ZN9P0Wrapper8p2OffsetEPv(i8* %0) #3 comdat align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = ptrtoint i8* %3 to i64
  %5 = lshr i64 %4, 40
  %6 = and i64 %5, 255
  %7 = trunc i64 %6 to i8
  ret i8 %7
}

; Function Attrs: noinline optnone uwtable
define linkonce_odr dso_local i64 @_ZN9P0Wrapper6getP0EEPv(%struct.P0Wrapper* %0, i8* %1) #0 comdat align 2 {
  %3 = alloca %struct.P0Wrapper*, align 8
  %4 = alloca i8*, align 8
  store %struct.P0Wrapper* %0, %struct.P0Wrapper** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %struct.P0Wrapper*, %struct.P0Wrapper** %3, align 8
  %6 = getelementptr inbounds %struct.P0Wrapper, %struct.P0Wrapper* %5, i32 0, i32 0
  %7 = load i64*, i64** %6, align 8
  %8 = load i8*, i8** %4, align 8
  %9 = call zeroext i8 @_ZN9P0Wrapper8p0OffsetEPv(i8* %8)
  %10 = zext i8 %9 to i64
  %11 = getelementptr inbounds i64, i64* %7, i64 %10
  %12 = load i64, i64* %11, align 8
  ret i64 %12
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local zeroext i8 @_ZN9P0Wrapper8p1OffsetEPv(i8* %0) #3 comdat align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = ptrtoint i8* %3 to i64
  %5 = lshr i64 %4, 48
  %6 = and i64 %5, 255
  %7 = trunc i64 %6 to i8
  ret i8 %7
}

; Function Attrs: noinline nounwind optnone uwtable
define linkonce_odr dso_local zeroext i8 @_ZN9P0Wrapper8p0OffsetEPv(i8* %0) #3 comdat align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = ptrtoint i8* %3 to i64
  %5 = lshr i64 %4, 56
  %6 = and i64 %5, 255
  %7 = trunc i64 %6 to i8
  ret i8 %7
}

attributes #0 = { noinline optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { naked noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { noinline norecurse optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { noinline nounwind optnone uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { nounwind }

!llvm.linker.options = !{}
!llvm.module.flags = !{!0}
!llvm.ident = !{!1}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{!"Ubuntu clang version 11.0.0-2"}
!2 = !{i32 2746}
!3 = !{i32 2146}
!4 = !{i32 2210}
!5 = !{i32 2274}
!6 = !{i32 2339}
!7 = !{i32 2639}
!8 = !{i32 2820}
!9 = !{i32 133}
