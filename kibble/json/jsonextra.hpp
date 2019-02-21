#pragma once
#include "json.hpp"
#include <fstream>

nlohmann::json jsonIn(const std::string& p_filename);

#define JSONHAS(str) p_json.find(str) != p_json.end()

#define LOOKUP(str) (p_json[str])
#define LOOKUPSTR(str) (LOOKUP(str).get<std::string>())
#define LOOKUPCHAR(str) (LOOKUP(str).get<std::string>()[0])
#define LOOKUPVEC3(str) (glm::vec3(LOOKUP(str)[0], LOOKUP(str)[1], LOOKUP(str)[2]))

#define LOOKUPDEF(str, defaultVal) ((JSONHAS(str))? LOOKUP(str) : (defaultVal))
#define LOOKUPSTRDEF(str, defaultVal)  ((JSONHAS(str))? LOOKUPSTR(str) : (defaultVal))
#define LOOKUPCHARDEF(str, defaultVal)  ((JSONHAS(str))? LOOKUPCHAR(str) : (defaultVal))
#define LOOKUPVEC3DEF(str, defaultVal)  ((JSONHAS(str))? LOOKUPVEC3(str) : (defaultVal))

#define SET(varName,jsonName) varName = LOOKUP(jsonName)
#define SETSTR(varName,jsonName) varName = LOOKUPSTR(jsonName)
#define SETCHAR(varName,jsonName) varName = LOOKUPCHAR(jsonName)
#define SETVEC3(varName,jsonName) varName = LOOKUPVEC3(jsonName)

#define SETOPT(varName,jsonName) if(JSONHAS(jsonName)) SET(varName,jsonName)
#define SETSTROPT(varName,jsonName) if(JSONHAS(jsonName)) SETSTR(varName,jsonName)
#define SETCHAROPT(varName,jsonName) if(JSONHAS(jsonName)) SETCHAR(varName,jsonName)
#define SETVEC3OPT(varName,jsonName) if(JSONHAS(jsonName)) SETVEC3(varName,jsonName)

#define SETOPTDEF(varName,jsonName,defaultVal) varName = LOOKUPDEF(jsonName,defaultVal)
#define SETSTROPTDEF(varName,jsonName,defaultVal) varName = LOOKUPSTRDEF(jsonName,defaultVal)
#define SETCHAROPTDEF(varName,jsonName,defaultVal) varName = LOOKUPCHARDEF(jsonName,defaultVal)
#define SETVEC3OPTDEF(varName,jsonName,defaultVal) varName = LOOKUPVEC3DEF(jsonName,defaultVal)
