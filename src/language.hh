#pragma once
#include "_components.hh"
#include "lexer.hh"
#include "variables.hh"

namespace ATM {
	namespace Language {
		struct Language_Components;
		typedef void (*BuiltInFunction)(struct Language_Components&);
		struct Function {
			Function();
			bool                       builtin;
			bool                       exists;
			BuiltInFunction            bfunction;
			std::vector <Lexer::Token> function;
		};
		class Language_Components {
			public:
				std::vector <uint8_t>                      stack;
				VariableMap                                variables;
				std::unordered_map <std::string, Function> functions;
				void                                       Init();
				void                                       AddBuiltInFunction(std::string name, BuiltInFunction function);
				uint32_t                                   GetIntFromPointer(uint32_t ptr);
		};
	}
}