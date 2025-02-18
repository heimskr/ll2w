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
%"class.std::vector" = type { %"struct.std::_Vector_base" }
%"struct.std::_Vector_base" = type { %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl" }
%"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl" = type { %"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data" }
%"struct.std::_Vector_base<std::__cxx11::basic_string<char>, std::allocator<std::__cxx11::basic_string<char>>>::_Vector_impl_data" = type { ptr, ptr, ptr }
%"class.std::__cxx11::basic_string" = type { %"struct.std::__cxx11::basic_string<char>::_Alloc_hider", i64, %union.anon }
%"struct.std::__cxx11::basic_string<char>::_Alloc_hider" = type { ptr }
%union.anon = type { i64, [8 x i8] }
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

$_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_appendIJS5_EEEvDpOT_ = comdat any

$_ZNSt6thread24_M_thread_deps_never_runEv = comdat any

@_ZSt4cerr = external global %"class.std::basic_ostream", align 8
@.str = private unnamed_addr constant [47 x i8] c"Usage: serial <device> [serial configuration]\0A\00", align 1
@.str.2 = private unnamed_addr constant [6 x i8] c"noems\00", align 1
@.str.3 = private unnamed_addr constant [4 x i8] c"NXR\00", align 1
@.str.4 = private unnamed_addr constant [5 x i8] c"5678\00", align 1
@.str.5 = private unnamed_addr constant [3 x i8] c"12\00", align 1
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
  %12 = getelementptr inbounds i8, ptr %0, i64 8
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
  %12 = getelementptr inbounds i8, ptr %1, i64 8
  %13 = load i64, ptr %12, align 8, !tbaa !14
  %14 = icmp eq i64 %13, 0
  br i1 %14, label %15, label %16

15:                                               ; preds = %4
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 8 dereferenceable(24) %0, i8 0, i64 24, i1 false)
  br label %165

16:                                               ; preds = %4
  %17 = load ptr, ptr %2, align 8, !tbaa !5
  %18 = getelementptr inbounds i8, ptr %2, i64 8
  %19 = load i64, ptr %18, align 8, !tbaa !14
  %20 = tail call noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEPKcmm(ptr noundef nonnull align 8 dereferenceable(32) %1, ptr noundef %17, i64 noundef 0, i64 noundef %19) #20
  %21 = icmp eq i64 %20, -1
  br i1 %21, label %22, label %72

22:                                               ; preds = %16
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %9) #20
  %23 = getelementptr inbounds i8, ptr %9, i64 16
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
  %37 = getelementptr inbounds i8, ptr %9, i64 8
  store i64 %36, ptr %37, align 8, !tbaa !14
  %38 = load ptr, ptr %9, align 8, !tbaa !5
  %39 = getelementptr inbounds i8, ptr %38, i64 %36
  store i8 0, ptr %39, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %8) #20
  %40 = call noalias noundef nonnull dereferenceable(32) ptr @_Znwm(i64 noundef 32) #22
  store ptr %40, ptr %0, align 8, !tbaa !17
  %41 = getelementptr inbounds i8, ptr %40, i64 32
  %42 = getelementptr inbounds i8, ptr %0, i64 16
  store ptr %41, ptr %42, align 8, !tbaa !19
  %43 = getelementptr inbounds i8, ptr %40, i64 16
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
  %57 = getelementptr inbounds i8, ptr %40, i64 8
  store i64 %56, ptr %57, align 8, !tbaa !14
  %58 = load ptr, ptr %40, align 8, !tbaa !5
  %59 = getelementptr inbounds i8, ptr %58, i64 %56
  store i8 0, ptr %59, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %7) #20
  %60 = getelementptr inbounds i8, ptr %0, i64 8
  store ptr %41, ptr %60, align 8, !tbaa !20
  %61 = load ptr, ptr %9, align 8, !tbaa !5
  %62 = getelementptr inbounds i8, ptr %9, i64 16
  %63 = icmp eq ptr %61, %62
  br i1 %63, label %64, label %68

64:                                               ; preds = %55
  %65 = getelementptr inbounds i8, ptr %9, i64 8
  %66 = load i64, ptr %65, align 8, !tbaa !14
  %67 = icmp ult i64 %66, 16
  call void @llvm.assume(i1 %67)
  br label %71

68:                                               ; preds = %55
  %69 = load i64, ptr %62, align 8, !tbaa !16
  %70 = add i64 %69, 1
  call void @_ZdlPvm(ptr noundef %61, i64 noundef %70) #23
  br label %71

71:                                               ; preds = %64, %68
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %9) #20
  br label %165

72:                                               ; preds = %16
  tail call void @llvm.memset.p0.i64(ptr noundef nonnull align 8 dereferenceable(24) %0, i8 0, i64 24, i1 false)
  %73 = load i64, ptr %18, align 8, !tbaa !14
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %10) #20
  tail call void @llvm.experimental.noalias.scope.decl(metadata !21)
  %74 = load i64, ptr %12, align 8, !tbaa !14, !noalias !21
  %75 = getelementptr inbounds i8, ptr %10, i64 16
  store ptr %75, ptr %10, align 8, !tbaa !15, !alias.scope !21
  %76 = load ptr, ptr %1, align 8, !tbaa !5, !noalias !21
  %77 = call noundef i64 @llvm.umin.i64(i64 %74, i64 %20)
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %6) #20, !noalias !21
  store i64 %77, ptr %6, align 8, !tbaa !12, !noalias !21
  %78 = icmp ugt i64 %77, 15
  br i1 %78, label %79, label %82

79:                                               ; preds = %72
  %80 = call noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32) %10, ptr noundef nonnull align 8 dereferenceable(8) %6, i64 noundef 0) #20
  store ptr %80, ptr %10, align 8, !tbaa !5, !alias.scope !21
  %81 = load i64, ptr %6, align 8, !tbaa !12, !noalias !21
  store i64 %81, ptr %75, align 8, !tbaa !16, !alias.scope !21
  br label %82

82:                                               ; preds = %79, %72
  %83 = phi ptr [ %80, %79 ], [ %75, %72 ]
  switch i64 %77, label %86 [
    i64 1, label %84
    i64 0, label %87
  ]

84:                                               ; preds = %82
  %85 = load i8, ptr %76, align 1, !tbaa !16
  store i8 %85, ptr %83, align 1, !tbaa !16
  br label %87

86:                                               ; preds = %82
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %83, ptr align 1 %76, i64 %77, i1 false)
  br label %87

87:                                               ; preds = %82, %84, %86
  %88 = load i64, ptr %6, align 8, !tbaa !12, !noalias !21
  %89 = getelementptr inbounds i8, ptr %10, i64 8
  store i64 %88, ptr %89, align 8, !tbaa !14, !alias.scope !21
  %90 = load ptr, ptr %10, align 8, !tbaa !5, !alias.scope !21
  %91 = getelementptr inbounds i8, ptr %90, i64 %88
  store i8 0, ptr %91, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %6) #20, !noalias !21
  %92 = getelementptr inbounds i8, ptr %0, i64 8
  %93 = getelementptr inbounds i8, ptr %0, i64 16
  call void @_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_appendIJS5_EEEvDpOT_(ptr noundef nonnull align 8 dereferenceable(24) %0, ptr noundef nonnull align 8 dereferenceable(32) %10)
  %94 = load ptr, ptr %10, align 8, !tbaa !5
  %95 = icmp eq ptr %94, %75
  br i1 %95, label %96, label %99

96:                                               ; preds = %87
  %97 = load i64, ptr %89, align 8, !tbaa !14
  %98 = icmp ult i64 %97, 16
  call void @llvm.assume(i1 %98)
  br label %102

99:                                               ; preds = %87
  %100 = load i64, ptr %75, align 8, !tbaa !16
  %101 = add i64 %100, 1
  call void @_ZdlPvm(ptr noundef %94, i64 noundef %101) #23
  br label %102

102:                                              ; preds = %99, %96
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %10) #20
  %103 = getelementptr inbounds i8, ptr %11, i64 16
  %104 = getelementptr inbounds i8, ptr %11, i64 8
  br label %105

105:                                              ; preds = %102, %163
  %106 = phi i64 [ %20, %102 ], [ %110, %163 ]
  %107 = add i64 %106, %73
  %108 = load ptr, ptr %2, align 8, !tbaa !5
  %109 = load i64, ptr %18, align 8, !tbaa !14
  %110 = call noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEPKcmm(ptr noundef nonnull align 8 dereferenceable(32) %1, ptr noundef %108, i64 noundef %107, i64 noundef %109) #20
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %11) #20
  call void @llvm.experimental.noalias.scope.decl(metadata !24)
  %111 = load i64, ptr %12, align 8, !tbaa !14, !noalias !24
  %112 = icmp ult i64 %111, %107
  br i1 %112, label %113, label %114

113:                                              ; preds = %105
  call void (ptr, ...) @_ZSt24__throw_out_of_range_fmtPKcz(ptr noundef nonnull @.str.22, ptr noundef nonnull @.str.21, i64 noundef %107, i64 noundef %111) #24, !noalias !24
  unreachable

114:                                              ; preds = %105
  %115 = sub i64 %110, %107
  store ptr %103, ptr %11, align 8, !tbaa !15, !alias.scope !24
  %116 = load ptr, ptr %1, align 8, !tbaa !5, !noalias !24
  %117 = getelementptr inbounds i8, ptr %116, i64 %107
  %118 = sub i64 %111, %107
  %119 = call noundef i64 @llvm.umin.i64(i64 %118, i64 %115)
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %5) #20, !noalias !24
  store i64 %119, ptr %5, align 8, !tbaa !12, !noalias !24
  %120 = icmp ugt i64 %119, 15
  br i1 %120, label %121, label %124

121:                                              ; preds = %114
  %122 = call noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32) %11, ptr noundef nonnull align 8 dereferenceable(8) %5, i64 noundef 0) #20
  store ptr %122, ptr %11, align 8, !tbaa !5, !alias.scope !24
  %123 = load i64, ptr %5, align 8, !tbaa !12, !noalias !24
  store i64 %123, ptr %103, align 8, !tbaa !16, !alias.scope !24
  br label %124

124:                                              ; preds = %121, %114
  %125 = phi ptr [ %122, %121 ], [ %103, %114 ]
  switch i64 %119, label %128 [
    i64 1, label %126
    i64 0, label %129
  ]

126:                                              ; preds = %124
  %127 = load i8, ptr %117, align 1, !tbaa !16
  store i8 %127, ptr %125, align 1, !tbaa !16
  br label %129

128:                                              ; preds = %124
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %125, ptr align 1 %117, i64 %119, i1 false)
  br label %129

129:                                              ; preds = %124, %126, %128
  %130 = load i64, ptr %5, align 8, !tbaa !12, !noalias !24
  store i64 %130, ptr %104, align 8, !tbaa !14, !alias.scope !24
  %131 = load ptr, ptr %11, align 8, !tbaa !5, !alias.scope !24
  %132 = getelementptr inbounds i8, ptr %131, i64 %130
  store i8 0, ptr %132, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %5) #20, !noalias !24
  %133 = load i64, ptr %104, align 8, !tbaa !14
  %134 = icmp eq i64 %133, 0
  %135 = and i1 %134, %3
  br i1 %135, label %154, label %136

136:                                              ; preds = %129
  %137 = load ptr, ptr %92, align 8, !tbaa !20
  %138 = load ptr, ptr %93, align 8, !tbaa !19
  %139 = icmp eq ptr %137, %138
  br i1 %139, label %153, label %140

140:                                              ; preds = %136
  %141 = getelementptr inbounds i8, ptr %137, i64 16
  store ptr %141, ptr %137, align 8, !tbaa !15
  %142 = load ptr, ptr %11, align 8, !tbaa !5
  %143 = icmp eq ptr %142, %103
  br i1 %143, label %144, label %147

144:                                              ; preds = %140
  %145 = icmp ult i64 %133, 16
  call void @llvm.assume(i1 %145)
  %146 = add nuw nsw i64 %133, 1
  call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(1) %141, ptr noundef nonnull align 8 dereferenceable(1) %103, i64 %146, i1 false)
  br label %149

147:                                              ; preds = %140
  store ptr %142, ptr %137, align 8, !tbaa !5
  %148 = load i64, ptr %103, align 8, !tbaa !16
  store i64 %148, ptr %141, align 8, !tbaa !16
  br label %149

149:                                              ; preds = %147, %144
  %150 = getelementptr inbounds i8, ptr %137, i64 8
  store i64 %133, ptr %150, align 8, !tbaa !14
  store ptr %103, ptr %11, align 8, !tbaa !5
  store i64 0, ptr %104, align 8, !tbaa !14
  store i8 0, ptr %103, align 8, !tbaa !16
  %151 = load ptr, ptr %92, align 8, !tbaa !20
  %152 = getelementptr inbounds i8, ptr %151, i64 32
  store ptr %152, ptr %92, align 8, !tbaa !20
  br label %154

153:                                              ; preds = %136
  call void @_ZNSt6vectorINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEESaIS5_EE17_M_realloc_appendIJS5_EEEvDpOT_(ptr noundef nonnull align 8 dereferenceable(24) %0, ptr noundef nonnull align 8 dereferenceable(32) %11)
  br label %154

154:                                              ; preds = %153, %149, %129
  %155 = load ptr, ptr %11, align 8, !tbaa !5
  %156 = icmp eq ptr %155, %103
  br i1 %156, label %157, label %160

157:                                              ; preds = %154
  %158 = load i64, ptr %104, align 8, !tbaa !14
  %159 = icmp ult i64 %158, 16
  call void @llvm.assume(i1 %159)
  br label %163

160:                                              ; preds = %154
  %161 = load i64, ptr %103, align 8, !tbaa !16
  %162 = add i64 %161, 1
  call void @_ZdlPvm(ptr noundef %155, i64 noundef %162) #23
  br label %163

163:                                              ; preds = %157, %160
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %11) #20
  %164 = icmp eq i64 %110, -1
  br i1 %164, label %165, label %105, !llvm.loop !27

165:                                              ; preds = %163, %71, %15
  ret void
}

; Function Attrs: mustprogress nocallback nofree nounwind willreturn memory(argmem: write)
declare void @llvm.memset.p0.i64(ptr nocapture writeonly, i8, i64, i1 immarg) #4

; Function Attrs: mustprogress nounwind sspstrong uwtable
define dso_local noundef zeroext i1 @_Z7matchescPKc(i8 noundef signext %0, ptr noundef readonly %1) local_unnamed_addr #0 {
  %3 = alloca i64, align 8
  %4 = alloca %"class.std::__cxx11::basic_string", align 8
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %4) #20
  %5 = getelementptr inbounds i8, ptr %4, i64 16
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
  %21 = getelementptr inbounds i8, ptr %4, i64 8
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
  br label %33

30:                                               ; preds = %19
  %31 = load i64, ptr %5, align 8, !tbaa !16
  %32 = add i64 %31, 1
  call void @_ZdlPvm(ptr noundef %25, i64 noundef %32) #23
  br label %33

33:                                               ; preds = %27, %30
  %34 = icmp ne i64 %24, -1
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %4) #20
  ret i1 %34
}

; Function Attrs: nounwind
declare noundef i64 @_ZNKSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE4findEcm(ptr noundef nonnull align 8 dereferenceable(32), i8 noundef signext, i64 noundef) local_unnamed_addr #2

; Function Attrs: mustprogress norecurse nounwind sspstrong uwtable
define dso_local noundef range(i32 0, 2) i32 @main(i32 noundef %0, ptr nocapture noundef readonly %1) local_unnamed_addr #5 {
  %3 = alloca ptr, align 8
  %4 = alloca i64, align 8
  %5 = alloca %"class.std::vector", align 8
  %6 = alloca %"class.std::__cxx11::basic_string", align 8
  %7 = alloca %"class.std::__cxx11::basic_string", align 8
  %8 = alloca i32, align 4
  %9 = alloca %struct.termios, align 4
  %10 = alloca i8, align 1
  %11 = alloca [2 x i32], align 4
  %12 = alloca %"class.std::thread", align 8
  %13 = alloca %class.anon, align 8
  %14 = alloca %struct.fd_set, align 8
  %15 = alloca %struct.timeval, align 8
  %16 = alloca i8, align 1
  %17 = add i32 %0, -4
  %18 = icmp ult i32 %17, -2
  br i1 %18, label %19, label %21

19:                                               ; preds = %2
  %20 = tail call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str, i64 noundef 46) #20
  br label %386

21:                                               ; preds = %2
  %22 = getelementptr inbounds i8, ptr %1, i64 8
  %23 = load ptr, ptr %22, align 8, !tbaa !13
  %24 = icmp eq i32 %0, 3
  br i1 %24, label %25, label %170

25:                                               ; preds = %21
  call void @llvm.lifetime.start.p0(i64 24, ptr nonnull %5) #20
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %6) #20
  %26 = getelementptr inbounds i8, ptr %1, i64 16
  %27 = load ptr, ptr %26, align 8, !tbaa !13
  %28 = getelementptr inbounds i8, ptr %6, i64 16
  store ptr %28, ptr %6, align 8, !tbaa !15
  %29 = icmp eq ptr %27, null
  br i1 %29, label %30, label %31

30:                                               ; preds = %25
  call void @_ZSt19__throw_logic_errorPKc(ptr noundef nonnull @.str.25) #24
  unreachable

31:                                               ; preds = %25
  %32 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %27) #20
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %4) #20
  store i64 %32, ptr %4, align 8, !tbaa !12
  %33 = icmp ugt i64 %32, 15
  br i1 %33, label %34, label %37

34:                                               ; preds = %31
  %35 = call noundef ptr @_ZNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEE9_M_createERmm(ptr noundef nonnull align 8 dereferenceable(32) %6, ptr noundef nonnull align 8 dereferenceable(8) %4, i64 noundef 0) #20
  store ptr %35, ptr %6, align 8, !tbaa !5
  %36 = load i64, ptr %4, align 8, !tbaa !12
  store i64 %36, ptr %28, align 8, !tbaa !16
  br label %37

37:                                               ; preds = %34, %31
  %38 = phi ptr [ %35, %34 ], [ %28, %31 ]
  switch i64 %32, label %41 [
    i64 1, label %39
    i64 0, label %42
  ]

39:                                               ; preds = %37
  %40 = load i8, ptr %27, align 1, !tbaa !16
  store i8 %40, ptr %38, align 1, !tbaa !16
  br label %42

41:                                               ; preds = %37
  call void @llvm.memcpy.p0.p0.i64(ptr align 1 %38, ptr nonnull align 1 %27, i64 %32, i1 false)
  br label %42

42:                                               ; preds = %37, %39, %41
  %43 = load i64, ptr %4, align 8, !tbaa !12
  %44 = getelementptr inbounds i8, ptr %6, i64 8
  store i64 %43, ptr %44, align 8, !tbaa !14
  %45 = load ptr, ptr %6, align 8, !tbaa !5
  %46 = getelementptr inbounds i8, ptr %45, i64 %43
  store i8 0, ptr %46, align 1, !tbaa !16
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %4) #20
  call void @llvm.lifetime.start.p0(i64 32, ptr nonnull %7) #20
  %47 = getelementptr inbounds i8, ptr %7, i64 16
  store ptr %47, ptr %7, align 8, !tbaa !15
  store i8 44, ptr %47, align 8, !tbaa !16
  %48 = getelementptr inbounds i8, ptr %7, i64 8
  store i64 1, ptr %48, align 8, !tbaa !14
  %49 = getelementptr inbounds i8, ptr %7, i64 17
  store i8 0, ptr %49, align 1, !tbaa !16
  call void @_Z5splitRKNSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES6_b(ptr dead_on_unwind nonnull writable sret(%"class.std::vector") align 8 %5, ptr noundef nonnull align 8 dereferenceable(32) %6, ptr noundef nonnull align 8 dereferenceable(32) %7, i1 noundef zeroext true)
  %50 = load ptr, ptr %7, align 8, !tbaa !5
  %51 = icmp eq ptr %50, %47
  br i1 %51, label %52, label %55

52:                                               ; preds = %42
  %53 = load i64, ptr %48, align 8, !tbaa !14
  %54 = icmp ult i64 %53, 16
  call void @llvm.assume(i1 %54)
  br label %58

55:                                               ; preds = %42
  %56 = load i64, ptr %47, align 8, !tbaa !16
  %57 = add i64 %56, 1
  call void @_ZdlPvm(ptr noundef %50, i64 noundef %57) #23
  br label %58

58:                                               ; preds = %52, %55
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %7) #20
  %59 = load ptr, ptr %6, align 8, !tbaa !5
  %60 = icmp eq ptr %59, %28
  br i1 %60, label %61, label %64

61:                                               ; preds = %58
  %62 = load i64, ptr %44, align 8, !tbaa !14
  %63 = icmp ult i64 %62, 16
  call void @llvm.assume(i1 %63)
  br label %67

64:                                               ; preds = %58
  %65 = load i64, ptr %28, align 8, !tbaa !16
  %66 = add i64 %65, 1
  call void @_ZdlPvm(ptr noundef %59, i64 noundef %66) #23
  br label %67

67:                                               ; preds = %61, %64
  call void @llvm.lifetime.end.p0(i64 32, ptr nonnull %6) #20
  %68 = load ptr, ptr %5, align 8, !tbaa !13
  %69 = getelementptr inbounds i8, ptr %5, i64 8
  %70 = load ptr, ptr %69, align 8, !tbaa !13
  %71 = icmp eq ptr %68, %70
  br i1 %71, label %124, label %72

72:                                               ; preds = %67, %110
  %73 = phi i64 [ %115, %110 ], [ 115200, %67 ]
  %74 = phi i8 [ %114, %110 ], [ 110, %67 ]
  %75 = phi i32 [ %113, %110 ], [ 2, %67 ]
  %76 = phi i8 [ %112, %110 ], [ 78, %67 ]
  %77 = phi i32 [ %111, %110 ], [ 8, %67 ]
  %78 = phi ptr [ %116, %110 ], [ %68, %67 ]
  %79 = getelementptr inbounds i8, ptr %78, i64 8
  %80 = load i64, ptr %79, align 8, !tbaa !14
  %81 = load ptr, ptr %78, align 8, !tbaa !5
  switch i64 %80, label %101 [
    i64 1, label %82
    i64 3, label %98
  ]

82:                                               ; preds = %72
  %83 = load i8, ptr %81, align 1, !tbaa !16
  %84 = call noundef zeroext i1 @_Z7matchescPKc(i8 noundef signext %83, ptr noundef nonnull @.str.2)
  br i1 %84, label %110, label %85

85:                                               ; preds = %82
  %86 = call noundef zeroext i1 @_Z7matchescPKc(i8 noundef signext %83, ptr noundef nonnull @.str.3)
  br i1 %86, label %110, label %87

87:                                               ; preds = %85
  %88 = call noundef zeroext i1 @_Z7matchescPKc(i8 noundef signext %83, ptr noundef nonnull @.str.4)
  br i1 %88, label %89, label %92

89:                                               ; preds = %87
  %90 = sext i8 %83 to i32
  %91 = add nsw i32 %90, -48
  br label %110

92:                                               ; preds = %87
  %93 = call noundef zeroext i1 @_Z7matchescPKc(i8 noundef signext %83, ptr noundef nonnull @.str.5)
  br i1 %93, label %94, label %118

94:                                               ; preds = %92
  %95 = sext i8 %83 to i32
  %96 = shl nsw i32 %95, 1
  %97 = add nsw i32 %96, -96
  br label %110

98:                                               ; preds = %72
  %99 = call i32 @bcmp(ptr noundef nonnull dereferenceable(3) %81, ptr noundef nonnull dereferenceable(3) @.str.8, i64 3)
  %100 = icmp eq i32 %99, 0
  br i1 %100, label %110, label %101

101:                                              ; preds = %72, %98
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %3) #20
  %102 = call i64 @__isoc23_strtoull(ptr noundef %81, ptr noundef nonnull %3, i32 noundef 10) #20
  %103 = load ptr, ptr %3, align 8, !tbaa !13
  %104 = load ptr, ptr %78, align 8, !tbaa !5
  %105 = ptrtoint ptr %103 to i64
  %106 = ptrtoint ptr %104 to i64
  %107 = sub i64 %105, %106
  %108 = load i64, ptr %79, align 8, !tbaa !14
  %109 = icmp eq i64 %107, %108
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %3) #20
  br i1 %109, label %110, label %118

110:                                              ; preds = %101, %89, %94, %82, %85, %98
  %111 = phi i32 [ %77, %98 ], [ %77, %85 ], [ %77, %82 ], [ %77, %94 ], [ %91, %89 ], [ %77, %101 ]
  %112 = phi i8 [ %76, %98 ], [ %83, %85 ], [ %76, %82 ], [ %76, %94 ], [ %76, %89 ], [ %76, %101 ]
  %113 = phi i32 [ 3, %98 ], [ %75, %85 ], [ %75, %82 ], [ %97, %94 ], [ %75, %89 ], [ %75, %101 ]
  %114 = phi i8 [ %74, %98 ], [ %74, %85 ], [ %83, %82 ], [ %74, %94 ], [ %74, %89 ], [ %74, %101 ]
  %115 = phi i64 [ %73, %98 ], [ %73, %85 ], [ %73, %82 ], [ %73, %94 ], [ %73, %89 ], [ %102, %101 ]
  %116 = getelementptr inbounds i8, ptr %78, i64 32
  %117 = icmp eq ptr %116, %70
  br i1 %117, label %124, label %72

118:                                              ; preds = %101, %92
  %119 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.6, i64 noundef 18) #20
  %120 = load ptr, ptr %78, align 8, !tbaa !5
  %121 = load i64, ptr %79, align 8, !tbaa !14
  %122 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef %120, i64 noundef %121) #20
  %123 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %122, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %124

124:                                              ; preds = %110, %118, %67
  %125 = phi i32 [ 8, %67 ], [ %77, %118 ], [ %111, %110 ]
  %126 = phi i8 [ 78, %67 ], [ %76, %118 ], [ %112, %110 ]
  %127 = phi i32 [ 2, %67 ], [ %75, %118 ], [ %113, %110 ]
  %128 = phi i8 [ 110, %67 ], [ %74, %118 ], [ %114, %110 ]
  %129 = phi i64 [ 115200, %67 ], [ %73, %118 ], [ %115, %110 ]
  %130 = phi i1 [ true, %67 ], [ false, %118 ], [ true, %110 ]
  %131 = phi i32 [ 0, %67 ], [ 1, %118 ], [ 0, %110 ]
  %132 = load ptr, ptr %5, align 8, !tbaa !17
  %133 = load ptr, ptr %69, align 8, !tbaa !20
  %134 = icmp eq ptr %132, %133
  br i1 %134, label %152, label %135

135:                                              ; preds = %124, %147
  %136 = phi ptr [ %148, %147 ], [ %132, %124 ]
  %137 = load ptr, ptr %136, align 8, !tbaa !5
  %138 = getelementptr inbounds i8, ptr %136, i64 16
  %139 = icmp eq ptr %137, %138
  br i1 %139, label %140, label %144

140:                                              ; preds = %135
  %141 = getelementptr inbounds i8, ptr %136, i64 8
  %142 = load i64, ptr %141, align 8, !tbaa !14
  %143 = icmp ult i64 %142, 16
  call void @llvm.assume(i1 %143)
  br label %147

144:                                              ; preds = %135
  %145 = load i64, ptr %138, align 8, !tbaa !16
  %146 = add i64 %145, 1
  call void @_ZdlPvm(ptr noundef %137, i64 noundef %146) #23
  br label %147

147:                                              ; preds = %144, %140
  %148 = getelementptr inbounds i8, ptr %136, i64 32
  %149 = icmp eq ptr %148, %133
  br i1 %149, label %150, label %135, !llvm.loop !29

150:                                              ; preds = %147
  %151 = load ptr, ptr %5, align 8, !tbaa !17
  br label %152

152:                                              ; preds = %150, %124
  %153 = phi ptr [ %151, %150 ], [ %132, %124 ]
  %154 = icmp eq ptr %153, null
  br i1 %154, label %161, label %155

155:                                              ; preds = %152
  %156 = getelementptr inbounds i8, ptr %5, i64 16
  %157 = load ptr, ptr %156, align 8, !tbaa !19
  %158 = ptrtoint ptr %157 to i64
  %159 = ptrtoint ptr %153 to i64
  %160 = sub i64 %158, %159
  call void @_ZdlPvm(ptr noundef nonnull %153, i64 noundef %160) #23
  br label %161

161:                                              ; preds = %152, %155
  call void @llvm.lifetime.end.p0(i64 24, ptr nonnull %5) #20
  br i1 %130, label %162, label %386

162:                                              ; preds = %161
  %163 = icmp eq i32 %127, 3
  %164 = icmp ne i32 %125, 5
  %165 = select i1 %163, i1 %164, i1 false
  br i1 %165, label %166, label %170

166:                                              ; preds = %162
  %167 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.9, i64 noundef 43) #20
  %168 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSolsEi(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, i32 noundef %125) #20
  %169 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %168, ptr noundef nonnull @.str.10, i64 noundef 14) #20
  br label %386

170:                                              ; preds = %21, %162
  %171 = phi i64 [ %129, %162 ], [ 115200, %21 ]
  %172 = phi i8 [ %128, %162 ], [ 110, %21 ]
  %173 = phi i32 [ %127, %162 ], [ 2, %21 ]
  %174 = phi i8 [ %126, %162 ], [ 78, %21 ]
  %175 = phi i32 [ %125, %162 ], [ 8, %21 ]
  call void @llvm.lifetime.start.p0(i64 4, ptr nonnull %8) #20
  %176 = call i32 (ptr, i32, ...) @open(ptr noundef %23, i32 noundef 1054978) #20
  store i32 %176, ptr %8, align 4, !tbaa !30
  %177 = icmp slt i32 %176, 0
  br i1 %177, label %178, label %211

178:                                              ; preds = %170
  %179 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.11, i64 noundef 14) #20
  %180 = icmp eq ptr %23, null
  br i1 %180, label %181, label %189

181:                                              ; preds = %178
  %182 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %183 = getelementptr i8, ptr %182, i64 -24
  %184 = load i64, ptr %183, align 8
  %185 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %184
  %186 = getelementptr inbounds i8, ptr %185, i64 32
  %187 = load i32, ptr %186, align 8, !tbaa !34
  %188 = or i32 %187, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %185, i32 noundef %188) #20
  br label %192

189:                                              ; preds = %178
  %190 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %23) #20
  %191 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %23, i64 noundef %190) #20
  br label %192

192:                                              ; preds = %181, %189
  %193 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.12, i64 noundef 2) #20
  %194 = tail call ptr @__errno_location() #25
  %195 = load i32, ptr %194, align 4, !tbaa !30
  %196 = call ptr @strerror(i32 noundef %195) #20
  %197 = icmp eq ptr %196, null
  br i1 %197, label %198, label %206

198:                                              ; preds = %192
  %199 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %200 = getelementptr i8, ptr %199, i64 -24
  %201 = load i64, ptr %200, align 8
  %202 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %201
  %203 = getelementptr inbounds i8, ptr %202, i64 32
  %204 = load i32, ptr %203, align 8, !tbaa !34
  %205 = or i32 %204, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %202, i32 noundef %205) #20
  br label %209

206:                                              ; preds = %192
  %207 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %196) #20
  %208 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %196, i64 noundef %207) #20
  br label %209

209:                                              ; preds = %198, %206
  %210 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %384

211:                                              ; preds = %170
  %212 = call i32 (i32, i32, ...) @fcntl(i32 noundef %176, i32 noundef 4, i32 noundef 0) #20
  %213 = icmp eq i32 %212, -1
  br i1 %213, label %214, label %233

214:                                              ; preds = %211
  %215 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.13, i64 noundef 14) #20
  %216 = tail call ptr @__errno_location() #25
  %217 = load i32, ptr %216, align 4, !tbaa !30
  %218 = call ptr @strerror(i32 noundef %217) #20
  %219 = icmp eq ptr %218, null
  br i1 %219, label %220, label %228

220:                                              ; preds = %214
  %221 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %222 = getelementptr i8, ptr %221, i64 -24
  %223 = load i64, ptr %222, align 8
  %224 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %223
  %225 = getelementptr inbounds i8, ptr %224, i64 32
  %226 = load i32, ptr %225, align 8, !tbaa !34
  %227 = or i32 %226, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %224, i32 noundef %227) #20
  br label %231

228:                                              ; preds = %214
  %229 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %218) #20
  %230 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %218, i64 noundef %229) #20
  br label %231

231:                                              ; preds = %220, %228
  %232 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %384

233:                                              ; preds = %211
  call void @llvm.lifetime.start.p0(i64 60, ptr nonnull %9) #20
  %234 = call i32 @tcgetattr(i32 noundef %176, ptr noundef nonnull %9) #20
  %235 = icmp eq i32 %234, 0
  br i1 %235, label %255, label %236

236:                                              ; preds = %233
  %237 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.14, i64 noundef 18) #20
  %238 = tail call ptr @__errno_location() #25
  %239 = load i32, ptr %238, align 4, !tbaa !30
  %240 = call ptr @strerror(i32 noundef %239) #20
  %241 = icmp eq ptr %240, null
  br i1 %241, label %242, label %250

242:                                              ; preds = %236
  %243 = load ptr, ptr @_ZSt4cerr, align 8, !tbaa !32
  %244 = getelementptr i8, ptr %243, i64 -24
  %245 = load i64, ptr %244, align 8
  %246 = getelementptr inbounds i8, ptr @_ZSt4cerr, i64 %245
  %247 = getelementptr inbounds i8, ptr %246, i64 32
  %248 = load i32, ptr %247, align 8, !tbaa !34
  %249 = or i32 %248, 1
  call void @_ZNSt9basic_iosIcSt11char_traitsIcEE5clearESt12_Ios_Iostate(ptr noundef nonnull align 8 dereferenceable(264) %246, i32 noundef %249) #20
  br label %253

250:                                              ; preds = %236
  %251 = call noundef i64 @strlen(ptr noundef nonnull dereferenceable(1) %240) #20
  %252 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull %240, i64 noundef %251) #20
  br label %253

253:                                              ; preds = %242, %250
  %254 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %382

255:                                              ; preds = %233
  %256 = trunc i64 %171 to i32
  %257 = call i32 @cfsetspeed(ptr noundef nonnull %9, i32 noundef %256) #20
  %258 = getelementptr inbounds i8, ptr %9, i64 8
  %259 = load i32, ptr %258, align 4, !tbaa !40
  %260 = and i32 %259, -49
  store i32 %260, ptr %258, align 4, !tbaa !40
  switch i32 %175, label %267 [
    i32 5, label %271
    i32 6, label %261
    i32 7, label %263
    i32 8, label %265
  ]

261:                                              ; preds = %255
  %262 = or disjoint i32 %260, 16
  br label %271

263:                                              ; preds = %255
  %264 = or disjoint i32 %260, 32
  br label %271

265:                                              ; preds = %255
  %266 = or i32 %259, 48
  br label %271

267:                                              ; preds = %255
  %268 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.15, i64 noundef 19) #20
  %269 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSolsEi(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, i32 noundef %175) #20
  %270 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %269, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %382

271:                                              ; preds = %255, %265, %263, %261
  %272 = phi i32 [ %266, %265 ], [ %264, %263 ], [ %262, %261 ], [ %260, %255 ]
  %273 = load i32, ptr %9, align 4, !tbaa !42
  %274 = getelementptr inbounds i8, ptr %9, i64 12
  store i32 0, ptr %274, align 4, !tbaa !43
  %275 = getelementptr inbounds i8, ptr %9, i64 4
  store i32 0, ptr %275, align 4, !tbaa !44
  %276 = getelementptr inbounds i8, ptr %9, i64 23
  store i8 0, ptr %276, align 1, !tbaa !16
  %277 = getelementptr inbounds i8, ptr %9, i64 22
  store i8 5, ptr %277, align 2, !tbaa !16
  %278 = and i32 %273, -7170
  %279 = icmp eq i8 %174, 88
  %280 = or disjoint i32 %278, 5120
  %281 = select i1 %279, i32 %280, i32 %278
  store i32 %281, ptr %9, align 4, !tbaa !42
  %282 = and i32 %272, -1073744769
  %283 = or disjoint i32 %282, 2176
  store i32 %283, ptr %258, align 4, !tbaa !40
  switch i8 %172, label %292 [
    i8 101, label %284
    i8 111, label %286
    i8 109, label %288
    i8 115, label %290
    i8 110, label %297
  ]

284:                                              ; preds = %271
  %285 = or disjoint i32 %282, 2432
  br label %297

286:                                              ; preds = %271
  %287 = or disjoint i32 %282, 2944
  br label %297

288:                                              ; preds = %271
  %289 = or i32 %272, 1073744768
  br label %297

290:                                              ; preds = %271
  %291 = or disjoint i32 %282, 1073744256
  br label %297

292:                                              ; preds = %271
  %293 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.16, i64 noundef 16) #20
  %294 = sext i8 %172 to i32
  %295 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZNSolsEi(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, i32 noundef %294) #20
  %296 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %295, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %382

297:                                              ; preds = %271, %290, %288, %286, %284
  %298 = phi i32 [ %283, %271 ], [ %291, %290 ], [ %289, %288 ], [ %287, %286 ], [ %285, %284 ]
  %299 = icmp eq i32 %173, 2
  %300 = and i32 %298, 2147483583
  %301 = select i1 %299, i32 0, i32 64
  %302 = icmp eq i8 %174, 82
  %303 = select i1 %302, i32 -2147483648, i32 0
  %304 = or disjoint i32 %303, %301
  %305 = or disjoint i32 %304, %300
  store i32 %305, ptr %258, align 4, !tbaa !40
  %306 = call i32 @tcsetattr(i32 noundef %176, i32 noundef 0, ptr noundef nonnull %9) #20
  %307 = icmp eq i32 %306, 0
  br i1 %307, label %315, label %308

308:                                              ; preds = %297
  %309 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.17, i64 noundef 18) #20
  %310 = tail call ptr @__errno_location() #25
  %311 = load i32, ptr %310, align 4, !tbaa !30
  %312 = call ptr @strerror(i32 noundef %311) #20
  %313 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef %312)
  %314 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %313, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %382

315:                                              ; preds = %297
  call void @llvm.lifetime.start.p0(i64 1, ptr nonnull %10) #20
  store i8 1, ptr %10, align 1, !tbaa !45
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %11) #20
  %316 = call i32 @pipe(ptr noundef nonnull %11) #20
  %317 = icmp slt i32 %316, 0
  br i1 %317, label %318, label %325

318:                                              ; preds = %315
  %319 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.18, i64 noundef 13) #20
  %320 = tail call ptr @__errno_location() #25
  %321 = load i32, ptr %320, align 4, !tbaa !30
  %322 = call ptr @strerror(i32 noundef %321) #20
  %323 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef %322)
  %324 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %323, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %380

325:                                              ; preds = %315
  call void @llvm.lifetime.start.p0(i64 8, ptr nonnull %12) #20
  call void @llvm.lifetime.start.p0(i64 24, ptr nonnull %13) #20
  store ptr %10, ptr %13, align 8, !tbaa !13
  %326 = getelementptr inbounds i8, ptr %13, i64 8
  store ptr %11, ptr %326, align 8, !tbaa !13
  %327 = getelementptr inbounds i8, ptr %13, i64 16
  store ptr %8, ptr %327, align 8, !tbaa !13
  call fastcc void @"_ZNSt6threadC2IZ4mainE3$_0JEvEEOT_DpOT0_"(ptr noundef nonnull align 8 dereferenceable(8) %12, ptr noundef nonnull align 8 dereferenceable(24) %13)
  call void @llvm.lifetime.end.p0(i64 24, ptr nonnull %13) #20
  call void @llvm.lifetime.start.p0(i64 128, ptr nonnull %14) #20
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 8 dereferenceable(128) %14, i8 0, i64 128, i1 false), !tbaa !12
  %328 = load i32, ptr %8, align 4, !tbaa !30
  %329 = srem i32 %328, 64
  %330 = zext nneg i32 %329 to i64
  %331 = shl nuw i64 1, %330
  %332 = sdiv i32 %328, 64
  %333 = sext i32 %332 to i64
  %334 = getelementptr inbounds [16 x i64], ptr %14, i64 0, i64 %333
  %335 = load i64, ptr %334, align 8, !tbaa !12
  %336 = or i64 %331, %335
  store i64 %336, ptr %334, align 8, !tbaa !12
  %337 = load i32, ptr %11, align 4, !tbaa !30
  %338 = srem i32 %337, 64
  %339 = zext nneg i32 %338 to i64
  %340 = shl nuw i64 1, %339
  %341 = sdiv i32 %337, 64
  %342 = sext i32 %341 to i64
  %343 = getelementptr inbounds [16 x i64], ptr %14, i64 0, i64 %342
  %344 = load i64, ptr %343, align 8, !tbaa !12
  %345 = or i64 %340, %344
  store i64 %345, ptr %343, align 8, !tbaa !12
  call void @llvm.lifetime.start.p0(i64 16, ptr nonnull %15) #20
  call void @llvm.memset.p0.i64(ptr noundef nonnull align 8 dereferenceable(16) %15, i8 0, i64 16, i1 false)
  call void @llvm.lifetime.start.p0(i64 1, ptr nonnull %16) #20
  %346 = call i32 @select(i32 noundef 2, ptr noundef nonnull %14, ptr noundef null, ptr noundef null, ptr noundef nonnull %15) #20
  %347 = load ptr, ptr @stdout, align 8, !tbaa !13
  %348 = call i32 @fflush(ptr noundef %347)
  %349 = load i8, ptr %10, align 1, !tbaa !45, !range !47, !noundef !48
  %350 = trunc nuw i8 %349 to i1
  br i1 %350, label %351, label %373

351:                                              ; preds = %325, %367
  %352 = load i32, ptr %8, align 4, !tbaa !30
  %353 = call i64 @read(i32 noundef %352, ptr noundef nonnull %16, i64 noundef 1) #20
  %354 = icmp slt i64 %353, 0
  br i1 %354, label %355, label %362

355:                                              ; preds = %351
  %356 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef nonnull @.str.19, i64 noundef 16) #20
  %357 = tail call ptr @__errno_location() #25
  %358 = load i32, ptr %357, align 4, !tbaa !30
  %359 = call ptr @strerror(i32 noundef %358) #20
  %360 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_PKc(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cerr, ptr noundef %359)
  %361 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZSt16__ostream_insertIcSt11char_traitsIcEERSt13basic_ostreamIT_T0_ES6_PKS3_l(ptr noundef nonnull align 8 dereferenceable(8) %360, ptr noundef nonnull @.str.7, i64 noundef 1) #20
  br label %374

362:                                              ; preds = %351
  %363 = icmp eq i64 %353, 0
  br i1 %363, label %367, label %364

364:                                              ; preds = %362
  %365 = load i8, ptr %16, align 1, !tbaa !16
  %366 = call noundef nonnull align 8 dereferenceable(8) ptr @_ZStlsISt11char_traitsIcEERSt13basic_ostreamIcT_ES5_c(ptr noundef nonnull align 8 dereferenceable(8) @_ZSt4cout, i8 noundef signext %365)
  br label %367

367:                                              ; preds = %362, %364
  %368 = call i32 @select(i32 noundef 2, ptr noundef nonnull %14, ptr noundef null, ptr noundef null, ptr noundef nonnull %15) #20
  %369 = load ptr, ptr @stdout, align 8, !tbaa !13
  %370 = call i32 @fflush(ptr noundef %369)
  %371 = load i8, ptr %10, align 1, !tbaa !45, !range !47, !noundef !48
  %372 = trunc nuw i8 %371 to i1
  br i1 %372, label %351, label %373

373:                                              ; preds = %367, %325
  call void @_ZNSt6thread4joinEv(ptr noundef nonnull align 8 dereferenceable(8) %12) #20
  br label %374

374:                                              ; preds = %355, %373
  %375 = phi i32 [ 0, %373 ], [ 1, %355 ]
  call void @llvm.lifetime.end.p0(i64 1, ptr nonnull %16) #20
  call void @llvm.lifetime.end.p0(i64 16, ptr nonnull %15) #20
  call void @llvm.lifetime.end.p0(i64 128, ptr nonnull %14) #20
  %376 = load i64, ptr %12, align 8, !tbaa !12
  %377 = icmp eq i64 %376, 0
  br i1 %377, label %379, label %378

378:                                              ; preds = %374
  call void @_ZSt9terminatev() #24
  unreachable

379:                                              ; preds = %374
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %12) #20
  br label %380

380:                                              ; preds = %379, %318
  %381 = phi i32 [ 1, %318 ], [ %375, %379 ]
  call void @llvm.lifetime.end.p0(i64 8, ptr nonnull %11) #20
  call void @llvm.lifetime.end.p0(i64 1, ptr nonnull %10) #20
  br label %382

382:                                              ; preds = %380, %308, %292, %267, %253
  %383 = phi i32 [ 1, %253 ], [ 1, %267 ], [ 1, %292 ], [ 1, %308 ], [ %381, %380 ]
  call void @llvm.lifetime.end.p0(i64 60, ptr nonnull %9) #20
  br label %384

384:                                              ; preds = %382, %231, %209
  %385 = phi i32 [ 1, %209 ], [ 1, %231 ], [ %383, %382 ]
  call void @llvm.lifetime.end.p0(i64 4, ptr nonnull %8) #20
  br label %386

386:                                              ; preds = %166, %384, %161, %19
  %387 = phi i32 [ 1, %19 ], [ 1, %166 ], [ %385, %384 ], [ %131, %161 ]
  ret i32 %387
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
  store i64 0, ptr %0, align 8, !tbaa !49
  %4 = tail call noalias noundef nonnull dereferenceable(32) ptr @_Znwm(i64 noundef 32) #22
  store ptr getelementptr inbounds inrange(-16, 24) (i8, ptr @"_ZTVNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEEE", i64 16), ptr %4, align 8, !tbaa !32
  %5 = getelementptr inbounds i8, ptr %4, i64 8
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(24) %5, ptr noundef nonnull readonly align 8 dereferenceable(24) %1, i64 24, i1 false), !tbaa.struct !51
  store ptr %4, ptr %3, align 8, !tbaa !13
  call void @_ZNSt6thread15_M_start_threadESt10unique_ptrINS_6_StateESt14default_deleteIS1_EEPFvvE(ptr noundef nonnull align 8 dereferenceable(8) %0, ptr noundef nonnull %3, ptr noundef nonnull @_ZNSt6thread24_M_thread_deps_never_runEv) #20
  %6 = load ptr, ptr %3, align 8, !tbaa !13
  %7 = icmp eq ptr %6, null
  br i1 %7, label %12, label %8

8:                                                ; preds = %2
  %9 = load ptr, ptr %6, align 8, !tbaa !32
  %10 = getelementptr inbounds i8, ptr %9, i64 8
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
declare void @_ZdlPvm(ptr noundef, i64 noundef) local_unnamed_addr #13

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
  %3 = getelementptr inbounds i8, ptr %0, i64 8
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
  %22 = getelementptr inbounds i8, ptr %21, i64 16
  store ptr %22, ptr %21, align 8, !tbaa !15
  %23 = load ptr, ptr %1, align 8, !tbaa !5
  %24 = getelementptr inbounds i8, ptr %1, i64 16
  %25 = icmp eq ptr %23, %24
  br i1 %25, label %26, label %31

26:                                               ; preds = %11
  %27 = getelementptr inbounds i8, ptr %1, i64 8
  %28 = load i64, ptr %27, align 8, !tbaa !14
  %29 = icmp ult i64 %28, 16
  tail call void @llvm.assume(i1 %29)
  %30 = add nuw nsw i64 %28, 1
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(1) %22, ptr noundef nonnull align 8 dereferenceable(1) %24, i64 %30, i1 false)
  br label %35

31:                                               ; preds = %11
  store ptr %23, ptr %21, align 8, !tbaa !5
  %32 = load i64, ptr %24, align 8, !tbaa !16
  store i64 %32, ptr %22, align 8, !tbaa !16
  %33 = getelementptr inbounds i8, ptr %1, i64 8
  %34 = load i64, ptr %33, align 8, !tbaa !14
  br label %35

35:                                               ; preds = %26, %31
  %36 = phi i64 [ %28, %26 ], [ %34, %31 ]
  %37 = getelementptr inbounds i8, ptr %1, i64 8
  %38 = getelementptr inbounds i8, ptr %21, i64 8
  store i64 %36, ptr %38, align 8, !tbaa !14
  store ptr %24, ptr %1, align 8, !tbaa !5
  store i64 0, ptr %37, align 8, !tbaa !14
  store i8 0, ptr %24, align 8, !tbaa !16
  %39 = icmp eq ptr %5, %4
  br i1 %39, label %63, label %40

40:                                               ; preds = %35, %56
  %41 = phi ptr [ %61, %56 ], [ %20, %35 ]
  %42 = phi ptr [ %60, %56 ], [ %5, %35 ]
  tail call void @llvm.experimental.noalias.scope.decl(metadata !52)
  tail call void @llvm.experimental.noalias.scope.decl(metadata !55)
  %43 = getelementptr inbounds i8, ptr %41, i64 16
  store ptr %43, ptr %41, align 8, !tbaa !15, !alias.scope !52, !noalias !55
  %44 = load ptr, ptr %42, align 8, !tbaa !5, !alias.scope !55, !noalias !52
  %45 = getelementptr inbounds i8, ptr %42, i64 16
  %46 = icmp eq ptr %44, %45
  br i1 %46, label %47, label %52

47:                                               ; preds = %40
  %48 = getelementptr inbounds i8, ptr %42, i64 8
  %49 = load i64, ptr %48, align 8, !tbaa !14, !alias.scope !55, !noalias !52
  %50 = icmp ult i64 %49, 16
  tail call void @llvm.assume(i1 %50)
  %51 = add nuw nsw i64 %49, 1
  tail call void @llvm.memcpy.p0.p0.i64(ptr noundef nonnull align 8 dereferenceable(1) %43, ptr noundef nonnull align 8 dereferenceable(1) %45, i64 %51, i1 false), !alias.scope !57
  br label %56

52:                                               ; preds = %40
  store ptr %44, ptr %41, align 8, !tbaa !5, !alias.scope !52, !noalias !55
  %53 = load i64, ptr %45, align 8, !tbaa !16, !alias.scope !55, !noalias !52
  store i64 %53, ptr %43, align 8, !tbaa !16, !alias.scope !52, !noalias !55
  %54 = getelementptr inbounds i8, ptr %42, i64 8
  %55 = load i64, ptr %54, align 8, !tbaa !14, !alias.scope !55, !noalias !52
  br label %56

56:                                               ; preds = %52, %47
  %57 = phi i64 [ %49, %47 ], [ %55, %52 ]
  %58 = getelementptr inbounds i8, ptr %42, i64 8
  %59 = getelementptr inbounds i8, ptr %41, i64 8
  store i64 %57, ptr %59, align 8, !tbaa !14, !alias.scope !52, !noalias !55
  store ptr %45, ptr %42, align 8, !tbaa !5, !alias.scope !55, !noalias !52
  store i64 0, ptr %58, align 8, !tbaa !14, !alias.scope !55, !noalias !52
  store i8 0, ptr %45, align 1, !tbaa !16, !alias.scope !55, !noalias !52
  %60 = getelementptr inbounds i8, ptr %42, i64 32
  %61 = getelementptr inbounds i8, ptr %41, i64 32
  %62 = icmp eq ptr %60, %4
  br i1 %62, label %63, label %40, !llvm.loop !58

63:                                               ; preds = %56, %35
  %64 = phi ptr [ %20, %35 ], [ %61, %56 ]
  %65 = getelementptr inbounds i8, ptr %0, i64 16
  %66 = icmp eq ptr %5, null
  br i1 %66, label %71, label %67

67:                                               ; preds = %63
  %68 = load ptr, ptr %65, align 8, !tbaa !19
  %69 = ptrtoint ptr %68 to i64
  %70 = sub i64 %69, %7
  tail call void @_ZdlPvm(ptr noundef nonnull %5, i64 noundef %70) #23
  br label %71

71:                                               ; preds = %63, %67
  %72 = getelementptr inbounds i8, ptr %64, i64 32
  store ptr %20, ptr %0, align 8, !tbaa !17
  store ptr %72, ptr %3, align 8, !tbaa !20
  %73 = getelementptr inbounds %"class.std::__cxx11::basic_string", ptr %20, i64 %17
  store ptr %73, ptr %65, align 8, !tbaa !19
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
  tail call void @_ZdlPvm(ptr noundef nonnull %0, i64 noundef 32) #23
  ret void
}

; Function Attrs: mustprogress nounwind sspstrong uwtable
define internal void @"_ZNSt6thread11_State_implINS_8_InvokerISt5tupleIJZ4mainE3$_0EEEEE6_M_runEv"(ptr nocapture noundef nonnull readonly align 8 dereferenceable(32) %0) unnamed_addr #0 align 2 {
  %2 = alloca %struct.termios, align 4
  %3 = alloca i8, align 1
  %4 = getelementptr inbounds i8, ptr %0, i64 8
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
  %18 = getelementptr inbounds i8, ptr %17, i64 32
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
  %27 = getelementptr inbounds i8, ptr %2, i64 12
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
  %45 = getelementptr inbounds i8, ptr %44, i64 32
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
  %57 = getelementptr inbounds i8, ptr %0, i64 24
  %58 = getelementptr inbounds i8, ptr %0, i64 16
  br label %59

59:                                               ; preds = %137, %56
  %60 = load i8, ptr %3, align 1, !tbaa !16
  %61 = icmp eq i8 %60, 3
  br i1 %61, label %62, label %88

62:                                               ; preds = %59
  %63 = load ptr, ptr %4, align 8, !tbaa !59
  store i8 0, ptr %63, align 1, !tbaa !45
  %64 = load ptr, ptr %58, align 8, !tbaa !61
  %65 = getelementptr inbounds i8, ptr %64, i64 4
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
  %80 = getelementptr inbounds i8, ptr %79, i64 32
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
  %104 = getelementptr inbounds i8, ptr %103, i64 32
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
  %114 = getelementptr inbounds i8, ptr %113, i64 4
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
  %129 = getelementptr inbounds i8, ptr %128, i64 32
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
!4 = !{!"clang version 19.1.7"}
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
!49 = !{!50, !11, i64 0}
!50 = !{!"_ZTSNSt6thread2idE", !11, i64 0}
!51 = !{i64 0, i64 8, !13, i64 8, i64 8, !13, i64 16, i64 8, !13}
!52 = !{!53}
!53 = distinct !{!53, !54, !"_ZSt19__relocate_object_aINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_SaIS5_EEvPT_PT0_RT1_: argument 0"}
!54 = distinct !{!54, !"_ZSt19__relocate_object_aINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_SaIS5_EEvPT_PT0_RT1_"}
!55 = !{!56}
!56 = distinct !{!56, !54, !"_ZSt19__relocate_object_aINSt7__cxx1112basic_stringIcSt11char_traitsIcESaIcEEES5_SaIS5_EEvPT_PT0_RT1_: argument 1"}
!57 = !{!53, !56}
!58 = distinct !{!58, !28}
!59 = !{!60, !8, i64 0}
!60 = !{!"_ZTSZ4mainE3$_0", !8, i64 0, !8, i64 8, !8, i64 16}
!61 = !{!60, !8, i64 8}
!62 = !{!60, !8, i64 16}
!63 = distinct !{!63, !28}
