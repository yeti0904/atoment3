#include "variables.hh"

Variable& VariableMap::operator[](std::string name) {
	bool   found = false;
	size_t index = 0;
	for (size_t i = 0; i < variableData.size(); ++i) {
		if (variableData[i].name == name) {
			found = true;
			index = i;
			break;
		}
	}
	if (!found) {
		Variable newVariable;
		newVariable.constant = false;
		newVariable.name     = name;
		newVariable.value    = 0;
		variableData.push_back(newVariable);
		index = variableData.size() - 1;
	}

	return variableData[index];
}

bool VariableMap::Exists(std::string name) {
	for (size_t i = 0; i < variableData.size(); ++i) {
		if (variableData[i].name == name) {
			return true;
		}
	}
	return false;
}

void VariableMap::SetConst(std::string name, bool set) {
	for (size_t i = 0; i < variableData.size(); ++i) {
		if (variableData[i].name == name) {
			variableData[i].constant = set;
			return;
		}
	}
}

void VariableMap::New(std::string name, uint32_t value) {
	bool   found = false;
	size_t index = 0;
	for (size_t i = 0; i < variableData.size(); ++i) {
		if (variableData[i].name == name) {
			found = true;
			index = i;
			if (variableData[i].constant) {
				printf("[VariableMap Error] Tried to set constant '%s' to %d\n", name.c_str(), value);
				exit(1);
			}
			break;
		}
	}
	Variable add;
	add.name     = name;
	add.value    = value;
	add.constant = false;
	if (found) {
		variableData[index] = add;
	}
	else {
		variableData.push_back(add);
	}
}

void VariableMap::NewConst(std::string name, uint32_t value) {
	bool   found = false;
	for (size_t i = 0; i < variableData.size(); ++i) {
		if (variableData[i].name == name) {
			found = true;
			break;
		}
	}
	if (found) {
		printf("[VariableMap Error] tried to edit an existing variable '%s'\n", name.c_str());
		exit(1);
	}
	Variable add;
	add.name     = name;
	add.value    = value;
	add.constant = true;

	variableData.push_back(add);
}