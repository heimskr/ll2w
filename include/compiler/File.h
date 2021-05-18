#pragma once

#include <string>

namespace LL2W {
	struct File {
		std::string filename, directory;
		/** The index of the file within the debug data section, not within the LLVM IR. */
		int index = -1;
		File() = delete;
		File(const std::string &filename_, const std::string &directory_): filename(filename_), directory(directory_) {}
	};
}
