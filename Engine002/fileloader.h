#pragma once
#include <string>
#include <fstream>
#include <iostream>
#include <vector>

char* getFileContent(const std::string filename, bool binary = false);
void readFileContent(const std::string filename, std::vector<unsigned char>& buffer);