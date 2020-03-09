; Function Attrs: noinline nounwind optnone ssp uwtable
define i32 @fat_newfile(i32, i8*, i32, i32, %struct.times_t*, %struct.dir_t**, i64*, %struct.dir_t**, i64*, i32) #0 {
  %11 = alloca i32, align 4
  %12 = alloca i32, align 4
  %13 = alloca i8*, align 8
  %14 = alloca i32, align 4
  %15 = alloca i32, align 4
  %16 = alloca %struct.times_t*, align 8
  %17 = alloca %struct.dir_t**, align 8
  %18 = alloca i64*, align 8
  %19 = alloca %struct.dir_t**, align 8
  %20 = alloca i64*, align 8
  %21 = alloca i32, align 4
  %22 = alloca %struct.dir_t*, align 8
  %23 = alloca i64, align 8
  %24 = alloca i8*, align 8
  %25 = alloca i32, align 4
  %26 = alloca i32, align 4
  %27 = alloca i64, align 8
  %28 = alloca %struct.dir_t, align 8
  %29 = alloca i32, align 4
  %30 = alloca i32, align 4
  %31 = alloca %struct.dir_t*, align 8
  %32 = alloca i64*, align 8
  %33 = alloca i64, align 8
  %34 = alloca i32, align 4
  %35 = alloca i64, align 8
  %36 = alloca i64, align 8
  %37 = alloca i64, align 8
  %38 = alloca i64, align 8
  %39 = alloca i64, align 8
  %40 = alloca i32, align 4
  %41 = alloca i64, align 8
  %42 = alloca i32, align 4
  %43 = alloca i32, align 4
  %44 = alloca i32, align 4
  %45 = alloca i32, align 4
  %46 = alloca i32, align 4
  %47 = alloca i32, align 4
  %48 = alloca %struct.pathc_t*, align 8
  %49 = alloca %struct.dir_t*, align 8
  store i32 %0, i32* %12, align 4
  store i8* %1, i8** %13, align 8
  store i32 %2, i32* %14, align 4
  store i32 %3, i32* %15, align 4
  store %struct.times_t* %4, %struct.times_t** %16, align 8
  store %struct.dir_t** %5, %struct.dir_t*** %17, align 8
  store i64* %6, i64** %18, align 8
  store %struct.dir_t** %7, %struct.dir_t*** %19, align 8
  store i64* %8, i64** %20, align 8
  store i32 %9, i32* %21, align 4
  %50 = load i32, i32* @debug_disable_method, align 4
  %51 = or i32 %50, 16
  store i32 %51, i32* @debug_disable_method, align 4
  call void @indent(i32 1)
  %52 = load i8*, i8** %13, align 8
  call void @dbg2(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 900, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([29 x i8], [29 x i8]* @.str.93, i32 0, i32 0), i8* %52)
  store i64 0, i64* %23, align 8
  store i8* null, i8** %24, align 8
  %53 = load i32, i32* %12, align 4
  %54 = load i8*, i8** %13, align 8
  %55 = call i32 @fat_find(i32 %53, i64 -1, i8* %54, %struct.dir_t* null, %struct.dir_t** %22, i64* %23, i32 1, i8** %24)
  store i32 %55, i32* %25, align 4
  %56 = load i32, i32* %25, align 4
  %57 = icmp eq i32 %56, 1
  %58 = zext i1 %57 to i32
  store i32 %58, i32* %26, align 4
  %59 = load i32, i32* %25, align 4
  %60 = icmp slt i32 %59, 0
  br i1 %60, label %61, label %98

; <label>:61:                                     ; preds = %10
  %62 = load i32, i32* %25, align 4
  %63 = icmp ne i32 %62, -2
  br i1 %63, label %64, label %98

; <label>:64:                                     ; preds = %61
  %65 = load i32, i32* %25, align 4
  %66 = icmp slt i32 %65, 0
  br i1 %66, label %67, label %97

; <label>:67:                                     ; preds = %64
  store i32 1, i32* @debug_enable, align 4
  %68 = load i32, i32* @debug_enable, align 4
  %69 = icmp eq i32 %68, 1
  br i1 %69, label %70, label %95

; <label>:70:                                     ; preds = %67
  %71 = load i32, i32* @debug_disable_method, align 4
  %72 = icmp eq i32 %71, 0
  br i1 %72, label %73, label %95

; <label>:73:                                     ; preds = %70
  %74 = load i32, i32* @debug_disable_external, align 4
  %75 = icmp ne i32 %74, 1
  br i1 %75, label %76, label %95

; <label>:76:                                     ; preds = %73
  %77 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %78 = icmp ne %struct.__sFILE* %77, null
  br i1 %78, label %79, label %95

; <label>:79:                                     ; preds = %76
  %80 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %81 = load i32, i32* %25, align 4
  %82 = load i32, i32* %25, align 4
  %83 = icmp slt i32 %82, 0
  br i1 %83, label %84, label %87

; <label>:84:                                     ; preds = %79
  %85 = load i32, i32* %25, align 4
  %86 = sub nsw i32 0, %85
  br label %89

; <label>:87:                                     ; preds = %79
  %88 = load i32, i32* %25, align 4
  br label %89

; <label>:89:                                     ; preds = %87, %84
  %90 = phi i32 [ %86, %84 ], [ %88, %87 ]
  %91 = call i8* @"\01_strerror"(i32 %90)
  %92 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %80, i8* getelementptr inbounds ([142 x i8], [142 x i8]* @.str.94, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 910, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %81, i8* %91)
  %93 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %94 = call i32 @fflush(%struct.__sFILE* %93)
  br label %95

; <label>:95:                                     ; preds = %89, %76, %73, %70, %67
  %96 = load i32, i32* %25, align 4
  store i32 %96, i32* %11, align 4
  br label %1022

; <label>:97:                                     ; preds = %64
  br label %98

; <label>:98:                                     ; preds = %97, %61, %10
  %99 = load i8*, i8** %24, align 8
  %100 = call i64 @strlen(i8* %99)
  store i64 %100, i64* %27, align 8
  %101 = load i64, i64* %27, align 8
  %102 = icmp ugt i64 %101, 24
  br i1 %102, label %103, label %135

; <label>:103:                                    ; preds = %98
  %104 = load i32, i32* @debug_enable, align 4
  %105 = icmp eq i32 %104, 1
  br i1 %105, label %106, label %121

; <label>:106:                                    ; preds = %103
  %107 = load i32, i32* @debug_disable_method, align 4
  %108 = icmp eq i32 %107, 0
  br i1 %108, label %109, label %121

; <label>:109:                                    ; preds = %106
  %110 = load i32, i32* @debug_disable_external, align 4
  %111 = icmp ne i32 %110, 1
  br i1 %111, label %112, label %121

; <label>:112:                                    ; preds = %109
  %113 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %114 = icmp ne %struct.__sFILE* %113, null
  br i1 %114, label %115, label %121

; <label>:115:                                    ; preds = %112
  %116 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %117 = load i8*, i8** %24, align 8
  %118 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %116, i8* getelementptr inbounds ([170 x i8], [170 x i8]* @.str.95, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 917, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %117)
  %119 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %120 = call i32 @fflush(%struct.__sFILE* %119)
  br label %121

; <label>:121:                                    ; preds = %115, %112, %109, %106, %103
  %122 = load i8*, i8** %24, align 8
  %123 = icmp ne i8* %122, null
  br i1 %123, label %124, label %126

; <label>:124:                                    ; preds = %121
  %125 = load i8*, i8** %24, align 8
  call void @free(i8* %125)
  store i8* null, i8** %24, align 8
  br label %126

; <label>:126:                                    ; preds = %124, %121
  %127 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %128 = icmp ne %struct.dir_t* %127, null
  br i1 %128, label %129, label %132

; <label>:129:                                    ; preds = %126
  %130 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %131 = bitcast %struct.dir_t* %130 to i8*
  call void @free(i8* %131)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %132

; <label>:132:                                    ; preds = %129, %126
  %133 = load i32, i32* @debug_disable_method, align 4
  %134 = and i32 %133, -17
  store i32 %134, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -63, i32* %11, align 4
  br label %1022

; <label>:135:                                    ; preds = %98
  %136 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 0
  %137 = bitcast %union.fname_u* %136 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %137, i8 0, i64 24, i1 false)
  %138 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 1
  %139 = load %struct.times_t*, %struct.times_t** %16, align 8
  %140 = icmp eq %struct.times_t* %139, null
  br i1 %140, label %141, label %142

; <label>:141:                                    ; preds = %135
  call void (%struct.times_t*, ...) @gettimes(%struct.times_t* sret %138)
  br label %146

; <label>:142:                                    ; preds = %135
  %143 = load %struct.times_t*, %struct.times_t** %16, align 8
  %144 = bitcast %struct.times_t* %138 to i8*
  %145 = bitcast %struct.times_t* %143 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %144, i8* align 8 %145, i64 24, i1 false)
  br label %146

; <label>:146:                                    ; preds = %142, %141
  %147 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 2
  %148 = load i32, i32* %14, align 4
  store i32 %148, i32* %147, align 8
  %149 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  store i32 0, i32* %149, align 4
  %150 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 4
  %151 = load i32, i32* %15, align 4
  store i32 %151, i32* %150, align 8
  %152 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 5
  store i32 0, i32* %152, align 4
  %153 = call i32 @fat_find_free_block()
  store i32 %153, i32* %29, align 4
  %154 = load i32, i32* %21, align 4
  %155 = icmp ne i32 %154, 0
  br i1 %155, label %156, label %158

; <label>:156:                                    ; preds = %146
  %157 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  store i32 0, i32* %157, align 4
  br label %226

; <label>:158:                                    ; preds = %146
  %159 = load i32, i32* %29, align 4
  %160 = icmp eq i32 %159, -1
  br i1 %160, label %161, label %192

; <label>:161:                                    ; preds = %158
  %162 = load i32, i32* @debug_enable, align 4
  %163 = icmp eq i32 %162, 1
  br i1 %163, label %164, label %178

; <label>:164:                                    ; preds = %161
  %165 = load i32, i32* @debug_disable_method, align 4
  %166 = icmp eq i32 %165, 0
  br i1 %166, label %167, label %178

; <label>:167:                                    ; preds = %164
  %168 = load i32, i32* @debug_disable_external, align 4
  %169 = icmp ne i32 %168, 1
  br i1 %169, label %170, label %178

; <label>:170:                                    ; preds = %167
  %171 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %172 = icmp ne %struct.__sFILE* %171, null
  br i1 %172, label %173, label %178

; <label>:173:                                    ; preds = %170
  %174 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %175 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %174, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 940, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([43 x i8], [43 x i8]* @.str.96, i32 0, i32 0))
  %176 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %177 = call i32 @fflush(%struct.__sFILE* %176)
  br label %178

; <label>:178:                                    ; preds = %173, %170, %167, %164, %161
  %179 = load i8*, i8** %24, align 8
  %180 = icmp ne i8* %179, null
  br i1 %180, label %181, label %183

; <label>:181:                                    ; preds = %178
  %182 = load i8*, i8** %24, align 8
  call void @free(i8* %182)
  store i8* null, i8** %24, align 8
  br label %183

; <label>:183:                                    ; preds = %181, %178
  %184 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %185 = icmp ne %struct.dir_t* %184, null
  br i1 %185, label %186, label %189

; <label>:186:                                    ; preds = %183
  %187 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %188 = bitcast %struct.dir_t* %187 to i8*
  call void @free(i8* %188)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %189

; <label>:189:                                    ; preds = %186, %183
  %190 = load i32, i32* @debug_disable_method, align 4
  %191 = and i32 %190, -17
  store i32 %191, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:192:                                    ; preds = %158
  %193 = load i32, i32* @debug_enable, align 4
  %194 = icmp eq i32 %193, 1
  br i1 %194, label %195, label %211

; <label>:195:                                    ; preds = %192
  %196 = load i32, i32* @debug_disable_method, align 4
  %197 = icmp eq i32 %196, 0
  br i1 %197, label %198, label %211

; <label>:198:                                    ; preds = %195
  %199 = load i32, i32* @debug_disable_external, align 4
  %200 = icmp ne i32 %199, 1
  br i1 %200, label %201, label %211

; <label>:201:                                    ; preds = %198
  %202 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %203 = icmp ne %struct.__sFILE* %202, null
  br i1 %203, label %204, label %211

; <label>:204:                                    ; preds = %201
  %205 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %206 = load i8*, i8** %13, align 8
  %207 = load i32, i32* %29, align 4
  %208 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %205, i8* getelementptr inbounds ([152 x i8], [152 x i8]* @.str.97, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 946, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %206, i32 %207)
  %209 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %210 = call i32 @fflush(%struct.__sFILE* %209)
  br label %211

; <label>:211:                                    ; preds = %204, %201, %198, %195, %192
  %212 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %213 = load i32, i32* %29, align 4
  %214 = sext i32 %213 to i64
  %215 = getelementptr inbounds i32, i32* %212, i64 %214
  store i32 -2, i32* %215, align 4
  %216 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %217 = add nsw i64 %216, -1
  store i64 %217, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %218 = load i32, i32* %29, align 4
  %219 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  store i32 %218, i32* %219, align 4
  %220 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 0
  %221 = bitcast %union.fname_u* %220 to [24 x i8]*
  %222 = getelementptr inbounds [24 x i8], [24 x i8]* %221, i32 0, i32 0
  %223 = load i8*, i8** %24, align 8
  %224 = load i64, i64* %27, align 8
  %225 = call i8* @__memcpy_chk(i8* %222, i8* %223, i64 %224, i64 64) #7
  br label %226

; <label>:226:                                    ; preds = %211, %156
  %227 = load i8*, i8** %24, align 8
  %228 = icmp ne i8* %227, null
  br i1 %228, label %229, label %231

; <label>:229:                                    ; preds = %226
  %230 = load i8*, i8** %24, align 8
  call void @free(i8* %230)
  store i8* null, i8** %24, align 8
  br label %231

; <label>:231:                                    ; preds = %229, %226
  %232 = load i32, i32* %29, align 4
  store i32 %232, i32* %30, align 4
  %233 = load i32, i32* %12, align 4
  %234 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %235 = call i32 @fat_read_dir(i32 %233, %struct.dir_t* %234, %struct.dir_t** %31, i64** %32, i64* %33, i32* %34)
  store i32 %235, i32* %25, align 4
  store i64 -1, i64* %35, align 8
  store i64 -1, i64* %36, align 8
  %236 = load i32, i32* %34, align 4
  %237 = sext i32 %236 to i64
  store i64 %237, i64* %37, align 8
  br label %238

; <label>:238:                                    ; preds = %285, %231
  %239 = load i64, i64* %37, align 8
  %240 = load i64, i64* %33, align 8
  %241 = icmp ult i64 %239, %240
  br i1 %241, label %242, label %288

; <label>:242:                                    ; preds = %238
  %243 = load %struct.dir_t*, %struct.dir_t** %31, align 8
  %244 = load i64, i64* %37, align 8
  %245 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %243, i64 %244
  %246 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %245, i32 0, i32 3
  %247 = load i32, i32* %246, align 4
  %248 = icmp eq i32 %247, 0
  br i1 %248, label %260, label %249

; <label>:249:                                    ; preds = %242
  %250 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %251 = load %struct.dir_t*, %struct.dir_t** %31, align 8
  %252 = load i64, i64* %37, align 8
  %253 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %251, i64 %252
  %254 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %253, i32 0, i32 3
  %255 = load i32, i32* %254, align 4
  %256 = sext i32 %255 to i64
  %257 = getelementptr inbounds i32, i32* %250, i64 %256
  %258 = load i32, i32* %257, align 4
  %259 = icmp eq i32 %258, 0
  br i1 %259, label %260, label %284

; <label>:260:                                    ; preds = %249, %242
  %261 = load i64*, i64** %32, align 8
  %262 = load i64, i64* %37, align 8
  %263 = getelementptr inbounds i64, i64* %261, i64 %262
  %264 = load i64, i64* %263, align 8
  store i64 %264, i64* %35, align 8
  %265 = load i64, i64* %37, align 8
  store i64 %265, i64* %36, align 8
  %266 = load i32, i32* @debug_enable, align 4
  %267 = icmp eq i32 %266, 1
  br i1 %267, label %268, label %283

; <label>:268:                                    ; preds = %260
  %269 = load i32, i32* @debug_disable_method, align 4
  %270 = icmp eq i32 %269, 0
  br i1 %270, label %271, label %283

; <label>:271:                                    ; preds = %268
  %272 = load i32, i32* @debug_disable_external, align 4
  %273 = icmp ne i32 %272, 1
  br i1 %273, label %274, label %283

; <label>:274:                                    ; preds = %271
  %275 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %276 = icmp ne %struct.__sFILE* %275, null
  br i1 %276, label %277, label %283

; <label>:277:                                    ; preds = %274
  %278 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %279 = load i64, i64* %35, align 8
  %280 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %278, i8* getelementptr inbounds ([160 x i8], [160 x i8]* @.str.98, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 976, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %279)
  %281 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %282 = call i32 @fflush(%struct.__sFILE* %281)
  br label %283

; <label>:283:                                    ; preds = %277, %274, %271, %268, %260
  br label %288

; <label>:284:                                    ; preds = %249
  br label %285

; <label>:285:                                    ; preds = %284
  %286 = load i64, i64* %37, align 8
  %287 = add i64 %286, 1
  store i64 %287, i64* %37, align 8
  br label %238

; <label>:288:                                    ; preds = %283, %238
  %289 = load %struct.dir_t*, %struct.dir_t** %31, align 8
  %290 = icmp ne %struct.dir_t* %289, null
  br i1 %290, label %291, label %294

; <label>:291:                                    ; preds = %288
  %292 = load %struct.dir_t*, %struct.dir_t** %31, align 8
  %293 = bitcast %struct.dir_t* %292 to i8*
  call void @free(i8* %293)
  store %struct.dir_t* null, %struct.dir_t** %31, align 8
  br label %294

; <label>:294:                                    ; preds = %291, %288
  %295 = load i64*, i64** %32, align 8
  %296 = icmp ne i64* %295, null
  br i1 %296, label %297, label %300

; <label>:297:                                    ; preds = %294
  %298 = load i64*, i64** %32, align 8
  %299 = bitcast i64* %298 to i8*
  call void @free(i8* %299)
  store i64* null, i64** %32, align 8
  br label %300

; <label>:300:                                    ; preds = %297, %294
  %301 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %302 = zext i32 %301 to i64
  store i64 %302, i64* %38, align 8
  %303 = load i32, i32* %14, align 4
  %304 = zext i32 %303 to i64
  %305 = load i64, i64* %38, align 8
  %306 = call i64 @updiv(i64 %304, i64 %305)
  store i64 %306, i64* %39, align 8
  store i32 1, i32* %40, align 4
  %307 = load i64, i64* %35, align 8
  %308 = icmp ne i64 %307, -1
  br i1 %308, label %309, label %402

; <label>:309:                                    ; preds = %300
  %310 = load i32, i32* @debug_enable, align 4
  %311 = icmp eq i32 %310, 1
  br i1 %311, label %312, label %326

; <label>:312:                                    ; preds = %309
  %313 = load i32, i32* @debug_disable_method, align 4
  %314 = icmp eq i32 %313, 0
  br i1 %314, label %315, label %326

; <label>:315:                                    ; preds = %312
  %316 = load i32, i32* @debug_disable_external, align 4
  %317 = icmp ne i32 %316, 1
  br i1 %317, label %318, label %326

; <label>:318:                                    ; preds = %315
  %319 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %320 = icmp ne %struct.__sFILE* %319, null
  br i1 %320, label %321, label %326

; <label>:321:                                    ; preds = %318
  %322 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %323 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %322, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 998, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.100, i32 0, i32 0))
  %324 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %325 = call i32 @fflush(%struct.__sFILE* %324)
  br label %326

; <label>:326:                                    ; preds = %321, %318, %315, %312, %309
  %327 = load i32, i32* %12, align 4
  %328 = load i64, i64* %35, align 8
  %329 = call i32 @fat_write_entry(i32 %327, %struct.dir_t* %28, i64 %328)
  store i32 %329, i32* %25, align 4
  %330 = load i32, i32* %25, align 4
  %331 = icmp slt i32 %330, 0
  br i1 %331, label %332, label %362

; <label>:332:                                    ; preds = %326
  store i32 1, i32* @debug_enable, align 4
  %333 = load i32, i32* @debug_enable, align 4
  %334 = icmp eq i32 %333, 1
  br i1 %334, label %335, label %360

; <label>:335:                                    ; preds = %332
  %336 = load i32, i32* @debug_disable_method, align 4
  %337 = icmp eq i32 %336, 0
  br i1 %337, label %338, label %360

; <label>:338:                                    ; preds = %335
  %339 = load i32, i32* @debug_disable_external, align 4
  %340 = icmp ne i32 %339, 1
  br i1 %340, label %341, label %360

; <label>:341:                                    ; preds = %338
  %342 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %343 = icmp ne %struct.__sFILE* %342, null
  br i1 %343, label %344, label %360

; <label>:344:                                    ; preds = %341
  %345 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %346 = load i32, i32* %25, align 4
  %347 = load i32, i32* %25, align 4
  %348 = icmp slt i32 %347, 0
  br i1 %348, label %349, label %352

; <label>:349:                                    ; preds = %344
  %350 = load i32, i32* %25, align 4
  %351 = sub nsw i32 0, %350
  br label %354

; <label>:352:                                    ; preds = %344
  %353 = load i32, i32* %25, align 4
  br label %354

; <label>:354:                                    ; preds = %352, %349
  %355 = phi i32 [ %351, %349 ], [ %353, %352 ]
  %356 = call i8* @"\01_strerror"(i32 %355)
  %357 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %345, i8* getelementptr inbounds ([165 x i8], [165 x i8]* @.str.101, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1000, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %346, i8* %356)
  %358 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %359 = call i32 @fflush(%struct.__sFILE* %358)
  br label %360

; <label>:360:                                    ; preds = %354, %341, %338, %335, %332
  %361 = load i32, i32* %25, align 4
  store i32 %361, i32* %11, align 4
  br label %1022

; <label>:362:                                    ; preds = %326
  %363 = load i32, i32* @debug_enable, align 4
  %364 = icmp eq i32 %363, 1
  br i1 %364, label %365, label %392

; <label>:365:                                    ; preds = %362
  %366 = load i32, i32* @debug_disable_method, align 4
  %367 = icmp eq i32 %366, 0
  br i1 %367, label %368, label %392

; <label>:368:                                    ; preds = %365
  %369 = load i32, i32* @debug_disable_external, align 4
  %370 = icmp ne i32 %369, 1
  br i1 %370, label %371, label %392

; <label>:371:                                    ; preds = %368
  %372 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %373 = icmp ne %struct.__sFILE* %372, null
  br i1 %373, label %374, label %392

; <label>:374:                                    ; preds = %371
  %375 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %376 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %377 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %376, i32 0, i32 2
  %378 = load i32, i32* %377, align 8
  %379 = load i64, i64* %36, align 8
  %380 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %381 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %380, i32 0, i32 2
  %382 = load i32, i32* %381, align 8
  %383 = zext i32 %382 to i64
  %384 = udiv i64 %383, 64
  %385 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %386 = icmp eq %struct.dir_t* %385, getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 4)
  %387 = zext i1 %386 to i64
  %388 = select i1 %386, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.103, i32 0, i32 0), i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.104, i32 0, i32 0)
  %389 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %375, i8* getelementptr inbounds ([264 x i8], [264 x i8]* @.str.102, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1003, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %378, i64 %379, i64 %384, i8* %388)
  %390 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %391 = call i32 @fflush(%struct.__sFILE* %390)
  br label %392

; <label>:392:                                    ; preds = %374, %371, %368, %365, %362
  %393 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %394 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %393, i32 0, i32 2
  %395 = load i32, i32* %394, align 8
  %396 = zext i32 %395 to i64
  %397 = udiv i64 %396, 64
  %398 = load i64, i64* %36, align 8
  %399 = icmp ugt i64 %397, %398
  br i1 %399, label %400, label %401

; <label>:400:                                    ; preds = %392
  store i32 0, i32* %40, align 4
  br label %401

; <label>:401:                                    ; preds = %400, %392
  br label %811

; <label>:402:                                    ; preds = %300
  %403 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %404 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %403, i32 0, i32 2
  %405 = load i32, i32* %404, align 8
  %406 = zext i32 %405 to i64
  %407 = load i64, i64* %38, align 8
  %408 = sub i64 %407, 64
  %409 = icmp ule i64 %406, %408
  br i1 %409, label %410, label %512

; <label>:410:                                    ; preds = %402
  %411 = load i32, i32* @debug_enable, align 4
  %412 = icmp eq i32 %411, 1
  br i1 %412, label %413, label %427

; <label>:413:                                    ; preds = %410
  %414 = load i32, i32* @debug_disable_method, align 4
  %415 = icmp eq i32 %414, 0
  br i1 %415, label %416, label %427

; <label>:416:                                    ; preds = %413
  %417 = load i32, i32* @debug_disable_external, align 4
  %418 = icmp ne i32 %417, 1
  br i1 %418, label %419, label %427

; <label>:419:                                    ; preds = %416
  %420 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %421 = icmp ne %struct.__sFILE* %420, null
  br i1 %421, label %422, label %427

; <label>:422:                                    ; preds = %419
  %423 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %424 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %423, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1010, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.105, i32 0, i32 0))
  %425 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %426 = call i32 @fflush(%struct.__sFILE* %425)
  br label %427

; <label>:427:                                    ; preds = %422, %419, %416, %413, %410
  %428 = load i32, i32* %21, align 4
  %429 = icmp ne i32 %428, 0
  br i1 %429, label %464, label %430

; <label>:430:                                    ; preds = %427
  %431 = load i64, i64* %39, align 8
  %432 = call i32 @fat_has_free(i64 %431)
  %433 = icmp ne i32 %432, 0
  br i1 %433, label %464, label %434

; <label>:434:                                    ; preds = %430
  %435 = load i32, i32* @debug_enable, align 4
  %436 = icmp eq i32 %435, 1
  br i1 %436, label %437, label %451

; <label>:437:                                    ; preds = %434
  %438 = load i32, i32* @debug_disable_method, align 4
  %439 = icmp eq i32 %438, 0
  br i1 %439, label %440, label %451

; <label>:440:                                    ; preds = %437
  %441 = load i32, i32* @debug_disable_external, align 4
  %442 = icmp ne i32 %441, 1
  br i1 %442, label %443, label %451

; <label>:443:                                    ; preds = %440
  %444 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %445 = icmp ne %struct.__sFILE* %444, null
  br i1 %445, label %446, label %451

; <label>:446:                                    ; preds = %443
  %447 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %448 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %447, i8* getelementptr inbounds ([147 x i8], [147 x i8]* @.str.106, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1015, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.107, i32 0, i32 0))
  %449 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %450 = call i32 @fflush(%struct.__sFILE* %449)
  br label %451

; <label>:451:                                    ; preds = %446, %443, %440, %437, %434
  %452 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %453 = load i32, i32* %30, align 4
  %454 = sext i32 %453 to i64
  %455 = getelementptr inbounds i32, i32* %452, i64 %454
  store i32 0, i32* %455, align 4
  %456 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %457 = icmp ne %struct.dir_t* %456, null
  br i1 %457, label %458, label %461

; <label>:458:                                    ; preds = %451
  %459 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %460 = bitcast %struct.dir_t* %459 to i8*
  call void @free(i8* %460)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %461

; <label>:461:                                    ; preds = %458, %451
  %462 = load i32, i32* @debug_disable_method, align 4
  %463 = and i32 %462, -17
  store i32 %463, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:464:                                    ; preds = %430, %427
  %465 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %466 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %465, i32 0, i32 3
  %467 = load i32, i32* %466, align 4
  %468 = sext i32 %467 to i64
  %469 = load i64, i64* %38, align 8
  %470 = mul i64 %468, %469
  %471 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %472 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %471, i32 0, i32 2
  %473 = load i32, i32* %472, align 8
  %474 = zext i32 %473 to i64
  %475 = add i64 %470, %474
  store i64 %475, i64* %35, align 8
  %476 = load i32, i32* %12, align 4
  %477 = load i64, i64* %35, align 8
  %478 = call i32 @fat_write_entry(i32 %476, %struct.dir_t* %28, i64 %477)
  store i32 %478, i32* %25, align 4
  %479 = load i32, i32* %25, align 4
  %480 = icmp slt i32 %479, 0
  br i1 %480, label %481, label %511

; <label>:481:                                    ; preds = %464
  store i32 1, i32* @debug_enable, align 4
  %482 = load i32, i32* @debug_enable, align 4
  %483 = icmp eq i32 %482, 1
  br i1 %483, label %484, label %509

; <label>:484:                                    ; preds = %481
  %485 = load i32, i32* @debug_disable_method, align 4
  %486 = icmp eq i32 %485, 0
  br i1 %486, label %487, label %509

; <label>:487:                                    ; preds = %484
  %488 = load i32, i32* @debug_disable_external, align 4
  %489 = icmp ne i32 %488, 1
  br i1 %489, label %490, label %509

; <label>:490:                                    ; preds = %487
  %491 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %492 = icmp ne %struct.__sFILE* %491, null
  br i1 %492, label %493, label %509

; <label>:493:                                    ; preds = %490
  %494 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %495 = load i32, i32* %25, align 4
  %496 = load i32, i32* %25, align 4
  %497 = icmp slt i32 %496, 0
  br i1 %497, label %498, label %501

; <label>:498:                                    ; preds = %493
  %499 = load i32, i32* %25, align 4
  %500 = sub nsw i32 0, %499
  br label %503

; <label>:501:                                    ; preds = %493
  %502 = load i32, i32* %25, align 4
  br label %503

; <label>:503:                                    ; preds = %501, %498
  %504 = phi i32 [ %500, %498 ], [ %502, %501 ]
  %505 = call i8* @"\01_strerror"(i32 %504)
  %506 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %494, i8* getelementptr inbounds ([165 x i8], [165 x i8]* @.str.101, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1025, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %495, i8* %505)
  %507 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %508 = call i32 @fflush(%struct.__sFILE* %507)
  br label %509

; <label>:509:                                    ; preds = %503, %490, %487, %484, %481
  %510 = load i32, i32* %25, align 4
  store i32 %510, i32* %11, align 4
  br label %1022

; <label>:511:                                    ; preds = %464
  br label %810

; <label>:512:                                    ; preds = %402
  %513 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %514 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %513, i32 0, i32 2
  %515 = load i32, i32* %514, align 8
  %516 = zext i32 %515 to i64
  store i64 %516, i64* %41, align 8
  %517 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %518 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %517, i32 0, i32 3
  %519 = load i32, i32* %518, align 4
  store i32 %519, i32* %42, align 4
  %520 = load i32, i32* %42, align 4
  %521 = sext i32 %520 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1033, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([20 x i8], [20 x i8]* @.str.108, i32 0, i32 0), i64 %521)
  store i32 0, i32* %43, align 4
  br label %522

; <label>:522:                                    ; preds = %541, %512
  %523 = load i64, i64* %38, align 8
  %524 = load i64, i64* %41, align 8
  %525 = icmp ult i64 %523, %524
  br i1 %525, label %526, label %542

; <label>:526:                                    ; preds = %522
  %527 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %528 = load i32, i32* %42, align 4
  %529 = sext i32 %528 to i64
  %530 = getelementptr inbounds i32, i32* %527, i64 %529
  %531 = load i32, i32* %530, align 4
  store i32 %531, i32* %42, align 4
  %532 = load i64, i64* %38, align 8
  %533 = load i64, i64* %41, align 8
  %534 = sub i64 %533, %532
  store i64 %534, i64* %41, align 8
  %535 = load i32, i32* %43, align 4
  %536 = add nsw i32 %535, 1
  store i32 %536, i32* %43, align 4
  %537 = icmp sle i32 %536, 4
  br i1 %537, label %538, label %541

; <label>:538:                                    ; preds = %526
  %539 = load i32, i32* %42, align 4
  %540 = sext i32 %539 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1039, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.109, i32 0, i32 0), i64 %540)
  br label %541

; <label>:541:                                    ; preds = %538, %526
  br label %522

; <label>:542:                                    ; preds = %522
  %543 = load i32, i32* %43, align 4
  %544 = icmp sgt i32 %543, 4
  br i1 %544, label %545, label %564

; <label>:545:                                    ; preds = %542
  %546 = load i32, i32* @debug_enable, align 4
  %547 = icmp eq i32 %546, 1
  br i1 %547, label %548, label %563

; <label>:548:                                    ; preds = %545
  %549 = load i32, i32* @debug_disable_method, align 4
  %550 = icmp eq i32 %549, 0
  br i1 %550, label %551, label %563

; <label>:551:                                    ; preds = %548
  %552 = load i32, i32* @debug_disable_external, align 4
  %553 = icmp ne i32 %552, 1
  br i1 %553, label %554, label %563

; <label>:554:                                    ; preds = %551
  %555 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %556 = icmp ne %struct.__sFILE* %555, null
  br i1 %556, label %557, label %563

; <label>:557:                                    ; preds = %554
  %558 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %559 = load i32, i32* %43, align 4
  %560 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %558, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.110, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1043, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %559)
  %561 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %562 = call i32 @fflush(%struct.__sFILE* %561)
  br label %563

; <label>:563:                                    ; preds = %557, %554, %551, %548, %545
  br label %564

; <label>:564:                                    ; preds = %563, %542
  %565 = load i32, i32* @debug_enable, align 4
  %566 = icmp eq i32 %565, 1
  br i1 %566, label %567, label %586

; <label>:567:                                    ; preds = %564
  %568 = load i32, i32* @debug_disable_method, align 4
  %569 = icmp eq i32 %568, 0
  br i1 %569, label %570, label %586

; <label>:570:                                    ; preds = %567
  %571 = load i32, i32* @debug_disable_external, align 4
  %572 = icmp ne i32 %571, 1
  br i1 %572, label %573, label %586

; <label>:573:                                    ; preds = %570
  %574 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %575 = icmp ne %struct.__sFILE* %574, null
  br i1 %575, label %576, label %586

; <label>:576:                                    ; preds = %573
  %577 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %578 = load i64, i64* %38, align 8
  %579 = load i64, i64* %41, align 8
  %580 = load i64, i64* %38, align 8
  %581 = sub i64 %580, 64
  %582 = load i64, i64* %41, align 8
  %583 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %577, i8* getelementptr inbounds ([228 x i8], [228 x i8]* @.str.111, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1047, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %578, i64 64, i64 %579, i64 %581, i64 %582)
  %584 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %585 = call i32 @fflush(%struct.__sFILE* %584)
  br label %586

; <label>:586:                                    ; preds = %576, %573, %570, %567, %564
  %587 = load i64, i64* %38, align 8
  %588 = sub i64 %587, 64
  %589 = load i64, i64* %41, align 8
  %590 = icmp ult i64 %588, %589
  br i1 %590, label %591, label %749

; <label>:591:                                    ; preds = %586
  %592 = load i32, i32* @debug_enable, align 4
  %593 = icmp eq i32 %592, 1
  br i1 %593, label %594, label %608

; <label>:594:                                    ; preds = %591
  %595 = load i32, i32* @debug_disable_method, align 4
  %596 = icmp eq i32 %595, 0
  br i1 %596, label %597, label %608

; <label>:597:                                    ; preds = %594
  %598 = load i32, i32* @debug_disable_external, align 4
  %599 = icmp ne i32 %598, 1
  br i1 %599, label %600, label %608

; <label>:600:                                    ; preds = %597
  %601 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %602 = icmp ne %struct.__sFILE* %601, null
  br i1 %602, label %603, label %608

; <label>:603:                                    ; preds = %600
  %604 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %605 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %604, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1052, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.112, i32 0, i32 0))
  %606 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %607 = call i32 @fflush(%struct.__sFILE* %606)
  br label %608

; <label>:608:                                    ; preds = %603, %600, %597, %594, %591
  store i32 0, i32* %44, align 4
  %609 = load i32, i32* %21, align 4
  %610 = icmp ne i32 %609, 0
  br i1 %610, label %621, label %611

; <label>:611:                                    ; preds = %608
  %612 = load i64, i64* %39, align 8
  %613 = add i64 2, %612
  %614 = call i32 @fat_has_free(i64 %613)
  %615 = icmp ne i32 %614, 0
  br i1 %615, label %621, label %616

; <label>:616:                                    ; preds = %611
  %617 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %618 = load i32, i32* %30, align 4
  %619 = sext i32 %618 to i64
  %620 = getelementptr inbounds i32, i32* %617, i64 %619
  store i32 0, i32* %620, align 4
  store i32 1, i32* %44, align 4
  br label %629

; <label>:621:                                    ; preds = %611, %608
  %622 = load i32, i32* %21, align 4
  %623 = icmp ne i32 %622, 0
  br i1 %623, label %624, label %628

; <label>:624:                                    ; preds = %621
  %625 = call i32 @fat_has_free(i64 1)
  %626 = icmp ne i32 %625, 0
  br i1 %626, label %628, label %627

; <label>:627:                                    ; preds = %624
  store i32 1, i32* %44, align 4
  br label %628

; <label>:628:                                    ; preds = %627, %624, %621
  br label %629

; <label>:629:                                    ; preds = %628, %616
  %630 = load i32, i32* %44, align 4
  %631 = icmp ne i32 %630, 0
  br i1 %631, label %632, label %660

; <label>:632:                                    ; preds = %629
  %633 = load i32, i32* @debug_enable, align 4
  %634 = icmp eq i32 %633, 1
  br i1 %634, label %635, label %651

; <label>:635:                                    ; preds = %632
  %636 = load i32, i32* @debug_disable_method, align 4
  %637 = icmp eq i32 %636, 0
  br i1 %637, label %638, label %651

; <label>:638:                                    ; preds = %635
  %639 = load i32, i32* @debug_disable_external, align 4
  %640 = icmp ne i32 %639, 1
  br i1 %640, label %641, label %651

; <label>:641:                                    ; preds = %638
  %642 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %643 = icmp ne %struct.__sFILE* %642, null
  br i1 %643, label %644, label %651

; <label>:644:                                    ; preds = %641
  %645 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %646 = load i64, i64* %39, align 8
  %647 = add i64 2, %646
  %648 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %645, i8* getelementptr inbounds ([167 x i8], [167 x i8]* @.str.113, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1071, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %647, i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.107, i32 0, i32 0))
  %649 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %650 = call i32 @fflush(%struct.__sFILE* %649)
  br label %651

; <label>:651:                                    ; preds = %644, %641, %638, %635, %632
  %652 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %653 = icmp ne %struct.dir_t* %652, null
  br i1 %653, label %654, label %657

; <label>:654:                                    ; preds = %651
  %655 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %656 = bitcast %struct.dir_t* %655 to i8*
  call void @free(i8* %656)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %657

; <label>:657:                                    ; preds = %654, %651
  %658 = load i32, i32* @debug_disable_method, align 4
  %659 = and i32 %658, -17
  store i32 %659, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:660:                                    ; preds = %629
  %661 = load i32, i32* %30, align 4
  %662 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %663 = load i32, i32* %42, align 4
  %664 = sext i32 %663 to i64
  %665 = getelementptr inbounds i32, i32* %662, i64 %664
  store i32 %661, i32* %665, align 4
  %666 = load i32, i32* %30, align 4
  store i32 %666, i32* %42, align 4
  %667 = load i32, i32* %21, align 4
  %668 = icmp ne i32 %667, 0
  br i1 %668, label %708, label %669

; <label>:669:                                    ; preds = %660
  %670 = call i32 @fat_find_free_block()
  store i32 %670, i32* %29, align 4
  %671 = load i32, i32* %29, align 4
  %672 = icmp eq i32 %671, -1
  br i1 %672, label %673, label %703

; <label>:673:                                    ; preds = %669
  %674 = load i32, i32* @debug_enable, align 4
  %675 = icmp eq i32 %674, 1
  br i1 %675, label %676, label %690

; <label>:676:                                    ; preds = %673
  %677 = load i32, i32* @debug_disable_method, align 4
  %678 = icmp eq i32 %677, 0
  br i1 %678, label %679, label %690

; <label>:679:                                    ; preds = %676
  %680 = load i32, i32* @debug_disable_external, align 4
  %681 = icmp ne i32 %680, 1
  br i1 %681, label %682, label %690

; <label>:682:                                    ; preds = %679
  %683 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %684 = icmp ne %struct.__sFILE* %683, null
  br i1 %684, label %685, label %690

; <label>:685:                                    ; preds = %682
  %686 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %687 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %686, i8* getelementptr inbounds ([147 x i8], [147 x i8]* @.str.106, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1086, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.107, i32 0, i32 0))
  %688 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %689 = call i32 @fflush(%struct.__sFILE* %688)
  br label %690

; <label>:690:                                    ; preds = %685, %682, %679, %676, %673
  %691 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %692 = load i32, i32* %30, align 4
  %693 = sext i32 %692 to i64
  %694 = getelementptr inbounds i32, i32* %691, i64 %693
  store i32 0, i32* %694, align 4
  %695 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %696 = icmp ne %struct.dir_t* %695, null
  br i1 %696, label %697, label %700

; <label>:697:                                    ; preds = %690
  %698 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %699 = bitcast %struct.dir_t* %698 to i8*
  call void @free(i8* %699)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %700

; <label>:700:                                    ; preds = %697, %690
  %701 = load i32, i32* @debug_disable_method, align 4
  %702 = and i32 %701, -17
  store i32 %702, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:703:                                    ; preds = %669
  %704 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %705 = add nsw i64 %704, -1
  store i64 %705, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %706 = load i32, i32* %29, align 4
  %707 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  store i32 %706, i32* %707, align 4
  br label %708

; <label>:708:                                    ; preds = %703, %660
  %709 = load i32, i32* %42, align 4
  %710 = sext i32 %709 to i64
  %711 = load i64, i64* %38, align 8
  %712 = mul i64 %710, %711
  store i64 %712, i64* %35, align 8
  %713 = load i32, i32* %12, align 4
  %714 = load i64, i64* %35, align 8
  %715 = call i32 @fat_write_entry(i32 %713, %struct.dir_t* %28, i64 %714)
  store i32 %715, i32* %25, align 4
  %716 = load i32, i32* %25, align 4
  %717 = icmp slt i32 %716, 0
  br i1 %717, label %718, label %748

; <label>:718:                                    ; preds = %708
  store i32 1, i32* @debug_enable, align 4
  %719 = load i32, i32* @debug_enable, align 4
  %720 = icmp eq i32 %719, 1
  br i1 %720, label %721, label %746

; <label>:721:                                    ; preds = %718
  %722 = load i32, i32* @debug_disable_method, align 4
  %723 = icmp eq i32 %722, 0
  br i1 %723, label %724, label %746

; <label>:724:                                    ; preds = %721
  %725 = load i32, i32* @debug_disable_external, align 4
  %726 = icmp ne i32 %725, 1
  br i1 %726, label %727, label %746

; <label>:727:                                    ; preds = %724
  %728 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %729 = icmp ne %struct.__sFILE* %728, null
  br i1 %729, label %730, label %746

; <label>:730:                                    ; preds = %727
  %731 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %732 = load i32, i32* %25, align 4
  %733 = load i32, i32* %25, align 4
  %734 = icmp slt i32 %733, 0
  br i1 %734, label %735, label %738

; <label>:735:                                    ; preds = %730
  %736 = load i32, i32* %25, align 4
  %737 = sub nsw i32 0, %736
  br label %740

; <label>:738:                                    ; preds = %730
  %739 = load i32, i32* %25, align 4
  br label %740

; <label>:740:                                    ; preds = %738, %735
  %741 = phi i32 [ %737, %735 ], [ %739, %738 ]
  %742 = call i8* @"\01_strerror"(i32 %741)
  %743 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %731, i8* getelementptr inbounds ([166 x i8], [166 x i8]* @.str.114, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1100, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %732, i8* %742)
  %744 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %745 = call i32 @fflush(%struct.__sFILE* %744)
  br label %746

; <label>:746:                                    ; preds = %740, %727, %724, %721, %718
  %747 = load i32, i32* %25, align 4
  store i32 %747, i32* %11, align 4
  br label %1022

; <label>:748:                                    ; preds = %708
  br label %809

; <label>:749:                                    ; preds = %586
  %750 = load i32, i32* @debug_enable, align 4
  %751 = icmp eq i32 %750, 1
  br i1 %751, label %752, label %766

; <label>:752:                                    ; preds = %749
  %753 = load i32, i32* @debug_disable_method, align 4
  %754 = icmp eq i32 %753, 0
  br i1 %754, label %755, label %766

; <label>:755:                                    ; preds = %752
  %756 = load i32, i32* @debug_disable_external, align 4
  %757 = icmp ne i32 %756, 1
  br i1 %757, label %758, label %766

; <label>:758:                                    ; preds = %755
  %759 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %760 = icmp ne %struct.__sFILE* %759, null
  br i1 %760, label %761, label %766

; <label>:761:                                    ; preds = %758
  %762 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %763 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %762, i8* getelementptr inbounds ([119 x i8], [119 x i8]* @.str.99, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1103, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.115, i32 0, i32 0))
  %764 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %765 = call i32 @fflush(%struct.__sFILE* %764)
  br label %766

; <label>:766:                                    ; preds = %761, %758, %755, %752, %749
  %767 = load i32, i32* %42, align 4
  %768 = sext i32 %767 to i64
  %769 = load i64, i64* %38, align 8
  %770 = mul i64 %768, %769
  %771 = load i64, i64* %41, align 8
  %772 = add i64 %770, %771
  store i64 %772, i64* %35, align 8
  %773 = load i32, i32* %12, align 4
  %774 = load i64, i64* %35, align 8
  %775 = call i32 @fat_write_entry(i32 %773, %struct.dir_t* %28, i64 %774)
  store i32 %775, i32* %25, align 4
  %776 = load i32, i32* %25, align 4
  %777 = icmp slt i32 %776, 0
  br i1 %777, label %778, label %808

; <label>:778:                                    ; preds = %766
  store i32 1, i32* @debug_enable, align 4
  %779 = load i32, i32* @debug_enable, align 4
  %780 = icmp eq i32 %779, 1
  br i1 %780, label %781, label %806

; <label>:781:                                    ; preds = %778
  %782 = load i32, i32* @debug_disable_method, align 4
  %783 = icmp eq i32 %782, 0
  br i1 %783, label %784, label %806

; <label>:784:                                    ; preds = %781
  %785 = load i32, i32* @debug_disable_external, align 4
  %786 = icmp ne i32 %785, 1
  br i1 %786, label %787, label %806

; <label>:787:                                    ; preds = %784
  %788 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %789 = icmp ne %struct.__sFILE* %788, null
  br i1 %789, label %790, label %806

; <label>:790:                                    ; preds = %787
  %791 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %792 = load i32, i32* %25, align 4
  %793 = load i32, i32* %25, align 4
  %794 = icmp slt i32 %793, 0
  br i1 %794, label %795, label %798

; <label>:795:                                    ; preds = %790
  %796 = load i32, i32* %25, align 4
  %797 = sub nsw i32 0, %796
  br label %800

; <label>:798:                                    ; preds = %790
  %799 = load i32, i32* %25, align 4
  br label %800

; <label>:800:                                    ; preds = %798, %795
  %801 = phi i32 [ %797, %795 ], [ %799, %798 ]
  %802 = call i8* @"\01_strerror"(i32 %801)
  %803 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %791, i8* getelementptr inbounds ([166 x i8], [166 x i8]* @.str.114, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1107, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %792, i8* %802)
  %804 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %805 = call i32 @fflush(%struct.__sFILE* %804)
  br label %806

; <label>:806:                                    ; preds = %800, %787, %784, %781, %778
  %807 = load i32, i32* %25, align 4
  store i32 %807, i32* %11, align 4
  br label %1022

; <label>:808:                                    ; preds = %766
  br label %809

; <label>:809:                                    ; preds = %808, %748
  br label %810

; <label>:810:                                    ; preds = %809, %511
  br label %811

; <label>:811:                                    ; preds = %810, %401
  %812 = load i32, i32* %40, align 4
  %813 = icmp ne i32 %812, 0
  br i1 %813, label %814, label %858

; <label>:814:                                    ; preds = %811
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1113, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.116, i32 0, i32 0))
  %815 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %816 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %815, i32 0, i32 2
  %817 = load i32, i32* %816, align 8
  %818 = zext i32 %817 to i64
  %819 = add i64 %818, 64
  %820 = trunc i64 %819 to i32
  store i32 %820, i32* %816, align 8
  %821 = load i32, i32* %12, align 4
  %822 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %823 = load i64, i64* %23, align 8
  %824 = call i32 @fat_write_entry(i32 %821, %struct.dir_t* %822, i64 %823)
  store i32 %824, i32* %25, align 4
  %825 = load i32, i32* %25, align 4
  %826 = icmp slt i32 %825, 0
  br i1 %826, label %827, label %857

; <label>:827:                                    ; preds = %814
  store i32 1, i32* @debug_enable, align 4
  %828 = load i32, i32* @debug_enable, align 4
  %829 = icmp eq i32 %828, 1
  br i1 %829, label %830, label %855

; <label>:830:                                    ; preds = %827
  %831 = load i32, i32* @debug_disable_method, align 4
  %832 = icmp eq i32 %831, 0
  br i1 %832, label %833, label %855

; <label>:833:                                    ; preds = %830
  %834 = load i32, i32* @debug_disable_external, align 4
  %835 = icmp ne i32 %834, 1
  br i1 %835, label %836, label %855

; <label>:836:                                    ; preds = %833
  %837 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %838 = icmp ne %struct.__sFILE* %837, null
  br i1 %838, label %839, label %855

; <label>:839:                                    ; preds = %836
  %840 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %841 = load i32, i32* %25, align 4
  %842 = load i32, i32* %25, align 4
  %843 = icmp slt i32 %842, 0
  br i1 %843, label %844, label %847

; <label>:844:                                    ; preds = %839
  %845 = load i32, i32* %25, align 4
  %846 = sub nsw i32 0, %845
  br label %849

; <label>:847:                                    ; preds = %839
  %848 = load i32, i32* %25, align 4
  br label %849

; <label>:849:                                    ; preds = %847, %844
  %850 = phi i32 [ %846, %844 ], [ %848, %847 ]
  %851 = call i8* @"\01_strerror"(i32 %850)
  %852 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %840, i8* getelementptr inbounds ([170 x i8], [170 x i8]* @.str.117, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1117, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %841, i8* %851)
  %853 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %854 = call i32 @fflush(%struct.__sFILE* %853)
  br label %855

; <label>:855:                                    ; preds = %849, %836, %833, %830, %827
  %856 = load i32, i32* %25, align 4
  store i32 %856, i32* %11, align 4
  br label %1022

; <label>:857:                                    ; preds = %814
  br label %858

; <label>:858:                                    ; preds = %857, %811
  %859 = load i32, i32* %21, align 4
  %860 = icmp ne i32 %859, 0
  br i1 %860, label %978, label %861

; <label>:861:                                    ; preds = %858
  %862 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 3
  %863 = load i32, i32* %862, align 4
  store i32 %863, i32* %45, align 4
  %864 = load i32, i32* %14, align 4
  store i32 %864, i32* %46, align 4
  br label %865

; <label>:865:                                    ; preds = %919, %861
  %866 = load i64, i64* %38, align 8
  %867 = load i32, i32* %46, align 4
  %868 = zext i32 %867 to i64
  %869 = icmp ult i64 %866, %868
  br i1 %869, label %870, label %925

; <label>:870:                                    ; preds = %865
  %871 = call i32 @fat_find_free_block()
  store i32 %871, i32* %47, align 4
  %872 = load i32, i32* %47, align 4
  %873 = icmp eq i32 %872, -1
  br i1 %873, label %874, label %911

; <label>:874:                                    ; preds = %870
  %875 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %876 = load i32, i32* %45, align 4
  %877 = sext i32 %876 to i64
  %878 = getelementptr inbounds i32, i32* %875, i64 %877
  store i32 -2, i32* %878, align 4
  store i64 -1, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %879 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %880 = load i32, i32* %30, align 4
  %881 = sext i32 %880 to i64
  %882 = getelementptr inbounds i32, i32* %879, i64 %881
  store i32 0, i32* %882, align 4
  %883 = load i32, i32* @debug_enable, align 4
  %884 = icmp eq i32 %883, 1
  br i1 %884, label %885, label %899

; <label>:885:                                    ; preds = %874
  %886 = load i32, i32* @debug_disable_method, align 4
  %887 = icmp eq i32 %886, 0
  br i1 %887, label %888, label %899

; <label>:888:                                    ; preds = %885
  %889 = load i32, i32* @debug_disable_external, align 4
  %890 = icmp ne i32 %889, 1
  br i1 %890, label %891, label %899

; <label>:891:                                    ; preds = %888
  %892 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %893 = icmp ne %struct.__sFILE* %892, null
  br i1 %893, label %894, label %899

; <label>:894:                                    ; preds = %891
  %895 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %896 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %895, i8* getelementptr inbounds ([147 x i8], [147 x i8]* @.str.106, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1129, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([7 x i8], [7 x i8]* @.str.107, i32 0, i32 0))
  %897 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %898 = call i32 @fflush(%struct.__sFILE* %897)
  br label %899

; <label>:899:                                    ; preds = %894, %891, %888, %885, %874
  %900 = call i64 (...) @pathc_count_free()
  %901 = load i32, i32* %12, align 4
  %902 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %901, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %902)
  %903 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %904 = icmp ne %struct.dir_t* %903, null
  br i1 %904, label %905, label %908

; <label>:905:                                    ; preds = %899
  %906 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %907 = bitcast %struct.dir_t* %906 to i8*
  call void @free(i8* %907)
  store %struct.dir_t* null, %struct.dir_t** %22, align 8
  br label %908

; <label>:908:                                    ; preds = %905, %899
  %909 = load i32, i32* @debug_disable_method, align 4
  %910 = and i32 %909, -17
  store i32 %910, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  store i32 -28, i32* %11, align 4
  br label %1022

; <label>:911:                                    ; preds = %870
  %912 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %913 = add nsw i64 %912, -1
  store i64 %913, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %914 = load i32, i32* %47, align 4
  %915 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %916 = load i32, i32* %45, align 4
  %917 = sext i32 %916 to i64
  %918 = getelementptr inbounds i32, i32* %915, i64 %917
  store i32 %914, i32* %918, align 4
  store i32 %914, i32* %45, align 4
  br label %919

; <label>:919:                                    ; preds = %911
  %920 = load i64, i64* %38, align 8
  %921 = load i32, i32* %46, align 4
  %922 = zext i32 %921 to i64
  %923 = sub i64 %922, %920
  %924 = trunc i64 %923 to i32
  store i32 %924, i32* %46, align 4
  br label %865

; <label>:925:                                    ; preds = %865
  %926 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %927 = load i32, i32* %45, align 4
  %928 = sext i32 %927 to i64
  %929 = getelementptr inbounds i32, i32* %926, i64 %928
  store i32 -2, i32* %929, align 4
  %930 = load i32, i32* @debug_enable, align 4
  %931 = icmp eq i32 %930, 1
  br i1 %931, label %932, label %950

; <label>:932:                                    ; preds = %925
  %933 = load i32, i32* @debug_disable_method, align 4
  %934 = icmp eq i32 %933, 0
  br i1 %934, label %935, label %950

; <label>:935:                                    ; preds = %932
  %936 = load i32, i32* @debug_disable_external, align 4
  %937 = icmp ne i32 %936, 1
  br i1 %937, label %938, label %950

; <label>:938:                                    ; preds = %935
  %939 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %940 = icmp ne %struct.__sFILE* %939, null
  br i1 %940, label %941, label %950

; <label>:941:                                    ; preds = %938
  %942 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %943 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 0
  %944 = bitcast %union.fname_u* %943 to [24 x i8]*
  %945 = getelementptr inbounds [24 x i8], [24 x i8]* %944, i32 0, i32 0
  %946 = load i64, i64* %35, align 8
  %947 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %942, i8* getelementptr inbounds ([222 x i8], [222 x i8]* @.str.118, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1143, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %945, i64 %946)
  %948 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %949 = call i32 @fflush(%struct.__sFILE* %948)
  br label %950

; <label>:950:                                    ; preds = %941, %938, %935, %932, %925
  %951 = load i8*, i8** %13, align 8
  %952 = load i64, i64* %35, align 8
  %953 = call i32 @pathc_insert(i8* %951, %struct.dir_t* byval align 8 %28, i64 %952, %struct.pathc_t** %48)
  store i32 %953, i32* %25, align 4
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1146, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([10 x i8], [10 x i8]* @.str.119, i32 0, i32 0))
  %954 = load i32, i32* %25, align 4
  %955 = icmp ne i32 %954, 0
  br i1 %955, label %956, label %963

; <label>:956:                                    ; preds = %950
  %957 = load i32, i32* %25, align 4
  %958 = icmp ne i32 %957, 1
  br i1 %958, label %959, label %963

; <label>:959:                                    ; preds = %956
  %960 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %961 = load i32, i32* %25, align 4
  %962 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %960, i8* getelementptr inbounds ([152 x i8], [152 x i8]* @.str.120, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1149, i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.92, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %961)
  call void @quit(i32 1, i32 1)
  br label %977

; <label>:963:                                    ; preds = %956, %950
  %964 = load i32, i32* %21, align 4
  %965 = icmp ne i32 %964, 0
  br i1 %965, label %966, label %969

; <label>:966:                                    ; preds = %963
  %967 = load %struct.pathc_t*, %struct.pathc_t** %48, align 8
  %968 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %967, i32 0, i32 0
  store i8 0, i8* %968, align 8
  br label %969

; <label>:969:                                    ; preds = %966, %963
  %970 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  %971 = icmp ne %struct.dir_t** %970, null
  br i1 %971, label %972, label %976

; <label>:972:                                    ; preds = %969
  %973 = load %struct.pathc_t*, %struct.pathc_t** %48, align 8
  %974 = getelementptr inbounds %struct.pathc_t, %struct.pathc_t* %973, i32 0, i32 2
  %975 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  store %struct.dir_t* %974, %struct.dir_t** %975, align 8
  br label %976

; <label>:976:                                    ; preds = %972, %969
  br label %977

; <label>:977:                                    ; preds = %976, %959
  br label %998

; <label>:978:                                    ; preds = %858
  %979 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  %980 = icmp ne %struct.dir_t** %979, null
  br i1 %980, label %981, label %997

; <label>:981:                                    ; preds = %978
  %982 = call i8* @malloc(i64 64) #9
  %983 = bitcast i8* %982 to %struct.dir_t*
  store %struct.dir_t* %983, %struct.dir_t** %49, align 8
  %984 = load %struct.dir_t*, %struct.dir_t** %49, align 8
  %985 = bitcast %struct.dir_t* %984 to i8*
  %986 = bitcast %struct.dir_t* %28 to i8*
  %987 = load %struct.dir_t*, %struct.dir_t** %49, align 8
  %988 = bitcast %struct.dir_t* %987 to i8*
  %989 = call i64 @llvm.objectsize.i64.p0i8(i8* %988, i1 false, i1 true)
  %990 = call i8* @__memcpy_chk(i8* %985, i8* %986, i64 64, i64 %989) #7
  %991 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  %992 = icmp ne %struct.dir_t** %991, null
  br i1 %992, label %993, label %996

; <label>:993:                                    ; preds = %981
  %994 = load %struct.dir_t*, %struct.dir_t** %49, align 8
  %995 = load %struct.dir_t**, %struct.dir_t*** %17, align 8
  store %struct.dir_t* %994, %struct.dir_t** %995, align 8
  br label %996

; <label>:996:                                    ; preds = %993, %981
  br label %997

; <label>:997:                                    ; preds = %996, %978
  br label %998

; <label>:998:                                    ; preds = %997, %977
  %999 = load i32, i32* %12, align 4
  %1000 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %999, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %1000)
  %1001 = load i64*, i64** %18, align 8
  %1002 = icmp ne i64* %1001, null
  br i1 %1002, label %1003, label %1006

; <label>:1003:                                   ; preds = %998
  %1004 = load i64, i64* %35, align 8
  %1005 = load i64*, i64** %18, align 8
  store i64 %1004, i64* %1005, align 8
  br label %1006

; <label>:1006:                                   ; preds = %1003, %998
  %1007 = load %struct.dir_t**, %struct.dir_t*** %19, align 8
  %1008 = icmp ne %struct.dir_t** %1007, null
  br i1 %1008, label %1009, label %1012

; <label>:1009:                                   ; preds = %1006
  %1010 = load %struct.dir_t*, %struct.dir_t** %22, align 8
  %1011 = load %struct.dir_t**, %struct.dir_t*** %19, align 8
  store %struct.dir_t* %1010, %struct.dir_t** %1011, align 8
  br label %1012

; <label>:1012:                                   ; preds = %1009, %1006
  %1013 = load i64*, i64** %20, align 8
  %1014 = icmp ne i64* %1013, null
  br i1 %1014, label %1015, label %1018

; <label>:1015:                                   ; preds = %1012
  %1016 = load i64, i64* %23, align 8
  %1017 = load i64*, i64** %20, align 8
  store i64 %1016, i64* %1017, align 8
  br label %1018

; <label>:1018:                                   ; preds = %1015, %1012
  %1019 = load i32, i32* @debug_disable_method, align 4
  %1020 = and i32 %1019, -17
  store i32 %1020, i32* @debug_disable_method, align 4
  call void @indent(i32 -1)
  %1021 = load i32, i32* %26, align 4
  store i32 %1021, i32* %11, align 4
  br label %1022

; <label>:1022:                                   ; preds = %1018, %908, %855, %806, %746, %700, %657, %509, %461, %360, %189, %132, %95
  ; %1023 = load i32, i32* %11, align 4
  ret i32 %57 ; Originally %1023; changed to test spilling.
}