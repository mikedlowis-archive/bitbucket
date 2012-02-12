; ModuleID = 'runtime.c'
target datalayout = "e-p:32:32:32-i1:8:8-i8:8:8-i16:16:16-i32:32:32-i64:64:64-f32:32:32-f64:64:64-f80:128:128-v64:64:64-v128:128:128-a0:0:64-f80:32:32-n8:16:32"
target triple = "i386-pc-mingw32"

%struct.DuckyType = type { i8* }

@.str = private unnamed_addr constant [8 x i8] c"integer\00"
@T_INT = global %struct.DuckyType { i8* getelementptr inbounds ([8 x i8]* @.str, i32 0, i32 0) }, align 4
@.str1 = private unnamed_addr constant [6 x i8] c"float\00"
@T_FLOAT = global %struct.DuckyType { i8* getelementptr inbounds ([6 x i8]* @.str1, i32 0, i32 0) }, align 4
@.str2 = private unnamed_addr constant [7 x i8] c"string\00"
@T_STRING = global %struct.DuckyType { i8* getelementptr inbounds ([7 x i8]* @.str2, i32 0, i32 0) }, align 4
@.str3 = private unnamed_addr constant [6 x i8] c"array\00"
@T_ARRAY = global %struct.DuckyType { i8* getelementptr inbounds ([6 x i8]* @.str3, i32 0, i32 0) }, align 4
@.str4 = private unnamed_addr constant [4 x i8] c"map\00"
@T_MAP = global %struct.DuckyType { i8* getelementptr inbounds ([4 x i8]* @.str4, i32 0, i32 0) }, align 4

define i8* @Ducky_DeclareVar(%struct.DuckyType* %type, i32 %size) nounwind {
  %1 = alloca %struct.DuckyType*, align 4
  %2 = alloca i32, align 4
  %temp = alloca i8*, align 4
  store %struct.DuckyType* %type, %struct.DuckyType** %1, align 4
  store i32 %size, i32* %2, align 4
  %3 = load i32* %2, align 4
  %4 = add i32 4, %3
  %5 = call i8* @malloc(i32 %4)
  store i8* %5, i8** %temp, align 4
  %6 = load %struct.DuckyType** %1, align 4
  %7 = load i8** %temp, align 4
  %8 = bitcast i8* %7 to %struct.DuckyType**
  store %struct.DuckyType* %6, %struct.DuckyType** %8
  %9 = load i8** %temp, align 4
  ret i8* %9
}

declare i8* @malloc(i32)

define i32 @main() nounwind {
  %1 = alloca i32, align 4
  %foo = alloca i8*, align 4
  store i32 0, i32* %1
  %2 = call i8* @Ducky_DeclareVar(%struct.DuckyType* @T_INT, i32 4)
  store i8* %2, i8** %foo, align 4
  %3 = load i8** %foo, align 4
  %4 = getelementptr inbounds i8* %3, i32 4
  %5 = bitcast i8* %4 to i32*
  store i32 5, i32* %5
  ret i32 0
}
