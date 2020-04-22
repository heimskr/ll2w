%struct.block_meta = type { i64, %struct.block_meta*, i32 }

define void @test() #0 {
	%1 = alloca %struct.block_meta*, align 8
	%2 = getelementptr inbounds %struct.block_meta, %struct.block_meta* %1, i64 1
	; Should be 24, not 20
	ret i64 %2
}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
