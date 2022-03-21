#include "util.hh"

bool Util::ValidateArgument(std::string str, std::string shorts, std::string longs) {
	return (
		(str == shorts) ||
		(str == longs)
	);
}