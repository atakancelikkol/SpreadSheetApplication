#pragma once
#include <vector>
#include "Cell.h"
class FileParser
{
public:
	FileParser();
	~FileParser();
	std::vector<std::string> lines;
	std::vector<Cell>combinedCellVector;

private:

	void ProcessFileInput();
	std::vector <std::string> SplitLinesWithTabDelimeter(std::string, std::string);
	std::string replaceOperandWithItsValue(std::string substr, std::string stringExpression, std::string cellValue);
	std::string Replace(std::string& str, const std::string& sub, const std::string& mod);
	bool calculateCellValueIfPossible(Cell& cellInput, std::vector <Cell> cellVector);
	bool doesCellExist(Cell& cellInput, std::string cellReference, std::vector <Cell>& cellVector, int* cellValue);
	std::vector<std::string> split(std::string s, std::string delimiter);
	void try2CalculateCellsIn2BeCalculatedVector(std::vector <Cell>& cell2BeCalculatedVector, std::vector <Cell>& cellResultVector);
	void write2OutputFile(std::vector<std::string> lines, std::vector <Cell> combinedCellVector);
	void convertInputString2RowColumnStruct(std::string cellReference, struct RowColumnStruct* localRowColumnStruct);
};