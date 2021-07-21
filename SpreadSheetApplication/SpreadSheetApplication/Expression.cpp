#include "Expression.h"
#include <string>
Expression::Expression()
{
	this->expression = "";
	this->value = NAN;
}

Expression::Expression(std::string expression)
{
	
	if (expression.find('=') != std::string::npos )
	{
		this->expression = expression;
		this->value = NAN;
	}
	else
	{
		this->expression = "";
		this->value = std::stoi(expression);
	}
}

int Expression::getValue() const
{
	return value;
}

void Expression::setValue(int value)
{
	this->value = value;
}

std::string Expression::getExpression() const
{
	return expression;
}

void Expression::setExpression(std::string expression)
{
	this->expression = expression;
}
/*string Expression::parseExpressionUntilOperator()
{
	this->expression = this->expression.substr(1);

}*/

