#include "fs.hh"

bool FS::FileExists(std::string fname) {
	std::ifstream fhnd(fname);
	if (fhnd.good()) {
		fhnd.close();
		return true;
	}
	return false;
}

std::string FS::ReadFile(std::string fname) {
	std::ifstream fhnd(fname);
	std::string   ret;
	std::string   line;
	if (!fhnd.good()) {
		printf("[FATAL] Could not open file: %s\n", fname.c_str());
		exit(2);
	}
	while (std::getline(fhnd, line)) {
		ret += line + '\n';
	}
	fhnd.close();

	return ret;
}
