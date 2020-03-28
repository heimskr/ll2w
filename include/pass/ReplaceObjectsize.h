#ifndef PASS_REPLACEOBJECTSIZE_H_
#define PASS_REPLACEOBJECTSIZE_H_

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Replaces the @llvm.objectsize.* intrinsic with set instructions. */
	int replaceObjectsize(Function &);
}

#endif
