#pragma once

#include <string>

namespace LL2W {
	struct File {
		std::string filename, directory;
		File() = delete;
		File(const std::string &filename_, const std::string &directory_): filename(filename_), directory(directory_) {}
	};
}
