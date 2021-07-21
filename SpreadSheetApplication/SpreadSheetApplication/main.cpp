#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>
#include <algorithm>
#include <regex>
#include <ctype.h>
#include "Cell.h"
#include "String2IntConversion.h"
#include "Solution.h"

using namespace std;
bool calculateCellValueIfPossible(Cell &cellInput, vector <Cell> cellVector);
bool doesCellExist(Cell& cellInput, string cellReference, vector <Cell>&cellVector, int *cellValue);
vector<string> split(string s, string delimiter);
void convertInputString2RowColumnStruct(string cellReference, struct RowColumnStruct *localRowColumnStruct);
void try2CalculateCellsIn2BeCalculatedVector(vector <Cell> &cell2BeCalculatedVector, vector <Cell> &cellResultVector);


int main()
{
    fstream inFile;
    // open the file stream
    inFile.open("input.txt");
    // check if opening a file failed
    if (inFile.fail())
    {
        cerr << "Error opeing a file" << endl;
        inFile.close();
        exit(1);
    }
    string line;
    int row = 0;
    vector<Cell> cellResultVector, cell2BeCalculatedVector;
    Solution solveExpressionObject;
    while (getline(inFile, line))
    {
        int column = 0;
        string delimiter = "\t";
        vector<string> lineVector = split(line, delimiter);
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
                        cout << result << endl;

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
    // close the file stream
    inFile.close();
    return 0;
}

void try2CalculateCellsIn2BeCalculatedVector(vector <Cell> &cell2BeCalculatedVector, vector <Cell> &cellResultVector)
{
    Solution solveExpressionObject;
    int index = 0;
    for (Cell element : cell2BeCalculatedVector)
    {/*find (cell2BeCalculatedVector.begin(), cell2BeCalculatedVector.end(), element) != cell2BeCalculatedVector.end()*/
        if (calculateCellValueIfPossible(element, cellResultVector))
        {
            if (element.isOk)
            {
                int result = solveExpressionObject.calculate(element.getCellValue().getExpression());
                cout << result << endl;
                element.setCellValue(result);
                cellResultVector.push_back(element);
                cell2BeCalculatedVector.erase(cell2BeCalculatedVector.begin() + index);
                try2CalculateCellsIn2BeCalculatedVector(cell2BeCalculatedVector, cellResultVector);
            }
        }
        index++;
    }
}

vector<string> split(string s, string delimiter)
{
    size_t pos_start = 0, pos_end, delim_len = delimiter.length();
    string token;
    vector<string> res;

    while ((pos_end = s.find(delimiter, pos_start)) != string::npos)
    {
        token = s.substr(pos_start, pos_end - pos_start);
        pos_start = pos_end + delim_len;
        res.push_back(token);
    }

    res.push_back(s.substr(pos_start));
    return res;
}

unsigned findFirstOperatorPosition(string str)
{
    unsigned operatorpositionArray[5];
    char operatorArray[] = "+-*/)";
    for (size_t i = 0; i < 5; i++)
    {
        operatorpositionArray[i] = str.find(operatorArray[i]);
    }
    return *min_element(operatorpositionArray, operatorpositionArray + 5);
}

string replaceOperandWithItsValue(string substr, string stringExpression, int cellValue)
{
    
    return regex_replace(stringExpression, std::regex(substr), to_string(cellValue));
}

bool calculateCellValueIfPossible(Cell &cellInput, vector <Cell> cellVector)
{
    string str = (cellInput.getCellValue()).getExpression();
    string stringExpression = str;
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
                string substr = str.substr(first, last - first);
                if (last == string::npos)
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
                    stringExpression = replaceOperandWithItsValue(substr, stringExpression, cellValue);
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
    cout << cellInput.getCellValue().getExpression() << endl;
    return true;
}

bool doesCellExist(Cell& cellInput, string cellReference, vector <Cell>&cellVector, int *cellValue)
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
        }
            
    }
    return false;

}

void convertInputString2RowColumnStruct(string cellReference, struct RowColumnStruct* localRowColumnStruct)
{
    //since in the task it says that latin "letter" so it's assumed it will be just 26
    //latin letters for the column tab.
    RowColumnStruct returnedRowColumnStruct = convertColumnRowChars2Integer(cellReference);
    localRowColumnStruct->row = returnedRowColumnStruct.row;
    localRowColumnStruct->column = returnedRowColumnStruct.column;
}