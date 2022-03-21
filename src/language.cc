#include "language.hh"
#include "builtin.hh"

ATM::Language::Function::Function() {
	exists = false;
}

void ATM::Language::Language_Components::AddBuiltInFunction(std::string name, ATM::Language::BuiltInFunction function) {
	ATM::Language::Function add;
	add.builtin     = true;
	add.exists      = true;
	add.bfunction   = function;
	functions[name] = add;
}

void ATM::Language::Language_Components::Init() {
	/******************************/
	/********* init memory ********/
	/******************************/
	// NULL
	stack.push_back(0);
	variables.NewConst("MEM_NULL", 0);

	// accumulator
	for (uint8_t i = 0; i < 4; ++i) {
		stack.push_back(0);
	}
	variables.NewConst("MEM_ACC", 4);

	// booleans
	variables.NewConst("true", 1);
	variables.NewConst("false", 0);

	// arguments pointer
	variables.New("MEM_ARGV", 0);
	variables.New("MEM_ARGC", 0);

	/****************************/
	/****** init functions ******/
	/****************************/
	AddBuiltInFunction("test", BuiltIn::Test);
	AddBuiltInFunction("push", BuiltIn::Push);
	AddBuiltInFunction("pop", BuiltIn::Pop);
}

uint32_t ATM::Language::Language_Components::GetIntFromPointer(uint32_t ptr) {
	uint32_t ret;
	uint8_t  bytes[4];
	for (size_t i = 0; i < sizeof(bytes); ++i) {
		bytes[i] = stack[ptr + i];
	}
	memcpy(&ret, bytes, sizeof(bytes));

	return ret;
}