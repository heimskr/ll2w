define i32* @hello() {
	foo:
}

/*
declare i32 @printf(i8* nocapture readonly, ...) unnamed_addr readonly convergent
declare private hidden dllimport fastcc zeroext signext dereferenceable_or_null(42) i32 @puts(i8* nocapture readonly, [3 x i64]) #5
declare void @exit(i32) local_unnamed_addr #2
declare %struct.__sFILE* @"\01_fopen"(i8*, i8*) local_unnamed_addr #3
declare i32 @fscanf(%struct.__sFILE* nocapture, i8* nocapture readonly, ...) local_unnamed_addr #1
declare i32 @fprintf(%struct.__sFILE* nocapture, i8* nocapture readonly, ...) local_unnamed_addr #1
declare noalias i8* @calloc(i64, i64) local_unnamed_addr #1
declare i32 @fclose(%struct.__sFILE* nocapture) local_unnamed_addr #1
declare void @free(i8* nocapture %"foo", i8 nocapture %bar) local_unnamed_addr
declare void @ellipse(...) local_unnamed_addr #1

attributes #5 = { noinline norecurse nounwind readonly ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

%struct.__sFILE = type { i8*, i32, i32, i16, i16, %struct.__sbuf, i32, i8*, i32 (i8*)*, i32 (i8*, i8*, i32)*, i64 (i8*, i64, i32)*, i32 (i8*, i8*, i32)*, %struct.__sbuf, %struct.__sFILEX*, i32, [3 x i8], [1 x i8], %struct.__sbuf, i32, i64 }
%struct.opaque = type opaque
@.str.6 = private unnamed_addr constant [6 x i8] c"%d %d\00", align 1
@.str.7 = private default unnamed_addr constant [37 x i8] c"Adjacency list representation of G:\0A\00", align 1
@__stderrp = external hidden dllimport thread_local(localexec) local_unnamed_addr addrspace(42) global %struct.__sFILE*, align 8
@.str.1.16 = private protected unnamed_addr externally_initialized constant [1 x i8] zeroinitializer, align 1
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
*/