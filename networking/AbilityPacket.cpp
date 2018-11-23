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
		std::pair<int, int> tilePos = m_targetTilesGO[i];
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
void AbilityPacket::writeInt(Buffer& buffer, int value)
{
	assert(buffer.m_index + sizeof(int) <= buffer.m_size);
	
	*((int*)(buffer.m_data + buffer.m_index)) = value;
	buffer.m_index += sizeof(int);
}

void AbilityPacket::writeChar(Buffer &buffer, char value)
{
	assert(buffer.m_index + sizeof(char) <= buffer.m_size);

	*((char*)(buffer.m_data + buffer.m_index)) = value;
	buffer.m_index += sizeof(char);
}

int AbilityPacket::readInt(Buffer& buffer)
{
	// For ResizeablePacket, Can't check against buffer size when reading as the size is set
	// from a non constant value (getsize()), so we don't know that actual size that the buffer should be
	// unless we set it to the number of bytes read
	//assert(buffer.m_index + sizeof(int) <= buffer.m_size);

	int value;
	value = *((int*)(buffer.m_data + buffer.m_index));
	buffer.m_index += sizeof(int);

	return value;
}

char AbilityPacket::readChar(Buffer &buffer)
{
	//assert(buffer.m_index + sizeof(char) <= buffer.m_size);

	char value;
	value = *((char*)(buffer.m_data + buffer.m_index));
	buffer.m_index += sizeof(char);

	return value;
}

void AbilityPacket::serialize(Buffer& buffer)
{
	writeInt(buffer, this->m_packetType);
	writeInt(buffer, this->m_clientId);
	writeInt(buffer, this->m_totalBytes);
	writeInt(buffer, this->m_sourceUnit);

	writeInt(buffer, this->m_numTargetUnits);
	networking::ClientGame* client = networking::ClientGame::getInstance();
	assert(client != nullptr);
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		int targetIndex = m_targets[i];
		writeInt(buffer, targetIndex);
	}

	writeInt(buffer, this->m_numIntValues);
	for (auto it = m_intValue.begin(); it != m_intValue.end(); ++it)
	{
		// For each key, value pair in the map, we need to:
		// Get the key, the length of the key, and then write each char in the key to the buffer
		// Finally, write the value tied to the key to the buffer
		std::string strKey = it->first;
		char key[MAX_CHAR_BUFSIZE];
		strcpy(key, strKey.c_str());
		int keyLength = strKey.size();

		writeInt(buffer, keyLength);
		for (int i = 0; i < keyLength; ++i)
		{
			writeChar(buffer, key[i]);
		}
		writeInt(buffer, it->second);
	}

	writeInt(buffer, this->m_numTargetTiles);
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		std::pair<int,int> tilePos = m_targetTilesGO[i];
		int posX = tilePos.first;
		int posY = tilePos.second;
		writeInt(buffer, posX);
		writeInt(buffer, posY);
	}

	// AbilityName
	writeInt(buffer, m_abilityNameLength);
	for (int i = 0; i < m_abilityNameLength; ++i)
	{
		writeChar(buffer, m_abilityName[i]);
	}
}

void AbilityPacket::deserialize(Buffer& buffer)
{
	this->m_packetType = readInt(buffer);
	this->m_clientId = readInt(buffer);
	this->m_totalBytes = readInt(buffer);
	this->m_sourceUnit = readInt(buffer);

	m_numTargetUnits = readInt(buffer);	
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		int targetIndex = readInt(buffer);
		m_targets.push_back(targetIndex);
	}

	m_numIntValues = readInt(buffer);
	for (int i = 0; i < m_numIntValues; ++i)
	{
		int keyLength = readInt(buffer);
		std::string key = "";
		for (int j = 0; j < keyLength; ++j)
		{
			key += readChar(buffer);
		}
		int value = readInt(buffer);
		m_intValue.insert({ key, value });
	}

	m_numTargetTiles = readInt(buffer);
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		int posX = readInt(buffer);
		int posY = readInt(buffer);
		m_targetTilesGO.push_back(std::make_pair(posX, posY));
	}

	m_abilityNameLength = readInt(buffer);	
	for (int i = 0; i < m_abilityNameLength; ++i)
	{
		m_abilityName += readChar(buffer);
	}
}

int AbilityPacket::getSize()
{
	/*int total = 0;
	total += sizeof(packetType);
	total += sizeof(clientId);
	total += sizeof(sourceUnit);
	total += sizeof(m_numTargetUnits);
	total += sizeof(int) * m_numTargetUnits; printf("Calculated TargetUnits size: %d\n", sizeof(int) * m_numTargetUnits);
	total += sizeof(m_numIntValues);
	total += sizeof(int) * m_numIntValues;
	total += sizeof(char) * sumKeysLength;
	total += sizeof(int) * m_numIntValues; printf("Calculated IntValues size: %d\n", (sizeof(int) * m_numIntValues) + (sizeof(char) * sumKeysLength) + (sizeof(int) * m_numIntValues));
	total += sizeof(m_numTargetTiles);
	total += sizeof(int) * 2 * m_numTargetTiles; printf("Calculated TargetTiles size: %d\n", sizeof(int) * 2 * m_numTargetTiles);
	total += sizeof(m_abilityNameLength);
	total += sizeof(char) * m_abilityNameLength; printf("Calculated AbilityName size: %d\n", sizeof(char) * m_abilityNameLength);*/

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
	m_targetTilesGO = tiles;
}

std::vector<unit::Unit*> AbilityPacket::getTargetUnits()
{
	networking::ClientGame* client = networking::ClientGame::getInstance();
	assert(client != nullptr);

	TargetUnits targetUnits;
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		targetUnits.push_back(client->getUnitGameObject(m_targets[i])->getComponent<unit::Unit>());
	}

	return targetUnits;
}

std::unordered_map<std::string, int> AbilityPacket::getIntValues()
{
	return m_intValue;
}

std::vector<kitten::K_GameObject*> AbilityPacket::getTargetTiles()
{
	BoardManager* board = BoardManager::getInstance();
	assert(board != nullptr);

	TargetTiles targetTiles;
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		int x = m_targetTilesGO[i].first;
		int y = m_targetTilesGO[i].second;
		kitten::K_GameObject* tile = board->getTile(x, y);		
		targetTiles.push_back(tile);
	}

	return targetTiles;
}