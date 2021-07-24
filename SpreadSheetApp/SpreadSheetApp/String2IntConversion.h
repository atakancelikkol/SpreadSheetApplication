#ifndef STRING2INTCONVERSION_H
#define STRING2INTCONVERSION_H

#include <string>

struct RowColumnStruct
{
    int column;
    int row;
};

struct RowColumnStruct convertColumnRowChars2Integer(std::string cellReference);



#endif