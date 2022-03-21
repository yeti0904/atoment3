#include "_components.hh"
#include "string.hh"

char ATM::String::GetEscape(const char& ch) {
	switch (ch) {
		case '\'': {
			return '\'';
		}
		case '"': {
			return '"';
		}
		case 'n': {
			return '\n';
		}
		case 'r': {
			return '\r';
		}
		case 't': {
			return '\t';
		}
		case 'e': {
			return '\033';
		}
		case '\\': {
			return '\\';
		}
		default: {
			printf("[String Error] unknown escape code \\%c\n", ch);
			exit(1);
		}
	}
}

bool ATM::String::IsInteger(const std::string& str) {
	if (str.length() == 0) {
		return false;
	}
	for (size_t i = 0; i < str.length(); ++i) {
		if (!isdigit(str[i])) {
			return false;
		}
	}
	return true;
}

std::string ATM::String::CreateString(const std::string& str) {
	std::string ret;
	for (size_t i = 0; i<str.length(); ++i) {
		switch (str[i]) {
			case '\\': {
				++ i;
				ret += GetEscape(str[i]);
				break;
			}
			default: {
				ret += str[i];
				break;
			}
		}
	}
	return ret;
}