#include "networking\NetworkData.h"
#include "networking\ClientGame.h"
#include "kitten\K_GameObjectManager.h"

#include "unit\Unit.h"
#include "board\BoardManager.h"
#include "kibble\databank\databank.hpp"
#include <sstream>

void AbilityPacket::print()
{
	printf("***** Packet Info *****\n\n");
	printf("PacketType: %d\n", m_packetType);
	printf("clientId: %d\n", m_clientId);
	printf("sourceUnit: %d\n", m_sourceUnit);
	printf("m_numTargetUnits: %d\nTarget Unit Indexes: ", m_numTargetUnits);
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		printf("%d, ", m_targets[i]);
	}

	printf("\nm_numIntValues: %d\nInt Values: ", m_numIntValues);
	for (auto it = m_intValue.begin(); it != m_intValue.end(); ++it)
	{
		printf("(Key: ");
		for (int i = 0; i < it->first.size(); ++i)
		{
			printf("%c", it->first.at(i));
		}
		printf(", Value: %d), ", it->second);
	}

	printf("\nm_numTargetTiles: %d\nTiles: ", m_numTargetTiles);
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		std::pair<int, int> tilePos = m_targetTiles[i];
		int posX = tilePos.first;
		int posY = tilePos.second;
		printf("(%d, %d), ", posX, posY);
	}

	printf("\nm_abilityNameLength: %d, Name: ", m_abilityNameLength);
	for (int i = 0; i < m_abilityNameLength; ++i)
	{
		printf("%c", m_abilityName[i]);
	}
	printf("\n\n*** End Packet Info ***\n");
}

std::string AbilityPacket::getFormattedAbilityInfo()
{
	std::stringstream message;
	message << "\tAbility Name: ";
	for (int i = 0; i < m_abilityNameLength; ++i)
	{
		message << m_abilityName[i];
	}

	if (m_unit.m_kibbleID != -1)
	{
		message << "\n\tSummoned Unit Kibble ID: " << m_unit.m_kibbleID << "\n";
	}

	message << "\tClient ID: " << m_clientId << "\n";

	unit::Unit* sourceUnitComp = getUnitFromPos(m_sourceUnit.posX, m_sourceUnit.posY);
	message << "\tSource Unit Kibble ID: " << sourceUnitComp->m_kibbleID << "\n";
	message << "\tSource Unit Pos: (" << m_sourceUnit.posX << ", " << m_sourceUnit.posY << ")\n";

	message << "\tNumber of Target Units: " << m_numTargetUnits << "\n";
	message << "\tTarget Units Kibble IDs:\n\t\t";
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		UnitPos pos = m_targets[i];
		TileInfo* info = BoardManager::getInstance()->getTile(pos.posX, pos.posY)->getComponent<TileInfo>();;
		unit::Unit* unit = info->getUnit()->getComponent<unit::Unit>();
		message << unit->m_kibbleID << "(Pos: " << pos.posX << ", " << pos.posY << "), ";
	}
	message << "\n\tNumber of Int Values: " << m_numIntValues << "\n";
	message << "\tInt Values:\n";
	for (auto it = m_intValue.begin(); it != m_intValue.end(); ++it)
	{
		message << "\t\t(Key: ";
		for (int i = 0; i < it->first.size(); ++i)
		{
			message << it->first.at(i);
		}
		message << ", Value: " << it->second << ")\n";
	}

	message << "\tNumber of Target Tiles: " << m_numTargetTiles << "\n";
	message << "\tTiles:\n";
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		std::pair<int, int> tilePos = m_targetTiles[i];
		int posX = tilePos.first;
		int posY = tilePos.second;
		message << "\t\t(" << posX << ", " << posY << ")\n";
	}

	if (m_clickedObjectPos.first > -1)
	{
		message << "\tm_clickedObjectPos: " << m_clickedObjectPos.first << ", " << m_clickedObjectPos.second;
	}

	return message.str();
}

// If an assert is failed, make sure you are using a fresh Buffer for serializing
// and a fresh one for deserializing
void AbilityPacket::writeInt(Buffer& p_buffer, int p_value)
{
	assert(p_buffer.m_index + sizeof(int) <= p_buffer.m_size);
	
	*((int*)(p_buffer.m_data + p_buffer.m_index)) = p_value;
	p_buffer.m_index += sizeof(int);
}

void AbilityPacket::writeChar(Buffer &p_buffer, char p_value)
{
	assert(p_buffer.m_index + sizeof(char) <= p_buffer.m_size);

	*((char*)(p_buffer.m_data + p_buffer.m_index)) = p_value;
	p_buffer.m_index += sizeof(char);
}

int AbilityPacket::readInt(Buffer& p_buffer)
{
	// For ResizeablePacket, Can't check against buffer size when reading as the size is set
	// from a non constant value (getsize()), so we don't know that actual size that the buffer should be
	// unless we set it to the number of bytes read
	//assert(buffer.m_index + sizeof(int) <= buffer.m_size);

	int value;
	value = *((int*)(p_buffer.m_data + p_buffer.m_index));
	p_buffer.m_index += sizeof(int);

	return value;
}

char AbilityPacket::readChar(Buffer &p_buffer)
{
	//assert(buffer.m_index + sizeof(char) <= buffer.m_size);

	char value;
	value = *((char*)(p_buffer.m_data + p_buffer.m_index));
	p_buffer.m_index += sizeof(char);

	return value;
}

void AbilityPacket::serialize(Buffer& p_buffer)
{
	writeInt(p_buffer, this->m_packetType);
	writeInt(p_buffer, this->m_clientId);
	writeInt(p_buffer, this->m_totalBytes);
	writeInt(p_buffer, this->m_sourceUnit.posX);
	writeInt(p_buffer, this->m_sourceUnit.posY);

	writeInt(p_buffer, this->m_numTargetUnits);
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		auto pos = m_targets[i];
		writeInt(p_buffer, pos.posX);
		writeInt(p_buffer, pos.posY);
	}

	writeInt(p_buffer, this->m_numIntValues);
	for (auto it = m_intValue.begin(); it != m_intValue.end(); ++it)
	{
		// For each key, value pair in the map, we need to:
		// Get the key, the length of the key, and then write each char in the key to the buffer
		// Finally, write the value tied to the key to the buffer
		std::string strKey = it->first;
		char key[MAX_CHAR_BUFSIZE];
		strcpy(key, strKey.c_str());
		int keyLength = strKey.size();

		writeInt(p_buffer, keyLength);
		for (int i = 0; i < keyLength; ++i)
		{
			writeChar(p_buffer, key[i]);
		}
		writeInt(p_buffer, it->second);
	}

	writeInt(p_buffer, this->m_numTargetTiles);
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		std::pair<int,int> tilePos = m_targetTiles[i];
		int posX = tilePos.first;
		int posY = tilePos.second;
		writeInt(p_buffer, posX);
		writeInt(p_buffer, posY);
	}

	// AbilityName
	writeInt(p_buffer, m_abilityNameLength);
	for (int i = 0; i < m_abilityNameLength; ++i)
	{
		writeChar(p_buffer, m_abilityName[i]);
	}

	// Unit Data
	writeInt(p_buffer, m_unit.m_kibbleID);
	writeInt(p_buffer, m_unit.m_HP);
	writeInt(p_buffer, m_unit.m_maxHP);
	writeInt(p_buffer, m_unit.m_IN);
	writeInt(p_buffer, m_unit.m_baseIN);
	writeInt(p_buffer, m_unit.m_MV);
	writeInt(p_buffer, m_unit.m_baseMV);
	writeInt(p_buffer, m_unit.m_cost);
	writeInt(p_buffer, m_unit.m_baseCost);

	// AbilityInfoPacket::m_clickedObject
	writeInt(p_buffer, m_clickedObjectPos.first);
	writeInt(p_buffer, m_clickedObjectPos.second);
}

void AbilityPacket::deserialize(Buffer& p_buffer)
{
	this->m_packetType = readInt(p_buffer);
	this->m_clientId = readInt(p_buffer);
	this->m_totalBytes = readInt(p_buffer);

	this->m_sourceUnit.posX = readInt(p_buffer);
	this->m_sourceUnit.posY = readInt(p_buffer);

	m_numTargetUnits = readInt(p_buffer);	
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		UnitPos unit;
		unit.posX = readInt(p_buffer);
		unit.posY = readInt(p_buffer);
		m_targets.push_back(unit);
	}

	m_numIntValues = readInt(p_buffer);
	for (int i = 0; i < m_numIntValues; ++i)
	{
		int keyLength = readInt(p_buffer);
		std::string key = "";
		for (int j = 0; j < keyLength; ++j)
		{
			key += readChar(p_buffer);
		}
		int value = readInt(p_buffer);
		m_intValue.insert({ key, value });
	}

	m_numTargetTiles = readInt(p_buffer);
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		int posX = readInt(p_buffer);
		int posY = readInt(p_buffer);
		m_targetTiles.push_back(std::make_pair(posX, posY));
	}

	m_abilityNameLength = readInt(p_buffer);	
	for (int i = 0; i < m_abilityNameLength; ++i)
	{
		m_abilityName += readChar(p_buffer);
	}

	// Unit Data
	m_unit.m_kibbleID = readInt(p_buffer);
	m_unit.m_HP = readInt(p_buffer);
	m_unit.m_maxHP = readInt(p_buffer);
	m_unit.m_IN = readInt(p_buffer);
	m_unit.m_baseIN = readInt(p_buffer);
	m_unit.m_MV = readInt(p_buffer);
	m_unit.m_baseMV = readInt(p_buffer);
	m_unit.m_cost = readInt(p_buffer);
	m_unit.m_baseCost = readInt(p_buffer);

	// AbilityInfoPacket::m_clickedObject
	m_clickedObjectPos.first = readInt(p_buffer);
	m_clickedObjectPos.second = readInt(p_buffer);
}

int AbilityPacket::getSize()
{
	// sizeof all member int variables
	int intVariablesSize = 
		sizeof(m_packetType) 
		+ sizeof(m_clientId) 
		+ sizeof(m_sourceUnit)
		+ sizeof(m_numTargetUnits) 
		+ sizeof(m_numIntValues) 
		+ sizeof(m_numTargetTiles)
		+ sizeof(m_abilityNameLength)
		+ sizeof(m_unit)
		+ sizeof(m_clickedObjectPos);

	// sizeof all int values in TargetUnits vector
	int targetUnitsSize = sizeof(int) * 2 * m_numTargetUnits;

	// sizeof all string values and int values in IntValues map
	int intValuesSize = (sizeof(int) * m_numIntValues) + ((sizeof(char) * m_sumKeysLength)) + (sizeof(int) * m_numIntValues);

	// sizeof all int values in TargetTiles vector, note it's a vector of int pairs
	int  targetTilesSize = sizeof(int) * 2 * m_numTargetTiles;

	// sizeof ability name
	int abilityNameSize = m_abilityNameLength * sizeof(char);

	m_totalBytes = intVariablesSize + targetUnitsSize + intValuesSize + targetTilesSize + abilityNameSize + sizeof(int);

	return m_totalBytes;
}

void AbilityPacket::extractFromPackage(ability::AbilityInfoPackage* p_package)
{
	m_sourceUnit = getPosFromUnit(p_package->m_source);
	addTargetUnits(p_package->m_targets);
	addIntValues(p_package->m_intValue);
	addTargetTiles(p_package->m_targetTilesGO);

	if (p_package->m_cardGOForUnitSummon != nullptr)
	{
		addUnitData(p_package->m_cardGOForUnitSummon->getComponent<unit::Unit>());
	}

	if (p_package->m_clickedObject != nullptr)
	{
		TileInfo* tile = p_package->m_clickedObject->getComponent<TileInfo>();
		if (tile != nullptr)
		{
			m_clickedObjectPos = { tile->getPosX(), tile->getPosY() };
		}
	}
}

void AbilityPacket::insertIntoPackage(ability::AbilityInfoPackage* p_package)
{
	p_package->m_source = getUnitFromPos(m_sourceUnit.posX, m_sourceUnit.posY);
	p_package->m_targets = getTargetUnits();
	p_package->m_intValue = getIntValues();
	p_package->m_targetTilesGO = getTargetTiles();

	kitten::K_GameObject* unitGO = nullptr;
	unit::Unit* unitComp = getUnit();
	if (unitComp != nullptr)
	{
		unitGO = kitten::K_GameObjectManager::getInstance()->createNewGameObject();
		unitGO->addComponent(unitComp);
	}	
	p_package->m_cardGOForUnitSummon = unitGO;

	if (m_clickedObjectPos.first > -1)
	{
		p_package->m_clickedObject = BoardManager::getInstance()->getTile(m_clickedObjectPos.first, m_clickedObjectPos.second);
	}
}

void AbilityPacket::addTargetUnits(TargetUnits p_targets)
{
	m_numTargetUnits = p_targets.size();

	networking::ClientGame* client = networking::ClientGame::getInstance();
	assert(client != nullptr);

	std::vector<UnitPos> targets;
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		//targets.push_back(client->getUnitGameObjectIndex(&p_targets[i]->getGameObject()));
		TileInfo* tile = p_targets[i]->getTile()->getComponent<TileInfo>();
		UnitPos unit;
		unit.posX = tile->getPosX();
		unit.posY = tile->getPosY();
		targets.push_back(unit);
	}
	m_targets = targets;
}

void AbilityPacket::addIntValues(IntValues p_values)
{
	m_numIntValues = p_values.size();
	m_intValue = p_values;

	for (auto it = m_intValue.begin(); it != m_intValue.end(); ++it)
	{
		std::string strKey = it->first;
		m_sumKeysLength += strKey.size();
	}
}

void AbilityPacket::addTargetTiles(TargetTiles p_targetTilesGO)
{
	m_numTargetTiles = p_targetTilesGO.size();

	BoardManager* board = BoardManager::getInstance();
	assert(board != nullptr);

	std::vector<std::pair<int, int>> tiles;
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		TileInfo* tileInfo = p_targetTilesGO[i]->getComponent<TileInfo>();
		int x = tileInfo->getPosX();
		int y = tileInfo->getPosY();
		tiles.push_back(std::make_pair(x, y));
	}
	m_targetTiles = tiles;
}

void AbilityPacket::addUnitData(unit::Unit* p_unit)
{
	m_unit.m_kibbleID = p_unit->m_kibbleID;

	m_unit.m_HP = p_unit->m_attributes[UNIT_HP];
	m_unit.m_maxHP = p_unit->m_attributes[UNIT_HP];

	m_unit.m_IN = p_unit->m_attributes[UNIT_IN];
	m_unit.m_baseIN = p_unit->m_attributes[UNIT_BASE_IN];

	m_unit.m_MV = p_unit->m_attributes[UNIT_MV];
	m_unit.m_baseMV = p_unit->m_attributes[UNIT_BASE_MV];

	m_unit.m_cost = p_unit->m_attributes[UNIT_COST];
	m_unit.m_baseCost = p_unit->m_attributes[UNIT_BASE_COST];
}

const std::vector<unit::Unit*>& AbilityPacket::getTargetUnits()
{
	networking::ClientGame* client = networking::ClientGame::getInstance();
	assert(client != nullptr);

	m_targetObj.clear();
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		int x = m_targets[i].posX;
		int y = m_targets[i].posY;

		unit::Unit* unit = getUnitFromPos(x, y);
		m_targetObj.push_back(unit);
	}

	return m_targetObj;
}

const std::unordered_map<std::string, int>& AbilityPacket::getIntValues()
{
	return m_intValue;
}

const std::vector<kitten::K_GameObject*>& AbilityPacket::getTargetTiles()
{
	BoardManager* board = BoardManager::getInstance();
	assert(board != nullptr);

	m_targetTilesGO.clear();
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		int x = m_targetTiles[i].first;
		int y = m_targetTiles[i].second;
		kitten::K_GameObject* tile = board->getTile(x, y);		
		m_targetTilesGO.push_back(tile);
	}

	return m_targetTilesGO;
}

unit::Unit* AbilityPacket::getUnit()
{
	if (m_unit.m_kibbleID == -1)
		return nullptr;

	// Create a copy of the unit component grabbed from kibble
	unit::Unit* unit = kibble::getUnitInstanceFromId(m_unit.m_kibbleID);

	unit->m_attributes[UNIT_HP] = m_unit.m_HP;
	unit->m_attributes[UNIT_HP] = m_unit.m_maxHP;

	unit->m_attributes[UNIT_IN] = m_unit.m_IN;
	unit->m_attributes[UNIT_BASE_IN] = m_unit.m_baseIN;

	unit->m_attributes[UNIT_MV] = m_unit.m_MV;
	unit->m_attributes[UNIT_BASE_MV] = m_unit.m_baseMV;

	unit->m_attributes[UNIT_COST] = m_unit.m_cost;
	unit->m_attributes[UNIT_BASE_COST] = m_unit.m_baseCost;

	return unit;
}