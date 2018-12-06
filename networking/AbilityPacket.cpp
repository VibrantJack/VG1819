#include "networking\NetworkData.h"
#include "networking\ClientGame.h"

#include "unit\Unit.h"
#include "board\BoardManager.h"

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
	writeInt(p_buffer, this->m_sourceUnit);

	writeInt(p_buffer, this->m_numTargetUnits);
	networking::ClientGame* client = networking::ClientGame::getInstance();
	assert(client != nullptr);
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		int targetIndex = m_targets[i];
		writeInt(p_buffer, targetIndex);
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
}

void AbilityPacket::deserialize(Buffer& p_buffer)
{
	this->m_packetType = readInt(p_buffer);
	this->m_clientId = readInt(p_buffer);
	this->m_totalBytes = readInt(p_buffer);
	this->m_sourceUnit = readInt(p_buffer);

	m_numTargetUnits = readInt(p_buffer);	
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		int targetIndex = readInt(p_buffer);
		m_targets.push_back(targetIndex);
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
		+ sizeof(m_abilityNameLength);

	// sizeof all int values in TargetUnits vector
	int targetUnitsSize = sizeof(int) * m_numTargetUnits;

	// sizeof all string values and int values in IntValues map
	int intValuesSize = (sizeof(int) * m_numIntValues) + ((sizeof(char) * m_sumKeysLength)) + (sizeof(int) * m_numIntValues);

	// sizeof all int values in TargetTiles vector, note it's a vector of int pairs
	int  targetTilesSize = sizeof(int) * 2 * m_numTargetTiles;

	// sizeof ability name
	int abilityNameSize = m_abilityNameLength * sizeof(char);

	m_totalBytes = intVariablesSize + targetUnitsSize + intValuesSize + targetTilesSize + abilityNameSize + sizeof(int);

	return m_totalBytes;
}

void AbilityPacket::addTargetUnits(TargetUnits p_targets)
{
	m_numTargetUnits = p_targets.size();

	networking::ClientGame* client = networking::ClientGame::getInstance();
	assert(client != nullptr);

	std::vector<int> targets;
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		targets.push_back(client->getUnitGameObjectIndex(&p_targets[i]->getGameObject()));
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

const std::vector<unit::Unit*>& AbilityPacket::getTargetUnits()
{
	networking::ClientGame* client = networking::ClientGame::getInstance();
	assert(client != nullptr);

	m_targetObj.clear();
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		m_targetObj.push_back(client->getUnitGameObject(m_targets[i])->getComponent<unit::Unit>());
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