#pragma once
#include "json.hpp"
#include <fstream>

nlohmann::json jsonIn(const std::string& p_filename);