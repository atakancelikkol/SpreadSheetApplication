#ifndef CELL_H
#define CELL_H
#include "Expression.h"

class Cell
{
	public:
		Cell(int row, int column, Expression input);
		int getCellRow() const;
		int getCellColumn() const;
		Expression getCellValue() const;
		void setCellValue(int value);
		void setCellExpression(std::string expression);
		bool isOk = false;
		bool isCellEmpty = true;

	private:
		int row;
		int column;
		Expression input;
};
#endif