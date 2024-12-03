#include <string>
#include <vector>

#define pPar(x) getParentModule()->par(x)

std::string readFileAsString(const std::string& filePath);
std::vector<std::string> readFileLines(const std::string& filePath);
