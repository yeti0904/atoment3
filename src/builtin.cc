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

void BuiltIn::Push32(ATM::Language::Language_Components& language) {
	// we dont need to do anything because the arguments are already pushed to the stack
	(void) language;
}

void BuiltIn::Pop32(ATM::Language::Language_Components& language) {
	//printf("%d\n", language.variables["MEM_ARGC"].value);
	std::string popTo;
	if (language.variables["MEM_ARGC"].value > 1) {
		printf("BuiltIn Pop: too many arguments");
		exit(1);
	}
	if (language.variables["MEM_ARGC"].value != 0) {
		uint32_t stringStart = language.GetIntFromPointer(language.variables["MEM_ARGV"].value);
		/*for (size_t i = stringStart; language.stack[i] != 0; ++i) {
			if (i >= language.stack.size()) {
				printf("BuiltIn Pop: stack end is before string end\n");
				exit(1);
			}
			popTo += language.stack[i];
		}
		for (size_t i = 0; i <= popTo.length() + 1; ++i) {
			language.stack.pop_back();
		}*/
		popTo = language.GetAndPopString(stringStart);
		
		/*uint8_t bytes[4];
		for (size_t i = 0; i < 4; ++i) {
			bytes[i] = language.stack[language.stack.size() - i];
		}
		uint32_t value;
		memcpy(&value, bytes, sizeof(bytes));*/
		uint32_t value = language.GetIntFromPointer(language.stack.size() - 4);
		language.variables.New(popTo, value);
	}
	for (size_t i = 0; i < 4; ++i) {
		language.stack.pop_back();
	}
}

void BuiltIn::Push8(ATM::Language::Language_Components& language) {
	std::vector <uint8_t> toPush;
	for (size_t i = 0; i < language.variables["MEM_ARGC"].value; ++i) {
		uint32_t value = language.GetIntFromPointer(language.variables["MEM_ARGV"].value + (i * 4));
		for (size_t i = 0; i < 4; ++i) {
			language.stack.pop_back();
		}
		toPush.push_back((uint8_t) value);
	}
	for (size_t i = 0; i < toPush.size(); ++i) {
		language.stack.push_back(toPush[i]);
	}
}

void BuiltIn::Pop8(ATM::Language::Language_Components& language) {
	if (language.variables["MEM_ARGC"].value > 1) {
		fputs("BuiltIn Pop8: Too many arguments\n", stderr);
		exit(1);
	}
	if (language.variables["MEM_ARGC"].value == 1) {
		uint32_t stringStart = language.GetIntFromPointer(language.variables["MEM_ARGV"].value);
		for (size_t i = 0; i < 4; ++i) {
			language.stack.pop_back();
		}
		std::string popTo = language.GetAndPopString(stringStart);
		language.variables.New(popTo, language.stack.back());
	}
	language.stack.pop_back();
}

void BuiltIn::Putchar(ATM::Language::Language_Components& language) {
	putchar(language.stack.back());
	language.stack.pop_back();
}

void BuiltIn::Puts(ATM::Language::Language_Components& language) {
	if (language.variables["MEM_ARGC"].value < 1) {
		puts("BuiltIn Puts: Too little arguments");
		exit(1);
	}
	if (language.variables["MEM_ARGC"].value > 1) {
		puts("BuiltIn Puts: Too many arguments");
		exit(1);
	}
	uint32_t stringPointer = language.GetIntFromPointer(language.variables["MEM_ARGV"].value);
	for (size_t i = 0; i < 4; ++i) {
		language.stack.pop_back();
	}
	std::string str = language.GetAndPopString(stringPointer);
	fputs(str.c_str(), stdout);
}

void BuiltIn::Printf(ATM::Language::Language_Components& language) {
	if (language.variables["MEM_ARGC"].value < 1) {
		fputs("BuiltIn Printf: Too little arguments\n", stderr);
	}
	std::string format = language.GetAndPopString(language.GetIntFromPointer(language.variables["MEM_ARGV"].value));
	size_t argIterator = 1;
	for (size_t i = 0; i < format.length(); ++i) {
		switch (format[i]) {
			case '%': {
				switch (format[i + 1]) {
					case '\0':
					case '%': {
						putchar('%');
						break;
					}
					case 'd':
					case 'u':
					case 'i': {
						fprintf(stdout, "%d", language.GetIntFromPointer(language.variables["MEM_ARGV"].value + (argIterator * 4)));
						++ argIterator;
						break;
					}
				}
				++ i;
				break;
			}
			default: {
				putchar(format[i]);
				break;
			}
		}
	}
	while (language.stack.size() >= language.variables["MEM_ARGV"].value) {
		language.stack.pop_back();
	}
}