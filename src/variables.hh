#pragma once
#include "_components.hh"

struct Variable {
	std::string name;
	uint32_t    value;
	bool        constant;
};

class VariableMap {
	public:
		VariableMap() {}
		std::vector <Variable> variableData;
		Variable& operator[](std::string name);
		bool      Exists(std::string name);
		void      SetConst(std::string name, bool set);
		void      New(std::string name, uint32_t value);
		void      NewConst(std::string name, uint32_t value);
};