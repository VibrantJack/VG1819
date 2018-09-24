#include "jsonextra.hpp"
#include <fstream>

nlohmann::json jsonIn(const std::string& p_filename) {
	std::ifstream input(p_filename);
	nlohmann::json jsontarget;
	if (input.is_open()) {
		input >> jsontarget;
		input.close();
	}
	else {
		throw std::exception("Something went wrong, file can't be opened."); // check if filename is correct.
		return nullptr;
	}

	return jsontarget;
}