#include "Error.h"
#include "fileloader.h"

char* getFileContent(const std::string filename, bool binary) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (file.is_open()) {
		size_t len = file.tellg();
		char* buffer = new char[len + (size_t)(!binary)] { 0 };
		file.seekg(0, std::ios::beg);
		file.read(buffer, len);
		file.close();
		return buffer;
	} else {
		std::cerr << std::endl << "[ERROR]: file '" << filename << "' does not exist!" << std::endl;
		fatalError("File NOT FOUND");
		return nullptr;
	}
}


void readFileContent(const std::string filename, std::vector<unsigned char>& buffer) {
	std::ifstream file(filename, std::ios::ate | std::ios::binary);
	if (file.is_open()) {
		size_t len = file.tellg();
		buffer.resize(len);
		file.seekg(0, std::ios::beg);
		file.read((char*)&buffer[0], len);
		file.close();
	} else {
		std::cerr << std::endl << "[ERROR]: file '" << filename << "' does not exist!" << std::endl;
		fatalError("File NOT FOUND");
	}
}