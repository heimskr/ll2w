; ModuleID = '/home/kai/src/simple.cpp'
source_filename = "/home/kai/src/simple.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress nofree norecurse nosync nounwind readnone sspstrong uwtable willreturn
define dso_local noundef i32 @_Z6triplei(i32 noundef %0) local_unnamed_addr #0 !dbg !11 {
  call void @llvm.dbg.value(metadata i32 %0, metadata !16, metadata !DIExpression()), !dbg !17
  %2 = mul nsw i32 %0, 3, !dbg !18
  ret i32 %2, !dbg !19
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind readnone sspstrong uwtable willreturn
define dso_local noundef i32 @_Z8sextuplej(i32 noundef %0) local_unnamed_addr #0 !dbg !20 {
  call void @llvm.dbg.value(metadata i32 %0, metadata !25, metadata !DIExpression()), !dbg !26
  %2 = mul i32 %0, 6, !dbg !27
  ret i32 %2, !dbg !28
}

; Function Attrs: mustprogress nofree norecurse nosync nounwind readnone sspstrong uwtable willreturn
define dso_local noundef i32 @main() local_unnamed_addr #0 !dbg !29 {
  ret i32 60, !dbg !32
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #1

attributes #0 = { mustprogress nofree norecurse nosync nounwind readnone sspstrong uwtable willreturn "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nofree nosync nounwind readnone speculatable willreturn }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!4, !5, !6, !7, !8, !9}
!llvm.ident = !{!10}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 14.0.6", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug, retainedTypes: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/home/kai/src/simple.cpp", directory: "/home/kai/src/ll2w", checksumkind: CSK_MD5, checksum: "2aeecf3ac283c39b4763d974fd6cc0ee")
!2 = !{!3}
!3 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!4 = !{i32 7, !"Dwarf Version", i32 5}
!5 = !{i32 2, !"Debug Info Version", i32 3}
!6 = !{i32 1, !"wchar_size", i32 4}
!7 = !{i32 7, !"PIC Level", i32 2}
!8 = !{i32 7, !"PIE Level", i32 2}
!9 = !{i32 7, !"uwtable", i32 1}
!10 = !{!"clang version 14.0.6"}
!11 = distinct !DISubprogram(name: "triple", linkageName: "_Z6triplei", scope: !12, file: !12, line: 1, type: !13, scopeLine: 1, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !15)
!12 = !DIFile(filename: "simple.cpp", directory: "/home/kai/src", checksumkind: CSK_MD5, checksum: "2aeecf3ac283c39b4763d974fd6cc0ee")
!13 = !DISubroutineType(types: !14)
!14 = !{!3, !3}
!15 = !{!16}
!16 = !DILocalVariable(name: "x", arg: 1, scope: !11, file: !12, line: 1, type: !3)
!17 = !DILocation(line: 0, scope: !11)
!18 = !DILocation(line: 2, column: 15, scope: !11)
!19 = !DILocation(line: 2, column: 2, scope: !11)
!20 = distinct !DISubprogram(name: "sextuple", linkageName: "_Z8sextuplej", scope: !12, file: !12, line: 5, type: !21, scopeLine: 5, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !24)
!21 = !DISubroutineType(types: !22)
!22 = !{!23, !23}
!23 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!24 = !{!25}
!25 = !DILocalVariable(name: "x", arg: 1, scope: !20, file: !12, line: 5, type: !23)
!26 = !DILocation(line: 0, scope: !20)
!27 = !DILocation(line: 6, column: 37, scope: !20)
!28 = !DILocation(line: 6, column: 2, scope: !20)
!29 = distinct !DISubprogram(name: "main", scope: !12, file: !12, line: 9, type: !30, scopeLine: 9, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !31)
!30 = !DISubroutineType(types: !2)
!31 = !{}
!32 = !DILocation(line: 10, column: 2, scope: !29)
