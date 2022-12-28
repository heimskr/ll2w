; ModuleID = '/home/kai/src/simple.cpp'
source_filename = "/home/kai/src/simple.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress noinline nounwind optnone sspstrong uwtable
define dso_local noundef i32 @_Z6triplei(i32 noundef %0) #0 !dbg !12 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !17, metadata !DIExpression()), !dbg !18
  %3 = load i32, i32* %2, align 4, !dbg !19
  %4 = mul nsw i32 2, %3, !dbg !20
  %5 = load i32, i32* %2, align 4, !dbg !21
  %6 = add nsw i32 %4, %5, !dbg !22
  ret i32 %6, !dbg !23
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.declare(metadata, metadata, metadata) #1

; Function Attrs: mustprogress noinline nounwind optnone sspstrong uwtable
define dso_local noundef i32 @_Z8sextuplej(i32 noundef %0) #0 !dbg !24 {
  %2 = alloca i32, align 4
  store i32 %0, i32* %2, align 4
  call void @llvm.dbg.declare(metadata i32* %2, metadata !28, metadata !DIExpression()), !dbg !29
  %3 = load i32, i32* %2, align 4, !dbg !30
  %4 = call noundef i32 @_Z6triplei(i32 noundef %3), !dbg !31
  %5 = load i32, i32* %2, align 4, !dbg !32
  %6 = mul i32 3, %5, !dbg !33
  %7 = add i32 %4, %6, !dbg !34
  ret i32 %7, !dbg !35
}

; Function Attrs: mustprogress noinline norecurse nounwind optnone sspstrong uwtable
define dso_local noundef i32 @main() #2 !dbg !36 {
  %1 = alloca i32, align 4
  store i32 0, i32* %1, align 4
  %2 = call noundef i32 @_Z8sextuplej(i32 noundef 10), !dbg !38
  ret i32 %2, !dbg !39
}

attributes #0 = { mustprogress noinline nounwind optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #2 = { mustprogress noinline norecurse nounwind optnone sspstrong uwtable "frame-pointer"="all" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!4, !5, !6, !7, !8, !9, !10}
!llvm.ident = !{!11}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 14.0.6", isOptimized: false, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/home/kai/src/simple.cpp", directory: "/home/kai/src/ll2w", checksumkind: CSK_MD5, checksum: "2aeecf3ac283c39b4763d974fd6cc0ee")
!2 = !{!3}
!3 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!4 = !{i32 7, !"Dwarf Version", i32 5}
!5 = !{i32 2, !"Debug Info Version", i32 3}
!6 = !{i32 1, !"wchar_size", i32 4}
!7 = !{i32 7, !"PIC Level", i32 2}
!8 = !{i32 7, !"PIE Level", i32 2}
!9 = !{i32 7, !"uwtable", i32 1}
!10 = !{i32 7, !"frame-pointer", i32 2}
!11 = !{!"clang version 14.0.6"}
!12 = distinct !DISubprogram(name: "triple", linkageName: "_Z6triplei", scope: !13, file: !13, line: 1, type: !14, scopeLine: 1, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !16)
!13 = !DIFile(filename: "simple.cpp", directory: "/home/kai/src", checksumkind: CSK_MD5, checksum: "2aeecf3ac283c39b4763d974fd6cc0ee")
!14 = !DISubroutineType(types: !15)
!15 = !{!3, !3}
!16 = !{}
!17 = !DILocalVariable(name: "x", arg: 1, scope: !12, file: !13, line: 1, type: !3)
!18 = !DILocation(line: 1, column: 16, scope: !12)
!19 = !DILocation(line: 2, column: 13, scope: !12)
!20 = !DILocation(line: 2, column: 11, scope: !12)
!21 = !DILocation(line: 2, column: 17, scope: !12)
!22 = !DILocation(line: 2, column: 15, scope: !12)
!23 = !DILocation(line: 2, column: 2, scope: !12)
!24 = distinct !DISubprogram(name: "sextuple", linkageName: "_Z8sextuplej", scope: !13, file: !13, line: 5, type: !25, scopeLine: 5, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !16)
!25 = !DISubroutineType(types: !26)
!26 = !{!27, !27}
!27 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!28 = !DILocalVariable(name: "x", arg: 1, scope: !24, file: !13, line: 5, type: !27)
!29 = !DILocation(line: 5, column: 28, scope: !24)
!30 = !DILocation(line: 6, column: 33, scope: !24)
!31 = !DILocation(line: 6, column: 9, scope: !24)
!32 = !DILocation(line: 6, column: 43, scope: !24)
!33 = !DILocation(line: 6, column: 41, scope: !24)
!34 = !DILocation(line: 6, column: 37, scope: !24)
!35 = !DILocation(line: 6, column: 2, scope: !24)
!36 = distinct !DISubprogram(name: "main", scope: !13, file: !13, line: 9, type: !37, scopeLine: 9, flags: DIFlagPrototyped, spFlags: DISPFlagDefinition, unit: !0, retainedNodes: !16)
!37 = !DISubroutineType(types: !2)
!38 = !DILocation(line: 10, column: 9, scope: !36)
!39 = !DILocation(line: 10, column: 2, scope: !36)
