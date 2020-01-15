@.str.6 = private unnamed_addr constant [6 x i8] c"%d %d\00", align 1

source_filename = "foobar"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.12.0"

!llvm.ident = !{!0, !0, !0}
!llvm.module.flags = !{!1}

!0 = !{!"clang version 4.0.0 (tags/RELEASE_400/final)"}
!1 = !{i32 1, !"PIC Level", i32 2}
!2 = distinct !{!2, !3}
!3 = !{!"llvm.loop.unroll.disable"}
!4 = !{!0, !3, !2, !4, !1, !"four", !5, i32 1}
!5 = distinct !{!5, !3}
