#include "_components.hh"
#include "util.hh"
#include "constants.hh"
#include "fs.hh"
#include "lexer.hh"
#include "language.hh"
#include "interpreter.hh"

int main(int argc, char** argv) {
	std::vector <std::string> args;
	for (size_t i = 0; i < (size_t)argc; ++i) {
		args.push_back(argv[i]);
	}

	std::string sourceFile;
	bool        debugLexer     = false;
	bool        debugStack     = false;
	bool        debugVariables = false;

	for (size_t i = 1; i < args.size(); ++i) {
		if (args[i][0] == '-') {
			if (Util::ValidateArgument(args[i], "-v", "--version")) {
				printf("%s %s\n", APP_TITLE, APP_VERSION);
				return 0;
			}
			if (Util::ValidateArgument(args[i], "-ld", "--lexer-debug")) {
				debugLexer = !debugLexer;
			}
			if (Util::ValidateArgument(args[i], "-sd", "--stack-debug")) {
				debugStack = !debugStack;
			}
			if (Util::ValidateArgument(args[i], "-vd", "--variables-debug")) {
				debugVariables = !debugVariables;
			}
			if (Util::ValidateArgument(args[i], "-h", "--help")) {
				printf(
					"Usage: %s [FILE] [OPTIONS]\n"
					"Options:\n"
					"    -h  / --help            : Show this help menu\n"
					"    -v  / --version         : Show version\n"
					"    -sd / --stack-debug     : Print all stack items after interpreting\n"
					"    -ld / --lexer-debug     : Print tokens after tokenising\n"
					"    -vd / --variables-debug : Print all variables after interpreting\n"
					, argv[0]
				);
				exit(0);
			}
		}
		else {
			sourceFile = args[i];
		}
	}

	if (sourceFile == "") {
		printf("[FATAL] No source file specified.\n");
		return 1;
	}
	if (!FS::FileExists(sourceFile)) {
		printf("[FATAL] Source file does not exist: %s\n", sourceFile.c_str());
		return 1;
	}

	std::string sourceCode = FS::ReadFile(sourceFile);

	// lex
	std::vector <Lexer::Token> tokens = Lexer::Lex(sourceFile, sourceCode);
	if (debugLexer) {
		Lexer::Debug::PrintTokens(tokens);
		return 0;
	}

	// init language
	ATM::Language::Language_Components language;
	language.Init();

	// interpret
	Interpreter::Interpret(sourceFile, tokens, language);
	if (debugStack) {
		printf("\n\n\nSTACK DEBUG\n===========\nSize: %d\n", (int)language.stack.size());
		for (size_t i = 0; i < language.stack.size(); ++i) {
			printf("%.10i: %i\n", (int) i, language.stack[i]);
		}
	}
	if (debugVariables) {
		printf("\n\n\nVARIABLES DEBUG\n===============\nSize: %d\n", (int)language.variables.variableData.size());
		for (size_t i = 0; i < language.variables.variableData.size(); ++i) {
			printf("%s = %d\n", language.variables.variableData[i].name.c_str(), language.variables.variableData[i].value);
		}
	}

	return 0;
}