@foo = unnamed_addr constant { [6 x i8*] } {
    [6 x i8*] [
        i8* null,
        i8* bitcast ({ i8*, i8*, i8* }* @bar to i8*),
        i8* bitcast (void (%"struct.LL2W::SelectNode"*)* @baz to i8*),
        i8* bitcast (void (%"struct.LL2W::SelectNode"*)* @quux to i8*),
        i8* bitcast (void (%"class.std::__1::basic_string"*, %"struct.LL2W::SelectNode"*)* @quack to i8*),
        i8* bitcast (void (%"class.std::__1::basic_string"*, %"struct.LL2W::InstructionNode"*)* @honk to i8*)
    ]
}, align 8
