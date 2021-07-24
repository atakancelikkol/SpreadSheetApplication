#ifndef EXPRESSION_H
#define EXPRESSION_H
#include <string>

class Expression
{
public:
	Expression();
	Expression(std::string expression);
	int getValue() const;
	void setValue(int value);
	std::string getExpression() const;
	void setExpression(std::string expression);
	std::string findExpression;
private:
	int value;
	std::string expression;
};
#endif