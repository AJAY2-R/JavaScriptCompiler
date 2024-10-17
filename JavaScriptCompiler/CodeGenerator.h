#ifndef CODEGENERATOR_H
#define CODEGENERATOR_H

#include <string>
#include "ASTNode.h"

class CodeGenerator {
public:
	CodeGenerator(ASTNode* root);
	std::string generateCode();
private:
	ASTNode* root;
	std::string generateCode(ASTNode* node);
};

#endif // !CODEGENERATOR_H
