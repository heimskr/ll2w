/*
; ModuleID = 'main.cpp'
source_filename = "main.cpp"
target datalayout = "e-m:o-i64:64-f80:128-n8:16:32:64-S128"
target triple = "x86_64-apple-macosx10.15.0"

%"class.std::__1::basic_ostream" = type { i32 (...)**, %"class.std::__1::basic_ios.base" }
%"class.std::__1::basic_ios.base" = type <{ %"class.std::__1::ios_base", %"class.std::__1::basic_ostream"*, i32 }>
%"class.std::__1::ios_base" = type { i32 (...)**, i32, i64, i64, i32, i32, i8*, i8*, void (i32, %"class.std::__1::ios_base"*, i32)**, i32*, i64, i64, i64*, i64, i64, i8**, i64, i64 }
%"class.LL2W::ASTNode" = type { i32 (...)**, i32, %"struct.LL2W::Location", %"class.std::__1::basic_string"*, %"class.LL2W::ASTNode"*, %"class.std::__1::list.112" }
%"struct.LL2W::Location" = type { i64, i64 }
%"class.std::__1::basic_string" = type { %"class.std::__1::__compressed_pair.18" }
%"class.std::__1::__compressed_pair.18" = type { %"struct.std::__1::__compressed_pair_elem.19" }
%"struct.std::__1::__compressed_pair_elem.19" = type { %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep" }
%"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep" = type { %union.anon }
%union.anon = type { %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long" }
%"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long" = type { i64, i64, i8* }
%"class.std::__1::list.112" = type { %"class.std::__1::__list_imp.113" }
%"class.std::__1::__list_imp.113" = type { %"struct.std::__1::__list_node_base.114", %"class.std::__1::__compressed_pair.115" }
%"struct.std::__1::__list_node_base.114" = type { %"struct.std::__1::__list_node_base.114"*, %"struct.std::__1::__list_node_base.114"* }
%"class.std::__1::__compressed_pair.115" = type { %"struct.std::__1::__compressed_pair_elem" }
%"struct.std::__1::__compressed_pair_elem" = type { i64 }
%"class.std::__1::locale::id" = type <{ %"struct.std::__1::once_flag", i32, [4 x i8] }>
%"struct.std::__1::once_flag" = type { i64 }
%"class.LL2W::Graph" = type { i32 (...)**, %"class.std::__1::list", %"class.std::__1::unordered_map" }
%"class.std::__1::list" = type { %"class.std::__1::__list_imp" }
%"class.std::__1::__list_imp" = type { %"struct.std::__1::__list_node_base", %"class.std::__1::__compressed_pair" }
%"struct.std::__1::__list_node_base" = type { %"struct.std::__1::__list_node_base"*, %"struct.std::__1::__list_node_base"* }
%"class.std::__1::__compressed_pair" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::unordered_map" = type { %"class.std::__1::__hash_table" }
%"class.std::__1::__hash_table" = type <{ %"class.std::__1::unique_ptr", %"class.std::__1::__compressed_pair.8", %"class.std::__1::__compressed_pair.13", %"class.std::__1::__compressed_pair.15", [4 x i8] }>
%"class.std::__1::unique_ptr" = type { %"class.std::__1::__compressed_pair.1" }
%"class.std::__1::__compressed_pair.1" = type { %"struct.std::__1::__compressed_pair_elem.2", %"struct.std::__1::__compressed_pair_elem.3" }
%"struct.std::__1::__compressed_pair_elem.2" = type { %"struct.std::__1::__hash_node_base"** }
%"struct.std::__1::__hash_node_base" = type { %"struct.std::__1::__hash_node_base"* }
%"struct.std::__1::__compressed_pair_elem.3" = type { %"class.std::__1::__bucket_list_deallocator" }
%"class.std::__1::__bucket_list_deallocator" = type { %"class.std::__1::__compressed_pair.4" }
%"class.std::__1::__compressed_pair.4" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.8" = type { %"struct.std::__1::__compressed_pair_elem.9" }
%"struct.std::__1::__compressed_pair_elem.9" = type { %"struct.std::__1::__hash_node_base" }
%"class.std::__1::__compressed_pair.13" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.15" = type { %"struct.std::__1::__compressed_pair_elem.16" }
%"struct.std::__1::__compressed_pair_elem.16" = type { float }
%"class.std::initializer_list" = type { %"class.std::__1::basic_string"*, i64 }
%"class.LL2W::DTree" = type { %"class.LL2W::Graph" }
%"class.LL2W::Node" = type <{ %"class.LL2W::Graph"*, %"class.std::__1::basic_string", %"class.std::__1::set", %"class.std::__1::set", i32, [4 x i8] }>
%"class.std::__1::set" = type { %"class.std::__1::__tree" }
%"class.std::__1::__tree" = type { %"class.std::__1::__tree_end_node"*, %"class.std::__1::__compressed_pair.24", %"class.std::__1::__compressed_pair.29" }
%"class.std::__1::__tree_end_node" = type { %"class.std::__1::__tree_node_base"* }
%"class.std::__1::__tree_node_base" = type opaque
%"class.std::__1::__compressed_pair.24" = type { %"struct.std::__1::__compressed_pair_elem.25" }
%"struct.std::__1::__compressed_pair_elem.25" = type { %"class.std::__1::__tree_end_node" }
%"class.std::__1::__compressed_pair.29" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.LL2W::DJGraph" = type { %"class.LL2W::Graph", %"class.std::__1::unordered_map.31", %"class.std::__1::vector" }
%"class.std::__1::unordered_map.31" = type { %"class.std::__1::__hash_table.32" }
%"class.std::__1::__hash_table.32" = type <{ %"class.std::__1::unique_ptr.33", %"class.std::__1::__compressed_pair.43", %"class.std::__1::__compressed_pair.48", %"class.std::__1::__compressed_pair.53", [4 x i8] }>
%"class.std::__1::unique_ptr.33" = type { %"class.std::__1::__compressed_pair.34" }
%"class.std::__1::__compressed_pair.34" = type { %"struct.std::__1::__compressed_pair_elem.35", %"struct.std::__1::__compressed_pair_elem.37" }
%"struct.std::__1::__compressed_pair_elem.35" = type { %"struct.std::__1::__hash_node_base.36"** }
%"struct.std::__1::__hash_node_base.36" = type { %"struct.std::__1::__hash_node_base.36"* }
%"struct.std::__1::__compressed_pair_elem.37" = type { %"class.std::__1::__bucket_list_deallocator.38" }
%"class.std::__1::__bucket_list_deallocator.38" = type { %"class.std::__1::__compressed_pair.39" }
%"class.std::__1::__compressed_pair.39" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.43" = type { %"struct.std::__1::__compressed_pair_elem.44" }
%"struct.std::__1::__compressed_pair_elem.44" = type { %"struct.std::__1::__hash_node_base.36" }
%"class.std::__1::__compressed_pair.48" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.53" = type { %"struct.std::__1::__compressed_pair_elem.16" }
%"class.std::__1::vector" = type { %"class.std::__1::__vector_base" }
%"class.std::__1::__vector_base" = type { %"struct.std::__1::pair"*, %"struct.std::__1::pair"*, %"class.std::__1::__compressed_pair.59" }
%"struct.std::__1::pair" = type { %"class.LL2W::Node"*, %"class.LL2W::Node"* }
%"class.std::__1::__compressed_pair.59" = type { %"struct.std::__1::__compressed_pair_elem.60" }
%"struct.std::__1::__compressed_pair_elem.60" = type { %"struct.std::__1::pair"* }
%"class.std::__1::__wrap_iter" = type { %"struct.std::__1::pair"* }
%"struct.LL2W::DFSResult" = type { %"class.LL2W::Graph"*, %"class.std::__1::unordered_map.64", %"class.std::__1::unordered_map.88", %"class.std::__1::unordered_map.88" }
%"class.std::__1::unordered_map.64" = type { %"class.std::__1::__hash_table.65" }
%"class.std::__1::__hash_table.65" = type <{ %"class.std::__1::unique_ptr.66", %"class.std::__1::__compressed_pair.76", %"class.std::__1::__compressed_pair.81", %"class.std::__1::__compressed_pair.84", [4 x i8] }>
%"class.std::__1::unique_ptr.66" = type { %"class.std::__1::__compressed_pair.67" }
%"class.std::__1::__compressed_pair.67" = type { %"struct.std::__1::__compressed_pair_elem.68", %"struct.std::__1::__compressed_pair_elem.70" }
%"struct.std::__1::__compressed_pair_elem.68" = type { %"struct.std::__1::__hash_node_base.69"** }
%"struct.std::__1::__hash_node_base.69" = type { %"struct.std::__1::__hash_node_base.69"* }
%"struct.std::__1::__compressed_pair_elem.70" = type { %"class.std::__1::__bucket_list_deallocator.71" }
%"class.std::__1::__bucket_list_deallocator.71" = type { %"class.std::__1::__compressed_pair.72" }
%"class.std::__1::__compressed_pair.72" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.76" = type { %"struct.std::__1::__compressed_pair_elem.77" }
%"struct.std::__1::__compressed_pair_elem.77" = type { %"struct.std::__1::__hash_node_base.69" }
%"class.std::__1::__compressed_pair.81" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.84" = type { %"struct.std::__1::__compressed_pair_elem.16" }
%"class.std::__1::unordered_map.88" = type { %"class.std::__1::__hash_table.89" }
%"class.std::__1::__hash_table.89" = type <{ %"class.std::__1::unique_ptr.90", %"class.std::__1::__compressed_pair.100", %"class.std::__1::__compressed_pair.105", %"class.std::__1::__compressed_pair.108", [4 x i8] }>
%"class.std::__1::unique_ptr.90" = type { %"class.std::__1::__compressed_pair.91" }
%"class.std::__1::__compressed_pair.91" = type { %"struct.std::__1::__compressed_pair_elem.92", %"struct.std::__1::__compressed_pair_elem.94" }
%"struct.std::__1::__compressed_pair_elem.92" = type { %"struct.std::__1::__hash_node_base.93"** }
%"struct.std::__1::__hash_node_base.93" = type { %"struct.std::__1::__hash_node_base.93"* }
%"struct.std::__1::__compressed_pair_elem.94" = type { %"class.std::__1::__bucket_list_deallocator.95" }
%"class.std::__1::__bucket_list_deallocator.95" = type { %"class.std::__1::__compressed_pair.96" }
%"class.std::__1::__compressed_pair.96" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.100" = type { %"struct.std::__1::__compressed_pair_elem.101" }
%"struct.std::__1::__compressed_pair_elem.101" = type { %"struct.std::__1::__hash_node_base.93" }
%"class.std::__1::__compressed_pair.105" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.108" = type { %"struct.std::__1::__compressed_pair_elem.16" }
%"class.std::__1::allocator.62" = type { i8 }
%"struct.std::__1::integral_constant" = type { i8 }
%"struct.std::__1::__has_destroy" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.61" = type { i8 }
%"class.std::__1::allocator.46" = type { i8 }
%"struct.std::__1::__hash_node" = type { %"struct.std::__1::__hash_node_base.36", i64, %"struct.std::__1::__hash_value_type" }
%"struct.std::__1::__hash_value_type" = type { %"struct.std::__1::pair.119" }
%"struct.std::__1::pair.119" = type { %"class.LL2W::Node"*, %"class.std::__1::unordered_set" }
%"class.std::__1::unordered_set" = type { %"class.std::__1::__hash_table.120" }
%"class.std::__1::__hash_table.120" = type <{ %"class.std::__1::unique_ptr.121", %"class.std::__1::__compressed_pair.131", %"class.std::__1::__compressed_pair.136", %"class.std::__1::__compressed_pair.138", [4 x i8] }>
%"class.std::__1::unique_ptr.121" = type { %"class.std::__1::__compressed_pair.122" }
%"class.std::__1::__compressed_pair.122" = type { %"struct.std::__1::__compressed_pair_elem.123", %"struct.std::__1::__compressed_pair_elem.125" }
%"struct.std::__1::__compressed_pair_elem.123" = type { %"struct.std::__1::__hash_node_base.124"** }
%"struct.std::__1::__hash_node_base.124" = type { %"struct.std::__1::__hash_node_base.124"* }
%"struct.std::__1::__compressed_pair_elem.125" = type { %"class.std::__1::__bucket_list_deallocator.126" }
%"class.std::__1::__bucket_list_deallocator.126" = type { %"class.std::__1::__compressed_pair.127" }
%"class.std::__1::__compressed_pair.127" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.131" = type { %"struct.std::__1::__compressed_pair_elem.132" }
%"struct.std::__1::__compressed_pair_elem.132" = type { %"struct.std::__1::__hash_node_base.124" }
%"class.std::__1::__compressed_pair.136" = type { %"struct.std::__1::__compressed_pair_elem" }
%"class.std::__1::__compressed_pair.138" = type { %"struct.std::__1::__compressed_pair_elem.16" }
%"struct.std::__1::integral_constant.141" = type { i8 }
%"struct.std::__1::__has_destroy.142" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.45" = type { i8 }
%"class.std::__1::allocator.134" = type { i8 }
%"struct.std::__1::__hash_node.143" = type { %"struct.std::__1::__hash_node_base.124", i64, %"class.LL2W::Node"* }
%"struct.std::__1::__has_destroy.144" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.133" = type { i8 }
%"class.std::__1::allocator.129" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.128" = type { i8 }
%"class.std::__1::allocator.41" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.40" = type { i8 }
%"class.std::__1::allocator.103" = type { i8 }
%"struct.std::__1::__hash_node.145" = type { %"struct.std::__1::__hash_node_base.93", i64, %"struct.std::__1::__hash_value_type.146" }
%"struct.std::__1::__hash_value_type.146" = type { %"struct.std::__1::pair.147" }
%"struct.std::__1::pair.147" = type <{ %"class.LL2W::Node"*, i32, [4 x i8] }>
%"struct.std::__1::__has_destroy.148" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.102" = type { i8 }
%"class.std::__1::allocator.98" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.97" = type { i8 }
%"class.std::__1::allocator.79" = type { i8 }
%"struct.std::__1::__hash_node.149" = type { %"struct.std::__1::__hash_node_base.69", i64, %"struct.std::__1::__hash_value_type.150" }
%"struct.std::__1::__hash_value_type.150" = type { %"struct.std::__1::pair.151" }
%"struct.std::__1::pair.151" = type { %"class.LL2W::Node"*, %"class.LL2W::Node"* }
%"struct.std::__1::__has_destroy.152" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.78" = type { i8 }
%"class.std::__1::allocator.74" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.73" = type { i8 }
%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry" = type { i8, %"class.std::__1::basic_ostream"* }
%"class.std::__1::ostreambuf_iterator" = type { %"class.std::__1::basic_streambuf"* }
%"class.std::__1::basic_streambuf" = type { i32 (...)**, %"class.std::__1::locale", i8*, i8*, i8*, i8*, i8*, i8* }
%"class.std::__1::locale" = type { %"class.std::__1::locale::__imp"* }
%"class.std::__1::locale::__imp" = type opaque
%"class.std::__1::basic_ios" = type <{ %"class.std::__1::ios_base", %"class.std::__1::basic_ostream"*, i32, [4 x i8] }>
%"class.std::__1::__basic_string_common" = type { i8 }
%"struct.std::__1::__compressed_pair_elem.21" = type { i8 }
%"class.std::__1::allocator.22" = type { i8 }
%"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short" = type { %union.anon.20, [23 x i8] }
%union.anon.20 = type { i8 }
%"struct.std::__1::iterator" = type { i8 }
%"class.std::__1::ctype" = type <{ %"class.std::__1::locale::facet", i32*, i8, [7 x i8] }>
%"class.std::__1::locale::facet" = type { %"class.std::__1::__shared_count" }
%"class.std::__1::__shared_count" = type { i32 (...)**, i64 }

@_ZNSt3__14cerrE = external global %"class.std::__1::basic_ostream", align 8
@.str = private unnamed_addr constant [8 x i8] c"Usage: \00", align 1
@.str.1 = private unnamed_addr constant [19 x i8] c" <input> <output>\0A\00", align 1
@.str.2 = private unnamed_addr constant [2 x i8] c"R\00", align 1
@.str.3 = private unnamed_addr constant [2 x i8] c"A\00", align 1
@.str.4 = private unnamed_addr constant [2 x i8] c"B\00", align 1
@.str.5 = private unnamed_addr constant [2 x i8] c"C\00", align 1
@.str.6 = private unnamed_addr constant [2 x i8] c"D\00", align 1
@.str.7 = private unnamed_addr constant [2 x i8] c"E\00", align 1
@.str.8 = private unnamed_addr constant [2 x i8] c"F\00", align 1
@.str.9 = private unnamed_addr constant [2 x i8] c"G\00", align 1
@.str.10 = private unnamed_addr constant [2 x i8] c"H\00", align 1
@.str.11 = private unnamed_addr constant [2 x i8] c"I\00", align 1
@.str.12 = private unnamed_addr constant [2 x i8] c"J\00", align 1
@.str.13 = private unnamed_addr constant [2 x i8] c"K\00", align 1
@.str.14 = private unnamed_addr constant [2 x i8] c"L\00", align 1
@.str.15 = private unnamed_addr constant [84 x i8] c"A:D B:A B:D B:E C:F C:G D:L E:H F:I G:I G:J H:E H:K I:K J:I K:I K:R L:H R:A R:B R:C\00", align 1
@.str.16 = private unnamed_addr constant [16 x i8] c"graph_lt_in.png\00", align 1
@.str.17 = private unnamed_addr constant [3 x i8] c"TB\00", align 1
@.str.18 = private unnamed_addr constant [17 x i8] c"graph_lt_out.png\00", align 1
@.str.19 = private unnamed_addr constant [3 x i8] c"BT\00", align 1
@.str.20 = private unnamed_addr constant [2 x i8] c"1\00", align 1
@.str.21 = private unnamed_addr constant [2 x i8] c"2\00", align 1
@.str.22 = private unnamed_addr constant [2 x i8] c"3\00", align 1
@.str.23 = private unnamed_addr constant [2 x i8] c"4\00", align 1
@.str.24 = private unnamed_addr constant [2 x i8] c"5\00", align 1
@.str.25 = private unnamed_addr constant [2 x i8] c"6\00", align 1
@.str.26 = private unnamed_addr constant [2 x i8] c"7\00", align 1
@.str.27 = private unnamed_addr constant [2 x i8] c"8\00", align 1
@.str.28 = private unnamed_addr constant [2 x i8] c"9\00", align 1
@.str.29 = private unnamed_addr constant [3 x i8] c"10\00", align 1
@.str.30 = private unnamed_addr constant [3 x i8] c"11\00", align 1
@.str.31 = private unnamed_addr constant [59 x i8] c"1:2 2:3 2:11 3:4 3:8 4:5 5:6 6:5 6:7 7:2 8:9 9:6 9:10 10:8\00", align 1
@.str.32 = private unnamed_addr constant [16 x i8] c"graph_dj_in.png\00", align 1
@.str.33 = private unnamed_addr constant [16 x i8] c"graph_dj_dt.png\00", align 1
@.str.34 = private unnamed_addr constant [17 x i8] c"graph_dj_out.png\00", align 1
@_ZNSt3__14coutE = external global %"class.std::__1::basic_ostream", align 8
@.str.35 = private unnamed_addr constant [6 x i8] c" <-> \00", align 1
@.str.36 = private unnamed_addr constant [2 x i8] c"\0A\00", align 1
@.str.37 = private unnamed_addr constant [4 x i8] c"one\00", align 1
@.str.38 = private unnamed_addr constant [4 x i8] c"two\00", align 1
@.str.39 = private unnamed_addr constant [6 x i8] c"three\00", align 1
@.str.40 = private unnamed_addr constant [5 x i8] c"four\00", align 1
@.str.41 = private unnamed_addr constant [78 x i8] c"one:two two:three three:four four:one one:four one:three two:four three:three\00", align 1
@.str.42 = private unnamed_addr constant [44 x i8] c"1:2 1:5 1:8 2:3 3:4 2:4 4:5 6:7 7:6 6:8 8:9\00", align 1
@.str.43 = private unnamed_addr constant [18 x i8] c"graph_complex.png\00", align 1
@.str.44 = private unnamed_addr constant [15 x i8] c"graph_1234.png\00", align 1
@.str.45 = private unnamed_addr constant [14 x i8] c"graph_123.png\00", align 1
@.str.46 = private unnamed_addr constant [19 x i8] c"graph_unlinked.png\00", align 1
@.str.47 = private unnamed_addr constant [9 x i8] c"basic.ll\00", align 1
@_ZN4LL2W6Parser4rootE = external global %"class.LL2W::ASTNode"*, align 8
@_ZNSt3__15ctypeIcE2idE = external global %"class.std::__1::locale::id", align 8
*/
@_ZTVN4LL2W7DJGraphE = external unnamed_addr constant { [3 x i8*] }, section "foo", comdat($what), align 8
; Function Attrs: noinline norecurse optnone ssp uwtable
define i32 @main(i32, i8**) #0 {
  %foo = alloca i32, i32 666
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  %5 = alloca i8**, align 8
  store i32 0, i32* %3, align 4
  store i32 %0, i32* %4, align 4
  store i8** %1, i8*** %5, align 8
  %6 = load i32, i32* %4, align 4
  %7 = icmp ne i32 %6, 3
  br i1 %7, label %8, label %15
  br label %foo

; <label>:8:                                      ; preds = %2
  %9 = tail call nnan reassoc ccc zeroext signext inreg dereferenceable(160) addrspace(42) %"class.std::__1::basic_ostream"* @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc(%"class.std::__1::basic_ostream"* dereferenceable(160) @_ZNSt3__14cerrE, i8* getelementptr inbounds ([8 x i8], [8 x i8]* @.str, i32 0, i32 0)) #1 #2 #3
  %10 = load i8**, i8*** %5, align 8
  %11 = getelementptr inbounds i8*, i8** %10, i64 0, inrange i64 1
  %12 = load i8*, i8** %11, align 8
  %13 = call dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc(%"class.std::__1::basic_ostream"* dereferenceable(160) %9, i8* %12)
  %14 = call dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc(%"class.std::__1::basic_ostream"* dereferenceable(160) %13, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.1, i32 0, i32 0))
  store i32 1, i32* %3, align 4
  br label %16

; <label>:15:                                     ; preds = %2
  call void @_Z10parsertestv()
  br label %16

; <label>:16:                                     ; preds = %15, %8
  %17 = load i32, i32* %3, align 4
  ret i32 %17
  ret { i32, i8 } { i32 4, i8 2 }
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc(%"class.std::__1::basic_ostream"* dereferenceable(160), i8*) #1 {
  %3 = alloca %"class.std::__1::basic_ostream"*, align 8
  %4 = alloca i8*, align 8
  store %"class.std::__1::basic_ostream"* %0, %"class.std::__1::basic_ostream"** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %3, align 8
  %6 = load i8*, i8** %4, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = call i64 @_ZNSt3__111char_traitsIcE6lengthEPKc(i8* %7) #8
  %9 = call dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m(%"class.std::__1::basic_ostream"* dereferenceable(160) %5, i8* %6, i64 %8)
  ret %"class.std::__1::basic_ostream"* %9
}

; Function Attrs: noinline optnone ssp uwtable
define void @_Z10parsertestv() #1 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %1 = alloca %"class.std::__1::basic_string", align 8
  %2 = alloca i8*
  %3 = alloca i32
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %1, i8* getelementptr inbounds ([9 x i8], [9 x i8]* @.str.47, i32 0, i32 0))
  invoke void @_ZN4LL2W6Parser4openERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"class.std::__1::basic_string"* dereferenceable(24) %1)
          to label %4 unwind label %6

; <label>:4:                                      ; preds = %0
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %1) #8
  call void @_ZN4LL2W6Parser5parseEv()
  %5 = load %"class.LL2W::ASTNode"*, %"class.LL2W::ASTNode"** @_ZN4LL2W6Parser4rootE, align 8
  call void @_ZN4LL2W7ASTNode5debugEib(%"class.LL2W::ASTNode"* %5, i32 0, i1 zeroext false)
  call void @_ZN4LL2W6Parser4doneEv()
  ret void

; <label>:6:                                      ; preds = %0
  %7 = landingpad { i8*, i32 }
          cleanup
  %8 = extractvalue { i8*, i32 } %7, 0
  store i8* %8, i8** %2, align 8
  %9 = extractvalue { i8*, i32 } %7, 1
  store i32 %9, i32* %3, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %1) #8
  br label %10

; <label>:10:                                     ; preds = %6
  %11 = load i8*, i8** %2, align 8
  %12 = load i32, i32* %3, align 4
  %13 = insertvalue { i8*, i32 } undef, i8* %11, 0
  %14 = insertvalue { i8*, i32 } %13, i32 %12, 1
  resume { i8*, i32 } %14
}/*

; Function Attrs: noinline optnone ssp uwtable
define void @_Z6lttestv() #1 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %1 = alloca %"class.LL2W::Graph", align 8
  %2 = alloca %"class.std::initializer_list", align 8
  %3 = alloca [13 x %"class.std::__1::basic_string"], align 8
  %4 = alloca %"class.std::__1::basic_string"*, align 8
  %5 = alloca i8*
  %6 = alloca i32
  %7 = alloca %"class.std::__1::basic_string", align 8
  %8 = alloca %"class.std::__1::basic_string", align 8
  %9 = alloca %"class.std::__1::basic_string", align 8
  %10 = alloca %"class.LL2W::DTree", align 8
  %11 = alloca %"class.std::__1::basic_string", align 8
  %12 = alloca %"class.std::__1::basic_string", align 8
  %13 = getelementptr inbounds [13 x %"class.std::__1::basic_string"], [13 x %"class.std::__1::basic_string"]* %3, i64 0, i64 0
  store %"class.std::__1::basic_string"* %13, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %13, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.2, i32 0, i32 0))
          to label %14 unwind label %71

; <label>:14:                                     ; preds = %0
  %15 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %13, i64 1
  store %"class.std::__1::basic_string"* %15, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %15, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.3, i32 0, i32 0))
          to label %16 unwind label %71

; <label>:16:                                     ; preds = %14
  %17 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %15, i64 1
  store %"class.std::__1::basic_string"* %17, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %17, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.4, i32 0, i32 0))
          to label %18 unwind label %71

; <label>:18:                                     ; preds = %16
  %19 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %17, i64 1
  store %"class.std::__1::basic_string"* %19, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %19, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.5, i32 0, i32 0))
          to label %20 unwind label %71

; <label>:20:                                     ; preds = %18
  %21 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %19, i64 1
  store %"class.std::__1::basic_string"* %21, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %21, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.6, i32 0, i32 0))
          to label %22 unwind label %71

; <label>:22:                                     ; preds = %20
  %23 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %21, i64 1
  store %"class.std::__1::basic_string"* %23, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %23, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.7, i32 0, i32 0))
          to label %24 unwind label %71

; <label>:24:                                     ; preds = %22
  %25 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %23, i64 1
  store %"class.std::__1::basic_string"* %25, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %25, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.8, i32 0, i32 0))
          to label %26 unwind label %71

; <label>:26:                                     ; preds = %24
  %27 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %25, i64 1
  store %"class.std::__1::basic_string"* %27, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %27, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.9, i32 0, i32 0))
          to label %28 unwind label %71

; <label>:28:                                     ; preds = %26
  %29 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %27, i64 1
  store %"class.std::__1::basic_string"* %29, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %29, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.10, i32 0, i32 0))
          to label %30 unwind label %71

; <label>:30:                                     ; preds = %28
  %31 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %29, i64 1
  store %"class.std::__1::basic_string"* %31, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %31, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.11, i32 0, i32 0))
          to label %32 unwind label %71

; <label>:32:                                     ; preds = %30
  %33 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %31, i64 1
  store %"class.std::__1::basic_string"* %33, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %33, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.12, i32 0, i32 0))
          to label %34 unwind label %71

; <label>:34:                                     ; preds = %32
  %35 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %33, i64 1
  store %"class.std::__1::basic_string"* %35, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %35, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.13, i32 0, i32 0))
          to label %36 unwind label %71

; <label>:36:                                     ; preds = %34
  %37 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %35, i64 1
  store %"class.std::__1::basic_string"* %37, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %37, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.14, i32 0, i32 0))
          to label %38 unwind label %71

; <label>:38:                                     ; preds = %36
  %39 = getelementptr inbounds %"class.std::initializer_list", %"class.std::initializer_list"* %2, i32 0, i32 0
  %40 = getelementptr inbounds [13 x %"class.std::__1::basic_string"], [13 x %"class.std::__1::basic_string"]* %3, i64 0, i64 0
  store %"class.std::__1::basic_string"* %40, %"class.std::__1::basic_string"** %39, align 8
  %41 = getelementptr inbounds %"class.std::initializer_list", %"class.std::initializer_list"* %2, i32 0, i32 1
  store i64 13, i64* %41, align 8
  %42 = bitcast %"class.std::initializer_list"* %2 to { %"class.std::__1::basic_string"*, i64 }*
  %43 = getelementptr inbounds { %"class.std::__1::basic_string"*, i64 }, { %"class.std::__1::basic_string"*, i64 }* %42, i32 0, i32 0
  %44 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %43, align 8
  %45 = getelementptr inbounds { %"class.std::__1::basic_string"*, i64 }, { %"class.std::__1::basic_string"*, i64 }* %42, i32 0, i32 1
  %46 = load i64, i64* %45, align 8
  invoke void @_ZN4LL2W5GraphC1ESt16initializer_listINSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEE(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* %44, i64 %46)
          to label %47 unwind label %82

; <label>:47:                                     ; preds = %38
  %48 = getelementptr inbounds [13 x %"class.std::__1::basic_string"], [13 x %"class.std::__1::basic_string"]* %3, i32 0, i32 0
  %49 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %48, i64 13
  br label %50

; <label>:50:                                     ; preds = %50, %47
  %51 = phi %"class.std::__1::basic_string"* [ %49, %47 ], [ %52, %50 ]
  %52 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %51, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %52) #8
  %53 = icmp eq %"class.std::__1::basic_string"* %52, %48
  br i1 %53, label %54, label %50

; <label>:54:                                     ; preds = %50
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %7, i8* getelementptr inbounds ([84 x i8], [84 x i8]* @.str.15, i32 0, i32 0))
          to label %55 unwind label %93

; <label>:55:                                     ; preds = %54
  invoke void @_ZN4LL2W5Graph8addEdgesERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %7)
          to label %56 unwind label %97

; <label>:56:                                     ; preds = %55
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %7) #8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %8, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.16, i32 0, i32 0))
          to label %57 unwind label %93

; <label>:57:                                     ; preds = %56
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %9, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.17, i32 0, i32 0))
          to label %58 unwind label %101

; <label>:58:                                     ; preds = %57
  invoke void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %8, %"class.std::__1::basic_string"* dereferenceable(24) %9)
          to label %59 unwind label %105

; <label>:59:                                     ; preds = %58
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %9) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %8) #8
  %60 = invoke i32 @"\01_usleep"(i32 100000)
          to label %61 unwind label %93

; <label>:61:                                     ; preds = %59
  %62 = invoke dereferenceable(88) %"class.LL2W::Node"* @_ZNK4LL2W5GraphixEm(%"class.LL2W::Graph"* %1, i64 0)
          to label %63 unwind label %93

; <label>:63:                                     ; preds = %61
  invoke void @_ZN4LL2W5DTreeC1ERNS_5GraphERNS_4NodeE(%"class.LL2W::DTree"* %10, %"class.LL2W::Graph"* dereferenceable(72) %1, %"class.LL2W::Node"* dereferenceable(88) %62)
          to label %64 unwind label %93

; <label>:64:                                     ; preds = %63
  %65 = bitcast %"class.LL2W::DTree"* %10 to %"class.LL2W::Graph"*
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %11, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.18, i32 0, i32 0))
          to label %66 unwind label %110

; <label>:66:                                     ; preds = %64
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %12, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.19, i32 0, i32 0))
          to label %67 unwind label %114

; <label>:67:                                     ; preds = %66
  invoke void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"* %65, %"class.std::__1::basic_string"* dereferenceable(24) %11, %"class.std::__1::basic_string"* dereferenceable(24) %12)
          to label %68 unwind label %118

; <label>:68:                                     ; preds = %67
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %12) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %11) #8
  call void @_ZN4LL2W5DTreeD1Ev(%"class.LL2W::DTree"* %10) #8
  %69 = invoke i32 @"\01_usleep"(i32 100000)
          to label %70 unwind label %93

; <label>:70:                                     ; preds = %68
  call void @_ZN4LL2W5GraphD1Ev(%"class.LL2W::Graph"* %1) #8
  ret void

; <label>:71:                                     ; preds = %36, %34, %32, %30, %28, %26, %24, %22, %20, %18, %16, %14, %0
  %72 = landingpad { i8*, i32 }
          cleanup
  %73 = extractvalue { i8*, i32 } %72, 0
  store i8* %73, i8** %5, align 8
  %74 = extractvalue { i8*, i32 } %72, 1
  store i32 %74, i32* %6, align 4
  %75 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %4, align 8
  %76 = icmp eq %"class.std::__1::basic_string"* %13, %75
  br i1 %76, label %81, label %77

; <label>:77:                                     ; preds = %77, %71
  %78 = phi %"class.std::__1::basic_string"* [ %75, %71 ], [ %79, %77 ]
  %79 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %78, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %79) #8
  %80 = icmp eq %"class.std::__1::basic_string"* %79, %13
  br i1 %80, label %81, label %77

; <label>:81:                                     ; preds = %77, %71
  br label %125

; <label>:82:                                     ; preds = %38
  %83 = landingpad { i8*, i32 }
          cleanup
  %84 = extractvalue { i8*, i32 } %83, 0
  store i8* %84, i8** %5, align 8
  %85 = extractvalue { i8*, i32 } %83, 1
  store i32 %85, i32* %6, align 4
  %86 = getelementptr inbounds [13 x %"class.std::__1::basic_string"], [13 x %"class.std::__1::basic_string"]* %3, i32 0, i32 0
  %87 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %86, i64 13
  br label %88

; <label>:88:                                     ; preds = %88, %82
  %89 = phi %"class.std::__1::basic_string"* [ %87, %82 ], [ %90, %88 ]
  %90 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %89, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %90) #8
  %91 = icmp eq %"class.std::__1::basic_string"* %90, %86
  br i1 %91, label %92, label %88

; <label>:92:                                     ; preds = %88
  br label %125

; <label>:93:                                     ; preds = %68, %63, %61, %59, %56, %54
  %94 = landingpad { i8*, i32 }
          cleanup
  %95 = extractvalue { i8*, i32 } %94, 0
  store i8* %95, i8** %5, align 8
  %96 = extractvalue { i8*, i32 } %94, 1
  store i32 %96, i32* %6, align 4
  br label %124

; <label>:97:                                     ; preds = %55
  %98 = landingpad { i8*, i32 }
          cleanup
  %99 = extractvalue { i8*, i32 } %98, 0
  store i8* %99, i8** %5, align 8
  %100 = extractvalue { i8*, i32 } %98, 1
  store i32 %100, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %7) #8
  br label %124

; <label>:101:                                    ; preds = %57
  %102 = landingpad { i8*, i32 }
          cleanup
  %103 = extractvalue { i8*, i32 } %102, 0
  store i8* %103, i8** %5, align 8
  %104 = extractvalue { i8*, i32 } %102, 1
  store i32 %104, i32* %6, align 4
  br label %109

; <label>:105:                                    ; preds = %58
  %106 = landingpad { i8*, i32 }
          cleanup
  %107 = extractvalue { i8*, i32 } %106, 0
  store i8* %107, i8** %5, align 8
  %108 = extractvalue { i8*, i32 } %106, 1
  store i32 %108, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %9) #8
  br label %109

; <label>:109:                                    ; preds = %105, %101
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %8) #8
  br label %124

; <label>:110:                                    ; preds = %64
  %111 = landingpad { i8*, i32 }
          cleanup
  %112 = extractvalue { i8*, i32 } %111, 0
  store i8* %112, i8** %5, align 8
  %113 = extractvalue { i8*, i32 } %111, 1
  store i32 %113, i32* %6, align 4
  br label %123

; <label>:114:                                    ; preds = %66
  %115 = landingpad { i8*, i32 }
          cleanup
  %116 = extractvalue { i8*, i32 } %115, 0
  store i8* %116, i8** %5, align 8
  %117 = extractvalue { i8*, i32 } %115, 1
  store i32 %117, i32* %6, align 4
  br label %122

; <label>:118:                                    ; preds = %67
  %119 = landingpad { i8*, i32 }
          cleanup
  %120 = extractvalue { i8*, i32 } %119, 0
  store i8* %120, i8** %5, align 8
  %121 = extractvalue { i8*, i32 } %119, 1
  store i32 %121, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %12) #8
  br label %122

; <label>:122:                                    ; preds = %118, %114
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %11) #8
  br label %123

; <label>:123:                                    ; preds = %122, %110
  call void @_ZN4LL2W5DTreeD1Ev(%"class.LL2W::DTree"* %10) #8
  br label %124

; <label>:124:                                    ; preds = %123, %109, %97, %93
  call void @_ZN4LL2W5GraphD1Ev(%"class.LL2W::Graph"* %1) #8
  br label %125

; <label>:125:                                    ; preds = %124, %92, %81
  %126 = load i8*, i8** %5, align 8
  %127 = load i32, i32* %6, align 4
  %128 = insertvalue { i8*, i32 } undef, i8* %126, 0
  %129 = insertvalue { i8*, i32 } %128, i32 %127, 1
  resume { i8*, i32 } %129
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"*, i8*) unnamed_addr #1 align 2 {
  %3 = alloca %"class.std::__1::basic_string"*, align 8
  %4 = alloca i8*, align 8
  store %"class.std::__1::basic_string"* %0, %"class.std::__1::basic_string"** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %3, align 8
  %6 = load i8*, i8** %4, align 8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2IDnEEPKc(%"class.std::__1::basic_string"* %5, i8* %6)
  ret void
}

declare i32 @__gxx_personality_v0(...)

; Function Attrs: nounwind
declare void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"*) unnamed_addr #2

declare void @_ZN4LL2W5GraphC1ESt16initializer_listINSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEE(%"class.LL2W::Graph"*, %"class.std::__1::basic_string"*, i64) unnamed_addr #3

declare void @_ZN4LL2W5Graph8addEdgesERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"class.LL2W::Graph"*, %"class.std::__1::basic_string"* dereferenceable(24)) #3

declare void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"*, %"class.std::__1::basic_string"* dereferenceable(24), %"class.std::__1::basic_string"* dereferenceable(24)) #3

declare i32 @"\01_usleep"(i32) #3

declare dereferenceable(88) %"class.LL2W::Node"* @_ZNK4LL2W5GraphixEm(%"class.LL2W::Graph"*, i64) #3

declare void @_ZN4LL2W5DTreeC1ERNS_5GraphERNS_4NodeE(%"class.LL2W::DTree"*, %"class.LL2W::Graph"* dereferenceable(72), %"class.LL2W::Node"* dereferenceable(88)) unnamed_addr #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZN4LL2W5DTreeD1Ev(%"class.LL2W::DTree"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.LL2W::DTree"*, align 8
  store %"class.LL2W::DTree"* %0, %"class.LL2W::DTree"** %2, align 8
  %3 = load %"class.LL2W::DTree"*, %"class.LL2W::DTree"** %2, align 8
  call void @_ZN4LL2W5DTreeD2Ev(%"class.LL2W::DTree"* %3) #8
  ret void
}

; Function Attrs: nounwind
declare void @_ZN4LL2W5GraphD1Ev(%"class.LL2W::Graph"*) unnamed_addr #2

; Function Attrs: noinline optnone ssp uwtable
define void @_Z6djtestv() #1 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %1 = alloca %"class.LL2W::Graph", align 8
  %2 = alloca %"class.std::initializer_list", align 8
  %3 = alloca [11 x %"class.std::__1::basic_string"], align 8
  %4 = alloca %"class.std::__1::basic_string"*, align 8
  %5 = alloca i8*
  %6 = alloca i32
  %7 = alloca %"class.std::__1::basic_string", align 8
  %8 = alloca %"class.std::__1::basic_string", align 8
  %9 = alloca %"class.std::__1::basic_string", align 8
  %10 = alloca %"class.LL2W::DJGraph", align 8
  %11 = alloca %"class.LL2W::DTree", align 8
  %12 = alloca %"class.std::__1::basic_string", align 8
  %13 = alloca %"class.std::__1::basic_string", align 8
  %14 = alloca %"class.std::__1::basic_string", align 8
  %15 = alloca %"class.std::__1::basic_string", align 8
  %16 = alloca %"class.std::__1::vector"*, align 8
  %17 = alloca %"class.std::__1::__wrap_iter", align 8
  %18 = alloca %"class.std::__1::__wrap_iter", align 8
  %19 = alloca %"struct.std::__1::pair", align 8
  %20 = alloca %"class.LL2W::Node"*, align 8
  %21 = alloca %"class.LL2W::Node"*, align 8
  %22 = getelementptr inbounds [11 x %"class.std::__1::basic_string"], [11 x %"class.std::__1::basic_string"]* %3, i64 0, i64 0
  store %"class.std::__1::basic_string"* %22, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %22, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.20, i32 0, i32 0))
          to label %23 unwind label %112

; <label>:23:                                     ; preds = %0
  %24 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %22, i64 1
  store %"class.std::__1::basic_string"* %24, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %24, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.21, i32 0, i32 0))
          to label %25 unwind label %112

; <label>:25:                                     ; preds = %23
  %26 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %24, i64 1
  store %"class.std::__1::basic_string"* %26, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %26, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.22, i32 0, i32 0))
          to label %27 unwind label %112

; <label>:27:                                     ; preds = %25
  %28 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %26, i64 1
  store %"class.std::__1::basic_string"* %28, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %28, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i32 0, i32 0))
          to label %29 unwind label %112

; <label>:29:                                     ; preds = %27
  %30 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %28, i64 1
  store %"class.std::__1::basic_string"* %30, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %30, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.24, i32 0, i32 0))
          to label %31 unwind label %112

; <label>:31:                                     ; preds = %29
  %32 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %30, i64 1
  store %"class.std::__1::basic_string"* %32, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %32, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.25, i32 0, i32 0))
          to label %33 unwind label %112

; <label>:33:                                     ; preds = %31
  %34 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %32, i64 1
  store %"class.std::__1::basic_string"* %34, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %34, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.26, i32 0, i32 0))
          to label %35 unwind label %112

; <label>:35:                                     ; preds = %33
  %36 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %34, i64 1
  store %"class.std::__1::basic_string"* %36, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %36, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.27, i32 0, i32 0))
          to label %37 unwind label %112

; <label>:37:                                     ; preds = %35
  %38 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %36, i64 1
  store %"class.std::__1::basic_string"* %38, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %38, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.28, i32 0, i32 0))
          to label %39 unwind label %112

; <label>:39:                                     ; preds = %37
  %40 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %38, i64 1
  store %"class.std::__1::basic_string"* %40, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %40, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.29, i32 0, i32 0))
          to label %41 unwind label %112

; <label>:41:                                     ; preds = %39
  %42 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %40, i64 1
  store %"class.std::__1::basic_string"* %42, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %42, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.30, i32 0, i32 0))
          to label %43 unwind label %112

; <label>:43:                                     ; preds = %41
  %44 = getelementptr inbounds %"class.std::initializer_list", %"class.std::initializer_list"* %2, i32 0, i32 0
  %45 = getelementptr inbounds [11 x %"class.std::__1::basic_string"], [11 x %"class.std::__1::basic_string"]* %3, i64 0, i64 0
  store %"class.std::__1::basic_string"* %45, %"class.std::__1::basic_string"** %44, align 8
  %46 = getelementptr inbounds %"class.std::initializer_list", %"class.std::initializer_list"* %2, i32 0, i32 1
  store i64 11, i64* %46, align 8
  %47 = bitcast %"class.std::initializer_list"* %2 to { %"class.std::__1::basic_string"*, i64 }*
  %48 = getelementptr inbounds { %"class.std::__1::basic_string"*, i64 }, { %"class.std::__1::basic_string"*, i64 }* %47, i32 0, i32 0
  %49 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %48, align 8
  %50 = getelementptr inbounds { %"class.std::__1::basic_string"*, i64 }, { %"class.std::__1::basic_string"*, i64 }* %47, i32 0, i32 1
  %51 = load i64, i64* %50, align 8
  invoke void @_ZN4LL2W5GraphC1ESt16initializer_listINSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEE(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* %49, i64 %51)
          to label %52 unwind label %123

; <label>:52:                                     ; preds = %43
  %53 = getelementptr inbounds [11 x %"class.std::__1::basic_string"], [11 x %"class.std::__1::basic_string"]* %3, i32 0, i32 0
  %54 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %53, i64 11
  br label %55

; <label>:55:                                     ; preds = %55, %52
  %56 = phi %"class.std::__1::basic_string"* [ %54, %52 ], [ %57, %55 ]
  %57 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %56, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %57) #8
  %58 = icmp eq %"class.std::__1::basic_string"* %57, %53
  br i1 %58, label %59, label %55

; <label>:59:                                     ; preds = %55
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %7, i8* getelementptr inbounds ([59 x i8], [59 x i8]* @.str.31, i32 0, i32 0))
          to label %60 unwind label %134

; <label>:60:                                     ; preds = %59
  invoke void @_ZN4LL2W5Graph8addEdgesERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %7)
          to label %61 unwind label %138

; <label>:61:                                     ; preds = %60
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %7) #8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %8, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.32, i32 0, i32 0))
          to label %62 unwind label %134

; <label>:62:                                     ; preds = %61
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %9, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.17, i32 0, i32 0))
          to label %63 unwind label %142

; <label>:63:                                     ; preds = %62
  invoke void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %8, %"class.std::__1::basic_string"* dereferenceable(24) %9)
          to label %64 unwind label %146

; <label>:64:                                     ; preds = %63
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %9) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %8) #8
  %65 = invoke i32 @"\01_usleep"(i32 100000)
          to label %66 unwind label %134

; <label>:66:                                     ; preds = %64
  %67 = invoke dereferenceable(88) %"class.LL2W::Node"* @_ZNK4LL2W5GraphixEm(%"class.LL2W::Graph"* %1, i64 0)
          to label %68 unwind label %134

; <label>:68:                                     ; preds = %66
  invoke void @_ZN4LL2W7DJGraphC1ERNS_5GraphERNS_4NodeE(%"class.LL2W::DJGraph"* %10, %"class.LL2W::Graph"* dereferenceable(72) %1, %"class.LL2W::Node"* dereferenceable(88) %67)
          to label %69 unwind label %134

; <label>:69:                                     ; preds = %68
  %70 = invoke dereferenceable(88) %"class.LL2W::Node"* @_ZNK4LL2W5GraphixEm(%"class.LL2W::Graph"* %1, i64 0)
          to label %71 unwind label %151

; <label>:71:                                     ; preds = %69
  invoke void @_ZN4LL2W5DTreeC1ERNS_5GraphERNS_4NodeE(%"class.LL2W::DTree"* %11, %"class.LL2W::Graph"* dereferenceable(72) %1, %"class.LL2W::Node"* dereferenceable(88) %70)
          to label %72 unwind label %151

; <label>:72:                                     ; preds = %71
  %73 = bitcast %"class.LL2W::DTree"* %11 to %"class.LL2W::Graph"*
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %12, i8* getelementptr inbounds ([16 x i8], [16 x i8]* @.str.33, i32 0, i32 0))
          to label %74 unwind label %155

; <label>:74:                                     ; preds = %72
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %13, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.19, i32 0, i32 0))
          to label %75 unwind label %159

; <label>:75:                                     ; preds = %74
  invoke void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"* %73, %"class.std::__1::basic_string"* dereferenceable(24) %12, %"class.std::__1::basic_string"* dereferenceable(24) %13)
          to label %76 unwind label %163

; <label>:76:                                     ; preds = %75
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %13) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %12) #8
  call void @_ZN4LL2W5DTreeD1Ev(%"class.LL2W::DTree"* %11) #8
  %77 = invoke i32 @"\01_usleep"(i32 100000)
          to label %78 unwind label %151

; <label>:78:                                     ; preds = %76
  %79 = bitcast %"class.LL2W::DJGraph"* %10 to %"class.LL2W::Graph"*
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %14, i8* getelementptr inbounds ([17 x i8], [17 x i8]* @.str.34, i32 0, i32 0))
          to label %80 unwind label %151

; <label>:80:                                     ; preds = %78
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %15, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.19, i32 0, i32 0))
          to label %81 unwind label %169

; <label>:81:                                     ; preds = %80
  invoke void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"* %79, %"class.std::__1::basic_string"* dereferenceable(24) %14, %"class.std::__1::basic_string"* dereferenceable(24) %15)
          to label %82 unwind label %173

; <label>:82:                                     ; preds = %81
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %15) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %14) #8
  %83 = invoke i32 @"\01_usleep"(i32 100000)
          to label %84 unwind label %151

; <label>:84:                                     ; preds = %82
  %85 = getelementptr inbounds %"class.LL2W::DJGraph", %"class.LL2W::DJGraph"* %10, i32 0, i32 2
  store %"class.std::__1::vector"* %85, %"class.std::__1::vector"** %16, align 8
  %86 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %16, align 8
  %87 = call %"struct.std::__1::pair"* @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE5beginEv(%"class.std::__1::vector"* %86) #8
  %88 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %17, i32 0, i32 0
  store %"struct.std::__1::pair"* %87, %"struct.std::__1::pair"** %88, align 8
  %89 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %16, align 8
  %90 = call %"struct.std::__1::pair"* @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE3endEv(%"class.std::__1::vector"* %89) #8
  %91 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %18, i32 0, i32 0
  store %"struct.std::__1::pair"* %90, %"struct.std::__1::pair"** %91, align 8
  br label %92

; <label>:92:                                     ; preds = %110, %84
  %93 = call zeroext i1 @_ZNSt3__1neIPNS_4pairIRN4LL2W4NodeES4_EEEEbRKNS_11__wrap_iterIT_EESB_(%"class.std::__1::__wrap_iter"* dereferenceable(8) %17, %"class.std::__1::__wrap_iter"* dereferenceable(8) %18) #8
  br i1 %93, label %94, label %178

; <label>:94:                                     ; preds = %92
  %95 = call dereferenceable(16) %"struct.std::__1::pair"* @_ZNKSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEEdeEv(%"class.std::__1::__wrap_iter"* %17) #8
  %96 = bitcast %"struct.std::__1::pair"* %19 to i8*
  %97 = bitcast %"struct.std::__1::pair"* %95 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %96, i8* align 8 %97, i64 16, i1 false)
  %98 = call dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__13getILm0ERN4LL2W4NodeES3_EEOKNS_13tuple_elementIXT_ENS_4pairIT0_T1_EEE4typeEOKS8_(%"struct.std::__1::pair"* dereferenceable(16) %19) #8
  store %"class.LL2W::Node"* %98, %"class.LL2W::Node"** %20, align 8
  %99 = call dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__13getILm1ERN4LL2W4NodeES3_EEOKNS_13tuple_elementIXT_ENS_4pairIT0_T1_EEE4typeEOKS8_(%"struct.std::__1::pair"* dereferenceable(16) %19) #8
  store %"class.LL2W::Node"* %99, %"class.LL2W::Node"** %21, align 8
  %100 = load %"class.LL2W::Node"*, %"class.LL2W::Node"** %20, align 8
  %101 = invoke dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZN4LL2WlsERNSt3__113basic_ostreamIcNS0_11char_traitsIcEEEERKNS_4NodeE(%"class.std::__1::basic_ostream"* dereferenceable(160) @_ZNSt3__14coutE, %"class.LL2W::Node"* dereferenceable(88) %100)
          to label %102 unwind label %151

; <label>:102:                                    ; preds = %94
  %103 = invoke dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc(%"class.std::__1::basic_ostream"* dereferenceable(160) %101, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.35, i32 0, i32 0))
          to label %104 unwind label %151

; <label>:104:                                    ; preds = %102
  %105 = load %"class.LL2W::Node"*, %"class.LL2W::Node"** %21, align 8
  %106 = invoke dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZN4LL2WlsERNSt3__113basic_ostreamIcNS0_11char_traitsIcEEEERKNS_4NodeE(%"class.std::__1::basic_ostream"* dereferenceable(160) %103, %"class.LL2W::Node"* dereferenceable(88) %105)
          to label %107 unwind label %151

; <label>:107:                                    ; preds = %104
  %108 = invoke dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__1lsINS_11char_traitsIcEEEERNS_13basic_ostreamIcT_EES6_PKc(%"class.std::__1::basic_ostream"* dereferenceable(160) %106, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.36, i32 0, i32 0))
          to label %109 unwind label %151

; <label>:109:                                    ; preds = %107
  br label %110

; <label>:110:                                    ; preds = %109
  %111 = call dereferenceable(8) %"class.std::__1::__wrap_iter"* @_ZNSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEEppEv(%"class.std::__1::__wrap_iter"* %17) #8
  br label %92

; <label>:112:                                    ; preds = %41, %39, %37, %35, %33, %31, %29, %27, %25, %23, %0
  %113 = landingpad { i8*, i32 }
          cleanup
  %114 = extractvalue { i8*, i32 } %113, 0
  store i8* %114, i8** %5, align 8
  %115 = extractvalue { i8*, i32 } %113, 1
  store i32 %115, i32* %6, align 4
  %116 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %4, align 8
  %117 = icmp eq %"class.std::__1::basic_string"* %22, %116
  br i1 %117, label %122, label %118

; <label>:118:                                    ; preds = %118, %112
  %119 = phi %"class.std::__1::basic_string"* [ %116, %112 ], [ %120, %118 ]
  %120 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %119, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %120) #8
  %121 = icmp eq %"class.std::__1::basic_string"* %120, %22
  br i1 %121, label %122, label %118

; <label>:122:                                    ; preds = %118, %112
  br label %181

; <label>:123:                                    ; preds = %43
  %124 = landingpad { i8*, i32 }
          cleanup
  %125 = extractvalue { i8*, i32 } %124, 0
  store i8* %125, i8** %5, align 8
  %126 = extractvalue { i8*, i32 } %124, 1
  store i32 %126, i32* %6, align 4
  %127 = getelementptr inbounds [11 x %"class.std::__1::basic_string"], [11 x %"class.std::__1::basic_string"]* %3, i32 0, i32 0
  %128 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %127, i64 11
  br label %129

; <label>:129:                                    ; preds = %129, %123
  %130 = phi %"class.std::__1::basic_string"* [ %128, %123 ], [ %131, %129 ]
  %131 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %130, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %131) #8
  %132 = icmp eq %"class.std::__1::basic_string"* %131, %127
  br i1 %132, label %133, label %129

; <label>:133:                                    ; preds = %129
  br label %181

; <label>:134:                                    ; preds = %68, %66, %64, %61, %59
  %135 = landingpad { i8*, i32 }
          cleanup
  %136 = extractvalue { i8*, i32 } %135, 0
  store i8* %136, i8** %5, align 8
  %137 = extractvalue { i8*, i32 } %135, 1
  store i32 %137, i32* %6, align 4
  br label %180

; <label>:138:                                    ; preds = %60
  %139 = landingpad { i8*, i32 }
          cleanup
  %140 = extractvalue { i8*, i32 } %139, 0
  store i8* %140, i8** %5, align 8
  %141 = extractvalue { i8*, i32 } %139, 1
  store i32 %141, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %7) #8
  br label %180

; <label>:142:                                    ; preds = %62
  %143 = landingpad { i8*, i32 }
          cleanup
  %144 = extractvalue { i8*, i32 } %143, 0
  store i8* %144, i8** %5, align 8
  %145 = extractvalue { i8*, i32 } %143, 1
  store i32 %145, i32* %6, align 4
  br label %150

; <label>:146:                                    ; preds = %63
  %147 = landingpad { i8*, i32 }
          cleanup
  %148 = extractvalue { i8*, i32 } %147, 0
  store i8* %148, i8** %5, align 8
  %149 = extractvalue { i8*, i32 } %147, 1
  store i32 %149, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %9) #8
  br label %150

; <label>:150:                                    ; preds = %146, %142
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %8) #8
  br label %180

; <label>:151:                                    ; preds = %107, %104, %102, %94, %82, %78, %76, %71, %69
  %152 = landingpad { i8*, i32 }
          cleanup
  %153 = extractvalue { i8*, i32 } %152, 0
  store i8* %153, i8** %5, align 8
  %154 = extractvalue { i8*, i32 } %152, 1
  store i32 %154, i32* %6, align 4
  br label %179

; <label>:155:                                    ; preds = %72
  %156 = landingpad { i8*, i32 }
          cleanup
  %157 = extractvalue { i8*, i32 } %156, 0
  store i8* %157, i8** %5, align 8
  %158 = extractvalue { i8*, i32 } %156, 1
  store i32 %158, i32* %6, align 4
  br label %168

; <label>:159:                                    ; preds = %74
  %160 = landingpad { i8*, i32 }
          cleanup
  %161 = extractvalue { i8*, i32 } %160, 0
  store i8* %161, i8** %5, align 8
  %162 = extractvalue { i8*, i32 } %160, 1
  store i32 %162, i32* %6, align 4
  br label %167

; <label>:163:                                    ; preds = %75
  %164 = landingpad { i8*, i32 }
          cleanup
  %165 = extractvalue { i8*, i32 } %164, 0
  store i8* %165, i8** %5, align 8
  %166 = extractvalue { i8*, i32 } %164, 1
  store i32 %166, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %13) #8
  br label %167

; <label>:167:                                    ; preds = %163, %159
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %12) #8
  br label %168

; <label>:168:                                    ; preds = %167, %155
  call void @_ZN4LL2W5DTreeD1Ev(%"class.LL2W::DTree"* %11) #8
  br label %179

; <label>:169:                                    ; preds = %80
  %170 = landingpad { i8*, i32 }
          cleanup
  %171 = extractvalue { i8*, i32 } %170, 0
  store i8* %171, i8** %5, align 8
  %172 = extractvalue { i8*, i32 } %170, 1
  store i32 %172, i32* %6, align 4
  br label %177

; <label>:173:                                    ; preds = %81
  %174 = landingpad { i8*, i32 }
          cleanup
  %175 = extractvalue { i8*, i32 } %174, 0
  store i8* %175, i8** %5, align 8
  %176 = extractvalue { i8*, i32 } %174, 1
  store i32 %176, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %15) #8
  br label %177

; <label>:177:                                    ; preds = %173, %169
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %14) #8
  br label %179

; <label>:178:                                    ; preds = %92
  call void @_ZN4LL2W7DJGraphD1Ev(%"class.LL2W::DJGraph"* %10) #8
  call void @_ZN4LL2W5GraphD1Ev(%"class.LL2W::Graph"* %1) #8
  ret void

; <label>:179:                                    ; preds = %177, %168, %151
  call void @_ZN4LL2W7DJGraphD1Ev(%"class.LL2W::DJGraph"* %10) #8
  br label %180

; <label>:180:                                    ; preds = %179, %150, %138, %134
  call void @_ZN4LL2W5GraphD1Ev(%"class.LL2W::Graph"* %1) #8
  br label %181

; <label>:181:                                    ; preds = %180, %133, %122
  %182 = load i8*, i8** %5, align 8
  %183 = load i32, i32* %6, align 4
  %184 = insertvalue { i8*, i32 } undef, i8* %182, 0
  %185 = insertvalue { i8*, i32 } %184, i32 %183, 1
  resume { i8*, i32 } %185
}

declare void @_ZN4LL2W7DJGraphC1ERNS_5GraphERNS_4NodeE(%"class.LL2W::DJGraph"*, %"class.LL2W::Graph"* dereferenceable(72), %"class.LL2W::Node"* dereferenceable(88)) unnamed_addr #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair"* @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE5beginEv(%"class.std::__1::vector"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__wrap_iter", align 8
  %3 = alloca %"class.std::__1::vector"*, align 8
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %3, align 8
  %4 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %3, align 8
  %5 = bitcast %"class.std::__1::vector"* %4 to %"class.std::__1::__vector_base"*
  %6 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %5, i32 0, i32 0
  %7 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %6, align 8
  %8 = call %"struct.std::__1::pair"* @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE11__make_iterEPS5_(%"class.std::__1::vector"* %4, %"struct.std::__1::pair"* %7) #8
  %9 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %2, i32 0, i32 0
  store %"struct.std::__1::pair"* %8, %"struct.std::__1::pair"** %9, align 8
  %10 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %2, i32 0, i32 0
  %11 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %10, align 8
  ret %"struct.std::__1::pair"* %11
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair"* @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE3endEv(%"class.std::__1::vector"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__wrap_iter", align 8
  %3 = alloca %"class.std::__1::vector"*, align 8
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %3, align 8
  %4 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %3, align 8
  %5 = bitcast %"class.std::__1::vector"* %4 to %"class.std::__1::__vector_base"*
  %6 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %5, i32 0, i32 1
  %7 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %6, align 8
  %8 = call %"struct.std::__1::pair"* @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE11__make_iterEPS5_(%"class.std::__1::vector"* %4, %"struct.std::__1::pair"* %7) #8
  %9 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %2, i32 0, i32 0
  store %"struct.std::__1::pair"* %8, %"struct.std::__1::pair"** %9, align 8
  %10 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %2, i32 0, i32 0
  %11 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %10, align 8
  ret %"struct.std::__1::pair"* %11
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden zeroext i1 @_ZNSt3__1neIPNS_4pairIRN4LL2W4NodeES4_EEEEbRKNS_11__wrap_iterIT_EESB_(%"class.std::__1::__wrap_iter"* dereferenceable(8), %"class.std::__1::__wrap_iter"* dereferenceable(8)) #4 {
  %3 = alloca %"class.std::__1::__wrap_iter"*, align 8
  %4 = alloca %"class.std::__1::__wrap_iter"*, align 8
  store %"class.std::__1::__wrap_iter"* %0, %"class.std::__1::__wrap_iter"** %3, align 8
  store %"class.std::__1::__wrap_iter"* %1, %"class.std::__1::__wrap_iter"** %4, align 8
  %5 = load %"class.std::__1::__wrap_iter"*, %"class.std::__1::__wrap_iter"** %3, align 8
  %6 = load %"class.std::__1::__wrap_iter"*, %"class.std::__1::__wrap_iter"** %4, align 8
  %7 = call zeroext i1 @_ZNSt3__1eqIPNS_4pairIRN4LL2W4NodeES4_EES6_EEbRKNS_11__wrap_iterIT_EERKNS7_IT0_EE(%"class.std::__1::__wrap_iter"* dereferenceable(8) %5, %"class.std::__1::__wrap_iter"* dereferenceable(8) %6) #8
  %8 = xor i1 %7, true
  ret i1 %8
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(16) %"struct.std::__1::pair"* @_ZNKSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEEdeEv(%"class.std::__1::__wrap_iter"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__wrap_iter"*, align 8
  store %"class.std::__1::__wrap_iter"* %0, %"class.std::__1::__wrap_iter"** %2, align 8
  %3 = load %"class.std::__1::__wrap_iter"*, %"class.std::__1::__wrap_iter"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %3, i32 0, i32 0
  %5 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  ret %"struct.std::__1::pair"* %5
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memcpy.p0i8.p0i8.i64(i8* nocapture writeonly, i8* nocapture readonly, i64, i1) #5

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__13getILm0ERN4LL2W4NodeES3_EEOKNS_13tuple_elementIXT_ENS_4pairIT0_T1_EEE4typeEOKS8_(%"struct.std::__1::pair"* dereferenceable(16)) #4 {
  %2 = alloca %"struct.std::__1::pair"*, align 8
  store %"struct.std::__1::pair"* %0, %"struct.std::__1::pair"** %2, align 8
  %3 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %2, align 8
  %4 = call dereferenceable(16) %"struct.std::__1::pair"* @_ZNSt3__14moveIRKNS_4pairIRN4LL2W4NodeES4_EEEEONS_16remove_referenceIT_E4typeEOS9_(%"struct.std::__1::pair"* dereferenceable(16) %3) #8
  %5 = call dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__110__get_pairILm0EE3getIRN4LL2W4NodeES5_EEOKT_OKNS_4pairIS6_T0_EE(%"struct.std::__1::pair"* dereferenceable(16) %4) #8
  ret %"class.LL2W::Node"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__13getILm1ERN4LL2W4NodeES3_EEOKNS_13tuple_elementIXT_ENS_4pairIT0_T1_EEE4typeEOKS8_(%"struct.std::__1::pair"* dereferenceable(16)) #4 {
  %2 = alloca %"struct.std::__1::pair"*, align 8
  store %"struct.std::__1::pair"* %0, %"struct.std::__1::pair"** %2, align 8
  %3 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %2, align 8
  %4 = call dereferenceable(16) %"struct.std::__1::pair"* @_ZNSt3__14moveIRKNS_4pairIRN4LL2W4NodeES4_EEEEONS_16remove_referenceIT_E4typeEOS9_(%"struct.std::__1::pair"* dereferenceable(16) %3) #8
  %5 = call dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__110__get_pairILm1EE3getIRN4LL2W4NodeES5_EEOKT0_OKNS_4pairIT_S6_EE(%"struct.std::__1::pair"* dereferenceable(16) %4) #8
  ret %"class.LL2W::Node"* %5
}

declare dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZN4LL2WlsERNSt3__113basic_ostreamIcNS0_11char_traitsIcEEEERKNS_4NodeE(%"class.std::__1::basic_ostream"* dereferenceable(160), %"class.LL2W::Node"* dereferenceable(88)) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"class.std::__1::__wrap_iter"* @_ZNSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEEppEv(%"class.std::__1::__wrap_iter"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__wrap_iter"*, align 8
  store %"class.std::__1::__wrap_iter"* %0, %"class.std::__1::__wrap_iter"** %2, align 8
  %3 = load %"class.std::__1::__wrap_iter"*, %"class.std::__1::__wrap_iter"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %3, i32 0, i32 0
  %5 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  %6 = getelementptr inbounds %"struct.std::__1::pair", %"struct.std::__1::pair"* %5, i32 1
  store %"struct.std::__1::pair"* %6, %"struct.std::__1::pair"** %4, align 8
  ret %"class.std::__1::__wrap_iter"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZN4LL2W7DJGraphD1Ev(%"class.LL2W::DJGraph"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.LL2W::DJGraph"*, align 8
  store %"class.LL2W::DJGraph"* %0, %"class.LL2W::DJGraph"** %2, align 8
  %3 = load %"class.LL2W::DJGraph"*, %"class.LL2W::DJGraph"** %2, align 8
  call void @_ZN4LL2W7DJGraphD2Ev(%"class.LL2W::DJGraph"* %3) #8
  ret void
}

; Function Attrs: noinline optnone ssp uwtable
define void @_Z10rendertestv() #1 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %1 = alloca %"class.LL2W::Graph", align 8
  %2 = alloca %"class.std::initializer_list", align 8
  %3 = alloca [4 x %"class.std::__1::basic_string"], align 8
  %4 = alloca %"class.std::__1::basic_string"*, align 8
  %5 = alloca i8*
  %6 = alloca i32
  %7 = alloca %"class.std::__1::basic_string", align 8
  %8 = alloca %"class.LL2W::Graph", align 8
  %9 = alloca %"class.std::initializer_list", align 8
  %10 = alloca [9 x %"class.std::__1::basic_string"], align 8
  %11 = alloca %"class.std::__1::basic_string"*, align 8
  %12 = alloca %"class.std::__1::basic_string", align 8
  %13 = alloca %"struct.LL2W::DFSResult", align 8
  %14 = alloca %"class.std::__1::basic_string", align 8
  %15 = alloca %"class.std::__1::basic_string", align 8
  %16 = alloca %"class.std::__1::basic_string", align 8
  %17 = alloca %"class.std::__1::basic_string", align 8
  %18 = alloca %"class.std::__1::basic_string", align 8
  %19 = alloca %"class.std::__1::basic_string", align 8
  %20 = alloca %"class.std::__1::basic_string", align 8
  %21 = alloca %"class.std::__1::basic_string", align 8
  %22 = alloca %"class.std::__1::basic_string", align 8
  %23 = alloca %"class.std::__1::basic_string", align 8
  %24 = alloca %"class.std::__1::basic_string", align 8
  %25 = alloca %"class.std::__1::basic_string", align 8
  %26 = alloca %"class.std::__1::basic_string", align 8
  %27 = alloca %"class.std::__1::basic_string", align 8
  %28 = alloca %"class.std::__1::basic_string", align 8
  %29 = alloca %"class.std::__1::basic_string", align 8
  %30 = alloca %"class.std::__1::basic_string", align 8
  %31 = alloca %"class.std::__1::basic_string", align 8
  %32 = getelementptr inbounds [4 x %"class.std::__1::basic_string"], [4 x %"class.std::__1::basic_string"]* %3, i64 0, i64 0
  store %"class.std::__1::basic_string"* %32, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %32, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.37, i32 0, i32 0))
          to label %33 unwind label %131

; <label>:33:                                     ; preds = %0
  %34 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %32, i64 1
  store %"class.std::__1::basic_string"* %34, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %34, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.38, i32 0, i32 0))
          to label %35 unwind label %131

; <label>:35:                                     ; preds = %33
  %36 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %34, i64 1
  store %"class.std::__1::basic_string"* %36, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %36, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.39, i32 0, i32 0))
          to label %37 unwind label %131

; <label>:37:                                     ; preds = %35
  %38 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %36, i64 1
  store %"class.std::__1::basic_string"* %38, %"class.std::__1::basic_string"** %4, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %38, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.40, i32 0, i32 0))
          to label %39 unwind label %131

; <label>:39:                                     ; preds = %37
  %40 = getelementptr inbounds %"class.std::initializer_list", %"class.std::initializer_list"* %2, i32 0, i32 0
  %41 = getelementptr inbounds [4 x %"class.std::__1::basic_string"], [4 x %"class.std::__1::basic_string"]* %3, i64 0, i64 0
  store %"class.std::__1::basic_string"* %41, %"class.std::__1::basic_string"** %40, align 8
  %42 = getelementptr inbounds %"class.std::initializer_list", %"class.std::initializer_list"* %2, i32 0, i32 1
  store i64 4, i64* %42, align 8
  %43 = bitcast %"class.std::initializer_list"* %2 to { %"class.std::__1::basic_string"*, i64 }*
  %44 = getelementptr inbounds { %"class.std::__1::basic_string"*, i64 }, { %"class.std::__1::basic_string"*, i64 }* %43, i32 0, i32 0
  %45 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %44, align 8
  %46 = getelementptr inbounds { %"class.std::__1::basic_string"*, i64 }, { %"class.std::__1::basic_string"*, i64 }* %43, i32 0, i32 1
  %47 = load i64, i64* %46, align 8
  invoke void @_ZN4LL2W5GraphC1ESt16initializer_listINSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEE(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* %45, i64 %47)
          to label %48 unwind label %142

; <label>:48:                                     ; preds = %39
  %49 = getelementptr inbounds [4 x %"class.std::__1::basic_string"], [4 x %"class.std::__1::basic_string"]* %3, i32 0, i32 0
  %50 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %49, i64 4
  br label %51

; <label>:51:                                     ; preds = %51, %48
  %52 = phi %"class.std::__1::basic_string"* [ %50, %48 ], [ %53, %51 ]
  %53 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %52, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %53) #8
  %54 = icmp eq %"class.std::__1::basic_string"* %53, %49
  br i1 %54, label %55, label %51

; <label>:55:                                     ; preds = %51
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %7, i8* getelementptr inbounds ([78 x i8], [78 x i8]* @.str.41, i32 0, i32 0))
          to label %56 unwind label %153

; <label>:56:                                     ; preds = %55
  invoke void @_ZN4LL2W5Graph8addEdgesERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %7)
          to label %57 unwind label %157

; <label>:57:                                     ; preds = %56
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %7) #8
  %58 = getelementptr inbounds [9 x %"class.std::__1::basic_string"], [9 x %"class.std::__1::basic_string"]* %10, i64 0, i64 0
  store %"class.std::__1::basic_string"* %58, %"class.std::__1::basic_string"** %11, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %58, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.20, i32 0, i32 0))
          to label %59 unwind label %161

; <label>:59:                                     ; preds = %57
  %60 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %58, i64 1
  store %"class.std::__1::basic_string"* %60, %"class.std::__1::basic_string"** %11, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %60, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.21, i32 0, i32 0))
          to label %61 unwind label %161

; <label>:61:                                     ; preds = %59
  %62 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %60, i64 1
  store %"class.std::__1::basic_string"* %62, %"class.std::__1::basic_string"** %11, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %62, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.22, i32 0, i32 0))
          to label %63 unwind label %161

; <label>:63:                                     ; preds = %61
  %64 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %62, i64 1
  store %"class.std::__1::basic_string"* %64, %"class.std::__1::basic_string"** %11, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %64, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.23, i32 0, i32 0))
          to label %65 unwind label %161

; <label>:65:                                     ; preds = %63
  %66 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %64, i64 1
  store %"class.std::__1::basic_string"* %66, %"class.std::__1::basic_string"** %11, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %66, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.24, i32 0, i32 0))
          to label %67 unwind label %161

; <label>:67:                                     ; preds = %65
  %68 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %66, i64 1
  store %"class.std::__1::basic_string"* %68, %"class.std::__1::basic_string"** %11, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %68, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.25, i32 0, i32 0))
          to label %69 unwind label %161

; <label>:69:                                     ; preds = %67
  %70 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %68, i64 1
  store %"class.std::__1::basic_string"* %70, %"class.std::__1::basic_string"** %11, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %70, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.26, i32 0, i32 0))
          to label %71 unwind label %161

; <label>:71:                                     ; preds = %69
  %72 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %70, i64 1
  store %"class.std::__1::basic_string"* %72, %"class.std::__1::basic_string"** %11, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %72, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.27, i32 0, i32 0))
          to label %73 unwind label %161

; <label>:73:                                     ; preds = %71
  %74 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %72, i64 1
  store %"class.std::__1::basic_string"* %74, %"class.std::__1::basic_string"** %11, align 8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %74, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.28, i32 0, i32 0))
          to label %75 unwind label %161

; <label>:75:                                     ; preds = %73
  %76 = getelementptr inbounds %"class.std::initializer_list", %"class.std::initializer_list"* %9, i32 0, i32 0
  %77 = getelementptr inbounds [9 x %"class.std::__1::basic_string"], [9 x %"class.std::__1::basic_string"]* %10, i64 0, i64 0
  store %"class.std::__1::basic_string"* %77, %"class.std::__1::basic_string"** %76, align 8
  %78 = getelementptr inbounds %"class.std::initializer_list", %"class.std::initializer_list"* %9, i32 0, i32 1
  store i64 9, i64* %78, align 8
  %79 = bitcast %"class.std::initializer_list"* %9 to { %"class.std::__1::basic_string"*, i64 }*
  %80 = getelementptr inbounds { %"class.std::__1::basic_string"*, i64 }, { %"class.std::__1::basic_string"*, i64 }* %79, i32 0, i32 0
  %81 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %80, align 8
  %82 = getelementptr inbounds { %"class.std::__1::basic_string"*, i64 }, { %"class.std::__1::basic_string"*, i64 }* %79, i32 0, i32 1
  %83 = load i64, i64* %82, align 8
  invoke void @_ZN4LL2W5GraphC1ESt16initializer_listINSt3__112basic_stringIcNS2_11char_traitsIcEENS2_9allocatorIcEEEEE(%"class.LL2W::Graph"* %8, %"class.std::__1::basic_string"* %81, i64 %83)
          to label %84 unwind label %172

; <label>:84:                                     ; preds = %75
  %85 = getelementptr inbounds [9 x %"class.std::__1::basic_string"], [9 x %"class.std::__1::basic_string"]* %10, i32 0, i32 0
  %86 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %85, i64 9
  br label %87

; <label>:87:                                     ; preds = %87, %84
  %88 = phi %"class.std::__1::basic_string"* [ %86, %84 ], [ %89, %87 ]
  %89 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %88, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %89) #8
  %90 = icmp eq %"class.std::__1::basic_string"* %89, %85
  br i1 %90, label %91, label %87

; <label>:91:                                     ; preds = %87
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %12, i8* getelementptr inbounds ([44 x i8], [44 x i8]* @.str.42, i32 0, i32 0))
          to label %92 unwind label %183

; <label>:92:                                     ; preds = %91
  invoke void @_ZN4LL2W5Graph8addEdgesERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"class.LL2W::Graph"* %8, %"class.std::__1::basic_string"* dereferenceable(24) %12)
          to label %93 unwind label %187

; <label>:93:                                     ; preds = %92
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %12) #8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %14, i8* getelementptr inbounds ([2 x i8], [2 x i8]* @.str.20, i32 0, i32 0))
          to label %94 unwind label %183

; <label>:94:                                     ; preds = %93
  invoke void @_ZN4LL2W5Graph3DFSERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"struct.LL2W::DFSResult"* sret %13, %"class.LL2W::Graph"* %8, %"class.std::__1::basic_string"* dereferenceable(24) %14)
          to label %95 unwind label %191

; <label>:95:                                     ; preds = %94
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %14) #8
  %96 = invoke dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZN4LL2WlsERNSt3__113basic_ostreamIcNS0_11char_traitsIcEEEERKNS_9DFSResultE(%"class.std::__1::basic_ostream"* dereferenceable(160) @_ZNSt3__14coutE, %"struct.LL2W::DFSResult"* dereferenceable(128) %13)
          to label %97 unwind label %195

; <label>:97:                                     ; preds = %95
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %15, i8* getelementptr inbounds ([18 x i8], [18 x i8]* @.str.43, i32 0, i32 0))
          to label %98 unwind label %195

; <label>:98:                                     ; preds = %97
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %16, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.17, i32 0, i32 0))
          to label %99 unwind label %199

; <label>:99:                                     ; preds = %98
  invoke void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"* %8, %"class.std::__1::basic_string"* dereferenceable(24) %15, %"class.std::__1::basic_string"* dereferenceable(24) %16)
          to label %100 unwind label %203

; <label>:100:                                    ; preds = %99
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %16) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %15) #8
  %101 = invoke i32 @"\01_usleep"(i32 100000)
          to label %102 unwind label %195

; <label>:102:                                    ; preds = %100
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %17, i8* getelementptr inbounds ([15 x i8], [15 x i8]* @.str.44, i32 0, i32 0))
          to label %103 unwind label %195

; <label>:103:                                    ; preds = %102
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %18, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.17, i32 0, i32 0))
          to label %104 unwind label %208

; <label>:104:                                    ; preds = %103
  invoke void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %17, %"class.std::__1::basic_string"* dereferenceable(24) %18)
          to label %105 unwind label %212

; <label>:105:                                    ; preds = %104
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %18) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %17) #8
  %106 = invoke i32 @"\01_usleep"(i32 100000)
          to label %107 unwind label %195

; <label>:107:                                    ; preds = %105
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %19, i8* getelementptr inbounds ([5 x i8], [5 x i8]* @.str.40, i32 0, i32 0))
          to label %108 unwind label %195

; <label>:108:                                    ; preds = %107
  %109 = invoke dereferenceable(72) %"class.LL2W::Graph"* @_ZN4LL2W5GraphmIERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %19)
          to label %110 unwind label %217

; <label>:110:                                    ; preds = %108
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %19) #8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %20, i8* getelementptr inbounds ([14 x i8], [14 x i8]* @.str.45, i32 0, i32 0))
          to label %111 unwind label %195

; <label>:111:                                    ; preds = %110
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %21, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.17, i32 0, i32 0))
          to label %112 unwind label %221

; <label>:112:                                    ; preds = %111
  invoke void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %20, %"class.std::__1::basic_string"* dereferenceable(24) %21)
          to label %113 unwind label %225

; <label>:113:                                    ; preds = %112
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %21) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %20) #8
  %114 = invoke i32 @"\01_usleep"(i32 100000)
          to label %115 unwind label %195

; <label>:115:                                    ; preds = %113
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %22, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.37, i32 0, i32 0))
          to label %116 unwind label %195

; <label>:116:                                    ; preds = %115
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %23, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.38, i32 0, i32 0))
          to label %117 unwind label %230

; <label>:117:                                    ; preds = %116
  invoke void @_ZN4LL2W5Graph6unlinkERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_b(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %22, %"class.std::__1::basic_string"* dereferenceable(24) %23, i1 zeroext false)
          to label %118 unwind label %234

; <label>:118:                                    ; preds = %117
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %23) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %22) #8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %24, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.37, i32 0, i32 0))
          to label %119 unwind label %195

; <label>:119:                                    ; preds = %118
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %25, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.39, i32 0, i32 0))
          to label %120 unwind label %239

; <label>:120:                                    ; preds = %119
  invoke void @_ZN4LL2W5Graph6unlinkERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_b(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %24, %"class.std::__1::basic_string"* dereferenceable(24) %25, i1 zeroext false)
          to label %121 unwind label %243

; <label>:121:                                    ; preds = %120
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %25) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %24) #8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %26, i8* getelementptr inbounds ([4 x i8], [4 x i8]* @.str.38, i32 0, i32 0))
          to label %122 unwind label %195

; <label>:122:                                    ; preds = %121
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %27, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.39, i32 0, i32 0))
          to label %123 unwind label %248

; <label>:123:                                    ; preds = %122
  invoke void @_ZN4LL2W5Graph6unlinkERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_b(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %26, %"class.std::__1::basic_string"* dereferenceable(24) %27, i1 zeroext false)
          to label %124 unwind label %252

; <label>:124:                                    ; preds = %123
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %27) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %26) #8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %28, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.39, i32 0, i32 0))
          to label %125 unwind label %195

; <label>:125:                                    ; preds = %124
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %29, i8* getelementptr inbounds ([6 x i8], [6 x i8]* @.str.39, i32 0, i32 0))
          to label %126 unwind label %257

; <label>:126:                                    ; preds = %125
  invoke void @_ZN4LL2W5Graph6unlinkERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_b(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %28, %"class.std::__1::basic_string"* dereferenceable(24) %29, i1 zeroext false)
          to label %127 unwind label %261

; <label>:127:                                    ; preds = %126
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %29) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %28) #8
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %30, i8* getelementptr inbounds ([19 x i8], [19 x i8]* @.str.46, i32 0, i32 0))
          to label %128 unwind label %195

; <label>:128:                                    ; preds = %127
  invoke void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1IDnEEPKc(%"class.std::__1::basic_string"* %31, i8* getelementptr inbounds ([3 x i8], [3 x i8]* @.str.17, i32 0, i32 0))
          to label %129 unwind label %266

; <label>:129:                                    ; preds = %128
  invoke void @_ZN4LL2W5Graph8renderToERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_(%"class.LL2W::Graph"* %1, %"class.std::__1::basic_string"* dereferenceable(24) %30, %"class.std::__1::basic_string"* dereferenceable(24) %31)
          to label %130 unwind label %270

; <label>:130:                                    ; preds = %129
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %31) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %30) #8
  call void @_ZN4LL2W9DFSResultD1Ev(%"struct.LL2W::DFSResult"* %13) #8
  call void @_ZN4LL2W5GraphD1Ev(%"class.LL2W::Graph"* %8) #8
  call void @_ZN4LL2W5GraphD1Ev(%"class.LL2W::Graph"* %1) #8
  ret void

; <label>:131:                                    ; preds = %37, %35, %33, %0
  %132 = landingpad { i8*, i32 }
          cleanup
  %133 = extractvalue { i8*, i32 } %132, 0
  store i8* %133, i8** %5, align 8
  %134 = extractvalue { i8*, i32 } %132, 1
  store i32 %134, i32* %6, align 4
  %135 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %4, align 8
  %136 = icmp eq %"class.std::__1::basic_string"* %32, %135
  br i1 %136, label %141, label %137

; <label>:137:                                    ; preds = %137, %131
  %138 = phi %"class.std::__1::basic_string"* [ %135, %131 ], [ %139, %137 ]
  %139 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %138, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %139) #8
  %140 = icmp eq %"class.std::__1::basic_string"* %139, %32
  br i1 %140, label %141, label %137

; <label>:141:                                    ; preds = %137, %131
  br label %278

; <label>:142:                                    ; preds = %39
  %143 = landingpad { i8*, i32 }
          cleanup
  %144 = extractvalue { i8*, i32 } %143, 0
  store i8* %144, i8** %5, align 8
  %145 = extractvalue { i8*, i32 } %143, 1
  store i32 %145, i32* %6, align 4
  %146 = getelementptr inbounds [4 x %"class.std::__1::basic_string"], [4 x %"class.std::__1::basic_string"]* %3, i32 0, i32 0
  %147 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %146, i64 4
  br label %148

; <label>:148:                                    ; preds = %148, %142
  %149 = phi %"class.std::__1::basic_string"* [ %147, %142 ], [ %150, %148 ]
  %150 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %149, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %150) #8
  %151 = icmp eq %"class.std::__1::basic_string"* %150, %146
  br i1 %151, label %152, label %148

; <label>:152:                                    ; preds = %148
  br label %278

; <label>:153:                                    ; preds = %55
  %154 = landingpad { i8*, i32 }
          cleanup
  %155 = extractvalue { i8*, i32 } %154, 0
  store i8* %155, i8** %5, align 8
  %156 = extractvalue { i8*, i32 } %154, 1
  store i32 %156, i32* %6, align 4
  br label %277

; <label>:157:                                    ; preds = %56
  %158 = landingpad { i8*, i32 }
          cleanup
  %159 = extractvalue { i8*, i32 } %158, 0
  store i8* %159, i8** %5, align 8
  %160 = extractvalue { i8*, i32 } %158, 1
  store i32 %160, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %7) #8
  br label %277

; <label>:161:                                    ; preds = %73, %71, %69, %67, %65, %63, %61, %59, %57
  %162 = landingpad { i8*, i32 }
          cleanup
  %163 = extractvalue { i8*, i32 } %162, 0
  store i8* %163, i8** %5, align 8
  %164 = extractvalue { i8*, i32 } %162, 1
  store i32 %164, i32* %6, align 4
  %165 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %11, align 8
  %166 = icmp eq %"class.std::__1::basic_string"* %58, %165
  br i1 %166, label %171, label %167

; <label>:167:                                    ; preds = %167, %161
  %168 = phi %"class.std::__1::basic_string"* [ %165, %161 ], [ %169, %167 ]
  %169 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %168, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %169) #8
  %170 = icmp eq %"class.std::__1::basic_string"* %169, %58
  br i1 %170, label %171, label %167

; <label>:171:                                    ; preds = %167, %161
  br label %277

; <label>:172:                                    ; preds = %75
  %173 = landingpad { i8*, i32 }
          cleanup
  %174 = extractvalue { i8*, i32 } %173, 0
  store i8* %174, i8** %5, align 8
  %175 = extractvalue { i8*, i32 } %173, 1
  store i32 %175, i32* %6, align 4
  %176 = getelementptr inbounds [9 x %"class.std::__1::basic_string"], [9 x %"class.std::__1::basic_string"]* %10, i32 0, i32 0
  %177 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %176, i64 9
  br label %178

; <label>:178:                                    ; preds = %178, %172
  %179 = phi %"class.std::__1::basic_string"* [ %177, %172 ], [ %180, %178 ]
  %180 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %179, i64 -1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %180) #8
  %181 = icmp eq %"class.std::__1::basic_string"* %180, %176
  br i1 %181, label %182, label %178

; <label>:182:                                    ; preds = %178
  br label %277

; <label>:183:                                    ; preds = %93, %91
  %184 = landingpad { i8*, i32 }
          cleanup
  %185 = extractvalue { i8*, i32 } %184, 0
  store i8* %185, i8** %5, align 8
  %186 = extractvalue { i8*, i32 } %184, 1
  store i32 %186, i32* %6, align 4
  br label %276

; <label>:187:                                    ; preds = %92
  %188 = landingpad { i8*, i32 }
          cleanup
  %189 = extractvalue { i8*, i32 } %188, 0
  store i8* %189, i8** %5, align 8
  %190 = extractvalue { i8*, i32 } %188, 1
  store i32 %190, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %12) #8
  br label %276

; <label>:191:                                    ; preds = %94
  %192 = landingpad { i8*, i32 }
          cleanup
  %193 = extractvalue { i8*, i32 } %192, 0
  store i8* %193, i8** %5, align 8
  %194 = extractvalue { i8*, i32 } %192, 1
  store i32 %194, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %14) #8
  br label %276

; <label>:195:                                    ; preds = %127, %124, %121, %118, %115, %113, %110, %107, %105, %102, %100, %97, %95
  %196 = landingpad { i8*, i32 }
          cleanup
  %197 = extractvalue { i8*, i32 } %196, 0
  store i8* %197, i8** %5, align 8
  %198 = extractvalue { i8*, i32 } %196, 1
  store i32 %198, i32* %6, align 4
  br label %275

; <label>:199:                                    ; preds = %98
  %200 = landingpad { i8*, i32 }
          cleanup
  %201 = extractvalue { i8*, i32 } %200, 0
  store i8* %201, i8** %5, align 8
  %202 = extractvalue { i8*, i32 } %200, 1
  store i32 %202, i32* %6, align 4
  br label %207

; <label>:203:                                    ; preds = %99
  %204 = landingpad { i8*, i32 }
          cleanup
  %205 = extractvalue { i8*, i32 } %204, 0
  store i8* %205, i8** %5, align 8
  %206 = extractvalue { i8*, i32 } %204, 1
  store i32 %206, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %16) #8
  br label %207

; <label>:207:                                    ; preds = %203, %199
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %15) #8
  br label %275

; <label>:208:                                    ; preds = %103
  %209 = landingpad { i8*, i32 }
          cleanup
  %210 = extractvalue { i8*, i32 } %209, 0
  store i8* %210, i8** %5, align 8
  %211 = extractvalue { i8*, i32 } %209, 1
  store i32 %211, i32* %6, align 4
  br label %216

; <label>:212:                                    ; preds = %104
  %213 = landingpad { i8*, i32 }
          cleanup
  %214 = extractvalue { i8*, i32 } %213, 0
  store i8* %214, i8** %5, align 8
  %215 = extractvalue { i8*, i32 } %213, 1
  store i32 %215, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %18) #8
  br label %216

; <label>:216:                                    ; preds = %212, %208
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %17) #8
  br label %275

; <label>:217:                                    ; preds = %108
  %218 = landingpad { i8*, i32 }
          cleanup
  %219 = extractvalue { i8*, i32 } %218, 0
  store i8* %219, i8** %5, align 8
  %220 = extractvalue { i8*, i32 } %218, 1
  store i32 %220, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %19) #8
  br label %275

; <label>:221:                                    ; preds = %111
  %222 = landingpad { i8*, i32 }
          cleanup
  %223 = extractvalue { i8*, i32 } %222, 0
  store i8* %223, i8** %5, align 8
  %224 = extractvalue { i8*, i32 } %222, 1
  store i32 %224, i32* %6, align 4
  br label %229

; <label>:225:                                    ; preds = %112
  %226 = landingpad { i8*, i32 }
          cleanup
  %227 = extractvalue { i8*, i32 } %226, 0
  store i8* %227, i8** %5, align 8
  %228 = extractvalue { i8*, i32 } %226, 1
  store i32 %228, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %21) #8
  br label %229

; <label>:229:                                    ; preds = %225, %221
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %20) #8
  br label %275

; <label>:230:                                    ; preds = %116
  %231 = landingpad { i8*, i32 }
          cleanup
  %232 = extractvalue { i8*, i32 } %231, 0
  store i8* %232, i8** %5, align 8
  %233 = extractvalue { i8*, i32 } %231, 1
  store i32 %233, i32* %6, align 4
  br label %238

; <label>:234:                                    ; preds = %117
  %235 = landingpad { i8*, i32 }
          cleanup
  %236 = extractvalue { i8*, i32 } %235, 0
  store i8* %236, i8** %5, align 8
  %237 = extractvalue { i8*, i32 } %235, 1
  store i32 %237, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %23) #8
  br label %238

; <label>:238:                                    ; preds = %234, %230
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %22) #8
  br label %275

; <label>:239:                                    ; preds = %119
  %240 = landingpad { i8*, i32 }
          cleanup
  %241 = extractvalue { i8*, i32 } %240, 0
  store i8* %241, i8** %5, align 8
  %242 = extractvalue { i8*, i32 } %240, 1
  store i32 %242, i32* %6, align 4
  br label %247

; <label>:243:                                    ; preds = %120
  %244 = landingpad { i8*, i32 }
          cleanup
  %245 = extractvalue { i8*, i32 } %244, 0
  store i8* %245, i8** %5, align 8
  %246 = extractvalue { i8*, i32 } %244, 1
  store i32 %246, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %25) #8
  br label %247

; <label>:247:                                    ; preds = %243, %239
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %24) #8
  br label %275

; <label>:248:                                    ; preds = %122
  %249 = landingpad { i8*, i32 }
          cleanup
  %250 = extractvalue { i8*, i32 } %249, 0
  store i8* %250, i8** %5, align 8
  %251 = extractvalue { i8*, i32 } %249, 1
  store i32 %251, i32* %6, align 4
  br label %256

; <label>:252:                                    ; preds = %123
  %253 = landingpad { i8*, i32 }
          cleanup
  %254 = extractvalue { i8*, i32 } %253, 0
  store i8* %254, i8** %5, align 8
  %255 = extractvalue { i8*, i32 } %253, 1
  store i32 %255, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %27) #8
  br label %256

; <label>:256:                                    ; preds = %252, %248
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %26) #8
  br label %275

; <label>:257:                                    ; preds = %125
  %258 = landingpad { i8*, i32 }
          cleanup
  %259 = extractvalue { i8*, i32 } %258, 0
  store i8* %259, i8** %5, align 8
  %260 = extractvalue { i8*, i32 } %258, 1
  store i32 %260, i32* %6, align 4
  br label %265

; <label>:261:                                    ; preds = %126
  %262 = landingpad { i8*, i32 }
          cleanup
  %263 = extractvalue { i8*, i32 } %262, 0
  store i8* %263, i8** %5, align 8
  %264 = extractvalue { i8*, i32 } %262, 1
  store i32 %264, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %29) #8
  br label %265

; <label>:265:                                    ; preds = %261, %257
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %28) #8
  br label %275

; <label>:266:                                    ; preds = %128
  %267 = landingpad { i8*, i32 }
          cleanup
  %268 = extractvalue { i8*, i32 } %267, 0
  store i8* %268, i8** %5, align 8
  %269 = extractvalue { i8*, i32 } %267, 1
  store i32 %269, i32* %6, align 4
  br label %274

; <label>:270:                                    ; preds = %129
  %271 = landingpad { i8*, i32 }
          cleanup
  %272 = extractvalue { i8*, i32 } %271, 0
  store i8* %272, i8** %5, align 8
  %273 = extractvalue { i8*, i32 } %271, 1
  store i32 %273, i32* %6, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %31) #8
  br label %274

; <label>:274:                                    ; preds = %270, %266
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %30) #8
  br label %275

; <label>:275:                                    ; preds = %274, %265, %256, %247, %238, %229, %217, %216, %207, %195
  call void @_ZN4LL2W9DFSResultD1Ev(%"struct.LL2W::DFSResult"* %13) #8
  br label %276

; <label>:276:                                    ; preds = %275, %191, %187, %183
  call void @_ZN4LL2W5GraphD1Ev(%"class.LL2W::Graph"* %8) #8
  br label %277

; <label>:277:                                    ; preds = %276, %182, %171, %157, %153
  call void @_ZN4LL2W5GraphD1Ev(%"class.LL2W::Graph"* %1) #8
  br label %278

; <label>:278:                                    ; preds = %277, %152, %141
  %279 = load i8*, i8** %5, align 8
  %280 = load i32, i32* %6, align 4
  %281 = insertvalue { i8*, i32 } undef, i8* %279, 0
  %282 = insertvalue { i8*, i32 } %281, i32 %280, 1
  resume { i8*, i32 } %282
}

declare void @_ZN4LL2W5Graph3DFSERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"struct.LL2W::DFSResult"* sret, %"class.LL2W::Graph"*, %"class.std::__1::basic_string"* dereferenceable(24)) #3

declare dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZN4LL2WlsERNSt3__113basic_ostreamIcNS0_11char_traitsIcEEEERKNS_9DFSResultE(%"class.std::__1::basic_ostream"* dereferenceable(160), %"struct.LL2W::DFSResult"* dereferenceable(128)) #3

declare dereferenceable(72) %"class.LL2W::Graph"* @_ZN4LL2W5GraphmIERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"class.LL2W::Graph"*, %"class.std::__1::basic_string"* dereferenceable(24)) #3

declare void @_ZN4LL2W5Graph6unlinkERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEES9_b(%"class.LL2W::Graph"*, %"class.std::__1::basic_string"* dereferenceable(24), %"class.std::__1::basic_string"* dereferenceable(24), i1 zeroext) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZN4LL2W9DFSResultD1Ev(%"struct.LL2W::DFSResult"*) unnamed_addr #4 align 2 {
  %2 = alloca %"struct.LL2W::DFSResult"*, align 8
  store %"struct.LL2W::DFSResult"* %0, %"struct.LL2W::DFSResult"** %2, align 8
  %3 = load %"struct.LL2W::DFSResult"*, %"struct.LL2W::DFSResult"** %2, align 8
  call void @_ZN4LL2W9DFSResultD2Ev(%"struct.LL2W::DFSResult"* %3) #8
  ret void
}

declare void @_ZN4LL2W6Parser4openERKNSt3__112basic_stringIcNS1_11char_traitsIcEENS1_9allocatorIcEEEE(%"class.std::__1::basic_string"* dereferenceable(24)) #3

declare void @_ZN4LL2W6Parser5parseEv() #3

declare void @_ZN4LL2W7ASTNode5debugEib(%"class.LL2W::ASTNode"*, i32, i1 zeroext) #3

declare void @_ZN4LL2W6Parser4doneEv() #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZN4LL2W5DTreeD2Ev(%"class.LL2W::DTree"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.LL2W::DTree"*, align 8
  store %"class.LL2W::DTree"* %0, %"class.LL2W::DTree"** %2, align 8
  %3 = load %"class.LL2W::DTree"*, %"class.LL2W::DTree"** %2, align 8
  %4 = bitcast %"class.LL2W::DTree"* %3 to %"class.LL2W::Graph"*
  call void @_ZN4LL2W5GraphD2Ev(%"class.LL2W::Graph"* %4) #8
  ret void
}

; Function Attrs: nounwind
declare void @_ZN4LL2W5GraphD2Ev(%"class.LL2W::Graph"*) unnamed_addr #2

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden zeroext i1 @_ZNSt3__1eqIPNS_4pairIRN4LL2W4NodeES4_EES6_EEbRKNS_11__wrap_iterIT_EERKNS7_IT0_EE(%"class.std::__1::__wrap_iter"* dereferenceable(8), %"class.std::__1::__wrap_iter"* dereferenceable(8)) #4 {
  %3 = alloca %"class.std::__1::__wrap_iter"*, align 8
  %4 = alloca %"class.std::__1::__wrap_iter"*, align 8
  store %"class.std::__1::__wrap_iter"* %0, %"class.std::__1::__wrap_iter"** %3, align 8
  store %"class.std::__1::__wrap_iter"* %1, %"class.std::__1::__wrap_iter"** %4, align 8
  %5 = load %"class.std::__1::__wrap_iter"*, %"class.std::__1::__wrap_iter"** %3, align 8
  %6 = call %"struct.std::__1::pair"* @_ZNKSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEE4baseEv(%"class.std::__1::__wrap_iter"* %5) #8
  %7 = load %"class.std::__1::__wrap_iter"*, %"class.std::__1::__wrap_iter"** %4, align 8
  %8 = call %"struct.std::__1::pair"* @_ZNKSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEE4baseEv(%"class.std::__1::__wrap_iter"* %7) #8
  %9 = icmp eq %"struct.std::__1::pair"* %6, %8
  ret i1 %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair"* @_ZNKSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEE4baseEv(%"class.std::__1::__wrap_iter"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__wrap_iter"*, align 8
  store %"class.std::__1::__wrap_iter"* %0, %"class.std::__1::__wrap_iter"** %2, align 8
  %3 = load %"class.std::__1::__wrap_iter"*, %"class.std::__1::__wrap_iter"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %3, i32 0, i32 0
  %5 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  ret %"struct.std::__1::pair"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__110__get_pairILm0EE3getIRN4LL2W4NodeES5_EEOKT_OKNS_4pairIS6_T0_EE(%"struct.std::__1::pair"* dereferenceable(16)) #4 align 2 {
  %2 = alloca %"struct.std::__1::pair"*, align 8
  store %"struct.std::__1::pair"* %0, %"struct.std::__1::pair"** %2, align 8
  %3 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::pair", %"struct.std::__1::pair"* %3, i32 0, i32 0
  %5 = load %"class.LL2W::Node"*, %"class.LL2W::Node"** %4, align 8
  %6 = call dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__17forwardIRN4LL2W4NodeEEEOT_RNS_16remove_referenceIS4_E4typeE(%"class.LL2W::Node"* dereferenceable(88) %5) #8
  ret %"class.LL2W::Node"* %6
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(16) %"struct.std::__1::pair"* @_ZNSt3__14moveIRKNS_4pairIRN4LL2W4NodeES4_EEEEONS_16remove_referenceIT_E4typeEOS9_(%"struct.std::__1::pair"* dereferenceable(16)) #4 {
  %2 = alloca %"struct.std::__1::pair"*, align 8
  store %"struct.std::__1::pair"* %0, %"struct.std::__1::pair"** %2, align 8
  %3 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %2, align 8
  ret %"struct.std::__1::pair"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__17forwardIRN4LL2W4NodeEEEOT_RNS_16remove_referenceIS4_E4typeE(%"class.LL2W::Node"* dereferenceable(88)) #4 {
  %2 = alloca %"class.LL2W::Node"*, align 8
  store %"class.LL2W::Node"* %0, %"class.LL2W::Node"** %2, align 8
  %3 = load %"class.LL2W::Node"*, %"class.LL2W::Node"** %2, align 8
  ret %"class.LL2W::Node"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__110__get_pairILm1EE3getIRN4LL2W4NodeES5_EEOKT0_OKNS_4pairIT_S6_EE(%"struct.std::__1::pair"* dereferenceable(16)) #4 align 2 {
  %2 = alloca %"struct.std::__1::pair"*, align 8
  store %"struct.std::__1::pair"* %0, %"struct.std::__1::pair"** %2, align 8
  %3 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::pair", %"struct.std::__1::pair"* %3, i32 0, i32 1
  %5 = load %"class.LL2W::Node"*, %"class.LL2W::Node"** %4, align 8
  %6 = call dereferenceable(88) %"class.LL2W::Node"* @_ZNSt3__17forwardIRN4LL2W4NodeEEEOT_RNS_16remove_referenceIS4_E4typeE(%"class.LL2W::Node"* dereferenceable(88) %5) #8
  ret %"class.LL2W::Node"* %6
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZN4LL2W7DJGraphD2Ev(%"class.LL2W::DJGraph"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.LL2W::DJGraph"*, align 8
  store %"class.LL2W::DJGraph"* %0, %"class.LL2W::DJGraph"** %2, align 8
  %3 = load %"class.LL2W::DJGraph"*, %"class.LL2W::DJGraph"** %2, align 8
  %4 = bitcast %"class.LL2W::DJGraph"* %3 to i32 (...)***
  store i32 (...)** bitcast (i8** getelementptr inbounds ({ [3 x i8*] }, { [3 x i8*] }* @_ZTVN4LL2W7DJGraphE, i32 0, inrange i32 0, i32 2) to i32 (...)**), i32 (...)*** %4, align 8
  %5 = getelementptr inbounds %"class.LL2W::DJGraph", %"class.LL2W::DJGraph"* %3, i32 0, i32 2
  call void @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEED1Ev(%"class.std::__1::vector"* %5) #8
  %6 = getelementptr inbounds %"class.LL2W::DJGraph", %"class.LL2W::DJGraph"* %3, i32 0, i32 1
  call void @_ZNSt3__113unordered_mapIPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEES6_S8_NS9_INS_4pairIKS3_SB_EEEEED1Ev(%"class.std::__1::unordered_map.31"* %6) #8
  %7 = bitcast %"class.LL2W::DJGraph"* %3 to %"class.LL2W::Graph"*
  call void @_ZN4LL2W5GraphD2Ev(%"class.LL2W::Graph"* %7) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEED1Ev(%"class.std::__1::vector"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::vector"*, align 8
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %2, align 8
  %3 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %2, align 8
  call void @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEED2Ev(%"class.std::__1::vector"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__113unordered_mapIPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEES6_S8_NS9_INS_4pairIKS3_SB_EEEEED1Ev(%"class.std::__1::unordered_map.31"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unordered_map.31"*, align 8
  store %"class.std::__1::unordered_map.31"* %0, %"class.std::__1::unordered_map.31"** %2, align 8
  %3 = load %"class.std::__1::unordered_map.31"*, %"class.std::__1::unordered_map.31"** %2, align 8
  call void @_ZNSt3__113unordered_mapIPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEES6_S8_NS9_INS_4pairIKS3_SB_EEEEED2Ev(%"class.std::__1::unordered_map.31"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEED2Ev(%"class.std::__1::vector"*) unnamed_addr #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %2 = alloca %"class.std::__1::vector"*, align 8
  %3 = alloca i8*
  %4 = alloca i32
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %2, align 8
  %5 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %2, align 8
  invoke void @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE17__annotate_deleteEv(%"class.std::__1::vector"* %5)
          to label %6 unwind label %8

; <label>:6:                                      ; preds = %1
  %7 = bitcast %"class.std::__1::vector"* %5 to %"class.std::__1::__vector_base"*
  call void @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEED2Ev(%"class.std::__1::__vector_base"* %7) #8
  ret void

; <label>:8:                                      ; preds = %1
  %9 = landingpad { i8*, i32 }
          catch i8* null
  %10 = extractvalue { i8*, i32 } %9, 0
  store i8* %10, i8** %3, align 8
  %11 = extractvalue { i8*, i32 } %9, 1
  store i32 %11, i32* %4, align 4
  %12 = bitcast %"class.std::__1::vector"* %5 to %"class.std::__1::__vector_base"*
  call void @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEED2Ev(%"class.std::__1::__vector_base"* %12) #8
  br label %13

; <label>:13:                                     ; preds = %8
  %14 = load i8*, i8** %3, align 8
  call void @__clang_call_terminate(i8* %14) #9
  unreachable
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden void @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE17__annotate_deleteEv(%"class.std::__1::vector"*) #1 align 2 {
  %2 = alloca %"class.std::__1::vector"*, align 8
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %2, align 8
  %3 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %2, align 8
  %4 = call %"struct.std::__1::pair"* @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE4dataEv(%"class.std::__1::vector"* %3) #8
  %5 = bitcast %"struct.std::__1::pair"* %4 to i8*
  %6 = call %"struct.std::__1::pair"* @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE4dataEv(%"class.std::__1::vector"* %3) #8
  %7 = call i64 @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE8capacityEv(%"class.std::__1::vector"* %3) #8
  %8 = getelementptr inbounds %"struct.std::__1::pair", %"struct.std::__1::pair"* %6, i64 %7
  %9 = bitcast %"struct.std::__1::pair"* %8 to i8*
  %10 = call %"struct.std::__1::pair"* @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE4dataEv(%"class.std::__1::vector"* %3) #8
  %11 = call i64 @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE4sizeEv(%"class.std::__1::vector"* %3) #8
  %12 = getelementptr inbounds %"struct.std::__1::pair", %"struct.std::__1::pair"* %10, i64 %11
  %13 = bitcast %"struct.std::__1::pair"* %12 to i8*
  %14 = call %"struct.std::__1::pair"* @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE4dataEv(%"class.std::__1::vector"* %3) #8
  %15 = call i64 @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE8capacityEv(%"class.std::__1::vector"* %3) #8
  %16 = getelementptr inbounds %"struct.std::__1::pair", %"struct.std::__1::pair"* %14, i64 %15
  %17 = bitcast %"struct.std::__1::pair"* %16 to i8*
  call void @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE31__annotate_contiguous_containerEPKvSA_SA_SA_(%"class.std::__1::vector"* %3, i8* %5, i8* %9, i8* %13, i8* %17)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEED2Ev(%"class.std::__1::__vector_base"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::__vector_base"*, align 8
  store %"class.std::__1::__vector_base"* %0, %"class.std::__1::__vector_base"** %2, align 8
  %3 = load %"class.std::__1::__vector_base"*, %"class.std::__1::__vector_base"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %3, i32 0, i32 0
  %5 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  %6 = icmp ne %"struct.std::__1::pair"* %5, null
  br i1 %6, label %7, label %12

; <label>:7:                                      ; preds = %1
  call void @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE5clearEv(%"class.std::__1::__vector_base"* %3) #8
  %8 = call dereferenceable(1) %"class.std::__1::allocator.62"* @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE7__allocEv(%"class.std::__1::__vector_base"* %3) #8
  %9 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %3, i32 0, i32 0
  %10 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %9, align 8
  %11 = call i64 @_ZNKSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE8capacityEv(%"class.std::__1::__vector_base"* %3) #8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_4pairIRN4LL2W4NodeES5_EEEEE10deallocateERS7_PS6_m(%"class.std::__1::allocator.62"* dereferenceable(1) %8, %"struct.std::__1::pair"* %10, i64 %11) #8
  br label %12

; <label>:12:                                     ; preds = %7, %1
  ret void
}

; Function Attrs: noinline noreturn nounwind
define linkonce_odr hidden void @__clang_call_terminate(i8*) #6 {
  %2 = call i8* @__cxa_begin_catch(i8* %0) #8
  call void @_ZSt9terminatev() #9
  unreachable
}

declare i8* @__cxa_begin_catch(i8*)

declare void @_ZSt9terminatev()

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE31__annotate_contiguous_containerEPKvSA_SA_SA_(%"class.std::__1::vector"*, i8*, i8*, i8*, i8*) #4 align 2 {
  %6 = alloca %"class.std::__1::vector"*, align 8
  %7 = alloca i8*, align 8
  %8 = alloca i8*, align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8*, align 8
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %6, align 8
  store i8* %1, i8** %7, align 8
  store i8* %2, i8** %8, align 8
  store i8* %3, i8** %9, align 8
  store i8* %4, i8** %10, align 8
  %11 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %6, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair"* @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE4dataEv(%"class.std::__1::vector"*) #4 align 2 {
  %2 = alloca %"class.std::__1::vector"*, align 8
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %2, align 8
  %3 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %2, align 8
  %4 = bitcast %"class.std::__1::vector"* %3 to %"class.std::__1::__vector_base"*
  %5 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %4, i32 0, i32 0
  %6 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %5, align 8
  %7 = call %"struct.std::__1::pair"* @_ZNSt3__116__to_raw_pointerINS_4pairIRN4LL2W4NodeES4_EEEEPT_S7_(%"struct.std::__1::pair"* %6) #8
  ret %"struct.std::__1::pair"* %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i64 @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE8capacityEv(%"class.std::__1::vector"*) #4 align 2 {
  %2 = alloca %"class.std::__1::vector"*, align 8
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %2, align 8
  %3 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %2, align 8
  %4 = bitcast %"class.std::__1::vector"* %3 to %"class.std::__1::__vector_base"*
  %5 = call i64 @_ZNKSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE8capacityEv(%"class.std::__1::__vector_base"* %4) #8
  ret i64 %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i64 @_ZNKSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE4sizeEv(%"class.std::__1::vector"*) #4 align 2 {
  %2 = alloca %"class.std::__1::vector"*, align 8
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %2, align 8
  %3 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %2, align 8
  %4 = bitcast %"class.std::__1::vector"* %3 to %"class.std::__1::__vector_base"*
  %5 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %4, i32 0, i32 1
  %6 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %5, align 8
  %7 = bitcast %"class.std::__1::vector"* %3 to %"class.std::__1::__vector_base"*
  %8 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %7, i32 0, i32 0
  %9 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %8, align 8
  %10 = ptrtoint %"struct.std::__1::pair"* %6 to i64
  %11 = ptrtoint %"struct.std::__1::pair"* %9 to i64
  %12 = sub i64 %10, %11
  %13 = sdiv exact i64 %12, 16
  ret i64 %13
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair"* @_ZNSt3__116__to_raw_pointerINS_4pairIRN4LL2W4NodeES4_EEEEPT_S7_(%"struct.std::__1::pair"*) #4 {
  %2 = alloca %"struct.std::__1::pair"*, align 8
  store %"struct.std::__1::pair"* %0, %"struct.std::__1::pair"** %2, align 8
  %3 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %2, align 8
  ret %"struct.std::__1::pair"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i64 @_ZNKSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE8capacityEv(%"class.std::__1::__vector_base"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__vector_base"*, align 8
  store %"class.std::__1::__vector_base"* %0, %"class.std::__1::__vector_base"** %2, align 8
  %3 = load %"class.std::__1::__vector_base"*, %"class.std::__1::__vector_base"** %2, align 8
  %4 = call dereferenceable(8) %"struct.std::__1::pair"** @_ZNKSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE9__end_capEv(%"class.std::__1::__vector_base"* %3) #8
  %5 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  %6 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %3, i32 0, i32 0
  %7 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %6, align 8
  %8 = ptrtoint %"struct.std::__1::pair"* %5 to i64
  %9 = ptrtoint %"struct.std::__1::pair"* %7 to i64
  %10 = sub i64 %8, %9
  %11 = sdiv exact i64 %10, 16
  ret i64 %11
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::pair"** @_ZNKSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE9__end_capEv(%"class.std::__1::__vector_base"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__vector_base"*, align 8
  store %"class.std::__1::__vector_base"* %0, %"class.std::__1::__vector_base"** %2, align 8
  %3 = load %"class.std::__1::__vector_base"*, %"class.std::__1::__vector_base"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %3, i32 0, i32 2
  %5 = call dereferenceable(8) %"struct.std::__1::pair"** @_ZNKSt3__117__compressed_pairIPNS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE5firstEv(%"class.std::__1::__compressed_pair.59"* %4) #8
  ret %"struct.std::__1::pair"** %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::pair"** @_ZNKSt3__117__compressed_pairIPNS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE5firstEv(%"class.std::__1::__compressed_pair.59"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.59"*, align 8
  store %"class.std::__1::__compressed_pair.59"* %0, %"class.std::__1::__compressed_pair.59"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.59"*, %"class.std::__1::__compressed_pair.59"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.59"* %3 to %"struct.std::__1::__compressed_pair_elem.60"*
  %5 = call dereferenceable(8) %"struct.std::__1::pair"** @_ZNKSt3__122__compressed_pair_elemIPNS_4pairIRN4LL2W4NodeES4_EELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.60"* %4) #8
  ret %"struct.std::__1::pair"** %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::pair"** @_ZNKSt3__122__compressed_pair_elemIPNS_4pairIRN4LL2W4NodeES4_EELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.60"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.60"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.60"* %0, %"struct.std::__1::__compressed_pair_elem.60"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.60"*, %"struct.std::__1::__compressed_pair_elem.60"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.60", %"struct.std::__1::__compressed_pair_elem.60"* %3, i32 0, i32 0
  ret %"struct.std::__1::pair"** %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE5clearEv(%"class.std::__1::__vector_base"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__vector_base"*, align 8
  store %"class.std::__1::__vector_base"* %0, %"class.std::__1::__vector_base"** %2, align 8
  %3 = load %"class.std::__1::__vector_base"*, %"class.std::__1::__vector_base"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %3, i32 0, i32 0
  %5 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  call void @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE17__destruct_at_endEPS5_(%"class.std::__1::__vector_base"* %3, %"struct.std::__1::pair"* %5) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__116allocator_traitsINS_9allocatorINS_4pairIRN4LL2W4NodeES5_EEEEE10deallocateERS7_PS6_m(%"class.std::__1::allocator.62"* dereferenceable(1), %"struct.std::__1::pair"*, i64) #4 align 2 {
  %4 = alloca %"class.std::__1::allocator.62"*, align 8
  %5 = alloca %"struct.std::__1::pair"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.62"* %0, %"class.std::__1::allocator.62"** %4, align 8
  store %"struct.std::__1::pair"* %1, %"struct.std::__1::pair"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.62"*, %"class.std::__1::allocator.62"** %4, align 8
  %8 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__19allocatorINS_4pairIRN4LL2W4NodeES4_EEE10deallocateEPS5_m(%"class.std::__1::allocator.62"* %7, %"struct.std::__1::pair"* %8, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.62"* @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE7__allocEv(%"class.std::__1::__vector_base"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__vector_base"*, align 8
  store %"class.std::__1::__vector_base"* %0, %"class.std::__1::__vector_base"** %2, align 8
  %3 = load %"class.std::__1::__vector_base"*, %"class.std::__1::__vector_base"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %3, i32 0, i32 2
  %5 = call dereferenceable(1) %"class.std::__1::allocator.62"* @_ZNSt3__117__compressed_pairIPNS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE6secondEv(%"class.std::__1::__compressed_pair.59"* %4) #8
  ret %"class.std::__1::allocator.62"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE17__destruct_at_endEPS5_(%"class.std::__1::__vector_base"*, %"struct.std::__1::pair"*) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::__1::__vector_base"*, align 8
  %4 = alloca %"struct.std::__1::pair"*, align 8
  %5 = alloca %"struct.std::__1::pair"*, align 8
  store %"class.std::__1::__vector_base"* %0, %"class.std::__1::__vector_base"** %3, align 8
  store %"struct.std::__1::pair"* %1, %"struct.std::__1::pair"** %4, align 8
  %6 = load %"class.std::__1::__vector_base"*, %"class.std::__1::__vector_base"** %3, align 8
  %7 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %6, i32 0, i32 1
  %8 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %7, align 8
  store %"struct.std::__1::pair"* %8, %"struct.std::__1::pair"** %5, align 8
  br label %9

; <label>:9:                                      ; preds = %18, %2
  %10 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  %11 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %5, align 8
  %12 = icmp ne %"struct.std::__1::pair"* %10, %11
  br i1 %12, label %13, label %19

; <label>:13:                                     ; preds = %9
  %14 = call dereferenceable(1) %"class.std::__1::allocator.62"* @_ZNSt3__113__vector_baseINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE7__allocEv(%"class.std::__1::__vector_base"* %6) #8
  %15 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %5, align 8
  %16 = getelementptr inbounds %"struct.std::__1::pair", %"struct.std::__1::pair"* %15, i32 -1
  store %"struct.std::__1::pair"* %16, %"struct.std::__1::pair"** %5, align 8
  %17 = call %"struct.std::__1::pair"* @_ZNSt3__116__to_raw_pointerINS_4pairIRN4LL2W4NodeES4_EEEEPT_S7_(%"struct.std::__1::pair"* %16) #8
  invoke void @_ZNSt3__116allocator_traitsINS_9allocatorINS_4pairIRN4LL2W4NodeES5_EEEEE7destroyIS6_EEvRS7_PT_(%"class.std::__1::allocator.62"* dereferenceable(1) %14, %"struct.std::__1::pair"* %17)
          to label %18 unwind label %22

; <label>:18:                                     ; preds = %13
  br label %9

; <label>:19:                                     ; preds = %9
  %20 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  %21 = getelementptr inbounds %"class.std::__1::__vector_base", %"class.std::__1::__vector_base"* %6, i32 0, i32 1
  store %"struct.std::__1::pair"* %20, %"struct.std::__1::pair"** %21, align 8
  ret void

; <label>:22:                                     ; preds = %13
  %23 = landingpad { i8*, i32 }
          catch i8* null
  %24 = extractvalue { i8*, i32 } %23, 0
  call void @__clang_call_terminate(i8* %24) #9
  unreachable
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_4pairIRN4LL2W4NodeES5_EEEEE7destroyIS6_EEvRS7_PT_(%"class.std::__1::allocator.62"* dereferenceable(1), %"struct.std::__1::pair"*) #1 align 2 {
  %3 = alloca %"class.std::__1::allocator.62"*, align 8
  %4 = alloca %"struct.std::__1::pair"*, align 8
  %5 = alloca %"struct.std::__1::integral_constant", align 1
  %6 = alloca %"struct.std::__1::__has_destroy", align 1
  store %"class.std::__1::allocator.62"* %0, %"class.std::__1::allocator.62"** %3, align 8
  store %"struct.std::__1::pair"* %1, %"struct.std::__1::pair"** %4, align 8
  %7 = bitcast %"struct.std::__1::__has_destroy"* %6 to %"struct.std::__1::integral_constant"*
  %8 = load %"class.std::__1::allocator.62"*, %"class.std::__1::allocator.62"** %3, align 8
  %9 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_4pairIRN4LL2W4NodeES5_EEEEE9__destroyIS6_EEvNS_17integral_constantIbLb1EEERS7_PT_(%"class.std::__1::allocator.62"* dereferenceable(1) %8, %"struct.std::__1::pair"* %9)
  ret void
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_4pairIRN4LL2W4NodeES5_EEEEE9__destroyIS6_EEvNS_17integral_constantIbLb1EEERS7_PT_(%"class.std::__1::allocator.62"* dereferenceable(1), %"struct.std::__1::pair"*) #1 align 2 {
  %3 = alloca %"struct.std::__1::integral_constant", align 1
  %4 = alloca %"class.std::__1::allocator.62"*, align 8
  %5 = alloca %"struct.std::__1::pair"*, align 8
  store %"class.std::__1::allocator.62"* %0, %"class.std::__1::allocator.62"** %4, align 8
  store %"struct.std::__1::pair"* %1, %"struct.std::__1::pair"** %5, align 8
  %6 = load %"class.std::__1::allocator.62"*, %"class.std::__1::allocator.62"** %4, align 8
  %7 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %5, align 8
  call void @_ZNSt3__19allocatorINS_4pairIRN4LL2W4NodeES4_EEE7destroyEPS5_(%"class.std::__1::allocator.62"* %6, %"struct.std::__1::pair"* %7)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorINS_4pairIRN4LL2W4NodeES4_EEE7destroyEPS5_(%"class.std::__1::allocator.62"*, %"struct.std::__1::pair"*) #4 align 2 {
  %3 = alloca %"class.std::__1::allocator.62"*, align 8
  %4 = alloca %"struct.std::__1::pair"*, align 8
  store %"class.std::__1::allocator.62"* %0, %"class.std::__1::allocator.62"** %3, align 8
  store %"struct.std::__1::pair"* %1, %"struct.std::__1::pair"** %4, align 8
  %5 = load %"class.std::__1::allocator.62"*, %"class.std::__1::allocator.62"** %3, align 8
  %6 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorINS_4pairIRN4LL2W4NodeES4_EEE10deallocateEPS5_m(%"class.std::__1::allocator.62"*, %"struct.std::__1::pair"*, i64) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::allocator.62"*, align 8
  %5 = alloca %"struct.std::__1::pair"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.62"* %0, %"class.std::__1::allocator.62"** %4, align 8
  store %"struct.std::__1::pair"* %1, %"struct.std::__1::pair"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.62"*, %"class.std::__1::allocator.62"** %4, align 8
  %8 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %5, align 8
  %9 = bitcast %"struct.std::__1::pair"* %8 to i8*
  %10 = load i64, i64* %6, align 8
  %11 = mul i64 %10, 16
  invoke void @_ZNSt3__119__libcpp_deallocateEPvmm(i8* %9, i64 %11, i64 8)
          to label %12 unwind label %13

; <label>:12:                                     ; preds = %3
  ret void

; <label>:13:                                     ; preds = %3
  %14 = landingpad { i8*, i32 }
          catch i8* null
  %15 = extractvalue { i8*, i32 } %14, 0
  call void @__clang_call_terminate(i8* %15) #9
  unreachable
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__119__libcpp_deallocateEPvmm(i8*, i64, i64) #1 {
  %4 = alloca i8*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  store i8* %0, i8** %4, align 8
  store i64 %1, i64* %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = load i64, i64* %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__117_DeallocateCaller33__do_deallocate_handle_size_alignEPvmm(i8* %7, i64 %8, i64 %9)
  ret void
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__117_DeallocateCaller33__do_deallocate_handle_size_alignEPvmm(i8*, i64, i64) #1 align 2 {
  %4 = alloca i8*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  %7 = alloca i64, align 8
  store i8* %0, i8** %4, align 8
  store i64 %1, i64* %5, align 8
  store i64 %2, i64* %6, align 8
  %8 = load i64, i64* %6, align 8
  %9 = call zeroext i1 @_ZNSt3__124__is_overaligned_for_newEm(i64 %8) #8
  br i1 %9, label %10, label %15

; <label>:10:                                     ; preds = %3
  %11 = load i64, i64* %6, align 8
  store i64 %11, i64* %7, align 8
  %12 = load i8*, i8** %4, align 8
  %13 = load i64, i64* %5, align 8
  %14 = load i64, i64* %7, align 8
  call void @_ZNSt3__117_DeallocateCaller27__do_deallocate_handle_sizeEPvmSt11align_val_t(i8* %12, i64 %13, i64 %14)
  br label %18

; <label>:15:                                     ; preds = %3
  %16 = load i8*, i8** %4, align 8
  %17 = load i64, i64* %5, align 8
  call void @_ZNSt3__117_DeallocateCaller27__do_deallocate_handle_sizeEPvm(i8* %16, i64 %17)
  br label %18

; <label>:18:                                     ; preds = %15, %10
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden zeroext i1 @_ZNSt3__124__is_overaligned_for_newEm(i64) #4 {
  %2 = alloca i64, align 8
  store i64 %0, i64* %2, align 8
  %3 = load i64, i64* %2, align 8
  %4 = icmp ugt i64 %3, 16
  ret i1 %4
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__117_DeallocateCaller27__do_deallocate_handle_sizeEPvmSt11align_val_t(i8*, i64, i64) #1 align 2 {
  %4 = alloca i8*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i64, align 8
  store i8* %0, i8** %4, align 8
  store i64 %1, i64* %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load i8*, i8** %4, align 8
  %8 = load i64, i64* %6, align 8
  call void @_ZNSt3__117_DeallocateCaller9__do_callISt11align_val_tEEvPvT_(i8* %7, i64 %8)
  ret void
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__117_DeallocateCaller27__do_deallocate_handle_sizeEPvm(i8*, i64) #1 align 2 {
  %3 = alloca i8*, align 8
  %4 = alloca i64, align 8
  store i8* %0, i8** %3, align 8
  store i64 %1, i64* %4, align 8
  %5 = load i8*, i8** %3, align 8
  call void @_ZNSt3__117_DeallocateCaller9__do_callEPv(i8* %5)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__117_DeallocateCaller9__do_callISt11align_val_tEEvPvT_(i8*, i64) #4 align 2 {
  %3 = alloca i8*, align 8
  %4 = alloca i64, align 8
  store i8* %0, i8** %3, align 8
  store i64 %1, i64* %4, align 8
  %5 = load i8*, i8** %3, align 8
  %6 = load i64, i64* %4, align 8
  call void @_ZdlPvSt11align_val_t(i8* %5, i64 %6) #10
  ret void
}

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPvSt11align_val_t(i8*, i64) #7

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__117_DeallocateCaller9__do_callEPv(i8*) #4 align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  call void @_ZdlPv(i8* %3) #10
  ret void
}

; Function Attrs: nobuiltin nounwind
declare void @_ZdlPv(i8*) #7

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.62"* @_ZNSt3__117__compressed_pairIPNS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE6secondEv(%"class.std::__1::__compressed_pair.59"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.59"*, align 8
  store %"class.std::__1::__compressed_pair.59"* %0, %"class.std::__1::__compressed_pair.59"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.59"*, %"class.std::__1::__compressed_pair.59"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.59"* %3 to %"struct.std::__1::__compressed_pair_elem.61"*
  %5 = call dereferenceable(1) %"class.std::__1::allocator.62"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_4pairIRN4LL2W4NodeES5_EEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.61"* %4) #8
  ret %"class.std::__1::allocator.62"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.62"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_4pairIRN4LL2W4NodeES5_EEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.61"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.61"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.61"* %0, %"struct.std::__1::__compressed_pair_elem.61"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.61"*, %"struct.std::__1::__compressed_pair_elem.61"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.61"* %3 to %"class.std::__1::allocator.62"*
  ret %"class.std::__1::allocator.62"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__113unordered_mapIPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEES6_S8_NS9_INS_4pairIKS3_SB_EEEEED2Ev(%"class.std::__1::unordered_map.31"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unordered_map.31"*, align 8
  store %"class.std::__1::unordered_map.31"* %0, %"class.std::__1::unordered_map.31"** %2, align 8
  %3 = load %"class.std::__1::unordered_map.31"*, %"class.std::__1::unordered_map.31"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::unordered_map.31", %"class.std::__1::unordered_map.31"* %3, i32 0, i32 0
  call void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEENS_22__unordered_map_hasherIS4_SD_S7_Lb1EEENS_21__unordered_map_equalIS4_SD_S9_Lb1EEENSA_ISD_EEED1Ev(%"class.std::__1::__hash_table.32"* %4) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEENS_22__unordered_map_hasherIS4_SD_S7_Lb1EEENS_21__unordered_map_equalIS4_SD_S9_Lb1EEENSA_ISD_EEED1Ev(%"class.std::__1::__hash_table.32"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.32"*, align 8
  store %"class.std::__1::__hash_table.32"* %0, %"class.std::__1::__hash_table.32"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.32"*, %"class.std::__1::__hash_table.32"** %2, align 8
  call void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEENS_22__unordered_map_hasherIS4_SD_S7_Lb1EEENS_21__unordered_map_equalIS4_SD_S9_Lb1EEENSA_ISD_EEED2Ev(%"class.std::__1::__hash_table.32"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEENS_22__unordered_map_hasherIS4_SD_S7_Lb1EEENS_21__unordered_map_equalIS4_SD_S9_Lb1EEENSA_ISD_EEED2Ev(%"class.std::__1::__hash_table.32"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.32"*, align 8
  store %"class.std::__1::__hash_table.32"* %0, %"class.std::__1::__hash_table.32"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.32"*, %"class.std::__1::__hash_table.32"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__hash_table.32", %"class.std::__1::__hash_table.32"* %3, i32 0, i32 1
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.36"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENSC_ISH_EEE5firstEv(%"class.std::__1::__compressed_pair.43"* %4) #8
  %6 = getelementptr inbounds %"struct.std::__1::__hash_node_base.36", %"struct.std::__1::__hash_node_base.36"* %5, i32 0, i32 0
  %7 = load %"struct.std::__1::__hash_node_base.36"*, %"struct.std::__1::__hash_node_base.36"** %6, align 8
  call void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEENS_22__unordered_map_hasherIS4_SD_S7_Lb1EEENS_21__unordered_map_equalIS4_SD_S9_Lb1EEENSA_ISD_EEE17__deallocate_nodeEPNS_16__hash_node_baseIPNS_11__hash_nodeISD_PvEEEE(%"class.std::__1::__hash_table.32"* %3, %"struct.std::__1::__hash_node_base.36"* %7) #8
  %8 = getelementptr inbounds %"class.std::__1::__hash_table.32", %"class.std::__1::__hash_table.32"* %3, i32 0, i32 0
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEED1Ev(%"class.std::__1::unique_ptr.33"* %8) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEENS_22__unordered_map_hasherIS4_SD_S7_Lb1EEENS_21__unordered_map_equalIS4_SD_S9_Lb1EEENSA_ISD_EEE17__deallocate_nodeEPNS_16__hash_node_baseIPNS_11__hash_nodeISD_PvEEEE(%"class.std::__1::__hash_table.32"*, %"struct.std::__1::__hash_node_base.36"*) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::__1::__hash_table.32"*, align 8
  %4 = alloca %"struct.std::__1::__hash_node_base.36"*, align 8
  %5 = alloca %"class.std::__1::allocator.46"*, align 8
  %6 = alloca %"struct.std::__1::__hash_node_base.36"*, align 8
  %7 = alloca %"struct.std::__1::__hash_node"*, align 8
  store %"class.std::__1::__hash_table.32"* %0, %"class.std::__1::__hash_table.32"** %3, align 8
  store %"struct.std::__1::__hash_node_base.36"* %1, %"struct.std::__1::__hash_node_base.36"** %4, align 8
  %8 = load %"class.std::__1::__hash_table.32"*, %"class.std::__1::__hash_table.32"** %3, align 8
  %9 = call dereferenceable(1) %"class.std::__1::allocator.46"* @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEENS_22__unordered_map_hasherIS4_SD_S7_Lb1EEENS_21__unordered_map_equalIS4_SD_S9_Lb1EEENSA_ISD_EEE12__node_allocEv(%"class.std::__1::__hash_table.32"* %8) #8
  store %"class.std::__1::allocator.46"* %9, %"class.std::__1::allocator.46"** %5, align 8
  br label %10

; <label>:10:                                     ; preds = %24, %2
  %11 = load %"struct.std::__1::__hash_node_base.36"*, %"struct.std::__1::__hash_node_base.36"** %4, align 8
  %12 = icmp ne %"struct.std::__1::__hash_node_base.36"* %11, null
  br i1 %12, label %13, label %28

; <label>:13:                                     ; preds = %10
  %14 = load %"struct.std::__1::__hash_node_base.36"*, %"struct.std::__1::__hash_node_base.36"** %4, align 8
  %15 = getelementptr inbounds %"struct.std::__1::__hash_node_base.36", %"struct.std::__1::__hash_node_base.36"* %14, i32 0, i32 0
  %16 = load %"struct.std::__1::__hash_node_base.36"*, %"struct.std::__1::__hash_node_base.36"** %15, align 8
  store %"struct.std::__1::__hash_node_base.36"* %16, %"struct.std::__1::__hash_node_base.36"** %6, align 8
  %17 = load %"struct.std::__1::__hash_node_base.36"*, %"struct.std::__1::__hash_node_base.36"** %4, align 8
  %18 = call %"struct.std::__1::__hash_node"* @_ZNSt3__116__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS5_NS_4hashIS5_EENS_8equal_toIS5_EENS_9allocatorIS5_EEEEEEPvEEE8__upcastEv(%"struct.std::__1::__hash_node_base.36"* %17) #8
  store %"struct.std::__1::__hash_node"* %18, %"struct.std::__1::__hash_node"** %7, align 8
  %19 = load %"class.std::__1::allocator.46"*, %"class.std::__1::allocator.46"** %5, align 8
  %20 = load %"struct.std::__1::__hash_node"*, %"struct.std::__1::__hash_node"** %7, align 8
  %21 = getelementptr inbounds %"struct.std::__1::__hash_node", %"struct.std::__1::__hash_node"* %20, i32 0, i32 2
  %22 = invoke %"struct.std::__1::pair.119"* @_ZNSt3__122__hash_key_value_typesINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEEE9__get_ptrERSD_(%"struct.std::__1::__hash_value_type"* dereferenceable(48) %21)
          to label %23 unwind label %29

; <label>:23:                                     ; preds = %13
  invoke void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS1_IS6_EEEEEEPvEEEEE7destroyINS_4pairIKS6_SD_EEEEvRSH_PT_(%"class.std::__1::allocator.46"* dereferenceable(1) %19, %"struct.std::__1::pair.119"* %22)
          to label %24 unwind label %29

; <label>:24:                                     ; preds = %23
  %25 = load %"class.std::__1::allocator.46"*, %"class.std::__1::allocator.46"** %5, align 8
  %26 = load %"struct.std::__1::__hash_node"*, %"struct.std::__1::__hash_node"** %7, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS1_IS6_EEEEEEPvEEEEE10deallocateERSH_PSG_m(%"class.std::__1::allocator.46"* dereferenceable(1) %25, %"struct.std::__1::__hash_node"* %26, i64 1) #8
  %27 = load %"struct.std::__1::__hash_node_base.36"*, %"struct.std::__1::__hash_node_base.36"** %6, align 8
  store %"struct.std::__1::__hash_node_base.36"* %27, %"struct.std::__1::__hash_node_base.36"** %4, align 8
  br label %10

; <label>:28:                                     ; preds = %10
  ret void

; <label>:29:                                     ; preds = %23, %13
  %30 = landingpad { i8*, i32 }
          catch i8* null
  %31 = extractvalue { i8*, i32 } %30, 0
  call void @__clang_call_terminate(i8* %31) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.36"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENSC_ISH_EEE5firstEv(%"class.std::__1::__compressed_pair.43"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.43"*, align 8
  store %"class.std::__1::__compressed_pair.43"* %0, %"class.std::__1::__compressed_pair.43"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.43"*, %"class.std::__1::__compressed_pair.43"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.43"* %3 to %"struct.std::__1::__compressed_pair_elem.44"*
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.36"* @_ZNSt3__122__compressed_pair_elemINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.44"* %4) #8
  ret %"struct.std::__1::__hash_node_base.36"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEED1Ev(%"class.std::__1::unique_ptr.33"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.33"*, align 8
  store %"class.std::__1::unique_ptr.33"* %0, %"class.std::__1::unique_ptr.33"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.33"*, %"class.std::__1::unique_ptr.33"** %2, align 8
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEED2Ev(%"class.std::__1::unique_ptr.33"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.46"* @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEENS_22__unordered_map_hasherIS4_SD_S7_Lb1EEENS_21__unordered_map_equalIS4_SD_S9_Lb1EEENSA_ISD_EEE12__node_allocEv(%"class.std::__1::__hash_table.32"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.32"*, align 8
  store %"class.std::__1::__hash_table.32"* %0, %"class.std::__1::__hash_table.32"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.32"*, %"class.std::__1::__hash_table.32"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__hash_table.32", %"class.std::__1::__hash_table.32"* %3, i32 0, i32 1
  %5 = call dereferenceable(1) %"class.std::__1::allocator.46"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENSC_ISH_EEE6secondEv(%"class.std::__1::__compressed_pair.43"* %4) #8
  ret %"class.std::__1::allocator.46"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node"* @_ZNSt3__116__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS5_NS_4hashIS5_EENS_8equal_toIS5_EENS_9allocatorIS5_EEEEEEPvEEE8__upcastEv(%"struct.std::__1::__hash_node_base.36"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_node_base.36"*, align 8
  store %"struct.std::__1::__hash_node_base.36"* %0, %"struct.std::__1::__hash_node_base.36"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.36"*, %"struct.std::__1::__hash_node_base.36"** %2, align 8
  %4 = call %"struct.std::__1::__hash_node_base.36"* @_ZNSt3__114pointer_traitsIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEEE10pointer_toERSJ_(%"struct.std::__1::__hash_node_base.36"* dereferenceable(8) %3) #8
  %5 = bitcast %"struct.std::__1::__hash_node_base.36"* %4 to %"struct.std::__1::__hash_node"*
  ret %"struct.std::__1::__hash_node"* %5
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS1_IS6_EEEEEEPvEEEEE7destroyINS_4pairIKS6_SD_EEEEvRSH_PT_(%"class.std::__1::allocator.46"* dereferenceable(1), %"struct.std::__1::pair.119"*) #1 align 2 {
  %3 = alloca %"class.std::__1::allocator.46"*, align 8
  %4 = alloca %"struct.std::__1::pair.119"*, align 8
  %5 = alloca %"struct.std::__1::integral_constant.141", align 1
  %6 = alloca %"struct.std::__1::__has_destroy.142", align 1
  store %"class.std::__1::allocator.46"* %0, %"class.std::__1::allocator.46"** %3, align 8
  store %"struct.std::__1::pair.119"* %1, %"struct.std::__1::pair.119"** %4, align 8
  %7 = bitcast %"struct.std::__1::__has_destroy.142"* %6 to %"struct.std::__1::integral_constant.141"*
  %8 = load %"class.std::__1::allocator.46"*, %"class.std::__1::allocator.46"** %3, align 8
  %9 = load %"struct.std::__1::pair.119"*, %"struct.std::__1::pair.119"** %4, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS1_IS6_EEEEEEPvEEEEE9__destroyINS_4pairIKS6_SD_EEEEvNS_17integral_constantIbLb0EEERSH_PT_(%"class.std::__1::allocator.46"* dereferenceable(1) %8, %"struct.std::__1::pair.119"* %9)
  ret void
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair.119"* @_ZNSt3__122__hash_key_value_typesINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEEE9__get_ptrERSD_(%"struct.std::__1::__hash_value_type"* dereferenceable(48)) #1 align 2 {
  %2 = alloca %"struct.std::__1::__hash_value_type"*, align 8
  store %"struct.std::__1::__hash_value_type"* %0, %"struct.std::__1::__hash_value_type"** %2, align 8
  %3 = load %"struct.std::__1::__hash_value_type"*, %"struct.std::__1::__hash_value_type"** %2, align 8
  %4 = call dereferenceable(48) %"struct.std::__1::pair.119"* @_ZNSt3__117__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEEE11__get_valueEv(%"struct.std::__1::__hash_value_type"* %3)
  %5 = call %"struct.std::__1::pair.119"* @_ZNSt3__19addressofINS_4pairIKPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEEEEPT_RSF_(%"struct.std::__1::pair.119"* dereferenceable(48) %4) #8
  ret %"struct.std::__1::pair.119"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS1_IS6_EEEEEEPvEEEEE10deallocateERSH_PSG_m(%"class.std::__1::allocator.46"* dereferenceable(1), %"struct.std::__1::__hash_node"*, i64) #4 align 2 {
  %4 = alloca %"class.std::__1::allocator.46"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.46"* %0, %"class.std::__1::allocator.46"** %4, align 8
  store %"struct.std::__1::__hash_node"* %1, %"struct.std::__1::__hash_node"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.46"*, %"class.std::__1::allocator.46"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node"*, %"struct.std::__1::__hash_node"** %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__19allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS5_NS_4hashIS5_EENS_8equal_toIS5_EENS0_IS5_EEEEEEPvEEE10deallocateEPSF_m(%"class.std::__1::allocator.46"* %7, %"struct.std::__1::__hash_node"* %8, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.46"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENSC_ISH_EEE6secondEv(%"class.std::__1::__compressed_pair.43"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.43"*, align 8
  store %"class.std::__1::__compressed_pair.43"* %0, %"class.std::__1::__compressed_pair.43"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.43"*, %"class.std::__1::__compressed_pair.43"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.43"* %3 to %"struct.std::__1::__compressed_pair_elem.45"*
  %5 = call dereferenceable(1) %"class.std::__1::allocator.46"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS1_IS6_EEEEEEPvEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.45"* %4) #8
  ret %"class.std::__1::allocator.46"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.46"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS1_IS6_EEEEEEPvEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.45"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.45"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.45"* %0, %"struct.std::__1::__compressed_pair_elem.45"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.45"*, %"struct.std::__1::__compressed_pair_elem.45"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.45"* %3 to %"class.std::__1::allocator.46"*
  ret %"class.std::__1::allocator.46"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node_base.36"* @_ZNSt3__114pointer_traitsIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEEE10pointer_toERSJ_(%"struct.std::__1::__hash_node_base.36"* dereferenceable(8)) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_node_base.36"*, align 8
  store %"struct.std::__1::__hash_node_base.36"* %0, %"struct.std::__1::__hash_node_base.36"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.36"*, %"struct.std::__1::__hash_node_base.36"** %2, align 8
  %4 = call %"struct.std::__1::__hash_node_base.36"* @_ZNSt3__19addressofINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEEEEPT_RSK_(%"struct.std::__1::__hash_node_base.36"* dereferenceable(8) %3) #8
  ret %"struct.std::__1::__hash_node_base.36"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node_base.36"* @_ZNSt3__19addressofINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEEEEPT_RSK_(%"struct.std::__1::__hash_node_base.36"* dereferenceable(8)) #4 {
  %2 = alloca %"struct.std::__1::__hash_node_base.36"*, align 8
  store %"struct.std::__1::__hash_node_base.36"* %0, %"struct.std::__1::__hash_node_base.36"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.36"*, %"struct.std::__1::__hash_node_base.36"** %2, align 8
  ret %"struct.std::__1::__hash_node_base.36"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS1_IS6_EEEEEEPvEEEEE9__destroyINS_4pairIKS6_SD_EEEEvNS_17integral_constantIbLb0EEERSH_PT_(%"class.std::__1::allocator.46"* dereferenceable(1), %"struct.std::__1::pair.119"*) #4 align 2 {
  %3 = alloca %"struct.std::__1::integral_constant.141", align 1
  %4 = alloca %"class.std::__1::allocator.46"*, align 8
  %5 = alloca %"struct.std::__1::pair.119"*, align 8
  store %"class.std::__1::allocator.46"* %0, %"class.std::__1::allocator.46"** %4, align 8
  store %"struct.std::__1::pair.119"* %1, %"struct.std::__1::pair.119"** %5, align 8
  %6 = load %"struct.std::__1::pair.119"*, %"struct.std::__1::pair.119"** %5, align 8
  call void @_ZNSt3__14pairIKPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEEED1Ev(%"struct.std::__1::pair.119"* %6) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__14pairIKPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEEED1Ev(%"struct.std::__1::pair.119"*) unnamed_addr #4 align 2 {
  %2 = alloca %"struct.std::__1::pair.119"*, align 8
  store %"struct.std::__1::pair.119"* %0, %"struct.std::__1::pair.119"** %2, align 8
  %3 = load %"struct.std::__1::pair.119"*, %"struct.std::__1::pair.119"** %2, align 8
  call void @_ZNSt3__14pairIKPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEEED2Ev(%"struct.std::__1::pair.119"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__14pairIKPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEEED2Ev(%"struct.std::__1::pair.119"*) unnamed_addr #4 align 2 {
  %2 = alloca %"struct.std::__1::pair.119"*, align 8
  store %"struct.std::__1::pair.119"* %0, %"struct.std::__1::pair.119"** %2, align 8
  %3 = load %"struct.std::__1::pair.119"*, %"struct.std::__1::pair.119"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::pair.119", %"struct.std::__1::pair.119"* %3, i32 0, i32 1
  call void @_ZNSt3__113unordered_setIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEED1Ev(%"class.std::__1::unordered_set"* %4) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__113unordered_setIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEED1Ev(%"class.std::__1::unordered_set"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unordered_set"*, align 8
  store %"class.std::__1::unordered_set"* %0, %"class.std::__1::unordered_set"** %2, align 8
  %3 = load %"class.std::__1::unordered_set"*, %"class.std::__1::unordered_set"** %2, align 8
  call void @_ZNSt3__113unordered_setIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEED2Ev(%"class.std::__1::unordered_set"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__113unordered_setIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEED2Ev(%"class.std::__1::unordered_set"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unordered_set"*, align 8
  store %"class.std::__1::unordered_set"* %0, %"class.std::__1::unordered_set"** %2, align 8
  %3 = load %"class.std::__1::unordered_set"*, %"class.std::__1::unordered_set"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::unordered_set", %"class.std::__1::unordered_set"* %3, i32 0, i32 0
  call void @_ZNSt3__112__hash_tableIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEED1Ev(%"class.std::__1::__hash_table.120"* %4) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEED1Ev(%"class.std::__1::__hash_table.120"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.120"*, align 8
  store %"class.std::__1::__hash_table.120"* %0, %"class.std::__1::__hash_table.120"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.120"*, %"class.std::__1::__hash_table.120"** %2, align 8
  call void @_ZNSt3__112__hash_tableIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEED2Ev(%"class.std::__1::__hash_table.120"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEED2Ev(%"class.std::__1::__hash_table.120"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.120"*, align 8
  store %"class.std::__1::__hash_table.120"* %0, %"class.std::__1::__hash_table.120"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.120"*, %"class.std::__1::__hash_table.120"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__hash_table.120", %"class.std::__1::__hash_table.120"* %3, i32 0, i32 1
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.124"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_9allocatorIS7_EEE5firstEv(%"class.std::__1::__compressed_pair.131"* %4) #8
  %6 = getelementptr inbounds %"struct.std::__1::__hash_node_base.124", %"struct.std::__1::__hash_node_base.124"* %5, i32 0, i32 0
  %7 = load %"struct.std::__1::__hash_node_base.124"*, %"struct.std::__1::__hash_node_base.124"** %6, align 8
  call void @_ZNSt3__112__hash_tableIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEE17__deallocate_nodeEPNS_16__hash_node_baseIPNS_11__hash_nodeIS3_PvEEEE(%"class.std::__1::__hash_table.120"* %3, %"struct.std::__1::__hash_node_base.124"* %7) #8
  %8 = getelementptr inbounds %"class.std::__1::__hash_table.120", %"class.std::__1::__hash_table.120"* %3, i32 0, i32 0
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEED1Ev(%"class.std::__1::unique_ptr.121"* %8) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEE17__deallocate_nodeEPNS_16__hash_node_baseIPNS_11__hash_nodeIS3_PvEEEE(%"class.std::__1::__hash_table.120"*, %"struct.std::__1::__hash_node_base.124"*) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::__1::__hash_table.120"*, align 8
  %4 = alloca %"struct.std::__1::__hash_node_base.124"*, align 8
  %5 = alloca %"class.std::__1::allocator.134"*, align 8
  %6 = alloca %"struct.std::__1::__hash_node_base.124"*, align 8
  %7 = alloca %"struct.std::__1::__hash_node.143"*, align 8
  store %"class.std::__1::__hash_table.120"* %0, %"class.std::__1::__hash_table.120"** %3, align 8
  store %"struct.std::__1::__hash_node_base.124"* %1, %"struct.std::__1::__hash_node_base.124"** %4, align 8
  %8 = load %"class.std::__1::__hash_table.120"*, %"class.std::__1::__hash_table.120"** %3, align 8
  %9 = call dereferenceable(1) %"class.std::__1::allocator.134"* @_ZNSt3__112__hash_tableIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEE12__node_allocEv(%"class.std::__1::__hash_table.120"* %8) #8
  store %"class.std::__1::allocator.134"* %9, %"class.std::__1::allocator.134"** %5, align 8
  br label %10

; <label>:10:                                     ; preds = %24, %2
  %11 = load %"struct.std::__1::__hash_node_base.124"*, %"struct.std::__1::__hash_node_base.124"** %4, align 8
  %12 = icmp ne %"struct.std::__1::__hash_node_base.124"* %11, null
  br i1 %12, label %13, label %28

; <label>:13:                                     ; preds = %10
  %14 = load %"struct.std::__1::__hash_node_base.124"*, %"struct.std::__1::__hash_node_base.124"** %4, align 8
  %15 = getelementptr inbounds %"struct.std::__1::__hash_node_base.124", %"struct.std::__1::__hash_node_base.124"* %14, i32 0, i32 0
  %16 = load %"struct.std::__1::__hash_node_base.124"*, %"struct.std::__1::__hash_node_base.124"** %15, align 8
  store %"struct.std::__1::__hash_node_base.124"* %16, %"struct.std::__1::__hash_node_base.124"** %6, align 8
  %17 = load %"struct.std::__1::__hash_node_base.124"*, %"struct.std::__1::__hash_node_base.124"** %4, align 8
  %18 = call %"struct.std::__1::__hash_node.143"* @_ZNSt3__116__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEE8__upcastEv(%"struct.std::__1::__hash_node_base.124"* %17) #8
  store %"struct.std::__1::__hash_node.143"* %18, %"struct.std::__1::__hash_node.143"** %7, align 8
  %19 = load %"class.std::__1::allocator.134"*, %"class.std::__1::allocator.134"** %5, align 8
  %20 = load %"struct.std::__1::__hash_node.143"*, %"struct.std::__1::__hash_node.143"** %7, align 8
  %21 = getelementptr inbounds %"struct.std::__1::__hash_node.143", %"struct.std::__1::__hash_node.143"* %20, i32 0, i32 2
  %22 = invoke %"class.LL2W::Node"** @_ZNSt3__122__hash_key_value_typesIPN4LL2W4NodeEE9__get_ptrERS3_(%"class.LL2W::Node"** dereferenceable(8) %21)
          to label %23 unwind label %29

; <label>:23:                                     ; preds = %13
  invoke void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE7destroyIS5_EEvRS8_PT_(%"class.std::__1::allocator.134"* dereferenceable(1) %19, %"class.LL2W::Node"** %22)
          to label %24 unwind label %29

; <label>:24:                                     ; preds = %23
  %25 = load %"class.std::__1::allocator.134"*, %"class.std::__1::allocator.134"** %5, align 8
  %26 = load %"struct.std::__1::__hash_node.143"*, %"struct.std::__1::__hash_node.143"** %7, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE10deallocateERS8_PS7_m(%"class.std::__1::allocator.134"* dereferenceable(1) %25, %"struct.std::__1::__hash_node.143"* %26, i64 1) #8
  %27 = load %"struct.std::__1::__hash_node_base.124"*, %"struct.std::__1::__hash_node_base.124"** %6, align 8
  store %"struct.std::__1::__hash_node_base.124"* %27, %"struct.std::__1::__hash_node_base.124"** %4, align 8
  br label %10

; <label>:28:                                     ; preds = %10
  ret void

; <label>:29:                                     ; preds = %23, %13
  %30 = landingpad { i8*, i32 }
          catch i8* null
  %31 = extractvalue { i8*, i32 } %30, 0
  call void @__clang_call_terminate(i8* %31) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.124"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_9allocatorIS7_EEE5firstEv(%"class.std::__1::__compressed_pair.131"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.131"*, align 8
  store %"class.std::__1::__compressed_pair.131"* %0, %"class.std::__1::__compressed_pair.131"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.131"*, %"class.std::__1::__compressed_pair.131"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.131"* %3 to %"struct.std::__1::__compressed_pair_elem.132"*
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.124"* @_ZNSt3__122__compressed_pair_elemINS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.132"* %4) #8
  ret %"struct.std::__1::__hash_node_base.124"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEED1Ev(%"class.std::__1::unique_ptr.121"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.121"*, align 8
  store %"class.std::__1::unique_ptr.121"* %0, %"class.std::__1::unique_ptr.121"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.121"*, %"class.std::__1::unique_ptr.121"** %2, align 8
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEED2Ev(%"class.std::__1::unique_ptr.121"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.134"* @_ZNSt3__112__hash_tableIPN4LL2W4NodeENS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEE12__node_allocEv(%"class.std::__1::__hash_table.120"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.120"*, align 8
  store %"class.std::__1::__hash_table.120"* %0, %"class.std::__1::__hash_table.120"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.120"*, %"class.std::__1::__hash_table.120"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__hash_table.120", %"class.std::__1::__hash_table.120"* %3, i32 0, i32 1
  %5 = call dereferenceable(1) %"class.std::__1::allocator.134"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_9allocatorIS7_EEE6secondEv(%"class.std::__1::__compressed_pair.131"* %4) #8
  ret %"class.std::__1::allocator.134"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node.143"* @_ZNSt3__116__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEE8__upcastEv(%"struct.std::__1::__hash_node_base.124"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_node_base.124"*, align 8
  store %"struct.std::__1::__hash_node_base.124"* %0, %"struct.std::__1::__hash_node_base.124"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.124"*, %"struct.std::__1::__hash_node_base.124"** %2, align 8
  %4 = call %"struct.std::__1::__hash_node_base.124"* @_ZNSt3__114pointer_traitsIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE10pointer_toERS9_(%"struct.std::__1::__hash_node_base.124"* dereferenceable(8) %3) #8
  %5 = bitcast %"struct.std::__1::__hash_node_base.124"* %4 to %"struct.std::__1::__hash_node.143"*
  ret %"struct.std::__1::__hash_node.143"* %5
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE7destroyIS5_EEvRS8_PT_(%"class.std::__1::allocator.134"* dereferenceable(1), %"class.LL2W::Node"**) #1 align 2 {
  %3 = alloca %"class.std::__1::allocator.134"*, align 8
  %4 = alloca %"class.LL2W::Node"**, align 8
  %5 = alloca %"struct.std::__1::integral_constant.141", align 1
  %6 = alloca %"struct.std::__1::__has_destroy.144", align 1
  store %"class.std::__1::allocator.134"* %0, %"class.std::__1::allocator.134"** %3, align 8
  store %"class.LL2W::Node"** %1, %"class.LL2W::Node"*** %4, align 8
  %7 = bitcast %"struct.std::__1::__has_destroy.144"* %6 to %"struct.std::__1::integral_constant.141"*
  %8 = load %"class.std::__1::allocator.134"*, %"class.std::__1::allocator.134"** %3, align 8
  %9 = load %"class.LL2W::Node"**, %"class.LL2W::Node"*** %4, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE9__destroyIS5_EEvNS_17integral_constantIbLb0EEERS8_PT_(%"class.std::__1::allocator.134"* dereferenceable(1) %8, %"class.LL2W::Node"** %9)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"class.LL2W::Node"** @_ZNSt3__122__hash_key_value_typesIPN4LL2W4NodeEE9__get_ptrERS3_(%"class.LL2W::Node"** dereferenceable(8)) #4 align 2 {
  %2 = alloca %"class.LL2W::Node"**, align 8
  store %"class.LL2W::Node"** %0, %"class.LL2W::Node"*** %2, align 8
  %3 = load %"class.LL2W::Node"**, %"class.LL2W::Node"*** %2, align 8
  %4 = call %"class.LL2W::Node"** @_ZNSt3__19addressofIPN4LL2W4NodeEEEPT_RS4_(%"class.LL2W::Node"** dereferenceable(8) %3) #8
  ret %"class.LL2W::Node"** %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE10deallocateERS8_PS7_m(%"class.std::__1::allocator.134"* dereferenceable(1), %"struct.std::__1::__hash_node.143"*, i64) #4 align 2 {
  %4 = alloca %"class.std::__1::allocator.134"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node.143"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.134"* %0, %"class.std::__1::allocator.134"** %4, align 8
  store %"struct.std::__1::__hash_node.143"* %1, %"struct.std::__1::__hash_node.143"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.134"*, %"class.std::__1::allocator.134"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node.143"*, %"struct.std::__1::__hash_node.143"** %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__19allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEE10deallocateEPS6_m(%"class.std::__1::allocator.134"* %7, %"struct.std::__1::__hash_node.143"* %8, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.134"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_9allocatorIS7_EEE6secondEv(%"class.std::__1::__compressed_pair.131"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.131"*, align 8
  store %"class.std::__1::__compressed_pair.131"* %0, %"class.std::__1::__compressed_pair.131"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.131"*, %"class.std::__1::__compressed_pair.131"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.131"* %3 to %"struct.std::__1::__compressed_pair_elem.133"*
  %5 = call dereferenceable(1) %"class.std::__1::allocator.134"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.133"* %4) #8
  ret %"class.std::__1::allocator.134"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.134"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.133"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.133"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.133"* %0, %"struct.std::__1::__compressed_pair_elem.133"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.133"*, %"struct.std::__1::__compressed_pair_elem.133"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.133"* %3 to %"class.std::__1::allocator.134"*
  ret %"class.std::__1::allocator.134"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node_base.124"* @_ZNSt3__114pointer_traitsIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE10pointer_toERS9_(%"struct.std::__1::__hash_node_base.124"* dereferenceable(8)) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_node_base.124"*, align 8
  store %"struct.std::__1::__hash_node_base.124"* %0, %"struct.std::__1::__hash_node_base.124"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.124"*, %"struct.std::__1::__hash_node_base.124"** %2, align 8
  %4 = call %"struct.std::__1::__hash_node_base.124"* @_ZNSt3__19addressofINS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEPT_RSA_(%"struct.std::__1::__hash_node_base.124"* dereferenceable(8) %3) #8
  ret %"struct.std::__1::__hash_node_base.124"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node_base.124"* @_ZNSt3__19addressofINS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEPT_RSA_(%"struct.std::__1::__hash_node_base.124"* dereferenceable(8)) #4 {
  %2 = alloca %"struct.std::__1::__hash_node_base.124"*, align 8
  store %"struct.std::__1::__hash_node_base.124"* %0, %"struct.std::__1::__hash_node_base.124"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.124"*, %"struct.std::__1::__hash_node_base.124"** %2, align 8
  ret %"struct.std::__1::__hash_node_base.124"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE9__destroyIS5_EEvNS_17integral_constantIbLb0EEERS8_PT_(%"class.std::__1::allocator.134"* dereferenceable(1), %"class.LL2W::Node"**) #4 align 2 {
  %3 = alloca %"struct.std::__1::integral_constant.141", align 1
  %4 = alloca %"class.std::__1::allocator.134"*, align 8
  %5 = alloca %"class.LL2W::Node"**, align 8
  store %"class.std::__1::allocator.134"* %0, %"class.std::__1::allocator.134"** %4, align 8
  store %"class.LL2W::Node"** %1, %"class.LL2W::Node"*** %5, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"class.LL2W::Node"** @_ZNSt3__19addressofIPN4LL2W4NodeEEEPT_RS4_(%"class.LL2W::Node"** dereferenceable(8)) #4 {
  %2 = alloca %"class.LL2W::Node"**, align 8
  store %"class.LL2W::Node"** %0, %"class.LL2W::Node"*** %2, align 8
  %3 = load %"class.LL2W::Node"**, %"class.LL2W::Node"*** %2, align 8
  ret %"class.LL2W::Node"** %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorINS_11__hash_nodeIPN4LL2W4NodeEPvEEE10deallocateEPS6_m(%"class.std::__1::allocator.134"*, %"struct.std::__1::__hash_node.143"*, i64) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::allocator.134"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node.143"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.134"* %0, %"class.std::__1::allocator.134"** %4, align 8
  store %"struct.std::__1::__hash_node.143"* %1, %"struct.std::__1::__hash_node.143"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.134"*, %"class.std::__1::allocator.134"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node.143"*, %"struct.std::__1::__hash_node.143"** %5, align 8
  %9 = bitcast %"struct.std::__1::__hash_node.143"* %8 to i8*
  %10 = load i64, i64* %6, align 8
  %11 = mul i64 %10, 24
  invoke void @_ZNSt3__119__libcpp_deallocateEPvmm(i8* %9, i64 %11, i64 8)
          to label %12 unwind label %13

; <label>:12:                                     ; preds = %3
  ret void

; <label>:13:                                     ; preds = %3
  %14 = landingpad { i8*, i32 }
          catch i8* null
  %15 = extractvalue { i8*, i32 } %14, 0
  call void @__clang_call_terminate(i8* %15) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.124"* @_ZNSt3__122__compressed_pair_elemINS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.132"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.132"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.132"* %0, %"struct.std::__1::__compressed_pair_elem.132"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.132"*, %"struct.std::__1::__compressed_pair_elem.132"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.132", %"struct.std::__1::__compressed_pair_elem.132"* %3, i32 0, i32 0
  ret %"struct.std::__1::__hash_node_base.124"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEED2Ev(%"class.std::__1::unique_ptr.121"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.121"*, align 8
  store %"class.std::__1::unique_ptr.121"* %0, %"class.std::__1::unique_ptr.121"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.121"*, %"class.std::__1::unique_ptr.121"** %2, align 8
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEE5resetEDn(%"class.std::__1::unique_ptr.121"* %3, i8* null) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEE5resetEDn(%"class.std::__1::unique_ptr.121"*, i8*) #4 align 2 {
  %3 = alloca %"class.std::__1::unique_ptr.121"*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.124"**, align 8
  store %"class.std::__1::unique_ptr.121"* %0, %"class.std::__1::unique_ptr.121"** %3, align 8
  store i8* %1, i8** %4, align 8
  %6 = load %"class.std::__1::unique_ptr.121"*, %"class.std::__1::unique_ptr.121"** %3, align 8
  %7 = getelementptr inbounds %"class.std::__1::unique_ptr.121", %"class.std::__1::unique_ptr.121"* %6, i32 0, i32 0
  %8 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.124"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEE5firstEv(%"class.std::__1::__compressed_pair.122"* %7) #8
  %9 = load %"struct.std::__1::__hash_node_base.124"**, %"struct.std::__1::__hash_node_base.124"*** %8, align 8
  store %"struct.std::__1::__hash_node_base.124"** %9, %"struct.std::__1::__hash_node_base.124"*** %5, align 8
  %10 = getelementptr inbounds %"class.std::__1::unique_ptr.121", %"class.std::__1::unique_ptr.121"* %6, i32 0, i32 0
  %11 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.124"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEE5firstEv(%"class.std::__1::__compressed_pair.122"* %10) #8
  store %"struct.std::__1::__hash_node_base.124"** null, %"struct.std::__1::__hash_node_base.124"*** %11, align 8
  %12 = load %"struct.std::__1::__hash_node_base.124"**, %"struct.std::__1::__hash_node_base.124"*** %5, align 8
  %13 = icmp ne %"struct.std::__1::__hash_node_base.124"** %12, null
  br i1 %13, label %14, label %18

; <label>:14:                                     ; preds = %2
  %15 = getelementptr inbounds %"class.std::__1::unique_ptr.121", %"class.std::__1::unique_ptr.121"* %6, i32 0, i32 0
  %16 = call dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.126"* @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEE6secondEv(%"class.std::__1::__compressed_pair.122"* %15) #8
  %17 = load %"struct.std::__1::__hash_node_base.124"**, %"struct.std::__1::__hash_node_base.124"*** %5, align 8
  call void @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEEclEPSB_(%"class.std::__1::__bucket_list_deallocator.126"* %16, %"struct.std::__1::__hash_node_base.124"** %17) #8
  br label %18

; <label>:18:                                     ; preds = %14, %2
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.124"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEE5firstEv(%"class.std::__1::__compressed_pair.122"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.122"*, align 8
  store %"class.std::__1::__compressed_pair.122"* %0, %"class.std::__1::__compressed_pair.122"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.122"*, %"class.std::__1::__compressed_pair.122"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.122"* %3 to %"struct.std::__1::__compressed_pair_elem.123"*
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.124"*** @_ZNSt3__122__compressed_pair_elemIPPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.123"* %4) #8
  ret %"struct.std::__1::__hash_node_base.124"*** %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.126"* @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISA_EEEEE6secondEv(%"class.std::__1::__compressed_pair.122"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.122"*, align 8
  store %"class.std::__1::__compressed_pair.122"* %0, %"class.std::__1::__compressed_pair.122"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.122"*, %"class.std::__1::__compressed_pair.122"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.122"* %3 to i8*
  %5 = getelementptr inbounds i8, i8* %4, i64 8
  %6 = bitcast i8* %5 to %"struct.std::__1::__compressed_pair_elem.125"*
  %7 = call dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.126"* @_ZNSt3__122__compressed_pair_elemINS_25__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEEELi1ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.125"* %6) #8
  ret %"class.std::__1::__bucket_list_deallocator.126"* %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEEclEPSB_(%"class.std::__1::__bucket_list_deallocator.126"*, %"struct.std::__1::__hash_node_base.124"**) #4 align 2 {
  %3 = alloca %"class.std::__1::__bucket_list_deallocator.126"*, align 8
  %4 = alloca %"struct.std::__1::__hash_node_base.124"**, align 8
  store %"class.std::__1::__bucket_list_deallocator.126"* %0, %"class.std::__1::__bucket_list_deallocator.126"** %3, align 8
  store %"struct.std::__1::__hash_node_base.124"** %1, %"struct.std::__1::__hash_node_base.124"*** %4, align 8
  %5 = load %"class.std::__1::__bucket_list_deallocator.126"*, %"class.std::__1::__bucket_list_deallocator.126"** %3, align 8
  %6 = call dereferenceable(1) %"class.std::__1::allocator.129"* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE7__allocEv(%"class.std::__1::__bucket_list_deallocator.126"* %5) #8
  %7 = load %"struct.std::__1::__hash_node_base.124"**, %"struct.std::__1::__hash_node_base.124"*** %4, align 8
  %8 = call dereferenceable(8) i64* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE4sizeEv(%"class.std::__1::__bucket_list_deallocator.126"* %5) #8
  %9 = load i64, i64* %8, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE10deallocateERSC_PSB_m(%"class.std::__1::allocator.129"* dereferenceable(1) %6, %"struct.std::__1::__hash_node_base.124"** %7, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.124"*** @_ZNSt3__122__compressed_pair_elemIPPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.123"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.123"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.123"* %0, %"struct.std::__1::__compressed_pair_elem.123"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.123"*, %"struct.std::__1::__compressed_pair_elem.123"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.123", %"struct.std::__1::__compressed_pair_elem.123"* %3, i32 0, i32 0
  ret %"struct.std::__1::__hash_node_base.124"*** %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.126"* @_ZNSt3__122__compressed_pair_elemINS_25__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEEELi1ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.125"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.125"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.125"* %0, %"struct.std::__1::__compressed_pair_elem.125"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.125"*, %"struct.std::__1::__compressed_pair_elem.125"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.125", %"struct.std::__1::__compressed_pair_elem.125"* %3, i32 0, i32 0
  ret %"class.std::__1::__bucket_list_deallocator.126"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__116allocator_traitsINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE10deallocateERSC_PSB_m(%"class.std::__1::allocator.129"* dereferenceable(1), %"struct.std::__1::__hash_node_base.124"**, i64) #4 align 2 {
  %4 = alloca %"class.std::__1::allocator.129"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.124"**, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.129"* %0, %"class.std::__1::allocator.129"** %4, align 8
  store %"struct.std::__1::__hash_node_base.124"** %1, %"struct.std::__1::__hash_node_base.124"*** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.129"*, %"class.std::__1::allocator.129"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node_base.124"**, %"struct.std::__1::__hash_node_base.124"*** %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__19allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE10deallocateEPSA_m(%"class.std::__1::allocator.129"* %7, %"struct.std::__1::__hash_node_base.124"** %8, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.129"* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE7__allocEv(%"class.std::__1::__bucket_list_deallocator.126"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__bucket_list_deallocator.126"*, align 8
  store %"class.std::__1::__bucket_list_deallocator.126"* %0, %"class.std::__1::__bucket_list_deallocator.126"** %2, align 8
  %3 = load %"class.std::__1::__bucket_list_deallocator.126"*, %"class.std::__1::__bucket_list_deallocator.126"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__bucket_list_deallocator.126", %"class.std::__1::__bucket_list_deallocator.126"* %3, i32 0, i32 0
  %5 = call dereferenceable(1) %"class.std::__1::allocator.129"* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE6secondEv(%"class.std::__1::__compressed_pair.127"* %4) #8
  ret %"class.std::__1::allocator.129"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) i64* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE4sizeEv(%"class.std::__1::__bucket_list_deallocator.126"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__bucket_list_deallocator.126"*, align 8
  store %"class.std::__1::__bucket_list_deallocator.126"* %0, %"class.std::__1::__bucket_list_deallocator.126"** %2, align 8
  %3 = load %"class.std::__1::__bucket_list_deallocator.126"*, %"class.std::__1::__bucket_list_deallocator.126"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__bucket_list_deallocator.126", %"class.std::__1::__bucket_list_deallocator.126"* %3, i32 0, i32 0
  %5 = call dereferenceable(8) i64* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE5firstEv(%"class.std::__1::__compressed_pair.127"* %4) #8
  ret i64* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEE10deallocateEPSA_m(%"class.std::__1::allocator.129"*, %"struct.std::__1::__hash_node_base.124"**, i64) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::allocator.129"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.124"**, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.129"* %0, %"class.std::__1::allocator.129"** %4, align 8
  store %"struct.std::__1::__hash_node_base.124"** %1, %"struct.std::__1::__hash_node_base.124"*** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.129"*, %"class.std::__1::allocator.129"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node_base.124"**, %"struct.std::__1::__hash_node_base.124"*** %5, align 8
  %9 = bitcast %"struct.std::__1::__hash_node_base.124"** %8 to i8*
  %10 = load i64, i64* %6, align 8
  %11 = mul i64 %10, 8
  invoke void @_ZNSt3__119__libcpp_deallocateEPvmm(i8* %9, i64 %11, i64 8)
          to label %12 unwind label %13

; <label>:12:                                     ; preds = %3
  ret void

; <label>:13:                                     ; preds = %3
  %14 = landingpad { i8*, i32 }
          catch i8* null
  %15 = extractvalue { i8*, i32 } %14, 0
  call void @__clang_call_terminate(i8* %15) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.129"* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE6secondEv(%"class.std::__1::__compressed_pair.127"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.127"*, align 8
  store %"class.std::__1::__compressed_pair.127"* %0, %"class.std::__1::__compressed_pair.127"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.127"*, %"class.std::__1::__compressed_pair.127"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.127"* %3 to %"struct.std::__1::__compressed_pair_elem.128"*
  %5 = call dereferenceable(1) %"class.std::__1::allocator.129"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.128"* %4) #8
  ret %"class.std::__1::allocator.129"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.129"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.128"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.128"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.128"* %0, %"struct.std::__1::__compressed_pair_elem.128"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.128"*, %"struct.std::__1::__compressed_pair_elem.128"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.128"* %3 to %"class.std::__1::allocator.129"*
  ret %"class.std::__1::allocator.129"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) i64* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeIPN4LL2W4NodeEPvEEEEEEE5firstEv(%"class.std::__1::__compressed_pair.127"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.127"*, align 8
  store %"class.std::__1::__compressed_pair.127"* %0, %"class.std::__1::__compressed_pair.127"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.127"*, %"class.std::__1::__compressed_pair.127"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.127"* %3 to %"struct.std::__1::__compressed_pair_elem"*
  %5 = call dereferenceable(8) i64* @_ZNSt3__122__compressed_pair_elemImLi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem"* %4) #8
  ret i64* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) i64* @_ZNSt3__122__compressed_pair_elemImLi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem"*, align 8
  store %"struct.std::__1::__compressed_pair_elem"* %0, %"struct.std::__1::__compressed_pair_elem"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem"*, %"struct.std::__1::__compressed_pair_elem"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem", %"struct.std::__1::__compressed_pair_elem"* %3, i32 0, i32 0
  ret i64* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair.119"* @_ZNSt3__19addressofINS_4pairIKPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEEEEPT_RSF_(%"struct.std::__1::pair.119"* dereferenceable(48)) #4 {
  %2 = alloca %"struct.std::__1::pair.119"*, align 8
  store %"struct.std::__1::pair.119"* %0, %"struct.std::__1::pair.119"** %2, align 8
  %3 = load %"struct.std::__1::pair.119"*, %"struct.std::__1::pair.119"** %2, align 8
  ret %"struct.std::__1::pair.119"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(48) %"struct.std::__1::pair.119"* @_ZNSt3__117__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorIS3_EEEEE11__get_valueEv(%"struct.std::__1::__hash_value_type"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_value_type"*, align 8
  store %"struct.std::__1::__hash_value_type"* %0, %"struct.std::__1::__hash_value_type"** %2, align 8
  %3 = load %"struct.std::__1::__hash_value_type"*, %"struct.std::__1::__hash_value_type"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__hash_value_type", %"struct.std::__1::__hash_value_type"* %3, i32 0, i32 0
  %5 = call %"struct.std::__1::pair.119"* @_ZNSt3__19addressofINS_4pairIKPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEEEEPT_RSF_(%"struct.std::__1::pair.119"* dereferenceable(48) %4) #8
  %6 = call %"struct.std::__1::pair.119"* @_ZNSt3__17launderINS_4pairIKPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEEEEPT_SG_(%"struct.std::__1::pair.119"* %5) #8
  ret %"struct.std::__1::pair.119"* %6
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair.119"* @_ZNSt3__17launderINS_4pairIKPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEEEEPT_SG_(%"struct.std::__1::pair.119"*) #4 {
  %2 = alloca %"struct.std::__1::pair.119"*, align 8
  store %"struct.std::__1::pair.119"* %0, %"struct.std::__1::pair.119"** %2, align 8
  %3 = load %"struct.std::__1::pair.119"*, %"struct.std::__1::pair.119"** %2, align 8
  %4 = call %"struct.std::__1::pair.119"* @_ZNSt3__19__launderINS_4pairIKPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEEEEPT_SG_(%"struct.std::__1::pair.119"* %3) #8
  ret %"struct.std::__1::pair.119"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"struct.std::__1::pair.119"* @_ZNSt3__19__launderINS_4pairIKPN4LL2W4NodeENS_13unordered_setIS4_NS_4hashIS4_EENS_8equal_toIS4_EENS_9allocatorIS4_EEEEEEEEPT_SG_(%"struct.std::__1::pair.119"*) #4 {
  %2 = alloca %"struct.std::__1::pair.119"*, align 8
  store %"struct.std::__1::pair.119"* %0, %"struct.std::__1::pair.119"** %2, align 8
  %3 = load %"struct.std::__1::pair.119"*, %"struct.std::__1::pair.119"** %2, align 8
  ret %"struct.std::__1::pair.119"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS5_NS_4hashIS5_EENS_8equal_toIS5_EENS0_IS5_EEEEEEPvEEE10deallocateEPSF_m(%"class.std::__1::allocator.46"*, %"struct.std::__1::__hash_node"*, i64) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::allocator.46"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.46"* %0, %"class.std::__1::allocator.46"** %4, align 8
  store %"struct.std::__1::__hash_node"* %1, %"struct.std::__1::__hash_node"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.46"*, %"class.std::__1::allocator.46"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node"*, %"struct.std::__1::__hash_node"** %5, align 8
  %9 = bitcast %"struct.std::__1::__hash_node"* %8 to i8*
  %10 = load i64, i64* %6, align 8
  %11 = mul i64 %10, 64
  invoke void @_ZNSt3__119__libcpp_deallocateEPvmm(i8* %9, i64 %11, i64 8)
          to label %12 unwind label %13

; <label>:12:                                     ; preds = %3
  ret void

; <label>:13:                                     ; preds = %3
  %14 = landingpad { i8*, i32 }
          catch i8* null
  %15 = extractvalue { i8*, i32 } %14, 0
  call void @__clang_call_terminate(i8* %15) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.36"* @_ZNSt3__122__compressed_pair_elemINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.44"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.44"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.44"* %0, %"struct.std::__1::__compressed_pair_elem.44"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.44"*, %"struct.std::__1::__compressed_pair_elem.44"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.44", %"struct.std::__1::__compressed_pair_elem.44"* %3, i32 0, i32 0
  ret %"struct.std::__1::__hash_node_base.36"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEED2Ev(%"class.std::__1::unique_ptr.33"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.33"*, align 8
  store %"class.std::__1::unique_ptr.33"* %0, %"class.std::__1::unique_ptr.33"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.33"*, %"class.std::__1::unique_ptr.33"** %2, align 8
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEE5resetEDn(%"class.std::__1::unique_ptr.33"* %3, i8* null) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEE5resetEDn(%"class.std::__1::unique_ptr.33"*, i8*) #4 align 2 {
  %3 = alloca %"class.std::__1::unique_ptr.33"*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.36"**, align 8
  store %"class.std::__1::unique_ptr.33"* %0, %"class.std::__1::unique_ptr.33"** %3, align 8
  store i8* %1, i8** %4, align 8
  %6 = load %"class.std::__1::unique_ptr.33"*, %"class.std::__1::unique_ptr.33"** %3, align 8
  %7 = getelementptr inbounds %"class.std::__1::unique_ptr.33", %"class.std::__1::unique_ptr.33"* %6, i32 0, i32 0
  %8 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.36"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEE5firstEv(%"class.std::__1::__compressed_pair.34"* %7) #8
  %9 = load %"struct.std::__1::__hash_node_base.36"**, %"struct.std::__1::__hash_node_base.36"*** %8, align 8
  store %"struct.std::__1::__hash_node_base.36"** %9, %"struct.std::__1::__hash_node_base.36"*** %5, align 8
  %10 = getelementptr inbounds %"class.std::__1::unique_ptr.33", %"class.std::__1::unique_ptr.33"* %6, i32 0, i32 0
  %11 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.36"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEE5firstEv(%"class.std::__1::__compressed_pair.34"* %10) #8
  store %"struct.std::__1::__hash_node_base.36"** null, %"struct.std::__1::__hash_node_base.36"*** %11, align 8
  %12 = load %"struct.std::__1::__hash_node_base.36"**, %"struct.std::__1::__hash_node_base.36"*** %5, align 8
  %13 = icmp ne %"struct.std::__1::__hash_node_base.36"** %12, null
  br i1 %13, label %14, label %18

; <label>:14:                                     ; preds = %2
  %15 = getelementptr inbounds %"class.std::__1::unique_ptr.33", %"class.std::__1::unique_ptr.33"* %6, i32 0, i32 0
  %16 = call dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.38"* @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEE6secondEv(%"class.std::__1::__compressed_pair.34"* %15) #8
  %17 = load %"struct.std::__1::__hash_node_base.36"**, %"struct.std::__1::__hash_node_base.36"*** %5, align 8
  call void @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEEclEPSK_(%"class.std::__1::__bucket_list_deallocator.38"* %16, %"struct.std::__1::__hash_node_base.36"** %17) #8
  br label %18

; <label>:18:                                     ; preds = %14, %2
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.36"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEE5firstEv(%"class.std::__1::__compressed_pair.34"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.34"*, align 8
  store %"class.std::__1::__compressed_pair.34"* %0, %"class.std::__1::__compressed_pair.34"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.34"*, %"class.std::__1::__compressed_pair.34"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.34"* %3 to %"struct.std::__1::__compressed_pair_elem.35"*
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.36"*** @_ZNSt3__122__compressed_pair_elemIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.35"* %4) #8
  ret %"struct.std::__1::__hash_node_base.36"*** %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.38"* @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEENS_25__bucket_list_deallocatorINSC_ISK_EEEEE6secondEv(%"class.std::__1::__compressed_pair.34"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.34"*, align 8
  store %"class.std::__1::__compressed_pair.34"* %0, %"class.std::__1::__compressed_pair.34"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.34"*, %"class.std::__1::__compressed_pair.34"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.34"* %3 to i8*
  %5 = getelementptr inbounds i8, i8* %4, i64 8
  %6 = bitcast i8* %5 to %"struct.std::__1::__compressed_pair_elem.37"*
  %7 = call dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.38"* @_ZNSt3__122__compressed_pair_elemINS_25__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS8_NS_4hashIS8_EENS_8equal_toIS8_EENS2_IS8_EEEEEEPvEEEEEEEELi1ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.37"* %6) #8
  ret %"class.std::__1::__bucket_list_deallocator.38"* %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEEclEPSK_(%"class.std::__1::__bucket_list_deallocator.38"*, %"struct.std::__1::__hash_node_base.36"**) #4 align 2 {
  %3 = alloca %"class.std::__1::__bucket_list_deallocator.38"*, align 8
  %4 = alloca %"struct.std::__1::__hash_node_base.36"**, align 8
  store %"class.std::__1::__bucket_list_deallocator.38"* %0, %"class.std::__1::__bucket_list_deallocator.38"** %3, align 8
  store %"struct.std::__1::__hash_node_base.36"** %1, %"struct.std::__1::__hash_node_base.36"*** %4, align 8
  %5 = load %"class.std::__1::__bucket_list_deallocator.38"*, %"class.std::__1::__bucket_list_deallocator.38"** %3, align 8
  %6 = call dereferenceable(1) %"class.std::__1::allocator.41"* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE7__allocEv(%"class.std::__1::__bucket_list_deallocator.38"* %5) #8
  %7 = load %"struct.std::__1::__hash_node_base.36"**, %"struct.std::__1::__hash_node_base.36"*** %4, align 8
  %8 = call dereferenceable(8) i64* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE4sizeEv(%"class.std::__1::__bucket_list_deallocator.38"* %5) #8
  %9 = load i64, i64* %8, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE10deallocateERSL_PSK_m(%"class.std::__1::allocator.41"* dereferenceable(1) %6, %"struct.std::__1::__hash_node_base.36"** %7, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.36"*** @_ZNSt3__122__compressed_pair_elemIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS_9allocatorIS6_EEEEEEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.35"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.35"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.35"* %0, %"struct.std::__1::__compressed_pair_elem.35"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.35"*, %"struct.std::__1::__compressed_pair_elem.35"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.35", %"struct.std::__1::__compressed_pair_elem.35"* %3, i32 0, i32 0
  ret %"struct.std::__1::__hash_node_base.36"*** %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.38"* @_ZNSt3__122__compressed_pair_elemINS_25__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS8_NS_4hashIS8_EENS_8equal_toIS8_EENS2_IS8_EEEEEEPvEEEEEEEELi1ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.37"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.37"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.37"* %0, %"struct.std::__1::__compressed_pair_elem.37"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.37"*, %"struct.std::__1::__compressed_pair_elem.37"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.37", %"struct.std::__1::__compressed_pair_elem.37"* %3, i32 0, i32 0
  ret %"class.std::__1::__bucket_list_deallocator.38"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__116allocator_traitsINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE10deallocateERSL_PSK_m(%"class.std::__1::allocator.41"* dereferenceable(1), %"struct.std::__1::__hash_node_base.36"**, i64) #4 align 2 {
  %4 = alloca %"class.std::__1::allocator.41"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.36"**, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.41"* %0, %"class.std::__1::allocator.41"** %4, align 8
  store %"struct.std::__1::__hash_node_base.36"** %1, %"struct.std::__1::__hash_node_base.36"*** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.41"*, %"class.std::__1::allocator.41"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node_base.36"**, %"struct.std::__1::__hash_node_base.36"*** %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__19allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS0_IS6_EEEEEEPvEEEEE10deallocateEPSJ_m(%"class.std::__1::allocator.41"* %7, %"struct.std::__1::__hash_node_base.36"** %8, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.41"* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE7__allocEv(%"class.std::__1::__bucket_list_deallocator.38"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__bucket_list_deallocator.38"*, align 8
  store %"class.std::__1::__bucket_list_deallocator.38"* %0, %"class.std::__1::__bucket_list_deallocator.38"** %2, align 8
  %3 = load %"class.std::__1::__bucket_list_deallocator.38"*, %"class.std::__1::__bucket_list_deallocator.38"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__bucket_list_deallocator.38", %"class.std::__1::__bucket_list_deallocator.38"* %3, i32 0, i32 0
  %5 = call dereferenceable(1) %"class.std::__1::allocator.41"* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE6secondEv(%"class.std::__1::__compressed_pair.39"* %4) #8
  ret %"class.std::__1::allocator.41"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) i64* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE4sizeEv(%"class.std::__1::__bucket_list_deallocator.38"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__bucket_list_deallocator.38"*, align 8
  store %"class.std::__1::__bucket_list_deallocator.38"* %0, %"class.std::__1::__bucket_list_deallocator.38"** %2, align 8
  %3 = load %"class.std::__1::__bucket_list_deallocator.38"*, %"class.std::__1::__bucket_list_deallocator.38"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__bucket_list_deallocator.38", %"class.std::__1::__bucket_list_deallocator.38"* %3, i32 0, i32 0
  %5 = call dereferenceable(8) i64* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE5firstEv(%"class.std::__1::__compressed_pair.39"* %4) #8
  ret i64* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS6_NS_4hashIS6_EENS_8equal_toIS6_EENS0_IS6_EEEEEEPvEEEEE10deallocateEPSJ_m(%"class.std::__1::allocator.41"*, %"struct.std::__1::__hash_node_base.36"**, i64) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::allocator.41"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.36"**, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.41"* %0, %"class.std::__1::allocator.41"** %4, align 8
  store %"struct.std::__1::__hash_node_base.36"** %1, %"struct.std::__1::__hash_node_base.36"*** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.41"*, %"class.std::__1::allocator.41"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node_base.36"**, %"struct.std::__1::__hash_node_base.36"*** %5, align 8
  %9 = bitcast %"struct.std::__1::__hash_node_base.36"** %8 to i8*
  %10 = load i64, i64* %6, align 8
  %11 = mul i64 %10, 8
  invoke void @_ZNSt3__119__libcpp_deallocateEPvmm(i8* %9, i64 %11, i64 8)
          to label %12 unwind label %13

; <label>:12:                                     ; preds = %3
  ret void

; <label>:13:                                     ; preds = %3
  %14 = landingpad { i8*, i32 }
          catch i8* null
  %15 = extractvalue { i8*, i32 } %14, 0
  call void @__clang_call_terminate(i8* %15) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.41"* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE6secondEv(%"class.std::__1::__compressed_pair.39"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.39"*, align 8
  store %"class.std::__1::__compressed_pair.39"* %0, %"class.std::__1::__compressed_pair.39"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.39"*, %"class.std::__1::__compressed_pair.39"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.39"* %3 to %"struct.std::__1::__compressed_pair_elem.40"*
  %5 = call dereferenceable(1) %"class.std::__1::allocator.41"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.40"* %4) #8
  ret %"class.std::__1::allocator.41"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.41"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.40"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.40"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.40"* %0, %"struct.std::__1::__compressed_pair_elem.40"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.40"*, %"struct.std::__1::__compressed_pair_elem.40"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.40"* %3 to %"class.std::__1::allocator.41"*
  ret %"class.std::__1::allocator.41"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) i64* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeENS_13unordered_setIS7_NS_4hashIS7_EENS_8equal_toIS7_EENS1_IS7_EEEEEEPvEEEEEEE5firstEv(%"class.std::__1::__compressed_pair.39"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.39"*, align 8
  store %"class.std::__1::__compressed_pair.39"* %0, %"class.std::__1::__compressed_pair.39"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.39"*, %"class.std::__1::__compressed_pair.39"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.39"* %3 to %"struct.std::__1::__compressed_pair_elem"*
  %5 = call dereferenceable(8) i64* @_ZNSt3__122__compressed_pair_elemImLi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem"* %4) #8
  ret i64* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZN4LL2W9DFSResultD2Ev(%"struct.LL2W::DFSResult"*) unnamed_addr #4 align 2 {
  %2 = alloca %"struct.LL2W::DFSResult"*, align 8
  store %"struct.LL2W::DFSResult"* %0, %"struct.LL2W::DFSResult"** %2, align 8
  %3 = load %"struct.LL2W::DFSResult"*, %"struct.LL2W::DFSResult"** %2, align 8
  %4 = getelementptr inbounds %"struct.LL2W::DFSResult", %"struct.LL2W::DFSResult"* %3, i32 0, i32 3
  call void @_ZNSt3__113unordered_mapIPN4LL2W4NodeEiNS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorINS_4pairIKS3_iEEEEED1Ev(%"class.std::__1::unordered_map.88"* %4) #8
  %5 = getelementptr inbounds %"struct.LL2W::DFSResult", %"struct.LL2W::DFSResult"* %3, i32 0, i32 2
  call void @_ZNSt3__113unordered_mapIPN4LL2W4NodeEiNS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorINS_4pairIKS3_iEEEEED1Ev(%"class.std::__1::unordered_map.88"* %5) #8
  %6 = getelementptr inbounds %"struct.LL2W::DFSResult", %"struct.LL2W::DFSResult"* %3, i32 0, i32 1
  call void @_ZNSt3__113unordered_mapIPN4LL2W4NodeES3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorINS_4pairIKS3_S3_EEEEED1Ev(%"class.std::__1::unordered_map.64"* %6) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__113unordered_mapIPN4LL2W4NodeEiNS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorINS_4pairIKS3_iEEEEED1Ev(%"class.std::__1::unordered_map.88"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unordered_map.88"*, align 8
  store %"class.std::__1::unordered_map.88"* %0, %"class.std::__1::unordered_map.88"** %2, align 8
  %3 = load %"class.std::__1::unordered_map.88"*, %"class.std::__1::unordered_map.88"** %2, align 8
  call void @_ZNSt3__113unordered_mapIPN4LL2W4NodeEiNS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorINS_4pairIKS3_iEEEEED2Ev(%"class.std::__1::unordered_map.88"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__113unordered_mapIPN4LL2W4NodeES3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorINS_4pairIKS3_S3_EEEEED1Ev(%"class.std::__1::unordered_map.64"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unordered_map.64"*, align 8
  store %"class.std::__1::unordered_map.64"* %0, %"class.std::__1::unordered_map.64"** %2, align 8
  %3 = load %"class.std::__1::unordered_map.64"*, %"class.std::__1::unordered_map.64"** %2, align 8
  call void @_ZNSt3__113unordered_mapIPN4LL2W4NodeES3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorINS_4pairIKS3_S3_EEEEED2Ev(%"class.std::__1::unordered_map.64"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__113unordered_mapIPN4LL2W4NodeEiNS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorINS_4pairIKS3_iEEEEED2Ev(%"class.std::__1::unordered_map.88"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unordered_map.88"*, align 8
  store %"class.std::__1::unordered_map.88"* %0, %"class.std::__1::unordered_map.88"** %2, align 8
  %3 = load %"class.std::__1::unordered_map.88"*, %"class.std::__1::unordered_map.88"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::unordered_map.88", %"class.std::__1::unordered_map.88"* %3, i32 0, i32 0
  call void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeEiEENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEED1Ev(%"class.std::__1::__hash_table.89"* %4) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeEiEENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEED1Ev(%"class.std::__1::__hash_table.89"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.89"*, align 8
  store %"class.std::__1::__hash_table.89"* %0, %"class.std::__1::__hash_table.89"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.89"*, %"class.std::__1::__hash_table.89"** %2, align 8
  call void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeEiEENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEED2Ev(%"class.std::__1::__hash_table.89"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeEiEENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEED2Ev(%"class.std::__1::__hash_table.89"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.89"*, align 8
  store %"class.std::__1::__hash_table.89"* %0, %"class.std::__1::__hash_table.89"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.89"*, %"class.std::__1::__hash_table.89"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__hash_table.89", %"class.std::__1::__hash_table.89"* %3, i32 0, i32 1
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.93"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_9allocatorIS9_EEE5firstEv(%"class.std::__1::__compressed_pair.100"* %4) #8
  %6 = getelementptr inbounds %"struct.std::__1::__hash_node_base.93", %"struct.std::__1::__hash_node_base.93"* %5, i32 0, i32 0
  %7 = load %"struct.std::__1::__hash_node_base.93"*, %"struct.std::__1::__hash_node_base.93"** %6, align 8
  call void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeEiEENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEE17__deallocate_nodeEPNS_16__hash_node_baseIPNS_11__hash_nodeIS5_PvEEEE(%"class.std::__1::__hash_table.89"* %3, %"struct.std::__1::__hash_node_base.93"* %7) #8
  %8 = getelementptr inbounds %"class.std::__1::__hash_table.89", %"class.std::__1::__hash_table.89"* %3, i32 0, i32 0
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEED1Ev(%"class.std::__1::unique_ptr.90"* %8) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeEiEENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEE17__deallocate_nodeEPNS_16__hash_node_baseIPNS_11__hash_nodeIS5_PvEEEE(%"class.std::__1::__hash_table.89"*, %"struct.std::__1::__hash_node_base.93"*) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::__1::__hash_table.89"*, align 8
  %4 = alloca %"struct.std::__1::__hash_node_base.93"*, align 8
  %5 = alloca %"class.std::__1::allocator.103"*, align 8
  %6 = alloca %"struct.std::__1::__hash_node_base.93"*, align 8
  %7 = alloca %"struct.std::__1::__hash_node.145"*, align 8
  store %"class.std::__1::__hash_table.89"* %0, %"class.std::__1::__hash_table.89"** %3, align 8
  store %"struct.std::__1::__hash_node_base.93"* %1, %"struct.std::__1::__hash_node_base.93"** %4, align 8
  %8 = load %"class.std::__1::__hash_table.89"*, %"class.std::__1::__hash_table.89"** %3, align 8
  %9 = call dereferenceable(1) %"class.std::__1::allocator.103"* @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeEiEENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEE12__node_allocEv(%"class.std::__1::__hash_table.89"* %8) #8
  store %"class.std::__1::allocator.103"* %9, %"class.std::__1::allocator.103"** %5, align 8
  br label %10

; <label>:10:                                     ; preds = %24, %2
  %11 = load %"struct.std::__1::__hash_node_base.93"*, %"struct.std::__1::__hash_node_base.93"** %4, align 8
  %12 = icmp ne %"struct.std::__1::__hash_node_base.93"* %11, null
  br i1 %12, label %13, label %28

; <label>:13:                                     ; preds = %10
  %14 = load %"struct.std::__1::__hash_node_base.93"*, %"struct.std::__1::__hash_node_base.93"** %4, align 8
  %15 = getelementptr inbounds %"struct.std::__1::__hash_node_base.93", %"struct.std::__1::__hash_node_base.93"* %14, i32 0, i32 0
  %16 = load %"struct.std::__1::__hash_node_base.93"*, %"struct.std::__1::__hash_node_base.93"** %15, align 8
  store %"struct.std::__1::__hash_node_base.93"* %16, %"struct.std::__1::__hash_node_base.93"** %6, align 8
  %17 = load %"struct.std::__1::__hash_node_base.93"*, %"struct.std::__1::__hash_node_base.93"** %4, align 8
  %18 = call %"struct.std::__1::__hash_node.145"* @_ZNSt3__116__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEE8__upcastEv(%"struct.std::__1::__hash_node_base.93"* %17) #8
  store %"struct.std::__1::__hash_node.145"* %18, %"struct.std::__1::__hash_node.145"** %7, align 8
  %19 = load %"class.std::__1::allocator.103"*, %"class.std::__1::allocator.103"** %5, align 8
  %20 = load %"struct.std::__1::__hash_node.145"*, %"struct.std::__1::__hash_node.145"** %7, align 8
  %21 = getelementptr inbounds %"struct.std::__1::__hash_node.145", %"struct.std::__1::__hash_node.145"* %20, i32 0, i32 2
  %22 = invoke %"struct.std::__1::pair.147"* @_ZNSt3__122__hash_key_value_typesINS_17__hash_value_typeIPN4LL2W4NodeEiEEE9__get_ptrERS5_(%"struct.std::__1::__hash_value_type.146"* dereferenceable(16) %21)
          to label %23 unwind label %29

; <label>:23:                                     ; preds = %13
  invoke void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE7destroyINS_4pairIKS6_iEEEEvRSA_PT_(%"class.std::__1::allocator.103"* dereferenceable(1) %19, %"struct.std::__1::pair.147"* %22)
          to label %24 unwind label %29

; <label>:24:                                     ; preds = %23
  %25 = load %"class.std::__1::allocator.103"*, %"class.std::__1::allocator.103"** %5, align 8
  %26 = load %"struct.std::__1::__hash_node.145"*, %"struct.std::__1::__hash_node.145"** %7, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE10deallocateERSA_PS9_m(%"class.std::__1::allocator.103"* dereferenceable(1) %25, %"struct.std::__1::__hash_node.145"* %26, i64 1) #8
  %27 = load %"struct.std::__1::__hash_node_base.93"*, %"struct.std::__1::__hash_node_base.93"** %6, align 8
  store %"struct.std::__1::__hash_node_base.93"* %27, %"struct.std::__1::__hash_node_base.93"** %4, align 8
  br label %10

; <label>:28:                                     ; preds = %10
  ret void

; <label>:29:                                     ; preds = %23, %13
  %30 = landingpad { i8*, i32 }
          catch i8* null
  %31 = extractvalue { i8*, i32 } %30, 0
  call void @__clang_call_terminate(i8* %31) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.93"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_9allocatorIS9_EEE5firstEv(%"class.std::__1::__compressed_pair.100"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.100"*, align 8
  store %"class.std::__1::__compressed_pair.100"* %0, %"class.std::__1::__compressed_pair.100"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.100"*, %"class.std::__1::__compressed_pair.100"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.100"* %3 to %"struct.std::__1::__compressed_pair_elem.101"*
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.93"* @_ZNSt3__122__compressed_pair_elemINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.101"* %4) #8
  ret %"struct.std::__1::__hash_node_base.93"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEED1Ev(%"class.std::__1::unique_ptr.90"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.90"*, align 8
  store %"class.std::__1::unique_ptr.90"* %0, %"class.std::__1::unique_ptr.90"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.90"*, %"class.std::__1::unique_ptr.90"** %2, align 8
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEED2Ev(%"class.std::__1::unique_ptr.90"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.103"* @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeEiEENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEE12__node_allocEv(%"class.std::__1::__hash_table.89"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.89"*, align 8
  store %"class.std::__1::__hash_table.89"* %0, %"class.std::__1::__hash_table.89"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.89"*, %"class.std::__1::__hash_table.89"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__hash_table.89", %"class.std::__1::__hash_table.89"* %3, i32 0, i32 1
  %5 = call dereferenceable(1) %"class.std::__1::allocator.103"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_9allocatorIS9_EEE6secondEv(%"class.std::__1::__compressed_pair.100"* %4) #8
  ret %"class.std::__1::allocator.103"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node.145"* @_ZNSt3__116__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEE8__upcastEv(%"struct.std::__1::__hash_node_base.93"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_node_base.93"*, align 8
  store %"struct.std::__1::__hash_node_base.93"* %0, %"struct.std::__1::__hash_node_base.93"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.93"*, %"struct.std::__1::__hash_node_base.93"** %2, align 8
  %4 = call %"struct.std::__1::__hash_node_base.93"* @_ZNSt3__114pointer_traitsIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE10pointer_toERSB_(%"struct.std::__1::__hash_node_base.93"* dereferenceable(8) %3) #8
  %5 = bitcast %"struct.std::__1::__hash_node_base.93"* %4 to %"struct.std::__1::__hash_node.145"*
  ret %"struct.std::__1::__hash_node.145"* %5
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE7destroyINS_4pairIKS6_iEEEEvRSA_PT_(%"class.std::__1::allocator.103"* dereferenceable(1), %"struct.std::__1::pair.147"*) #1 align 2 {
  %3 = alloca %"class.std::__1::allocator.103"*, align 8
  %4 = alloca %"struct.std::__1::pair.147"*, align 8
  %5 = alloca %"struct.std::__1::integral_constant.141", align 1
  %6 = alloca %"struct.std::__1::__has_destroy.148", align 1
  store %"class.std::__1::allocator.103"* %0, %"class.std::__1::allocator.103"** %3, align 8
  store %"struct.std::__1::pair.147"* %1, %"struct.std::__1::pair.147"** %4, align 8
  %7 = bitcast %"struct.std::__1::__has_destroy.148"* %6 to %"struct.std::__1::integral_constant.141"*
  %8 = load %"class.std::__1::allocator.103"*, %"class.std::__1::allocator.103"** %3, align 8
  %9 = load %"struct.std::__1::pair.147"*, %"struct.std::__1::pair.147"** %4, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE9__destroyINS_4pairIKS6_iEEEEvNS_17integral_constantIbLb0EEERSA_PT_(%"class.std::__1::allocator.103"* dereferenceable(1) %8, %"struct.std::__1::pair.147"* %9)
  ret void
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair.147"* @_ZNSt3__122__hash_key_value_typesINS_17__hash_value_typeIPN4LL2W4NodeEiEEE9__get_ptrERS5_(%"struct.std::__1::__hash_value_type.146"* dereferenceable(16)) #1 align 2 {
  %2 = alloca %"struct.std::__1::__hash_value_type.146"*, align 8
  store %"struct.std::__1::__hash_value_type.146"* %0, %"struct.std::__1::__hash_value_type.146"** %2, align 8
  %3 = load %"struct.std::__1::__hash_value_type.146"*, %"struct.std::__1::__hash_value_type.146"** %2, align 8
  %4 = call dereferenceable(16) %"struct.std::__1::pair.147"* @_ZNSt3__117__hash_value_typeIPN4LL2W4NodeEiE11__get_valueEv(%"struct.std::__1::__hash_value_type.146"* %3)
  %5 = call %"struct.std::__1::pair.147"* @_ZNSt3__19addressofINS_4pairIKPN4LL2W4NodeEiEEEEPT_RS7_(%"struct.std::__1::pair.147"* dereferenceable(16) %4) #8
  ret %"struct.std::__1::pair.147"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE10deallocateERSA_PS9_m(%"class.std::__1::allocator.103"* dereferenceable(1), %"struct.std::__1::__hash_node.145"*, i64) #4 align 2 {
  %4 = alloca %"class.std::__1::allocator.103"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node.145"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.103"* %0, %"class.std::__1::allocator.103"** %4, align 8
  store %"struct.std::__1::__hash_node.145"* %1, %"struct.std::__1::__hash_node.145"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.103"*, %"class.std::__1::allocator.103"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node.145"*, %"struct.std::__1::__hash_node.145"** %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__19allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEE10deallocateEPS8_m(%"class.std::__1::allocator.103"* %7, %"struct.std::__1::__hash_node.145"* %8, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.103"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_9allocatorIS9_EEE6secondEv(%"class.std::__1::__compressed_pair.100"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.100"*, align 8
  store %"class.std::__1::__compressed_pair.100"* %0, %"class.std::__1::__compressed_pair.100"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.100"*, %"class.std::__1::__compressed_pair.100"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.100"* %3 to %"struct.std::__1::__compressed_pair_elem.102"*
  %5 = call dereferenceable(1) %"class.std::__1::allocator.103"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.102"* %4) #8
  ret %"class.std::__1::allocator.103"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.103"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.102"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.102"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.102"* %0, %"struct.std::__1::__compressed_pair_elem.102"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.102"*, %"struct.std::__1::__compressed_pair_elem.102"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.102"* %3 to %"class.std::__1::allocator.103"*
  ret %"class.std::__1::allocator.103"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node_base.93"* @_ZNSt3__114pointer_traitsIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE10pointer_toERSB_(%"struct.std::__1::__hash_node_base.93"* dereferenceable(8)) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_node_base.93"*, align 8
  store %"struct.std::__1::__hash_node_base.93"* %0, %"struct.std::__1::__hash_node_base.93"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.93"*, %"struct.std::__1::__hash_node_base.93"** %2, align 8
  %4 = call %"struct.std::__1::__hash_node_base.93"* @_ZNSt3__19addressofINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEPT_RSC_(%"struct.std::__1::__hash_node_base.93"* dereferenceable(8) %3) #8
  ret %"struct.std::__1::__hash_node_base.93"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node_base.93"* @_ZNSt3__19addressofINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEPT_RSC_(%"struct.std::__1::__hash_node_base.93"* dereferenceable(8)) #4 {
  %2 = alloca %"struct.std::__1::__hash_node_base.93"*, align 8
  store %"struct.std::__1::__hash_node_base.93"* %0, %"struct.std::__1::__hash_node_base.93"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.93"*, %"struct.std::__1::__hash_node_base.93"** %2, align 8
  ret %"struct.std::__1::__hash_node_base.93"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE9__destroyINS_4pairIKS6_iEEEEvNS_17integral_constantIbLb0EEERSA_PT_(%"class.std::__1::allocator.103"* dereferenceable(1), %"struct.std::__1::pair.147"*) #4 align 2 {
  %3 = alloca %"struct.std::__1::integral_constant.141", align 1
  %4 = alloca %"class.std::__1::allocator.103"*, align 8
  %5 = alloca %"struct.std::__1::pair.147"*, align 8
  store %"class.std::__1::allocator.103"* %0, %"class.std::__1::allocator.103"** %4, align 8
  store %"struct.std::__1::pair.147"* %1, %"struct.std::__1::pair.147"** %5, align 8
  %6 = load %"struct.std::__1::pair.147"*, %"struct.std::__1::pair.147"** %5, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair.147"* @_ZNSt3__19addressofINS_4pairIKPN4LL2W4NodeEiEEEEPT_RS7_(%"struct.std::__1::pair.147"* dereferenceable(16)) #4 {
  %2 = alloca %"struct.std::__1::pair.147"*, align 8
  store %"struct.std::__1::pair.147"* %0, %"struct.std::__1::pair.147"** %2, align 8
  %3 = load %"struct.std::__1::pair.147"*, %"struct.std::__1::pair.147"** %2, align 8
  ret %"struct.std::__1::pair.147"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(16) %"struct.std::__1::pair.147"* @_ZNSt3__117__hash_value_typeIPN4LL2W4NodeEiE11__get_valueEv(%"struct.std::__1::__hash_value_type.146"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_value_type.146"*, align 8
  store %"struct.std::__1::__hash_value_type.146"* %0, %"struct.std::__1::__hash_value_type.146"** %2, align 8
  %3 = load %"struct.std::__1::__hash_value_type.146"*, %"struct.std::__1::__hash_value_type.146"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__hash_value_type.146", %"struct.std::__1::__hash_value_type.146"* %3, i32 0, i32 0
  %5 = call %"struct.std::__1::pair.147"* @_ZNSt3__19addressofINS_4pairIKPN4LL2W4NodeEiEEEEPT_RS7_(%"struct.std::__1::pair.147"* dereferenceable(16) %4) #8
  %6 = call %"struct.std::__1::pair.147"* @_ZNSt3__17launderINS_4pairIKPN4LL2W4NodeEiEEEEPT_S8_(%"struct.std::__1::pair.147"* %5) #8
  ret %"struct.std::__1::pair.147"* %6
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair.147"* @_ZNSt3__17launderINS_4pairIKPN4LL2W4NodeEiEEEEPT_S8_(%"struct.std::__1::pair.147"*) #4 {
  %2 = alloca %"struct.std::__1::pair.147"*, align 8
  store %"struct.std::__1::pair.147"* %0, %"struct.std::__1::pair.147"** %2, align 8
  %3 = load %"struct.std::__1::pair.147"*, %"struct.std::__1::pair.147"** %2, align 8
  %4 = call %"struct.std::__1::pair.147"* @_ZNSt3__19__launderINS_4pairIKPN4LL2W4NodeEiEEEEPT_S8_(%"struct.std::__1::pair.147"* %3) #8
  ret %"struct.std::__1::pair.147"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"struct.std::__1::pair.147"* @_ZNSt3__19__launderINS_4pairIKPN4LL2W4NodeEiEEEEPT_S8_(%"struct.std::__1::pair.147"*) #4 {
  %2 = alloca %"struct.std::__1::pair.147"*, align 8
  store %"struct.std::__1::pair.147"* %0, %"struct.std::__1::pair.147"** %2, align 8
  %3 = load %"struct.std::__1::pair.147"*, %"struct.std::__1::pair.147"** %2, align 8
  ret %"struct.std::__1::pair.147"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEE10deallocateEPS8_m(%"class.std::__1::allocator.103"*, %"struct.std::__1::__hash_node.145"*, i64) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::allocator.103"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node.145"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.103"* %0, %"class.std::__1::allocator.103"** %4, align 8
  store %"struct.std::__1::__hash_node.145"* %1, %"struct.std::__1::__hash_node.145"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.103"*, %"class.std::__1::allocator.103"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node.145"*, %"struct.std::__1::__hash_node.145"** %5, align 8
  %9 = bitcast %"struct.std::__1::__hash_node.145"* %8 to i8*
  %10 = load i64, i64* %6, align 8
  %11 = mul i64 %10, 32
  invoke void @_ZNSt3__119__libcpp_deallocateEPvmm(i8* %9, i64 %11, i64 8)
          to label %12 unwind label %13

; <label>:12:                                     ; preds = %3
  ret void

; <label>:13:                                     ; preds = %3
  %14 = landingpad { i8*, i32 }
          catch i8* null
  %15 = extractvalue { i8*, i32 } %14, 0
  call void @__clang_call_terminate(i8* %15) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.93"* @_ZNSt3__122__compressed_pair_elemINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.101"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.101"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.101"* %0, %"struct.std::__1::__compressed_pair_elem.101"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.101"*, %"struct.std::__1::__compressed_pair_elem.101"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.101", %"struct.std::__1::__compressed_pair_elem.101"* %3, i32 0, i32 0
  ret %"struct.std::__1::__hash_node_base.93"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEED2Ev(%"class.std::__1::unique_ptr.90"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.90"*, align 8
  store %"class.std::__1::unique_ptr.90"* %0, %"class.std::__1::unique_ptr.90"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.90"*, %"class.std::__1::unique_ptr.90"** %2, align 8
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5resetEDn(%"class.std::__1::unique_ptr.90"* %3, i8* null) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5resetEDn(%"class.std::__1::unique_ptr.90"*, i8*) #4 align 2 {
  %3 = alloca %"class.std::__1::unique_ptr.90"*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.93"**, align 8
  store %"class.std::__1::unique_ptr.90"* %0, %"class.std::__1::unique_ptr.90"** %3, align 8
  store i8* %1, i8** %4, align 8
  %6 = load %"class.std::__1::unique_ptr.90"*, %"class.std::__1::unique_ptr.90"** %3, align 8
  %7 = getelementptr inbounds %"class.std::__1::unique_ptr.90", %"class.std::__1::unique_ptr.90"* %6, i32 0, i32 0
  %8 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.93"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5firstEv(%"class.std::__1::__compressed_pair.91"* %7) #8
  %9 = load %"struct.std::__1::__hash_node_base.93"**, %"struct.std::__1::__hash_node_base.93"*** %8, align 8
  store %"struct.std::__1::__hash_node_base.93"** %9, %"struct.std::__1::__hash_node_base.93"*** %5, align 8
  %10 = getelementptr inbounds %"class.std::__1::unique_ptr.90", %"class.std::__1::unique_ptr.90"* %6, i32 0, i32 0
  %11 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.93"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5firstEv(%"class.std::__1::__compressed_pair.91"* %10) #8
  store %"struct.std::__1::__hash_node_base.93"** null, %"struct.std::__1::__hash_node_base.93"*** %11, align 8
  %12 = load %"struct.std::__1::__hash_node_base.93"**, %"struct.std::__1::__hash_node_base.93"*** %5, align 8
  %13 = icmp ne %"struct.std::__1::__hash_node_base.93"** %12, null
  br i1 %13, label %14, label %18

; <label>:14:                                     ; preds = %2
  %15 = getelementptr inbounds %"class.std::__1::unique_ptr.90", %"class.std::__1::unique_ptr.90"* %6, i32 0, i32 0
  %16 = call dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.95"* @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE6secondEv(%"class.std::__1::__compressed_pair.91"* %15) #8
  %17 = load %"struct.std::__1::__hash_node_base.93"**, %"struct.std::__1::__hash_node_base.93"*** %5, align 8
  call void @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEEclEPSD_(%"class.std::__1::__bucket_list_deallocator.95"* %16, %"struct.std::__1::__hash_node_base.93"** %17) #8
  br label %18

; <label>:18:                                     ; preds = %14, %2
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.93"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5firstEv(%"class.std::__1::__compressed_pair.91"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.91"*, align 8
  store %"class.std::__1::__compressed_pair.91"* %0, %"class.std::__1::__compressed_pair.91"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.91"*, %"class.std::__1::__compressed_pair.91"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.91"* %3 to %"struct.std::__1::__compressed_pair_elem.92"*
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.93"*** @_ZNSt3__122__compressed_pair_elemIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.92"* %4) #8
  ret %"struct.std::__1::__hash_node_base.93"*** %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.95"* @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE6secondEv(%"class.std::__1::__compressed_pair.91"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.91"*, align 8
  store %"class.std::__1::__compressed_pair.91"* %0, %"class.std::__1::__compressed_pair.91"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.91"*, %"class.std::__1::__compressed_pair.91"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.91"* %3 to i8*
  %5 = getelementptr inbounds i8, i8* %4, i64 8
  %6 = bitcast i8* %5 to %"struct.std::__1::__compressed_pair_elem.94"*
  %7 = call dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.95"* @_ZNSt3__122__compressed_pair_elemINS_25__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEEELi1ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.94"* %6) #8
  ret %"class.std::__1::__bucket_list_deallocator.95"* %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEEclEPSD_(%"class.std::__1::__bucket_list_deallocator.95"*, %"struct.std::__1::__hash_node_base.93"**) #4 align 2 {
  %3 = alloca %"class.std::__1::__bucket_list_deallocator.95"*, align 8
  %4 = alloca %"struct.std::__1::__hash_node_base.93"**, align 8
  store %"class.std::__1::__bucket_list_deallocator.95"* %0, %"class.std::__1::__bucket_list_deallocator.95"** %3, align 8
  store %"struct.std::__1::__hash_node_base.93"** %1, %"struct.std::__1::__hash_node_base.93"*** %4, align 8
  %5 = load %"class.std::__1::__bucket_list_deallocator.95"*, %"class.std::__1::__bucket_list_deallocator.95"** %3, align 8
  %6 = call dereferenceable(1) %"class.std::__1::allocator.98"* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE7__allocEv(%"class.std::__1::__bucket_list_deallocator.95"* %5) #8
  %7 = load %"struct.std::__1::__hash_node_base.93"**, %"struct.std::__1::__hash_node_base.93"*** %4, align 8
  %8 = call dereferenceable(8) i64* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE4sizeEv(%"class.std::__1::__bucket_list_deallocator.95"* %5) #8
  %9 = load i64, i64* %8, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE10deallocateERSE_PSD_m(%"class.std::__1::allocator.98"* dereferenceable(1) %6, %"struct.std::__1::__hash_node_base.93"** %7, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.93"*** @_ZNSt3__122__compressed_pair_elemIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.92"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.92"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.92"* %0, %"struct.std::__1::__compressed_pair_elem.92"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.92"*, %"struct.std::__1::__compressed_pair_elem.92"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.92", %"struct.std::__1::__compressed_pair_elem.92"* %3, i32 0, i32 0
  ret %"struct.std::__1::__hash_node_base.93"*** %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.95"* @_ZNSt3__122__compressed_pair_elemINS_25__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEEELi1ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.94"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.94"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.94"* %0, %"struct.std::__1::__compressed_pair_elem.94"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.94"*, %"struct.std::__1::__compressed_pair_elem.94"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.94", %"struct.std::__1::__compressed_pair_elem.94"* %3, i32 0, i32 0
  ret %"class.std::__1::__bucket_list_deallocator.95"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__116allocator_traitsINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE10deallocateERSE_PSD_m(%"class.std::__1::allocator.98"* dereferenceable(1), %"struct.std::__1::__hash_node_base.93"**, i64) #4 align 2 {
  %4 = alloca %"class.std::__1::allocator.98"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.93"**, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.98"* %0, %"class.std::__1::allocator.98"** %4, align 8
  store %"struct.std::__1::__hash_node_base.93"** %1, %"struct.std::__1::__hash_node_base.93"*** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.98"*, %"class.std::__1::allocator.98"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node_base.93"**, %"struct.std::__1::__hash_node_base.93"*** %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__19allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE10deallocateEPSC_m(%"class.std::__1::allocator.98"* %7, %"struct.std::__1::__hash_node_base.93"** %8, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.98"* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE7__allocEv(%"class.std::__1::__bucket_list_deallocator.95"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__bucket_list_deallocator.95"*, align 8
  store %"class.std::__1::__bucket_list_deallocator.95"* %0, %"class.std::__1::__bucket_list_deallocator.95"** %2, align 8
  %3 = load %"class.std::__1::__bucket_list_deallocator.95"*, %"class.std::__1::__bucket_list_deallocator.95"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__bucket_list_deallocator.95", %"class.std::__1::__bucket_list_deallocator.95"* %3, i32 0, i32 0
  %5 = call dereferenceable(1) %"class.std::__1::allocator.98"* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE6secondEv(%"class.std::__1::__compressed_pair.96"* %4) #8
  ret %"class.std::__1::allocator.98"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) i64* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE4sizeEv(%"class.std::__1::__bucket_list_deallocator.95"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__bucket_list_deallocator.95"*, align 8
  store %"class.std::__1::__bucket_list_deallocator.95"* %0, %"class.std::__1::__bucket_list_deallocator.95"** %2, align 8
  %3 = load %"class.std::__1::__bucket_list_deallocator.95"*, %"class.std::__1::__bucket_list_deallocator.95"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__bucket_list_deallocator.95", %"class.std::__1::__bucket_list_deallocator.95"* %3, i32 0, i32 0
  %5 = call dereferenceable(8) i64* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE5firstEv(%"class.std::__1::__compressed_pair.96"* %4) #8
  ret i64* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEE10deallocateEPSC_m(%"class.std::__1::allocator.98"*, %"struct.std::__1::__hash_node_base.93"**, i64) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::allocator.98"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.93"**, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.98"* %0, %"class.std::__1::allocator.98"** %4, align 8
  store %"struct.std::__1::__hash_node_base.93"** %1, %"struct.std::__1::__hash_node_base.93"*** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.98"*, %"class.std::__1::allocator.98"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node_base.93"**, %"struct.std::__1::__hash_node_base.93"*** %5, align 8
  %9 = bitcast %"struct.std::__1::__hash_node_base.93"** %8 to i8*
  %10 = load i64, i64* %6, align 8
  %11 = mul i64 %10, 8
  invoke void @_ZNSt3__119__libcpp_deallocateEPvmm(i8* %9, i64 %11, i64 8)
          to label %12 unwind label %13

; <label>:12:                                     ; preds = %3
  ret void

; <label>:13:                                     ; preds = %3
  %14 = landingpad { i8*, i32 }
          catch i8* null
  %15 = extractvalue { i8*, i32 } %14, 0
  call void @__clang_call_terminate(i8* %15) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.98"* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE6secondEv(%"class.std::__1::__compressed_pair.96"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.96"*, align 8
  store %"class.std::__1::__compressed_pair.96"* %0, %"class.std::__1::__compressed_pair.96"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.96"*, %"class.std::__1::__compressed_pair.96"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.96"* %3 to %"struct.std::__1::__compressed_pair_elem.97"*
  %5 = call dereferenceable(1) %"class.std::__1::allocator.98"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.97"* %4) #8
  ret %"class.std::__1::allocator.98"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.98"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.97"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.97"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.97"* %0, %"struct.std::__1::__compressed_pair_elem.97"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.97"*, %"struct.std::__1::__compressed_pair_elem.97"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.97"* %3 to %"class.std::__1::allocator.98"*
  ret %"class.std::__1::allocator.98"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) i64* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeEiEEPvEEEEEEE5firstEv(%"class.std::__1::__compressed_pair.96"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.96"*, align 8
  store %"class.std::__1::__compressed_pair.96"* %0, %"class.std::__1::__compressed_pair.96"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.96"*, %"class.std::__1::__compressed_pair.96"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.96"* %3 to %"struct.std::__1::__compressed_pair_elem"*
  %5 = call dereferenceable(8) i64* @_ZNSt3__122__compressed_pair_elemImLi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem"* %4) #8
  ret i64* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__113unordered_mapIPN4LL2W4NodeES3_NS_4hashIS3_EENS_8equal_toIS3_EENS_9allocatorINS_4pairIKS3_S3_EEEEED2Ev(%"class.std::__1::unordered_map.64"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unordered_map.64"*, align 8
  store %"class.std::__1::unordered_map.64"* %0, %"class.std::__1::unordered_map.64"** %2, align 8
  %3 = load %"class.std::__1::unordered_map.64"*, %"class.std::__1::unordered_map.64"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::unordered_map.64", %"class.std::__1::unordered_map.64"* %3, i32 0, i32 0
  call void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeES4_EENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEED1Ev(%"class.std::__1::__hash_table.65"* %4) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeES4_EENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEED1Ev(%"class.std::__1::__hash_table.65"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.65"*, align 8
  store %"class.std::__1::__hash_table.65"* %0, %"class.std::__1::__hash_table.65"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.65"*, %"class.std::__1::__hash_table.65"** %2, align 8
  call void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeES4_EENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEED2Ev(%"class.std::__1::__hash_table.65"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeES4_EENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEED2Ev(%"class.std::__1::__hash_table.65"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.65"*, align 8
  store %"class.std::__1::__hash_table.65"* %0, %"class.std::__1::__hash_table.65"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.65"*, %"class.std::__1::__hash_table.65"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__hash_table.65", %"class.std::__1::__hash_table.65"* %3, i32 0, i32 1
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.69"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_9allocatorIS9_EEE5firstEv(%"class.std::__1::__compressed_pair.76"* %4) #8
  %6 = getelementptr inbounds %"struct.std::__1::__hash_node_base.69", %"struct.std::__1::__hash_node_base.69"* %5, i32 0, i32 0
  %7 = load %"struct.std::__1::__hash_node_base.69"*, %"struct.std::__1::__hash_node_base.69"** %6, align 8
  call void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeES4_EENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEE17__deallocate_nodeEPNS_16__hash_node_baseIPNS_11__hash_nodeIS5_PvEEEE(%"class.std::__1::__hash_table.65"* %3, %"struct.std::__1::__hash_node_base.69"* %7) #8
  %8 = getelementptr inbounds %"class.std::__1::__hash_table.65", %"class.std::__1::__hash_table.65"* %3, i32 0, i32 0
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEED1Ev(%"class.std::__1::unique_ptr.66"* %8) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeES4_EENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEE17__deallocate_nodeEPNS_16__hash_node_baseIPNS_11__hash_nodeIS5_PvEEEE(%"class.std::__1::__hash_table.65"*, %"struct.std::__1::__hash_node_base.69"*) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::__1::__hash_table.65"*, align 8
  %4 = alloca %"struct.std::__1::__hash_node_base.69"*, align 8
  %5 = alloca %"class.std::__1::allocator.79"*, align 8
  %6 = alloca %"struct.std::__1::__hash_node_base.69"*, align 8
  %7 = alloca %"struct.std::__1::__hash_node.149"*, align 8
  store %"class.std::__1::__hash_table.65"* %0, %"class.std::__1::__hash_table.65"** %3, align 8
  store %"struct.std::__1::__hash_node_base.69"* %1, %"struct.std::__1::__hash_node_base.69"** %4, align 8
  %8 = load %"class.std::__1::__hash_table.65"*, %"class.std::__1::__hash_table.65"** %3, align 8
  %9 = call dereferenceable(1) %"class.std::__1::allocator.79"* @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeES4_EENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEE12__node_allocEv(%"class.std::__1::__hash_table.65"* %8) #8
  store %"class.std::__1::allocator.79"* %9, %"class.std::__1::allocator.79"** %5, align 8
  br label %10

; <label>:10:                                     ; preds = %24, %2
  %11 = load %"struct.std::__1::__hash_node_base.69"*, %"struct.std::__1::__hash_node_base.69"** %4, align 8
  %12 = icmp ne %"struct.std::__1::__hash_node_base.69"* %11, null
  br i1 %12, label %13, label %28

; <label>:13:                                     ; preds = %10
  %14 = load %"struct.std::__1::__hash_node_base.69"*, %"struct.std::__1::__hash_node_base.69"** %4, align 8
  %15 = getelementptr inbounds %"struct.std::__1::__hash_node_base.69", %"struct.std::__1::__hash_node_base.69"* %14, i32 0, i32 0
  %16 = load %"struct.std::__1::__hash_node_base.69"*, %"struct.std::__1::__hash_node_base.69"** %15, align 8
  store %"struct.std::__1::__hash_node_base.69"* %16, %"struct.std::__1::__hash_node_base.69"** %6, align 8
  %17 = load %"struct.std::__1::__hash_node_base.69"*, %"struct.std::__1::__hash_node_base.69"** %4, align 8
  %18 = call %"struct.std::__1::__hash_node.149"* @_ZNSt3__116__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES5_EEPvEEE8__upcastEv(%"struct.std::__1::__hash_node_base.69"* %17) #8
  store %"struct.std::__1::__hash_node.149"* %18, %"struct.std::__1::__hash_node.149"** %7, align 8
  %19 = load %"class.std::__1::allocator.79"*, %"class.std::__1::allocator.79"** %5, align 8
  %20 = load %"struct.std::__1::__hash_node.149"*, %"struct.std::__1::__hash_node.149"** %7, align 8
  %21 = getelementptr inbounds %"struct.std::__1::__hash_node.149", %"struct.std::__1::__hash_node.149"* %20, i32 0, i32 2
  %22 = invoke %"struct.std::__1::pair.151"* @_ZNSt3__122__hash_key_value_typesINS_17__hash_value_typeIPN4LL2W4NodeES4_EEE9__get_ptrERS5_(%"struct.std::__1::__hash_value_type.150"* dereferenceable(16) %21)
          to label %23 unwind label %29

; <label>:23:                                     ; preds = %13
  invoke void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE7destroyINS_4pairIKS6_S6_EEEEvRSA_PT_(%"class.std::__1::allocator.79"* dereferenceable(1) %19, %"struct.std::__1::pair.151"* %22)
          to label %24 unwind label %29

; <label>:24:                                     ; preds = %23
  %25 = load %"class.std::__1::allocator.79"*, %"class.std::__1::allocator.79"** %5, align 8
  %26 = load %"struct.std::__1::__hash_node.149"*, %"struct.std::__1::__hash_node.149"** %7, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE10deallocateERSA_PS9_m(%"class.std::__1::allocator.79"* dereferenceable(1) %25, %"struct.std::__1::__hash_node.149"* %26, i64 1) #8
  %27 = load %"struct.std::__1::__hash_node_base.69"*, %"struct.std::__1::__hash_node_base.69"** %6, align 8
  store %"struct.std::__1::__hash_node_base.69"* %27, %"struct.std::__1::__hash_node_base.69"** %4, align 8
  br label %10

; <label>:28:                                     ; preds = %10
  ret void

; <label>:29:                                     ; preds = %23, %13
  %30 = landingpad { i8*, i32 }
          catch i8* null
  %31 = extractvalue { i8*, i32 } %30, 0
  call void @__clang_call_terminate(i8* %31) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.69"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_9allocatorIS9_EEE5firstEv(%"class.std::__1::__compressed_pair.76"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.76"*, align 8
  store %"class.std::__1::__compressed_pair.76"* %0, %"class.std::__1::__compressed_pair.76"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.76"*, %"class.std::__1::__compressed_pair.76"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.76"* %3 to %"struct.std::__1::__compressed_pair_elem.77"*
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.69"* @_ZNSt3__122__compressed_pair_elemINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.77"* %4) #8
  ret %"struct.std::__1::__hash_node_base.69"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEED1Ev(%"class.std::__1::unique_ptr.66"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.66"*, align 8
  store %"class.std::__1::unique_ptr.66"* %0, %"class.std::__1::unique_ptr.66"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.66"*, %"class.std::__1::unique_ptr.66"** %2, align 8
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEED2Ev(%"class.std::__1::unique_ptr.66"* %3) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.79"* @_ZNSt3__112__hash_tableINS_17__hash_value_typeIPN4LL2W4NodeES4_EENS_22__unordered_map_hasherIS4_S5_NS_4hashIS4_EELb1EEENS_21__unordered_map_equalIS4_S5_NS_8equal_toIS4_EELb1EEENS_9allocatorIS5_EEE12__node_allocEv(%"class.std::__1::__hash_table.65"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__hash_table.65"*, align 8
  store %"class.std::__1::__hash_table.65"* %0, %"class.std::__1::__hash_table.65"** %2, align 8
  %3 = load %"class.std::__1::__hash_table.65"*, %"class.std::__1::__hash_table.65"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__hash_table.65", %"class.std::__1::__hash_table.65"* %3, i32 0, i32 1
  %5 = call dereferenceable(1) %"class.std::__1::allocator.79"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_9allocatorIS9_EEE6secondEv(%"class.std::__1::__compressed_pair.76"* %4) #8
  ret %"class.std::__1::allocator.79"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node.149"* @_ZNSt3__116__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES5_EEPvEEE8__upcastEv(%"struct.std::__1::__hash_node_base.69"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_node_base.69"*, align 8
  store %"struct.std::__1::__hash_node_base.69"* %0, %"struct.std::__1::__hash_node_base.69"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.69"*, %"struct.std::__1::__hash_node_base.69"** %2, align 8
  %4 = call %"struct.std::__1::__hash_node_base.69"* @_ZNSt3__114pointer_traitsIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE10pointer_toERSB_(%"struct.std::__1::__hash_node_base.69"* dereferenceable(8) %3) #8
  %5 = bitcast %"struct.std::__1::__hash_node_base.69"* %4 to %"struct.std::__1::__hash_node.149"*
  ret %"struct.std::__1::__hash_node.149"* %5
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE7destroyINS_4pairIKS6_S6_EEEEvRSA_PT_(%"class.std::__1::allocator.79"* dereferenceable(1), %"struct.std::__1::pair.151"*) #1 align 2 {
  %3 = alloca %"class.std::__1::allocator.79"*, align 8
  %4 = alloca %"struct.std::__1::pair.151"*, align 8
  %5 = alloca %"struct.std::__1::integral_constant.141", align 1
  %6 = alloca %"struct.std::__1::__has_destroy.152", align 1
  store %"class.std::__1::allocator.79"* %0, %"class.std::__1::allocator.79"** %3, align 8
  store %"struct.std::__1::pair.151"* %1, %"struct.std::__1::pair.151"** %4, align 8
  %7 = bitcast %"struct.std::__1::__has_destroy.152"* %6 to %"struct.std::__1::integral_constant.141"*
  %8 = load %"class.std::__1::allocator.79"*, %"class.std::__1::allocator.79"** %3, align 8
  %9 = load %"struct.std::__1::pair.151"*, %"struct.std::__1::pair.151"** %4, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE9__destroyINS_4pairIKS6_S6_EEEEvNS_17integral_constantIbLb0EEERSA_PT_(%"class.std::__1::allocator.79"* dereferenceable(1) %8, %"struct.std::__1::pair.151"* %9)
  ret void
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair.151"* @_ZNSt3__122__hash_key_value_typesINS_17__hash_value_typeIPN4LL2W4NodeES4_EEE9__get_ptrERS5_(%"struct.std::__1::__hash_value_type.150"* dereferenceable(16)) #1 align 2 {
  %2 = alloca %"struct.std::__1::__hash_value_type.150"*, align 8
  store %"struct.std::__1::__hash_value_type.150"* %0, %"struct.std::__1::__hash_value_type.150"** %2, align 8
  %3 = load %"struct.std::__1::__hash_value_type.150"*, %"struct.std::__1::__hash_value_type.150"** %2, align 8
  %4 = call dereferenceable(16) %"struct.std::__1::pair.151"* @_ZNSt3__117__hash_value_typeIPN4LL2W4NodeES3_E11__get_valueEv(%"struct.std::__1::__hash_value_type.150"* %3)
  %5 = call %"struct.std::__1::pair.151"* @_ZNSt3__19addressofINS_4pairIKPN4LL2W4NodeES4_EEEEPT_RS7_(%"struct.std::__1::pair.151"* dereferenceable(16) %4) #8
  ret %"struct.std::__1::pair.151"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE10deallocateERSA_PS9_m(%"class.std::__1::allocator.79"* dereferenceable(1), %"struct.std::__1::__hash_node.149"*, i64) #4 align 2 {
  %4 = alloca %"class.std::__1::allocator.79"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node.149"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.79"* %0, %"class.std::__1::allocator.79"** %4, align 8
  store %"struct.std::__1::__hash_node.149"* %1, %"struct.std::__1::__hash_node.149"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.79"*, %"class.std::__1::allocator.79"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node.149"*, %"struct.std::__1::__hash_node.149"** %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__19allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES5_EEPvEEE10deallocateEPS8_m(%"class.std::__1::allocator.79"* %7, %"struct.std::__1::__hash_node.149"* %8, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.79"* @_ZNSt3__117__compressed_pairINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_9allocatorIS9_EEE6secondEv(%"class.std::__1::__compressed_pair.76"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.76"*, align 8
  store %"class.std::__1::__compressed_pair.76"* %0, %"class.std::__1::__compressed_pair.76"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.76"*, %"class.std::__1::__compressed_pair.76"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.76"* %3 to %"struct.std::__1::__compressed_pair_elem.78"*
  %5 = call dereferenceable(1) %"class.std::__1::allocator.79"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.78"* %4) #8
  ret %"class.std::__1::allocator.79"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.79"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.78"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.78"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.78"* %0, %"struct.std::__1::__compressed_pair_elem.78"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.78"*, %"struct.std::__1::__compressed_pair_elem.78"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.78"* %3 to %"class.std::__1::allocator.79"*
  ret %"class.std::__1::allocator.79"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node_base.69"* @_ZNSt3__114pointer_traitsIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE10pointer_toERSB_(%"struct.std::__1::__hash_node_base.69"* dereferenceable(8)) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_node_base.69"*, align 8
  store %"struct.std::__1::__hash_node_base.69"* %0, %"struct.std::__1::__hash_node_base.69"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.69"*, %"struct.std::__1::__hash_node_base.69"** %2, align 8
  %4 = call %"struct.std::__1::__hash_node_base.69"* @_ZNSt3__19addressofINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEEEPT_RSC_(%"struct.std::__1::__hash_node_base.69"* dereferenceable(8) %3) #8
  ret %"struct.std::__1::__hash_node_base.69"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::__hash_node_base.69"* @_ZNSt3__19addressofINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEEEPT_RSC_(%"struct.std::__1::__hash_node_base.69"* dereferenceable(8)) #4 {
  %2 = alloca %"struct.std::__1::__hash_node_base.69"*, align 8
  store %"struct.std::__1::__hash_node_base.69"* %0, %"struct.std::__1::__hash_node_base.69"** %2, align 8
  %3 = load %"struct.std::__1::__hash_node_base.69"*, %"struct.std::__1::__hash_node_base.69"** %2, align 8
  ret %"struct.std::__1::__hash_node_base.69"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr void @_ZNSt3__116allocator_traitsINS_9allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE9__destroyINS_4pairIKS6_S6_EEEEvNS_17integral_constantIbLb0EEERSA_PT_(%"class.std::__1::allocator.79"* dereferenceable(1), %"struct.std::__1::pair.151"*) #4 align 2 {
  %3 = alloca %"struct.std::__1::integral_constant.141", align 1
  %4 = alloca %"class.std::__1::allocator.79"*, align 8
  %5 = alloca %"struct.std::__1::pair.151"*, align 8
  store %"class.std::__1::allocator.79"* %0, %"class.std::__1::allocator.79"** %4, align 8
  store %"struct.std::__1::pair.151"* %1, %"struct.std::__1::pair.151"** %5, align 8
  %6 = load %"struct.std::__1::pair.151"*, %"struct.std::__1::pair.151"** %5, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair.151"* @_ZNSt3__19addressofINS_4pairIKPN4LL2W4NodeES4_EEEEPT_RS7_(%"struct.std::__1::pair.151"* dereferenceable(16)) #4 {
  %2 = alloca %"struct.std::__1::pair.151"*, align 8
  store %"struct.std::__1::pair.151"* %0, %"struct.std::__1::pair.151"** %2, align 8
  %3 = load %"struct.std::__1::pair.151"*, %"struct.std::__1::pair.151"** %2, align 8
  ret %"struct.std::__1::pair.151"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(16) %"struct.std::__1::pair.151"* @_ZNSt3__117__hash_value_typeIPN4LL2W4NodeES3_E11__get_valueEv(%"struct.std::__1::__hash_value_type.150"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__hash_value_type.150"*, align 8
  store %"struct.std::__1::__hash_value_type.150"* %0, %"struct.std::__1::__hash_value_type.150"** %2, align 8
  %3 = load %"struct.std::__1::__hash_value_type.150"*, %"struct.std::__1::__hash_value_type.150"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__hash_value_type.150", %"struct.std::__1::__hash_value_type.150"* %3, i32 0, i32 0
  %5 = call %"struct.std::__1::pair.151"* @_ZNSt3__19addressofINS_4pairIKPN4LL2W4NodeES4_EEEEPT_RS7_(%"struct.std::__1::pair.151"* dereferenceable(16) %4) #8
  %6 = call %"struct.std::__1::pair.151"* @_ZNSt3__17launderINS_4pairIKPN4LL2W4NodeES4_EEEEPT_S8_(%"struct.std::__1::pair.151"* %5) #8
  ret %"struct.std::__1::pair.151"* %6
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair.151"* @_ZNSt3__17launderINS_4pairIKPN4LL2W4NodeES4_EEEEPT_S8_(%"struct.std::__1::pair.151"*) #4 {
  %2 = alloca %"struct.std::__1::pair.151"*, align 8
  store %"struct.std::__1::pair.151"* %0, %"struct.std::__1::pair.151"** %2, align 8
  %3 = load %"struct.std::__1::pair.151"*, %"struct.std::__1::pair.151"** %2, align 8
  %4 = call %"struct.std::__1::pair.151"* @_ZNSt3__19__launderINS_4pairIKPN4LL2W4NodeES4_EEEEPT_S8_(%"struct.std::__1::pair.151"* %3) #8
  ret %"struct.std::__1::pair.151"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr %"struct.std::__1::pair.151"* @_ZNSt3__19__launderINS_4pairIKPN4LL2W4NodeES4_EEEEPT_S8_(%"struct.std::__1::pair.151"*) #4 {
  %2 = alloca %"struct.std::__1::pair.151"*, align 8
  store %"struct.std::__1::pair.151"* %0, %"struct.std::__1::pair.151"** %2, align 8
  %3 = load %"struct.std::__1::pair.151"*, %"struct.std::__1::pair.151"** %2, align 8
  ret %"struct.std::__1::pair.151"* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorINS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES5_EEPvEEE10deallocateEPS8_m(%"class.std::__1::allocator.79"*, %"struct.std::__1::__hash_node.149"*, i64) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::allocator.79"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node.149"*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.79"* %0, %"class.std::__1::allocator.79"** %4, align 8
  store %"struct.std::__1::__hash_node.149"* %1, %"struct.std::__1::__hash_node.149"** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.79"*, %"class.std::__1::allocator.79"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node.149"*, %"struct.std::__1::__hash_node.149"** %5, align 8
  %9 = bitcast %"struct.std::__1::__hash_node.149"* %8 to i8*
  %10 = load i64, i64* %6, align 8
  %11 = mul i64 %10, 32
  invoke void @_ZNSt3__119__libcpp_deallocateEPvmm(i8* %9, i64 %11, i64 8)
          to label %12 unwind label %13

; <label>:12:                                     ; preds = %3
  ret void

; <label>:13:                                     ; preds = %3
  %14 = landingpad { i8*, i32 }
          catch i8* null
  %15 = extractvalue { i8*, i32 } %14, 0
  call void @__clang_call_terminate(i8* %15) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.69"* @_ZNSt3__122__compressed_pair_elemINS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.77"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.77"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.77"* %0, %"struct.std::__1::__compressed_pair_elem.77"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.77"*, %"struct.std::__1::__compressed_pair_elem.77"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.77", %"struct.std::__1::__compressed_pair_elem.77"* %3, i32 0, i32 0
  ret %"struct.std::__1::__hash_node_base.69"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEED2Ev(%"class.std::__1::unique_ptr.66"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::unique_ptr.66"*, align 8
  store %"class.std::__1::unique_ptr.66"* %0, %"class.std::__1::unique_ptr.66"** %2, align 8
  %3 = load %"class.std::__1::unique_ptr.66"*, %"class.std::__1::unique_ptr.66"** %2, align 8
  call void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5resetEDn(%"class.std::__1::unique_ptr.66"* %3, i8* null) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__110unique_ptrIA_PNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5resetEDn(%"class.std::__1::unique_ptr.66"*, i8*) #4 align 2 {
  %3 = alloca %"class.std::__1::unique_ptr.66"*, align 8
  %4 = alloca i8*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.69"**, align 8
  store %"class.std::__1::unique_ptr.66"* %0, %"class.std::__1::unique_ptr.66"** %3, align 8
  store i8* %1, i8** %4, align 8
  %6 = load %"class.std::__1::unique_ptr.66"*, %"class.std::__1::unique_ptr.66"** %3, align 8
  %7 = getelementptr inbounds %"class.std::__1::unique_ptr.66", %"class.std::__1::unique_ptr.66"* %6, i32 0, i32 0
  %8 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.69"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5firstEv(%"class.std::__1::__compressed_pair.67"* %7) #8
  %9 = load %"struct.std::__1::__hash_node_base.69"**, %"struct.std::__1::__hash_node_base.69"*** %8, align 8
  store %"struct.std::__1::__hash_node_base.69"** %9, %"struct.std::__1::__hash_node_base.69"*** %5, align 8
  %10 = getelementptr inbounds %"class.std::__1::unique_ptr.66", %"class.std::__1::unique_ptr.66"* %6, i32 0, i32 0
  %11 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.69"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5firstEv(%"class.std::__1::__compressed_pair.67"* %10) #8
  store %"struct.std::__1::__hash_node_base.69"** null, %"struct.std::__1::__hash_node_base.69"*** %11, align 8
  %12 = load %"struct.std::__1::__hash_node_base.69"**, %"struct.std::__1::__hash_node_base.69"*** %5, align 8
  %13 = icmp ne %"struct.std::__1::__hash_node_base.69"** %12, null
  br i1 %13, label %14, label %18

; <label>:14:                                     ; preds = %2
  %15 = getelementptr inbounds %"class.std::__1::unique_ptr.66", %"class.std::__1::unique_ptr.66"* %6, i32 0, i32 0
  %16 = call dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.71"* @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE6secondEv(%"class.std::__1::__compressed_pair.67"* %15) #8
  %17 = load %"struct.std::__1::__hash_node_base.69"**, %"struct.std::__1::__hash_node_base.69"*** %5, align 8
  call void @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEEclEPSD_(%"class.std::__1::__bucket_list_deallocator.71"* %16, %"struct.std::__1::__hash_node_base.69"** %17) #8
  br label %18

; <label>:18:                                     ; preds = %14, %2
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.69"*** @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE5firstEv(%"class.std::__1::__compressed_pair.67"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.67"*, align 8
  store %"class.std::__1::__compressed_pair.67"* %0, %"class.std::__1::__compressed_pair.67"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.67"*, %"class.std::__1::__compressed_pair.67"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.67"* %3 to %"struct.std::__1::__compressed_pair_elem.68"*
  %5 = call dereferenceable(8) %"struct.std::__1::__hash_node_base.69"*** @_ZNSt3__122__compressed_pair_elemIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.68"* %4) #8
  ret %"struct.std::__1::__hash_node_base.69"*** %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.71"* @_ZNSt3__117__compressed_pairIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEENS_25__bucket_list_deallocatorINS_9allocatorISC_EEEEE6secondEv(%"class.std::__1::__compressed_pair.67"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.67"*, align 8
  store %"class.std::__1::__compressed_pair.67"* %0, %"class.std::__1::__compressed_pair.67"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.67"*, %"class.std::__1::__compressed_pair.67"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.67"* %3 to i8*
  %5 = getelementptr inbounds i8, i8* %4, i64 8
  %6 = bitcast i8* %5 to %"struct.std::__1::__compressed_pair_elem.70"*
  %7 = call dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.71"* @_ZNSt3__122__compressed_pair_elemINS_25__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES8_EEPvEEEEEEEELi1ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.70"* %6) #8
  ret %"class.std::__1::__bucket_list_deallocator.71"* %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEEclEPSD_(%"class.std::__1::__bucket_list_deallocator.71"*, %"struct.std::__1::__hash_node_base.69"**) #4 align 2 {
  %3 = alloca %"class.std::__1::__bucket_list_deallocator.71"*, align 8
  %4 = alloca %"struct.std::__1::__hash_node_base.69"**, align 8
  store %"class.std::__1::__bucket_list_deallocator.71"* %0, %"class.std::__1::__bucket_list_deallocator.71"** %3, align 8
  store %"struct.std::__1::__hash_node_base.69"** %1, %"struct.std::__1::__hash_node_base.69"*** %4, align 8
  %5 = load %"class.std::__1::__bucket_list_deallocator.71"*, %"class.std::__1::__bucket_list_deallocator.71"** %3, align 8
  %6 = call dereferenceable(1) %"class.std::__1::allocator.74"* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE7__allocEv(%"class.std::__1::__bucket_list_deallocator.71"* %5) #8
  %7 = load %"struct.std::__1::__hash_node_base.69"**, %"struct.std::__1::__hash_node_base.69"*** %4, align 8
  %8 = call dereferenceable(8) i64* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE4sizeEv(%"class.std::__1::__bucket_list_deallocator.71"* %5) #8
  %9 = load i64, i64* %8, align 8
  call void @_ZNSt3__116allocator_traitsINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE10deallocateERSE_PSD_m(%"class.std::__1::allocator.74"* dereferenceable(1) %6, %"struct.std::__1::__hash_node_base.69"** %7, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"struct.std::__1::__hash_node_base.69"*** @_ZNSt3__122__compressed_pair_elemIPPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.68"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.68"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.68"* %0, %"struct.std::__1::__compressed_pair_elem.68"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.68"*, %"struct.std::__1::__compressed_pair_elem.68"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.68", %"struct.std::__1::__compressed_pair_elem.68"* %3, i32 0, i32 0
  ret %"struct.std::__1::__hash_node_base.69"*** %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) %"class.std::__1::__bucket_list_deallocator.71"* @_ZNSt3__122__compressed_pair_elemINS_25__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES8_EEPvEEEEEEEELi1ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.70"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.70"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.70"* %0, %"struct.std::__1::__compressed_pair_elem.70"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.70"*, %"struct.std::__1::__compressed_pair_elem.70"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.70", %"struct.std::__1::__compressed_pair_elem.70"* %3, i32 0, i32 0
  ret %"class.std::__1::__bucket_list_deallocator.71"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__116allocator_traitsINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE10deallocateERSE_PSD_m(%"class.std::__1::allocator.74"* dereferenceable(1), %"struct.std::__1::__hash_node_base.69"**, i64) #4 align 2 {
  %4 = alloca %"class.std::__1::allocator.74"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.69"**, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.74"* %0, %"class.std::__1::allocator.74"** %4, align 8
  store %"struct.std::__1::__hash_node_base.69"** %1, %"struct.std::__1::__hash_node_base.69"*** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.74"*, %"class.std::__1::allocator.74"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node_base.69"**, %"struct.std::__1::__hash_node_base.69"*** %5, align 8
  %9 = load i64, i64* %6, align 8
  call void @_ZNSt3__19allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE10deallocateEPSC_m(%"class.std::__1::allocator.74"* %7, %"struct.std::__1::__hash_node_base.69"** %8, i64 %9) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.74"* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE7__allocEv(%"class.std::__1::__bucket_list_deallocator.71"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__bucket_list_deallocator.71"*, align 8
  store %"class.std::__1::__bucket_list_deallocator.71"* %0, %"class.std::__1::__bucket_list_deallocator.71"** %2, align 8
  %3 = load %"class.std::__1::__bucket_list_deallocator.71"*, %"class.std::__1::__bucket_list_deallocator.71"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__bucket_list_deallocator.71", %"class.std::__1::__bucket_list_deallocator.71"* %3, i32 0, i32 0
  %5 = call dereferenceable(1) %"class.std::__1::allocator.74"* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE6secondEv(%"class.std::__1::__compressed_pair.72"* %4) #8
  ret %"class.std::__1::allocator.74"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) i64* @_ZNSt3__125__bucket_list_deallocatorINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE4sizeEv(%"class.std::__1::__bucket_list_deallocator.71"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__bucket_list_deallocator.71"*, align 8
  store %"class.std::__1::__bucket_list_deallocator.71"* %0, %"class.std::__1::__bucket_list_deallocator.71"** %2, align 8
  %3 = load %"class.std::__1::__bucket_list_deallocator.71"*, %"class.std::__1::__bucket_list_deallocator.71"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::__bucket_list_deallocator.71", %"class.std::__1::__bucket_list_deallocator.71"* %3, i32 0, i32 0
  %5 = call dereferenceable(8) i64* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE5firstEv(%"class.std::__1::__compressed_pair.72"* %4) #8
  ret i64* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES6_EEPvEEEEE10deallocateEPSC_m(%"class.std::__1::allocator.74"*, %"struct.std::__1::__hash_node_base.69"**, i64) #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::allocator.74"*, align 8
  %5 = alloca %"struct.std::__1::__hash_node_base.69"**, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::allocator.74"* %0, %"class.std::__1::allocator.74"** %4, align 8
  store %"struct.std::__1::__hash_node_base.69"** %1, %"struct.std::__1::__hash_node_base.69"*** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::allocator.74"*, %"class.std::__1::allocator.74"** %4, align 8
  %8 = load %"struct.std::__1::__hash_node_base.69"**, %"struct.std::__1::__hash_node_base.69"*** %5, align 8
  %9 = bitcast %"struct.std::__1::__hash_node_base.69"** %8 to i8*
  %10 = load i64, i64* %6, align 8
  %11 = mul i64 %10, 8
  invoke void @_ZNSt3__119__libcpp_deallocateEPvmm(i8* %9, i64 %11, i64 8)
          to label %12 unwind label %13

; <label>:12:                                     ; preds = %3
  ret void

; <label>:13:                                     ; preds = %3
  %14 = landingpad { i8*, i32 }
          catch i8* null
  %15 = extractvalue { i8*, i32 } %14, 0
  call void @__clang_call_terminate(i8* %15) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.74"* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE6secondEv(%"class.std::__1::__compressed_pair.72"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.72"*, align 8
  store %"class.std::__1::__compressed_pair.72"* %0, %"class.std::__1::__compressed_pair.72"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.72"*, %"class.std::__1::__compressed_pair.72"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.72"* %3 to %"struct.std::__1::__compressed_pair_elem.73"*
  %5 = call dereferenceable(1) %"class.std::__1::allocator.74"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.73"* %4) #8
  ret %"class.std::__1::allocator.74"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(1) %"class.std::__1::allocator.74"* @_ZNSt3__122__compressed_pair_elemINS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEELi1ELb1EE5__getEv(%"struct.std::__1::__compressed_pair_elem.73"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.73"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.73"* %0, %"struct.std::__1::__compressed_pair_elem.73"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.73"*, %"struct.std::__1::__compressed_pair_elem.73"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.73"* %3 to %"class.std::__1::allocator.74"*
  ret %"class.std::__1::allocator.74"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(8) i64* @_ZNSt3__117__compressed_pairImNS_9allocatorIPNS_16__hash_node_baseIPNS_11__hash_nodeINS_17__hash_value_typeIPN4LL2W4NodeES7_EEPvEEEEEEE5firstEv(%"class.std::__1::__compressed_pair.72"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.72"*, align 8
  store %"class.std::__1::__compressed_pair.72"* %0, %"class.std::__1::__compressed_pair.72"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.72"*, %"class.std::__1::__compressed_pair.72"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.72"* %3 to %"struct.std::__1::__compressed_pair_elem"*
  %5 = call dereferenceable(8) i64* @_ZNSt3__122__compressed_pair_elemImLi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem"* %4) #8
  ret i64* %5
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr dereferenceable(160) %"class.std::__1::basic_ostream"* @_ZNSt3__124__put_character_sequenceIcNS_11char_traitsIcEEEERNS_13basic_ostreamIT_T0_EES7_PKS4_m(%"class.std::__1::basic_ostream"* dereferenceable(160), i8*, i64) #1 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %4 = alloca %"class.std::__1::basic_ostream"*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i64, align 8
  %7 = alloca %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry", align 8
  %8 = alloca i8*
  %9 = alloca i32
  %10 = alloca %"class.std::__1::ostreambuf_iterator", align 8
  %11 = alloca %"class.std::__1::ostreambuf_iterator", align 8
  store %"class.std::__1::basic_ostream"* %0, %"class.std::__1::basic_ostream"** %4, align 8
  store i8* %1, i8** %5, align 8
  store i64 %2, i64* %6, align 8
  %12 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  invoke void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %7, %"class.std::__1::basic_ostream"* dereferenceable(160) %12)
          to label %13 unwind label %80

; <label>:13:                                     ; preds = %3
  %14 = invoke zeroext i1 @_ZNKSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentrycvbEv(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %7)
          to label %15 unwind label %84

; <label>:15:                                     ; preds = %13
  br i1 %14, label %16, label %104

; <label>:16:                                     ; preds = %15
  %17 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  call void @_ZNSt3__119ostreambuf_iteratorIcNS_11char_traitsIcEEEC1ERNS_13basic_ostreamIcS2_EE(%"class.std::__1::ostreambuf_iterator"* %11, %"class.std::__1::basic_ostream"* dereferenceable(160) %17) #8
  %18 = load i8*, i8** %5, align 8
  %19 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  %20 = bitcast %"class.std::__1::basic_ostream"* %19 to i8**
  %21 = load i8*, i8** %20, align 8
  %22 = getelementptr i8, i8* %21, i64 -24
  %23 = bitcast i8* %22 to i64*
  %24 = load i64, i64* %23, align 8
  %25 = bitcast %"class.std::__1::basic_ostream"* %19 to i8*
  %26 = getelementptr inbounds i8, i8* %25, i64 %24
  %27 = bitcast i8* %26 to %"class.std::__1::ios_base"*
  %28 = invoke i32 @_ZNKSt3__18ios_base5flagsEv(%"class.std::__1::ios_base"* %27)
          to label %29 unwind label %84

; <label>:29:                                     ; preds = %16
  %30 = and i32 %28, 176
  %31 = icmp eq i32 %30, 32
  br i1 %31, label %32, label %36

; <label>:32:                                     ; preds = %29
  %33 = load i8*, i8** %5, align 8
  %34 = load i64, i64* %6, align 8
  %35 = getelementptr inbounds i8, i8* %33, i64 %34
  br label %38

; <label>:36:                                     ; preds = %29
  %37 = load i8*, i8** %5, align 8
  br label %38

; <label>:38:                                     ; preds = %36, %32
  %39 = phi i8* [ %35, %32 ], [ %37, %36 ]
  %40 = load i8*, i8** %5, align 8
  %41 = load i64, i64* %6, align 8
  %42 = getelementptr inbounds i8, i8* %40, i64 %41
  %43 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  %44 = bitcast %"class.std::__1::basic_ostream"* %43 to i8**
  %45 = load i8*, i8** %44, align 8
  %46 = getelementptr i8, i8* %45, i64 -24
  %47 = bitcast i8* %46 to i64*
  %48 = load i64, i64* %47, align 8
  %49 = bitcast %"class.std::__1::basic_ostream"* %43 to i8*
  %50 = getelementptr inbounds i8, i8* %49, i64 %48
  %51 = bitcast i8* %50 to %"class.std::__1::ios_base"*
  %52 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  %53 = bitcast %"class.std::__1::basic_ostream"* %52 to i8**
  %54 = load i8*, i8** %53, align 8
  %55 = getelementptr i8, i8* %54, i64 -24
  %56 = bitcast i8* %55 to i64*
  %57 = load i64, i64* %56, align 8
  %58 = bitcast %"class.std::__1::basic_ostream"* %52 to i8*
  %59 = getelementptr inbounds i8, i8* %58, i64 %57
  %60 = bitcast i8* %59 to %"class.std::__1::basic_ios"*
  %61 = invoke signext i8 @_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE4fillEv(%"class.std::__1::basic_ios"* %60)
          to label %62 unwind label %84

; <label>:62:                                     ; preds = %38
  %63 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %11, i32 0, i32 0
  %64 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %63, align 8
  %65 = invoke %"class.std::__1::basic_streambuf"* @_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_(%"class.std::__1::basic_streambuf"* %64, i8* %18, i8* %39, i8* %42, %"class.std::__1::ios_base"* dereferenceable(136) %51, i8 signext %61)
          to label %66 unwind label %84

; <label>:66:                                     ; preds = %62
  %67 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %10, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* %65, %"class.std::__1::basic_streambuf"** %67, align 8
  %68 = call zeroext i1 @_ZNKSt3__119ostreambuf_iteratorIcNS_11char_traitsIcEEE6failedEv(%"class.std::__1::ostreambuf_iterator"* %10) #8
  br i1 %68, label %69, label %103

; <label>:69:                                     ; preds = %66
  %70 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  %71 = bitcast %"class.std::__1::basic_ostream"* %70 to i8**
  %72 = load i8*, i8** %71, align 8
  %73 = getelementptr i8, i8* %72, i64 -24
  %74 = bitcast i8* %73 to i64*
  %75 = load i64, i64* %74, align 8
  %76 = bitcast %"class.std::__1::basic_ostream"* %70 to i8*
  %77 = getelementptr inbounds i8, i8* %76, i64 %75
  %78 = bitcast i8* %77 to %"class.std::__1::basic_ios"*
  invoke void @_ZNSt3__19basic_iosIcNS_11char_traitsIcEEE8setstateEj(%"class.std::__1::basic_ios"* %78, i32 5)
          to label %79 unwind label %84

; <label>:79:                                     ; preds = %69
  br label %103

; <label>:80:                                     ; preds = %3
  %81 = landingpad { i8*, i32 }
          catch i8* null
  %82 = extractvalue { i8*, i32 } %81, 0
  store i8* %82, i8** %8, align 8
  %83 = extractvalue { i8*, i32 } %81, 1
  store i32 %83, i32* %9, align 4
  br label %88

; <label>:84:                                     ; preds = %69, %62, %38, %16, %13
  %85 = landingpad { i8*, i32 }
          catch i8* null
  %86 = extractvalue { i8*, i32 } %85, 0
  store i8* %86, i8** %8, align 8
  %87 = extractvalue { i8*, i32 } %85, 1
  store i32 %87, i32* %9, align 4
  call void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %7) #8
  br label %88

; <label>:88:                                     ; preds = %84, %80
  %89 = load i8*, i8** %8, align 8
  %90 = call i8* @__cxa_begin_catch(i8* %89) #8
  %91 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  %92 = bitcast %"class.std::__1::basic_ostream"* %91 to i8**
  %93 = load i8*, i8** %92, align 8
  %94 = getelementptr i8, i8* %93, i64 -24
  %95 = bitcast i8* %94 to i64*
  %96 = load i64, i64* %95, align 8
  %97 = bitcast %"class.std::__1::basic_ostream"* %91 to i8*
  %98 = getelementptr inbounds i8, i8* %97, i64 %96
  %99 = bitcast i8* %98 to %"class.std::__1::ios_base"*
  invoke void @_ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv(%"class.std::__1::ios_base"* %99)
          to label %100 unwind label %105

; <label>:100:                                    ; preds = %88
  call void @__cxa_end_catch()
  br label %101

; <label>:101:                                    ; preds = %100, %104
  %102 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  ret %"class.std::__1::basic_ostream"* %102

; <label>:103:                                    ; preds = %79, %66
  br label %104

; <label>:104:                                    ; preds = %103, %15
  call void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %7) #8
  br label %101

; <label>:105:                                    ; preds = %88
  %106 = landingpad { i8*, i32 }
          cleanup
  %107 = extractvalue { i8*, i32 } %106, 0
  store i8* %107, i8** %8, align 8
  %108 = extractvalue { i8*, i32 } %106, 1
  store i32 %108, i32* %9, align 4
  invoke void @__cxa_end_catch()
          to label %109 unwind label %115

; <label>:109:                                    ; preds = %105
  br label %110

; <label>:110:                                    ; preds = %109
  %111 = load i8*, i8** %8, align 8
  %112 = load i32, i32* %9, align 4
  %113 = insertvalue { i8*, i32 } undef, i8* %111, 0
  %114 = insertvalue { i8*, i32 } %113, i32 %112, 1
  resume { i8*, i32 } %114

; <label>:115:                                    ; preds = %105
  %116 = landingpad { i8*, i32 }
          catch i8* null
  %117 = extractvalue { i8*, i32 } %116, 0
  call void @__clang_call_terminate(i8* %117) #9
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr i64 @_ZNSt3__111char_traitsIcE6lengthEPKc(i8*) #4 align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = call i64 @strlen(i8* %3) #8
  ret i64 %4
}

declare void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryC1ERS3_(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"*, %"class.std::__1::basic_ostream"* dereferenceable(160)) unnamed_addr #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden zeroext i1 @_ZNKSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentrycvbEv(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"*) #4 align 2 {
  %2 = alloca %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"*, align 8
  store %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %0, %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"** %2, align 8
  %3 = load %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"*, %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry", %"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"* %3, i32 0, i32 0
  %5 = load i8, i8* %4, align 8
  %6 = trunc i8 %5 to i1
  ret i1 %6
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden %"class.std::__1::basic_streambuf"* @_ZNSt3__116__pad_and_outputIcNS_11char_traitsIcEEEENS_19ostreambuf_iteratorIT_T0_EES6_PKS4_S8_S8_RNS_8ios_baseES4_(%"class.std::__1::basic_streambuf"*, i8*, i8*, i8*, %"class.std::__1::ios_base"* dereferenceable(136), i8 signext) #1 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %7 = alloca %"class.std::__1::ostreambuf_iterator", align 8
  %8 = alloca %"class.std::__1::ostreambuf_iterator", align 8
  %9 = alloca i8*, align 8
  %10 = alloca i8*, align 8
  %11 = alloca i8*, align 8
  %12 = alloca %"class.std::__1::ios_base"*, align 8
  %13 = alloca i8, align 1
  %14 = alloca i64, align 8
  %15 = alloca i64, align 8
  %16 = alloca i64, align 8
  %17 = alloca %"class.std::__1::basic_string", align 8
  %18 = alloca i8*
  %19 = alloca i32
  %20 = alloca i32, align 4
  %21 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %8, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* %0, %"class.std::__1::basic_streambuf"** %21, align 8
  store i8* %1, i8** %9, align 8
  store i8* %2, i8** %10, align 8
  store i8* %3, i8** %11, align 8
  store %"class.std::__1::ios_base"* %4, %"class.std::__1::ios_base"** %12, align 8
  store i8 %5, i8* %13, align 1
  %22 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %8, i32 0, i32 0
  %23 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %22, align 8
  %24 = icmp eq %"class.std::__1::basic_streambuf"* %23, null
  br i1 %24, label %25, label %28

; <label>:25:                                     ; preds = %6
  %26 = bitcast %"class.std::__1::ostreambuf_iterator"* %7 to i8*
  %27 = bitcast %"class.std::__1::ostreambuf_iterator"* %8 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %26, i8* align 8 %27, i64 8, i1 false)
  br label %117

; <label>:28:                                     ; preds = %6
  %29 = load i8*, i8** %11, align 8
  %30 = load i8*, i8** %9, align 8
  %31 = ptrtoint i8* %29 to i64
  %32 = ptrtoint i8* %30 to i64
  %33 = sub i64 %31, %32
  store i64 %33, i64* %14, align 8
  %34 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %12, align 8
  %35 = call i64 @_ZNKSt3__18ios_base5widthEv(%"class.std::__1::ios_base"* %34)
  store i64 %35, i64* %15, align 8
  %36 = load i64, i64* %15, align 8
  %37 = load i64, i64* %14, align 8
  %38 = icmp sgt i64 %36, %37
  br i1 %38, label %39, label %43

; <label>:39:                                     ; preds = %28
  %40 = load i64, i64* %14, align 8
  %41 = load i64, i64* %15, align 8
  %42 = sub nsw i64 %41, %40
  store i64 %42, i64* %15, align 8
  br label %44

; <label>:43:                                     ; preds = %28
  store i64 0, i64* %15, align 8
  br label %44

; <label>:44:                                     ; preds = %43, %39
  %45 = load i8*, i8** %10, align 8
  %46 = load i8*, i8** %9, align 8
  %47 = ptrtoint i8* %45 to i64
  %48 = ptrtoint i8* %46 to i64
  %49 = sub i64 %47, %48
  store i64 %49, i64* %16, align 8
  %50 = load i64, i64* %16, align 8
  %51 = icmp sgt i64 %50, 0
  br i1 %51, label %52, label %65

; <label>:52:                                     ; preds = %44
  %53 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %8, i32 0, i32 0
  %54 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %53, align 8
  %55 = load i8*, i8** %9, align 8
  %56 = load i64, i64* %16, align 8
  %57 = call i64 @_ZNSt3__115basic_streambufIcNS_11char_traitsIcEEE5sputnEPKcl(%"class.std::__1::basic_streambuf"* %54, i8* %55, i64 %56)
  %58 = load i64, i64* %16, align 8
  %59 = icmp ne i64 %57, %58
  br i1 %59, label %60, label %64

; <label>:60:                                     ; preds = %52
  %61 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %8, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* null, %"class.std::__1::basic_streambuf"** %61, align 8
  %62 = bitcast %"class.std::__1::ostreambuf_iterator"* %7 to i8*
  %63 = bitcast %"class.std::__1::ostreambuf_iterator"* %8 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %62, i8* align 8 %63, i64 8, i1 false)
  br label %117

; <label>:64:                                     ; preds = %52
  br label %65

; <label>:65:                                     ; preds = %64, %44
  %66 = load i64, i64* %15, align 8
  %67 = icmp sgt i64 %66, 0
  br i1 %67, label %68, label %91

; <label>:68:                                     ; preds = %65
  %69 = load i64, i64* %15, align 8
  %70 = load i8, i8* %13, align 1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1Emc(%"class.std::__1::basic_string"* %17, i64 %69, i8 signext %70)
  %71 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %8, i32 0, i32 0
  %72 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %71, align 8
  %73 = call i8* @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE4dataEv(%"class.std::__1::basic_string"* %17) #8
  %74 = load i64, i64* %15, align 8
  %75 = invoke i64 @_ZNSt3__115basic_streambufIcNS_11char_traitsIcEEE5sputnEPKcl(%"class.std::__1::basic_streambuf"* %72, i8* %73, i64 %74)
          to label %76 unwind label %83

; <label>:76:                                     ; preds = %68
  %77 = load i64, i64* %15, align 8
  %78 = icmp ne i64 %75, %77
  br i1 %78, label %79, label %87

; <label>:79:                                     ; preds = %76
  %80 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %8, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* null, %"class.std::__1::basic_streambuf"** %80, align 8
  %81 = bitcast %"class.std::__1::ostreambuf_iterator"* %7 to i8*
  %82 = bitcast %"class.std::__1::ostreambuf_iterator"* %8 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %81, i8* align 8 %82, i64 8, i1 false)
  store i32 1, i32* %20, align 4
  br label %88

; <label>:83:                                     ; preds = %68
  %84 = landingpad { i8*, i32 }
          cleanup
  %85 = extractvalue { i8*, i32 } %84, 0
  store i8* %85, i8** %18, align 8
  %86 = extractvalue { i8*, i32 } %84, 1
  store i32 %86, i32* %19, align 4
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %17) #8
  br label %120

; <label>:87:                                     ; preds = %76
  store i32 0, i32* %20, align 4
  br label %88

; <label>:88:                                     ; preds = %87, %79
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEED1Ev(%"class.std::__1::basic_string"* %17) #8
  %89 = load i32, i32* %20, align 4
  switch i32 %89, label %125 [
    i32 0, label %90
    i32 1, label %117
  ]

; <label>:90:                                     ; preds = %88
  br label %91

; <label>:91:                                     ; preds = %90, %65
  %92 = load i8*, i8** %11, align 8
  %93 = load i8*, i8** %10, align 8
  %94 = ptrtoint i8* %92 to i64
  %95 = ptrtoint i8* %93 to i64
  %96 = sub i64 %94, %95
  store i64 %96, i64* %16, align 8
  %97 = load i64, i64* %16, align 8
  %98 = icmp sgt i64 %97, 0
  br i1 %98, label %99, label %112

; <label>:99:                                     ; preds = %91
  %100 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %8, i32 0, i32 0
  %101 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %100, align 8
  %102 = load i8*, i8** %10, align 8
  %103 = load i64, i64* %16, align 8
  %104 = call i64 @_ZNSt3__115basic_streambufIcNS_11char_traitsIcEEE5sputnEPKcl(%"class.std::__1::basic_streambuf"* %101, i8* %102, i64 %103)
  %105 = load i64, i64* %16, align 8
  %106 = icmp ne i64 %104, %105
  br i1 %106, label %107, label %111

; <label>:107:                                    ; preds = %99
  %108 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %8, i32 0, i32 0
  store %"class.std::__1::basic_streambuf"* null, %"class.std::__1::basic_streambuf"** %108, align 8
  %109 = bitcast %"class.std::__1::ostreambuf_iterator"* %7 to i8*
  %110 = bitcast %"class.std::__1::ostreambuf_iterator"* %8 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %109, i8* align 8 %110, i64 8, i1 false)
  br label %117

; <label>:111:                                    ; preds = %99
  br label %112

; <label>:112:                                    ; preds = %111, %91
  %113 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %12, align 8
  %114 = call i64 @_ZNSt3__18ios_base5widthEl(%"class.std::__1::ios_base"* %113, i64 0)
  %115 = bitcast %"class.std::__1::ostreambuf_iterator"* %7 to i8*
  %116 = bitcast %"class.std::__1::ostreambuf_iterator"* %8 to i8*
  call void @llvm.memcpy.p0i8.p0i8.i64(i8* align 8 %115, i8* align 8 %116, i64 8, i1 false)
  br label %117

; <label>:117:                                    ; preds = %112, %107, %88, %60, %25
  %118 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %7, i32 0, i32 0
  %119 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %118, align 8
  ret %"class.std::__1::basic_streambuf"* %119

; <label>:120:                                    ; preds = %83
  %121 = load i8*, i8** %18, align 8
  %122 = load i32, i32* %19, align 4
  %123 = insertvalue { i8*, i32 } undef, i8* %121, 0
  %124 = insertvalue { i8*, i32 } %123, i32 %122, 1
  resume { i8*, i32 } %124

; <label>:125:                                    ; preds = %88
  unreachable
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__119ostreambuf_iteratorIcNS_11char_traitsIcEEEC1ERNS_13basic_ostreamIcS2_EE(%"class.std::__1::ostreambuf_iterator"*, %"class.std::__1::basic_ostream"* dereferenceable(160)) unnamed_addr #4 align 2 {
  %3 = alloca %"class.std::__1::ostreambuf_iterator"*, align 8
  %4 = alloca %"class.std::__1::basic_ostream"*, align 8
  store %"class.std::__1::ostreambuf_iterator"* %0, %"class.std::__1::ostreambuf_iterator"** %3, align 8
  store %"class.std::__1::basic_ostream"* %1, %"class.std::__1::basic_ostream"** %4, align 8
  %5 = load %"class.std::__1::ostreambuf_iterator"*, %"class.std::__1::ostreambuf_iterator"** %3, align 8
  %6 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  call void @_ZNSt3__119ostreambuf_iteratorIcNS_11char_traitsIcEEEC2ERNS_13basic_ostreamIcS2_EE(%"class.std::__1::ostreambuf_iterator"* %5, %"class.std::__1::basic_ostream"* dereferenceable(160) %6) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i32 @_ZNKSt3__18ios_base5flagsEv(%"class.std::__1::ios_base"*) #4 align 2 {
  %2 = alloca %"class.std::__1::ios_base"*, align 8
  store %"class.std::__1::ios_base"* %0, %"class.std::__1::ios_base"** %2, align 8
  %3 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %3, i32 0, i32 1
  %5 = load i32, i32* %4, align 8
  ret i32 %5
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden signext i8 @_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE4fillEv(%"class.std::__1::basic_ios"*) #1 align 2 {
  %2 = alloca %"class.std::__1::basic_ios"*, align 8
  store %"class.std::__1::basic_ios"* %0, %"class.std::__1::basic_ios"** %2, align 8
  %3 = load %"class.std::__1::basic_ios"*, %"class.std::__1::basic_ios"** %2, align 8
  %4 = call i32 @_ZNSt3__111char_traitsIcE3eofEv() #8
  %5 = getelementptr inbounds %"class.std::__1::basic_ios", %"class.std::__1::basic_ios"* %3, i32 0, i32 2
  %6 = load i32, i32* %5, align 8
  %7 = call zeroext i1 @_ZNSt3__111char_traitsIcE11eq_int_typeEii(i32 %4, i32 %6) #8
  br i1 %7, label %8, label %12

; <label>:8:                                      ; preds = %1
  %9 = call signext i8 @_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc(%"class.std::__1::basic_ios"* %3, i8 signext 32)
  %10 = sext i8 %9 to i32
  %11 = getelementptr inbounds %"class.std::__1::basic_ios", %"class.std::__1::basic_ios"* %3, i32 0, i32 2
  store i32 %10, i32* %11, align 8
  br label %12

; <label>:12:                                     ; preds = %8, %1
  %13 = getelementptr inbounds %"class.std::__1::basic_ios", %"class.std::__1::basic_ios"* %3, i32 0, i32 2
  %14 = load i32, i32* %13, align 8
  %15 = trunc i32 %14 to i8
  ret i8 %15
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden zeroext i1 @_ZNKSt3__119ostreambuf_iteratorIcNS_11char_traitsIcEEE6failedEv(%"class.std::__1::ostreambuf_iterator"*) #4 align 2 {
  %2 = alloca %"class.std::__1::ostreambuf_iterator"*, align 8
  store %"class.std::__1::ostreambuf_iterator"* %0, %"class.std::__1::ostreambuf_iterator"** %2, align 8
  %3 = load %"class.std::__1::ostreambuf_iterator"*, %"class.std::__1::ostreambuf_iterator"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %3, i32 0, i32 0
  %5 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %4, align 8
  %6 = icmp eq %"class.std::__1::basic_streambuf"* %5, null
  ret i1 %6
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19basic_iosIcNS_11char_traitsIcEEE8setstateEj(%"class.std::__1::basic_ios"*, i32) #1 align 2 {
  %3 = alloca %"class.std::__1::basic_ios"*, align 8
  %4 = alloca i32, align 4
  store %"class.std::__1::basic_ios"* %0, %"class.std::__1::basic_ios"** %3, align 8
  store i32 %1, i32* %4, align 4
  %5 = load %"class.std::__1::basic_ios"*, %"class.std::__1::basic_ios"** %3, align 8
  %6 = bitcast %"class.std::__1::basic_ios"* %5 to %"class.std::__1::ios_base"*
  %7 = load i32, i32* %4, align 4
  call void @_ZNSt3__18ios_base8setstateEj(%"class.std::__1::ios_base"* %6, i32 %7)
  ret void
}

; Function Attrs: nounwind
declare void @_ZNSt3__113basic_ostreamIcNS_11char_traitsIcEEE6sentryD1Ev(%"class.std::__1::basic_ostream<char, std::__1::char_traits<char> >::sentry"*) unnamed_addr #2

declare void @_ZNSt3__18ios_base33__set_badbit_and_consider_rethrowEv(%"class.std::__1::ios_base"*) #3

declare void @__cxa_end_catch()

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i64 @_ZNKSt3__18ios_base5widthEv(%"class.std::__1::ios_base"*) #4 align 2 {
  %2 = alloca %"class.std::__1::ios_base"*, align 8
  store %"class.std::__1::ios_base"* %0, %"class.std::__1::ios_base"** %2, align 8
  %3 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %3, i32 0, i32 3
  %5 = load i64, i64* %4, align 8
  ret i64 %5
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden i64 @_ZNSt3__115basic_streambufIcNS_11char_traitsIcEEE5sputnEPKcl(%"class.std::__1::basic_streambuf"*, i8*, i64) #1 align 2 {
  %4 = alloca %"class.std::__1::basic_streambuf"*, align 8
  %5 = alloca i8*, align 8
  %6 = alloca i64, align 8
  store %"class.std::__1::basic_streambuf"* %0, %"class.std::__1::basic_streambuf"** %4, align 8
  store i8* %1, i8** %5, align 8
  store i64 %2, i64* %6, align 8
  %7 = load %"class.std::__1::basic_streambuf"*, %"class.std::__1::basic_streambuf"** %4, align 8
  %8 = load i8*, i8** %5, align 8
  %9 = load i64, i64* %6, align 8
  %10 = bitcast %"class.std::__1::basic_streambuf"* %7 to i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)***
  %11 = load i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)**, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*** %10, align 8
  %12 = getelementptr inbounds i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)** %11, i64 12
  %13 = load i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)*, i64 (%"class.std::__1::basic_streambuf"*, i8*, i64)** %12, align 8
  %14 = call i64 %13(%"class.std::__1::basic_streambuf"* %7, i8* %8, i64 %9)
  ret i64 %14
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC1Emc(%"class.std::__1::basic_string"*, i64, i8 signext) unnamed_addr #1 align 2 {
  %4 = alloca %"class.std::__1::basic_string"*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i8, align 1
  store %"class.std::__1::basic_string"* %0, %"class.std::__1::basic_string"** %4, align 8
  store i64 %1, i64* %5, align 8
  store i8 %2, i8* %6, align 1
  %7 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %4, align 8
  %8 = load i64, i64* %5, align 8
  %9 = load i8, i8* %6, align 1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2Emc(%"class.std::__1::basic_string"* %7, i64 %8, i8 signext %9)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i8* @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE4dataEv(%"class.std::__1::basic_string"*) #4 align 2 {
  %2 = alloca %"class.std::__1::basic_string"*, align 8
  store %"class.std::__1::basic_string"* %0, %"class.std::__1::basic_string"** %2, align 8
  %3 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %2, align 8
  %4 = call i8* @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE13__get_pointerEv(%"class.std::__1::basic_string"* %3) #8
  %5 = call i8* @_ZNSt3__116__to_raw_pointerIcEEPT_S2_(i8* %4) #8
  ret i8* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i64 @_ZNSt3__18ios_base5widthEl(%"class.std::__1::ios_base"*, i64) #4 align 2 {
  %3 = alloca %"class.std::__1::ios_base"*, align 8
  %4 = alloca i64, align 8
  %5 = alloca i64, align 8
  store %"class.std::__1::ios_base"* %0, %"class.std::__1::ios_base"** %3, align 8
  store i64 %1, i64* %4, align 8
  %6 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %3, align 8
  %7 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %6, i32 0, i32 3
  %8 = load i64, i64* %7, align 8
  store i64 %8, i64* %5, align 8
  %9 = load i64, i64* %4, align 8
  %10 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %6, i32 0, i32 3
  store i64 %9, i64* %10, align 8
  %11 = load i64, i64* %5, align 8
  ret i64 %11
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2Emc(%"class.std::__1::basic_string"*, i64, i8 signext) unnamed_addr #1 align 2 {
  %4 = alloca %"class.std::__1::basic_string"*, align 8
  %5 = alloca i64, align 8
  %6 = alloca i8, align 1
  store %"class.std::__1::basic_string"* %0, %"class.std::__1::basic_string"** %4, align 8
  store i64 %1, i64* %5, align 8
  store i8 %2, i8* %6, align 1
  %7 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %4, align 8
  %8 = bitcast %"class.std::__1::basic_string"* %7 to %"class.std::__1::__basic_string_common"*
  %9 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %7, i32 0, i32 0
  call void @_ZNSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_EC1ILb1EvEEv(%"class.std::__1::__compressed_pair.18"* %9)
  %10 = load i64, i64* %5, align 8
  %11 = load i8, i8* %6, align 1
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEmc(%"class.std::__1::basic_string"* %7, i64 %10, i8 signext %11)
  ret void
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_EC1ILb1EvEEv(%"class.std::__1::__compressed_pair.18"*) unnamed_addr #1 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.18"*, align 8
  store %"class.std::__1::__compressed_pair.18"* %0, %"class.std::__1::__compressed_pair.18"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.18"*, %"class.std::__1::__compressed_pair.18"** %2, align 8
  call void @_ZNSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_EC2ILb1EvEEv(%"class.std::__1::__compressed_pair.18"* %3)
  ret void
}

declare void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEmc(%"class.std::__1::basic_string"*, i64, i8 signext) #3

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_EC2ILb1EvEEv(%"class.std::__1::__compressed_pair.18"*) unnamed_addr #1 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.18"*, align 8
  store %"class.std::__1::__compressed_pair.18"* %0, %"class.std::__1::__compressed_pair.18"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.18"*, %"class.std::__1::__compressed_pair.18"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.18"* %3 to %"struct.std::__1::__compressed_pair_elem.19"*
  call void @_ZNSt3__122__compressed_pair_elemINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repELi0ELb0EEC2Ev(%"struct.std::__1::__compressed_pair_elem.19"* %4)
  %5 = bitcast %"class.std::__1::__compressed_pair.18"* %3 to %"struct.std::__1::__compressed_pair_elem.21"*
  call void @_ZNSt3__122__compressed_pair_elemINS_9allocatorIcEELi1ELb1EEC2Ev(%"struct.std::__1::__compressed_pair_elem.21"* %5) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__122__compressed_pair_elemINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repELi0ELb0EEC2Ev(%"struct.std::__1::__compressed_pair_elem.19"*) unnamed_addr #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.19"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.19"* %0, %"struct.std::__1::__compressed_pair_elem.19"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.19"*, %"struct.std::__1::__compressed_pair_elem.19"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.19", %"struct.std::__1::__compressed_pair_elem.19"* %3, i32 0, i32 0
  %5 = bitcast %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %4 to i8*
  call void @llvm.memset.p0i8.i64(i8* align 8 %5, i8 0, i64 24, i1 false)
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__122__compressed_pair_elemINS_9allocatorIcEELi1ELb1EEC2Ev(%"struct.std::__1::__compressed_pair_elem.21"*) unnamed_addr #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.21"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.21"* %0, %"struct.std::__1::__compressed_pair_elem.21"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.21"*, %"struct.std::__1::__compressed_pair_elem.21"** %2, align 8
  %4 = bitcast %"struct.std::__1::__compressed_pair_elem.21"* %3 to %"class.std::__1::allocator.22"*
  call void @_ZNSt3__19allocatorIcEC2Ev(%"class.std::__1::allocator.22"* %4) #8
  ret void
}

; Function Attrs: argmemonly nounwind
declare void @llvm.memset.p0i8.i64(i8* nocapture writeonly, i8, i64, i1) #5

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__19allocatorIcEC2Ev(%"class.std::__1::allocator.22"*) unnamed_addr #4 align 2 {
  %2 = alloca %"class.std::__1::allocator.22"*, align 8
  store %"class.std::__1::allocator.22"* %0, %"class.std::__1::allocator.22"** %2, align 8
  %3 = load %"class.std::__1::allocator.22"*, %"class.std::__1::allocator.22"** %2, align 8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i8* @_ZNSt3__116__to_raw_pointerIcEEPT_S2_(i8*) #4 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  ret i8* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i8* @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE13__get_pointerEv(%"class.std::__1::basic_string"*) #4 align 2 {
  %2 = alloca %"class.std::__1::basic_string"*, align 8
  store %"class.std::__1::basic_string"* %0, %"class.std::__1::basic_string"** %2, align 8
  %3 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %2, align 8
  %4 = call zeroext i1 @_ZNKSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE9__is_longEv(%"class.std::__1::basic_string"* %3) #8
  br i1 %4, label %5, label %7

; <label>:5:                                      ; preds = %1
  %6 = call i8* @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE18__get_long_pointerEv(%"class.std::__1::basic_string"* %3) #8
  br label %9

; <label>:7:                                      ; preds = %1
  %8 = call i8* @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE19__get_short_pointerEv(%"class.std::__1::basic_string"* %3) #8
  br label %9

; <label>:9:                                      ; preds = %7, %5
  %10 = phi i8* [ %6, %5 ], [ %8, %7 ]
  ret i8* %10
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden zeroext i1 @_ZNKSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE9__is_longEv(%"class.std::__1::basic_string"*) #4 align 2 {
  %2 = alloca %"class.std::__1::basic_string"*, align 8
  store %"class.std::__1::basic_string"* %0, %"class.std::__1::basic_string"** %2, align 8
  %3 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %3, i32 0, i32 0
  %5 = call dereferenceable(24) %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* @_ZNKSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_E5firstEv(%"class.std::__1::__compressed_pair.18"* %4) #8
  %6 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %5, i32 0, i32 0
  %7 = bitcast %union.anon* %6 to %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short"*
  %8 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short"* %7, i32 0, i32 0
  %9 = bitcast %union.anon.20* %8 to i8*
  %10 = load i8, i8* %9, align 8
  %11 = zext i8 %10 to i64
  %12 = and i64 %11, 1
  %13 = icmp ne i64 %12, 0
  ret i1 %13
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i8* @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE18__get_long_pointerEv(%"class.std::__1::basic_string"*) #4 align 2 {
  %2 = alloca %"class.std::__1::basic_string"*, align 8
  store %"class.std::__1::basic_string"* %0, %"class.std::__1::basic_string"** %2, align 8
  %3 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %3, i32 0, i32 0
  %5 = call dereferenceable(24) %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* @_ZNSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_E5firstEv(%"class.std::__1::__compressed_pair.18"* %4) #8
  %6 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %5, i32 0, i32 0
  %7 = bitcast %union.anon* %6 to %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long"*
  %8 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__long"* %7, i32 0, i32 2
  %9 = load i8*, i8** %8, align 8
  ret i8* %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i8* @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE19__get_short_pointerEv(%"class.std::__1::basic_string"*) #4 align 2 {
  %2 = alloca %"class.std::__1::basic_string"*, align 8
  store %"class.std::__1::basic_string"* %0, %"class.std::__1::basic_string"** %2, align 8
  %3 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %3, i32 0, i32 0
  %5 = call dereferenceable(24) %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* @_ZNSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_E5firstEv(%"class.std::__1::__compressed_pair.18"* %4) #8
  %6 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %5, i32 0, i32 0
  %7 = bitcast %union.anon* %6 to %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short"*
  %8 = getelementptr inbounds %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short", %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__short"* %7, i32 0, i32 1
  %9 = getelementptr inbounds [23 x i8], [23 x i8]* %8, i64 0, i64 0
  %10 = call i8* @_ZNSt3__114pointer_traitsIPcE10pointer_toERc(i8* dereferenceable(1) %9) #8
  ret i8* %10
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(24) %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* @_ZNKSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_E5firstEv(%"class.std::__1::__compressed_pair.18"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.18"*, align 8
  store %"class.std::__1::__compressed_pair.18"* %0, %"class.std::__1::__compressed_pair.18"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.18"*, %"class.std::__1::__compressed_pair.18"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.18"* %3 to %"struct.std::__1::__compressed_pair_elem.19"*
  %5 = call dereferenceable(24) %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* @_ZNKSt3__122__compressed_pair_elemINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.19"* %4) #8
  ret %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(24) %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* @_ZNKSt3__122__compressed_pair_elemINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.19"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.19"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.19"* %0, %"struct.std::__1::__compressed_pair_elem.19"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.19"*, %"struct.std::__1::__compressed_pair_elem.19"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.19", %"struct.std::__1::__compressed_pair_elem.19"* %3, i32 0, i32 0
  ret %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(24) %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* @_ZNSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_E5firstEv(%"class.std::__1::__compressed_pair.18"*) #4 align 2 {
  %2 = alloca %"class.std::__1::__compressed_pair.18"*, align 8
  store %"class.std::__1::__compressed_pair.18"* %0, %"class.std::__1::__compressed_pair.18"** %2, align 8
  %3 = load %"class.std::__1::__compressed_pair.18"*, %"class.std::__1::__compressed_pair.18"** %2, align 8
  %4 = bitcast %"class.std::__1::__compressed_pair.18"* %3 to %"struct.std::__1::__compressed_pair_elem.19"*
  %5 = call dereferenceable(24) %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* @_ZNSt3__122__compressed_pair_elemINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.19"* %4) #8
  ret %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden dereferenceable(24) %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* @_ZNSt3__122__compressed_pair_elemINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repELi0ELb0EE5__getEv(%"struct.std::__1::__compressed_pair_elem.19"*) #4 align 2 {
  %2 = alloca %"struct.std::__1::__compressed_pair_elem.19"*, align 8
  store %"struct.std::__1::__compressed_pair_elem.19"* %0, %"struct.std::__1::__compressed_pair_elem.19"** %2, align 8
  %3 = load %"struct.std::__1::__compressed_pair_elem.19"*, %"struct.std::__1::__compressed_pair_elem.19"** %2, align 8
  %4 = getelementptr inbounds %"struct.std::__1::__compressed_pair_elem.19", %"struct.std::__1::__compressed_pair_elem.19"* %3, i32 0, i32 0
  ret %"struct.std::__1::basic_string<char, std::__1::char_traits<char>, std::__1::allocator<char> >::__rep"* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i8* @_ZNSt3__114pointer_traitsIPcE10pointer_toERc(i8* dereferenceable(1)) #4 align 2 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  %4 = call i8* @_ZNSt3__19addressofIcEEPT_RS1_(i8* dereferenceable(1) %3) #8
  ret i8* %4
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i8* @_ZNSt3__19addressofIcEEPT_RS1_(i8* dereferenceable(1)) #4 {
  %2 = alloca i8*, align 8
  store i8* %0, i8** %2, align 8
  %3 = load i8*, i8** %2, align 8
  ret i8* %3
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__119ostreambuf_iteratorIcNS_11char_traitsIcEEEC2ERNS_13basic_ostreamIcS2_EE(%"class.std::__1::ostreambuf_iterator"*, %"class.std::__1::basic_ostream"* dereferenceable(160)) unnamed_addr #4 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::__1::ostreambuf_iterator"*, align 8
  %4 = alloca %"class.std::__1::basic_ostream"*, align 8
  store %"class.std::__1::ostreambuf_iterator"* %0, %"class.std::__1::ostreambuf_iterator"** %3, align 8
  store %"class.std::__1::basic_ostream"* %1, %"class.std::__1::basic_ostream"** %4, align 8
  %5 = load %"class.std::__1::ostreambuf_iterator"*, %"class.std::__1::ostreambuf_iterator"** %3, align 8
  %6 = bitcast %"class.std::__1::ostreambuf_iterator"* %5 to %"struct.std::__1::iterator"*
  %7 = getelementptr inbounds %"class.std::__1::ostreambuf_iterator", %"class.std::__1::ostreambuf_iterator"* %5, i32 0, i32 0
  %8 = load %"class.std::__1::basic_ostream"*, %"class.std::__1::basic_ostream"** %4, align 8
  %9 = bitcast %"class.std::__1::basic_ostream"* %8 to i8**
  %10 = load i8*, i8** %9, align 8
  %11 = getelementptr i8, i8* %10, i64 -24
  %12 = bitcast i8* %11 to i64*
  %13 = load i64, i64* %12, align 8
  %14 = bitcast %"class.std::__1::basic_ostream"* %8 to i8*
  %15 = getelementptr inbounds i8, i8* %14, i64 %13
  %16 = bitcast i8* %15 to %"class.std::__1::basic_ios"*
  %17 = invoke %"class.std::__1::basic_streambuf"* @_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5rdbufEv(%"class.std::__1::basic_ios"* %16)
          to label %18 unwind label %19

; <label>:18:                                     ; preds = %2
  store %"class.std::__1::basic_streambuf"* %17, %"class.std::__1::basic_streambuf"** %7, align 8
  ret void

; <label>:19:                                     ; preds = %2
  %20 = landingpad { i8*, i32 }
          catch i8* null
  %21 = extractvalue { i8*, i32 } %20, 0
  call void @__clang_call_terminate(i8* %21) #9
  unreachable
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden %"class.std::__1::basic_streambuf"* @_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5rdbufEv(%"class.std::__1::basic_ios"*) #1 align 2 {
  %2 = alloca %"class.std::__1::basic_ios"*, align 8
  store %"class.std::__1::basic_ios"* %0, %"class.std::__1::basic_ios"** %2, align 8
  %3 = load %"class.std::__1::basic_ios"*, %"class.std::__1::basic_ios"** %2, align 8
  %4 = bitcast %"class.std::__1::basic_ios"* %3 to %"class.std::__1::ios_base"*
  %5 = call i8* @_ZNKSt3__18ios_base5rdbufEv(%"class.std::__1::ios_base"* %4)
  %6 = bitcast i8* %5 to %"class.std::__1::basic_streambuf"*
  ret %"class.std::__1::basic_streambuf"* %6
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden i8* @_ZNKSt3__18ios_base5rdbufEv(%"class.std::__1::ios_base"*) #4 align 2 {
  %2 = alloca %"class.std::__1::ios_base"*, align 8
  store %"class.std::__1::ios_base"* %0, %"class.std::__1::ios_base"** %2, align 8
  %3 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %2, align 8
  %4 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %3, i32 0, i32 6
  %5 = load i8*, i8** %4, align 8
  ret i8* %5
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr zeroext i1 @_ZNSt3__111char_traitsIcE11eq_int_typeEii(i32, i32) #4 align 2 {
  %3 = alloca i32, align 4
  %4 = alloca i32, align 4
  store i32 %0, i32* %3, align 4
  store i32 %1, i32* %4, align 4
  %5 = load i32, i32* %3, align 4
  %6 = load i32, i32* %4, align 4
  %7 = icmp eq i32 %5, %6
  ret i1 %7
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr i32 @_ZNSt3__111char_traitsIcE3eofEv() #4 align 2 {
  ret i32 -1
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden signext i8 @_ZNKSt3__19basic_iosIcNS_11char_traitsIcEEE5widenEc(%"class.std::__1::basic_ios"*, i8 signext) #1 align 2 personality i8* bitcast (i32 (...)* @__gxx_personality_v0 to i8*) {
  %3 = alloca %"class.std::__1::basic_ios"*, align 8
  %4 = alloca i8, align 1
  %5 = alloca %"class.std::__1::locale", align 8
  %6 = alloca i8*
  %7 = alloca i32
  store %"class.std::__1::basic_ios"* %0, %"class.std::__1::basic_ios"** %3, align 8
  store i8 %1, i8* %4, align 1
  %8 = load %"class.std::__1::basic_ios"*, %"class.std::__1::basic_ios"** %3, align 8
  %9 = bitcast %"class.std::__1::basic_ios"* %8 to %"class.std::__1::ios_base"*
  call void @_ZNKSt3__18ios_base6getlocEv(%"class.std::__1::locale"* sret %5, %"class.std::__1::ios_base"* %9)
  %10 = invoke dereferenceable(32) %"class.std::__1::ctype"* @_ZNSt3__19use_facetINS_5ctypeIcEEEERKT_RKNS_6localeE(%"class.std::__1::locale"* dereferenceable(8) %5)
          to label %11 unwind label %15

; <label>:11:                                     ; preds = %2
  %12 = load i8, i8* %4, align 1
  %13 = invoke signext i8 @_ZNKSt3__15ctypeIcE5widenEc(%"class.std::__1::ctype"* %10, i8 signext %12)
          to label %14 unwind label %15

; <label>:14:                                     ; preds = %11
  call void @_ZNSt3__16localeD1Ev(%"class.std::__1::locale"* %5) #8
  ret i8 %13

; <label>:15:                                     ; preds = %11, %2
  %16 = landingpad { i8*, i32 }
          cleanup
  %17 = extractvalue { i8*, i32 } %16, 0
  store i8* %17, i8** %6, align 8
  %18 = extractvalue { i8*, i32 } %16, 1
  store i32 %18, i32* %7, align 4
  call void @_ZNSt3__16localeD1Ev(%"class.std::__1::locale"* %5) #8
  br label %19

; <label>:19:                                     ; preds = %15
  %20 = load i8*, i8** %6, align 8
  %21 = load i32, i32* %7, align 4
  %22 = insertvalue { i8*, i32 } undef, i8* %20, 0
  %23 = insertvalue { i8*, i32 } %22, i32 %21, 1
  resume { i8*, i32 } %23
}

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden dereferenceable(32) %"class.std::__1::ctype"* @_ZNSt3__19use_facetINS_5ctypeIcEEEERKT_RKNS_6localeE(%"class.std::__1::locale"* dereferenceable(8)) #1 {
  %2 = alloca %"class.std::__1::locale"*, align 8
  store %"class.std::__1::locale"* %0, %"class.std::__1::locale"** %2, align 8
  %3 = load %"class.std::__1::locale"*, %"class.std::__1::locale"** %2, align 8
  %4 = call %"class.std::__1::locale::facet"* @_ZNKSt3__16locale9use_facetERNS0_2idE(%"class.std::__1::locale"* %3, %"class.std::__1::locale::id"* dereferenceable(16) @_ZNSt3__15ctypeIcE2idE)
  %5 = bitcast %"class.std::__1::locale::facet"* %4 to %"class.std::__1::ctype"*
  ret %"class.std::__1::ctype"* %5
}

declare void @_ZNKSt3__18ios_base6getlocEv(%"class.std::__1::locale"* sret, %"class.std::__1::ios_base"*) #3

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden signext i8 @_ZNKSt3__15ctypeIcE5widenEc(%"class.std::__1::ctype"*, i8 signext) #1 align 2 {
  %3 = alloca %"class.std::__1::ctype"*, align 8
  %4 = alloca i8, align 1
  store %"class.std::__1::ctype"* %0, %"class.std::__1::ctype"** %3, align 8
  store i8 %1, i8* %4, align 1
  %5 = load %"class.std::__1::ctype"*, %"class.std::__1::ctype"** %3, align 8
  %6 = load i8, i8* %4, align 1
  %7 = bitcast %"class.std::__1::ctype"* %5 to i8 (%"class.std::__1::ctype"*, i8)***
  %8 = load i8 (%"class.std::__1::ctype"*, i8)**, i8 (%"class.std::__1::ctype"*, i8)*** %7, align 8
  %9 = getelementptr inbounds i8 (%"class.std::__1::ctype"*, i8)*, i8 (%"class.std::__1::ctype"*, i8)** %8, i64 7
  %10 = load i8 (%"class.std::__1::ctype"*, i8)*, i8 (%"class.std::__1::ctype"*, i8)** %9, align 8
  %11 = call signext i8 %10(%"class.std::__1::ctype"* %5, i8 signext %6)
  ret i8 %11
}

; Function Attrs: nounwind
declare void @_ZNSt3__16localeD1Ev(%"class.std::__1::locale"*) unnamed_addr #2

declare %"class.std::__1::locale::facet"* @_ZNKSt3__16locale9use_facetERNS0_2idE(%"class.std::__1::locale"*, %"class.std::__1::locale::id"* dereferenceable(16)) #3

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__18ios_base8setstateEj(%"class.std::__1::ios_base"*, i32) #1 align 2 {
  %3 = alloca %"class.std::__1::ios_base"*, align 8
  %4 = alloca i32, align 4
  store %"class.std::__1::ios_base"* %0, %"class.std::__1::ios_base"** %3, align 8
  store i32 %1, i32* %4, align 4
  %5 = load %"class.std::__1::ios_base"*, %"class.std::__1::ios_base"** %3, align 8
  %6 = getelementptr inbounds %"class.std::__1::ios_base", %"class.std::__1::ios_base"* %5, i32 0, i32 4
  %7 = load i32, i32* %6, align 8
  %8 = load i32, i32* %4, align 4
  %9 = or i32 %7, %8
  call void @_ZNSt3__18ios_base5clearEj(%"class.std::__1::ios_base"* %5, i32 %9)
  ret void
}

declare void @_ZNSt3__18ios_base5clearEj(%"class.std::__1::ios_base"*, i32) #3

; Function Attrs: nounwind
declare i64 @strlen(i8*) #2

; Function Attrs: noinline optnone ssp uwtable
define linkonce_odr void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEEC2IDnEEPKc(%"class.std::__1::basic_string"*, i8*) unnamed_addr #1 align 2 {
  %3 = alloca %"class.std::__1::basic_string"*, align 8
  %4 = alloca i8*, align 8
  store %"class.std::__1::basic_string"* %0, %"class.std::__1::basic_string"** %3, align 8
  store i8* %1, i8** %4, align 8
  %5 = load %"class.std::__1::basic_string"*, %"class.std::__1::basic_string"** %3, align 8
  %6 = bitcast %"class.std::__1::basic_string"* %5 to %"class.std::__1::__basic_string_common"*
  %7 = getelementptr inbounds %"class.std::__1::basic_string", %"class.std::__1::basic_string"* %5, i32 0, i32 0
  call void @_ZNSt3__117__compressed_pairINS_12basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE5__repES5_EC1ILb1EvEEv(%"class.std::__1::__compressed_pair.18"* %7)
  %8 = load i8*, i8** %4, align 8
  %9 = load i8*, i8** %4, align 8
  %10 = call i64 @_ZNSt3__111char_traitsIcE6lengthEPKc(i8* %9) #8
  call void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm(%"class.std::__1::basic_string"* %5, i8* %8, i64 %10)
  ret void
}

declare void @_ZNSt3__112basic_stringIcNS_11char_traitsIcEENS_9allocatorIcEEE6__initEPKcm(%"class.std::__1::basic_string"*, i8*, i64) #3

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden %"struct.std::__1::pair"* @_ZNSt3__16vectorINS_4pairIRN4LL2W4NodeES4_EENS_9allocatorIS5_EEE11__make_iterEPS5_(%"class.std::__1::vector"*, %"struct.std::__1::pair"*) #4 align 2 {
  %3 = alloca %"class.std::__1::__wrap_iter", align 8
  %4 = alloca %"class.std::__1::vector"*, align 8
  %5 = alloca %"struct.std::__1::pair"*, align 8
  store %"class.std::__1::vector"* %0, %"class.std::__1::vector"** %4, align 8
  store %"struct.std::__1::pair"* %1, %"struct.std::__1::pair"** %5, align 8
  %6 = load %"class.std::__1::vector"*, %"class.std::__1::vector"** %4, align 8
  %7 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %5, align 8
  call void @_ZNSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEEC1ES6_(%"class.std::__1::__wrap_iter"* %3, %"struct.std::__1::pair"* %7) #8
  %8 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %3, i32 0, i32 0
  %9 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %8, align 8
  ret %"struct.std::__1::pair"* %9
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEEC1ES6_(%"class.std::__1::__wrap_iter"*, %"struct.std::__1::pair"*) unnamed_addr #4 align 2 {
  %3 = alloca %"class.std::__1::__wrap_iter"*, align 8
  %4 = alloca %"struct.std::__1::pair"*, align 8
  store %"class.std::__1::__wrap_iter"* %0, %"class.std::__1::__wrap_iter"** %3, align 8
  store %"struct.std::__1::pair"* %1, %"struct.std::__1::pair"** %4, align 8
  %5 = load %"class.std::__1::__wrap_iter"*, %"class.std::__1::__wrap_iter"** %3, align 8
  %6 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  call void @_ZNSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEEC2ES6_(%"class.std::__1::__wrap_iter"* %5, %"struct.std::__1::pair"* %6) #8
  ret void
}

; Function Attrs: noinline nounwind optnone ssp uwtable
define linkonce_odr hidden void @_ZNSt3__111__wrap_iterIPNS_4pairIRN4LL2W4NodeES4_EEEC2ES6_(%"class.std::__1::__wrap_iter"*, %"struct.std::__1::pair"*) unnamed_addr #4 align 2 {
  %3 = alloca %"class.std::__1::__wrap_iter"*, align 8
  %4 = alloca %"struct.std::__1::pair"*, align 8
  store %"class.std::__1::__wrap_iter"* %0, %"class.std::__1::__wrap_iter"** %3, align 8
  store %"struct.std::__1::pair"* %1, %"struct.std::__1::pair"** %4, align 8
  %5 = load %"class.std::__1::__wrap_iter"*, %"class.std::__1::__wrap_iter"** %3, align 8
  %6 = getelementptr inbounds %"class.std::__1::__wrap_iter", %"class.std::__1::__wrap_iter"* %5, i32 0, i32 0
  %7 = load %"struct.std::__1::pair"*, %"struct.std::__1::pair"** %4, align 8
  store %"struct.std::__1::pair"* %7, %"struct.std::__1::pair"** %6, align 8
  ret void
}

attributes #0 = { noinline norecurse optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #1 = { noinline optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #2 = { nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #3 = { "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #4 = { noinline nounwind optnone ssp uwtable "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "min-legal-vector-width"="0" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-jump-tables"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #5 = { argmemonly nounwind }
attributes #6 = { noinline noreturn nounwind }
attributes #7 = { nobuiltin nounwind "correctly-rounded-divide-sqrt-fp-math"="false" "disable-tail-calls"="false" "less-precise-fpmad"="false" "no-frame-pointer-elim"="true" "no-frame-pointer-elim-non-leaf" "no-infs-fp-math"="false" "no-nans-fp-math"="false" "no-signed-zeros-fp-math"="false" "no-trapping-math"="false" "stack-protector-buffer-size"="8" "target-cpu"="penryn" "target-features"="+cx16,+fxsr,+mmx,+sahf,+sse,+sse2,+sse3,+sse4.1,+ssse3,+x87" "unsafe-fp-math"="false" "use-soft-float"="false" }
attributes #8 = { nounwind }
attributes #9 = { noreturn nounwind }
attributes #10 = { builtin nounwind }

!llvm.module.flags = !{!0, !1, !2}
!llvm.ident = !{!3}

!0 = !{i32 2, !"SDK Version", [2 x i32] [i32 10, i32 15]}
!1 = !{i32 1, !"wchar_size", i32 4}
!2 = !{i32 7, !"PIC Level", i32 2}
!3 = !{!"clang version 8.0.1 (tags/RELEASE_801/final)"}

;*/
