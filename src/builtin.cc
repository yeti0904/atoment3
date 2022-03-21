#include "builtin.hh"
#include "lexer.hh"
// TODO: remove the above include

void BuiltIn::Test(ATM::Language::Language_Components& language) {
	puts("Welcome to Atoment 3");
	puts("====================");
	printf("Stack size: %d\n", (int)language.stack.size());
	puts("hello world");
	puts("====================");
}

void BuiltIn::Push(ATM::Language::Language_Components& language) {
	// we dont need to do anything because the arguments are already pushed to the stack
	(void) language;
}

void BuiltIn::Pop(ATM::Language::Language_Components& language) {
	//printf("%d\n", language.variables["MEM_ARGC"].value);
	std::string popTo;
	if (language.variables["MEM_ARGC"].value > 1) {
		printf("BuiltIn Pop: too many arguments");
		exit(1);
	}
	if (language.variables["MEM_ARGC"].value != 0) {
		uint32_t stringStart = language.GetIntFromPointer(language.variables["MEM_ARGV"].value);
		for (size_t i = stringStart; language.stack[i] != 0; ++i) {
			if (i >= language.stack.size()) {
				printf("BuiltIn Pop: stack end is before string end\n");
				exit(1);
			}
			popTo += language.stack[i];
		}
		for (size_t i = 0; i <= popTo.length(); ++i) {
			language.stack.pop_back();
		}

		if (language.variables["MEM_ARGC"].value != 0) {
			uint8_t bytes[4];
			for (size_t i = 0; i < 4; ++i) {
				bytes[i] = language.stack[language.stack.size() - i];
			}
			uint32_t value;
			memcpy(&value, bytes, sizeof(bytes));
			language.variables.New(popTo, value);
		}
	}
	for (size_t i = 0; i < 4; ++i) {
		language.stack.pop_back();
	}
}

void BuiltIn::Putchar(ATM::Language::Language_Components& language) {
	putchar(language.stack.back());
	language.stack.pop_back();
}