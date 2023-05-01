#include "Error.h"

void fatalError(std::string errorString) {
	std::cerr << errorString << std::endl;
	std::cerr << "Enter any key to quit " << std::endl;
	int tmp;
	std::cin >> tmp;
	exit(-1);
}
