#include "String2IntConversion.h"
#define ASCIICHAR2INTOFFSET 64
int columnChar2Int(char column)
{
	return (int)column - ASCIICHAR2INTOFFSET;
}

int rowChar2Int(std::string row)
{
	return std::stoi(row);
}

struct RowColumnStruct convertColumnRowChars2Integer(std::string cellReference)
{
	RowColumnStruct localRowColumnStruct;
	char column = cellReference.front();
	localRowColumnStruct.column = columnChar2Int(column);
	localRowColumnStruct.row = rowChar2Int(cellReference.substr(1));
	return localRowColumnStruct;
}