#pragma once
#include "_components.hh"

namespace ATM {
	namespace String {
		char        GetEscape(const char& ch);
		bool        IsInteger(const std::string& str);
		std::string CreateString(const std::string& str);
	}
}