#include <vector>
#include "Cell.h"

class FileWriter
{
public:
	FileWriter(std::vector<std::string> lines, std::vector<Cell> combinedCellVector);
	~FileWriter();

private:
    void write2OutputFile(std::vector<std::string> lines, std::vector <Cell> combinedCellVector);
};

