#include "interpreter.hh"

void Interpreter::Interpret(std::string fname, std::vector <Lexer::Token>& tokens, ATM::Language::Language_Components& language) {
	for (size_t i = 0; i < tokens.size(); ++i) {
		switch (tokens[i].type) {
			case Lexer::TokenType::FunctionCall: {
				if (language.functions[tokens[i].content].exists) {
					if (language.functions[tokens[i].content].builtin) {
						// push arguments to stack
						// start with strings
						++i;
						std::unordered_map <size_t, uint32_t> stringAddresses;
						for (size_t j = i; (tokens[j].type != Lexer::TokenType::EndOfStatement) && (j < tokens.size()); ++j) {
							if (tokens[j].type == Lexer::TokenType::ArgumentString) {
								// push string to the stack
								stringAddresses[j - i] = language.stack.size();
								for (size_t k = 0; k <= tokens[j].content.length(); ++k) {
									language.stack.push_back(tokens[j].content[k]);
								}
							}
						}
						size_t argAddr = language.stack.size();
						// other arguments
						size_t j;
						size_t argCount = 0;
						for (j = i; tokens[j].type != Lexer::TokenType::EndOfStatement; ++j) {
							if (j >= tokens.size()) {
								printf("[Interpreter Error] %s:%i:? Unexpected EOF while getting arguments\n", fname.c_str(), (int)tokens.back().line);
								exit(1);
							}
							switch (tokens[j].type) {
								case Lexer::TokenType::ArgumentCharacter: {
									uint32_t ch = tokens[j].content[0];
									uint8_t  arr[4];
									memcpy(arr, &ch, sizeof(ch));
									for (size_t i = 0; i<sizeof(arr); ++i) {
										language.stack.push_back(arr[i]);
									}
									++ argCount;
									break;
								}
								case Lexer::TokenType::ArgumentInteger: {
									uint32_t num = std::stoi(tokens[j].content);
									uint8_t  arr[4];
									memcpy(arr, &num, sizeof(num));
									for (size_t i = 0; i<sizeof(arr); ++i) {
										language.stack.push_back(arr[i]);
									}
									++ argCount;
									break;
								}
								case Lexer::TokenType::ArgumentString: {
									language.stack.push_back(stringAddresses[j - i]);
									++ argCount;
									break;
								}
								case Lexer::TokenType::Identifier: {
									if (language.variables.Exists(tokens[j].content)) {
										uint8_t arr[4];
										memcpy(arr, &language.variables[tokens[j].content].value, sizeof(language.variables[tokens[j].content].value));
										for (size_t i = 0; i<sizeof(arr); ++i) {
											language.stack.push_back(arr[i]);
										}
										++ argCount;
									}
									else {
										printf("[Interpreter Error] %s:%i:%i Reference to undefined variable %s\n", fname.c_str(), (int)tokens[j].line, (int)tokens[j].column, tokens[j].content.c_str());
										exit(1);
									}
									break;
								}
								default: {
									printf("[Interpreter Error] %s:%i:%i Unexpected token %s\n", fname.c_str(), (int)tokens[j].line, (int)tokens[j].column, Lexer::Debug::TokenToString(tokens[j]).c_str());
									exit(1);
								}
							}
						}
						size_t functionIndex = i - 1;
						i = j;
						if (language.functions[tokens[functionIndex].content].bfunction == NULL) {
							printf("[FATAL Error] Function %s is NULL\n", tokens[i].content.c_str());
							exit(1);
						}
						language.variables.New("MEM_ARGV", argAddr);
						language.variables.New("MEM_ARGC", argCount);
						

						language.functions[tokens[functionIndex].content].bfunction(language);
					}
					else {
						// TODO: call functions defined in atoment
					}
				}
				else {
					printf("[Interpreter Error] %s:%d:%d undefined reference to function %s\n", fname.c_str(), (int)tokens[i].line, (int)tokens[i].column, tokens[i].content.c_str());
					exit(1);
				}
			}
			default: {
				// hi
			}
		}
	}
}