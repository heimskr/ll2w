;/////////////////////////////////////////////////////////////////////////////
;  \author (c) Marco Paland (info@paland.com)
;              2014-2019, PALANDesign Hannover, Germany
; 
;  \license The MIT License (MIT)
; 
;  Permission is hereby granted, free of charge, to any person obtaining a copy
;  of this software and associated documentation files (the "Software"), to deal
;  in the Software without restriction, including without limitation the rights
;  to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
;  copies of the Software, and to permit persons to whom the Software is
;  furnished to do so, subject to the following conditions:
; 
;  The above copyright notice and this permission notice shall be included in
;  all copies or substantial portions of the Software.
; 
;  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
;  IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
;  FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
;  AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
;  LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
;  OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
;  THE SOFTWARE.
; 
;  \brief Tiny printf, sprintf and (v)snprintf implementation, optimized for speed on
;         embedded systems with a very limited resources. These routines are thread
;         safe and reentrant!
;         Use this instead of the bloated standard/newlib printf cause these use
;         malloc for printf (and may not be thread safe).
; 
;/////////////////////////////////////////////////////////////////////////////

; ModuleID = 'printf.ll'
source_filename = "printf.c"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%struct.__va_list_tag = type { i32, i32, i8*, i8* }
%struct.out_fct_wrap_type = type { void (i8, i8*)*, i8* }

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @printf_(i8*, ...) local_unnamed_addr #0 {
  %2 = alloca i8*, align 8
  %3 = alloca [1 x %struct.__va_list_tag], align 16
  %4 = alloca [1 x i8], align 1
  %5 = alloca i32, align 4
  store i8* %0, i8** %2, align 8
  %6 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i32 0, i32 0
  %7 = bitcast %struct.__va_list_tag* %6 to i8*
  call void @llvm.va_start(i8* %7)
  %8 = getelementptr inbounds [1 x i8], [1 x i8]* %4, i32 0, i32 0
  %9 = load i8*, i8** %2, align 8
  %10 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i32 0, i32 0
  %11 = call fastcc i32 @_vsnprintf(void (i8, i8*, i64, i64)* @_out_char, i8* %8, i64 -1, i8* %9, %struct.__va_list_tag* %10)
  store i32 %11, i32* %5, align 4
  %12 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %3, i32 0, i32 0
  %13 = bitcast %struct.__va_list_tag* %12 to i8*
  call void @llvm.va_end(i8* %13)
  %14 = load i32, i32* %5, align 4
  ret i32 %14
}

; Function Attrs: nounwind
declare void @llvm.va_start(i8*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal fastcc i32 @_vsnprintf(void (i8, i8*, i64, i64)*, i8*, i64, i8*, %struct.__va_list_tag*) unnamed_addr #0 {
  %6 = alloca void (i8, i8*, i64, i64)*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i64, align 8
  %9 = alloca i8*, align 8
  %10 = alloca %struct.__va_list_tag*, align 8
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i32, align 4
  %14 = alloca i32, align 4
  %15 = alloca i64, align 8
  %16 = alloca i32, align 4
  %17 = alloca i32, align 4
  %18 = alloca i32, align 4
  %19 = alloca i64, align 8
  %20 = alloca i64, align 8
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  %23 = alloca i32, align 4
  %24 = alloca i8*, align 8
  %25 = alloca i32, align 4
  %26 = alloca i8, align 1
  store void (i8, i8*, i64, i64)* %0, void (i8, i8*, i64, i64)** %6, align 8
  store i8* %1, i8** %7, align 8
  store i64 %2, i64* %8, align 8
  store i8* %3, i8** %9, align 8
  store %struct.__va_list_tag* %4, %struct.__va_list_tag** %10, align 8
  store i64 0, i64* %15, align 8
  %27 = load i8*, i8** %7, align 8
  %28 = icmp ne i8* %27, null
  br i1 %28, label %30, label %29

; <label>:29:                                     ; preds = %5
  store void (i8, i8*, i64, i64)* @_out_null, void (i8, i8*, i64, i64)** %6, align 8
  br label %30

; <label>:30:                                     ; preds = %29, %5
  br label %31

; <label>:31:                                     ; preds = %.backedge, %30
  %32 = load i8*, i8** %9, align 8
  %33 = load i8, i8* %32, align 1
  %34 = icmp ne i8 %33, 0
  br i1 %34, label %35, label %860

; <label>:35:                                     ; preds = %31
  %36 = load i8*, i8** %9, align 8
  %37 = load i8, i8* %36, align 1
  %38 = sext i8 %37 to i32
  %39 = icmp ne i32 %38, 37
  br i1 %39, label %40, label %50

; <label>:40:                                     ; preds = %35
  %41 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %42 = load i8*, i8** %9, align 8
  %43 = load i8, i8* %42, align 1
  %44 = load i8*, i8** %7, align 8
  %45 = load i64, i64* %15, align 8
  %46 = add i64 %45, 1
  store i64 %46, i64* %15, align 8
  %47 = load i64, i64* %8, align 8
  call void %41(i8 signext %43, i8* %44, i64 %45, i64 %47)
  %48 = load i8*, i8** %9, align 8
  %49 = getelementptr inbounds i8, i8* %48, i32 1
  store i8* %49, i8** %9, align 8
  br label %.backedge

.backedge:                                        ; preds = %40, %859
  br label %31

; <label>:50:                                     ; preds = %35
  %51 = load i8*, i8** %9, align 8
  %52 = getelementptr inbounds i8, i8* %51, i32 1
  store i8* %52, i8** %9, align 8
  br label %53

; <label>:53:                                     ; preds = %50
  store i32 0, i32* %11, align 4
  br label %54

; <label>:54:                                     ; preds = %85, %53
  %55 = load i8*, i8** %9, align 8
  %56 = load i8, i8* %55, align 1
  %57 = sext i8 %56 to i32
  switch i32 %57, label %83 [
    i32 48, label %58
    i32 45, label %63
    i32 43, label %68
    i32 32, label %73
    i32 35, label %78
  ]

; <label>:58:                                     ; preds = %54
  %59 = load i32, i32* %11, align 4
  %60 = or i32 %59, 1
  store i32 %60, i32* %11, align 4
  %61 = load i8*, i8** %9, align 8
  %62 = getelementptr inbounds i8, i8* %61, i32 1
  store i8* %62, i8** %9, align 8
  store i32 1, i32* %14, align 4
  br label %84

; <label>:63:                                     ; preds = %54
  %64 = load i32, i32* %11, align 4
  %65 = or i32 %64, 2
  store i32 %65, i32* %11, align 4
  %66 = load i8*, i8** %9, align 8
  %67 = getelementptr inbounds i8, i8* %66, i32 1
  store i8* %67, i8** %9, align 8
  store i32 1, i32* %14, align 4
  br label %84

; <label>:68:                                     ; preds = %54
  %69 = load i32, i32* %11, align 4
  %70 = or i32 %69, 4
  store i32 %70, i32* %11, align 4
  %71 = load i8*, i8** %9, align 8
  %72 = getelementptr inbounds i8, i8* %71, i32 1
  store i8* %72, i8** %9, align 8
  store i32 1, i32* %14, align 4
  br label %84

; <label>:73:                                     ; preds = %54
  %74 = load i32, i32* %11, align 4
  %75 = or i32 %74, 8
  store i32 %75, i32* %11, align 4
  %76 = load i8*, i8** %9, align 8
  %77 = getelementptr inbounds i8, i8* %76, i32 1
  store i8* %77, i8** %9, align 8
  store i32 1, i32* %14, align 4
  br label %84

; <label>:78:                                     ; preds = %54
  %79 = load i32, i32* %11, align 4
  %80 = or i32 %79, 16
  store i32 %80, i32* %11, align 4
  %81 = load i8*, i8** %9, align 8
  %82 = getelementptr inbounds i8, i8* %81, i32 1
  store i8* %82, i8** %9, align 8
  store i32 1, i32* %14, align 4
  br label %84

; <label>:83:                                     ; preds = %54
  store i32 0, i32* %14, align 4
  br label %84

; <label>:84:                                     ; preds = %83, %78, %73, %68, %63, %58
  br label %85

; <label>:85:                                     ; preds = %84
  %86 = load i32, i32* %14, align 4
  %87 = icmp ne i32 %86, 0
  br i1 %87, label %54, label %88

; <label>:88:                                     ; preds = %85
  store i32 0, i32* %12, align 4
  %89 = load i8*, i8** %9, align 8
  %90 = load i8, i8* %89, align 1
  %91 = call fastcc zeroext i1 @_is_digit(i8 signext %90)
  br i1 %91, label %92, label %94

; <label>:92:                                     ; preds = %88
  %93 = call fastcc i32 @_atoi(i8** %9)
  store i32 %93, i32* %12, align 4
  br label %131

; <label>:94:                                     ; preds = %88
  %95 = load i8*, i8** %9, align 8
  %96 = load i8, i8* %95, align 1
  %97 = sext i8 %96 to i32
  %98 = icmp eq i32 %97, 42
  br i1 %98, label %99, label %130

; <label>:99:                                     ; preds = %94
  %100 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %101 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %100, i32 0, i32 0
  %102 = load i32, i32* %101, align 8
  %103 = icmp ule i32 %102, 40
  br i1 %103, label %104, label %110

; <label>:104:                                    ; preds = %99
  %105 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %100, i32 0, i32 3
  %106 = load i8*, i8** %105, align 8
  %107 = getelementptr i8, i8* %106, i32 %102
  %108 = bitcast i8* %107 to i32*
  %109 = add i32 %102, 8
  store i32 %109, i32* %101, align 8
  br label %115

; <label>:110:                                    ; preds = %99
  %111 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %100, i32 0, i32 2
  %112 = load i8*, i8** %111, align 8
  %113 = bitcast i8* %112 to i32*
  %114 = getelementptr i8, i8* %112, i32 8
  store i8* %114, i8** %111, align 8
  br label %115

; <label>:115:                                    ; preds = %110, %104
  %116 = phi i32* [ %108, %104 ], [ %113, %110 ]
  %117 = load i32, i32* %116, align 4
  store i32 %117, i32* %16, align 4
  %118 = load i32, i32* %16, align 4
  %119 = icmp slt i32 %118, 0
  br i1 %119, label %120, label %125

; <label>:120:                                    ; preds = %115
  %121 = load i32, i32* %11, align 4
  %122 = or i32 %121, 2
  store i32 %122, i32* %11, align 4
  %123 = load i32, i32* %16, align 4
  %124 = sub nsw i32 0, %123
  store i32 %124, i32* %12, align 4
  br label %127

; <label>:125:                                    ; preds = %115
  %126 = load i32, i32* %16, align 4
  store i32 %126, i32* %12, align 4
  br label %127

; <label>:127:                                    ; preds = %125, %120
  %128 = load i8*, i8** %9, align 8
  %129 = getelementptr inbounds i8, i8* %128, i32 1
  store i8* %129, i8** %9, align 8
  br label %130

; <label>:130:                                    ; preds = %127, %94
  br label %131

; <label>:131:                                    ; preds = %130, %92
  store i32 0, i32* %13, align 4
  %132 = load i8*, i8** %9, align 8
  %133 = load i8, i8* %132, align 1
  %134 = sext i8 %133 to i32
  %135 = icmp eq i32 %134, 46
  br i1 %135, label %136, label %181

; <label>:136:                                    ; preds = %131
  %137 = load i32, i32* %11, align 4
  %138 = or i32 %137, 1024
  store i32 %138, i32* %11, align 4
  %139 = load i8*, i8** %9, align 8
  %140 = getelementptr inbounds i8, i8* %139, i32 1
  store i8* %140, i8** %9, align 8
  %141 = load i8*, i8** %9, align 8
  %142 = load i8, i8* %141, align 1
  %143 = call fastcc zeroext i1 @_is_digit(i8 signext %142)
  br i1 %143, label %144, label %146

; <label>:144:                                    ; preds = %136
  %145 = call fastcc i32 @_atoi(i8** %9)
  store i32 %145, i32* %13, align 4
  br label %180

; <label>:146:                                    ; preds = %136
  %147 = load i8*, i8** %9, align 8
  %148 = load i8, i8* %147, align 1
  %149 = sext i8 %148 to i32
  %150 = icmp eq i32 %149, 42
  br i1 %150, label %151, label %179

; <label>:151:                                    ; preds = %146
  %152 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %153 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %152, i32 0, i32 0
  %154 = load i32, i32* %153, align 8
  %155 = icmp ule i32 %154, 40
  br i1 %155, label %156, label %162

; <label>:156:                                    ; preds = %151
  %157 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %152, i32 0, i32 3
  %158 = load i8*, i8** %157, align 8
  %159 = getelementptr i8, i8* %158, i32 %154
  %160 = bitcast i8* %159 to i32*
  %161 = add i32 %154, 8
  store i32 %161, i32* %153, align 8
  br label %167

; <label>:162:                                    ; preds = %151
  %163 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %152, i32 0, i32 2
  %164 = load i8*, i8** %163, align 8
  %165 = bitcast i8* %164 to i32*
  %166 = getelementptr i8, i8* %164, i32 8
  store i8* %166, i8** %163, align 8
  br label %167

; <label>:167:                                    ; preds = %162, %156
  %168 = phi i32* [ %160, %156 ], [ %165, %162 ]
  %169 = load i32, i32* %168, align 4
  store i32 %169, i32* %17, align 4
  %170 = load i32, i32* %17, align 4
  %171 = icmp sgt i32 %170, 0
  br i1 %171, label %172, label %174

; <label>:172:                                    ; preds = %167
  %173 = load i32, i32* %17, align 4
  br label %175

; <label>:174:                                    ; preds = %167
  br label %175

; <label>:175:                                    ; preds = %174, %172
  %176 = phi i32 [ %173, %172 ], [ 0, %174 ]
  store i32 %176, i32* %13, align 4
  %177 = load i8*, i8** %9, align 8
  %178 = getelementptr inbounds i8, i8* %177, i32 1
  store i8* %178, i8** %9, align 8
  br label %179

; <label>:179:                                    ; preds = %175, %146
  br label %180

; <label>:180:                                    ; preds = %179, %144
  br label %181

; <label>:181:                                    ; preds = %180, %131
  %182 = load i8*, i8** %9, align 8
  %183 = load i8, i8* %182, align 1
  %184 = sext i8 %183 to i32
  switch i32 %184, label %230 [
    i32 108, label %185
    i32 104, label %200
    i32 116, label %215
    i32 106, label %220
    i32 122, label %225
  ]

; <label>:185:                                    ; preds = %181
  %186 = load i32, i32* %11, align 4
  %187 = or i32 %186, 256
  store i32 %187, i32* %11, align 4
  %188 = load i8*, i8** %9, align 8
  %189 = getelementptr inbounds i8, i8* %188, i32 1
  store i8* %189, i8** %9, align 8
  %190 = load i8*, i8** %9, align 8
  %191 = load i8, i8* %190, align 1
  %192 = sext i8 %191 to i32
  %193 = icmp eq i32 %192, 108
  br i1 %193, label %194, label %199

; <label>:194:                                    ; preds = %185
  %195 = load i32, i32* %11, align 4
  %196 = or i32 %195, 512
  store i32 %196, i32* %11, align 4
  %197 = load i8*, i8** %9, align 8
  %198 = getelementptr inbounds i8, i8* %197, i32 1
  store i8* %198, i8** %9, align 8
  br label %199

; <label>:199:                                    ; preds = %194, %185
  br label %231

; <label>:200:                                    ; preds = %181
  %201 = load i32, i32* %11, align 4
  %202 = or i32 %201, 128
  store i32 %202, i32* %11, align 4
  %203 = load i8*, i8** %9, align 8
  %204 = getelementptr inbounds i8, i8* %203, i32 1
  store i8* %204, i8** %9, align 8
  %205 = load i8*, i8** %9, align 8
  %206 = load i8, i8* %205, align 1
  %207 = sext i8 %206 to i32
  %208 = icmp eq i32 %207, 104
  br i1 %208, label %209, label %214

; <label>:209:                                    ; preds = %200
  %210 = load i32, i32* %11, align 4
  %211 = or i32 %210, 64
  store i32 %211, i32* %11, align 4
  %212 = load i8*, i8** %9, align 8
  %213 = getelementptr inbounds i8, i8* %212, i32 1
  store i8* %213, i8** %9, align 8
  br label %214

; <label>:214:                                    ; preds = %209, %200
  br label %231

; <label>:215:                                    ; preds = %181
  %216 = load i32, i32* %11, align 4
  %217 = or i32 %216, 256
  store i32 %217, i32* %11, align 4
  %218 = load i8*, i8** %9, align 8
  %219 = getelementptr inbounds i8, i8* %218, i32 1
  store i8* %219, i8** %9, align 8
  br label %231

; <label>:220:                                    ; preds = %181
  %221 = load i32, i32* %11, align 4
  %222 = or i32 %221, 256
  store i32 %222, i32* %11, align 4
  %223 = load i8*, i8** %9, align 8
  %224 = getelementptr inbounds i8, i8* %223, i32 1
  store i8* %224, i8** %9, align 8
  br label %231

; <label>:225:                                    ; preds = %181
  %226 = load i32, i32* %11, align 4
  %227 = or i32 %226, 256
  store i32 %227, i32* %11, align 4
  %228 = load i8*, i8** %9, align 8
  %229 = getelementptr inbounds i8, i8* %228, i32 1
  store i8* %229, i8** %9, align 8
  br label %231

; <label>:230:                                    ; preds = %181
  br label %231

; <label>:231:                                    ; preds = %230, %225, %220, %215, %214, %199
  %232 = load i8*, i8** %9, align 8
  %233 = load i8, i8* %232, align 1
  %234 = sext i8 %233 to i32
  switch i32 %234, label %849 [
    i32 100, label %235
    i32 105, label %235
    i32 117, label %235
    i32 120, label %235
    i32 88, label %235
    i32 111, label %235
    i32 98, label %235
    i32 99, label %642
    i32 115, label %703
    i32 112, label %809
    i32 37, label %841
  ]

; <label>:235:                                    ; preds = %231, %231, %231, %231, %231, %231, %231
  %236 = load i8*, i8** %9, align 8
  %237 = load i8, i8* %236, align 1
  %238 = sext i8 %237 to i32
  %239 = icmp eq i32 %238, 120
  br i1 %239, label %245, label %240

; <label>:240:                                    ; preds = %235
  %241 = load i8*, i8** %9, align 8
  %242 = load i8, i8* %241, align 1
  %243 = sext i8 %242 to i32
  %244 = icmp eq i32 %243, 88
  br i1 %244, label %245, label %246

; <label>:245:                                    ; preds = %240, %235
  store i32 16, i32* %18, align 4
  br label %263

; <label>:246:                                    ; preds = %240
  %247 = load i8*, i8** %9, align 8
  %248 = load i8, i8* %247, align 1
  %249 = sext i8 %248 to i32
  %250 = icmp eq i32 %249, 111
  br i1 %250, label %251, label %252

; <label>:251:                                    ; preds = %246
  store i32 8, i32* %18, align 4
  br label %262

; <label>:252:                                    ; preds = %246
  %253 = load i8*, i8** %9, align 8
  %254 = load i8, i8* %253, align 1
  %255 = sext i8 %254 to i32
  %256 = icmp eq i32 %255, 98
  br i1 %256, label %257, label %258

; <label>:257:                                    ; preds = %252
  store i32 2, i32* %18, align 4
  br label %261

; <label>:258:                                    ; preds = %252
  store i32 10, i32* %18, align 4
  %259 = load i32, i32* %11, align 4
  %260 = and i32 %259, -17
  store i32 %260, i32* %11, align 4
  br label %261

; <label>:261:                                    ; preds = %258, %257
  br label %262

; <label>:262:                                    ; preds = %261, %251
  br label %263

; <label>:263:                                    ; preds = %262, %245
  %264 = load i8*, i8** %9, align 8
  %265 = load i8, i8* %264, align 1
  %266 = sext i8 %265 to i32
  %267 = icmp eq i32 %266, 88
  br i1 %267, label %268, label %271

; <label>:268:                                    ; preds = %263
  %269 = load i32, i32* %11, align 4
  %270 = or i32 %269, 32
  store i32 %270, i32* %11, align 4
  br label %271

; <label>:271:                                    ; preds = %268, %263
  %272 = load i8*, i8** %9, align 8
  %273 = load i8, i8* %272, align 1
  %274 = sext i8 %273 to i32
  %275 = icmp ne i32 %274, 105
  br i1 %275, label %276, label %284

; <label>:276:                                    ; preds = %271
  %277 = load i8*, i8** %9, align 8
  %278 = load i8, i8* %277, align 1
  %279 = sext i8 %278 to i32
  %280 = icmp ne i32 %279, 100
  br i1 %280, label %281, label %284

; <label>:281:                                    ; preds = %276
  %282 = load i32, i32* %11, align 4
  %283 = and i32 %282, -13
  store i32 %283, i32* %11, align 4
  br label %284

; <label>:284:                                    ; preds = %281, %276, %271
  %285 = load i32, i32* %11, align 4
  %286 = and i32 %285, 1024
  %287 = icmp ne i32 %286, 0
  br i1 %287, label %288, label %291

; <label>:288:                                    ; preds = %284
  %289 = load i32, i32* %11, align 4
  %290 = and i32 %289, -2
  store i32 %290, i32* %11, align 4
  br label %291

; <label>:291:                                    ; preds = %288, %284
  %292 = load i8*, i8** %9, align 8
  %293 = load i8, i8* %292, align 1
  %294 = sext i8 %293 to i32
  %295 = icmp eq i32 %294, 105
  br i1 %295, label %301, label %296

; <label>:296:                                    ; preds = %291
  %297 = load i8*, i8** %9, align 8
  %298 = load i8, i8* %297, align 1
  %299 = sext i8 %298 to i32
  %300 = icmp eq i32 %299, 100
  br i1 %300, label %301, label %486

; <label>:301:                                    ; preds = %296, %291
  %302 = load i32, i32* %11, align 4
  %303 = and i32 %302, 512
  %304 = icmp ne i32 %303, 0
  br i1 %304, label %305, label %345

; <label>:305:                                    ; preds = %301
  %306 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %307 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %306, i32 0, i32 0
  %308 = load i32, i32* %307, align 8
  %309 = icmp ule i32 %308, 40
  br i1 %309, label %310, label %316

; <label>:310:                                    ; preds = %305
  %311 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %306, i32 0, i32 3
  %312 = load i8*, i8** %311, align 8
  %313 = getelementptr i8, i8* %312, i32 %308
  %314 = bitcast i8* %313 to i64*
  %315 = add i32 %308, 8
  store i32 %315, i32* %307, align 8
  br label %321

; <label>:316:                                    ; preds = %305
  %317 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %306, i32 0, i32 2
  %318 = load i8*, i8** %317, align 8
  %319 = bitcast i8* %318 to i64*
  %320 = getelementptr i8, i8* %318, i32 8
  store i8* %320, i8** %317, align 8
  br label %321

; <label>:321:                                    ; preds = %316, %310
  %322 = phi i64* [ %314, %310 ], [ %319, %316 ]
  %323 = load i64, i64* %322, align 8
  store i64 %323, i64* %19, align 8
  %324 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %325 = load i8*, i8** %7, align 8
  %326 = load i64, i64* %15, align 8
  %327 = load i64, i64* %8, align 8
  %328 = load i64, i64* %19, align 8
  %329 = icmp sgt i64 %328, 0
  br i1 %329, label %330, label %332

; <label>:330:                                    ; preds = %321
  %331 = load i64, i64* %19, align 8
  br label %335

; <label>:332:                                    ; preds = %321
  %333 = load i64, i64* %19, align 8
  %334 = sub nsw i64 0, %333
  br label %335

; <label>:335:                                    ; preds = %332, %330
  %336 = phi i64 [ %331, %330 ], [ %334, %332 ]
  %337 = load i64, i64* %19, align 8
  %338 = icmp slt i64 %337, 0
  %339 = load i32, i32* %18, align 4
  %340 = zext i32 %339 to i64
  %341 = load i32, i32* %13, align 4
  %342 = load i32, i32* %12, align 4
  %343 = load i32, i32* %11, align 4
  %344 = call fastcc i64 @_ntoa_long_long(void (i8, i8*, i64, i64)* %324, i8* %325, i64 %326, i64 %327, i64 %336, i1 zeroext %338, i64 %340, i32 %341, i32 %342, i32 %343)
  store i64 %344, i64* %15, align 8
  br label %485

; <label>:345:                                    ; preds = %301
  %346 = load i32, i32* %11, align 4
  %347 = and i32 %346, 256
  %348 = icmp ne i32 %347, 0
  br i1 %348, label %349, label %389

; <label>:349:                                    ; preds = %345
  %350 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %351 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %350, i32 0, i32 0
  %352 = load i32, i32* %351, align 8
  %353 = icmp ule i32 %352, 40
  br i1 %353, label %354, label %360

; <label>:354:                                    ; preds = %349
  %355 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %350, i32 0, i32 3
  %356 = load i8*, i8** %355, align 8
  %357 = getelementptr i8, i8* %356, i32 %352
  %358 = bitcast i8* %357 to i64*
  %359 = add i32 %352, 8
  store i32 %359, i32* %351, align 8
  br label %365

; <label>:360:                                    ; preds = %349
  %361 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %350, i32 0, i32 2
  %362 = load i8*, i8** %361, align 8
  %363 = bitcast i8* %362 to i64*
  %364 = getelementptr i8, i8* %362, i32 8
  store i8* %364, i8** %361, align 8
  br label %365

; <label>:365:                                    ; preds = %360, %354
  %366 = phi i64* [ %358, %354 ], [ %363, %360 ]
  %367 = load i64, i64* %366, align 8
  store i64 %367, i64* %20, align 8
  %368 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %369 = load i8*, i8** %7, align 8
  %370 = load i64, i64* %15, align 8
  %371 = load i64, i64* %8, align 8
  %372 = load i64, i64* %20, align 8
  %373 = icmp sgt i64 %372, 0
  br i1 %373, label %374, label %376

; <label>:374:                                    ; preds = %365
  %375 = load i64, i64* %20, align 8
  br label %379

; <label>:376:                                    ; preds = %365
  %377 = load i64, i64* %20, align 8
  %378 = sub nsw i64 0, %377
  br label %379

; <label>:379:                                    ; preds = %376, %374
  %380 = phi i64 [ %375, %374 ], [ %378, %376 ]
  %381 = load i64, i64* %20, align 8
  %382 = icmp slt i64 %381, 0
  %383 = load i32, i32* %18, align 4
  %384 = zext i32 %383 to i64
  %385 = load i32, i32* %13, align 4
  %386 = load i32, i32* %12, align 4
  %387 = load i32, i32* %11, align 4
  %388 = call fastcc i64 @_ntoa_long(void (i8, i8*, i64, i64)* %368, i8* %369, i64 %370, i64 %371, i64 %380, i1 zeroext %382, i64 %384, i32 %385, i32 %386, i32 %387)
  store i64 %388, i64* %15, align 8
  br label %484

; <label>:389:                                    ; preds = %345
  %390 = load i32, i32* %11, align 4
  %391 = and i32 %390, 64
  %392 = icmp ne i32 %391, 0
  br i1 %392, label %393, label %414

; <label>:393:                                    ; preds = %389
  %394 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %395 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %394, i32 0, i32 0
  %396 = load i32, i32* %395, align 8
  %397 = icmp ule i32 %396, 40
  br i1 %397, label %398, label %404

; <label>:398:                                    ; preds = %393
  %399 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %394, i32 0, i32 3
  %400 = load i8*, i8** %399, align 8
  %401 = getelementptr i8, i8* %400, i32 %396
  %402 = bitcast i8* %401 to i32*
  %403 = add i32 %396, 8
  store i32 %403, i32* %395, align 8
  br label %409

; <label>:404:                                    ; preds = %393
  %405 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %394, i32 0, i32 2
  %406 = load i8*, i8** %405, align 8
  %407 = bitcast i8* %406 to i32*
  %408 = getelementptr i8, i8* %406, i32 8
  store i8* %408, i8** %405, align 8
  br label %409

; <label>:409:                                    ; preds = %404, %398
  %410 = phi i32* [ %402, %398 ], [ %407, %404 ]
  %411 = load i32, i32* %410, align 4
  %412 = trunc i32 %411 to i8
  %413 = sext i8 %412 to i32
  br label %460

; <label>:414:                                    ; preds = %389
  %415 = load i32, i32* %11, align 4
  %416 = and i32 %415, 128
  %417 = icmp ne i32 %416, 0
  br i1 %417, label %418, label %439

; <label>:418:                                    ; preds = %414
  %419 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %420 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %419, i32 0, i32 0
  %421 = load i32, i32* %420, align 8
  %422 = icmp ule i32 %421, 40
  br i1 %422, label %423, label %429

; <label>:423:                                    ; preds = %418
  %424 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %419, i32 0, i32 3
  %425 = load i8*, i8** %424, align 8
  %426 = getelementptr i8, i8* %425, i32 %421
  %427 = bitcast i8* %426 to i32*
  %428 = add i32 %421, 8
  store i32 %428, i32* %420, align 8
  br label %434

; <label>:429:                                    ; preds = %418
  %430 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %419, i32 0, i32 2
  %431 = load i8*, i8** %430, align 8
  %432 = bitcast i8* %431 to i32*
  %433 = getelementptr i8, i8* %431, i32 8
  store i8* %433, i8** %430, align 8
  br label %434

; <label>:434:                                    ; preds = %429, %423
  %435 = phi i32* [ %427, %423 ], [ %432, %429 ]
  %436 = load i32, i32* %435, align 4
  %437 = trunc i32 %436 to i16
  %438 = sext i16 %437 to i32
  br label %458

; <label>:439:                                    ; preds = %414
  %440 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %441 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %440, i32 0, i32 0
  %442 = load i32, i32* %441, align 8
  %443 = icmp ule i32 %442, 40
  br i1 %443, label %444, label %450

; <label>:444:                                    ; preds = %439
  %445 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %440, i32 0, i32 3
  %446 = load i8*, i8** %445, align 8
  %447 = getelementptr i8, i8* %446, i32 %442
  %448 = bitcast i8* %447 to i32*
  %449 = add i32 %442, 8
  store i32 %449, i32* %441, align 8
  br label %455

; <label>:450:                                    ; preds = %439
  %451 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %440, i32 0, i32 2
  %452 = load i8*, i8** %451, align 8
  %453 = bitcast i8* %452 to i32*
  %454 = getelementptr i8, i8* %452, i32 8
  store i8* %454, i8** %451, align 8
  br label %455

; <label>:455:                                    ; preds = %450, %444
  %456 = phi i32* [ %448, %444 ], [ %453, %450 ]
  %457 = load i32, i32* %456, align 4
  br label %458

; <label>:458:                                    ; preds = %455, %434
  %459 = phi i32 [ %438, %434 ], [ %457, %455 ]
  br label %460

; <label>:460:                                    ; preds = %458, %409
  %461 = phi i32 [ %413, %409 ], [ %459, %458 ]
  store i32 %461, i32* %21, align 4
  %462 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %463 = load i8*, i8** %7, align 8
  %464 = load i64, i64* %15, align 8
  %465 = load i64, i64* %8, align 8
  %466 = load i32, i32* %21, align 4
  %467 = icmp sgt i32 %466, 0
  br i1 %467, label %468, label %470

; <label>:468:                                    ; preds = %460
  %469 = load i32, i32* %21, align 4
  br label %473

; <label>:470:                                    ; preds = %460
  %471 = load i32, i32* %21, align 4
  %472 = sub nsw i32 0, %471
  br label %473

; <label>:473:                                    ; preds = %470, %468
  %474 = phi i32 [ %469, %468 ], [ %472, %470 ]
  %475 = zext i32 %474 to i64
  %476 = load i32, i32* %21, align 4
  %477 = icmp slt i32 %476, 0
  %478 = load i32, i32* %18, align 4
  %479 = zext i32 %478 to i64
  %480 = load i32, i32* %13, align 4
  %481 = load i32, i32* %12, align 4
  %482 = load i32, i32* %11, align 4
  %483 = call fastcc i64 @_ntoa_long(void (i8, i8*, i64, i64)* %462, i8* %463, i64 %464, i64 %465, i64 %475, i1 zeroext %477, i64 %479, i32 %480, i32 %481, i32 %482)
  store i64 %483, i64* %15, align 8
  br label %484

; <label>:484:                                    ; preds = %473, %379
  br label %485

; <label>:485:                                    ; preds = %484, %335
  br label %639

; <label>:486:                                    ; preds = %296
  %487 = load i32, i32* %11, align 4
  %488 = and i32 %487, 512
  %489 = icmp ne i32 %488, 0
  br i1 %489, label %490, label %519

; <label>:490:                                    ; preds = %486
  %491 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %492 = load i8*, i8** %7, align 8
  %493 = load i64, i64* %15, align 8
  %494 = load i64, i64* %8, align 8
  %495 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %496 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %495, i32 0, i32 0
  %497 = load i32, i32* %496, align 8
  %498 = icmp ule i32 %497, 40
  br i1 %498, label %499, label %505

; <label>:499:                                    ; preds = %490
  %500 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %495, i32 0, i32 3
  %501 = load i8*, i8** %500, align 8
  %502 = getelementptr i8, i8* %501, i32 %497
  %503 = bitcast i8* %502 to i64*
  %504 = add i32 %497, 8
  store i32 %504, i32* %496, align 8
  br label %510

; <label>:505:                                    ; preds = %490
  %506 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %495, i32 0, i32 2
  %507 = load i8*, i8** %506, align 8
  %508 = bitcast i8* %507 to i64*
  %509 = getelementptr i8, i8* %507, i32 8
  store i8* %509, i8** %506, align 8
  br label %510

; <label>:510:                                    ; preds = %505, %499
  %511 = phi i64* [ %503, %499 ], [ %508, %505 ]
  %512 = load i64, i64* %511, align 8
  %513 = load i32, i32* %18, align 4
  %514 = zext i32 %513 to i64
  %515 = load i32, i32* %13, align 4
  %516 = load i32, i32* %12, align 4
  %517 = load i32, i32* %11, align 4
  %518 = call fastcc i64 @_ntoa_long_long(void (i8, i8*, i64, i64)* %491, i8* %492, i64 %493, i64 %494, i64 %512, i1 zeroext false, i64 %514, i32 %515, i32 %516, i32 %517)
  store i64 %518, i64* %15, align 8
  br label %638

; <label>:519:                                    ; preds = %486
  %520 = load i32, i32* %11, align 4
  %521 = and i32 %520, 256
  %522 = icmp ne i32 %521, 0
  br i1 %522, label %523, label %552

; <label>:523:                                    ; preds = %519
  %524 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %525 = load i8*, i8** %7, align 8
  %526 = load i64, i64* %15, align 8
  %527 = load i64, i64* %8, align 8
  %528 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %529 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %528, i32 0, i32 0
  %530 = load i32, i32* %529, align 8
  %531 = icmp ule i32 %530, 40
  br i1 %531, label %532, label %538

; <label>:532:                                    ; preds = %523
  %533 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %528, i32 0, i32 3
  %534 = load i8*, i8** %533, align 8
  %535 = getelementptr i8, i8* %534, i32 %530
  %536 = bitcast i8* %535 to i64*
  %537 = add i32 %530, 8
  store i32 %537, i32* %529, align 8
  br label %543

; <label>:538:                                    ; preds = %523
  %539 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %528, i32 0, i32 2
  %540 = load i8*, i8** %539, align 8
  %541 = bitcast i8* %540 to i64*
  %542 = getelementptr i8, i8* %540, i32 8
  store i8* %542, i8** %539, align 8
  br label %543

; <label>:543:                                    ; preds = %538, %532
  %544 = phi i64* [ %536, %532 ], [ %541, %538 ]
  %545 = load i64, i64* %544, align 8
  %546 = load i32, i32* %18, align 4
  %547 = zext i32 %546 to i64
  %548 = load i32, i32* %13, align 4
  %549 = load i32, i32* %12, align 4
  %550 = load i32, i32* %11, align 4
  %551 = call fastcc i64 @_ntoa_long(void (i8, i8*, i64, i64)* %524, i8* %525, i64 %526, i64 %527, i64 %545, i1 zeroext false, i64 %547, i32 %548, i32 %549, i32 %550)
  store i64 %551, i64* %15, align 8
  br label %637

; <label>:552:                                    ; preds = %519
  %553 = load i32, i32* %11, align 4
  %554 = and i32 %553, 64
  %555 = icmp ne i32 %554, 0
  br i1 %555, label %556, label %577

; <label>:556:                                    ; preds = %552
  %557 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %558 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %557, i32 0, i32 0
  %559 = load i32, i32* %558, align 8
  %560 = icmp ule i32 %559, 40
  br i1 %560, label %561, label %567

; <label>:561:                                    ; preds = %556
  %562 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %557, i32 0, i32 3
  %563 = load i8*, i8** %562, align 8
  %564 = getelementptr i8, i8* %563, i32 %559
  %565 = bitcast i8* %564 to i32*
  %566 = add i32 %559, 8
  store i32 %566, i32* %558, align 8
  br label %572

; <label>:567:                                    ; preds = %556
  %568 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %557, i32 0, i32 2
  %569 = load i8*, i8** %568, align 8
  %570 = bitcast i8* %569 to i32*
  %571 = getelementptr i8, i8* %569, i32 8
  store i8* %571, i8** %568, align 8
  br label %572

; <label>:572:                                    ; preds = %567, %561
  %573 = phi i32* [ %565, %561 ], [ %570, %567 ]
  %574 = load i32, i32* %573, align 4
  %575 = trunc i32 %574 to i8
  %576 = zext i8 %575 to i32
  br label %623

; <label>:577:                                    ; preds = %552
  %578 = load i32, i32* %11, align 4
  %579 = and i32 %578, 128
  %580 = icmp ne i32 %579, 0
  br i1 %580, label %581, label %602

; <label>:581:                                    ; preds = %577
  %582 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %583 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %582, i32 0, i32 0
  %584 = load i32, i32* %583, align 8
  %585 = icmp ule i32 %584, 40
  br i1 %585, label %586, label %592

; <label>:586:                                    ; preds = %581
  %587 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %582, i32 0, i32 3
  %588 = load i8*, i8** %587, align 8
  %589 = getelementptr i8, i8* %588, i32 %584
  %590 = bitcast i8* %589 to i32*
  %591 = add i32 %584, 8
  store i32 %591, i32* %583, align 8
  br label %597

; <label>:592:                                    ; preds = %581
  %593 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %582, i32 0, i32 2
  %594 = load i8*, i8** %593, align 8
  %595 = bitcast i8* %594 to i32*
  %596 = getelementptr i8, i8* %594, i32 8
  store i8* %596, i8** %593, align 8
  br label %597

; <label>:597:                                    ; preds = %592, %586
  %598 = phi i32* [ %590, %586 ], [ %595, %592 ]
  %599 = load i32, i32* %598, align 4
  %600 = trunc i32 %599 to i16
  %601 = zext i16 %600 to i32
  br label %621

; <label>:602:                                    ; preds = %577
  %603 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %604 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %603, i32 0, i32 0
  %605 = load i32, i32* %604, align 8
  %606 = icmp ule i32 %605, 40
  br i1 %606, label %607, label %613

; <label>:607:                                    ; preds = %602
  %608 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %603, i32 0, i32 3
  %609 = load i8*, i8** %608, align 8
  %610 = getelementptr i8, i8* %609, i32 %605
  %611 = bitcast i8* %610 to i32*
  %612 = add i32 %605, 8
  store i32 %612, i32* %604, align 8
  br label %618

; <label>:613:                                    ; preds = %602
  %614 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %603, i32 0, i32 2
  %615 = load i8*, i8** %614, align 8
  %616 = bitcast i8* %615 to i32*
  %617 = getelementptr i8, i8* %615, i32 8
  store i8* %617, i8** %614, align 8
  br label %618

; <label>:618:                                    ; preds = %613, %607
  %619 = phi i32* [ %611, %607 ], [ %616, %613 ]
  %620 = load i32, i32* %619, align 4
  br label %621

; <label>:621:                                    ; preds = %618, %597
  %622 = phi i32 [ %601, %597 ], [ %620, %618 ]
  br label %623

; <label>:623:                                    ; preds = %621, %572
  %624 = phi i32 [ %576, %572 ], [ %622, %621 ]
  store i32 %624, i32* %22, align 4
  %625 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %626 = load i8*, i8** %7, align 8
  %627 = load i64, i64* %15, align 8
  %628 = load i64, i64* %8, align 8
  %629 = load i32, i32* %22, align 4
  %630 = zext i32 %629 to i64
  %631 = load i32, i32* %18, align 4
  %632 = zext i32 %631 to i64
  %633 = load i32, i32* %13, align 4
  %634 = load i32, i32* %12, align 4
  %635 = load i32, i32* %11, align 4
  %636 = call fastcc i64 @_ntoa_long(void (i8, i8*, i64, i64)* %625, i8* %626, i64 %627, i64 %628, i64 %630, i1 zeroext false, i64 %632, i32 %633, i32 %634, i32 %635)
  store i64 %636, i64* %15, align 8
  br label %637

; <label>:637:                                    ; preds = %623, %543
  br label %638

; <label>:638:                                    ; preds = %637, %510
  br label %639

; <label>:639:                                    ; preds = %638, %485
  %640 = load i8*, i8** %9, align 8
  %641 = getelementptr inbounds i8, i8* %640, i32 1
  store i8* %641, i8** %9, align 8
  br label %859

; <label>:642:                                    ; preds = %231
  store i32 1, i32* %23, align 4
  %643 = load i32, i32* %11, align 4
  %644 = and i32 %643, 2
  %645 = icmp ne i32 %644, 0
  br i1 %645, label %659, label %646

; <label>:646:                                    ; preds = %642
  br label %647

; <label>:647:                                    ; preds = %652, %646
  %648 = load i32, i32* %23, align 4
  %649 = add i32 %648, 1
  store i32 %649, i32* %23, align 4
  %650 = load i32, i32* %12, align 4
  %651 = icmp ult i32 %648, %650
  br i1 %651, label %652, label %658

; <label>:652:                                    ; preds = %647
  %653 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %654 = load i8*, i8** %7, align 8
  %655 = load i64, i64* %15, align 8
  %656 = add i64 %655, 1
  store i64 %656, i64* %15, align 8
  %657 = load i64, i64* %8, align 8
  call void %653(i8 signext 32, i8* %654, i64 %655, i64 %657)
  br label %647

; <label>:658:                                    ; preds = %647
  br label %659

; <label>:659:                                    ; preds = %658, %642
  %660 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %661 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %662 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %661, i32 0, i32 0
  %663 = load i32, i32* %662, align 8
  %664 = icmp ule i32 %663, 40
  br i1 %664, label %665, label %671

; <label>:665:                                    ; preds = %659
  %666 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %661, i32 0, i32 3
  %667 = load i8*, i8** %666, align 8
  %668 = getelementptr i8, i8* %667, i32 %663
  %669 = bitcast i8* %668 to i32*
  %670 = add i32 %663, 8
  store i32 %670, i32* %662, align 8
  br label %676

; <label>:671:                                    ; preds = %659
  %672 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %661, i32 0, i32 2
  %673 = load i8*, i8** %672, align 8
  %674 = bitcast i8* %673 to i32*
  %675 = getelementptr i8, i8* %673, i32 8
  store i8* %675, i8** %672, align 8
  br label %676

; <label>:676:                                    ; preds = %671, %665
  %677 = phi i32* [ %669, %665 ], [ %674, %671 ]
  %678 = load i32, i32* %677, align 4
  %679 = trunc i32 %678 to i8
  %680 = load i8*, i8** %7, align 8
  %681 = load i64, i64* %15, align 8
  %682 = add i64 %681, 1
  store i64 %682, i64* %15, align 8
  %683 = load i64, i64* %8, align 8
  call void %660(i8 signext %679, i8* %680, i64 %681, i64 %683)
  %684 = load i32, i32* %11, align 4
  %685 = and i32 %684, 2
  %686 = icmp ne i32 %685, 0
  br i1 %686, label %687, label %700

; <label>:687:                                    ; preds = %676
  br label %688

; <label>:688:                                    ; preds = %693, %687
  %689 = load i32, i32* %23, align 4
  %690 = add i32 %689, 1
  store i32 %690, i32* %23, align 4
  %691 = load i32, i32* %12, align 4
  %692 = icmp ult i32 %689, %691
  br i1 %692, label %693, label %699

; <label>:693:                                    ; preds = %688
  %694 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %695 = load i8*, i8** %7, align 8
  %696 = load i64, i64* %15, align 8
  %697 = add i64 %696, 1
  store i64 %697, i64* %15, align 8
  %698 = load i64, i64* %8, align 8
  call void %694(i8 signext 32, i8* %695, i64 %696, i64 %698)
  br label %688

; <label>:699:                                    ; preds = %688
  br label %700

; <label>:700:                                    ; preds = %699, %676
  %701 = load i8*, i8** %9, align 8
  %702 = getelementptr inbounds i8, i8* %701, i32 1
  store i8* %702, i8** %9, align 8
  br label %859

; <label>:703:                                    ; preds = %231
  %704 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %705 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %704, i32 0, i32 0
  %706 = load i32, i32* %705, align 8
  %707 = icmp ule i32 %706, 40
  br i1 %707, label %708, label %714

; <label>:708:                                    ; preds = %703
  %709 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %704, i32 0, i32 3
  %710 = load i8*, i8** %709, align 8
  %711 = getelementptr i8, i8* %710, i32 %706
  %712 = bitcast i8* %711 to i8**
  %713 = add i32 %706, 8
  store i32 %713, i32* %705, align 8
  br label %719

; <label>:714:                                    ; preds = %703
  %715 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %704, i32 0, i32 2
  %716 = load i8*, i8** %715, align 8
  %717 = bitcast i8* %716 to i8**
  %718 = getelementptr i8, i8* %716, i32 8
  store i8* %718, i8** %715, align 8
  br label %719

; <label>:719:                                    ; preds = %714, %708
  %720 = phi i8** [ %712, %708 ], [ %717, %714 ]
  %721 = load i8*, i8** %720, align 8
  store i8* %721, i8** %24, align 8
  %722 = load i8*, i8** %24, align 8
  %723 = load i32, i32* %13, align 4
  %724 = icmp ne i32 %723, 0
  br i1 %724, label %725, label %728

; <label>:725:                                    ; preds = %719
  %726 = load i32, i32* %13, align 4
  %727 = zext i32 %726 to i64
  br label %729

; <label>:728:                                    ; preds = %719
  br label %729

; <label>:729:                                    ; preds = %728, %725
  %730 = phi i64 [ %727, %725 ], [ -1, %728 ]
  %731 = call fastcc i32 @_strnlen_s(i8* %722, i64 %730)
  store i32 %731, i32* %25, align 4
  %732 = load i32, i32* %11, align 4
  %733 = and i32 %732, 1024
  %734 = icmp ne i32 %733, 0
  br i1 %734, label %735, label %745

; <label>:735:                                    ; preds = %729
  %736 = load i32, i32* %25, align 4
  %737 = load i32, i32* %13, align 4
  %738 = icmp ult i32 %736, %737
  br i1 %738, label %739, label %741

; <label>:739:                                    ; preds = %735
  %740 = load i32, i32* %25, align 4
  br label %743

; <label>:741:                                    ; preds = %735
  %742 = load i32, i32* %13, align 4
  br label %743

; <label>:743:                                    ; preds = %741, %739
  %744 = phi i32 [ %740, %739 ], [ %742, %741 ]
  store i32 %744, i32* %25, align 4
  br label %745

; <label>:745:                                    ; preds = %743, %729
  %746 = load i32, i32* %11, align 4
  %747 = and i32 %746, 2
  %748 = icmp ne i32 %747, 0
  br i1 %748, label %762, label %749

; <label>:749:                                    ; preds = %745
  br label %750

; <label>:750:                                    ; preds = %755, %749
  %751 = load i32, i32* %25, align 4
  %752 = add i32 %751, 1
  store i32 %752, i32* %25, align 4
  %753 = load i32, i32* %12, align 4
  %754 = icmp ult i32 %751, %753
  br i1 %754, label %755, label %761

; <label>:755:                                    ; preds = %750
  %756 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %757 = load i8*, i8** %7, align 8
  %758 = load i64, i64* %15, align 8
  %759 = add i64 %758, 1
  store i64 %759, i64* %15, align 8
  %760 = load i64, i64* %8, align 8
  call void %756(i8 signext 32, i8* %757, i64 %758, i64 %760)
  br label %750

; <label>:761:                                    ; preds = %750
  br label %762

; <label>:762:                                    ; preds = %761, %745
  br label %763

; <label>:763:                                    ; preds = %780, %762
  %764 = load i8*, i8** %24, align 8
  %765 = load i8, i8* %764, align 1
  %766 = sext i8 %765 to i32
  %767 = icmp ne i32 %766, 0
  br i1 %767, label %768, label %778

; <label>:768:                                    ; preds = %763
  %769 = load i32, i32* %11, align 4
  %770 = and i32 %769, 1024
  %771 = icmp ne i32 %770, 0
  br i1 %771, label %772, label %776

; <label>:772:                                    ; preds = %768
  %773 = load i32, i32* %13, align 4
  %774 = add i32 %773, -1
  store i32 %774, i32* %13, align 4
  %775 = icmp ne i32 %773, 0
  br label %776

; <label>:776:                                    ; preds = %772, %768
  %777 = phi i1 [ true, %768 ], [ %775, %772 ]
  br label %778

; <label>:778:                                    ; preds = %776, %763
  %779 = phi i1 [ false, %763 ], [ %777, %776 ]
  br i1 %779, label %780, label %789

; <label>:780:                                    ; preds = %778
  %781 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %782 = load i8*, i8** %24, align 8
  %783 = getelementptr inbounds i8, i8* %782, i32 1
  store i8* %783, i8** %24, align 8
  %784 = load i8, i8* %782, align 1
  %785 = load i8*, i8** %7, align 8
  %786 = load i64, i64* %15, align 8
  %787 = add i64 %786, 1
  store i64 %787, i64* %15, align 8
  %788 = load i64, i64* %8, align 8
  call void %781(i8 signext %784, i8* %785, i64 %786, i64 %788)
  br label %763

; <label>:789:                                    ; preds = %778
  %790 = load i32, i32* %11, align 4
  %791 = and i32 %790, 2
  %792 = icmp ne i32 %791, 0
  br i1 %792, label %793, label %806

; <label>:793:                                    ; preds = %789
  br label %794

; <label>:794:                                    ; preds = %799, %793
  %795 = load i32, i32* %25, align 4
  %796 = add i32 %795, 1
  store i32 %796, i32* %25, align 4
  %797 = load i32, i32* %12, align 4
  %798 = icmp ult i32 %795, %797
  br i1 %798, label %799, label %805

; <label>:799:                                    ; preds = %794
  %800 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %801 = load i8*, i8** %7, align 8
  %802 = load i64, i64* %15, align 8
  %803 = add i64 %802, 1
  store i64 %803, i64* %15, align 8
  %804 = load i64, i64* %8, align 8
  call void %800(i8 signext 32, i8* %801, i64 %802, i64 %804)
  br label %794

; <label>:805:                                    ; preds = %794
  br label %806

; <label>:806:                                    ; preds = %805, %789
  %807 = load i8*, i8** %9, align 8
  %808 = getelementptr inbounds i8, i8* %807, i32 1
  store i8* %808, i8** %9, align 8
  br label %859

; <label>:809:                                    ; preds = %231
  store i32 16, i32* %12, align 4
  %810 = load i32, i32* %11, align 4
  %811 = or i32 %810, 33
  store i32 %811, i32* %11, align 4
  store i8 1, i8* %26, align 1
  %812 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %813 = load i8*, i8** %7, align 8
  %814 = load i64, i64* %15, align 8
  %815 = load i64, i64* %8, align 8
  %816 = load %struct.__va_list_tag*, %struct.__va_list_tag** %10, align 8
  %817 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %816, i32 0, i32 0
  %818 = load i32, i32* %817, align 8
  %819 = icmp ule i32 %818, 40
  br i1 %819, label %820, label %826

; <label>:820:                                    ; preds = %809
  %821 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %816, i32 0, i32 3
  %822 = load i8*, i8** %821, align 8
  %823 = getelementptr i8, i8* %822, i32 %818
  %824 = bitcast i8* %823 to i8**
  %825 = add i32 %818, 8
  store i32 %825, i32* %817, align 8
  br label %831

; <label>:826:                                    ; preds = %809
  %827 = getelementptr inbounds %struct.__va_list_tag, %struct.__va_list_tag* %816, i32 0, i32 2
  %828 = load i8*, i8** %827, align 8
  %829 = bitcast i8* %828 to i8**
  %830 = getelementptr i8, i8* %828, i32 8
  store i8* %830, i8** %827, align 8
  br label %831

; <label>:831:                                    ; preds = %826, %820
  %832 = phi i8** [ %824, %820 ], [ %829, %826 ]
  %833 = load i8*, i8** %832, align 8
  %834 = ptrtoint i8* %833 to i64
  %835 = load i32, i32* %13, align 4
  %836 = load i32, i32* %12, align 4
  %837 = load i32, i32* %11, align 4
  %838 = call fastcc i64 @_ntoa_long_long(void (i8, i8*, i64, i64)* %812, i8* %813, i64 %814, i64 %815, i64 %834, i1 zeroext false, i64 16, i32 %835, i32 %836, i32 %837)
  store i64 %838, i64* %15, align 8
  %839 = load i8*, i8** %9, align 8
  %840 = getelementptr inbounds i8, i8* %839, i32 1
  store i8* %840, i8** %9, align 8
  br label %859

; <label>:841:                                    ; preds = %231
  %842 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %843 = load i8*, i8** %7, align 8
  %844 = load i64, i64* %15, align 8
  %845 = add i64 %844, 1
  store i64 %845, i64* %15, align 8
  %846 = load i64, i64* %8, align 8
  call void %842(i8 signext 37, i8* %843, i64 %844, i64 %846)
  %847 = load i8*, i8** %9, align 8
  %848 = getelementptr inbounds i8, i8* %847, i32 1
  store i8* %848, i8** %9, align 8
  br label %859

; <label>:849:                                    ; preds = %231
  %850 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %851 = load i8*, i8** %9, align 8
  %852 = load i8, i8* %851, align 1
  %853 = load i8*, i8** %7, align 8
  %854 = load i64, i64* %15, align 8
  %855 = add i64 %854, 1
  store i64 %855, i64* %15, align 8
  %856 = load i64, i64* %8, align 8
  call void %850(i8 signext %852, i8* %853, i64 %854, i64 %856)
  %857 = load i8*, i8** %9, align 8
  %858 = getelementptr inbounds i8, i8* %857, i32 1
  store i8* %858, i8** %9, align 8
  br label %859

; <label>:859:                                    ; preds = %849, %841, %831, %806, %700, %639
  br label %.backedge

; <label>:860:                                    ; preds = %31
  %861 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %6, align 8
  %862 = load i8*, i8** %7, align 8
  %863 = load i64, i64* %15, align 8
  %864 = load i64, i64* %8, align 8
  %865 = icmp ult i64 %863, %864
  br i1 %865, label %866, label %868

; <label>:866:                                    ; preds = %860
  %867 = load i64, i64* %15, align 8
  br label %871

; <label>:868:                                    ; preds = %860
  %869 = load i64, i64* %8, align 8
  %870 = sub i64 %869, 1
  br label %871

; <label>:871:                                    ; preds = %868, %866
  %872 = phi i64 [ %867, %866 ], [ %870, %868 ]
  %873 = load i64, i64* %8, align 8
  call void %861(i8 signext 0, i8* %862, i64 %872, i64 %873)
  %874 = load i64, i64* %15, align 8
  %875 = trunc i64 %874 to i32
  ret i32 %875
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @_out_char(i8 signext, i8*, i64, i64) #0 {
  %5 = alloca i8, align 1
  %6 = alloca i8*, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  store i8 %0, i8* %5, align 1
  store i8* %1, i8** %6, align 8
  store i64 %2, i64* %7, align 8
  store i64 %3, i64* %8, align 8
  %9 = load i8*, i8** %6, align 8
  %10 = load i64, i64* %7, align 8
  %11 = load i64, i64* %8, align 8
  %12 = load i8, i8* %5, align 1
  %13 = icmp ne i8 %12, 0
  br i1 %13, label %14, label %16

; <label>:14:                                     ; preds = %4
  %15 = load i8, i8* %5, align 1
  call void @_putchar(i8 signext %15)
  br label %16

; <label>:16:                                     ; preds = %14, %4
  ret void
}

; Function Attrs: nounwind
declare void @llvm.va_end(i8*) #1

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @sprintf_(i8*, i8*, ...) local_unnamed_addr #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca [1 x %struct.__va_list_tag], align 16
  %6 = alloca i32, align 4
  store i8* %0, i8** %3, align 8
  store i8* %1, i8** %4, align 8
  %7 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i32 0, i32 0
  %8 = bitcast %struct.__va_list_tag* %7 to i8*
  call void @llvm.va_start(i8* %8)
  %9 = load i8*, i8** %3, align 8
  %10 = load i8*, i8** %4, align 8
  %11 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i32 0, i32 0
  %12 = call fastcc i32 @_vsnprintf(void (i8, i8*, i64, i64)* @_out_buffer, i8* %9, i64 -1, i8* %10, %struct.__va_list_tag* %11)
  store i32 %12, i32* %6, align 4
  %13 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %5, i32 0, i32 0
  %14 = bitcast %struct.__va_list_tag* %13 to i8*
  call void @llvm.va_end(i8* %14)
  %15 = load i32, i32* %6, align 4
  ret i32 %15
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @_out_buffer(i8 signext, i8*, i64, i64) #0 {
  %5 = alloca i8, align 1
  %6 = alloca i8*, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  store i8 %0, i8* %5, align 1
  store i8* %1, i8** %6, align 8
  store i64 %2, i64* %7, align 8
  store i64 %3, i64* %8, align 8
  %9 = load i64, i64* %7, align 8
  %10 = load i64, i64* %8, align 8
  %11 = icmp ult i64 %9, %10
  br i1 %11, label %12, label %17

; <label>:12:                                     ; preds = %4
  %13 = load i8, i8* %5, align 1
  %14 = load i8*, i8** %6, align 8
  %15 = load i64, i64* %7, align 8
  %16 = getelementptr inbounds i8, i8* %14, i64 %15
  store i8 %13, i8* %16, align 1
  br label %17

; <label>:17:                                     ; preds = %12, %4
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @snprintf_(i8*, i64, i8*, ...) local_unnamed_addr #0 {
  %4 = alloca i8*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i8*, align 8
  %7 = alloca [1 x %struct.__va_list_tag], align 16
  %8 = alloca i32, align 4
  store i8* %0, i8** %4, align 8
  store i64 %1, i64* %5, align 8
  store i8* %2, i8** %6, align 8
  %9 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i32 0, i32 0
  %10 = bitcast %struct.__va_list_tag* %9 to i8*
  call void @llvm.va_start(i8* %10)
  %11 = load i8*, i8** %4, align 8
  %12 = load i64, i64* %5, align 8
  %13 = load i8*, i8** %6, align 8
  %14 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i32 0, i32 0
  %15 = call fastcc i32 @_vsnprintf(void (i8, i8*, i64, i64)* @_out_buffer, i8* %11, i64 %12, i8* %13, %struct.__va_list_tag* %14)
  store i32 %15, i32* %8, align 4
  %16 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i32 0, i32 0
  %17 = bitcast %struct.__va_list_tag* %16 to i8*
  call void @llvm.va_end(i8* %17)
  %18 = load i32, i32* %8, align 4
  ret i32 %18
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @vprintf_(i8*, %struct.__va_list_tag*) local_unnamed_addr #0 {
  %3 = alloca i8*, align 8
  %4 = alloca %struct.__va_list_tag*, align 8
  %5 = alloca [1 x i8], align 1
  store i8* %0, i8** %3, align 8
  store %struct.__va_list_tag* %1, %struct.__va_list_tag** %4, align 8
  %6 = getelementptr inbounds [1 x i8], [1 x i8]* %5, i32 0, i32 0
  %7 = load i8*, i8** %3, align 8
  %8 = load %struct.__va_list_tag*, %struct.__va_list_tag** %4, align 8
  %9 = call fastcc i32 @_vsnprintf(void (i8, i8*, i64, i64)* @_out_char, i8* %6, i64 -1, i8* %7, %struct.__va_list_tag* %8)
  ret i32 %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @vsnprintf_(i8*, i64, i8*, %struct.__va_list_tag*) local_unnamed_addr #0 {
  %5 = alloca i8*, align 8
  %6 = alloca i64, align 8
  %7 = alloca i8*, align 8
  %8 = alloca %struct.__va_list_tag*, align 8
  store i8* %0, i8** %5, align 8
  store i64 %1, i64* %6, align 8
  store i8* %2, i8** %7, align 8
  store %struct.__va_list_tag* %3, %struct.__va_list_tag** %8, align 8
  %9 = load i8*, i8** %5, align 8
  %10 = load i64, i64* %6, align 8
  %11 = load i8*, i8** %7, align 8
  %12 = load %struct.__va_list_tag*, %struct.__va_list_tag** %8, align 8
  %13 = call fastcc i32 @_vsnprintf(void (i8, i8*, i64, i64)* @_out_buffer, i8* %9, i64 %10, i8* %11, %struct.__va_list_tag* %12)
  ret i32 %13
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fctprintf(void (i8, i8*)*, i8*, i8*, ...) local_unnamed_addr #0 {
  %4 = alloca void (i8, i8*)*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i8*, align 8
  %7 = alloca [1 x %struct.__va_list_tag], align 16
  %8 = alloca %struct.out_fct_wrap_type, align 8
  %9 = alloca i32, align 4
  store void (i8, i8*)* %0, void (i8, i8*)** %4, align 8
  store i8* %1, i8** %5, align 8
  store i8* %2, i8** %6, align 8
  %10 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i32 0, i32 0
  %11 = bitcast %struct.__va_list_tag* %10 to i8*
  call void @llvm.va_start(i8* %11)
  %12 = getelementptr inbounds %struct.out_fct_wrap_type, %struct.out_fct_wrap_type* %8, i32 0, i32 0
  %13 = load void (i8, i8*)*, void (i8, i8*)** %4, align 8
  store void (i8, i8*)* %13, void (i8, i8*)** %12, align 8
  %14 = getelementptr inbounds %struct.out_fct_wrap_type, %struct.out_fct_wrap_type* %8, i32 0, i32 1
  %15 = load i8*, i8** %5, align 8
  store i8* %15, i8** %14, align 8
  %16 = ptrtoint %struct.out_fct_wrap_type* %8 to i64
  %17 = inttoptr i64 %16 to i8*
  %18 = load i8*, i8** %6, align 8
  %19 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i32 0, i32 0
  %20 = call fastcc i32 @_vsnprintf(void (i8, i8*, i64, i64)* @_out_fct, i8* %17, i64 -1, i8* %18, %struct.__va_list_tag* %19)
  store i32 %20, i32* %9, align 4
  %21 = getelementptr inbounds [1 x %struct.__va_list_tag], [1 x %struct.__va_list_tag]* %7, i32 0, i32 0
  %22 = bitcast %struct.__va_list_tag* %21 to i8*
  call void @llvm.va_end(i8* %22)
  %23 = load i32, i32* %9, align 4
  ret i32 %23
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @_out_fct(i8 signext, i8*, i64, i64) #0 {
  %5 = alloca i8, align 1
  %6 = alloca i8*, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  store i8 %0, i8* %5, align 1
  store i8* %1, i8** %6, align 8
  store i64 %2, i64* %7, align 8
  store i64 %3, i64* %8, align 8
  %9 = load i64, i64* %7, align 8
  %10 = load i64, i64* %8, align 8
  %11 = load i8, i8* %5, align 1
  %12 = icmp ne i8 %11, 0
  br i1 %12, label %13, label %23

; <label>:13:                                     ; preds = %4
  %14 = load i8*, i8** %6, align 8
  %15 = bitcast i8* %14 to %struct.out_fct_wrap_type*
  %16 = getelementptr inbounds %struct.out_fct_wrap_type, %struct.out_fct_wrap_type* %15, i32 0, i32 0
  %17 = load void (i8, i8*)*, void (i8, i8*)** %16, align 8
  %18 = load i8, i8* %5, align 1
  %19 = load i8*, i8** %6, align 8
  %20 = bitcast i8* %19 to %struct.out_fct_wrap_type*
  %21 = getelementptr inbounds %struct.out_fct_wrap_type, %struct.out_fct_wrap_type* %20, i32 0, i32 1
  %22 = load i8*, i8** %21, align 8
  call void %17(i8 signext %18, i8* %22)
  br label %23

; <label>:23:                                     ; preds = %13, %4
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal void @_out_null(i8 signext, i8*, i64, i64) #0 {
  %5 = alloca i8, align 1
  %6 = alloca i8*, align 8
  %7 = alloca i64, align 8
  %8 = alloca i64, align 8
  store i8 %0, i8* %5, align 1
  store i8* %1, i8** %6, align 8
  store i64 %2, i64* %7, align 8
  store i64 %3, i64* %8, align 8
  %9 = load i8, i8* %5, align 1
  %10 = load i8*, i8** %6, align 8
  %11 = load i64, i64* %7, align 8
  %12 = load i64, i64* %8, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal fastcc zeroext i1 @_is_digit(i8 signext) unnamed_addr #0 {
  %2 = alloca i8, align 1
  store i8 %0, i8* %2, align 1
  %3 = load i8, i8* %2, align 1
  %4 = sext i8 %3 to i32
  %5 = icmp sge i32 %4, 48
  br i1 %5, label %6, label %10

; <label>:6:                                      ; preds = %1
  %7 = load i8, i8* %2, align 1
  %8 = sext i8 %7 to i32
  %9 = icmp sle i32 %8, 57
  br label %10

; <label>:10:                                     ; preds = %6, %1
  %11 = phi i1 [ false, %1 ], [ %9, %6 ]
  ret i1 %11
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal fastcc i32 @_atoi(i8**) unnamed_addr #0 {
  %2 = alloca i8**, align 8
  %3 = alloca i32, align 4
  store i8** %0, i8*** %2, align 8
  store i32 0, i32* %3, align 4
  br label %4

; <label>:4:                                      ; preds = %9, %1
  %5 = load i8**, i8*** %2, align 8
  %6 = load i8*, i8** %5, align 8
  %7 = load i8, i8* %6, align 1
  %8 = call fastcc zeroext i1 @_is_digit(i8 signext %7)
  br i1 %8, label %9, label %19

; <label>:9:                                      ; preds = %4
  %10 = load i32, i32* %3, align 4
  %11 = mul i32 %10, 10
  %12 = load i8**, i8*** %2, align 8
  %13 = load i8*, i8** %12, align 8
  %14 = getelementptr inbounds i8, i8* %13, i32 1
  store i8* %14, i8** %12, align 8
  %15 = load i8, i8* %13, align 1
  %16 = sext i8 %15 to i32
  %17 = sub nsw i32 %16, 48
  %18 = add i32 %11, %17
  store i32 %18, i32* %3, align 4
  br label %4

; <label>:19:                                     ; preds = %4
  %20 = load i32, i32* %3, align 4
  ret i32 %20
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal fastcc i64 @_ntoa_long_long(void (i8, i8*, i64, i64)*, i8*, i64, i64, i64, i1 zeroext, i64, i32, i32, i32) unnamed_addr #0 {
  %11 = alloca void (i8, i8*, i64, i64)*, align 8
  %12 = alloca i8*, align 8
  %13 = alloca i64, align 8
  %14 = alloca i64, align 8
  %15 = alloca i64, align 8
  %16 = alloca i8, align 1
  %17 = alloca i64, align 8
  %18 = alloca i32, align 4
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %21 = alloca [32 x i8], align 16
  %22 = alloca i64, align 8
  %23 = alloca i8, align 1
  store void (i8, i8*, i64, i64)* %0, void (i8, i8*, i64, i64)** %11, align 8
  store i8* %1, i8** %12, align 8
  store i64 %2, i64* %13, align 8
  store i64 %3, i64* %14, align 8
  store i64 %4, i64* %15, align 8
  %24 = zext i1 %5 to i8
  store i8 %24, i8* %16, align 1
  store i64 %6, i64* %17, align 8
  store i32 %7, i32* %18, align 4
  store i32 %8, i32* %19, align 4
  store i32 %9, i32* %20, align 4
  store i64 0, i64* %22, align 8
  %25 = load i64, i64* %15, align 8
  %26 = icmp ne i64 %25, 0
  br i1 %26, label %30, label %27

; <label>:27:                                     ; preds = %10
  %28 = load i32, i32* %20, align 4
  %29 = and i32 %28, -17
  store i32 %29, i32* %20, align 4
  br label %30

; <label>:30:                                     ; preds = %27, %10
  %31 = load i32, i32* %20, align 4
  %32 = and i32 %31, 1024
  %33 = icmp ne i32 %32, 0
  br i1 %33, label %34, label %37

; <label>:34:                                     ; preds = %30
  %35 = load i64, i64* %15, align 8
  %36 = icmp ne i64 %35, 0
  br i1 %36, label %37, label %78

; <label>:37:                                     ; preds = %34, %30
  br label %38

; <label>:38:                                     ; preds = %75, %37
  %39 = load i64, i64* %15, align 8
  %40 = load i64, i64* %17, align 8
  %41 = urem i64 %39, %40
  %42 = trunc i64 %41 to i8
  store i8 %42, i8* %23, align 1
  %43 = load i8, i8* %23, align 1
  %44 = sext i8 %43 to i32
  %45 = icmp slt i32 %44, 10
  br i1 %45, label %46, label %50

; <label>:46:                                     ; preds = %38
  %47 = load i8, i8* %23, align 1
  %48 = sext i8 %47 to i32
  %49 = add nsw i32 48, %48
  br label %60

; <label>:50:                                     ; preds = %38
  %51 = load i32, i32* %20, align 4
  %52 = and i32 %51, 32
  %53 = icmp ne i32 %52, 0
  %54 = zext i1 %53 to i64
  %55 = select i1 %53, i32 65, i32 97
  %56 = load i8, i8* %23, align 1
  %57 = sext i8 %56 to i32
  %58 = add nsw i32 %55, %57
  %59 = sub nsw i32 %58, 10
  br label %60

; <label>:60:                                     ; preds = %50, %46
  %61 = phi i32 [ %49, %46 ], [ %59, %50 ]
  %62 = trunc i32 %61 to i8
  %63 = load i64, i64* %22, align 8
  %64 = add i64 %63, 1
  store i64 %64, i64* %22, align 8
  %65 = getelementptr inbounds [32 x i8], [32 x i8]* %21, i64 0, i64 %63
  store i8 %62, i8* %65, align 1
  %66 = load i64, i64* %17, align 8
  %67 = load i64, i64* %15, align 8
  %68 = udiv i64 %67, %66
  store i64 %68, i64* %15, align 8
  br label %69

; <label>:69:                                     ; preds = %60
  %70 = load i64, i64* %15, align 8
  %71 = icmp ne i64 %70, 0
  br i1 %71, label %72, label %75

; <label>:72:                                     ; preds = %69
  %73 = load i64, i64* %22, align 8
  %74 = icmp ult i64 %73, 32
  br label %75

; <label>:75:                                     ; preds = %72, %69
  %76 = phi i1 [ false, %69 ], [ %74, %72 ]
  br i1 %76, label %38, label %77

; <label>:77:                                     ; preds = %75
  br label %78

; <label>:78:                                     ; preds = %77, %34
  %79 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %11, align 8
  %80 = load i8*, i8** %12, align 8
  %81 = load i64, i64* %13, align 8
  %82 = load i64, i64* %14, align 8
  %83 = getelementptr inbounds [32 x i8], [32 x i8]* %21, i32 0, i32 0
  %84 = load i64, i64* %22, align 8
  %85 = load i8, i8* %16, align 1
  %86 = trunc i8 %85 to i1
  %87 = load i64, i64* %17, align 8
  %88 = trunc i64 %87 to i32
  %89 = load i32, i32* %18, align 4
  %90 = load i32, i32* %19, align 4
  %91 = load i32, i32* %20, align 4
  %92 = call fastcc i64 @_ntoa_format(void (i8, i8*, i64, i64)* %79, i8* %80, i64 %81, i64 %82, i8* %83, i64 %84, i1 zeroext %86, i32 %88, i32 %89, i32 %90, i32 %91)
  ret i64 %92
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal fastcc i64 @_ntoa_long(void (i8, i8*, i64, i64)*, i8*, i64, i64, i64, i1 zeroext, i64, i32, i32, i32) unnamed_addr #0 {
  %11 = alloca void (i8, i8*, i64, i64)*, align 8
  %12 = alloca i8*, align 8
  %13 = alloca i64, align 8
  %14 = alloca i64, align 8
  %15 = alloca i64, align 8
  %16 = alloca i8, align 1
  %17 = alloca i64, align 8
  %18 = alloca i32, align 4
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %21 = alloca [32 x i8], align 16
  %22 = alloca i64, align 8
  %23 = alloca i8, align 1
  store void (i8, i8*, i64, i64)* %0, void (i8, i8*, i64, i64)** %11, align 8
  store i8* %1, i8** %12, align 8
  store i64 %2, i64* %13, align 8
  store i64 %3, i64* %14, align 8
  store i64 %4, i64* %15, align 8
  %24 = zext i1 %5 to i8
  store i8 %24, i8* %16, align 1
  store i64 %6, i64* %17, align 8
  store i32 %7, i32* %18, align 4
  store i32 %8, i32* %19, align 4
  store i32 %9, i32* %20, align 4
  store i64 0, i64* %22, align 8
  %25 = load i64, i64* %15, align 8
  %26 = icmp ne i64 %25, 0
  br i1 %26, label %30, label %27

; <label>:27:                                     ; preds = %10
  %28 = load i32, i32* %20, align 4
  %29 = and i32 %28, -17
  store i32 %29, i32* %20, align 4
  br label %30

; <label>:30:                                     ; preds = %27, %10
  %31 = load i32, i32* %20, align 4
  %32 = and i32 %31, 1024
  %33 = icmp ne i32 %32, 0
  br i1 %33, label %34, label %37

; <label>:34:                                     ; preds = %30
  %35 = load i64, i64* %15, align 8
  %36 = icmp ne i64 %35, 0
  br i1 %36, label %37, label %78

; <label>:37:                                     ; preds = %34, %30
  br label %38

; <label>:38:                                     ; preds = %75, %37
  %39 = load i64, i64* %15, align 8
  %40 = load i64, i64* %17, align 8
  %41 = urem i64 %39, %40
  %42 = trunc i64 %41 to i8
  store i8 %42, i8* %23, align 1
  %43 = load i8, i8* %23, align 1
  %44 = sext i8 %43 to i32
  %45 = icmp slt i32 %44, 10
  br i1 %45, label %46, label %50

; <label>:46:                                     ; preds = %38
  %47 = load i8, i8* %23, align 1
  %48 = sext i8 %47 to i32
  %49 = add nsw i32 48, %48
  br label %60

; <label>:50:                                     ; preds = %38
  %51 = load i32, i32* %20, align 4
  %52 = and i32 %51, 32
  %53 = icmp ne i32 %52, 0
  %54 = zext i1 %53 to i64
  %55 = select i1 %53, i32 65, i32 97
  %56 = load i8, i8* %23, align 1
  %57 = sext i8 %56 to i32
  %58 = add nsw i32 %55, %57
  %59 = sub nsw i32 %58, 10
  br label %60

; <label>:60:                                     ; preds = %50, %46
  %61 = phi i32 [ %49, %46 ], [ %59, %50 ]
  %62 = trunc i32 %61 to i8
  %63 = load i64, i64* %22, align 8
  %64 = add i64 %63, 1
  store i64 %64, i64* %22, align 8
  %65 = getelementptr inbounds [32 x i8], [32 x i8]* %21, i64 0, i64 %63
  store i8 %62, i8* %65, align 1
  %66 = load i64, i64* %17, align 8
  %67 = load i64, i64* %15, align 8
  %68 = udiv i64 %67, %66
  store i64 %68, i64* %15, align 8
  br label %69

; <label>:69:                                     ; preds = %60
  %70 = load i64, i64* %15, align 8
  %71 = icmp ne i64 %70, 0
  br i1 %71, label %72, label %75

; <label>:72:                                     ; preds = %69
  %73 = load i64, i64* %22, align 8
  %74 = icmp ult i64 %73, 32
  br label %75

; <label>:75:                                     ; preds = %72, %69
  %76 = phi i1 [ false, %69 ], [ %74, %72 ]
  br i1 %76, label %38, label %77

; <label>:77:                                     ; preds = %75
  br label %78

; <label>:78:                                     ; preds = %77, %34
  %79 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %11, align 8
  %80 = load i8*, i8** %12, align 8
  %81 = load i64, i64* %13, align 8
  %82 = load i64, i64* %14, align 8
  %83 = getelementptr inbounds [32 x i8], [32 x i8]* %21, i32 0, i32 0
  %84 = load i64, i64* %22, align 8
  %85 = load i8, i8* %16, align 1
  %86 = trunc i8 %85 to i1
  %87 = load i64, i64* %17, align 8
  %88 = trunc i64 %87 to i32
  %89 = load i32, i32* %18, align 4
  %90 = load i32, i32* %19, align 4
  %91 = load i32, i32* %20, align 4
  %92 = call fastcc i64 @_ntoa_format(void (i8, i8*, i64, i64)* %79, i8* %80, i64 %81, i64 %82, i8* %83, i64 %84, i1 zeroext %86, i32 %88, i32 %89, i32 %90, i32 %91)
  ret i64 %92
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal fastcc i32 @_strnlen_s(i8*, i64) unnamed_addr #0 {
  %3 = alloca i8*, align 8
  %4 = alloca i64, align 8
  %5 = alloca i8*, align 8
  store i8* %0, i8** %3, align 8
  store i64 %1, i64* %4, align 8
  %6 = load i8*, i8** %3, align 8
  store i8* %6, i8** %5, align 8
  br label %7

; <label>:7:                                      ; preds = %19, %2
  %8 = load i8*, i8** %5, align 8
  %9 = load i8, i8* %8, align 1
  %10 = sext i8 %9 to i32
  %11 = icmp ne i32 %10, 0
  br i1 %11, label %12, label %16

; <label>:12:                                     ; preds = %7
  %13 = load i64, i64* %4, align 8
  %14 = add i64 %13, -1
  store i64 %14, i64* %4, align 8
  %15 = icmp ne i64 %13, 0
  br label %16

; <label>:16:                                     ; preds = %12, %7
  %17 = phi i1 [ false, %7 ], [ %15, %12 ]
  br i1 %17, label %18, label %22

; <label>:18:                                     ; preds = %16
  br label %19

; <label>:19:                                     ; preds = %18
  %20 = load i8*, i8** %5, align 8
  %21 = getelementptr inbounds i8, i8* %20, i32 1
  store i8* %21, i8** %5, align 8
  br label %7

; <label>:22:                                     ; preds = %16
  %23 = load i8*, i8** %5, align 8
  %24 = load i8*, i8** %3, align 8
  %25 = ptrtoint i8* %23 to i64
  %26 = ptrtoint i8* %24 to i64
  %27 = sub i64 %25, %26
  %28 = trunc i64 %27 to i32
  ret i32 %28
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal fastcc i64 @_ntoa_format(void (i8, i8*, i64, i64)*, i8*, i64, i64, i8*, i64, i1 zeroext, i32, i32, i32, i32) unnamed_addr #0 {
  %12 = alloca void (i8, i8*, i64, i64)*, align 8
  %13 = alloca i8*, align 8
  %14 = alloca i64, align 8
  %15 = alloca i64, align 8
  %16 = alloca i8*, align 8
  %17 = alloca i64, align 8
  %18 = alloca i8, align 1
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %21 = alloca i32, align 4
  %22 = alloca i32, align 4
  store void (i8, i8*, i64, i64)* %0, void (i8, i8*, i64, i64)** %12, align 8
  store i8* %1, i8** %13, align 8
  store i64 %2, i64* %14, align 8
  store i64 %3, i64* %15, align 8
  store i8* %4, i8** %16, align 8
  store i64 %5, i64* %17, align 8
  %23 = zext i1 %6 to i8
  store i8 %23, i8* %18, align 1
  store i32 %7, i32* %19, align 4
  store i32 %8, i32* %20, align 4
  store i32 %9, i32* %21, align 4
  store i32 %10, i32* %22, align 4
  %24 = load i32, i32* %22, align 4
  %25 = and i32 %24, 2
  %26 = icmp ne i32 %25, 0
  br i1 %26, label %81, label %27

; <label>:27:                                     ; preds = %11
  %28 = load i32, i32* %21, align 4
  %29 = icmp ne i32 %28, 0
  br i1 %29, label %30, label %44

; <label>:30:                                     ; preds = %27
  %31 = load i32, i32* %22, align 4
  %32 = and i32 %31, 1
  %33 = icmp ne i32 %32, 0
  br i1 %33, label %34, label %44

; <label>:34:                                     ; preds = %30
  %35 = load i8, i8* %18, align 1
  %36 = trunc i8 %35 to i1
  br i1 %36, label %41, label %37

; <label>:37:                                     ; preds = %34
  %38 = load i32, i32* %22, align 4
  %39 = and i32 %38, 12
  %40 = icmp ne i32 %39, 0
  br i1 %40, label %41, label %44

; <label>:41:                                     ; preds = %37, %34
  %42 = load i32, i32* %21, align 4
  %43 = add i32 %42, -1
  store i32 %43, i32* %21, align 4
  br label %44

; <label>:44:                                     ; preds = %41, %37, %30, %27
  br label %45

; <label>:45:                                     ; preds = %55, %44
  %46 = load i64, i64* %17, align 8
  %47 = load i32, i32* %20, align 4
  %48 = zext i32 %47 to i64
  %49 = icmp ult i64 %46, %48
  br i1 %49, label %50, label %53

; <label>:50:                                     ; preds = %45
  %51 = load i64, i64* %17, align 8
  %52 = icmp ult i64 %51, 32
  br label %53

; <label>:53:                                     ; preds = %50, %45
  %54 = phi i1 [ false, %45 ], [ %52, %50 ]
  br i1 %54, label %55, label %60

; <label>:55:                                     ; preds = %53
  %56 = load i8*, i8** %16, align 8
  %57 = load i64, i64* %17, align 8
  %58 = add i64 %57, 1
  store i64 %58, i64* %17, align 8
  %59 = getelementptr inbounds i8, i8* %56, i64 %57
  store i8 48, i8* %59, align 1
  br label %45

; <label>:60:                                     ; preds = %53
  br label %61

; <label>:61:                                     ; preds = %75, %60
  %62 = load i32, i32* %22, align 4
  %63 = and i32 %62, 1
  %64 = icmp ne i32 %63, 0
  br i1 %64, label %65, label %73

; <label>:65:                                     ; preds = %61
  %66 = load i64, i64* %17, align 8
  %67 = load i32, i32* %21, align 4
  %68 = zext i32 %67 to i64
  %69 = icmp ult i64 %66, %68
  br i1 %69, label %70, label %73

; <label>:70:                                     ; preds = %65
  %71 = load i64, i64* %17, align 8
  %72 = icmp ult i64 %71, 32
  br label %73

; <label>:73:                                     ; preds = %70, %65, %61
  %74 = phi i1 [ false, %65 ], [ false, %61 ], [ %72, %70 ]
  br i1 %74, label %75, label %80

; <label>:75:                                     ; preds = %73
  %76 = load i8*, i8** %16, align 8
  %77 = load i64, i64* %17, align 8
  %78 = add i64 %77, 1
  store i64 %78, i64* %17, align 8
  %79 = getelementptr inbounds i8, i8* %76, i64 %77
  store i8 48, i8* %79, align 1
  br label %61

; <label>:80:                                     ; preds = %73
  br label %81

; <label>:81:                                     ; preds = %80, %11
  %82 = load i32, i32* %22, align 4
  %83 = and i32 %82, 16
  %84 = icmp ne i32 %83, 0
  br i1 %84, label %85, label %166

; <label>:85:                                     ; preds = %81
  %86 = load i32, i32* %22, align 4
  %87 = and i32 %86, 1024
  %88 = icmp ne i32 %87, 0
  br i1 %88, label %114, label %89

; <label>:89:                                     ; preds = %85
  %90 = load i64, i64* %17, align 8
  %91 = icmp ne i64 %90, 0
  br i1 %91, label %92, label %114

; <label>:92:                                     ; preds = %89
  %93 = load i64, i64* %17, align 8
  %94 = load i32, i32* %20, align 4
  %95 = zext i32 %94 to i64
  %96 = icmp eq i64 %93, %95
  br i1 %96, label %102, label %97

; <label>:97:                                     ; preds = %92
  %98 = load i64, i64* %17, align 8
  %99 = load i32, i32* %21, align 4
  %100 = zext i32 %99 to i64
  %101 = icmp eq i64 %98, %100
  br i1 %101, label %102, label %114

; <label>:102:                                    ; preds = %97, %92
  %103 = load i64, i64* %17, align 8
  %104 = add i64 %103, -1
  store i64 %104, i64* %17, align 8
  %105 = load i64, i64* %17, align 8
  %106 = icmp ne i64 %105, 0
  br i1 %106, label %107, label %113

; <label>:107:                                    ; preds = %102
  %108 = load i32, i32* %19, align 4
  %109 = icmp eq i32 %108, 16
  br i1 %109, label %110, label %113

; <label>:110:                                    ; preds = %107
  %111 = load i64, i64* %17, align 8
  %112 = add i64 %111, -1
  store i64 %112, i64* %17, align 8
  br label %113

; <label>:113:                                    ; preds = %110, %107, %102
  br label %114

; <label>:114:                                    ; preds = %113, %97, %89, %85
  %115 = load i32, i32* %19, align 4
  %116 = icmp eq i32 %115, 16
  br i1 %116, label %117, label %129

; <label>:117:                                    ; preds = %114
  %118 = load i32, i32* %22, align 4
  %119 = and i32 %118, 32
  %120 = icmp ne i32 %119, 0
  br i1 %120, label %129, label %121

; <label>:121:                                    ; preds = %117
  %122 = load i64, i64* %17, align 8
  %123 = icmp ult i64 %122, 32
  br i1 %123, label %124, label %129

; <label>:124:                                    ; preds = %121
  %125 = load i8*, i8** %16, align 8
  %126 = load i64, i64* %17, align 8
  %127 = add i64 %126, 1
  store i64 %127, i64* %17, align 8
  %128 = getelementptr inbounds i8, i8* %125, i64 %126
  store i8 120, i8* %128, align 1
  br label %157

; <label>:129:                                    ; preds = %121, %117, %114
  %130 = load i32, i32* %19, align 4
  %131 = icmp eq i32 %130, 16
  br i1 %131, label %132, label %144

; <label>:132:                                    ; preds = %129
  %133 = load i32, i32* %22, align 4
  %134 = and i32 %133, 32
  %135 = icmp ne i32 %134, 0
  br i1 %135, label %136, label %144

; <label>:136:                                    ; preds = %132
  %137 = load i64, i64* %17, align 8
  %138 = icmp ult i64 %137, 32
  br i1 %138, label %139, label %144

; <label>:139:                                    ; preds = %136
  %140 = load i8*, i8** %16, align 8
  %141 = load i64, i64* %17, align 8
  %142 = add i64 %141, 1
  store i64 %142, i64* %17, align 8
  %143 = getelementptr inbounds i8, i8* %140, i64 %141
  store i8 88, i8* %143, align 1
  br label %156

; <label>:144:                                    ; preds = %136, %132, %129
  %145 = load i32, i32* %19, align 4
  %146 = icmp eq i32 %145, 2
  br i1 %146, label %147, label %155

; <label>:147:                                    ; preds = %144
  %148 = load i64, i64* %17, align 8
  %149 = icmp ult i64 %148, 32
  br i1 %149, label %150, label %155

; <label>:150:                                    ; preds = %147
  %151 = load i8*, i8** %16, align 8
  %152 = load i64, i64* %17, align 8
  %153 = add i64 %152, 1
  store i64 %153, i64* %17, align 8
  %154 = getelementptr inbounds i8, i8* %151, i64 %152
  store i8 98, i8* %154, align 1
  br label %155

; <label>:155:                                    ; preds = %150, %147, %144
  br label %156

; <label>:156:                                    ; preds = %155, %139
  br label %157

; <label>:157:                                    ; preds = %156, %124
  %158 = load i64, i64* %17, align 8
  %159 = icmp ult i64 %158, 32
  br i1 %159, label %160, label %165

; <label>:160:                                    ; preds = %157
  %161 = load i8*, i8** %16, align 8
  %162 = load i64, i64* %17, align 8
  %163 = add i64 %162, 1
  store i64 %163, i64* %17, align 8
  %164 = getelementptr inbounds i8, i8* %161, i64 %162
  store i8 48, i8* %164, align 1
  br label %165

; <label>:165:                                    ; preds = %160, %157
  br label %166

; <label>:166:                                    ; preds = %165, %81
  %167 = load i64, i64* %17, align 8
  %168 = icmp ult i64 %167, 32
  br i1 %168, label %169, label %198

; <label>:169:                                    ; preds = %166
  %170 = load i8, i8* %18, align 1
  %171 = trunc i8 %170 to i1
  br i1 %171, label %172, label %177

; <label>:172:                                    ; preds = %169
  %173 = load i8*, i8** %16, align 8
  %174 = load i64, i64* %17, align 8
  %175 = add i64 %174, 1
  store i64 %175, i64* %17, align 8
  %176 = getelementptr inbounds i8, i8* %173, i64 %174
  store i8 45, i8* %176, align 1
  br label %197

; <label>:177:                                    ; preds = %169
  %178 = load i32, i32* %22, align 4
  %179 = and i32 %178, 4
  %180 = icmp ne i32 %179, 0
  br i1 %180, label %181, label %186

; <label>:181:                                    ; preds = %177
  %182 = load i8*, i8** %16, align 8
  %183 = load i64, i64* %17, align 8
  %184 = add i64 %183, 1
  store i64 %184, i64* %17, align 8
  %185 = getelementptr inbounds i8, i8* %182, i64 %183
  store i8 43, i8* %185, align 1
  br label %196

; <label>:186:                                    ; preds = %177
  %187 = load i32, i32* %22, align 4
  %188 = and i32 %187, 8
  %189 = icmp ne i32 %188, 0
  br i1 %189, label %190, label %195

; <label>:190:                                    ; preds = %186
  %191 = load i8*, i8** %16, align 8
  %192 = load i64, i64* %17, align 8
  %193 = add i64 %192, 1
  store i64 %193, i64* %17, align 8
  %194 = getelementptr inbounds i8, i8* %191, i64 %192
  store i8 32, i8* %194, align 1
  br label %195

; <label>:195:                                    ; preds = %190, %186
  br label %196

; <label>:196:                                    ; preds = %195, %181
  br label %197

; <label>:197:                                    ; preds = %196, %172
  br label %198

; <label>:198:                                    ; preds = %197, %166
  %199 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %12, align 8
  %200 = load i8*, i8** %13, align 8
  %201 = load i64, i64* %14, align 8
  %202 = load i64, i64* %15, align 8
  %203 = load i8*, i8** %16, align 8
  %204 = load i64, i64* %17, align 8
  %205 = load i32, i32* %21, align 4
  %206 = load i32, i32* %22, align 4
  %207 = call fastcc i64 @_out_rev(void (i8, i8*, i64, i64)* %199, i8* %200, i64 %201, i64 %202, i8* %203, i64 %204, i32 %205, i32 %206)
  ret i64 %207
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define internal fastcc i64 @_out_rev(void (i8, i8*, i64, i64)*, i8*, i64, i64, i8*, i64, i32, i32) unnamed_addr #0 {
  %9 = alloca void (i8, i8*, i64, i64)*, align 8
  %10 = alloca i8*, align 8
  %11 = alloca i64, align 8
  %12 = alloca i64, align 8
  %13 = alloca i8*, align 8
  %14 = alloca i64, align 8
  %15 = alloca i32, align 4
  %16 = alloca i32, align 4
  %17 = alloca i64, align 8
  %18 = alloca i64, align 8
  store void (i8, i8*, i64, i64)* %0, void (i8, i8*, i64, i64)** %9, align 8
  store i8* %1, i8** %10, align 8
  store i64 %2, i64* %11, align 8
  store i64 %3, i64* %12, align 8
  store i8* %4, i8** %13, align 8
  store i64 %5, i64* %14, align 8
  store i32 %6, i32* %15, align 4
  store i32 %7, i32* %16, align 4
  %19 = load i64, i64* %11, align 8
  store i64 %19, i64* %17, align 8
  %20 = load i32, i32* %16, align 4
  %21 = and i32 %20, 2
  %22 = icmp ne i32 %21, 0
  br i1 %22, label %44, label %23

; <label>:23:                                     ; preds = %8
  %24 = load i32, i32* %16, align 4
  %25 = and i32 %24, 1
  %26 = icmp ne i32 %25, 0
  br i1 %26, label %44, label %27

; <label>:27:                                     ; preds = %23
  %28 = load i64, i64* %14, align 8
  store i64 %28, i64* %18, align 8
  br label %29

; <label>:29:                                     ; preds = %40, %27
  %30 = load i64, i64* %18, align 8
  %31 = load i32, i32* %15, align 4
  %32 = zext i32 %31 to i64
  %33 = icmp ult i64 %30, %32
  br i1 %33, label %34, label %43

; <label>:34:                                     ; preds = %29
  %35 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %9, align 8
  %36 = load i8*, i8** %10, align 8
  %37 = load i64, i64* %11, align 8
  %38 = add i64 %37, 1
  store i64 %38, i64* %11, align 8
  %39 = load i64, i64* %12, align 8
  call void %35(i8 signext 32, i8* %36, i64 %37, i64 %39)
  br label %40

; <label>:40:                                     ; preds = %34
  %41 = load i64, i64* %18, align 8
  %42 = add i64 %41, 1
  store i64 %42, i64* %18, align 8
  br label %29

; <label>:43:                                     ; preds = %29
  br label %44

; <label>:44:                                     ; preds = %43, %23, %8
  br label %45

; <label>:45:                                     ; preds = %48, %44
  %46 = load i64, i64* %14, align 8
  %47 = icmp ne i64 %46, 0
  br i1 %47, label %48, label %59

; <label>:48:                                     ; preds = %45
  %49 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %9, align 8
  %50 = load i8*, i8** %13, align 8
  %51 = load i64, i64* %14, align 8
  %52 = add i64 %51, -1
  store i64 %52, i64* %14, align 8
  %53 = getelementptr inbounds i8, i8* %50, i64 %52
  %54 = load i8, i8* %53, align 1
  %55 = load i8*, i8** %10, align 8
  %56 = load i64, i64* %11, align 8
  %57 = add i64 %56, 1
  store i64 %57, i64* %11, align 8
  %58 = load i64, i64* %12, align 8
  call void %49(i8 signext %54, i8* %55, i64 %56, i64 %58)
  br label %45

; <label>:59:                                     ; preds = %45
  %60 = load i32, i32* %16, align 4
  %61 = and i32 %60, 2
  %62 = icmp ne i32 %61, 0
  br i1 %62, label %63, label %78

; <label>:63:                                     ; preds = %59
  br label %64

; <label>:64:                                     ; preds = %71, %63
  %65 = load i64, i64* %11, align 8
  %66 = load i64, i64* %17, align 8
  %67 = sub i64 %65, %66
  %68 = load i32, i32* %15, align 4
  %69 = zext i32 %68 to i64
  %70 = icmp ult i64 %67, %69
  br i1 %70, label %71, label %77

; <label>:71:                                     ; preds = %64
  %72 = load void (i8, i8*, i64, i64)*, void (i8, i8*, i64, i64)** %9, align 8
  %73 = load i8*, i8** %10, align 8
  %74 = load i64, i64* %11, align 8
  %75 = add i64 %74, 1
  store i64 %75, i64* %11, align 8
  %76 = load i64, i64* %12, align 8
  call void %72(i8 signext 32, i8* %73, i64 %74, i64 %76)
  br label %64

; <label>:77:                                     ; preds = %64
  br label %78

; <label>:78:                                     ; preds = %77, %59
  %79 = load i64, i64* %11, align 8
  ret i64 %79
}

declare void @_putchar(i8 signext) local_unnamed_addr #2

attributes #0 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { nounwind }
attributes #2 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}
