#include "compiler/Variable.h"
#include "instruction/Clobber.h"

namespace LL2W {
	std::shared_ptr<SemiUnclobber> Clobber::makeSemi(const VariablePtr &destination) {
		auto out = SemiUnclobber::make(reg, nullptr, destination);
		semis.emplace_back(out);
		return out;
	}

	std::string SemiUnclobber::toString() const {
		if (source)
			return "\e[33msemiunclobber\e[39m " + std::string(*source) + " into " + std::string(*destination);
		return "\e[33msemiunclobber\e[32m $" + WhyInfo::registerName(reg) + "\e[39m into " + std::string(*destination);
	}

	ExtractionResult SemiUnclobber::extract(bool force) {
		if (extracted && !force)
			return {read.size(), written.size()};

		read.clear();
		written.clear();
		extracted = true;

		if (!secretWrites && destination)
			written.insert(destination);

		if (!secretReads && source)
			read.insert(source);

		return {read.size(), written.size()};
	}

	std::pair<int, int> SemiUnclobber::extractPrecolored() {
		precoloredWritten = {destination->registers.cbegin(), destination->registers.cend()};
		return {0, precoloredWritten.size()};
	}
}
