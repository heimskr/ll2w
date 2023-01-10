#include "util/Deleter.h"
#include "util/Util.h"

#include <execinfo.h>
#include <climits>
#include <cstdlib>
#include <span>
#include <stdexcept>

namespace LL2W::Util {
	long parseLong(const std::string &str, int base) {
		const char *c_str = str.c_str();
		char *end;
		long parsed = strtol(c_str, &end, base);
		if (c_str + str.length() != end)
			throw std::invalid_argument("Not an integer: \"" + str + '"');
		return parsed;
	}

	long parseLong(const std::string *str, int base) {
		return parseLong(*str, base);
	}

	long parseLong(const char *str, int base) {
		return parseLong(std::string(str), base);
	}

	struct FILE_deleter {
		void operator()(FILE *file) {
			pclose(file);
		}
	};

	std::string getExecutablePath() {
		// Credit: https://stackoverflow.com/q/51891987/227663
		std::array<char, PATH_MAX> out;
		const ssize_t count = readlink("/proc/self/exe", out.data(), PATH_MAX);
		return std::string(out.data(), 0 < count? count : 0);
	}


	std::string readAll(std::string_view command) {
		// Credit: https://stackoverflow.com/q/51891987/227663
		std::array<char, 128> buffer;
		std::string result;
		std::unique_ptr<FILE, FILE_deleter> file(popen(command.data(), "r"));
		if (!file)
			throw std::runtime_error("popen() failed");
		while (feof(file.get()) == 0)
			if (fgets(buffer.data(), 128, file.get()) != nullptr)
				result += buffer.data();
		return result;
	}

	std::vector<std::string> getBacktrace() {
		std::array<void *, 16> data;
		size_t size = backtrace(data.data(), 16);
		std::vector<std::string> out;
		constexpr size_t ignore = 2;
		auto span = std::span(data).subspan(ignore);
		size -= ignore;
		char **lines = backtrace_symbols(span.data(), size);
		Deleter deleter(lines);
		for (size_t i = 0; i < size; ++i)
			out.emplace_back(lines[i]);
		return out;
	}

	std::string translateBacktrace(const std::vector<std::string> &bt) {
		std::string out;
		const std::string start = "llvm-addr2line -e " + getExecutablePath() + ' ';
		for (size_t i = 0, max = bt.size(); i < max; ++i) {
			const std::string_view line(bt[i]);
			const auto plus = line.find('+');
			const auto closing = line.find(')', plus + 1);
			out += readAll(start + std::string(line.substr(plus + 1, closing - plus - 1)));
		}
		return out;
	}

	bool isNumeric(const std::string &str) {
		if (str.empty())
			return false;
		for (char ch: str)
			if (ch < '0' || '9' < ch)
				return false;
		return true;
	}

	bool isNumeric(const std::string *str) {
		return isNumeric(*str);
	}

	bool isNumeric(std::string_view str) {
		if (str.empty())
			return false;
		for (char ch: str)
			if (ch < '0' || '9' < ch)
				return false;
		return true;
	}

	bool isNumeric(const char *str) {
		return isNumeric(std::string(str));
	}

	bool isHex(const char ch) {
		return ('0' <= ch && ch <= '9') || ('a' <= ch && ch <= 'f') || ('A' <= ch && ch <= 'F');
	}

	bool outOfRange(long value) {
		return value < INT_MIN || INT_MAX < value;
	}

	std::string escape(const std::string &str) {
		std::stringstream out;
		for (char ch: str) {
			if (ch == '"' || ch == '\\')
				out << '\\' << ch;
			else if (ch == '\t')
				out << "\\t";
			else if (ch == '\n')
				out << "\\n";
			else if (ch == '\r')
				out << "\\r";
			else
				out << ch;
		}
		return out.str();
	}

	std::vector<std::string> split(const std::string &str, const std::string &delimiter, bool condense) {
		if (str.empty())
			return {};

		size_t next = str.find(delimiter);
		if (next == std::string::npos)
			return {str};

		std::vector<std::string> out {};
		const size_t delimiter_length = delimiter.size();
		size_t last = 0;

		out.push_back(str.substr(0, next));

		while (next != std::string::npos) {
			last = next;
			next = str.find(delimiter, last + delimiter_length);
			std::string sub = str.substr(last + delimiter_length, next - last - delimiter_length);
			if (!sub.empty() || !condense)
				out.push_back(std::move(sub));
		}

		return out;
	}
}

int strnatcmp(const std::string &left, const std::string &right) {
	return strnatcmp(left.c_str(), right.c_str());
}

int strnatcmp(const std::string *left, const std::string *right) {
	return strnatcmp(left->c_str(), right->c_str());
}

int strnatcasecmp(const std::string &left, const std::string &right) {
	return strnatcasecmp(left.c_str(), right.c_str());
}

int strnatcasecmp(const std::string *left, const std::string *right) {
	return strnatcasecmp(left->c_str(), right->c_str());
}