#pragma once
#include "language.hh"

namespace BuiltIn {
	void Test(ATM::Language::Language_Components& language);
	// stack operations
	void Push32(ATM::Language::Language_Components& language);
	void Pop32(ATM::Language::Language_Components& language);
	void Push8(ATM::Language::Language_Components& language);
	void Pop8(ATM::Language::Language_Components& language);
	void Putchar(ATM::Language::Language_Components& language);
	void Puts(ATM::Language::Language_Components& language);
	void Printf(ATM::Language::Language_Components& language);
}