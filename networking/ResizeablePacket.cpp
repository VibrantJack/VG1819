#include "networking\NetworkData.h"
#include "networking\ClientGame.h"

#include "unit\Unit.h"
#include "board\BoardManager.h"

void AbilityPacket::print()
{
	networking::ClientGame* client = networking::ClientGame::getInstance();
	printf("*** Packet Info ***\n");
	printf("PacketType: %d\n", packetType);
	printf("clientId: %d\n", clientId);
	printf("sourceUnit: %d\n", sourceUnit);
	printf("m_numTargetUnits: %d\nTarget Units: ", m_numTargetUnits);
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		printf("%d, ", client->getUnitGameObjectIndex(&m_targets[i]->getGameObject()));
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
		TileInfo* tileInfo = m_targetTilesGO[i]->getComponent<TileInfo>();
		int posX = tileInfo->getPosX();
		int posY = tileInfo->getPosY();
		printf("(%d, %d), ", posX, posY);
	}

	printf("\nm_abilityNameLength: %d, Name: ", m_abilityNameLength);
	for (int i = 0; i < m_abilityNameLength; ++i)
	{
		printf("%c", m_abilityName[i]);
	}
	printf("\n");
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
	writeInt(buffer, this->packetType);
	writeInt(buffer, this->clientId);
	writeInt(buffer, this->totalBytes);
	writeInt(buffer, this->sourceUnit);

	writeInt(buffer, this->m_numTargetUnits);
	networking::ClientGame* client = networking::ClientGame::getInstance();
	assert(client != nullptr);
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		int targetIndex = client->getUnitGameObjectIndex(&m_targets[i]->getGameObject());
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
		TileInfo* tileInfo = m_targetTilesGO[i]->getComponent<TileInfo>();
		int posX = tileInfo->getPosX();
		int posY = tileInfo->getPosY();
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
	this->packetType = readInt(buffer);
	this->clientId = readInt(buffer);
	this->totalBytes = readInt(buffer);
	this->sourceUnit = readInt(buffer);

	networking::ClientGame* client = networking::ClientGame::getInstance();
	assert(client != nullptr);
	m_numTargetUnits = readInt(buffer);	
	for (int i = 0; i < m_numTargetUnits; ++i)
	{
		int targetIndex = readInt(buffer);
		unit::Unit* targetUnit = client->getUnitGameObject(targetIndex)->getComponent<unit::Unit>();
		m_targets.push_back(targetUnit);
	}

	m_numIntValues = readInt(buffer);
	for (int i = 0; i < m_numIntValues; ++i)
	{
		int keyLength = readInt(buffer);
		//char key[BUFSIZE];
		std::string key = "";
		for (int j = 0; j < keyLength; ++j)
		{
			//key[i] = readChar(buffer);
			key += readChar(buffer);
		}
		int value = readInt(buffer);
		m_intValue.insert({ key, value });
	}

	BoardManager* board = BoardManager::getInstance();
	assert(board != nullptr);
	m_numTargetTiles = readInt(buffer);
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		int posX = readInt(buffer);
		int posY = readInt(buffer);
		
		m_targetTilesGO.push_back(board->getTile(posX, posY));
	}

	m_abilityNameLength = readInt(buffer);	
	for (int i = 0; i < m_abilityNameLength; ++i)
	{
		//m_abilityName[i] = readChar(buffer);
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
		sizeof(packetType) 
		+ sizeof(clientId) 
		+ sizeof(sourceUnit)
		+ sizeof(m_numTargetUnits) 
		+ sizeof(m_numIntValues) 
		+ sizeof(m_numTargetTiles)
		+ sizeof(m_abilityNameLength);

	// sizeof all int values in TargetUnits vector
	int targetUnitsSize = sizeof(int) * m_numTargetUnits;

	// sizeof all string values and int values in IntValues map
	int intValuesSize = (sizeof(int) * m_numIntValues) + ((sizeof(char) * sumKeysLength)) + (sizeof(int) * m_numIntValues);

	// sizeof all int values in TargetTiles vector, note it's a vector of int pairs
	int  targetTilesSize = sizeof(int) * 2 * m_numTargetTiles;

	// sizeof ability name
	int abilityNameSize = m_abilityNameLength * sizeof(char);

	totalBytes = intVariablesSize + targetUnitsSize + intValuesSize + targetTilesSize + abilityNameSize + sizeof(int);

	return totalBytes;
}

void AbilityPacket::addTargetUnits(TargetUnits p_targets)
{
	m_numTargetUnits = p_targets.size();
	m_targets = p_targets;
}

void AbilityPacket::addIntValues(IntValues p_values)
{
	m_numIntValues = p_values.size();
	m_intValue = p_values;

	for (auto it = m_intValue.begin(); it != m_intValue.end(); ++it)
	{
		std::string strKey = it->first;
		sumKeysLength += strKey.size();
	}
}

void AbilityPacket::addTargetTiles(TargetTiles p_targetTilesGO)
{
	m_numTargetTiles = p_targetTilesGO.size();
	m_targetTilesGO = p_targetTilesGO;
}