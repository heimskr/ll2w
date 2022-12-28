; ModuleID = '/home/kai/src/simplish.cpp'
source_filename = "/home/kai/src/simplish.cpp"
target datalayout = "e-m:e-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-pc-linux-gnu"

; Function Attrs: mustprogress nounwind sspstrong uwtable
define dso_local noundef i32 @_Z3bari(i32 noundef %0) local_unnamed_addr #0 !dbg !257 {
  call void @llvm.dbg.value(metadata i32 %0, metadata !260, metadata !DIExpression()), !dbg !261
  %2 = call i32 @rand() #4, !dbg !262
  %3 = srem i32 %2, 100, !dbg !263
  %4 = add nsw i32 %3, %0, !dbg !264
  ret i32 %4, !dbg !265
}

; Function Attrs: nounwind
declare !dbg !266 i32 @rand() local_unnamed_addr #1

; Function Attrs: mustprogress nounwind sspstrong uwtable
define dso_local noundef i32 @_Z3fooi(i32 noundef %0) local_unnamed_addr #0 !dbg !268 {
  call void @llvm.dbg.value(metadata i32 %0, metadata !270, metadata !DIExpression()), !dbg !271
  br label %2, !dbg !272

2:                                                ; preds = %2, %1
  %3 = phi i32 [ %0, %1 ], [ %6, %2 ]
  call void @llvm.dbg.value(metadata i32 %3, metadata !270, metadata !DIExpression()), !dbg !271
  call void @llvm.dbg.value(metadata i32 %3, metadata !260, metadata !DIExpression()) #4, !dbg !273
  %4 = call i32 @rand() #4, !dbg !276
  %5 = srem i32 %4, 100, !dbg !277
  %6 = add nsw i32 %5, %3, !dbg !278
  call void @llvm.dbg.value(metadata i32 %6, metadata !270, metadata !DIExpression()), !dbg !271
  %7 = icmp sgt i32 %6, 10000, !dbg !279
  br i1 %7, label %2, label %8, !dbg !280, !llvm.loop !281

8:                                                ; preds = %2
  %9 = sdiv i32 %6, 2, !dbg !285
  ret i32 %9, !dbg !286
}

; Function Attrs: mustprogress norecurse nounwind sspstrong uwtable
define dso_local noundef i32 @main() local_unnamed_addr #2 !dbg !287 {
  call void @llvm.dbg.value(metadata i32 10, metadata !270, metadata !DIExpression()) #4, !dbg !288
  call void @llvm.dbg.value(metadata i32 10, metadata !270, metadata !DIExpression()) #4, !dbg !288
  call void @llvm.dbg.value(metadata i32 10, metadata !260, metadata !DIExpression()) #4, !dbg !290
  %1 = call i32 @rand() #4, !dbg !292
  call void @llvm.dbg.value(metadata i32 %1, metadata !270, metadata !DIExpression(DW_OP_constu, 100, DW_OP_mod, DW_OP_plus_uconst, 10, DW_OP_stack_value)) #4, !dbg !288
  %2 = srem i32 %1, 100, !dbg !293
  call void @llvm.dbg.value(metadata i32 %2, metadata !270, metadata !DIExpression(DW_OP_plus_uconst, 10, DW_OP_stack_value)) #4, !dbg !288
  %3 = add nsw i32 %2, 10, !dbg !294
  call void @llvm.dbg.value(metadata i32 %3, metadata !270, metadata !DIExpression()) #4, !dbg !288
  %4 = sdiv i32 %3, 2, !dbg !295
  %5 = srem i32 %4, 100, !dbg !296
  ret i32 %5, !dbg !297
}

; Function Attrs: nofree nosync nounwind readnone speculatable willreturn
declare void @llvm.dbg.value(metadata, metadata, metadata) #3

attributes #0 = { mustprogress nounwind sspstrong uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #1 = { nounwind "frame-pointer"="none" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #2 = { mustprogress norecurse nounwind sspstrong uwtable "frame-pointer"="none" "min-legal-vector-width"="0" "no-trapping-math"="true" "stack-protector-buffer-size"="8" "target-cpu"="x86-64" "target-features"="+cx8,+fxsr,+mmx,+sse,+sse2,+x87" "tune-cpu"="generic" }
attributes #3 = { nofree nosync nounwind readnone speculatable willreturn }
attributes #4 = { nounwind }

!llvm.dbg.cu = !{!0}
!llvm.module.flags = !{!250, !251, !252, !253, !254, !255}
!llvm.ident = !{!256}

!0 = distinct !DICompileUnit(language: DW_LANG_C_plus_plus_14, file: !1, producer: "clang version 14.0.6", isOptimized: true, runtimeVersion: 0, emissionKind: FullDebug, imports: !2, splitDebugInlining: false, nameTableKind: None)
!1 = !DIFile(filename: "/home/kai/src/simplish.cpp", directory: "/home/kai/src/ll2w", checksumkind: CSK_MD5, checksum: "558706e777a8961fd614ac925a4e77b5")
!2 = !{!3, !11, !15, !22, !26, !31, !33, !42, !46, !50, !65, !69, !73, !77, !81, !86, !90, !94, !98, !102, !110, !114, !118, !120, !124, !128, !133, !139, !143, !147, !149, !157, !161, !169, !171, !175, !179, !183, !187, !192, !197, !202, !203, !204, !205, !207, !208, !209, !210, !211, !212, !213, !215, !216, !217, !218, !219, !220, !221, !226, !227, !228, !229, !230, !231, !232, !233, !234, !235, !236, !237, !238, !239, !240, !241, !242, !243, !244, !245, !246, !247, !248, !249}
!3 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !5, file: !10, line: 52)
!4 = !DINamespace(name: "std", scope: null)
!5 = !DISubprogram(name: "abs", scope: !6, file: !6, line: 861, type: !7, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!6 = !DIFile(filename: "/usr/include/stdlib.h", directory: "", checksumkind: CSK_MD5, checksum: "4b47dc81a92f1fe77a152c0aac236718")
!7 = !DISubroutineType(types: !8)
!8 = !{!9, !9}
!9 = !DIBasicType(name: "int", size: 32, encoding: DW_ATE_signed)
!10 = !DIFile(filename: "/usr/bin/../lib64/gcc/x86_64-pc-linux-gnu/12.2.0/../../../../include/c++/12.2.0/bits/std_abs.h", directory: "")
!11 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !12, file: !14, line: 127)
!12 = !DIDerivedType(tag: DW_TAG_typedef, name: "div_t", file: !6, line: 63, baseType: !13)
!13 = !DICompositeType(tag: DW_TAG_structure_type, file: !6, line: 59, size: 64, flags: DIFlagFwdDecl, identifier: "_ZTS5div_t")
!14 = !DIFile(filename: "/usr/bin/../lib64/gcc/x86_64-pc-linux-gnu/12.2.0/../../../../include/c++/12.2.0/cstdlib", directory: "")
!15 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !16, file: !14, line: 128)
!16 = !DIDerivedType(tag: DW_TAG_typedef, name: "ldiv_t", file: !6, line: 71, baseType: !17)
!17 = distinct !DICompositeType(tag: DW_TAG_structure_type, file: !6, line: 67, size: 128, flags: DIFlagTypePassByValue, elements: !18, identifier: "_ZTS6ldiv_t")
!18 = !{!19, !21}
!19 = !DIDerivedType(tag: DW_TAG_member, name: "quot", scope: !17, file: !6, line: 69, baseType: !20, size: 64)
!20 = !DIBasicType(name: "long", size: 64, encoding: DW_ATE_signed)
!21 = !DIDerivedType(tag: DW_TAG_member, name: "rem", scope: !17, file: !6, line: 70, baseType: !20, size: 64, offset: 64)
!22 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !23, file: !14, line: 130)
!23 = !DISubprogram(name: "abort", scope: !6, file: !6, line: 611, type: !24, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagOptimized)
!24 = !DISubroutineType(types: !25)
!25 = !{null}
!26 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !27, file: !14, line: 134)
!27 = !DISubprogram(name: "atexit", scope: !6, file: !6, line: 615, type: !28, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!28 = !DISubroutineType(types: !29)
!29 = !{!9, !30}
!30 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !24, size: 64)
!31 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !32, file: !14, line: 137)
!32 = !DISubprogram(name: "at_quick_exit", scope: !6, file: !6, line: 620, type: !28, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!33 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !34, file: !14, line: 140)
!34 = !DISubprogram(name: "atof", scope: !35, file: !35, line: 25, type: !36, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!35 = !DIFile(filename: "/usr/include/bits/stdlib-float.h", directory: "", checksumkind: CSK_MD5, checksum: "adfe1626ff4efc68ac58c367ff5f206b")
!36 = !DISubroutineType(types: !37)
!37 = !{!38, !39}
!38 = !DIBasicType(name: "double", size: 64, encoding: DW_ATE_float)
!39 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !40, size: 64)
!40 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !41)
!41 = !DIBasicType(name: "char", size: 8, encoding: DW_ATE_signed_char)
!42 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !43, file: !14, line: 141)
!43 = !DISubprogram(name: "atoi", scope: !6, file: !6, line: 362, type: !44, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!44 = !DISubroutineType(types: !45)
!45 = !{!9, !39}
!46 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !47, file: !14, line: 142)
!47 = !DISubprogram(name: "atol", scope: !6, file: !6, line: 367, type: !48, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!48 = !DISubroutineType(types: !49)
!49 = !{!20, !39}
!50 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !51, file: !14, line: 143)
!51 = !DISubprogram(name: "bsearch", scope: !52, file: !52, line: 20, type: !53, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!52 = !DIFile(filename: "/usr/include/bits/stdlib-bsearch.h", directory: "", checksumkind: CSK_MD5, checksum: "724ededa330cc3e0cbd34c5b4030a6f6")
!53 = !DISubroutineType(types: !54)
!54 = !{!55, !56, !56, !58, !58, !61}
!55 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: null, size: 64)
!56 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !57, size: 64)
!57 = !DIDerivedType(tag: DW_TAG_const_type, baseType: null)
!58 = !DIDerivedType(tag: DW_TAG_typedef, name: "size_t", file: !59, line: 46, baseType: !60)
!59 = !DIFile(filename: "/usr/lib/clang/14.0.6/include/stddef.h", directory: "", checksumkind: CSK_MD5, checksum: "2499dd2361b915724b073282bea3a7bc")
!60 = !DIBasicType(name: "unsigned long", size: 64, encoding: DW_ATE_unsigned)
!61 = !DIDerivedType(tag: DW_TAG_typedef, name: "__compar_fn_t", file: !6, line: 829, baseType: !62)
!62 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !63, size: 64)
!63 = !DISubroutineType(types: !64)
!64 = !{!9, !56, !56}
!65 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !66, file: !14, line: 144)
!66 = !DISubprogram(name: "calloc", scope: !6, file: !6, line: 556, type: !67, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!67 = !DISubroutineType(types: !68)
!68 = !{!55, !58, !58}
!69 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !70, file: !14, line: 145)
!70 = !DISubprogram(name: "div", scope: !6, file: !6, line: 873, type: !71, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!71 = !DISubroutineType(types: !72)
!72 = !{!12, !9, !9}
!73 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !74, file: !14, line: 146)
!74 = !DISubprogram(name: "exit", scope: !6, file: !6, line: 637, type: !75, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagOptimized)
!75 = !DISubroutineType(types: !76)
!76 = !{null, !9}
!77 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !78, file: !14, line: 147)
!78 = !DISubprogram(name: "free", scope: !6, file: !6, line: 568, type: !79, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!79 = !DISubroutineType(types: !80)
!80 = !{null, !55}
!81 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !82, file: !14, line: 148)
!82 = !DISubprogram(name: "getenv", scope: !6, file: !6, line: 654, type: !83, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!83 = !DISubroutineType(types: !84)
!84 = !{!85, !39}
!85 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !41, size: 64)
!86 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !87, file: !14, line: 149)
!87 = !DISubprogram(name: "labs", scope: !6, file: !6, line: 862, type: !88, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!88 = !DISubroutineType(types: !89)
!89 = !{!20, !20}
!90 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !91, file: !14, line: 150)
!91 = !DISubprogram(name: "ldiv", scope: !6, file: !6, line: 875, type: !92, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!92 = !DISubroutineType(types: !93)
!93 = !{!16, !20, !20}
!94 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !95, file: !14, line: 151)
!95 = !DISubprogram(name: "malloc", scope: !6, file: !6, line: 553, type: !96, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!96 = !DISubroutineType(types: !97)
!97 = !{!55, !58}
!98 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !99, file: !14, line: 153)
!99 = !DISubprogram(name: "mblen", scope: !6, file: !6, line: 943, type: !100, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!100 = !DISubroutineType(types: !101)
!101 = !{!9, !39, !58}
!102 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !103, file: !14, line: 154)
!103 = !DISubprogram(name: "mbstowcs", scope: !6, file: !6, line: 954, type: !104, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!104 = !DISubroutineType(types: !105)
!105 = !{!58, !106, !109, !58}
!106 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !107)
!107 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !108, size: 64)
!108 = !DIBasicType(name: "wchar_t", size: 32, encoding: DW_ATE_signed)
!109 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !39)
!110 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !111, file: !14, line: 155)
!111 = !DISubprogram(name: "mbtowc", scope: !6, file: !6, line: 946, type: !112, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!112 = !DISubroutineType(types: !113)
!113 = !{!9, !106, !109, !58}
!114 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !115, file: !14, line: 157)
!115 = !DISubprogram(name: "qsort", scope: !6, file: !6, line: 851, type: !116, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!116 = !DISubroutineType(types: !117)
!117 = !{null, !55, !58, !58, !61}
!118 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !119, file: !14, line: 160)
!119 = !DISubprogram(name: "quick_exit", scope: !6, file: !6, line: 643, type: !75, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagOptimized)
!120 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !121, file: !14, line: 163)
!121 = !DISubprogram(name: "rand", scope: !6, file: !6, line: 454, type: !122, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!122 = !DISubroutineType(types: !123)
!123 = !{!9}
!124 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !125, file: !14, line: 164)
!125 = !DISubprogram(name: "realloc", scope: !6, file: !6, line: 564, type: !126, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!126 = !DISubroutineType(types: !127)
!127 = !{!55, !55, !58}
!128 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !129, file: !14, line: 165)
!129 = !DISubprogram(name: "srand", scope: !6, file: !6, line: 456, type: !130, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!130 = !DISubroutineType(types: !131)
!131 = !{null, !132}
!132 = !DIBasicType(name: "unsigned int", size: 32, encoding: DW_ATE_unsigned)
!133 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !134, file: !14, line: 166)
!134 = !DISubprogram(name: "strtod", scope: !6, file: !6, line: 118, type: !135, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!135 = !DISubroutineType(types: !136)
!136 = !{!38, !109, !137}
!137 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !138)
!138 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !85, size: 64)
!139 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !140, file: !14, line: 167)
!140 = !DISubprogram(name: "strtol", scope: !6, file: !6, line: 177, type: !141, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!141 = !DISubroutineType(types: !142)
!142 = !{!20, !109, !137, !9}
!143 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !144, file: !14, line: 168)
!144 = !DISubprogram(name: "strtoul", scope: !6, file: !6, line: 181, type: !145, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!145 = !DISubroutineType(types: !146)
!146 = !{!60, !109, !137, !9}
!147 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !148, file: !14, line: 169)
!148 = !DISubprogram(name: "system", scope: !6, file: !6, line: 804, type: !44, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!149 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !150, file: !14, line: 171)
!150 = !DISubprogram(name: "wcstombs", scope: !6, file: !6, line: 958, type: !151, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!151 = !DISubroutineType(types: !152)
!152 = !{!58, !153, !154, !58}
!153 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !85)
!154 = !DIDerivedType(tag: DW_TAG_restrict_type, baseType: !155)
!155 = !DIDerivedType(tag: DW_TAG_pointer_type, baseType: !156, size: 64)
!156 = !DIDerivedType(tag: DW_TAG_const_type, baseType: !108)
!157 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !158, file: !14, line: 172)
!158 = !DISubprogram(name: "wctomb", scope: !6, file: !6, line: 950, type: !159, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!159 = !DISubroutineType(types: !160)
!160 = !{!9, !85, !108}
!161 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !162, entity: !163, file: !14, line: 200)
!162 = !DINamespace(name: "__gnu_cxx", scope: null)
!163 = !DIDerivedType(tag: DW_TAG_typedef, name: "lldiv_t", file: !6, line: 81, baseType: !164)
!164 = distinct !DICompositeType(tag: DW_TAG_structure_type, file: !6, line: 77, size: 128, flags: DIFlagTypePassByValue, elements: !165, identifier: "_ZTS7lldiv_t")
!165 = !{!166, !168}
!166 = !DIDerivedType(tag: DW_TAG_member, name: "quot", scope: !164, file: !6, line: 79, baseType: !167, size: 64)
!167 = !DIBasicType(name: "long long", size: 64, encoding: DW_ATE_signed)
!168 = !DIDerivedType(tag: DW_TAG_member, name: "rem", scope: !164, file: !6, line: 80, baseType: !167, size: 64, offset: 64)
!169 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !162, entity: !170, file: !14, line: 206)
!170 = !DISubprogram(name: "_Exit", scope: !6, file: !6, line: 649, type: !75, flags: DIFlagPrototyped | DIFlagNoReturn, spFlags: DISPFlagOptimized)
!171 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !162, entity: !172, file: !14, line: 210)
!172 = !DISubprogram(name: "llabs", scope: !6, file: !6, line: 865, type: !173, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!173 = !DISubroutineType(types: !174)
!174 = !{!167, !167}
!175 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !162, entity: !176, file: !14, line: 216)
!176 = !DISubprogram(name: "lldiv", scope: !6, file: !6, line: 879, type: !177, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!177 = !DISubroutineType(types: !178)
!178 = !{!163, !167, !167}
!179 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !162, entity: !180, file: !14, line: 227)
!180 = !DISubprogram(name: "atoll", scope: !6, file: !6, line: 374, type: !181, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!181 = !DISubroutineType(types: !182)
!182 = !{!167, !39}
!183 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !162, entity: !184, file: !14, line: 228)
!184 = !DISubprogram(name: "strtoll", scope: !6, file: !6, line: 201, type: !185, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!185 = !DISubroutineType(types: !186)
!186 = !{!167, !109, !137, !9}
!187 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !162, entity: !188, file: !14, line: 229)
!188 = !DISubprogram(name: "strtoull", scope: !6, file: !6, line: 206, type: !189, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!189 = !DISubroutineType(types: !190)
!190 = !{!191, !109, !137, !9}
!191 = !DIBasicType(name: "unsigned long long", size: 64, encoding: DW_ATE_unsigned)
!192 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !162, entity: !193, file: !14, line: 231)
!193 = !DISubprogram(name: "strtof", scope: !6, file: !6, line: 124, type: !194, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!194 = !DISubroutineType(types: !195)
!195 = !{!196, !109, !137}
!196 = !DIBasicType(name: "float", size: 32, encoding: DW_ATE_float)
!197 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !162, entity: !198, file: !14, line: 232)
!198 = !DISubprogram(name: "strtold", scope: !6, file: !6, line: 127, type: !199, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!199 = !DISubroutineType(types: !200)
!200 = !{!201, !109, !137}
!201 = !DIBasicType(name: "long double", size: 128, encoding: DW_ATE_float)
!202 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !163, file: !14, line: 240)
!203 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !170, file: !14, line: 242)
!204 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !172, file: !14, line: 244)
!205 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !206, file: !14, line: 245)
!206 = !DISubprogram(name: "div", linkageName: "_ZN9__gnu_cxx3divExx", scope: !162, file: !14, line: 213, type: !177, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!207 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !176, file: !14, line: 246)
!208 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !180, file: !14, line: 248)
!209 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !193, file: !14, line: 249)
!210 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !184, file: !14, line: 250)
!211 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !188, file: !14, line: 251)
!212 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !4, entity: !198, file: !14, line: 252)
!213 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !23, file: !214, line: 38)
!214 = !DIFile(filename: "/usr/bin/../lib64/gcc/x86_64-pc-linux-gnu/12.2.0/../../../../include/c++/12.2.0/stdlib.h", directory: "", checksumkind: CSK_MD5, checksum: "ce88caced6ed945413de73c65016f4c2")
!215 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !27, file: !214, line: 39)
!216 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !74, file: !214, line: 40)
!217 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !32, file: !214, line: 43)
!218 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !119, file: !214, line: 46)
!219 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !12, file: !214, line: 51)
!220 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !16, file: !214, line: 52)
!221 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !222, file: !214, line: 54)
!222 = !DISubprogram(name: "abs", linkageName: "_ZSt3absg", scope: !4, file: !10, line: 103, type: !223, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized)
!223 = !DISubroutineType(types: !224)
!224 = !{!225, !225}
!225 = !DIBasicType(name: "__float128", size: 128, encoding: DW_ATE_float)
!226 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !34, file: !214, line: 55)
!227 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !43, file: !214, line: 56)
!228 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !47, file: !214, line: 57)
!229 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !51, file: !214, line: 58)
!230 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !66, file: !214, line: 59)
!231 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !206, file: !214, line: 60)
!232 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !78, file: !214, line: 61)
!233 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !82, file: !214, line: 62)
!234 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !87, file: !214, line: 63)
!235 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !91, file: !214, line: 64)
!236 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !95, file: !214, line: 65)
!237 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !99, file: !214, line: 67)
!238 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !103, file: !214, line: 68)
!239 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !111, file: !214, line: 69)
!240 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !115, file: !214, line: 71)
!241 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !121, file: !214, line: 72)
!242 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !125, file: !214, line: 73)
!243 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !129, file: !214, line: 74)
!244 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !134, file: !214, line: 75)
!245 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !140, file: !214, line: 76)
!246 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !144, file: !214, line: 77)
!247 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !148, file: !214, line: 78)
!248 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !150, file: !214, line: 80)
!249 = !DIImportedEntity(tag: DW_TAG_imported_declaration, scope: !0, entity: !158, file: !214, line: 81)
!250 = !{i32 7, !"Dwarf Version", i32 5}
!251 = !{i32 2, !"Debug Info Version", i32 3}
!252 = !{i32 1, !"wchar_size", i32 4}
!253 = !{i32 7, !"PIC Level", i32 2}
!254 = !{i32 7, !"PIE Level", i32 2}
!255 = !{i32 7, !"uwtable", i32 1}
!256 = !{!"clang version 14.0.6"}
!257 = distinct !DISubprogram(name: "bar", linkageName: "_Z3bari", scope: !258, file: !258, line: 3, type: !7, scopeLine: 3, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !259)
!258 = !DIFile(filename: "simplish.cpp", directory: "/home/kai/src", checksumkind: CSK_MD5, checksum: "558706e777a8961fd614ac925a4e77b5")
!259 = !{!260}
!260 = !DILocalVariable(name: "x", arg: 1, scope: !257, file: !258, line: 3, type: !9)
!261 = !DILocation(line: 0, scope: !257)
!262 = !DILocation(line: 4, column: 13, scope: !257)
!263 = !DILocation(line: 4, column: 20, scope: !257)
!264 = !DILocation(line: 4, column: 11, scope: !257)
!265 = !DILocation(line: 4, column: 2, scope: !257)
!266 = !DISubprogram(name: "rand", scope: !6, file: !6, line: 454, type: !122, flags: DIFlagPrototyped, spFlags: DISPFlagOptimized, retainedNodes: !267)
!267 = !{}
!268 = distinct !DISubprogram(name: "foo", linkageName: "_Z3fooi", scope: !258, file: !258, line: 7, type: !7, scopeLine: 7, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !269)
!269 = !{!270}
!270 = !DILocalVariable(name: "x", arg: 1, scope: !268, file: !258, line: 7, type: !9)
!271 = !DILocation(line: 0, scope: !268)
!272 = !DILocation(line: 8, column: 2, scope: !268)
!273 = !DILocation(line: 0, scope: !257, inlinedAt: !274)
!274 = distinct !DILocation(line: 9, column: 7, scope: !275)
!275 = distinct !DILexicalBlock(scope: !268, file: !258, line: 8, column: 5)
!276 = !DILocation(line: 4, column: 13, scope: !257, inlinedAt: !274)
!277 = !DILocation(line: 4, column: 20, scope: !257, inlinedAt: !274)
!278 = !DILocation(line: 4, column: 11, scope: !257, inlinedAt: !274)
!279 = !DILocation(line: 10, column: 17, scope: !268)
!280 = !DILocation(line: 10, column: 2, scope: !275)
!281 = distinct !{!281, !272, !282, !283, !284}
!282 = !DILocation(line: 10, column: 20, scope: !268)
!283 = !{!"llvm.loop.mustprogress"}
!284 = !{!"llvm.loop.unroll.disable"}
!285 = !DILocation(line: 11, column: 11, scope: !268)
!286 = !DILocation(line: 11, column: 2, scope: !268)
!287 = distinct !DISubprogram(name: "main", scope: !258, file: !258, line: 14, type: !122, scopeLine: 14, flags: DIFlagPrototyped | DIFlagAllCallsDescribed, spFlags: DISPFlagDefinition | DISPFlagOptimized, unit: !0, retainedNodes: !267)
!288 = !DILocation(line: 0, scope: !268, inlinedAt: !289)
!289 = distinct !DILocation(line: 15, column: 9, scope: !287)
!290 = !DILocation(line: 0, scope: !257, inlinedAt: !291)
!291 = distinct !DILocation(line: 9, column: 7, scope: !275, inlinedAt: !289)
!292 = !DILocation(line: 4, column: 13, scope: !257, inlinedAt: !291)
!293 = !DILocation(line: 4, column: 20, scope: !257, inlinedAt: !291)
!294 = !DILocation(line: 4, column: 11, scope: !257, inlinedAt: !291)
!295 = !DILocation(line: 11, column: 11, scope: !268, inlinedAt: !289)
!296 = !DILocation(line: 15, column: 17, scope: !287)
!297 = !DILocation(line: 15, column: 2, scope: !287)
