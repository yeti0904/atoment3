#include "util.hh"

bool Util::ValidateArgument(std::string str, std::string shorts, std::string longs) {
	return (
		(str == shorts) ||
		(str == longs)
	);
}

uint32_t Util::SwapEndian(uint32_t integer) {
	uint8_t  retbytes[4];
	uint8_t  srcbytes[4];
	uint32_t ret;

	memcpy(srcbytes, &integer, sizeof(integer));

	retbytes[0] = srcbytes[3];
	retbytes[1] = srcbytes[2];
	retbytes[2] = srcbytes[1];
	retbytes[3] = srcbytes[0];

	memcpy(&ret, retbytes, sizeof(retbytes));

	return ret;
}