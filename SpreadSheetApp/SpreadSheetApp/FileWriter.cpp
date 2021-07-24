#include <iostream>
#include <fstream>
#include "FileWriter.h"

FileWriter::FileWriter(std::vector<std::string> lines, std::vector<Cell> combinedCellVector)
{
    write2OutputFile(lines, combinedCellVector);
}

void FileWriter::write2OutputFile(std::vector<std::string> lines, std::vector <Cell> combinedCellVector)
{
    std::ofstream myfile;
    myfile.open("output.txt");

    for (std::string line : lines)
    {
        for (Cell cell : combinedCellVector)
        {
            if (!cell.getCellValue().getExpression().empty())
            {
                std::string string2BeFound = cell.getCellValue().findExpression;
                int value = cell.getCellValue().getValue();
                std::string stringValue = std::to_string(value);
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
                if (pos != std::string::npos)
                {
                    line.replace(pos, string2BeFound.length(), stringValue);
                }
            }

        }
        myfile << line << "\n";
        std::cout << line << std::endl;
    }
}

FileWriter::~FileWriter()
{
}