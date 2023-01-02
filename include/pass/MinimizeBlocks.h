#pragma once

namespace LL2W {
	class Function;
}

namespace LL2W::Passes {
	/** Recomputes basic blocks such that each basic block contains exactly one instruction. Useful before liveness
	 *  analysis. */
	void minimizeBlocks(Function &, bool remake_cfg = true);
}
