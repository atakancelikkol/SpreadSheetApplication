#include "Cell.h"
Cell::Cell(int row, int column, Expression input)
{
	this->row = row;
	this->column = column;
	this->input = input;
}

int Cell::getCellRow() const
{
	return row;
}

int Cell::getCellColumn() const
{
	return column;
}

Expression Cell::getCellValue() const
{
	return this->input;
}

void Cell::setCellValue(int value)
{
	(this->input).setValue(value);
}

void Cell::setCellExpression(std::string expression)
{
	(this->input).setExpression(expression);
}

