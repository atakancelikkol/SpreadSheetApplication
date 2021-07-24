#include <iostream>
#include <fstream>
#include <vector>
#include <regex>
#include "FileParser.h"
#include "Solution.h"
#include "String2IntConversion.h"

namespace
{
	constexpr char INPUT_FILE[] = "input.txt";
}

FileParser::FileParser()
{
	ProcessFileInput();
}

FileParser::~FileParser()
{

}

void FileParser::ProcessFileInput()
{
	std::fstream inFile;
	inFile.open(INPUT_FILE);

	if (inFile.fail())
	{
		std::cerr << "Error opeing a file" << std::endl;
		inFile.close();
		exit(1);
	}
	std::string line;
	int row = 0;
	std::vector<Cell> cellResultVector, cell2BeCalculatedVector, combinedCellVector;
	Solution solveExpressionObject;
	std::vector<std::string> lines;
    while (getline(inFile, line))
    {
        lines.push_back(line);
        int column = 0;
        std::string delimiter = "\t";
        std::vector<std::string> lineVector = SplitLinesWithTabDelimeter(line, delimiter);
        ++row;
        for (auto element : lineVector)
        {
            ++column;
            if (!element.empty())
            {
                Cell cellInput(row, column, element);
                Expression cellExpression = cellInput.getCellValue();
                if ((cellExpression.getExpression()).empty())
                {
                    cellInput.isOk = true;
                    cellInput.isCellEmpty = false;
                    cellResultVector.push_back(cellInput);
                }
                else
                {
                    calculateCellValueIfPossible(cellInput, cellResultVector);
                    if (cellInput.isOk)
                    {
                        int result = solveExpressionObject.calculate(cellInput.getCellValue().getExpression());
                        std::cout << result << std::endl;

                        cellInput.setCellValue(result);
                        cellResultVector.push_back(cellInput);

                    }
                    else
                    {
                        cell2BeCalculatedVector.push_back(cellInput);
                    }
                }
            }

        }
    }
    try2CalculateCellsIn2BeCalculatedVector(cell2BeCalculatedVector, cellResultVector);
    combinedCellVector = cellResultVector;
    combinedCellVector.insert(combinedCellVector.end(), cell2BeCalculatedVector.begin(), cell2BeCalculatedVector.end());
    this->lines = lines;
    this->combinedCellVector = combinedCellVector;
    // close the file stream
    inFile.close();
}

std::vector<std::string> FileParser::SplitLinesWithTabDelimeter(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

std::string FileParser::replaceOperandWithItsValue(std::string substr, std::string stringExpression, std::string cellValue)
{
    return regex_replace(stringExpression, std::regex(substr), cellValue);
}

std::string FileParser::Replace(std::string& str, const std::string& sub, const std::string& mod)
{

    std::string tmp(str);
    tmp.replace(tmp.find(sub), mod.length(), mod);
    return tmp;
}


/*
void write2OutputFile(std::vector<std::string> lines, std::vector <Cell> combinedCellVector)
{
    ofstream myfile;
    myfile.open("output.txt");

    for (string line : lines)
    {
        for (Cell cell : combinedCellVector)
        {
            if (!cell.getCellValue().getExpression().empty())
            {
                string string2BeFound = cell.getCellValue().findExpression;
                int value = cell.getCellValue().getValue();
                string stringValue = to_string(value);
                if (!cell.isOk)
                {
                    if (cell.isCellEmpty)
                    {
                        stringValue = "#NAN";
                    }
                    else
                    {
                        stringValue = "#ERROR";
                    }
                }
                int pos = line.find(string2BeFound);
                if (pos != string::npos)
                {
                    line.replace(pos, string2BeFound.length(), stringValue);
                }
            }

        }
        myfile << line << "\n";
        cout << line << endl;
    }
}
*/

void FileParser::try2CalculateCellsIn2BeCalculatedVector(std::vector <Cell>& cell2BeCalculatedVector, std::vector <Cell>& cellResultVector)
{
    Solution solveExpressionObject;
    int index = 0;
    std::vector <Cell> combinedCellVector = cellResultVector;
    combinedCellVector.insert(combinedCellVector.end(), cell2BeCalculatedVector.begin(), cell2BeCalculatedVector.end());

    for (int i = 0; i < cell2BeCalculatedVector.size(); i++)
    {
        if (calculateCellValueIfPossible(cell2BeCalculatedVector[i], combinedCellVector))
        {
            if (cell2BeCalculatedVector[i].isOk)
            {
                int result = solveExpressionObject.calculate(cell2BeCalculatedVector[i].getCellValue().getExpression());
                //cout << result << endl;
                cell2BeCalculatedVector[i].setCellValue(result);
                cellResultVector.push_back(cell2BeCalculatedVector[i]);
                cell2BeCalculatedVector.erase(cell2BeCalculatedVector.begin() + index);
                try2CalculateCellsIn2BeCalculatedVector(cell2BeCalculatedVector, cellResultVector);
            }
        }
        index++;
    }
}

std::vector<std::string> split(std::string s, std::string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    std::string token;
    std::vector<std::string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != std::string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

unsigned findFirstOperatorPosition(std::string str)
{
    unsigned operatorpositionArray[5];
    char operatorArray[] = "+-*/)";
    for (size_t i = 0; i < 5; i++)
    {
        operatorpositionArray[i] = str.find(operatorArray[i]);
    }
    return *std::min_element(operatorpositionArray, operatorpositionArray + 5);
}

bool FileParser::calculateCellValueIfPossible(Cell& cellInput, std::vector <Cell> cellVector)
{
    std::string str = (cellInput.getCellValue()).getExpression();
    std::string stringExpression = str;
    if (str == "")
    {
        return false;
    }
    str = str.substr(1);
    unsigned first = 0;
    bool cellexists = true;
    int multiply = 1;
    bool flag = false;
    while (!str.empty())
    {
        if (isdigit(str[0]))
        {
            str = str.substr(1);
            flag = true;
        }
        else
        {
            if (flag)
            {
                str = str.substr(1);
                flag = false;
            }
            else if (str[0] == '+' || str[0] == '(' || str[0] == ')')
            {
                str = str.substr(1);
            }
            else if (str[0] == '-')
            {
                str = str.substr(1);
            }
            else
            {
                unsigned last = findFirstOperatorPosition(str);
                std::string substr = str.substr(first, last - first);
                if (last == std::string::npos)
                {
                    str.clear();
                }
                else
                {
                    str = str.substr(last + 1);
                }

                int cellValue;
                if (doesCellExist(cellInput, substr, cellVector, &cellValue))
                {
                    stringExpression = replaceOperandWithItsValue(substr, stringExpression, std::to_string(cellValue));
                    cellInput.setCellExpression(stringExpression);
                }
                else
                {
                    cellexists &= false;
                }
            }
        }


    }
    cellInput.isOk = cellexists;
    //cout << cellInput.getCellValue().getExpression() << endl;
    return true;
}

bool FileParser::doesCellExist(Cell& cellInput, std::string cellReference, std::vector <Cell>& cellVector, int* cellValue)
{
    RowColumnStruct localRowColumnStruct;
    convertInputString2RowColumnStruct(cellReference, &localRowColumnStruct);
    for (auto element : cellVector)
    {
        if (element.getCellRow() == localRowColumnStruct.row &&
            element.getCellColumn() == localRowColumnStruct.column)
        {
            cellInput.isCellEmpty = false;
            if (element.isOk)
            {
                *cellValue = (element.getCellValue()).getValue();
                return true;
            }
            break;
        }

    }
    return false;

}

void FileParser::convertInputString2RowColumnStruct(std::string cellReference, struct RowColumnStruct* localRowColumnStruct)
{
    //since in the task it says that latin "letter" so it's assumed it will be just 26
    //latin letters for the column tab.
    RowColumnStruct returnedRowColumnStruct = convertColumnRowChars2Integer(cellReference);
    localRowColumnStruct->row = returnedRowColumnStruct.row;
    localRowColumnStruct->column = returnedRowColumnStruct.column;
}