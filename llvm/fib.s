; ModuleID = 'fib.c'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-f80:128:128-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32"
target triple = "i386-pc-mingw32"

@.str = private unnamed_addr constant [4 x i8] c"%d\0A\00"
@.str1 = private unnamed_addr constant [15 x i8] c"Usage: %s <n>\0A\00"

define i32 @count(i32 %x, i32 %n) nounwind readnone {
  %1 = icmp eq i32 %x, %n
  %x.tr.lcssa = select i1 %1, i32 %x, i32 %n
  ret i32 %x.tr.lcssa
}

define i32 @main(i32 %argc, i8** nocapture %argv) nounwind {
  %1 = icmp eq i32 %argc, 2
  br i1 %1, label %2, label %7

; <label>:2                                       ; preds = %0
  %3 = getelementptr inbounds i8** %argv, i32 1
  %4 = load i8** %3, align 4, !tbaa !0
  %5 = tail call i32 (...)* @atoi(i8* %4) nounwind
  %6 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([4 x i8]* @.str, i32 0, i32 0), i32 %5) nounwind
  br label %10

; <label>:7                                       ; preds = %0
  %8 = load i8** %argv, align 4, !tbaa !0
  %9 = tail call i32 (i8*, ...)* @printf(i8* getelementptr inbounds ([15 x i8]* @.str1, i32 0, i32 0), i8* %8) nounwind
  br label %10

; <label>:10                                      ; preds = %7, %2
  %ret.0 = phi i32 [ 0, %2 ], [ 1, %7 ]
  ret i32 %ret.0
}

declare i32 @printf(i8* nocapture, ...) nounwind

declare i32 @atoi(...)

!0 = metadata !{metadata !"any pointer", metadata !1}
!1 = metadata !{metadata !"omnipotent char", metadata !2}
!2 = metadata !{metadata !"Simple C/C++ TBAA", null}
