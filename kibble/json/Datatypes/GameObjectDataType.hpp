#pragma once
#include "kibble/json/jsonextra.hpp"
#include "kitten/K_GameObject.h"
#include <string>

kitten::K_GameObject* getGameObjectBy(nlohmann::json& p_jsonfile);