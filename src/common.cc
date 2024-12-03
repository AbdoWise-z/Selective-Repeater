/*
 * common.cc
 *
 *  Created on: Nov 27, 2024
 *      Author: xAbdoMo
 */

#include "common.h"

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

std::string readFileAsString(const std::string& filePath){
    std::ifstream file(filePath); // Open the file

    if (!file) {
        throw std::ios_base::failure("Failed to open file: " + filePath);
    }

    std::ostringstream contentStream;
    contentStream << file.rdbuf(); // Read the file buffer into the stream
    file.close();

    return contentStream.str(); // Return the file contents as a string
}


std::vector<std::string> readFileLines(const std::string& filePath){
    auto content = readFileAsString(filePath);

    std::vector<std::string> result;
    std::istringstream stream(content);
    std::string line;

    while (std::getline(stream, line)) {
        result.push_back(line);
    }

    return result;
}




