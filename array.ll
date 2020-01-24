define void @foo() {
	%res = landingpad { i8*, i32 } catch i8** @_ZTIi filter [1 x i8**] [@_ZTId, i32 1]
}
