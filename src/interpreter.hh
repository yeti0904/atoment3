#pragma once
#include "lexer.hh"
#include "language.hh"

namespace Interpreter {
	void Interpret(std::string fname, std::vector <Lexer::Token>& tokens, ATM::Language::Language_Components& language);
}