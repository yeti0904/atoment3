#pragma once
#include "_components.hh"

namespace Util {
	bool     ValidateArgument(std::string str, std::string shorts, std::string longs);
	uint32_t SwapEndian(uint32_t integer);
}