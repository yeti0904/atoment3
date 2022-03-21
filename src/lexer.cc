#include "lexer.hh"
#include "string.hh"

std::string Lexer::Debug::TokenToString(Token& token) {
	switch (token.type) {
		case TokenType::FunctionCall: {
			return "FunctionCall";
			break;
		}
		case TokenType::FunctionDef: {
			return "FunctionDef";
			break;
		}
		case TokenType::Identifier: {
			return "Identifier";
			break;
		}
		case TokenType::Dereference: {
			return "Dereference";
			break;
		}
		case TokenType::Assignment: {
			return "Assignment";
			break;
		}
		case TokenType::EndOfStatement: {
			return "EndOfStatement";
			break;
		}
		case TokenType::ArgumentString: {
			return "ArgumentString";
			break;
		}
		case TokenType::ArgumentInteger: {
			return "ArgumentInteger";
			break;
		}
		case TokenType::ArgumentCharacter: {
			return "ArgumentCharacter";
			break;
		}
		case TokenType::If: {
			return "If";
			break;
		}
	}
	return "";
}

void Lexer::Debug::PrintTokens(std::vector<Token>& tokens) {
	for (size_t i = 0; i<tokens.size(); ++i) {
		std::string type = Lexer::Debug::TokenToString(tokens[i]);
		printf("(%i){%d:%d}[%s] %s\n", (int)i, (int)tokens[i].line, (int)tokens[i].column, type.c_str(), tokens[i].content.c_str());
	}
}

std::vector <Lexer::Token> Lexer::Lex(std::string& fname, const std::string& source) {
	std::vector <Lexer::Token> ret;
	std::string                reading;
	size_t line     = 1;
	size_t column   = 1;
	bool   inString = false;

	for (size_t i = 0; i <= source.length(); ++i) {
		++ column;
		switch (source[i]) {
			case ' ': 
			case '\n': {
				if (source[i] == '\n') {
					++ line;
					column = 1;
				}
				if ((source[i] == ' ') && inString) {
					reading += source[i];
				}
				break;
			}
			case '"': {
				if (!inString) {
					inString = true;
				}
				else {
					if (source[i-1] != '\\') {
						inString = false;
					}
				}
				reading += '"';
				break;
			}
			case ':': { // function
				if (inString) break;
				if (reading == "") {
					printf("(Lexer) error at file %s at %d:%d\n    Empty function name\n", fname.c_str(), (int)line, (int)column);
					exit(1);
				}
				ret.push_back(Token(TokenType::FunctionCall, reading, line, column));
				reading = "";
				break;
			}
			case '\0':  // end of file
			case ',':   // argument seperator
			case ';': { // end of statement
				if (inString) break;
				// might be a function
				if ((source[i] == ';')
					&& (
						(ret.size() == 0) ||
						(
							(ret.back().type != Lexer::TokenType::ArgumentCharacter) &&
							(ret.back().type != Lexer::TokenType::ArgumentInteger) &&
							(ret.back().type != Lexer::TokenType::ArgumentString) &&
							(ret.back().type != Lexer::TokenType::FunctionCall)
						)
					)
				) {
					ret.push_back(Token(TokenType::FunctionCall, reading, line, column));
					ret.push_back(Token(TokenType::EndOfStatement, "", line, column));
					reading = "";
					break;
				}
				// we have an argument
				// but what type?
				if ((reading[0] == '\'') && (reading[reading.length() - 1] == '\'')) {
					// could be a character
					if ((reading[1] == '\\') || (reading.length() == 3)) {
						// definitely a character
						char ch;
						if (reading[1] == '\\') {
							// escape code
							ch = ATM::String::GetEscape(reading[2]);
						}
						else {
							ch = reading[1];
						}
						ret.push_back(Token(TokenType::ArgumentCharacter, std::string(ch, 1), line, column));
					}
					else {
						printf("[Lexer Error] invalid character literal at %s:%i:%i\n", fname.c_str(), (int)line, (int)column);
						exit(1);
					}
					reading = "";
				}
				else if (ATM::String::IsInteger(reading)) {
					// integer
					ret.push_back(Token(TokenType::ArgumentInteger, reading, line, column));
					reading = "";
				}
				else if ((reading[0] == '"') && (reading[reading.length() - 1] == '"')) {
					// string
					std::string str = ATM::String::CreateString(reading);
					ret.push_back(Token(TokenType::ArgumentString, str.substr(1, str.length() - 2), line, column));
					reading = "";
				}
				else if (reading != "") {
					// identifier
					ret.push_back(Token(TokenType::Identifier, reading, line, column));
					reading = "";
				}
				if (source[i] == ';') {
					// we have an end of statement
					ret.push_back(Token(TokenType::EndOfStatement, reading, line, column));
					break;
				}
				break;
			}
			case '^': {
				if (!inString) {
					ret.push_back(Token(TokenType::Dereference, "", line, column));
					reading = "";
				}
				break;
			}
			case '=': {
				if (inString) break;
				ret.push_back(Token(TokenType::Identifier, reading, line, column));
				reading = "";
				ret.push_back(Token(TokenType::Assignment, "", line, column));
				break;
			}
			default: {
				reading += source[i];
				break;
			}
		}
	}

	return ret;
}