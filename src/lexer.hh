#pragma once
#include "_components.hh"

namespace Lexer {
	struct Token;
	namespace Debug {
		void PrintTokens(std::vector <Token>& tokens);
		std::string TokenToString(Token& token);
	}
	enum class TokenType {
		FunctionCall = 0,
		FunctionDef,
		Identifier,
		Dereference,
		Assignment,
		EndOfStatement,
		ArgumentString,
		ArgumentInteger,
		ArgumentCharacter,
		If
	};
	struct Token {
		Token(TokenType itype, std::string icontent, size_t iline, size_t icolumn) {
			type    = itype;
			content = icontent;
			line    = iline;
			column  = icolumn;
		}
		TokenType type;
		std::string content;
		size_t      line;
		size_t      column;
	};
	std::vector <Token> Lex(std::string& fname, const std::string &source);
}