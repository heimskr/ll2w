; ModuleID = 'main.cpp'
source_filename = "main.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-i128:128-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

module asm ".globl _ZSt21ios_base_library_initv"

%"class.std::basic_ostream" = type { ptr, %"class.std::basic_ios" }
%"class.std::basic_ios" = type { %"class.std::ios_base", ptr, i8, i8, ptr, ptr, ptr, ptr }
%"class.std::ios_base" = type { ptr, i64, i64, i32, i32, i32, ptr, %"struct.std::ios_base::_Words", [8 x %"struct.std::ios_base::_Words"], i32, ptr, %"class.std::locale" }
%"struct.std::ios_base::_Words" = type { ptr, i64 }
%"class.std::locale" = type { ptr }
%"class.std::__cxx11::basic_string" = type { %"struct.std::__cxx11::basic_string<char>::_Alloc_hider", i64, %union.anon }
%"struct.std::__cxx11::basic_string<char>::_Alloc_hider" = type { ptr }
%union.anon = type { i64, [8 x i8] }
%"class.std::vector" = type { %"struct.std::_Vector_base" }
%"struct.std::_Vector_base" = type { %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl" }
%"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl" = type { %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data" }
%"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data" = type { ptr, ptr, ptr }
%struct.termios = type { i32, i32, i32, i32, i8, [32 x i8], i32, i32 }
%"class.std::thread" = type { %"class.std::thread::id" }
%"class.std::thread::id" = type { i64 }
%class.anon = type { ptr, ptr, ptr }
%struct.fd_set = type { [16 x i64] }
%struct.timeval = type { i64, i64 }
%"class.std::unique_ptr" = type { %"struct.std::__uniq_ptr_data" }
%"struct.std::__uniq_ptr_data" = type { %"class.std::__uniq_ptr_impl" }
%"class.std::__uniq_ptr_impl" = type { %"class.std::tuple" }
%"class.std::tuple" = type { %"struct.std::_Tuple_impl" }
%"struct.std::_Tuple_impl" = type { %"struct.std::_Head_base.6" }
%"struct.std::_Head_base.6" = type { ptr }
%"struct.std::thread::_State_impl" = type { %"struct.std::thread::_State", %"struct.std::thread::_Invoker" }
%"struct.std::thread::_State" = type { ptr }
%"struct.std::thread::_Invoker" = type { %"class.std::tuple.7" }
%"class.std::tuple.7" = type { %"struct.std::_Tuple_impl.8" }
%"struct.std::_Tuple_impl.8" = type { %"struct.std::_Head_base.9" }
%"struct.std::_Head_base.9" = type { %class.anon }

$_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_appendIJS5_EEEvDpOT_ = comdat any

$_ZNSt6thread24_M_thread_deps_never_runEv = comdat any

@_ZSt4cerr = external global %"class.std::basic_ostream", align 8
@.str = private unnamed_addr constant [47 x i8] c"Usage: serial <device> [serial configuration]\0A\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"noems\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"NXR\00", align 1
@.str.6 = private unnamed_addr constant [19 x i8] c"Invalid argument: \00", align 1
@.str.7 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.8 = private unnamed_addr constant [4 x i8] c"1.5\00", align 1
@.str.9 = private unnamed_addr constant [44 x i8] c"Stop bits set to 1.5, but data bits set to \00", align 1
@.str.10 = private unnamed_addr constant [15 x i8] c" instead of 5\0A\00", align 1
@.str.11 = private unnamed_addr constant [15 x i8] c"Couldn't open \00", align 1
@.str.12 = private unnamed_addr constant [3 x i8] c": \00", align 1
@.str.13 = private unnamed_addr constant [15 x i8] c"fcntl failed: \00", align 1
@.str.14 = private unnamed_addr constant [19 x i8] c"tcgetattr failed: \00", align 1
@.str.15 = private unnamed_addr constant [20 x i8] c"Invalid data bits: \00", align 1
@.str.16 = private unnamed_addr constant [17 x i8] c"Invalid parity: \00", align 1
@.str.17 = private unnamed_addr constant [19 x i8] c"tcsetattr failed: \00", align 1
@.str.18 = private unnamed_addr constant [14 x i8] c"pipe failed: \00", align 1
@stdout = external local_unnamed_addr global ptr, align 8
@.str.19 = private unnamed_addr constant [17 x i8] c"Reading failed: \00", align 1
@_ZSt4cout = external global %"class.std::basic_ostream", align 8
@.str.21 = private unnamed_addr constant [21 x i8] c"basic_string::substr\00", align 1
@.str.22 = private unnamed_addr constant [55 x i8] c"%s: __pos (which is %zu) > this->size() (which is %zu)\00", align 1
@.str.24 = private unnamed_addr constant [26 x i8] c"vector::_M_realloc_append\00", align 1
@.str.25 = private unnamed_addr constant [50 x i8] c"basic_string: construction from null is not valid\00", align 1
@"_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEEE" = internal unnamed_addr constant { [5 x ptr] } { [5 x ptr] [ptr null, ptr @"_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEEE", ptr @_ZNSt6thread6_StateD2Ev, ptr @"_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEED0Ev", ptr @"_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEE6_M_runEv"] }, align 8
@_ZTVN10__cxxabiv120__si_class_type_infoE = external global [0 x ptr]
@"_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEEE" = internal constant [65 x i8] c"NSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEEE\00", align 1
@_ZTINSt6thread6_StateE = external constant ptr
@"_ZTINSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEEE" = internal constant { ptr, ptr, ptr } { ptr getelementptr inbounds (ptr, ptr @_ZTVN10__cxxabiv120__si_class_type_infoE, i64 2), ptr @"_ZTSNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEEE", ptr @_ZTINSt6thread6_StateE }, align 8
@.str.26 = private unnamed_addr constant [30 x i8] c"Couldn't tcgetattr on stdin: \00", align 1
@.str.27 = private unnamed_addr constant [30 x i8] c"Couldn't tcsetattr on stdin: \00", align 1
@.str.28 = private unnamed_addr constant [25 x i8] c"Couldn't write to pipe: \00", align 1
@.str.29 = private unnamed_addr constant [23 x i8] c"Couldn't write to fd: \00", align 1

; Function Attrs: mustprogress nounwind sspstrong uwtable
define dso_local noundef zeroext i1 @_Z10parseUlongRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEERmi(ptr nocapture noundef nonnull readonly align 8 dereferenceable(32) %0, ptr nocapture noundef nonnull writeonly align 8 dereferenceable(8) %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = alloca ptr, align 8
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %4) #20
  %5 = load ptr, ptr %0, align 8, !tbaa !5
  %6 = call i64 @__isoc23_strtoull(ptr noundef %5, ptr noundef nonnull %4, i32 noundef %2) #20
  store i64 %6, ptr %1, align 8, !tbaa !12
  %7 = load ptr, ptr %4, align 8, !tbaa !13
  %8 = load ptr, ptr %0, align 8, !tbaa !5
  %9 = ptrtoint ptr %7 to i64
  %10 = ptrtoint ptr %8 to i64
  %11 = sub i64 %9, %10
  %12 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %0, i64 0, i32 1
  %13 = load i64, ptr %12, align 8, !tbaa !14
  %14 = icmp eq i64 %11, %13
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %4) #20
  ret i1 %14
}

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.start.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: nounwind
declare i64 @__isoc23_strtoull(ptr noundef, ptr noundef, i32 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite)
declare void @llvm.lifetime.end.p0(i64 immarg, ptr nocapture) #1

; Function Attrs: mustprogress nounwind sspstrong uwtable
define dso_local noundef zeroext i1 @_Z10parseUlongPKcRmi(ptr noundef %0, ptr nocapture noundef nonnull writeonly align 8 dereferenceable(8) %1, i32 noundef %2) local_unnamed_addr #0 {
  %4 = alloca ptr, align 8
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %4) #20
  %5 = call i64 @__isoc23_strtoull(ptr noundef %0, ptr noundef nonnull %4, i32 noundef %2) #20
  store i64 %5, ptr %1, align 8, !tbaa !12
  %6 = load ptr, ptr %4, align 8, !tbaa !13
  %7 = ptrtoint ptr %6 to i64
  %8 = ptrtoint ptr %0 to i64
  %9 = sub i64 %7, %8
  %10 = call i64 @strlen(ptr noundef nonnull dereferenceable(1) %0) #21
  %11 = icmp eq i64 %9, %10
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %4) #20
  ret i1 %11
}

; Function Attrs: mustprogress nofree nounwind willreturn memory(argmem: read)
declare i64 @strlen(ptr nocapture noundef) local_unnamed_addr #3

; Function Attrs: mustprogress nounwind sspstrong uwtable
define dso_local void @_Z5splitRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES6_b(ptr dead_on_unwind noalias writable sret(%"class.std::vector") align 8 %0, ptr noundef nonnull align 8 dereferenceable(32) %1, ptr nocapture noundef nonnull readonly align 8 dereferenceable(32) %2, i1 noundef zeroext %3) local_unnamed_addr #0 {
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  %9 = alloca [1 x %"class.std::__cxx11::basic_string"], align 8
  %10 = alloca %"class.std::__cxx11::basic_string", align 8
  %11 = alloca %"class.std::__cxx11::basic_string", align 8
  %12 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %1, i64 0, i32 1
  %13 = load i64, ptr %12, align 8, !tbaa !14
  %14 = icmp eq i64 %13, 0
  br i1 %14, label %15, label %16

15:                                               ; preds = %4
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 8 dereferenceable(24) %0, i8 0, i64 24, i1 false)
  br label %159

16:                                               ; preds = %4
  %17 = load ptr, ptr %2, align 8, !tbaa !5
  %18 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %2, i64 0, i32 1
  %19 = load i64, ptr %18, align 8, !tbaa !14
  %20 = tail call noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEPKcmm(ptr noundef nonnull align 8 dereferenceable(32) %1, ptr noundef %17, i64 noundef 0, i64 noundef %19) #20
  %21 = icmp eq i64 %20, -1
  br i1 %21, label %22, label %70

22:                                               ; preds = %16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %9) #20
  %23 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %9, i64 0, i32 2
  store ptr %23, ptr %9, align 8, !tbaa !15
  %24 = load ptr, ptr %1, align 8, !tbaa !5
  %25 = load i64, ptr %12, align 8, !tbaa !14
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %8) #20
  store i64 %25, ptr %8, align 8, !tbaa !12
  %26 = icmp ugt i64 %25, 15
  br i1 %26, label %27, label %30

27:                                               ; preds = %22
  %28 = call noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32) %9, ptr noundef nonnull align 8 dereferenceable(8) %8, i64 noundef 0) #20
  store ptr %28, ptr %9, align 8, !tbaa !5
  %29 = load i64, ptr %8, align 8, !tbaa !12
  store i64 %29, ptr %23, align 8, !tbaa !16
  br label %30

30:                                               ; preds = %27, %22
  %31 = phi ptr [ %28, %27 ], [ %23, %22 ]
  switch i64 %25, label %34 [
    i64 1, label %32
    i64 0, label %35
  ]

32:                                               ; preds = %30
  %33 = load i8, ptr %24, align 1, !tbaa !16
  store i8 %33, ptr %31, align 1, !tbaa !16
  br label %35

34:                                               ; preds = %30
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %31, ptr align 1 %24, i64 %25, i1 false)
  br label %35

35:                                               ; preds = %30, %32, %34
  %36 = load i64, ptr %8, align 8, !tbaa !12
  %37 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %9, i64 0, i32 1
  store i64 %36, ptr %37, align 8, !tbaa !14
  %38 = load ptr, ptr %9, align 8, !tbaa !5
  %39 = getelementptr inbounds i8, ptr %38, i64 %36
  store i8 0, ptr %39, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %8) #20
  %40 = call noalias noundef nonnull dereferenceable(32) ptr @_Znwm(i64 noundef 32) #22
  store ptr %40, ptr %0, align 8, !tbaa !17
  %41 = getelementptr inbounds i8, ptr %40, i64 32
  %42 = getelementptr inbounds %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data", ptr %0, i64 0, i32 2
  store ptr %41, ptr %42, align 8, !tbaa !19
  %43 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %40, i64 0, i32 2
  store ptr %43, ptr %40, align 8, !tbaa !15
  %44 = load ptr, ptr %9, align 8, !tbaa !5
  %45 = load i64, ptr %37, align 8, !tbaa !14
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %7) #20
  store i64 %45, ptr %7, align 8, !tbaa !12
  %46 = icmp ugt i64 %45, 15
  br i1 %46, label %47, label %50

47:                                               ; preds = %35
  %48 = call noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32) %40, ptr noundef nonnull align 8 dereferenceable(8) %7, i64 noundef 0) #20
  store ptr %48, ptr %40, align 8, !tbaa !5
  %49 = load i64, ptr %7, align 8, !tbaa !12
  store i64 %49, ptr %43, align 8, !tbaa !16
  br label %50

50:                                               ; preds = %47, %35
  %51 = phi ptr [ %48, %47 ], [ %43, %35 ]
  switch i64 %45, label %54 [
    i64 1, label %52
    i64 0, label %55
  ]

52:                                               ; preds = %50
  %53 = load i8, ptr %44, align 1, !tbaa !16
  store i8 %53, ptr %51, align 1, !tbaa !16
  br label %55

54:                                               ; preds = %50
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %51, ptr align 1 %44, i64 %45, i1 false)
  br label %55

55:                                               ; preds = %54, %52, %50
  %56 = load i64, ptr %7, align 8, !tbaa !12
  %57 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %40, i64 0, i32 1
  store i64 %56, ptr %57, align 8, !tbaa !14
  %58 = load ptr, ptr %40, align 8, !tbaa !5
  %59 = getelementptr inbounds i8, ptr %58, i64 %56
  store i8 0, ptr %59, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %7) #20
  %60 = getelementptr inbounds %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data", ptr %0, i64 0, i32 1
  store ptr %41, ptr %60, align 8, !tbaa !20
  %61 = load ptr, ptr %9, align 8, !tbaa !5
  %62 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %9, i64 0, i32 2
  %63 = icmp eq ptr %61, %62
  br i1 %63, label %64, label %68

64:                                               ; preds = %55
  %65 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %9, i64 0, i32 1
  %66 = load i64, ptr %65, align 8, !tbaa !14
  %67 = icmp ult i64 %66, 16
  call void @llvm.assume(i1 %67)
  br label %69

68:                                               ; preds = %55
  call void @_ZdlPv(ptr noundef %61) #23
  br label %69

69:                                               ; preds = %64, %68
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %9) #20
  br label %159

70:                                               ; preds = %16
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 8 dereferenceable(24) %0, i8 0, i64 24, i1 false)
  %71 = load i64, ptr %18, align 8, !tbaa !14
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %10) #20
  tail call void @llvm.experimental.noalias.scope.decl(metadata !21)
  %72 = load i64, ptr %12, align 8, !tbaa !14, !noalias !21
  %73 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %10, i64 0, i32 2
  store ptr %73, ptr %10, align 8, !tbaa !15, !alias.scope !21
  %74 = load ptr, ptr %1, align 8, !tbaa !5, !noalias !21
  %75 = call noundef i64 @llvm.umin.i64(i64 %72, i64 %20)
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %6) #20, !noalias !21
  store i64 %75, ptr %6, align 8, !tbaa !12, !noalias !21
  %76 = icmp ugt i64 %75, 15
  br i1 %76, label %77, label %80

77:                                               ; preds = %70
  %78 = call noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32) %10, ptr noundef nonnull align 8 dereferenceable(8) %6, i64 noundef 0) #20
  store ptr %78, ptr %10, align 8, !tbaa !5, !alias.scope !21
  %79 = load i64, ptr %6, align 8, !tbaa !12, !noalias !21
  store i64 %79, ptr %73, align 8, !tbaa !16, !alias.scope !21
  br label %80

80:                                               ; preds = %77, %70
  %81 = phi ptr [ %78, %77 ], [ %73, %70 ]
  switch i64 %75, label %84 [
    i64 1, label %82
    i64 0, label %85
  ]

82:                                               ; preds = %80
  %83 = load i8, ptr %74, align 1, !tbaa !16
  store i8 %83, ptr %81, align 1, !tbaa !16
  br label %85

84:                                               ; preds = %80
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %81, ptr align 1 %74, i64 %75, i1 false)
  br label %85

85:                                               ; preds = %80, %82, %84
  %86 = load i64, ptr %6, align 8, !tbaa !12, !noalias !21
  %87 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %10, i64 0, i32 1
  store i64 %86, ptr %87, align 8, !tbaa !14, !alias.scope !21
  %88 = load ptr, ptr %10, align 8, !tbaa !5, !alias.scope !21
  %89 = getelementptr inbounds i8, ptr %88, i64 %86
  store i8 0, ptr %89, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %6) #20, !noalias !21
  %90 = getelementptr inbounds %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data", ptr %0, i64 0, i32 1
  %91 = getelementptr inbounds %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data", ptr %0, i64 0, i32 2
  call void @_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_appendIJS5_EEEvDpOT_(ptr noundef nonnull align 8 dereferenceable(24) %0, ptr noundef nonnull align 8 dereferenceable(32) %10)
  %92 = load ptr, ptr %10, align 8, !tbaa !5
  %93 = icmp eq ptr %92, %73
  br i1 %93, label %94, label %97

94:                                               ; preds = %85
  %95 = load i64, ptr %87, align 8, !tbaa !14
  %96 = icmp ult i64 %95, 16
  call void @llvm.assume(i1 %96)
  br label %98

97:                                               ; preds = %85
  call void @_ZdlPv(ptr noundef %92) #23
  br label %98

98:                                               ; preds = %97, %94
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %10) #20
  %99 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %11, i64 0, i32 2
  %100 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %11, i64 0, i32 1
  br label %101

101:                                              ; preds = %98, %157
  %102 = phi i64 [ %20, %98 ], [ %106, %157 ]
  %103 = add i64 %102, %71
  %104 = load ptr, ptr %2, align 8, !tbaa !5
  %105 = load i64, ptr %18, align 8, !tbaa !14
  %106 = call noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEPKcmm(ptr noundef nonnull align 8 dereferenceable(32) %1, ptr noundef %104, i64 noundef %103, i64 noundef %105) #20
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %11) #20
  call void @llvm.experimental.noalias.scope.decl(metadata !24)
  %107 = load i64, ptr %12, align 8, !tbaa !14, !noalias !24
  %108 = icmp ult i64 %107, %103
  br i1 %108, label %109, label %110

109:                                              ; preds = %101
  call void (ptr, ...) @_ZSt24__throw_out_of_range_fmtPKcz(ptr noundef nonnull @.str.22, ptr noundef nonnull @.str.21, i64 noundef %103, i64 noundef %107) #24, !noalias !24
  unreachable

110:                                              ; preds = %101
  %111 = sub i64 %106, %103
  store ptr %99, ptr %11, align 8, !tbaa !15, !alias.scope !24
  %112 = load ptr, ptr %1, align 8, !tbaa !5, !noalias !24
  %113 = getelementptr inbounds i8, ptr %112, i64 %103
  %114 = sub i64 %107, %103
  %115 = call noundef i64 @llvm.umin.i64(i64 %114, i64 %111)
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %5) #20, !noalias !24
  store i64 %115, ptr %5, align 8, !tbaa !12, !noalias !24
  %116 = icmp ugt i64 %115, 15
  br i1 %116, label %117, label %120

117:                                              ; preds = %110
  %118 = call noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32) %11, ptr noundef nonnull align 8 dereferenceable(8) %5, i64 noundef 0) #20
  store ptr %118, ptr %11, align 8, !tbaa !5, !alias.scope !24
  %119 = load i64, ptr %5, align 8, !tbaa !12, !noalias !24
  store i64 %119, ptr %99, align 8, !tbaa !16, !alias.scope !24
  br label %120

120:                                              ; preds = %117, %110
  %121 = phi ptr [ %118, %117 ], [ %99, %110 ]
  switch i64 %115, label %124 [
    i64 1, label %122
    i64 0, label %125
  ]

122:                                              ; preds = %120
  %123 = load i8, ptr %113, align 1, !tbaa !16
  store i8 %123, ptr %121, align 1, !tbaa !16
  br label %125

124:                                              ; preds = %120
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %121, ptr align 1 %113, i64 %115, i1 false)
  br label %125

125:                                              ; preds = %120, %122, %124
  %126 = load i64, ptr %5, align 8, !tbaa !12, !noalias !24
  store i64 %126, ptr %100, align 8, !tbaa !14, !alias.scope !24
  %127 = load ptr, ptr %11, align 8, !tbaa !5, !alias.scope !24
  %128 = getelementptr inbounds i8, ptr %127, i64 %126
  store i8 0, ptr %128, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %5) #20, !noalias !24
  %129 = load i64, ptr %100, align 8, !tbaa !14
  %130 = icmp eq i64 %129, 0
  %131 = and i1 %130, %3
  br i1 %131, label %150, label %132

132:                                              ; preds = %125
  %133 = load ptr, ptr %90, align 8, !tbaa !20
  %134 = load ptr, ptr %91, align 8, !tbaa !19
  %135 = icmp eq ptr %133, %134
  br i1 %135, label %149, label %136

136:                                              ; preds = %132
  %137 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %133, i64 0, i32 2
  store ptr %137, ptr %133, align 8, !tbaa !15
  %138 = load ptr, ptr %11, align 8, !tbaa !5
  %139 = icmp eq ptr %138, %99
  br i1 %139, label %140, label %143

140:                                              ; preds = %136
  %141 = icmp ult i64 %129, 16
  call void @llvm.assume(i1 %141)
  %142 = add nuw nsw i64 %129, 1
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(1) %137, ptr noundef nonnull align 8 dereferenceable(1) %99, i64 %142, i1 false)
  br label %145

143:                                              ; preds = %136
  store ptr %138, ptr %133, align 8, !tbaa !5
  %144 = load i64, ptr %99, align 8, !tbaa !16
  store i64 %144, ptr %137, align 8, !tbaa !16
  br label %145

145:                                              ; preds = %143, %140
  %146 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %133, i64 0, i32 1
  store i64 %129, ptr %146, align 8, !tbaa !14
  store ptr %99, ptr %11, align 8, !tbaa !5
  store i64 0, ptr %100, align 8, !tbaa !14
  store i8 0, ptr %99, align 8, !tbaa !16
  %147 = load ptr, ptr %90, align 8, !tbaa !20
  %148 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %147, i64 1
  store ptr %148, ptr %90, align 8, !tbaa !20
  br label %150

149:                                              ; preds = %132
  call void @_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_appendIJS5_EEEvDpOT_(ptr noundef nonnull align 8 dereferenceable(24) %0, ptr noundef nonnull align 8 dereferenceable(32) %11)
  br label %150

150:                                              ; preds = %149, %145, %125
  %151 = load ptr, ptr %11, align 8, !tbaa !5
  %152 = icmp eq ptr %151, %99
  br i1 %152, label %153, label %156

153:                                              ; preds = %150
  %154 = load i64, ptr %100, align 8, !tbaa !14
  %155 = icmp ult i64 %154, 16
  call void @llvm.assume(i1 %155)
  br label %157

156:                                              ; preds = %150
  call void @_ZdlPv(ptr noundef %151) #23
  br label %157

157:                                              ; preds = %153, %156
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %11) #20
  %158 = icmp eq i64 %106, -1
  br i1 %158, label %159, label %101, !llvm.loop !27

159:                                              ; preds = %157, %69, %15
  ret void
}

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #4

; Function Attrs: mustprogress nounwind sspstrong uwtable
define dso_local noundef zeroext i1 @_Z7matchescPKc(i8 noundef signext %0, ptr noundef readonly %1) local_unnamed_addr #0 {
  %3 = alloca i64, align 8
  %4 = alloca %"class.std::__cxx11::basic_string", align 8
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %4) #20
  %5 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %4, i64 0, i32 2
  store ptr %5, ptr %4, align 8, !tbaa !15
  %6 = icmp eq ptr %1, null
  br i1 %6, label %7, label %8

7:                                                ; preds = %2
  call void @_ZSt19__throw_logic_errorPKc(ptr noundef nonnull @.str.25) #24
  unreachable

8:                                                ; preds = %2
  %9 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %1) #20
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %3) #20
  store i64 %9, ptr %3, align 8, !tbaa !12
  %10 = icmp ugt i64 %9, 15
  br i1 %10, label %11, label %14

11:                                               ; preds = %8
  %12 = call noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32) %4, ptr noundef nonnull align 8 dereferenceable(8) %3, i64 noundef 0) #20
  store ptr %12, ptr %4, align 8, !tbaa !5
  %13 = load i64, ptr %3, align 8, !tbaa !12
  store i64 %13, ptr %5, align 8, !tbaa !16
  br label %14

14:                                               ; preds = %11, %8
  %15 = phi ptr [ %12, %11 ], [ %5, %8 ]
  switch i64 %9, label %18 [
    i64 1, label %16
    i64 0, label %19
  ]

16:                                               ; preds = %14
  %17 = load i8, ptr %1, align 1, !tbaa !16
  store i8 %17, ptr %15, align 1, !tbaa !16
  br label %19

18:                                               ; preds = %14
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %15, ptr nonnull align 1 %1, i64 %9, i1 false)
  br label %19

19:                                               ; preds = %14, %16, %18
  %20 = load i64, ptr %3, align 8, !tbaa !12
  %21 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %4, i64 0, i32 1
  store i64 %20, ptr %21, align 8, !tbaa !14
  %22 = load ptr, ptr %4, align 8, !tbaa !5
  %23 = getelementptr inbounds i8, ptr %22, i64 %20
  store i8 0, ptr %23, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %3) #20
  %24 = call noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcm(ptr noundef nonnull align 8 dereferenceable(32) %4, i8 noundef signext %0, i64 noundef 0) #20
  %25 = load ptr, ptr %4, align 8, !tbaa !5
  %26 = icmp eq ptr %25, %5
  br i1 %26, label %27, label %30

27:                                               ; preds = %19
  %28 = load i64, ptr %21, align 8, !tbaa !14
  %29 = icmp ult i64 %28, 16
  call void @llvm.assume(i1 %29)
  br label %31

30:                                               ; preds = %19
  call void @_ZdlPv(ptr noundef %25) #23
  br label %31

31:                                               ; preds = %27, %30
  %32 = icmp ne i64 %24, -1
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %4) #20
  ret i1 %32
}

; Function Attrs: nounwind
declare noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcm(ptr noundef nonnull align 8 dereferenceable(32), i8 noundef signext, i64 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress norecurse nounwind sspstrong uwtable
define dso_local noundef i32 @main(i32 noundef %0, ptr nocapture noundef readonly %1) local_unnamed_addr #5 {
  %3 = alloca ptr, align 8
  %4 = alloca %"class.std::__cxx11::basic_string", align 8
  %5 = alloca %"class.std::__cxx11::basic_string", align 8
  %6 = alloca %"class.std::__cxx11::basic_string", align 8
  %7 = alloca %"class.std::__cxx11::basic_string", align 8
  %8 = alloca i64, align 8
  %9 = alloca %"class.std::vector", align 8
  %10 = alloca %"class.std::__cxx11::basic_string", align 8
  %11 = alloca %"class.std::__cxx11::basic_string", align 8
  %12 = alloca i32, align 4
  %13 = alloca %struct.termios, align 4
  %14 = alloca i8, align 1
  %15 = alloca [2 x i32], align 4
  %16 = alloca %"class.std::thread", align 8
  %17 = alloca %class.anon, align 8
  %18 = alloca %struct.fd_set, align 8
  %19 = alloca %struct.timeval, align 8
  %20 = alloca i8, align 1
  %21 = add i32 %0, -4
  %22 = icmp ult i32 %21, -2
  br i1 %22, label %23, label %25

23:                                               ; preds = %2
  %24 = tail call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str, i64 noundef 46) #20
  br label %424

25:                                               ; preds = %2
  %26 = getelementptr inbounds ptr, ptr %1, i64 1
  %27 = load ptr, ptr %26, align 8, !tbaa !13
  %28 = icmp eq i32 %0, 3
  br i1 %28, label %29, label %208

29:                                               ; preds = %25
  call void @llvm.lifetime.start.p0(i64 24, ptr nonnull %9) #20
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %10) #20
  %30 = getelementptr inbounds ptr, ptr %1, i64 2
  %31 = load ptr, ptr %30, align 8, !tbaa !13
  %32 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %10, i64 0, i32 2
  store ptr %32, ptr %10, align 8, !tbaa !15
  %33 = icmp eq ptr %31, null
  br i1 %33, label %34, label %35

34:                                               ; preds = %29
  call void @_ZSt19__throw_logic_errorPKc(ptr noundef nonnull @.str.25) #24
  unreachable

35:                                               ; preds = %29
  %36 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %31) #20
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %8) #20
  store i64 %36, ptr %8, align 8, !tbaa !12
  %37 = icmp ugt i64 %36, 15
  br i1 %37, label %38, label %41

38:                                               ; preds = %35
  %39 = call noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32) %10, ptr noundef nonnull align 8 dereferenceable(8) %8, i64 noundef 0) #20
  store ptr %39, ptr %10, align 8, !tbaa !5
  %40 = load i64, ptr %8, align 8, !tbaa !12
  store i64 %40, ptr %32, align 8, !tbaa !16
  br label %41

41:                                               ; preds = %38, %35
  %42 = phi ptr [ %39, %38 ], [ %32, %35 ]
  switch i64 %36, label %45 [
    i64 1, label %43
    i64 0, label %46
  ]

43:                                               ; preds = %41
  %44 = load i8, ptr %31, align 1, !tbaa !16
  store i8 %44, ptr %42, align 1, !tbaa !16
  br label %46

45:                                               ; preds = %41
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %42, ptr nonnull align 1 %31, i64 %36, i1 false)
  br label %46

46:                                               ; preds = %41, %43, %45
  %47 = load i64, ptr %8, align 8, !tbaa !12
  %48 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %10, i64 0, i32 1
  store i64 %47, ptr %48, align 8, !tbaa !14
  %49 = load ptr, ptr %10, align 8, !tbaa !5
  %50 = getelementptr inbounds i8, ptr %49, i64 %47
  store i8 0, ptr %50, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %8) #20
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %11) #20
  %51 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %11, i64 0, i32 2
  store ptr %51, ptr %11, align 8, !tbaa !15
  store i8 44, ptr %51, align 8, !tbaa !16
  %52 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %11, i64 0, i32 1
  store i64 1, ptr %52, align 8, !tbaa !14
  %53 = getelementptr inbounds i8, ptr %11, i64 17
  store i8 0, ptr %53, align 1, !tbaa !16
  call void @_Z5splitRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES6_b(ptr dead_on_unwind nonnull writable sret(%"class.std::vector") align 8 %9, ptr noundef nonnull align 8 dereferenceable(32) %10, ptr noundef nonnull align 8 dereferenceable(32) %11, i1 noundef zeroext true)
  %54 = load ptr, ptr %11, align 8, !tbaa !5
  %55 = icmp eq ptr %54, %51
  br i1 %55, label %56, label %59

56:                                               ; preds = %46
  %57 = load i64, ptr %52, align 8, !tbaa !14
  %58 = icmp ult i64 %57, 16
  call void @llvm.assume(i1 %58)
  br label %60

59:                                               ; preds = %46
  call void @_ZdlPv(ptr noundef %54) #23
  br label %60

60:                                               ; preds = %56, %59
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %11) #20
  %61 = load ptr, ptr %10, align 8, !tbaa !5
  %62 = icmp eq ptr %61, %32
  br i1 %62, label %63, label %66

63:                                               ; preds = %60
  %64 = load i64, ptr %48, align 8, !tbaa !14
  %65 = icmp ult i64 %64, 16
  call void @llvm.assume(i1 %65)
  br label %67

66:                                               ; preds = %60
  call void @_ZdlPv(ptr noundef %61) #23
  br label %67

67:                                               ; preds = %63, %66
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %10) #20
  %68 = load ptr, ptr %9, align 8, !tbaa !13
  %69 = getelementptr inbounds %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data", ptr %9, i64 0, i32 1
  %70 = load ptr, ptr %69, align 8, !tbaa !13
  %71 = icmp eq ptr %68, %70
  br i1 %71, label %169, label %72

72:                                               ; preds = %67
  %73 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %7, i64 0, i32 2
  %74 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %7, i64 0, i32 1
  %75 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %6, i64 0, i32 2
  %76 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %6, i64 0, i32 1
  %77 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %5, i64 0, i32 2
  %78 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %5, i64 0, i32 1
  %79 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %4, i64 0, i32 2
  %80 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %4, i64 0, i32 1
  %81 = getelementptr inbounds i8, ptr %7, i64 21
  %82 = getelementptr inbounds i8, ptr %6, i64 19
  %83 = getelementptr inbounds i8, ptr %5, i64 20
  %84 = getelementptr inbounds i8, ptr %4, i64 18
  br label %85

85:                                               ; preds = %72, %155
  %86 = phi i64 [ 115200, %72 ], [ %160, %155 ]
  %87 = phi i8 [ 110, %72 ], [ %159, %155 ]
  %88 = phi i32 [ 2, %72 ], [ %158, %155 ]
  %89 = phi i8 [ 78, %72 ], [ %157, %155 ]
  %90 = phi i32 [ 8, %72 ], [ %156, %155 ]
  %91 = phi ptr [ %68, %72 ], [ %161, %155 ]
  %92 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %91, i64 0, i32 1
  %93 = load i64, ptr %92, align 8, !tbaa !14
  %94 = load ptr, ptr %91, align 8, !tbaa !5
  switch i64 %93, label %146 [
    i64 1, label %95
    i64 3, label %143
  ]

95:                                               ; preds = %85
  %96 = load i8, ptr %94, align 1, !tbaa !16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %7) #20
  store ptr %73, ptr %7, align 8, !tbaa !15
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(5) %73, ptr noundef nonnull align 1 dereferenceable(5) @.str.2, i64 5, i1 false)
  store i64 5, ptr %74, align 8, !tbaa !14
  store i8 0, ptr %81, align 1, !tbaa !16
  %97 = call noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcm(ptr noundef nonnull align 8 dereferenceable(32) %7, i8 noundef signext %96, i64 noundef 0) #20
  %98 = load ptr, ptr %7, align 8, !tbaa !5
  %99 = icmp eq ptr %98, %73
  br i1 %99, label %100, label %103

100:                                              ; preds = %95
  %101 = load i64, ptr %74, align 8, !tbaa !14
  %102 = icmp ult i64 %101, 16
  call void @llvm.assume(i1 %102)
  br label %104

103:                                              ; preds = %95
  call void @_ZdlPv(ptr noundef %98) #23
  br label %104

104:                                              ; preds = %100, %103
  %105 = icmp eq i64 %97, -1
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %7) #20
  br i1 %105, label %106, label %155

106:                                              ; preds = %104
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %6) #20
  store ptr %75, ptr %6, align 8, !tbaa !15
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(3) %75, ptr noundef nonnull align 1 dereferenceable(3) @.str.3, i64 3, i1 false)
  store i64 3, ptr %76, align 8, !tbaa !14
  store i8 0, ptr %82, align 1, !tbaa !16
  %107 = call noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcm(ptr noundef nonnull align 8 dereferenceable(32) %6, i8 noundef signext %96, i64 noundef 0) #20
  %108 = load ptr, ptr %6, align 8, !tbaa !5
  %109 = icmp eq ptr %108, %75
  br i1 %109, label %110, label %113

110:                                              ; preds = %106
  %111 = load i64, ptr %76, align 8, !tbaa !14
  %112 = icmp ult i64 %111, 16
  call void @llvm.assume(i1 %112)
  br label %114

113:                                              ; preds = %106
  call void @_ZdlPv(ptr noundef %108) #23
  br label %114

114:                                              ; preds = %110, %113
  %115 = icmp eq i64 %107, -1
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %6) #20
  br i1 %115, label %116, label %155

116:                                              ; preds = %114
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %5) #20
  store ptr %77, ptr %5, align 8, !tbaa !15
  store i32 943142453, ptr %77, align 8
  store i64 4, ptr %78, align 8, !tbaa !14
  store i8 0, ptr %83, align 4, !tbaa !16
  %117 = call noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcm(ptr noundef nonnull align 8 dereferenceable(32) %5, i8 noundef signext %96, i64 noundef 0) #20
  %118 = load ptr, ptr %5, align 8, !tbaa !5
  %119 = icmp eq ptr %118, %77
  br i1 %119, label %120, label %123

120:                                              ; preds = %116
  %121 = load i64, ptr %78, align 8, !tbaa !14
  %122 = icmp ult i64 %121, 16
  call void @llvm.assume(i1 %122)
  br label %124

123:                                              ; preds = %116
  call void @_ZdlPv(ptr noundef %118) #23
  br label %124

124:                                              ; preds = %120, %123
  %125 = icmp eq i64 %117, -1
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %5) #20
  br i1 %125, label %129, label %126

126:                                              ; preds = %124
  %127 = sext i8 %96 to i32
  %128 = add nsw i32 %127, -48
  br label %155

129:                                              ; preds = %124
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %4) #20
  store ptr %79, ptr %4, align 8, !tbaa !15
  store i16 12849, ptr %79, align 8
  store i64 2, ptr %80, align 8, !tbaa !14
  store i8 0, ptr %84, align 2, !tbaa !16
  %130 = call noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcm(ptr noundef nonnull align 8 dereferenceable(32) %4, i8 noundef signext %96, i64 noundef 0) #20
  %131 = load ptr, ptr %4, align 8, !tbaa !5
  %132 = icmp eq ptr %131, %79
  br i1 %132, label %133, label %136

133:                                              ; preds = %129
  %134 = load i64, ptr %80, align 8, !tbaa !14
  %135 = icmp ult i64 %134, 16
  call void @llvm.assume(i1 %135)
  br label %137

136:                                              ; preds = %129
  call void @_ZdlPv(ptr noundef %131) #23
  br label %137

137:                                              ; preds = %133, %136
  %138 = icmp eq i64 %130, -1
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %4) #20
  br i1 %138, label %163, label %139

139:                                              ; preds = %137
  %140 = sext i8 %96 to i32
  %141 = shl nsw i32 %140, 1
  %142 = add nsw i32 %141, -96
  br label %155

143:                                              ; preds = %85
  %144 = call i32 @bcmp(ptr noundef nonnull dereferenceable(3) %94, ptr noundef nonnull dereferenceable(3) @.str.8, i64 3)
  %145 = icmp eq i32 %144, 0
  br i1 %145, label %155, label %146

146:                                              ; preds = %85, %143
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %3) #20
  %147 = call i64 @__isoc23_strtoull(ptr noundef %94, ptr noundef nonnull %3, i32 noundef 10) #20
  %148 = load ptr, ptr %3, align 8, !tbaa !13
  %149 = load ptr, ptr %91, align 8, !tbaa !5
  %150 = ptrtoint ptr %148 to i64
  %151 = ptrtoint ptr %149 to i64
  %152 = sub i64 %150, %151
  %153 = load i64, ptr %92, align 8, !tbaa !14
  %154 = icmp eq i64 %152, %153
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %3) #20
  br i1 %154, label %155, label %163

155:                                              ; preds = %146, %126, %139, %104, %114, %143
  %156 = phi i32 [ %90, %143 ], [ %90, %114 ], [ %90, %104 ], [ %90, %139 ], [ %128, %126 ], [ %90, %146 ]
  %157 = phi i8 [ %89, %143 ], [ %96, %114 ], [ %89, %104 ], [ %89, %139 ], [ %89, %126 ], [ %89, %146 ]
  %158 = phi i32 [ 3, %143 ], [ %88, %114 ], [ %88, %104 ], [ %142, %139 ], [ %88, %126 ], [ %88, %146 ]
  %159 = phi i8 [ %87, %143 ], [ %87, %114 ], [ %96, %104 ], [ %87, %139 ], [ %87, %126 ], [ %87, %146 ]
  %160 = phi i64 [ %86, %143 ], [ %86, %114 ], [ %86, %104 ], [ %86, %139 ], [ %86, %126 ], [ %147, %146 ]
  %161 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %91, i64 1
  %162 = icmp eq ptr %161, %70
  br i1 %162, label %169, label %85

163:                                              ; preds = %146, %137
  %164 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.6, i64 noundef 18) #20
  %165 = load ptr, ptr %91, align 8, !tbaa !5
  %166 = load i64, ptr %92, align 8, !tbaa !14
  %167 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef %165, i64 noundef %166) #20
  %168 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %167, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %169

169:                                              ; preds = %155, %163, %67
  %170 = phi i32 [ 8, %67 ], [ %90, %163 ], [ %156, %155 ]
  %171 = phi i8 [ 78, %67 ], [ %89, %163 ], [ %157, %155 ]
  %172 = phi i32 [ 2, %67 ], [ %88, %163 ], [ %158, %155 ]
  %173 = phi i8 [ 110, %67 ], [ %87, %163 ], [ %159, %155 ]
  %174 = phi i64 [ 115200, %67 ], [ %86, %163 ], [ %160, %155 ]
  %175 = phi i1 [ true, %67 ], [ false, %163 ], [ true, %155 ]
  %176 = phi i32 [ 0, %67 ], [ 1, %163 ], [ 0, %155 ]
  %177 = load ptr, ptr %9, align 8, !tbaa !17
  %178 = load ptr, ptr %69, align 8, !tbaa !20
  %179 = icmp eq ptr %177, %178
  br i1 %179, label %195, label %180

180:                                              ; preds = %169, %190
  %181 = phi ptr [ %191, %190 ], [ %177, %169 ]
  %182 = load ptr, ptr %181, align 8, !tbaa !5
  %183 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %181, i64 0, i32 2
  %184 = icmp eq ptr %182, %183
  br i1 %184, label %185, label %189

185:                                              ; preds = %180
  %186 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %181, i64 0, i32 1
  %187 = load i64, ptr %186, align 8, !tbaa !14
  %188 = icmp ult i64 %187, 16
  call void @llvm.assume(i1 %188)
  br label %190

189:                                              ; preds = %180
  call void @_ZdlPv(ptr noundef %182) #23
  br label %190

190:                                              ; preds = %189, %185
  %191 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %181, i64 1
  %192 = icmp eq ptr %191, %178
  br i1 %192, label %193, label %180, !llvm.loop !29

193:                                              ; preds = %190
  %194 = load ptr, ptr %9, align 8, !tbaa !17
  br label %195

195:                                              ; preds = %193, %169
  %196 = phi ptr [ %194, %193 ], [ %177, %169 ]
  %197 = icmp eq ptr %196, null
  br i1 %197, label %199, label %198

198:                                              ; preds = %195
  call void @_ZdlPv(ptr noundef nonnull %196) #23
  br label %199

199:                                              ; preds = %195, %198
  call void @llvm.lifetime.end.p0(i64 24, ptr nonnull %9) #20
  br i1 %175, label %200, label %424

200:                                              ; preds = %199
  %201 = icmp eq i32 %172, 3
  %202 = icmp ne i32 %170, 5
  %203 = select i1 %201, i1 %202, i1 false
  br i1 %203, label %204, label %208

204:                                              ; preds = %200
  %205 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.9, i64 noundef 43) #20
  %206 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSolsEi(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, i32 noundef %170) #20
  %207 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %206, ptr noundef nonnull @.str.10, i64 noundef 14) #20
  br label %424

208:                                              ; preds = %25, %200
  %209 = phi i64 [ %174, %200 ], [ 115200, %25 ]
  %210 = phi i8 [ %173, %200 ], [ 110, %25 ]
  %211 = phi i32 [ %172, %200 ], [ 2, %25 ]
  %212 = phi i8 [ %171, %200 ], [ 78, %25 ]
  %213 = phi i32 [ %170, %200 ], [ 8, %25 ]
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %12) #20
  %214 = call i32 (ptr, i32, ...) @open(ptr noundef %27, i32 noundef 1054978) #20
  store i32 %214, ptr %12, align 4, !tbaa !30
  %215 = icmp slt i32 %214, 0
  br i1 %215, label %216, label %249

216:                                              ; preds = %208
  %217 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.11, i64 noundef 14) #20
  %218 = icmp eq ptr %27, null
  br i1 %218, label %219, label %227

219:                                              ; preds = %216
  %220 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %221 = getelementptr i8, ptr %220, i64 -24
  %222 = load i64, ptr %221, align 8
  %223 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %222
  %224 = getelementptr inbounds %"class.std::ios_base", ptr %223, i64 0, i32 5
  %225 = load i32, ptr %224, align 8, !tbaa !34
  %226 = or i32 %225, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %223, i32 noundef %226) #20
  br label %230

227:                                              ; preds = %216
  %228 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %27) #20
  %229 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %27, i64 noundef %228) #20
  br label %230

230:                                              ; preds = %219, %227
  %231 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.12, i64 noundef 2) #20
  %232 = tail call ptr @__errno_location() #25
  %233 = load i32, ptr %232, align 4, !tbaa !30
  %234 = call ptr @strerror(i32 noundef %233) #20
  %235 = icmp eq ptr %234, null
  br i1 %235, label %236, label %244

236:                                              ; preds = %230
  %237 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %238 = getelementptr i8, ptr %237, i64 -24
  %239 = load i64, ptr %238, align 8
  %240 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %239
  %241 = getelementptr inbounds %"class.std::ios_base", ptr %240, i64 0, i32 5
  %242 = load i32, ptr %241, align 8, !tbaa !34
  %243 = or i32 %242, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %240, i32 noundef %243) #20
  br label %247

244:                                              ; preds = %230
  %245 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %234) #20
  %246 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %234, i64 noundef %245) #20
  br label %247

247:                                              ; preds = %236, %244
  %248 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %422

249:                                              ; preds = %208
  %250 = call i32 (i32, i32, ...) @fcntl(i32 noundef %214, i32 noundef 4, i32 noundef 0) #20
  %251 = icmp eq i32 %250, -1
  br i1 %251, label %252, label %271

252:                                              ; preds = %249
  %253 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.13, i64 noundef 14) #20
  %254 = tail call ptr @__errno_location() #25
  %255 = load i32, ptr %254, align 4, !tbaa !30
  %256 = call ptr @strerror(i32 noundef %255) #20
  %257 = icmp eq ptr %256, null
  br i1 %257, label %258, label %266

258:                                              ; preds = %252
  %259 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %260 = getelementptr i8, ptr %259, i64 -24
  %261 = load i64, ptr %260, align 8
  %262 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %261
  %263 = getelementptr inbounds %"class.std::ios_base", ptr %262, i64 0, i32 5
  %264 = load i32, ptr %263, align 8, !tbaa !34
  %265 = or i32 %264, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %262, i32 noundef %265) #20
  br label %269

266:                                              ; preds = %252
  %267 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %256) #20
  %268 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %256, i64 noundef %267) #20
  br label %269

269:                                              ; preds = %258, %266
  %270 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %422

271:                                              ; preds = %249
  call void @llvm.lifetime.start.p0(i64 60, ptr nonnull %13) #20
  %272 = call i32 @tcgetattr(i32 noundef %214, ptr noundef nonnull %13) #20
  %273 = icmp eq i32 %272, 0
  br i1 %273, label %293, label %274

274:                                              ; preds = %271
  %275 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.14, i64 noundef 18) #20
  %276 = tail call ptr @__errno_location() #25
  %277 = load i32, ptr %276, align 4, !tbaa !30
  %278 = call ptr @strerror(i32 noundef %277) #20
  %279 = icmp eq ptr %278, null
  br i1 %279, label %280, label %288

280:                                              ; preds = %274
  %281 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %282 = getelementptr i8, ptr %281, i64 -24
  %283 = load i64, ptr %282, align 8
  %284 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %283
  %285 = getelementptr inbounds %"class.std::ios_base", ptr %284, i64 0, i32 5
  %286 = load i32, ptr %285, align 8, !tbaa !34
  %287 = or i32 %286, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %284, i32 noundef %287) #20
  br label %291

288:                                              ; preds = %274
  %289 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %278) #20
  %290 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %278, i64 noundef %289) #20
  br label %291

291:                                              ; preds = %280, %288
  %292 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %420

293:                                              ; preds = %271
  %294 = trunc i64 %209 to i32
  %295 = call i32 @cfsetspeed(ptr noundef nonnull %13, i32 noundef %294) #20
  %296 = getelementptr inbounds %struct.termios, ptr %13, i64 0, i32 2
  %297 = load i32, ptr %296, align 4, !tbaa !40
  %298 = and i32 %297, -49
  store i32 %298, ptr %296, align 4, !tbaa !40
  switch i32 %213, label %305 [
    i32 5, label %309
    i32 6, label %299
    i32 7, label %301
    i32 8, label %303
  ]

299:                                              ; preds = %293
  %300 = or disjoint i32 %298, 16
  br label %309

301:                                              ; preds = %293
  %302 = or disjoint i32 %298, 32
  br label %309

303:                                              ; preds = %293
  %304 = or i32 %297, 48
  br label %309

305:                                              ; preds = %293
  %306 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.15, i64 noundef 19) #20
  %307 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSolsEi(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, i32 noundef %213) #20
  %308 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %307, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %420

309:                                              ; preds = %293, %303, %301, %299
  %310 = phi i32 [ %304, %303 ], [ %302, %301 ], [ %300, %299 ], [ %298, %293 ]
  %311 = load i32, ptr %13, align 4, !tbaa !42
  %312 = getelementptr inbounds %struct.termios, ptr %13, i64 0, i32 3
  store i32 0, ptr %312, align 4, !tbaa !43
  %313 = getelementptr inbounds %struct.termios, ptr %13, i64 0, i32 1
  store i32 0, ptr %313, align 4, !tbaa !44
  %314 = getelementptr inbounds %struct.termios, ptr %13, i64 0, i32 5, i64 6
  store i8 0, ptr %314, align 1, !tbaa !16
  %315 = getelementptr inbounds %struct.termios, ptr %13, i64 0, i32 5, i64 5
  store i8 5, ptr %315, align 2, !tbaa !16
  %316 = and i32 %311, -7170
  %317 = icmp eq i8 %212, 88
  %318 = or disjoint i32 %316, 5120
  %319 = select i1 %317, i32 %318, i32 %316
  store i32 %319, ptr %13, align 4, !tbaa !42
  %320 = and i32 %310, -1073744769
  %321 = or disjoint i32 %320, 2176
  store i32 %321, ptr %296, align 4, !tbaa !40
  switch i8 %210, label %330 [
    i8 101, label %322
    i8 111, label %324
    i8 109, label %326
    i8 115, label %328
    i8 110, label %335
  ]

322:                                              ; preds = %309
  %323 = or disjoint i32 %320, 2432
  br label %335

324:                                              ; preds = %309
  %325 = or disjoint i32 %320, 2944
  br label %335

326:                                              ; preds = %309
  %327 = or i32 %310, 1073744768
  br label %335

328:                                              ; preds = %309
  %329 = or disjoint i32 %320, 1073744256
  br label %335

330:                                              ; preds = %309
  %331 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.16, i64 noundef 16) #20
  %332 = sext i8 %210 to i32
  %333 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSolsEi(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, i32 noundef %332) #20
  %334 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %333, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %420

335:                                              ; preds = %309, %328, %326, %324, %322
  %336 = phi i32 [ %321, %309 ], [ %329, %328 ], [ %327, %326 ], [ %325, %324 ], [ %323, %322 ]
  %337 = icmp eq i32 %211, 2
  %338 = and i32 %336, 2147483583
  %339 = select i1 %337, i32 0, i32 64
  %340 = icmp eq i8 %212, 82
  %341 = select i1 %340, i32 -2147483648, i32 0
  %342 = or disjoint i32 %341, %339
  %343 = or disjoint i32 %342, %338
  store i32 %343, ptr %296, align 4, !tbaa !40
  %344 = call i32 @tcsetattr(i32 noundef %214, i32 noundef 0, ptr noundef nonnull %13) #20
  %345 = icmp eq i32 %344, 0
  br i1 %345, label %353, label %346

346:                                              ; preds = %335
  %347 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.17, i64 noundef 18) #20
  %348 = tail call ptr @__errno_location() #25
  %349 = load i32, ptr %348, align 4, !tbaa !30
  %350 = call ptr @strerror(i32 noundef %349) #20
  %351 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef %350)
  %352 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %351, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %420

353:                                              ; preds = %335
  call void @llvm.lifetime.start.p0(i64 1, ptr nonnull %14) #20
  store i8 1, ptr %14, align 1, !tbaa !45
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %15) #20
  %354 = call i32 @pipe(ptr noundef nonnull %15) #20
  %355 = icmp slt i32 %354, 0
  br i1 %355, label %356, label %363

356:                                              ; preds = %353
  %357 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.18, i64 noundef 13) #20
  %358 = tail call ptr @__errno_location() #25
  %359 = load i32, ptr %358, align 4, !tbaa !30
  %360 = call ptr @strerror(i32 noundef %359) #20
  %361 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef %360)
  %362 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %361, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %418

363:                                              ; preds = %353
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %16) #20
  call void @llvm.lifetime.start.p0(i64 24, ptr nonnull %17) #20
  store ptr %14, ptr %17, align 8, !tbaa !13
  %364 = getelementptr inbounds %class.anon, ptr %17, i64 0, i32 1
  store ptr %15, ptr %364, align 8, !tbaa !13
  %365 = getelementptr inbounds %class.anon, ptr %17, i64 0, i32 2
  store ptr %12, ptr %365, align 8, !tbaa !13
  call fastcc void @"_ZNSt6threadC2IZ4mainE3$_0JEvEEOT_DpOT0_"(ptr noundef nonnull align 8 dereferenceable(8) %16, ptr noundef nonnull align 8 dereferenceable(24) %17)
  call void @llvm.lifetime.end.p0(i64 24, ptr nonnull %17) #20
  call void @llvm.lifetime.start.p0(i64 128, ptr nonnull %18) #20
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 8 dereferenceable(128) %18, i8 0, i64 128, i1 false), !tbaa !12
  %366 = load i32, ptr %12, align 4, !tbaa !30
  %367 = srem i32 %366, 64
  %368 = zext nneg i32 %367 to i64
  %369 = shl nuw i64 1, %368
  %370 = sdiv i32 %366, 64
  %371 = sext i32 %370 to i64
  %372 = getelementptr inbounds [16 x i64], ptr %18, i64 0, i64 %371
  %373 = load i64, ptr %372, align 8, !tbaa !12
  %374 = or i64 %369, %373
  store i64 %374, ptr %372, align 8, !tbaa !12
  %375 = load i32, ptr %15, align 4, !tbaa !30
  %376 = srem i32 %375, 64
  %377 = zext nneg i32 %376 to i64
  %378 = shl nuw i64 1, %377
  %379 = sdiv i32 %375, 64
  %380 = sext i32 %379 to i64
  %381 = getelementptr inbounds [16 x i64], ptr %18, i64 0, i64 %380
  %382 = load i64, ptr %381, align 8, !tbaa !12
  %383 = or i64 %378, %382
  store i64 %383, ptr %381, align 8, !tbaa !12
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %19) #20
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 8 dereferenceable(16) %19, i8 0, i64 16, i1 false)
  call void @llvm.lifetime.start.p0(i64 1, ptr nonnull %20) #20
  %384 = call i32 @select(i32 noundef 2, ptr noundef nonnull %18, ptr noundef null, ptr noundef null, ptr noundef nonnull %19) #20
  %385 = load ptr, ptr @stdout, align 8, !tbaa !13
  %386 = call i32 @fflush(ptr noundef %385)
  %387 = load i8, ptr %14, align 1, !tbaa !45, !range !47, !noundef !48
  %388 = icmp eq i8 %387, 0
  br i1 %388, label %411, label %389

389:                                              ; preds = %363, %405
  %390 = load i32, ptr %12, align 4, !tbaa !30
  %391 = call i64 @read(i32 noundef %390, ptr noundef nonnull %20, i64 noundef 1) #20
  %392 = icmp slt i64 %391, 0
  br i1 %392, label %393, label %400

393:                                              ; preds = %389
  %394 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.19, i64 noundef 16) #20
  %395 = tail call ptr @__errno_location() #25
  %396 = load i32, ptr %395, align 4, !tbaa !30
  %397 = call ptr @strerror(i32 noundef %396) #20
  %398 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef %397)
  %399 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %398, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %412

400:                                              ; preds = %389
  %401 = icmp eq i64 %391, 0
  br i1 %401, label %405, label %402

402:                                              ; preds = %400
  %403 = load i8, ptr %20, align 1, !tbaa !16
  %404 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cout, i8 noundef signext %403)
  br label %405

405:                                              ; preds = %400, %402
  %406 = call i32 @select(i32 noundef 2, ptr noundef nonnull %18, ptr noundef null, ptr noundef null, ptr noundef nonnull %19) #20
  %407 = load ptr, ptr @stdout, align 8, !tbaa !13
  %408 = call i32 @fflush(ptr noundef %407)
  %409 = load i8, ptr %14, align 1, !tbaa !45, !range !47, !noundef !48
  %410 = icmp eq i8 %409, 0
  br i1 %410, label %411, label %389

411:                                              ; preds = %405, %363
  call void @_ZNSt6thread4joinEv(ptr noundef nonnull align 8 dereferenceable(8) %16) #20
  br label %412

412:                                              ; preds = %393, %411
  %413 = phi i32 [ 0, %411 ], [ 1, %393 ]
  call void @llvm.lifetime.end.p0(i64 1, ptr nonnull %20) #20
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %19) #20
  call void @llvm.lifetime.end.p0(i64 128, ptr nonnull %18) #20
  %414 = load i64, ptr %16, align 8, !tbaa.struct !49
  %415 = icmp eq i64 %414, 0
  br i1 %415, label %417, label %416

416:                                              ; preds = %412
  call void @_ZSt9terminatev() #24
  unreachable

417:                                              ; preds = %412
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %16) #20
  br label %418

418:                                              ; preds = %417, %356
  %419 = phi i32 [ 1, %356 ], [ %413, %417 ]
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %15) #20
  call void @llvm.lifetime.end.p0(i64 1, ptr nonnull %14) #20
  br label %420

420:                                              ; preds = %418, %346, %330, %305, %291
  %421 = phi i32 [ 1, %291 ], [ 1, %305 ], [ 1, %330 ], [ 1, %346 ], [ %419, %418 ]
  call void @llvm.lifetime.end.p0(i64 60, ptr nonnull %13) #20
  br label %422

422:                                              ; preds = %420, %269, %247
  %423 = phi i32 [ 1, %247 ], [ 1, %269 ], [ %421, %420 ]
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %12) #20
  br label %424

424:                                              ; preds = %204, %422, %199, %23
  %425 = phi i32 [ 1, %23 ], [ 1, %204 ], [ %423, %422 ], [ %176, %199 ]
  ret i32 %425
}

; Function Attrs: inlinehint mustprogress nounwind sspstrong uwtable
declare noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8), ptr noundef) local_unnamed_addr #6

declare noundef nonnull align 8 dereferenceable(8) ptr @_ZNSolsEi(ptr noundef nonnull align 8 dereferenceable(8), i32 noundef) local_unnamed_addr #7

; Function Attrs: nofree
declare noundef i32 @open(ptr nocapture noundef readonly, i32 noundef, ...) local_unnamed_addr #8

; Function Attrs: nounwind
declare ptr @strerror(i32 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress nofree nosync nounwind willreturn memory(none)
declare ptr @__errno_location() local_unnamed_addr #9

declare i32 @fcntl(i32 noundef, i32 noundef, ...) local_unnamed_addr #7

; Function Attrs: nounwind
declare i32 @tcgetattr(i32 noundef, ptr noundef) local_unnamed_addr #2

; Function Attrs: nounwind
declare i32 @cfsetspeed(ptr noundef, i32 noundef) local_unnamed_addr #2

; Function Attrs: nounwind
declare i32 @tcsetattr(i32 noundef, i32 noundef, ptr noundef) local_unnamed_addr #2

; Function Attrs: nounwind
declare i32 @pipe(ptr noundef) local_unnamed_addr #2

; Function Attrs: mustprogress norecurse nounwind sspstrong uwtable
define internal fastcc void @"_ZNSt6threadC2IZ4mainE3$_0JEvEEOT_DpOT0_"(ptr noundef nonnull align 8 dereferenceable(8) %0, ptr nocapture noundef nonnull readonly align 8 dereferenceable(24) %1) unnamed_addr #5 align 2 {
  %3 = alloca %"class.std::unique_ptr", align 8
  store i64 0, ptr %0, align 8, !tbaa !50
  %4 = tail call noalias noundef nonnull dereferenceable(32) ptr @_Znwm(i64 noundef 32) #22
  store ptr getelementptr inbounds ({ [5 x ptr] }, ptr @"_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEEE", i64 0, inrange i32 0, i64 2), ptr %4, align 8, !tbaa !32
  %5 = getelementptr inbounds %"struct.std::thread::_State_impl", ptr %4, i64 0, i32 1
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(24) %5, ptr noundef nonnull align 8 dereferenceable(24) %1, i64 24, i1 false), !tbaa.struct !52
  store ptr %4, ptr %3, align 8, !tbaa !13
  call void @_ZNSt6thread15_M_start_threadESt10unique_ptrINS_6_StateESt14default_deleteIS1_EEPFvvE(ptr noundef nonnull align 8 dereferenceable(8) %0, ptr noundef nonnull %3, ptr noundef nonnull @_ZNSt6thread24_M_thread_deps_never_runEv) #20
  %6 = load ptr, ptr %3, align 8, !tbaa !13
  %7 = icmp eq ptr %6, null
  br i1 %7, label %12, label %8

8:                                                ; preds = %2
  %9 = load ptr, ptr %6, align 8, !tbaa !32
  %10 = getelementptr inbounds ptr, ptr %9, i64 1
  %11 = load ptr, ptr %10, align 8
  call void %11(ptr noundef nonnull align 8 dereferenceable(8) %6) #20
  br label %12

12:                                               ; preds = %2, %8
  ret void
}

declare i32 @select(i32 noundef, ptr noundef, ptr noundef, ptr noundef, ptr noundef) local_unnamed_addr #7

; Function Attrs: nofree nounwind
declare noundef i32 @fflush(ptr nocapture noundef) local_unnamed_addr #10

; Function Attrs: nofree
declare noundef i64 @read(i32 noundef, ptr nocapture noundef, i64 noundef) local_unnamed_addr #8

; Function Attrs: inlinehint mustprogress nounwind sspstrong uwtable
declare noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c(ptr noundef nonnull align 8 dereferenceable(8), i8 noundef signext) local_unnamed_addr #6

declare void @_ZNSt6thread4joinEv(ptr noundef nonnull align 8 dereferenceable(8)) local_unnamed_addr #7

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: readwrite)
declare void @llvm.memcpy.p0.p0.i64(ptr noalias nocapture writeonly, ptr noalias nocapture readonly, i64, i1 immarg) #11

; Function Attrs: cold noreturn nounwind
declare void @_ZSt9terminatev() local_unnamed_addr #12

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(ptr noundef) local_unnamed_addr #13

; Function Attrs: nounwind
declare noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEPKcmm(ptr noundef nonnull align 8 dereferenceable(32), ptr noundef, i64 noundef, i64 noundef) local_unnamed_addr #2

declare noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32), ptr noundef nonnull align 8 dereferenceable(8), i64 noundef) local_unnamed_addr #7

; Function Attrs: nobuiltin allocsize(0)
declare noundef nonnull ptr @_Znwm(i64 noundef) local_unnamed_addr #14

; Function Attrs: cold noreturn
declare void @_ZSt20__throw_length_errorPKc(ptr noundef) local_unnamed_addr #15

; Function Attrs: cold noreturn
declare void @_ZSt24__throw_out_of_range_fmtPKcz(ptr noundef, ...) local_unnamed_addr #15

; Function Attrs: mustprogress nounwind sspstrong uwtable
define linkonce_odr dso_local void @_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_appendIJS5_EEEvDpOT_(ptr noundef nonnull align 8 dereferenceable(24) %0, ptr noundef nonnull align 8 dereferenceable(32) %1) local_unnamed_addr #0 comdat align 2 {
  %3 = getelementptr inbounds %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data", ptr %0, i64 0, i32 1
  %4 = load ptr, ptr %3, align 8, !tbaa !13
  %5 = load ptr, ptr %0, align 8, !tbaa !13
  %6 = ptrtoint ptr %4 to i64
  %7 = ptrtoint ptr %5 to i64
  %8 = sub i64 %6, %7
  %9 = icmp eq i64 %8, 9223372036854775776
  br i1 %9, label %10, label %11

10:                                               ; preds = %2
  tail call void @_ZSt20__throw_length_errorPKc(ptr noundef nonnull @.str.24) #24
  unreachable

11:                                               ; preds = %2
  %12 = ashr exact i64 %8, 5
  %13 = tail call i64 @llvm.umax.i64(i64 %12, i64 1)
  %14 = add nsw i64 %13, %12
  %15 = icmp ult i64 %14, %12
  %16 = tail call i64 @llvm.umin.i64(i64 %14, i64 288230376151711743)
  %17 = select i1 %15, i64 288230376151711743, i64 %16
  %18 = icmp ne i64 %17, 0
  tail call void @llvm.assume(i1 %18)
  %19 = shl nuw nsw i64 %17, 5
  %20 = tail call noalias noundef nonnull ptr @_Znwm(i64 noundef %19) #22
  %21 = getelementptr inbounds i8, ptr %20, i64 %8
  %22 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %21, i64 0, i32 2
  store ptr %22, ptr %21, align 8, !tbaa !15
  %23 = load ptr, ptr %1, align 8, !tbaa !5
  %24 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %1, i64 0, i32 2
  %25 = icmp eq ptr %23, %24
  br i1 %25, label %26, label %31

26:                                               ; preds = %11
  %27 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %1, i64 0, i32 1
  %28 = load i64, ptr %27, align 8, !tbaa !14
  %29 = icmp ult i64 %28, 16
  tail call void @llvm.assume(i1 %29)
  %30 = add nuw nsw i64 %28, 1
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(1) %22, ptr noundef nonnull align 8 dereferenceable(1) %23, i64 %30, i1 false)
  br label %35

31:                                               ; preds = %11
  store ptr %23, ptr %21, align 8, !tbaa !5
  %32 = load i64, ptr %24, align 8, !tbaa !16
  store i64 %32, ptr %22, align 8, !tbaa !16
  %33 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %1, i64 0, i32 1
  %34 = load i64, ptr %33, align 8, !tbaa !14
  br label %35

35:                                               ; preds = %26, %31
  %36 = phi i64 [ %28, %26 ], [ %34, %31 ]
  %37 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %1, i64 0, i32 1
  %38 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %21, i64 0, i32 1
  store i64 %36, ptr %38, align 8, !tbaa !14
  store ptr %24, ptr %1, align 8, !tbaa !5
  store i64 0, ptr %37, align 8, !tbaa !14
  store i8 0, ptr %24, align 8, !tbaa !16
  %39 = icmp eq ptr %5, %4
  br i1 %39, label %63, label %40

40:                                               ; preds = %35, %56
  %41 = phi ptr [ %61, %56 ], [ %20, %35 ]
  %42 = phi ptr [ %60, %56 ], [ %5, %35 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !53)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !56)
  %43 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %41, i64 0, i32 2
  store ptr %43, ptr %41, align 8, !tbaa !15, !alias.scope !53, !noalias !56
  %44 = load ptr, ptr %42, align 8, !tbaa !5, !alias.scope !56, !noalias !53
  %45 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %42, i64 0, i32 2
  %46 = icmp eq ptr %44, %45
  br i1 %46, label %47, label %52

47:                                               ; preds = %40
  %48 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %42, i64 0, i32 1
  %49 = load i64, ptr %48, align 8, !tbaa !14, !alias.scope !56, !noalias !53
  %50 = icmp ult i64 %49, 16
  tail call void @llvm.assume(i1 %50)
  %51 = add nuw nsw i64 %49, 1
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(1) %43, ptr noundef nonnull align 8 dereferenceable(1) %44, i64 %51, i1 false)
  br label %56

52:                                               ; preds = %40
  store ptr %44, ptr %41, align 8, !tbaa !5, !alias.scope !53, !noalias !56
  %53 = load i64, ptr %45, align 8, !tbaa !16, !alias.scope !56, !noalias !53
  store i64 %53, ptr %43, align 8, !tbaa !16, !alias.scope !53, !noalias !56
  %54 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %42, i64 0, i32 1
  %55 = load i64, ptr %54, align 8, !tbaa !14, !alias.scope !56, !noalias !53
  br label %56

56:                                               ; preds = %52, %47
  %57 = phi i64 [ %49, %47 ], [ %55, %52 ]
  %58 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %42, i64 0, i32 1
  %59 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %41, i64 0, i32 1
  store i64 %57, ptr %59, align 8, !tbaa !14, !alias.scope !53, !noalias !56
  store ptr %45, ptr %42, align 8, !tbaa !5, !alias.scope !56, !noalias !53
  store i64 0, ptr %58, align 8, !tbaa !14, !alias.scope !56, !noalias !53
  store i8 0, ptr %45, align 1, !tbaa !16, !alias.scope !56, !noalias !53
  %60 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %42, i64 1
  %61 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %41, i64 1
  %62 = icmp eq ptr %60, %4
  br i1 %62, label %63, label %40, !llvm.loop !58

63:                                               ; preds = %56, %35
  %64 = phi ptr [ %20, %35 ], [ %61, %56 ]
  %65 = icmp eq ptr %5, null
  br i1 %65, label %67, label %66

66:                                               ; preds = %63
  tail call void @_ZdlPv(ptr noundef nonnull %5) #23
  br label %67

67:                                               ; preds = %63, %66
  %68 = getelementptr inbounds %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data", ptr %0, i64 0, i32 2
  %69 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %64, i64 1
  store ptr %20, ptr %0, align 8, !tbaa !17
  store ptr %69, ptr %3, align 8, !tbaa !20
  %70 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %20, i64 %17
  store ptr %70, ptr %68, align 8, !tbaa !19
  ret void
}

; Function Attrs: cold noreturn
declare void @_ZSt19__throw_logic_errorPKc(ptr noundef) local_unnamed_addr #15

declare noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8), ptr noundef, i64 noundef) local_unnamed_addr #7

declare void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264), i32 noundef) local_unnamed_addr #7

declare void @_ZNSt6thread15_M_start_threadESt10unique_ptrINS_6_StateESt14default_deleteIS1_EEPFvvE(ptr noundef nonnull align 8 dereferenceable(8), ptr noundef, ptr noundef) local_unnamed_addr #7

; Function Attrs: mustprogress nounwind sspstrong uwtable
define linkonce_odr dso_local void @_ZNSt6thread24_M_thread_deps_never_runEv() #0 comdat align 2 {
  ret void
}

; Function Attrs: nounwind
declare void @_ZNSt6thread6_StateD2Ev(ptr noundef nonnull align 8 dereferenceable(8)) unnamed_addr #2

; Function Attrs: inlinehint mustprogress nounwind sspstrong uwtable
define internal void @"_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEED0Ev"(ptr noundef nonnull align 8 dereferenceable(32) %0) unnamed_addr #6 align 2 {
  tail call void @_ZNSt6thread6_StateD2Ev(ptr noundef nonnull align 8 dereferenceable(32) %0) #20
  tail call void @_ZdlPv(ptr noundef nonnull %0) #23
  ret void
}

; Function Attrs: mustprogress nounwind sspstrong uwtable
define internal void @"_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEE6_M_runEv"(ptr nocapture noundef nonnull readonly align 8 dereferenceable(32) %0) unnamed_addr #0 align 2 {
  %2 = alloca %struct.termios, align 4
  %3 = alloca i8, align 1
  %4 = getelementptr inbounds %"struct.std::thread::_State_impl", ptr %0, i64 0, i32 1
  call void @llvm.lifetime.start.p0(i64 60, ptr nonnull %2) #20
  %5 = call i32 @tcgetattr(i32 noundef 0, ptr noundef nonnull %2) #20
  %6 = icmp slt i32 %5, 0
  br i1 %6, label %7, label %26

7:                                                ; preds = %1
  %8 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.26, i64 noundef 29) #20
  %9 = tail call ptr @__errno_location() #25
  %10 = load i32, ptr %9, align 4, !tbaa !30
  %11 = call ptr @strerror(i32 noundef %10) #20
  %12 = icmp eq ptr %11, null
  br i1 %12, label %13, label %21

13:                                               ; preds = %7
  %14 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %15 = getelementptr i8, ptr %14, i64 -24
  %16 = load i64, ptr %15, align 8
  %17 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %16
  %18 = getelementptr inbounds %"class.std::ios_base", ptr %17, i64 0, i32 5
  %19 = load i32, ptr %18, align 8, !tbaa !34
  %20 = or i32 %19, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %17, i32 noundef %20) #20
  br label %24

21:                                               ; preds = %7
  %22 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %11) #20
  %23 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %11, i64 noundef %22) #20
  br label %24

24:                                               ; preds = %21, %13
  %25 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %141

26:                                               ; preds = %1
  %27 = getelementptr inbounds %struct.termios, ptr %2, i64 0, i32 3
  %28 = load i32, ptr %27, align 4, !tbaa !43
  %29 = and i32 %28, -32844
  store i32 %29, ptr %27, align 4, !tbaa !43
  %30 = load i32, ptr %2, align 4, !tbaa !42
  %31 = and i32 %30, -1025
  store i32 %31, ptr %2, align 4, !tbaa !42
  %32 = call i32 @tcsetattr(i32 noundef 0, i32 noundef 2, ptr noundef nonnull %2) #20
  %33 = icmp slt i32 %32, 0
  br i1 %33, label %34, label %53

34:                                               ; preds = %26
  %35 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.27, i64 noundef 29) #20
  %36 = tail call ptr @__errno_location() #25
  %37 = load i32, ptr %36, align 4, !tbaa !30
  %38 = call ptr @strerror(i32 noundef %37) #20
  %39 = icmp eq ptr %38, null
  br i1 %39, label %40, label %48

40:                                               ; preds = %34
  %41 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %42 = getelementptr i8, ptr %41, i64 -24
  %43 = load i64, ptr %42, align 8
  %44 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %43
  %45 = getelementptr inbounds %"class.std::ios_base", ptr %44, i64 0, i32 5
  %46 = load i32, ptr %45, align 8, !tbaa !34
  %47 = or i32 %46, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %44, i32 noundef %47) #20
  br label %51

48:                                               ; preds = %34
  %49 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %38) #20
  %50 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %38, i64 noundef %49) #20
  br label %51

51:                                               ; preds = %48, %40
  %52 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %141

53:                                               ; preds = %26
  call void @llvm.lifetime.start.p0(i64 1, ptr nonnull %3) #20
  %54 = call i64 @read(i32 noundef 0, ptr noundef nonnull %3, i64 noundef 1) #20
  %55 = icmp eq i64 %54, 0
  br i1 %55, label %140, label %56

56:                                               ; preds = %53
  %57 = getelementptr inbounds %"struct.std::thread::_State_impl", ptr %0, i64 0, i32 1, i32 0, i32 0, i32 0, i32 0, i32 2
  %58 = getelementptr inbounds %"struct.std::thread::_State_impl", ptr %0, i64 0, i32 1, i32 0, i32 0, i32 0, i32 0, i32 1
  br label %59

59:                                               ; preds = %137, %56
  %60 = load i8, ptr %3, align 1, !tbaa !16
  %61 = icmp eq i8 %60, 3
  br i1 %61, label %62, label %88

62:                                               ; preds = %59
  %63 = load ptr, ptr %4, align 8, !tbaa !59
  store i8 0, ptr %63, align 1, !tbaa !45
  %64 = load ptr, ptr %58, align 8, !tbaa !61
  %65 = getelementptr inbounds [2 x i32], ptr %64, i64 0, i64 1
  %66 = load i32, ptr %65, align 4, !tbaa !30
  %67 = call i64 @write(i32 noundef %66, ptr noundef nonnull %3, i64 noundef 1) #20
  %68 = icmp slt i64 %67, 0
  br i1 %68, label %69, label %140

69:                                               ; preds = %62
  %70 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.28, i64 noundef 24) #20
  %71 = tail call ptr @__errno_location() #25
  %72 = load i32, ptr %71, align 4, !tbaa !30
  %73 = call ptr @strerror(i32 noundef %72) #20
  %74 = icmp eq ptr %73, null
  br i1 %74, label %75, label %83

75:                                               ; preds = %69
  %76 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %77 = getelementptr i8, ptr %76, i64 -24
  %78 = load i64, ptr %77, align 8
  %79 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %78
  %80 = getelementptr inbounds %"class.std::ios_base", ptr %79, i64 0, i32 5
  %81 = load i32, ptr %80, align 8, !tbaa !34
  %82 = or i32 %81, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %79, i32 noundef %82) #20
  br label %86

83:                                               ; preds = %69
  %84 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %73) #20
  %85 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %73, i64 noundef %84) #20
  br label %86

86:                                               ; preds = %83, %75
  %87 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %140

88:                                               ; preds = %59
  %89 = load ptr, ptr %57, align 8, !tbaa !62
  %90 = load i32, ptr %89, align 4, !tbaa !30
  %91 = call i64 @write(i32 noundef %90, ptr noundef nonnull %3, i64 noundef 1) #20
  %92 = icmp slt i64 %91, 0
  br i1 %92, label %93, label %112

93:                                               ; preds = %88
  %94 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.29, i64 noundef 22) #20
  %95 = tail call ptr @__errno_location() #25
  %96 = load i32, ptr %95, align 4, !tbaa !30
  %97 = call ptr @strerror(i32 noundef %96) #20
  %98 = icmp eq ptr %97, null
  br i1 %98, label %99, label %107

99:                                               ; preds = %93
  %100 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %101 = getelementptr i8, ptr %100, i64 -24
  %102 = load i64, ptr %101, align 8
  %103 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %102
  %104 = getelementptr inbounds %"class.std::ios_base", ptr %103, i64 0, i32 5
  %105 = load i32, ptr %104, align 8, !tbaa !34
  %106 = or i32 %105, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %103, i32 noundef %106) #20
  br label %110

107:                                              ; preds = %93
  %108 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %97) #20
  %109 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %97, i64 noundef %108) #20
  br label %110

110:                                              ; preds = %107, %99
  %111 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %112

112:                                              ; preds = %110, %88
  %113 = load ptr, ptr %58, align 8, !tbaa !61
  %114 = getelementptr inbounds [2 x i32], ptr %113, i64 0, i64 1
  %115 = load i32, ptr %114, align 4, !tbaa !30
  %116 = call i64 @write(i32 noundef %115, ptr noundef nonnull %3, i64 noundef 1) #20
  %117 = icmp slt i64 %116, 0
  br i1 %117, label %118, label %137

118:                                              ; preds = %112
  %119 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.28, i64 noundef 24) #20
  %120 = tail call ptr @__errno_location() #25
  %121 = load i32, ptr %120, align 4, !tbaa !30
  %122 = call ptr @strerror(i32 noundef %121) #20
  %123 = icmp eq ptr %122, null
  br i1 %123, label %124, label %132

124:                                              ; preds = %118
  %125 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %126 = getelementptr i8, ptr %125, i64 -24
  %127 = load i64, ptr %126, align 8
  %128 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %127
  %129 = getelementptr inbounds %"class.std::ios_base", ptr %128, i64 0, i32 5
  %130 = load i32, ptr %129, align 8, !tbaa !34
  %131 = or i32 %130, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %128, i32 noundef %131) #20
  br label %135

132:                                              ; preds = %118
  %133 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %122) #20
  %134 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %122, i64 noundef %133) #20
  br label %135

135:                                              ; preds = %132, %124
  %136 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %137

137:                                              ; preds = %135, %112
  %138 = call i64 @read(i32 noundef 0, ptr noundef nonnull %3, i64 noundef 1) #20
  %139 = icmp eq i64 %138, 0
  br i1 %139, label %140, label %59, !llvm.loop !63

140:                                              ; preds = %137, %86, %62, %53
  call void @llvm.lifetime.end.p0(i64 1, ptr nonnull %3) #20
  br label %141

141:                                              ; preds = %24, %51, %140
  call void @llvm.lifetime.end.p0(i64 60, ptr nonnull %2) #20
  ret void
}

; Function Attrs: nofree
declare noundef i64 @write(i32 noundef, ptr nocapture noundef readonly, i64 noundef) local_unnamed_addr #8

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(inaccessiblemem: write)
declare void @llvm.assume(i1 noundef) #16

; Function Attrs: nocallback nofree nosync nounwind willreturn memory(inaccessiblemem: readwrite)
declare void @llvm.experimental.noalias.scope.decl(metadata) #17

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i64 @llvm.umin.i64(i64, i64) #18

; Function Attrs: nocallback nofree nosync nounwind speculatable willreturn memory(none)
declare i64 @llvm.umax.i64(i64, i64) #18

; Function Attrs: nofree nounwind willreturn memory(argmem: read)
declare i32 @bcmp(ptr nocapture, ptr nocapture, i64) local_unnamed_addr #19

attributes #0 = { mustprogress nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { mustprogress nocallback nofree nosync nounwind willreturn memory(argmem: readwrite) }
attributes #2 = { nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { mustprogress nofree nounwind willreturn memory(argmem: read) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #4 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: write) }
attributes #5 = { mustprogress norecurse nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #6 = { inlinehint mustprogress nounwind sspstrong uwtable "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #7 = { "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #8 = { nofree "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #9 = { mustprogress nofree nosync nounwind willreturn memory(none) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #10 = { nofree nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #11 = { mustprogress nocallback nofree nounwind willreturn memory(argmem: readwrite) }
attributes #12 = { cold noreturn nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #13 = { nobuiltin nounwind "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #14 = { nobuiltin allocsize(0) "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #15 = { cold noreturn "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cmov,+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #16 = { nocallback nofree nosync nounwind willreturn memory(inaccessiblemem: write) }
attributes #17 = { nocallback nofree nosync nounwind willreturn memory(inaccessiblemem: readwrite) }
attributes #18 = { nocallback nofree nosync nounwind speculatable willreturn memory(none) }
attributes #19 = { nofree nounwind willreturn memory(argmem: read) }
attributes #20 = { nounwind }
attributes #21 = { nounwind willreturn memory(read) }
attributes #22 = { builtin nounwind allocsize(0) }
attributes #23 = { builtin nounwind }
attributes #24 = { cold noreturn nounwind }
attributes #25 = { nounwind willreturn memory(none) }

!llvm.module.flags = !{!0, !1, !2, !3}
!llvm.ident = !{!4}

!0 = !{i32 1, !"wchar_size", i32 4}
!1 = !{i32 8, !"PIC Level", i32 2}
!2 = !{i32 7, !"PIE Level", i32 2}
!3 = !{i32 7, !"uwtable", i32 2}
!4 = !{!"clang version 18.1.8"}
!5 = !{!6, !8, i64 0}
!6 = !{!"_ZTSNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEE", !7, i64 0, !11, i64 8, !9, i64 16}
!7 = !{!"_ZTSNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE12_Alloc_hiderE", !8, i64 0}
!8 = !{!"any pointer", !9, i64 0}
!9 = !{!"omnipotent char", !10, i64 0}
!10 = !{!"Simple C++ TBAA"}
!11 = !{!"long", !9, i64 0}
!12 = !{!11, !11, i64 0}
!13 = !{!8, !8, i64 0}
!14 = !{!6, !11, i64 8}
!15 = !{!7, !8, i64 0}
!16 = !{!9, !9, i64 0}
!17 = !{!18, !8, i64 0}
!18 = !{!"_ZTSNSt12_Vector_baseINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_Vector_impl_dataE", !8, i64 0, !8, i64 8, !8, i64 16}
!19 = !{!18, !8, i64 16}
!20 = !{!18, !8, i64 8}
!21 = !{!22}
!22 = distinct !{!22, !23, !"_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6substrEmm: argument 0"}
!23 = distinct !{!23, !"_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6substrEmm"}
!24 = !{!25}
!25 = distinct !{!25, !26, !"_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6substrEmm: argument 0"}
!26 = distinct !{!26, !"_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE6substrEmm"}
!27 = distinct !{!27, !28}
!28 = !{!"llvm.loop.mustprogress"}
!29 = distinct !{!29, !28}
!30 = !{!31, !31, i64 0}
!31 = !{!"int", !9, i64 0}
!32 = !{!33, !33, i64 0}
!33 = !{!"vtable pointer", !10, i64 0}
!34 = !{!35, !37, i64 32}
!35 = !{!"_ZTSSt8ios_base", !11, i64 8, !11, i64 16, !36, i64 24, !37, i64 28, !37, i64 32, !8, i64 40, !38, i64 48, !9, i64 64, !31, i64 192, !8, i64 200, !39, i64 208}
!36 = !{!"_ZTSSt13_Ios_Fmtflags", !9, i64 0}
!37 = !{!"_ZTSSt12_Ios_Iostate", !9, i64 0}
!38 = !{!"_ZTSNSt8ios_base6_WordsE", !8, i64 0, !11, i64 8}
!39 = !{!"_ZTSSt6locale", !8, i64 0}
!40 = !{!41, !31, i64 8}
!41 = !{!"_ZTS7termios", !31, i64 0, !31, i64 4, !31, i64 8, !31, i64 12, !9, i64 16, !9, i64 17, !31, i64 52, !31, i64 56}
!42 = !{!41, !31, i64 0}
!43 = !{!41, !31, i64 12}
!44 = !{!41, !31, i64 4}
!45 = !{!46, !46, i64 0}
!46 = !{!"bool", !9, i64 0}
!47 = !{i8 0, i8 2}
!48 = !{}
!49 = !{i64 0, i64 8, !12}
!50 = !{!51, !11, i64 0}
!51 = !{!"_ZTSNSt6thread2idE", !11, i64 0}
!52 = !{i64 0, i64 8, !13, i64 8, i64 8, !13, i64 16, i64 8, !13}
!53 = !{!54}
!54 = distinct !{!54, !55, !"_ZSt19__relocate_object_aINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_SaIS5_EEvPT_PT0_RT1_: argument 0"}
!55 = distinct !{!55, !"_ZSt19__relocate_object_aINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_SaIS5_EEvPT_PT0_RT1_"}
!56 = !{!57}
!57 = distinct !{!57, !55, !"_ZSt19__relocate_object_aINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_SaIS5_EEvPT_PT0_RT1_: argument 1"}
!58 = distinct !{!58, !28}
!59 = !{!60, !8, i64 0}
!60 = !{!"_ZTSZ4mainE3$_0", !8, i64 0, !8, i64 8, !8, i64 16}
!61 = !{!60, !8, i64 8}
!62 = !{!60, !8, i64 16}
!63 = distinct !{!63, !28}
