#pragma once
#include "_components.hh"

namespace FS {
	bool        FileExists(std::string fname);
	std::string ReadFile(std::string fname);
}