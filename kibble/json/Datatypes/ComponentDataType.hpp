#pragma once
#include "kibble/json/jsonextra.hpp"
#include "kitten/K_Component.h"
#include <string>

kitten::K_Component* getRelatedComponentBy(std::string key, nlohmann::json* jsonfile);
void setupComponentMap();