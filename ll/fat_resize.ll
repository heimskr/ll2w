define i32 @fat_resize(i32, %struct.dir_t*, i64, i64) #0 {
  %5 = alloca i32, align 4
  %6 = alloca i32, align 4
  %7 = alloca %struct.dir_t*, align 8
  %8 = alloca i64, align 8
  %9 = alloca i64, align 8
  %10 = alloca i64, align 8
  %11 = alloca i64, align 8
  %12 = alloca i64, align 8
  %13 = alloca i64, align 8
  %14 = alloca i32, align 4
  %15 = alloca i8*, align 8
  %16 = alloca i64, align 8
  %17 = alloca i32, align 4
  %18 = alloca i64, align 8
  %19 = alloca i32, align 4
  %20 = alloca i32, align 4
  %21 = alloca i64, align 8
  %22 = alloca i64, align 8
  %23 = alloca i32, align 4
  %24 = alloca i32, align 4
  %25 = alloca i64, align 8
  %26 = alloca i64, align 8
  %27 = alloca i64, align 8
  store i32 %0, i32* %6, align 4
  store %struct.dir_t* %1, %struct.dir_t** %7, align 8
  store i64 %2, i64* %8, align 8
  store i64 %3, i64* %9, align 8
  call void @indent(i32 1)
  %28 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %29 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %28, i32 0, i32 2
  %30 = load i32, i32* %29, align 8
  %31 = zext i32 %30 to i64
  %32 = load i64, i64* %9, align 8
  %33 = icmp eq i64 %31, %32
  br i1 %33, label %34, label %57

; <label>:34:                                     ; preds = %4
  %35 = load i32, i32* @debug_enable, align 4
  %36 = icmp eq i32 %35, 1
  br i1 %36, label %37, label %56

; <label>:37:                                     ; preds = %34
  %38 = load i32, i32* @debug_disable_method, align 4
  %39 = icmp eq i32 %38, 0
  br i1 %39, label %40, label %56

; <label>:40:                                     ; preds = %37
  %41 = load i32, i32* @debug_disable_external, align 4
  %42 = icmp ne i32 %41, 1
  br i1 %42, label %43, label %56

; <label>:43:                                     ; preds = %40
  %44 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %45 = icmp ne %struct.__sFILE* %44, null
  br i1 %45, label %46, label %56

; <label>:46:                                     ; preds = %43
  %47 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %48 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %49 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %48, i32 0, i32 0
  %50 = bitcast %union.fname_u* %49 to [24 x i8]*
  %51 = getelementptr inbounds [24 x i8], [24 x i8]* %50, i32 0, i32 0
  %52 = load i64, i64* %9, align 8
  %53 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %47, i8* getelementptr inbounds ([196 x i8], [196 x i8]* @.str.121, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1190, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %51, i64 %52)
  %54 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %55 = call i32 @fflush(%struct.__sFILE* %54)
  br label %56

; <label>:56:                                     ; preds = %46, %43, %40, %37, %34
  call void @indent(i32 -1)
  store i32 0, i32* %5, align 4
  br label %646

; <label>:57:                                     ; preds = %4
  %58 = load i64, i64* %9, align 8
  %59 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %60 = call i64 @fat_blocks_required(i64 %58, i32 %59)
  store i64 %60, i64* %11, align 8
  %61 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %62 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %61, i32 0, i32 2
  %63 = load i32, i32* %62, align 8
  %64 = zext i32 %63 to i64
  %65 = load i32, i32* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1, i32 3), align 4
  %66 = call i64 @fat_blocks_required(i64 %64, i32 %65)
  store i64 %66, i64* %12, align 8
  %67 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %68 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %67, i32 0, i32 3
  %69 = load i32, i32* %68, align 4
  %70 = icmp eq i32 %69, 0
  br i1 %70, label %71, label %90

; <label>:71:                                     ; preds = %57
  %72 = load i32, i32* @debug_enable, align 4
  %73 = icmp eq i32 %72, 1
  br i1 %73, label %74, label %88

; <label>:74:                                     ; preds = %71
  %75 = load i32, i32* @debug_disable_method, align 4
  %76 = icmp eq i32 %75, 0
  br i1 %76, label %77, label %88

; <label>:77:                                     ; preds = %74
  %78 = load i32, i32* @debug_disable_external, align 4
  %79 = icmp ne i32 %78, 1
  br i1 %79, label %80, label %88

; <label>:80:                                     ; preds = %77
  %81 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %82 = icmp ne %struct.__sFILE* %81, null
  br i1 %82, label %83, label %88

; <label>:83:                                     ; preds = %80
  %84 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %85 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %84, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1200, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([67 x i8], [67 x i8]* @.str.123, i32 0, i32 0))
  %86 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %87 = call i32 @fflush(%struct.__sFILE* %86)
  br label %88

; <label>:88:                                     ; preds = %83, %80, %77, %74, %71
  %89 = load i64, i64* %12, align 8
  store i64 %89, i64* %10, align 8
  br label %95

; <label>:90:                                     ; preds = %57
  %91 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %92 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %91, i32 0, i32 3
  %93 = load i32, i32* %92, align 4
  %94 = call i64 @fat_chain_length(i32 %93)
  store i64 %94, i64* %10, align 8
  br label %95

; <label>:95:                                     ; preds = %90, %88
  %96 = load i64, i64* %10, align 8
  store i64 %96, i64* %13, align 8
  %97 = load i32, i32* @debug_enable, align 4
  %98 = icmp eq i32 %97, 1
  br i1 %98, label %99, label %123

; <label>:99:                                     ; preds = %95
  %100 = load i32, i32* @debug_disable_method, align 4
  %101 = icmp eq i32 %100, 0
  br i1 %101, label %102, label %123

; <label>:102:                                    ; preds = %99
  %103 = load i32, i32* @debug_disable_external, align 4
  %104 = icmp ne i32 %103, 1
  br i1 %104, label %105, label %123

; <label>:105:                                    ; preds = %102
  %106 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %107 = icmp ne %struct.__sFILE* %106, null
  br i1 %107, label %108, label %123

; <label>:108:                                    ; preds = %105
  %109 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %110 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %111 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %110, i32 0, i32 0
  %112 = bitcast %union.fname_u* %111 to [24 x i8]*
  %113 = getelementptr inbounds [24 x i8], [24 x i8]* %112, i32 0, i32 0
  %114 = load i64, i64* %9, align 8
  %115 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %116 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %115, i32 0, i32 2
  %117 = load i32, i32* %116, align 8
  %118 = load i64, i64* %13, align 8
  %119 = load i64, i64* %11, align 8
  %120 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %109, i8* getelementptr inbounds ([346 x i8], [346 x i8]* @.str.124, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1210, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* %113, i64 %114, i32 %117, i64 %118, i64 %119)
  %121 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %122 = call i32 @fflush(%struct.__sFILE* %121)
  br label %123

; <label>:123:                                    ; preds = %108, %105, %102, %99, %95
  %124 = load i64, i64* %9, align 8
  %125 = icmp eq i64 %124, 0
  br i1 %125, label %126, label %145

; <label>:126:                                    ; preds = %123
  call void @dbg(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1213, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.125, i32 0, i32 0))
  %127 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %128 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %127, i32 0, i32 3
  %129 = load i32, i32* %128, align 4
  %130 = call i64 @fat_forget(i32 %129)
  %131 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %132 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %133 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %132, i32 0, i32 3
  %134 = load i32, i32* %133, align 4
  %135 = sext i32 %134 to i64
  %136 = getelementptr inbounds i32, i32* %131, i64 %135
  store i32 -2, i32* %136, align 4
  %137 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %138 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %137, i32 0, i32 2
  store i32 0, i32* %138, align 8
  %139 = load i32, i32* %6, align 4
  %140 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %141 = load i64, i64* %8, align 8
  %142 = call i32 @fat_write_entry(i32 %139, %struct.dir_t* %140, i64 %141)
  %143 = load i32, i32* %6, align 4
  %144 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %143, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %144)
  br label %628

; <label>:145:                                    ; preds = %123
  %146 = load i64, i64* %13, align 8
  %147 = load i64, i64* %11, align 8
  %148 = icmp eq i64 %146, %147
  br i1 %148, label %149, label %277

; <label>:149:                                    ; preds = %145
  %150 = load i32, i32* @debug_enable, align 4
  %151 = icmp eq i32 %150, 1
  br i1 %151, label %152, label %167

; <label>:152:                                    ; preds = %149
  %153 = load i32, i32* @debug_disable_method, align 4
  %154 = icmp eq i32 %153, 0
  br i1 %154, label %155, label %167

; <label>:155:                                    ; preds = %152
  %156 = load i32, i32* @debug_disable_external, align 4
  %157 = icmp ne i32 %156, 1
  br i1 %157, label %158, label %167

; <label>:158:                                    ; preds = %155
  %159 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %160 = icmp ne %struct.__sFILE* %159, null
  br i1 %160, label %161, label %167

; <label>:161:                                    ; preds = %158
  %162 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %163 = load i64, i64* %13, align 8
  %164 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %162, i8* getelementptr inbounds ([136 x i8], [136 x i8]* @.str.126, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1223, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %163)
  %165 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %166 = call i32 @fflush(%struct.__sFILE* %165)
  br label %167

; <label>:167:                                    ; preds = %161, %158, %155, %152, %149
  %168 = load i64, i64* %9, align 8
  %169 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %170 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %169, i32 0, i32 2
  %171 = load i32, i32* %170, align 8
  %172 = zext i32 %171 to i64
  %173 = icmp slt i64 %168, %172
  br i1 %173, label %174, label %213

; <label>:174:                                    ; preds = %167
  %175 = load i32, i32* %6, align 4
  %176 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %177 = load i64, i64* %9, align 8
  %178 = trunc i64 %177 to i32
  %179 = call i32 @fat_zero_out_free(i32 %175, %struct.dir_t* %176, i32 %178)
  store i32 %179, i32* %14, align 4
  %180 = load i32, i32* %14, align 4
  %181 = icmp slt i32 %180, 0
  br i1 %181, label %182, label %212

; <label>:182:                                    ; preds = %174
  store i32 1, i32* @debug_enable, align 4
  %183 = load i32, i32* @debug_enable, align 4
  %184 = icmp eq i32 %183, 1
  br i1 %184, label %185, label %210

; <label>:185:                                    ; preds = %182
  %186 = load i32, i32* @debug_disable_method, align 4
  %187 = icmp eq i32 %186, 0
  br i1 %187, label %188, label %210

; <label>:188:                                    ; preds = %185
  %189 = load i32, i32* @debug_disable_external, align 4
  %190 = icmp ne i32 %189, 1
  br i1 %190, label %191, label %210

; <label>:191:                                    ; preds = %188
  %192 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %193 = icmp ne %struct.__sFILE* %192, null
  br i1 %193, label %194, label %210

; <label>:194:                                    ; preds = %191
  %195 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %196 = load i32, i32* %14, align 4
  %197 = load i32, i32* %14, align 4
  %198 = icmp slt i32 %197, 0
  br i1 %198, label %199, label %202

; <label>:199:                                    ; preds = %194
  %200 = load i32, i32* %14, align 4
  %201 = sub nsw i32 0, %200
  br label %204

; <label>:202:                                    ; preds = %194
  %203 = load i32, i32* %14, align 4
  br label %204

; <label>:204:                                    ; preds = %202, %199
  %205 = phi i32 [ %201, %199 ], [ %203, %202 ]
  %206 = call i8* @"\01_strerror"(i32 %205)
  %207 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %195, i8* getelementptr inbounds ([151 x i8], [151 x i8]* @.str.127, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1230, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %196, i8* %206)
  %208 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %209 = call i32 @fflush(%struct.__sFILE* %208)
  br label %210

; <label>:210:                                    ; preds = %204, %191, %188, %185, %182
  call void @indent(i32 -1)
  %211 = load i32, i32* %14, align 4
  store i32 %211, i32* %5, align 4
  br label %646

; <label>:212:                                    ; preds = %174
  br label %213

; <label>:213:                                    ; preds = %212, %167
  %214 = load i32, i32* @debug_enable, align 4
  %215 = icmp eq i32 %214, 1
  br i1 %215, label %216, label %235

; <label>:216:                                    ; preds = %213
  %217 = load i32, i32* @debug_disable_method, align 4
  %218 = icmp eq i32 %217, 0
  br i1 %218, label %219, label %235

; <label>:219:                                    ; preds = %216
  %220 = load i32, i32* @debug_disable_external, align 4
  %221 = icmp ne i32 %220, 1
  br i1 %221, label %222, label %235

; <label>:222:                                    ; preds = %219
  %223 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %224 = icmp ne %struct.__sFILE* %223, null
  br i1 %224, label %225, label %235

; <label>:225:                                    ; preds = %222
  %226 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %227 = load i64, i64* %8, align 8
  %228 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %229 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %228, i32 0, i32 2
  %230 = load i32, i32* %229, align 8
  %231 = load i64, i64* %9, align 8
  %232 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %226, i8* getelementptr inbounds ([210 x i8], [210 x i8]* @.str.128, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1234, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %227, i32 %230, i64 %231)
  %233 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %234 = call i32 @fflush(%struct.__sFILE* %233)
  br label %235

; <label>:235:                                    ; preds = %225, %222, %219, %216, %213
  %236 = load i64, i64* %9, align 8
  %237 = trunc i64 %236 to i32
  %238 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %239 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %238, i32 0, i32 2
  store i32 %237, i32* %239, align 8
  %240 = load i32, i32* %6, align 4
  %241 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %242 = load i64, i64* %8, align 8
  %243 = call i32 @fat_write_entry(i32 %240, %struct.dir_t* %241, i64 %242)
  store i32 %243, i32* %14, align 4
  %244 = load i32, i32* %14, align 4
  %245 = icmp slt i32 %244, 0
  br i1 %245, label %246, label %276

; <label>:246:                                    ; preds = %235
  store i32 1, i32* @debug_enable, align 4
  %247 = load i32, i32* @debug_enable, align 4
  %248 = icmp eq i32 %247, 1
  br i1 %248, label %249, label %274

; <label>:249:                                    ; preds = %246
  %250 = load i32, i32* @debug_disable_method, align 4
  %251 = icmp eq i32 %250, 0
  br i1 %251, label %252, label %274

; <label>:252:                                    ; preds = %249
  %253 = load i32, i32* @debug_disable_external, align 4
  %254 = icmp ne i32 %253, 1
  br i1 %254, label %255, label %274

; <label>:255:                                    ; preds = %252
  %256 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %257 = icmp ne %struct.__sFILE* %256, null
  br i1 %257, label %258, label %274

; <label>:258:                                    ; preds = %255
  %259 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %260 = load i32, i32* %14, align 4
  %261 = load i32, i32* %14, align 4
  %262 = icmp slt i32 %261, 0
  br i1 %262, label %263, label %266

; <label>:263:                                    ; preds = %258
  %264 = load i32, i32* %14, align 4
  %265 = sub nsw i32 0, %264
  br label %268

; <label>:266:                                    ; preds = %258
  %267 = load i32, i32* %14, align 4
  br label %268

; <label>:268:                                    ; preds = %266, %263
  %269 = phi i32 [ %265, %263 ], [ %267, %266 ]
  %270 = call i8* @"\01_strerror"(i32 %269)
  %271 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %259, i8* getelementptr inbounds ([149 x i8], [149 x i8]* @.str.129, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1237, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %260, i8* %270)
  %272 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %273 = call i32 @fflush(%struct.__sFILE* %272)
  br label %274

; <label>:274:                                    ; preds = %268, %255, %252, %249, %246
  call void @indent(i32 -1)
  %275 = load i32, i32* %14, align 4
  store i32 %275, i32* %5, align 4
  br label %646

; <label>:276:                                    ; preds = %235
  br label %627

; <label>:277:                                    ; preds = %145
  %278 = load i64, i64* %11, align 8
  %279 = load i64, i64* %13, align 8
  %280 = icmp ult i64 %278, %279
  br i1 %280, label %281, label %452

; <label>:281:                                    ; preds = %277
  %282 = load i32, i32* @debug_enable, align 4
  %283 = icmp eq i32 %282, 1
  br i1 %283, label %284, label %300

; <label>:284:                                    ; preds = %281
  %285 = load i32, i32* @debug_disable_method, align 4
  %286 = icmp eq i32 %285, 0
  br i1 %286, label %287, label %300

; <label>:287:                                    ; preds = %284
  %288 = load i32, i32* @debug_disable_external, align 4
  %289 = icmp ne i32 %288, 1
  br i1 %289, label %290, label %300

; <label>:290:                                    ; preds = %287
  %291 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %292 = icmp ne %struct.__sFILE* %291, null
  br i1 %292, label %293, label %300

; <label>:293:                                    ; preds = %290
  %294 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %295 = load i64, i64* %13, align 8
  %296 = load i64, i64* %11, align 8
  %297 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %294, i8* getelementptr inbounds ([152 x i8], [152 x i8]* @.str.130, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1241, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %295, i64 %296)
  %298 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %299 = call i32 @fflush(%struct.__sFILE* %298)
  br label %300

; <label>:300:                                    ; preds = %293, %290, %287, %284, %281
  %301 = load i64, i64* %13, align 8
  %302 = call i8* @llvm.stacksave()
  store i8* %302, i8** %15, align 8
  %303 = alloca i32, i64 %301, align 16
  store i64 %301, i64* %16, align 8
  %304 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %305 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %304, i32 0, i32 3
  %306 = load i32, i32* %305, align 4
  store i32 %306, i32* %17, align 4
  store i64 0, i64* %18, align 8
  br label %307

; <label>:307:                                    ; preds = %324, %300
  %308 = load i64, i64* %18, align 8
  %309 = load i64, i64* %13, align 8
  %310 = icmp ult i64 %308, %309
  br i1 %310, label %311, label %327

; <label>:311:                                    ; preds = %307
  %312 = load i32, i32* %17, align 4
  %313 = load i64, i64* %18, align 8
  %314 = getelementptr inbounds i32, i32* %303, i64 %313
  store i32 %312, i32* %314, align 4
  %315 = load i64, i64* %18, align 8
  %316 = getelementptr inbounds i32, i32* %303, i64 %315
  %317 = load i32, i32* %316, align 4
  %318 = sext i32 %317 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1247, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([36 x i8], [36 x i8]* @.str.131, i32 0, i32 0), i64 %318)
  %319 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %320 = load i32, i32* %17, align 4
  %321 = sext i32 %320 to i64
  %322 = getelementptr inbounds i32, i32* %319, i64 %321
  %323 = load i32, i32* %322, align 4
  store i32 %323, i32* %17, align 4
  br label %324

; <label>:324:                                    ; preds = %311
  %325 = load i64, i64* %18, align 8
  %326 = add i64 %325, 1
  store i64 %326, i64* %18, align 8
  br label %307

; <label>:327:                                    ; preds = %307
  %328 = load i32, i32* %6, align 4
  %329 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %330 = load i64, i64* %9, align 8
  %331 = trunc i64 %330 to i32
  %332 = call i32 @fat_zero_out_free(i32 %328, %struct.dir_t* %329, i32 %331)
  store i32 %332, i32* %19, align 4
  %333 = load i32, i32* %19, align 4
  %334 = icmp slt i32 %333, 0
  br i1 %334, label %335, label %365

; <label>:335:                                    ; preds = %327
  store i32 1, i32* @debug_enable, align 4
  %336 = load i32, i32* @debug_enable, align 4
  %337 = icmp eq i32 %336, 1
  br i1 %337, label %338, label %363

; <label>:338:                                    ; preds = %335
  %339 = load i32, i32* @debug_disable_method, align 4
  %340 = icmp eq i32 %339, 0
  br i1 %340, label %341, label %363

; <label>:341:                                    ; preds = %338
  %342 = load i32, i32* @debug_disable_external, align 4
  %343 = icmp ne i32 %342, 1
  br i1 %343, label %344, label %363

; <label>:344:                                    ; preds = %341
  %345 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %346 = icmp ne %struct.__sFILE* %345, null
  br i1 %346, label %347, label %363

; <label>:347:                                    ; preds = %344
  %348 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %349 = load i32, i32* %19, align 4
  %350 = load i32, i32* %19, align 4
  %351 = icmp slt i32 %350, 0
  br i1 %351, label %352, label %355

; <label>:352:                                    ; preds = %347
  %353 = load i32, i32* %19, align 4
  %354 = sub nsw i32 0, %353
  br label %357

; <label>:355:                                    ; preds = %347
  %356 = load i32, i32* %19, align 4
  br label %357

; <label>:357:                                    ; preds = %355, %352
  %358 = phi i32 [ %354, %352 ], [ %356, %355 ]
  %359 = call i8* @"\01_strerror"(i32 %358)
  %360 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %348, i8* getelementptr inbounds ([151 x i8], [151 x i8]* @.str.127, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1253, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %349, i8* %359)
  %361 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %362 = call i32 @fflush(%struct.__sFILE* %361)
  br label %363

; <label>:363:                                    ; preds = %357, %344, %341, %338, %335
  call void @indent(i32 -1)
  %364 = load i32, i32* %19, align 4
  store i32 %364, i32* %5, align 4
  store i32 1, i32* %20, align 4
  br label %448

; <label>:365:                                    ; preds = %327
  %366 = load i64, i64* %11, align 8
  store i64 %366, i64* %21, align 8
  br label %367

; <label>:367:                                    ; preds = %384, %365
  %368 = load i64, i64* %21, align 8
  %369 = load i64, i64* %13, align 8
  %370 = icmp ult i64 %368, %369
  br i1 %370, label %371, label %387

; <label>:371:                                    ; preds = %367
  %372 = load i64, i64* %21, align 8
  %373 = getelementptr inbounds i32, i32* %303, i64 %372
  %374 = load i32, i32* %373, align 4
  %375 = sext i32 %374 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1256, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([31 x i8], [31 x i8]* @.str.132, i32 0, i32 0), i64 %375)
  %376 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %377 = load i64, i64* %21, align 8
  %378 = getelementptr inbounds i32, i32* %303, i64 %377
  %379 = load i32, i32* %378, align 4
  %380 = sext i32 %379 to i64
  %381 = getelementptr inbounds i32, i32* %376, i64 %380
  store i32 0, i32* %381, align 4
  %382 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %383 = add nsw i64 %382, 1
  store i64 %383, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  br label %384

; <label>:384:                                    ; preds = %371
  %385 = load i64, i64* %21, align 8
  %386 = add i64 %385, 1
  store i64 %386, i64* %21, align 8
  br label %367

; <label>:387:                                    ; preds = %367
  %388 = load i64, i64* %11, align 8
  %389 = icmp ult i64 0, %388
  br i1 %389, label %390, label %403

; <label>:390:                                    ; preds = %387
  %391 = load i64, i64* %11, align 8
  %392 = sub i64 %391, 1
  %393 = getelementptr inbounds i32, i32* %303, i64 %392
  %394 = load i32, i32* %393, align 4
  %395 = sext i32 %394 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1262, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.133, i32 0, i32 0), i64 %395)
  %396 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %397 = load i64, i64* %11, align 8
  %398 = sub i64 %397, 1
  %399 = getelementptr inbounds i32, i32* %303, i64 %398
  %400 = load i32, i32* %399, align 4
  %401 = sext i32 %400 to i64
  %402 = getelementptr inbounds i32, i32* %396, i64 %401
  store i32 -2, i32* %402, align 4
  br label %403

; <label>:403:                                    ; preds = %390, %387
  %404 = load i64, i64* %9, align 8
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1266, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([27 x i8], [27 x i8]* @.str.134, i32 0, i32 0), i64 %404)
  %405 = load i64, i64* %9, align 8
  %406 = trunc i64 %405 to i32
  %407 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %408 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %407, i32 0, i32 2
  store i32 %406, i32* %408, align 8
  %409 = load i32, i32* %6, align 4
  %410 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %411 = load i64, i64* %8, align 8
  %412 = call i32 @fat_write_entry(i32 %409, %struct.dir_t* %410, i64 %411)
  store i32 %412, i32* %19, align 4
  %413 = load i32, i32* %19, align 4
  %414 = icmp slt i32 %413, 0
  br i1 %414, label %415, label %445

; <label>:415:                                    ; preds = %403
  store i32 1, i32* @debug_enable, align 4
  %416 = load i32, i32* @debug_enable, align 4
  %417 = icmp eq i32 %416, 1
  br i1 %417, label %418, label %443

; <label>:418:                                    ; preds = %415
  %419 = load i32, i32* @debug_disable_method, align 4
  %420 = icmp eq i32 %419, 0
  br i1 %420, label %421, label %443

; <label>:421:                                    ; preds = %418
  %422 = load i32, i32* @debug_disable_external, align 4
  %423 = icmp ne i32 %422, 1
  br i1 %423, label %424, label %443

; <label>:424:                                    ; preds = %421
  %425 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %426 = icmp ne %struct.__sFILE* %425, null
  br i1 %426, label %427, label %443

; <label>:427:                                    ; preds = %424
  %428 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %429 = load i32, i32* %19, align 4
  %430 = load i32, i32* %19, align 4
  %431 = icmp slt i32 %430, 0
  br i1 %431, label %432, label %435

; <label>:432:                                    ; preds = %427
  %433 = load i32, i32* %19, align 4
  %434 = sub nsw i32 0, %433
  br label %437

; <label>:435:                                    ; preds = %427
  %436 = load i32, i32* %19, align 4
  br label %437

; <label>:437:                                    ; preds = %435, %432
  %438 = phi i32 [ %434, %432 ], [ %436, %435 ]
  %439 = call i8* @"\01_strerror"(i32 %438)
  %440 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %428, i8* getelementptr inbounds ([149 x i8], [149 x i8]* @.str.135, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1269, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i32 %429, i8* %439)
  %441 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %442 = call i32 @fflush(%struct.__sFILE* %441)
  br label %443

; <label>:443:                                    ; preds = %437, %424, %421, %418, %415
  call void @indent(i32 -1)
  %444 = load i32, i32* %19, align 4
  store i32 %444, i32* %5, align 4
  store i32 1, i32* %20, align 4
  br label %448

; <label>:445:                                    ; preds = %403
  %446 = load i32, i32* %6, align 4
  %447 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %446, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %447)
  store i32 0, i32* %20, align 4
  br label %448

; <label>:448:                                    ; preds = %445, %443, %363
  %449 = load i8*, i8** %15, align 8
  call void @llvm.stackrestore(i8* %449)
  %450 = load i32, i32* %20, align 4
  switch i32 %450, label %648 [
    i32 0, label %451
    i32 1, label %646
  ]

; <label>:451:                                    ; preds = %448
  br label %626

; <label>:452:                                    ; preds = %277
  %453 = load i32, i32* @debug_enable, align 4
  %454 = icmp eq i32 %453, 1
  br i1 %454, label %455, label %471

; <label>:455:                                    ; preds = %452
  %456 = load i32, i32* @debug_disable_method, align 4
  %457 = icmp eq i32 %456, 0
  br i1 %457, label %458, label %471

; <label>:458:                                    ; preds = %455
  %459 = load i32, i32* @debug_disable_external, align 4
  %460 = icmp ne i32 %459, 1
  br i1 %460, label %461, label %471

; <label>:461:                                    ; preds = %458
  %462 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %463 = icmp ne %struct.__sFILE* %462, null
  br i1 %463, label %464, label %471

; <label>:464:                                    ; preds = %461
  %465 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %466 = load i64, i64* %13, align 8
  %467 = load i64, i64* %11, align 8
  %468 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %465, i8* getelementptr inbounds ([154 x i8], [154 x i8]* @.str.136, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1272, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %466, i64 %467)
  %469 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %470 = call i32 @fflush(%struct.__sFILE* %469)
  br label %471

; <label>:471:                                    ; preds = %464, %461, %458, %455, %452
  %472 = load i64, i64* %11, align 8
  %473 = load i64, i64* %13, align 8
  %474 = icmp ne i64 %473, 0
  br i1 %474, label %476, label %475

; <label>:475:                                    ; preds = %471
  br label %476

; <label>:476:                                    ; preds = %475, %471
  %477 = phi i1 [ true, %471 ], [ true, %475 ]
  %478 = zext i1 %477 to i32
  %479 = sext i32 %478 to i64
  %480 = sub i64 %472, %479
  store i64 %480, i64* %22, align 8
  %481 = load i32, i32* @debug_enable, align 4
  %482 = icmp eq i32 %481, 1
  br i1 %482, label %483, label %502

; <label>:483:                                    ; preds = %476
  %484 = load i32, i32* @debug_disable_method, align 4
  %485 = icmp eq i32 %484, 0
  br i1 %485, label %486, label %502

; <label>:486:                                    ; preds = %483
  %487 = load i32, i32* @debug_disable_external, align 4
  %488 = icmp ne i32 %487, 1
  br i1 %488, label %489, label %502

; <label>:489:                                    ; preds = %486
  %490 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %491 = icmp ne %struct.__sFILE* %490, null
  br i1 %491, label %492, label %502

; <label>:492:                                    ; preds = %489
  %493 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %494 = load i64, i64* %22, align 8
  %495 = load i64, i64* %22, align 8
  %496 = icmp eq i64 %495, 1
  %497 = zext i1 %496 to i64
  %498 = select i1 %496, i8* getelementptr inbounds ([1 x i8], [1 x i8]* @.str.25, i32 0, i32 0), i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.26, i32 0, i32 0)
  %499 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %493, i8* getelementptr inbounds ([131 x i8], [131 x i8]* @.str.137, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1277, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %494, i8* %498)
  %500 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %501 = call i32 @fflush(%struct.__sFILE* %500)
  br label %502

; <label>:502:                                    ; preds = %492, %489, %486, %483, %476
  %503 = load i64, i64* %22, align 8
  %504 = call i32 @fat_has_free(i64 %503)
  %505 = icmp ne i32 %504, 0
  br i1 %505, label %524, label %506

; <label>:506:                                    ; preds = %502
  %507 = load i32, i32* @debug_enable, align 4
  %508 = icmp eq i32 %507, 1
  br i1 %508, label %509, label %523

; <label>:509:                                    ; preds = %506
  %510 = load i32, i32* @debug_disable_method, align 4
  %511 = icmp eq i32 %510, 0
  br i1 %511, label %512, label %523

; <label>:512:                                    ; preds = %509
  %513 = load i32, i32* @debug_disable_external, align 4
  %514 = icmp ne i32 %513, 1
  br i1 %514, label %515, label %523

; <label>:515:                                    ; preds = %512
  %516 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %517 = icmp ne %struct.__sFILE* %516, null
  br i1 %517, label %518, label %523

; <label>:518:                                    ; preds = %515
  %519 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %520 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %519, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1279, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([47 x i8], [47 x i8]* @.str.138, i32 0, i32 0))
  %521 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %522 = call i32 @fflush(%struct.__sFILE* %521)
  br label %523

; <label>:523:                                    ; preds = %518, %515, %512, %509, %506
  call void @indent(i32 -1)
  store i32 -28, i32* %5, align 4
  br label %646

; <label>:524:                                    ; preds = %502
  %525 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %526 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %525, i32 0, i32 3
  %527 = load i32, i32* %526, align 4
  store i32 %527, i32* %24, align 4
  store i64 0, i64* %25, align 8
  store i64 0, i64* %26, align 8
  br label %528

; <label>:528:                                    ; preds = %537, %524
  %529 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %530 = load i32, i32* %24, align 4
  %531 = sext i32 %530 to i64
  %532 = getelementptr inbounds i32, i32* %529, i64 %531
  %533 = load i32, i32* %532, align 4
  store i32 %533, i32* %23, align 4
  %534 = load i32, i32* %23, align 4
  %535 = icmp sle i32 %534, 0
  br i1 %535, label %536, label %537

; <label>:536:                                    ; preds = %528
  br label %545

; <label>:537:                                    ; preds = %528
  %538 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %539 = load i32, i32* %24, align 4
  %540 = sext i32 %539 to i64
  %541 = getelementptr inbounds i32, i32* %538, i64 %540
  %542 = load i32, i32* %541, align 4
  store i32 %542, i32* %24, align 4
  %543 = load i64, i64* %25, align 8
  %544 = add i64 %543, 1
  store i64 %544, i64* %25, align 8
  br label %528

; <label>:545:                                    ; preds = %536
  store i64 0, i64* %27, align 8
  br label %546

; <label>:546:                                    ; preds = %587, %545
  %547 = load i64, i64* %27, align 8
  %548 = load i64, i64* %22, align 8
  %549 = icmp ult i64 %547, %548
  br i1 %549, label %550, label %590

; <label>:550:                                    ; preds = %546
  %551 = call i32 @fat_find_free_block()
  store i32 %551, i32* %23, align 4
  %552 = load i32, i32* %23, align 4
  %553 = icmp eq i32 %552, -1
  br i1 %553, label %554, label %572

; <label>:554:                                    ; preds = %550
  %555 = load i32, i32* @debug_enable, align 4
  %556 = icmp eq i32 %555, 1
  br i1 %556, label %557, label %571

; <label>:557:                                    ; preds = %554
  %558 = load i32, i32* @debug_disable_method, align 4
  %559 = icmp eq i32 %558, 0
  br i1 %559, label %560, label %571

; <label>:560:                                    ; preds = %557
  %561 = load i32, i32* @debug_disable_external, align 4
  %562 = icmp ne i32 %561, 1
  br i1 %562, label %563, label %571

; <label>:563:                                    ; preds = %560
  %564 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %565 = icmp ne %struct.__sFILE* %564, null
  br i1 %565, label %566, label %571

; <label>:566:                                    ; preds = %563
  %567 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %568 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %567, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.62, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1301, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([42 x i8], [42 x i8]* @.str.139, i32 0, i32 0))
  %569 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %570 = call i32 @fflush(%struct.__sFILE* %569)
  br label %571

; <label>:571:                                    ; preds = %566, %563, %560, %557, %554
  call void @indent(i32 -1)
  store i32 -28, i32* %5, align 4
  br label %646

; <label>:572:                                    ; preds = %550
  %573 = load i32, i32* %23, align 4
  %574 = sext i32 %573 to i64
  call void @dbgn(i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1306, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.140, i32 0, i32 0), i64 %574)
  %575 = load i32, i32* %23, align 4
  %576 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %577 = load i32, i32* %24, align 4
  %578 = sext i32 %577 to i64
  %579 = getelementptr inbounds i32, i32* %576, i64 %578
  store i32 %575, i32* %579, align 4
  %580 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  %581 = load i32, i32* %23, align 4
  %582 = sext i32 %581 to i64
  %583 = getelementptr inbounds i32, i32* %580, i64 %582
  store i32 -2, i32* %583, align 4
  %584 = load i32, i32* %23, align 4
  store i32 %584, i32* %24, align 4
  %585 = load i64, i64* %26, align 8
  %586 = add i64 %585, 1
  store i64 %586, i64* %26, align 8
  br label %587

; <label>:587:                                    ; preds = %572
  %588 = load i64, i64* %27, align 8
  %589 = add i64 %588, 1
  store i64 %589, i64* %27, align 8
  br label %546

; <label>:590:                                    ; preds = %546
  %591 = load i64, i64* %26, align 8
  %592 = load i64, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %593 = sub i64 %592, %591
  store i64 %593, i64* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 3), align 8
  %594 = load i32, i32* @debug_enable, align 4
  %595 = icmp eq i32 %594, 1
  br i1 %595, label %596, label %615

; <label>:596:                                    ; preds = %590
  %597 = load i32, i32* @debug_disable_method, align 4
  %598 = icmp eq i32 %597, 0
  br i1 %598, label %599, label %615

; <label>:599:                                    ; preds = %596
  %600 = load i32, i32* @debug_disable_external, align 4
  %601 = icmp ne i32 %600, 1
  br i1 %601, label %602, label %615

; <label>:602:                                    ; preds = %599
  %603 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %604 = icmp ne %struct.__sFILE* %603, null
  br i1 %604, label %605, label %615

; <label>:605:                                    ; preds = %602
  %606 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %607 = load i64, i64* %8, align 8
  %608 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %609 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %608, i32 0, i32 2
  %610 = load i32, i32* %609, align 8
  %611 = load i64, i64* %9, align 8
  %612 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %606, i8* getelementptr inbounds ([192 x i8], [192 x i8]* @.str.141, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1316, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i64 %607, i32 %610, i64 %611)
  %613 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %614 = call i32 @fflush(%struct.__sFILE* %613)
  br label %615

; <label>:615:                                    ; preds = %605, %602, %599, %596, %590
  %616 = load i64, i64* %9, align 8
  %617 = trunc i64 %616 to i32
  %618 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %619 = getelementptr inbounds %struct.dir_t, %struct.dir_t* %618, i32 0, i32 2
  store i32 %617, i32* %619, align 8
  %620 = load i32, i32* %6, align 4
  %621 = load %struct.dir_t*, %struct.dir_t** %7, align 8
  %622 = load i64, i64* %8, align 8
  %623 = call i32 @fat_write_entry(i32 %620, %struct.dir_t* %621, i64 %622)
  %624 = load i32, i32* %6, align 4
  %625 = load i32*, i32** getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 2), align 8
  call void @fat_save(i32 %624, %struct.superblock_t* getelementptr inbounds (%struct.pcache_t, %struct.pcache_t* @pcache, i32 0, i32 1), i32* %625)
  br label %626

; <label>:626:                                    ; preds = %615, %451
  br label %627

; <label>:627:                                    ; preds = %626, %276
  br label %628

; <label>:628:                                    ; preds = %627, %126
  %629 = load i32, i32* @debug_enable, align 4
  %630 = icmp eq i32 %629, 1
  br i1 %630, label %631, label %645

; <label>:631:                                    ; preds = %628
  %632 = load i32, i32* @debug_disable_method, align 4
  %633 = icmp eq i32 %632, 0
  br i1 %633, label %634, label %645

; <label>:634:                                    ; preds = %631
  %635 = load i32, i32* @debug_disable_external, align 4
  %636 = icmp ne i32 %635, 1
  br i1 %636, label %637, label %645

; <label>:637:                                    ; preds = %634
  %638 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %639 = icmp ne %struct.__sFILE* %638, null
  br i1 %639, label %640, label %645

; <label>:640:                                    ; preds = %637
  %641 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %642 = call i32 (%struct.__sFILE*, i8*, ...) @fprintf(%struct.__sFILE* %641, i8* getelementptr inbounds ([111 x i8], [111 x i8]* @.str.142, i32 0, i32 0), i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.1, i32 0, i32 0), i32 1322, i8* getelementptr inbounds ([30 x i8], [30 x i8]* @.str.122, i32 0, i32 0), i8* getelementptr inbounds ([81 x i8], [81 x i8]* @indentation, i32 0, i32 0), i8* getelementptr inbounds ([22 x i8], [22 x i8]* @.str.143, i32 0, i32 0))
  %643 = load %struct.__sFILE*, %struct.__sFILE** @logfile, align 8
  %644 = call i32 @fflush(%struct.__sFILE* %643)
  br label %645

; <label>:645:                                    ; preds = %640, %637, %634, %631, %628
  call void @indent(i32 -1)
  store i32 0, i32* %5, align 4
  br label %646

; <label>:646:                                    ; preds = %645, %571, %523, %448, %274, %210, %56
  %647 = load i32, i32* %5, align 4
  ret i32 %647

; <label>:648:                                    ; preds = %448
  unreachable
}