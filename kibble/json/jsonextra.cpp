#include "jsonextra.hpp"
#include <fstream>

nlohmann::json jsonIn(std::string filename) {
	std::ifstream input(filename);
	nlohmann::json jsontarget;
	if (input.is_open()) {
		input >> jsontarget;
		input.close();
	}
	else {
		throw std::exception("Something went wrong, file can't be opened."); // check if filename is correct.
	}

	return jsontarget;
}