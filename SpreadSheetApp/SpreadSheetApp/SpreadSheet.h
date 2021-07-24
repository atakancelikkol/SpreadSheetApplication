#include "FileParser.h"
#include "FileWriter.h"

class SpreadSheet
{
public:
	SpreadSheet();
	~SpreadSheet();

private:

};

SpreadSheet::SpreadSheet()
{
	FileParser fparse;
	std::vector<std::string> lines = fparse.lines;
	std::vector <Cell> combinedCellVector = fparse.combinedCellVector;

	FileWriter fwrite(lines, combinedCellVector);
}

SpreadSheet::~SpreadSheet()
{
}