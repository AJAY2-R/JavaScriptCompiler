#ifndef  ASTNODE_H
#define ASTNODE_H

#include <string>
#include <vector>

class ASTNode {
public:
	virtual ~ASTNode() = default;
	virtual void print() const = 0;
	virtual std::string toString() const = 0;
};

class ExpressionNode : public ASTNode {
public:
	ExpressionNode(const std::string& value);
	void print() const override;
	std::string toString() const override;
private:
	std::string value;
};

class StatementNode : public ASTNode {
public:
	StatementNode(const std::string& value);
	void print() const override;
	std::string toString() const override;
private:
	std::string value;
};

class BinaryOperatorNode : public ASTNode {
public:
	BinaryOperatorNode(const std::string& op, ASTNode* left, ASTNode* right);
	void print() const override;
	std::string toString() const override;
private:
	std::string op;
	ASTNode* left;
	ASTNode* right;
};

class BlockNode : public ASTNode {
public:
	BlockNode(const std::vector<ASTNode*>& statements);
	void print() const override;
	std::string toString() const override;
private:
	std::vector<ASTNode*> statements;
};

class IfStatementNode : public ASTNode {
public:
	IfStatementNode(ASTNode* condition, ASTNode* ifBlock, ASTNode* elseBlock);
	void print() const override;
	std::string toString() const override;
private:
	ASTNode* condition;
	ASTNode* ifBlock;
	ASTNode* elseBlock;
};

class WhileStatementNode : public ASTNode {
public:
	WhileStatementNode(ASTNode* condition, ASTNode* whileBlock);
	void print() const override;
	std::string toString() const override;
private:
	ASTNode* condition;
	ASTNode* whileBlock;
};

class AssignmentNode : public ASTNode {
public:
	AssignmentNode(const std::string& identifier, ASTNode* value);
	void print() const override;
	std::string toString() const override;
private:
	std::string identifier;
	ASTNode* value;
};

#endif // ! ASTNODE_H
