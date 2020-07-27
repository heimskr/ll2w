; ModuleID = 'combined.c'
source_filename = "combined.c"
target datalayout = "e-m:o-p270:32:32-p271:32:32-p272:64:64-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.mintf_str = type { i8*, i64 }
%struct.__va_list_tag = type { i32, i32, i8*, i8* }

@.str = private unnamed_addr constant [42 x i8] c"Integer stringification\0A================\0A\00", align 1
@.str.1 = private unnamed_addr constant [44 x i8] c"================\0A\0Amintf()\0A================\0A\00", align 1
@.str.2 = private unnamed_addr constant [14 x i8] c"%lld -> \22%s\22\0A\00", align 1
@.str.3 = private unnamed_addr constant [14 x i8] c"%llu -> \22%s\22\0A\00", align 1
@.str.4 = private unnamed_addr constant [31 x i8] c"%d %d %ld %ld '%c' \22%s\22 %u %%\0A\00", align 1
@.str.5 = private unnamed_addr constant [6 x i8] c"hello\00", align 1
@.str.6 = private unnamed_addr constant [30 x i8] c"----------------\0APrinted: %d\0A\00", align 1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i64 @strlen(i8* %0) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca i64, align 8
  store i8* %0, i8** %2, align 8
  store i64 0, i64* %3, align 8
  br label %4

4:                                                ; preds = %11, %1
  %5 = load i8*, i8** %2, align 8
  %6 = load i64, i64* %3, align 8
  %7 = getelementptr inbounds i8, i8* %5, i64 %6
  %8 = load i8, i8* %7, align 1
  %9 = icmp ne i8 %8, 0
  br i1 %9, label %10, label %14

10:                                               ; preds = %4
  br label %11

11:                                               ; preds = %10
  %12 = load i64, i64* %3, align 8
  %13 = add i64 %12, 1
  store i64 %13, i64* %3, align 8
  br label %4

14:                                               ; preds = %4
  %15 = load i64, i64* %3, align 8
  ret i64 %15
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @mappend(%struct.mintf_str* %0, i64 %1, i8 signext %2) #0 {
  %4 = alloca i32, align 4
  %5 = alloca %struct.mintf_str*, align 8
  %6 = alloca i64, align 8
  %7 = alloca i8, align 1
  store %struct.mintf_str* %0, %struct.mintf_str** %5, align 8
  store i64 %1, i64* %6, align 8
  store i8 %2, i8* %7, align 1
  %8 = load %struct.mintf_str*, %struct.mintf_str** %5, align 8
  %9 = icmp eq %struct.mintf_str* %8, null
  br i1 %9, label %10, label %12

10:                                               ; preds = %3
  %11 = load i8, i8* %7, align 1
  call void @prc(i8 signext %11)
  store i32 1, i32* %4, align 4
  br label %36

12:                                               ; preds = %3
  %13 = load %struct.mintf_str*, %struct.mintf_str** %5, align 8
  %14 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %13, i32 0, i32 1
  %15 = load i64, i64* %14, align 8
  %16 = load i64, i64* %6, align 8
  %17 = icmp ult i64 %15, %16
  br i1 %17, label %18, label %35

18:                                               ; preds = %12
  %19 = load i8, i8* %7, align 1
  %20 = load %struct.mintf_str*, %struct.mintf_str** %5, align 8
  %21 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %20, i32 0, i32 0
  %22 = load i8*, i8** %21, align 8
  %23 = load %struct.mintf_str*, %struct.mintf_str** %5, align 8
  %24 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %23, i32 0, i32 1
  %25 = load i64, i64* %24, align 8
  %26 = add i64 %25, 1
  store i64 %26, i64* %24, align 8
  %27 = getelementptr inbounds i8, i8* %22, i64 %25
  store i8 %19, i8* %27, align 1
  %28 = load %struct.mintf_str*, %struct.mintf_str** %5, align 8
  %29 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %28, i32 0, i32 0
  %30 = load i8*, i8** %29, align 8
  %31 = load %struct.mintf_str*, %struct.mintf_str** %5, align 8
  %32 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %31, i32 0, i32 1
  %33 = load i64, i64* %32, align 8
  %34 = getelementptr inbounds i8, i8* %30, i64 %33
  store i8 0, i8* %34, align 1
  store i32 1, i32* %4, align 4
  br label %36

35:                                               ; preds = %12
  store i32 0, i32* %4, align 4
  br label %36

36:                                               ; preds = %35, %18, %10
  %37 = load i32, i32* %4, align 4
  ret i32 %37
}

declare void @prc(i8 signext) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @mintf(i8* %0, ...) #0 {
  %2 = alloca i8*, align 8
  %3 = alloca [1 x %struct.__va_list_tag], align 16
  %4 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  %5 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i64 0, i64 0
  %6 = bitcast %struct.__va_list_tag* %5 to i8*
  call void @llvm.va_start(i8* %6)
  %7 = load i8*, i8** %2, align 8
  %8 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i64 0, i64 0
  %9 = call i32 @vsnmintf(%struct.mintf_str* null, i64 -1, i8* %7, %struct.__va_list_tag* %8)
  store i32 %9, i32* %4, align 4
  %10 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i64 0, i64 0
  %11 = bitcast %struct.__va_list_tag* %10 to i8*
  call void @llvm.va_end(i8* %11)
  %12 = load i32, i32* %4, align 4
  ret i32 %12
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @vsnmintf(%struct.mintf_str* %0, i64 %1, i8* %2, %struct.__va_list_tag* %3) #0 {
  %5 = alloca i32, align 4
  %6 = alloca %struct.mintf_str*, align 8
  %7 = alloca i64, align 8
  %8 = alloca i8*, align 8
  %9 = alloca %struct.__va_list_tag*, align 8
  %10 = alloca i64, align 8
  %11 = alloca i64, align 8
  %12 = alloca i64, align 8
  %13 = alloca i32, align 4
  %14 = alloca i64, align 8
  %15 = alloca i32, align 4
  %16 = alloca i8, align 1
  %17 = alloca i8, align 1
  %18 = alloca i8*, align 8
  %19 = alloca i32, align 4
  store %struct.mintf_str* %0, %struct.mintf_str** %6, align 8
  store i64 %1, i64* %7, align 8
  store i8* %2, i8** %8, align 8
  store %struct.__va_list_tag* %3, %struct.__va_list_tag** %9, align 8
  %20 = load i8*, i8** %8, align 8
  %21 = call i64 @strlen(i8* %20)
  store i64 %21, i64* %10, align 8
  store i64 0, i64* %11, align 8
  %22 = load i64, i64* %10, align 8
  store i64 %22, i64* %12, align 8
  store i32 0, i32* %13, align 4
  %23 = load i64, i64* %12, align 8
  store i64 0, i64* %14, align 8
  store i32 0, i32* %15, align 4
  br label %24

24:                                               ; preds = %306, %75, %4
  %25 = load i64, i64* %14, align 8
  %26 = load i64, i64* %10, align 8
  %27 = icmp ult i64 %25, %26
  br i1 %27, label %28, label %307

28:                                               ; preds = %24
  %29 = load i32, i32* %13, align 4
  %30 = icmp eq i32 %29, 0
  br i1 %30, label %31, label %56

31:                                               ; preds = %28
  store i32 0, i32* %15, align 4
  %32 = load i8*, i8** %8, align 8
  %33 = load i64, i64* %14, align 8
  %34 = add i64 %33, 1
  store i64 %34, i64* %14, align 8
  %35 = getelementptr inbounds i8, i8* %32, i64 %33
  %36 = load i8, i8* %35, align 1
  store i8 %36, i8* %16, align 1
  %37 = load i8, i8* %16, align 1
  %38 = sext i8 %37 to i32
  %39 = icmp ne i32 %38, 37
  br i1 %39, label %40, label %54

40:                                               ; preds = %31
  br label %41

41:                                               ; preds = %40
  %42 = load %struct.mintf_str*, %struct.mintf_str** %6, align 8
  %43 = load i64, i64* %7, align 8
  %44 = load i8, i8* %16, align 1
  %45 = call i32 @mappend(%struct.mintf_str* %42, i64 %43, i8 signext %44)
  %46 = icmp ne i32 %45, 0
  br i1 %46, label %50, label %47

47:                                               ; preds = %41
  %48 = load i64, i64* %11, align 8
  %49 = trunc i64 %48 to i32
  store i32 %49, i32* %5, align 4
  br label %310

50:                                               ; preds = %41
  %51 = load i64, i64* %11, align 8
  %52 = add i64 %51, 1
  store i64 %52, i64* %11, align 8
  br label %53

53:                                               ; preds = %50
  br label %55

54:                                               ; preds = %31
  store i32 1, i32* %13, align 4
  br label %55

55:                                               ; preds = %54, %53
  br label %306

56:                                               ; preds = %28
  %57 = load i32, i32* %13, align 4
  %58 = icmp eq i32 %57, 1
  br i1 %58, label %59, label %150

59:                                               ; preds = %56
  %60 = load i64, i64* %14, align 8
  %61 = load i64, i64* %10, align 8
  %62 = icmp eq i64 %60, %61
  br i1 %62, label %63, label %66

63:                                               ; preds = %59
  %64 = load i64, i64* %11, align 8
  %65 = trunc i64 %64 to i32
  store i32 %65, i32* %5, align 4
  br label %310

66:                                               ; preds = %59
  %67 = load i8*, i8** %8, align 8
  %68 = load i64, i64* %14, align 8
  %69 = add i64 %68, 1
  store i64 %69, i64* %14, align 8
  %70 = getelementptr inbounds i8, i8* %67, i64 %68
  %71 = load i8, i8* %70, align 1
  store i8 %71, i8* %17, align 1
  %72 = load i8, i8* %17, align 1
  %73 = sext i8 %72 to i32
  %74 = icmp eq i32 %73, 108
  br i1 %74, label %75, label %76

75:                                               ; preds = %66
  store i32 1, i32* %15, align 4
  br label %24

76:                                               ; preds = %66
  %77 = load i8, i8* %17, align 1
  %78 = sext i8 %77 to i32
  %79 = icmp eq i32 %78, 100
  br i1 %79, label %80, label %81

80:                                               ; preds = %76
  store i32 2, i32* %13, align 4
  br label %148

81:                                               ; preds = %76
  %82 = load i8, i8* %17, align 1
  %83 = sext i8 %82 to i32
  %84 = icmp eq i32 %83, 117
  br i1 %84, label %85, label %86

85:                                               ; preds = %81
  store i32 3, i32* %13, align 4
  br label %147

86:                                               ; preds = %81
  %87 = load i8, i8* %17, align 1
  %88 = sext i8 %87 to i32
  %89 = icmp eq i32 %88, 115
  br i1 %89, label %90, label %91

90:                                               ; preds = %86
  store i32 4, i32* %13, align 4
  br label %146

91:                                               ; preds = %86
  %92 = load i8, i8* %17, align 1
  %93 = sext i8 %92 to i32
  %94 = icmp eq i32 %93, 99
  br i1 %94, label %95, label %127

95:                                               ; preds = %91
  br label %96

96:                                               ; preds = %95
  %97 = load %struct.mintf_str*, %struct.mintf_str** %6, align 8
  %98 = load i64, i64* %7, align 8
  %99 = load %struct.__va_list_tag*, %struct.__va_list_tag** %9, align 8
  %100 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %99, i32 0, i32 0
  %101 = load i32, i32* %100, align 8
  %102 = icmp ule i32 %101, 40
  br i1 %102, label %103, label %109

103:                                              ; preds = %96
  %104 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %99, i32 0, i32 3
  %105 = load i8*, i8** %104, align 8
  %106 = getelementptr i8, i8* %105, i32 %101
  %107 = bitcast i8* %106 to i32*
  %108 = add i32 %101, 8
  store i32 %108, i32* %100, align 8
  br label %114

109:                                              ; preds = %96
  %110 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %99, i32 0, i32 2
  %111 = load i8*, i8** %110, align 8
  %112 = bitcast i8* %111 to i32*
  %113 = getelementptr i8, i8* %111, i32 8
  store i8* %113, i8** %110, align 8
  br label %114

114:                                              ; preds = %109, %103
  %115 = phi i32* [ %107, %103 ], [ %112, %109 ]
  %116 = load i32, i32* %115, align 4
  %117 = trunc i32 %116 to i8
  %118 = call i32 @mappend(%struct.mintf_str* %97, i64 %98, i8 signext %117)
  %119 = icmp ne i32 %118, 0
  br i1 %119, label %123, label %120

120:                                              ; preds = %114
  %121 = load i64, i64* %11, align 8
  %122 = trunc i64 %121 to i32
  store i32 %122, i32* %5, align 4
  br label %310

123:                                              ; preds = %114
  %124 = load i64, i64* %11, align 8
  %125 = add i64 %124, 1
  store i64 %125, i64* %11, align 8
  br label %126

126:                                              ; preds = %123
  store i32 0, i32* %13, align 4
  br label %145

127:                                              ; preds = %91
  %128 = load i8, i8* %17, align 1
  %129 = sext i8 %128 to i32
  %130 = icmp eq i32 %129, 37
  br i1 %130, label %131, label %144

131:                                              ; preds = %127
  br label %132

132:                                              ; preds = %131
  %133 = load %struct.mintf_str*, %struct.mintf_str** %6, align 8
  %134 = load i64, i64* %7, align 8
  %135 = call i32 @mappend(%struct.mintf_str* %133, i64 %134, i8 signext 37)
  %136 = icmp ne i32 %135, 0
  br i1 %136, label %140, label %137

137:                                              ; preds = %132
  %138 = load i64, i64* %11, align 8
  %139 = trunc i64 %138 to i32
  store i32 %139, i32* %5, align 4
  br label %310

140:                                              ; preds = %132
  %141 = load i64, i64* %11, align 8
  %142 = add i64 %141, 1
  store i64 %142, i64* %11, align 8
  br label %143

143:                                              ; preds = %140
  store i32 0, i32* %13, align 4
  br label %144

144:                                              ; preds = %143, %127
  br label %145

145:                                              ; preds = %144, %126
  br label %146

146:                                              ; preds = %145, %90
  br label %147

147:                                              ; preds = %146, %85
  br label %148

148:                                              ; preds = %147, %80
  store i32 0, i32* %15, align 4
  br label %149

149:                                              ; preds = %148
  br label %305

150:                                              ; preds = %56
  %151 = load i32, i32* %13, align 4
  %152 = icmp eq i32 %151, 2
  br i1 %152, label %153, label %200

153:                                              ; preds = %150
  %154 = load i32, i32* %15, align 4
  %155 = icmp ne i32 %154, 0
  br i1 %155, label %156, label %177

156:                                              ; preds = %153
  %157 = load %struct.mintf_str*, %struct.mintf_str** %6, align 8
  %158 = load i64, i64* %7, align 8
  %159 = load %struct.__va_list_tag*, %struct.__va_list_tag** %9, align 8
  %160 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %159, i32 0, i32 0
  %161 = load i32, i32* %160, align 8
  %162 = icmp ule i32 %161, 40
  br i1 %162, label %163, label %169

163:                                              ; preds = %156
  %164 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %159, i32 0, i32 3
  %165 = load i8*, i8** %164, align 8
  %166 = getelementptr i8, i8* %165, i32 %161
  %167 = bitcast i8* %166 to i64*
  %168 = add i32 %161, 8
  store i32 %168, i32* %160, align 8
  br label %174

169:                                              ; preds = %156
  %170 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %159, i32 0, i32 2
  %171 = load i8*, i8** %170, align 8
  %172 = bitcast i8* %171 to i64*
  %173 = getelementptr i8, i8* %171, i32 8
  store i8* %173, i8** %170, align 8
  br label %174

174:                                              ; preds = %169, %163
  %175 = phi i64* [ %167, %163 ], [ %172, %169 ]
  %176 = load i64, i64* %175, align 8
  call void @msigned_to_str(%struct.mintf_str* %157, i64 %158, i64 %176)
  br label %199

177:                                              ; preds = %153
  %178 = load %struct.mintf_str*, %struct.mintf_str** %6, align 8
  %179 = load i64, i64* %7, align 8
  %180 = load %struct.__va_list_tag*, %struct.__va_list_tag** %9, align 8
  %181 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %180, i32 0, i32 0
  %182 = load i32, i32* %181, align 8
  %183 = icmp ule i32 %182, 40
  br i1 %183, label %184, label %190

184:                                              ; preds = %177
  %185 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %180, i32 0, i32 3
  %186 = load i8*, i8** %185, align 8
  %187 = getelementptr i8, i8* %186, i32 %182
  %188 = bitcast i8* %187 to i32*
  %189 = add i32 %182, 8
  store i32 %189, i32* %181, align 8
  br label %195

190:                                              ; preds = %177
  %191 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %180, i32 0, i32 2
  %192 = load i8*, i8** %191, align 8
  %193 = bitcast i8* %192 to i32*
  %194 = getelementptr i8, i8* %192, i32 8
  store i8* %194, i8** %191, align 8
  br label %195

195:                                              ; preds = %190, %184
  %196 = phi i32* [ %188, %184 ], [ %193, %190 ]
  %197 = load i32, i32* %196, align 4
  %198 = sext i32 %197 to i64
  call void @msigned_to_str(%struct.mintf_str* %178, i64 %179, i64 %198)
  br label %199

199:                                              ; preds = %195, %174
  store i32 0, i32* %13, align 4
  br label %304

200:                                              ; preds = %150
  %201 = load i32, i32* %13, align 4
  %202 = icmp eq i32 %201, 3
  br i1 %202, label %203, label %250

203:                                              ; preds = %200
  %204 = load i32, i32* %15, align 4
  %205 = icmp ne i32 %204, 0
  br i1 %205, label %206, label %227

206:                                              ; preds = %203
  %207 = load %struct.mintf_str*, %struct.mintf_str** %6, align 8
  %208 = load i64, i64* %7, align 8
  %209 = load %struct.__va_list_tag*, %struct.__va_list_tag** %9, align 8
  %210 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %209, i32 0, i32 0
  %211 = load i32, i32* %210, align 8
  %212 = icmp ule i32 %211, 40
  br i1 %212, label %213, label %219

213:                                              ; preds = %206
  %214 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %209, i32 0, i32 3
  %215 = load i8*, i8** %214, align 8
  %216 = getelementptr i8, i8* %215, i32 %211
  %217 = bitcast i8* %216 to i64*
  %218 = add i32 %211, 8
  store i32 %218, i32* %210, align 8
  br label %224

219:                                              ; preds = %206
  %220 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %209, i32 0, i32 2
  %221 = load i8*, i8** %220, align 8
  %222 = bitcast i8* %221 to i64*
  %223 = getelementptr i8, i8* %221, i32 8
  store i8* %223, i8** %220, align 8
  br label %224

224:                                              ; preds = %219, %213
  %225 = phi i64* [ %217, %213 ], [ %222, %219 ]
  %226 = load i64, i64* %225, align 8
  call void @munsigned_to_str(%struct.mintf_str* %207, i64 %208, i64 %226)
  br label %249

227:                                              ; preds = %203
  %228 = load %struct.mintf_str*, %struct.mintf_str** %6, align 8
  %229 = load i64, i64* %7, align 8
  %230 = load %struct.__va_list_tag*, %struct.__va_list_tag** %9, align 8
  %231 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %230, i32 0, i32 0
  %232 = load i32, i32* %231, align 8
  %233 = icmp ule i32 %232, 40
  br i1 %233, label %234, label %240

234:                                              ; preds = %227
  %235 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %230, i32 0, i32 3
  %236 = load i8*, i8** %235, align 8
  %237 = getelementptr i8, i8* %236, i32 %232
  %238 = bitcast i8* %237 to i32*
  %239 = add i32 %232, 8
  store i32 %239, i32* %231, align 8
  br label %245

240:                                              ; preds = %227
  %241 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %230, i32 0, i32 2
  %242 = load i8*, i8** %241, align 8
  %243 = bitcast i8* %242 to i32*
  %244 = getelementptr i8, i8* %242, i32 8
  store i8* %244, i8** %241, align 8
  br label %245

245:                                              ; preds = %240, %234
  %246 = phi i32* [ %238, %234 ], [ %243, %240 ]
  %247 = load i32, i32* %246, align 4
  %248 = zext i32 %247 to i64
  call void @munsigned_to_str(%struct.mintf_str* %228, i64 %229, i64 %248)
  br label %249

249:                                              ; preds = %245, %224
  store i32 0, i32* %13, align 4
  br label %303

250:                                              ; preds = %200
  %251 = load i32, i32* %13, align 4
  %252 = icmp eq i32 %251, 4
  br i1 %252, label %253, label %301

253:                                              ; preds = %250
  %254 = load %struct.__va_list_tag*, %struct.__va_list_tag** %9, align 8
  %255 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %254, i32 0, i32 0
  %256 = load i32, i32* %255, align 8
  %257 = icmp ule i32 %256, 40
  br i1 %257, label %258, label %264

258:                                              ; preds = %253
  %259 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %254, i32 0, i32 3
  %260 = load i8*, i8** %259, align 8
  %261 = getelementptr i8, i8* %260, i32 %256
  %262 = bitcast i8* %261 to i8**
  %263 = add i32 %256, 8
  store i32 %263, i32* %255, align 8
  br label %269

264:                                              ; preds = %253
  %265 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %254, i32 0, i32 2
  %266 = load i8*, i8** %265, align 8
  %267 = bitcast i8* %266 to i8**
  %268 = getelementptr i8, i8* %266, i32 8
  store i8* %268, i8** %265, align 8
  br label %269

269:                                              ; preds = %264, %258
  %270 = phi i8** [ %262, %258 ], [ %267, %264 ]
  %271 = load i8*, i8** %270, align 8
  store i8* %271, i8** %18, align 8
  store i32 0, i32* %19, align 4
  br label %272

272:                                              ; preds = %297, %269
  %273 = load i8*, i8** %18, align 8
  %274 = load i32, i32* %19, align 4
  %275 = sext i32 %274 to i64
  %276 = getelementptr inbounds i8, i8* %273, i64 %275
  %277 = load i8, i8* %276, align 1
  %278 = icmp ne i8 %277, 0
  br i1 %278, label %279, label %300

279:                                              ; preds = %272
  br label %280

280:                                              ; preds = %279
  %281 = load %struct.mintf_str*, %struct.mintf_str** %6, align 8
  %282 = load i64, i64* %7, align 8
  %283 = load i8*, i8** %18, align 8
  %284 = load i32, i32* %19, align 4
  %285 = sext i32 %284 to i64
  %286 = getelementptr inbounds i8, i8* %283, i64 %285
  %287 = load i8, i8* %286, align 1
  %288 = call i32 @mappend(%struct.mintf_str* %281, i64 %282, i8 signext %287)
  %289 = icmp ne i32 %288, 0
  br i1 %289, label %293, label %290

290:                                              ; preds = %280
  %291 = load i64, i64* %11, align 8
  %292 = trunc i64 %291 to i32
  store i32 %292, i32* %5, align 4
  br label %310

293:                                              ; preds = %280
  %294 = load i64, i64* %11, align 8
  %295 = add i64 %294, 1
  store i64 %295, i64* %11, align 8
  br label %296

296:                                              ; preds = %293
  br label %297

297:                                              ; preds = %296
  %298 = load i32, i32* %19, align 4
  %299 = add nsw i32 %298, 1
  store i32 %299, i32* %19, align 4
  br label %272

300:                                              ; preds = %272
  store i32 0, i32* %13, align 4
  br label %302

301:                                              ; preds = %250
  br label %302

302:                                              ; preds = %301, %300
  br label %303

303:                                              ; preds = %302, %249
  br label %304

304:                                              ; preds = %303, %199
  br label %305

305:                                              ; preds = %304, %149
  br label %306

306:                                              ; preds = %305, %55
  br label %24

307:                                              ; preds = %24
  %308 = load i64, i64* %11, align 8
  %309 = trunc i64 %308 to i32
  store i32 %309, i32* %5, align 4
  br label %310

310:                                              ; preds = %307, %290, %137, %120, %63, %47
  %311 = load i32, i32* %5, align 4
  ret i32 %311
}

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @smintf(i8* %0, i8* %1, ...) #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca [1 x %struct.__va_list_tag], align 16
  %6 = alloca %struct.mintf_str, align 8
  %7 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %8 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  %9 = bitcast %struct.__va_list_tag* %8 to i8*
  call void @llvm.va_start(i8* %9)
  %10 = load i8*, i8** %3, align 8
  %11 = getelementptr inbounds i8, i8* %10, i64 0
  store i8 0, i8* %11, align 1
  %12 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %6, i32 0, i32 0
  %13 = load i8*, i8** %3, align 8
  store i8* %13, i8** %12, align 8
  %14 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %6, i32 0, i32 1
  store i64 0, i64* %14, align 8
  %15 = load i8*, i8** %4, align 8
  %16 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  %17 = call i32 @vsnmintf(%struct.mintf_str* %6, i64 -1, i8* %15, %struct.__va_list_tag* %16)
  store i32 %17, i32* %7, align 4
  %18 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i64 0, i64 0
  %19 = bitcast %struct.__va_list_tag* %18 to i8*
  call void @llvm.va_end(i8* %19)
  %20 = load i32, i32* %7, align 4
  ret i32 %20
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @snmintf(i8* %0, i64 %1, i8* %2, ...) #0 {
  %4 = alloca i8*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i8*, align 8
  %7 = alloca [1 x %struct.__va_list_tag], align 16
  %8 = alloca %struct.mintf_str, align 8
  %9 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  store i64 %1, i64* %5, align 8
  store i8* %2, i8** %6, align 8
  %10 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i64 0, i64 0
  %11 = bitcast %struct.__va_list_tag* %10 to i8*
  call void @llvm.va_start(i8* %11)
  %12 = load i8*, i8** %4, align 8
  %13 = getelementptr inbounds i8, i8* %12, i64 0
  store i8 0, i8* %13, align 1
  %14 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %8, i32 0, i32 0
  %15 = load i8*, i8** %4, align 8
  store i8* %15, i8** %14, align 8
  %16 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %8, i32 0, i32 1
  store i64 0, i64* %16, align 8
  %17 = load i64, i64* %5, align 8
  %18 = load i8*, i8** %6, align 8
  %19 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i64 0, i64 0
  %20 = call i32 @vsnmintf(%struct.mintf_str* %8, i64 %17, i8* %18, %struct.__va_list_tag* %19)
  store i32 %20, i32* %9, align 4
  %21 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i64 0, i64 0
  %22 = bitcast %struct.__va_list_tag* %21 to i8*
  call void @llvm.va_end(i8* %22)
  %23 = load i32, i32* %9, align 4
  ret i32 %23
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @msigned_to_str(%struct.mintf_str* %0, i64 %1, i64 %2) #0 {
  %4 = alloca %struct.mintf_str*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  %7 = alloca [21 x i8], align 16
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  %10 = alloca i32, align 4
  store %struct.mintf_str* %0, %struct.mintf_str** %4, align 8
  store i64 %1, i64* %5, align 8
  store i64 %2, i64* %6, align 8
  %11 = load i64, i64* %6, align 8
  %12 = icmp eq i64 %11, 0
  br i1 %12, label %13, label %17

13:                                               ; preds = %3
  %14 = load %struct.mintf_str*, %struct.mintf_str** %4, align 8
  %15 = load i64, i64* %5, align 8
  %16 = call i32 @mappend(%struct.mintf_str* %14, i64 %15, i8 signext 48)
  br label %71

17:                                               ; preds = %3
  %18 = bitcast [21 x i8]* %7 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %18, i8 0, i64 21, i1 false)
  store i32 0, i32* %8, align 4
  %19 = load i64, i64* %6, align 8
  %20 = icmp slt i64 %19, 0
  %21 = zext i1 %20 to i32
  store i32 %21, i32* %9, align 4
  %22 = load i32, i32* %9, align 4
  %23 = icmp ne i32 %22, 0
  br i1 %23, label %24, label %27

24:                                               ; preds = %17
  %25 = load i64, i64* %6, align 8
  %26 = sub nsw i64 0, %25
  store i64 %26, i64* %6, align 8
  br label %27

27:                                               ; preds = %24, %17
  br label %28

28:                                               ; preds = %31, %27
  %29 = load i64, i64* %6, align 8
  %30 = icmp slt i64 0, %29
  br i1 %30, label %31, label %42

31:                                               ; preds = %28
  %32 = load i64, i64* %6, align 8
  %33 = srem i64 %32, 10
  %34 = add nsw i64 48, %33
  %35 = trunc i64 %34 to i8
  %36 = load i32, i32* %8, align 4
  %37 = add nsw i32 %36, 1
  store i32 %37, i32* %8, align 4
  %38 = sext i32 %36 to i64
  %39 = getelementptr inbounds [21 x i8], [21 x i8]* %7, i64 0, i64 %38
  store i8 %35, i8* %39, align 1
  %40 = load i64, i64* %6, align 8
  %41 = sdiv i64 %40, 10
  store i64 %41, i64* %6, align 8
  br label %28

42:                                               ; preds = %28
  %43 = load i32, i32* %9, align 4
  %44 = icmp ne i32 %43, 0
  br i1 %44, label %45, label %51

45:                                               ; preds = %42
  %46 = load %struct.mintf_str*, %struct.mintf_str** %4, align 8
  %47 = load i64, i64* %5, align 8
  %48 = call i32 @mappend(%struct.mintf_str* %46, i64 %47, i8 signext 45)
  %49 = icmp ne i32 %48, 0
  br i1 %49, label %51, label %50

50:                                               ; preds = %45
  br label %71

51:                                               ; preds = %45, %42
  %52 = load i32, i32* %8, align 4
  %53 = sub nsw i32 %52, 1
  store i32 %53, i32* %10, align 4
  br label %54

54:                                               ; preds = %68, %51
  %55 = load i32, i32* %10, align 4
  %56 = icmp sle i32 0, %55
  br i1 %56, label %57, label %71

57:                                               ; preds = %54
  %58 = load %struct.mintf_str*, %struct.mintf_str** %4, align 8
  %59 = load i64, i64* %5, align 8
  %60 = load i32, i32* %10, align 4
  %61 = sext i32 %60 to i64
  %62 = getelementptr inbounds [21 x i8], [21 x i8]* %7, i64 0, i64 %61
  %63 = load i8, i8* %62, align 1
  %64 = call i32 @mappend(%struct.mintf_str* %58, i64 %59, i8 signext %63)
  %65 = icmp ne i32 %64, 0
  br i1 %65, label %67, label %66

66:                                               ; preds = %57
  br label %71

67:                                               ; preds = %57
  br label %68

68:                                               ; preds = %67
  %69 = load i32, i32* %10, align 4
  %70 = add nsw i32 %69, -1
  store i32 %70, i32* %10, align 4
  br label %54

71:                                               ; preds = %13, %50, %66, %54
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @munsigned_to_str(%struct.mintf_str* %0, i64 %1, i64 %2) #0 {
  %4 = alloca %struct.mintf_str*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  %7 = alloca [20 x i8], align 16
  %8 = alloca i32, align 4
  %9 = alloca i32, align 4
  store %struct.mintf_str* %0, %struct.mintf_str** %4, align 8
  store i64 %1, i64* %5, align 8
  store i64 %2, i64* %6, align 8
  %10 = load i64, i64* %6, align 8
  %11 = icmp eq i64 %10, 0
  br i1 %11, label %12, label %16

12:                                               ; preds = %3
  %13 = load %struct.mintf_str*, %struct.mintf_str** %4, align 8
  %14 = load i64, i64* %5, align 8
  %15 = call i32 @mappend(%struct.mintf_str* %13, i64 %14, i8 signext 48)
  br label %52

16:                                               ; preds = %3
  %17 = bitcast [20 x i8]* %7 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 16 %17, i8 0, i64 20, i1 false)
  store i32 0, i32* %8, align 4
  br label %18

18:                                               ; preds = %21, %16
  %19 = load i64, i64* %6, align 8
  %20 = icmp ult i64 0, %19
  br i1 %20, label %21, label %32

21:                                               ; preds = %18
  %22 = load i64, i64* %6, align 8
  %23 = urem i64 %22, 10
  %24 = add i64 48, %23
  %25 = trunc i64 %24 to i8
  %26 = load i32, i32* %8, align 4
  %27 = add nsw i32 %26, 1
  store i32 %27, i32* %8, align 4
  %28 = sext i32 %26 to i64
  %29 = getelementptr inbounds [20 x i8], [20 x i8]* %7, i64 0, i64 %28
  store i8 %25, i8* %29, align 1
  %30 = load i64, i64* %6, align 8
  %31 = udiv i64 %30, 10
  store i64 %31, i64* %6, align 8
  br label %18

32:                                               ; preds = %18
  %33 = load i32, i32* %8, align 4
  %34 = sub nsw i32 %33, 1
  store i32 %34, i32* %9, align 4
  br label %35

35:                                               ; preds = %49, %32
  %36 = load i32, i32* %9, align 4
  %37 = icmp sle i32 0, %36
  br i1 %37, label %38, label %52

38:                                               ; preds = %35
  %39 = load %struct.mintf_str*, %struct.mintf_str** %4, align 8
  %40 = load i64, i64* %5, align 8
  %41 = load i32, i32* %9, align 4
  %42 = sext i32 %41 to i64
  %43 = getelementptr inbounds [20 x i8], [20 x i8]* %7, i64 0, i64 %42
  %44 = load i8, i8* %43, align 1
  %45 = call i32 @mappend(%struct.mintf_str* %39, i64 %40, i8 signext %44)
  %46 = icmp ne i32 %45, 0
  br i1 %46, label %48, label %47

47:                                               ; preds = %38
  br label %52

48:                                               ; preds = %38
  br label %49

49:                                               ; preds = %48
  %50 = load i32, i32* %9, align 4
  %51 = add nsw i32 %50, -1
  store i32 %51, i32* %9, align 4
  br label %35

52:                                               ; preds = %12, %47, %35
  ret void
}

; Function Attrs: argmemonly nounwind willreturn
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1 immarg) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @main(i32 %0, i8** %1) #0 {
  %3 = alloca i32, align 4
  %4 = alloca i8**, align 8
  store i32 %0, i32* %3, align 4
  store i8** %1, i8*** %4, align 8
  %5 = load i32, i32* %3, align 4
  %6 = load i8**, i8*** %4, align 8
  %7 = call i32 (i8*, ...) @mintf(i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str, i64 0, i64 0))
  call void @test_signed(i64 -690)
  call void @test_signed(i64 0)
  call void @test_signed(i64 1)
  call void @test_signed(i64 12)
  call void @test_signed(i64 -6)
  call void @test_signed(i64 9223372036854775807)
  call void @test_signed(i64 -9223372036854775807)
  call void @test_unsigned(i64 0)
  call void @test_unsigned(i64 1)
  call void @test_unsigned(i64 20)
  call void @test_unsigned(i64 35)
  call void @test_unsigned(i64 -1)
  %8 = call i32 (i8*, ...) @mintf(i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.1, i64 0, i64 0))
  call void @test_mintf()
  ret i32 0
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @test_signed(i64 %0) #0 {
  %2 = alloca i64, align 8
  %3 = alloca [9999 x i8], align 16
  %4 = alloca %struct.mintf_str, align 8
  store i64 %0, i64* %2, align 8
  %5 = getelementptr inbounds [9999 x i8], [9999 x i8]* %3, i64 0, i64 0
  store i8 0, i8* %5, align 16
  %6 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %4, i32 0, i32 0
  %7 = getelementptr inbounds [9999 x i8], [9999 x i8]* %3, i64 0, i64 0
  store i8* %7, i8** %6, align 8
  %8 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %4, i32 0, i32 1
  store i64 0, i64* %8, align 8
  %9 = load i64, i64* %2, align 8
  call void @msigned_to_str(%struct.mintf_str* %4, i64 -1, i64 %9)
  %10 = load i64, i64* %2, align 8
  %11 = getelementptr inbounds [9999 x i8], [9999 x i8]* %3, i64 0, i64 0
  %12 = call i32 (i8*, ...) @mintf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.2, i64 0, i64 0), i64 %10, i8* %11)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @test_unsigned(i64 %0) #0 {
  %2 = alloca i64, align 8
  %3 = alloca [9999 x i8], align 16
  %4 = alloca %struct.mintf_str, align 8
  store i64 %0, i64* %2, align 8
  %5 = getelementptr inbounds [9999 x i8], [9999 x i8]* %3, i64 0, i64 0
  store i8 0, i8* %5, align 16
  %6 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %4, i32 0, i32 0
  %7 = getelementptr inbounds [9999 x i8], [9999 x i8]* %3, i64 0, i64 0
  store i8* %7, i8** %6, align 8
  %8 = getelementptr inbounds %struct.mintf_str, %struct.mintf_str* %4, i32 0, i32 1
  store i64 0, i64* %8, align 8
  %9 = load i64, i64* %2, align 8
  call void @munsigned_to_str(%struct.mintf_str* %4, i64 -1, i64 %9)
  %10 = load i64, i64* %2, align 8
  %11 = getelementptr inbounds [9999 x i8], [9999 x i8]* %3, i64 0, i64 0
  %12 = call i32 (i8*, ...) @mintf(i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.3, i64 0, i64 0), i64 %10, i8* %11)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define void @test_mintf() #0 {
  %1 = alloca i32, align 4
  %2 = call i32 (i8*, ...) @mintf(i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.4, i64 0, i64 0), i32 -42, i64 -42, i32 -42, i64 -42, i32 36, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.5, i64 0, i64 0), i32 -1)
  store i32 %2, i32* %1, align 4
  %3 = load i32, i32* %1, align 4
  %4 = call i32 (i8*, ...) @mintf(i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.6, i64 0, i64 0), i32 %3)
  ret void
}

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "frame-pointer"="all" "less-precise-fpmad"="false" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+cx8,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind }
attributes #3 = { argmemonly nounwind willreturn }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 10.0.0 "}
