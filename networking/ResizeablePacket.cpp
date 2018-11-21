#include "networking\NetworkData.h"
#include "networking\ClientGame.h"

#include "unit\Unit.h"
#include "board\BoardManager.h"

void ResizeablePacket::print(ResizeablePacket& packet)
{
	networking::ClientGame* client = networking::ClientGame::getInstance();
	printf("PacketType: %d\n", packet.packetType);
	printf("clientId: %d\n", packet.clientId);
	printf("sourceUnit: %d\n", packet.sourceUnit);
	printf("m_numTargetUnits: %d\nTarget Units: ", packet.m_numTargetUnits);
	for (int i = 0; i < packet.m_numTargetUnits; ++i)
	{
		packet.m_targets.at(i);
		printf("%d, ", client->getUnitGameObjectIndex(&m_targets[i]->getGameObject()));
	}

	printf("\m_numIntValues: %d\nInt Values: ", packet.m_numIntValues);
	for (auto it = packet.m_intValue.begin(); it != packet.m_intValue.end(); ++it)
	{
		printf("Key: ");
		for (int i = 0; i < it->first.size(); ++i)
		{
			printf("%c", packet.m_abilityName[i]);
		}
		printf(", Value: %d\n", it->second);
	}

	printf("\nm_numTargetTiles: %d\n Tiles: ", packet.m_numTargetTiles);
	for (int i = 0; i < m_numTargetTiles; ++i)
	{
		TileInfo* tileInfo = m_targetTilesGO[i]->getComponent<TileInfo>();
		int posX = tileInfo->getPosX();
		int posY = tileInfo->getPosY();
		printf("(%d, %d), ", posX, posY);
	}

	printf("\nm_abilityNameLength: %d, Name: ", packet.m_abilityNameLength);
	for (int i = 0; i < packet.m_abilityNameLength; ++i)
	{
		printf("%c", packet.m_abilityName[i]);
	}
}

// If an assert is failed, make sure you are using a fresh Buffer for serializing
// and a fresh one for deserializing
void ResizeablePacket::writeInt(Buffer& buffer, int value)
{
	assert(buffer.m_index + sizeof(int) <= buffer.m_size);
	
	*((int*)(buffer.m_data + buffer.m_index)) = value;
	buffer.m_index += sizeof(int);
}

void ResizeablePacket::writeChar(Buffer &buffer, char value)
{
	assert(buffer.m_index + sizeof(char) <= buffer.m_size);

	*((char*)(buffer.m_data + buffer.m_index)) = value;
	buffer.m_index += sizeof(char);
}

int ResizeablePacket::readInt(Buffer& buffer)
{
	assert(buffer.m_index + sizeof(int) <= buffer.m_size);

	int value;
	value = *((int*)(buffer.m_data + buffer.m_index));
	buffer.m_index += sizeof(int);

	return value;
}

char ResizeablePacket::readChar(Buffer &buffer)
{
	assert(buffer.m_index + sizeof(char) <= buffer.m_size);

	char value;
	value = *((char*)(buffer.m_data + buffer.m_index));
	buffer.m_index += sizeof(char);

	return value;
}

void ResizeablePacket::serialize(Buffer& buffer)
{
	writeInt(buffer, this->packetType);
	writeInt(buffer, this->clientId);
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
		//char key[BUFSIZE];
		char * key = new char(strKey.size());
		strcpy(key, strKey.c_str());
		int keyLength = strKey.size();
				
		writeInt(buffer, keyLength);
		for (int i = 0; i < keyLength; ++i)
		{
			writeChar(buffer, key[i]);
		}
		writeInt(buffer, it->second);
		delete[] key;
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

void ResizeablePacket::deserialize(Buffer& buffer)
{
	this->packetType = readInt(buffer);
	this->clientId = readInt(buffer);
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
		char key[BUFSIZE];
		for (int j = 0; j < keyLength; ++j)
		{
			key[i] = readChar(buffer);
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
		m_abilityName[i] = readChar(buffer);
	}
}

int ResizeablePacket::getSize()
{
	// sizeof all declared int variables
	int intVariablesSize = sizeof(int) * 6;

	// sizeof all int values in TargetUnits vector
	int targetUnitsSize = sizeof(int) * m_targets.size();

	// sizeof all string values and int values in IntValues map
	int intValuesSize = (sizeof(char[BUFSIZE]) * m_intValue.size()) + (sizeof(int) * m_intValue.size());

	// sizeof all int values in TargetTiles vector, note it's a vector of int pairs
	int  targetTilesSize = sizeof(int) * 2 * m_targetTilesGO.size();


	return intVariablesSize + targetUnitsSize + intValuesSize + targetTilesSize;
}

//void ResizeablePacket::addTargetUnits(std::vector<unit::Unit*> p_targets)
//{
//	// Create vector of unit index ints for easier serialization
//
//	networking::ClientGame* client = networking::ClientGame::getInstance();
//	assert(client != nullptr);
//
//	TargetUnits targetUnits;
//	for (auto it = p_targets.begin(); it != p_targets.end(); ++it)
//	{
//		targetUnits.push_back(client->getUnitGameObjectIndex(&(*it)->getGameObject()));
//	}
//	m_targets = targetUnits;
//	m_numTargetUnits = m_targets.size();
//}
//
//void ResizeablePacket::addIntValues(IntValues p_values)
//{
//	m_intValue = p_values;
//	m_numIntValues = p_values.size();
//}
//
//void ResizeablePacket::addTargetTiles(std::vector<kitten::K_GameObject*> p_targetTilesGO)
//{
//	// Create vector of unit index ints
//	TargetTiles targetTiles;
//	for (int i = 0; i < p_targetTilesGO.size(); ++i)
//	{
//		TileInfo* tileInfo = p_targetTilesGO[i]->getComponent<TileInfo>();
//		int posX = tileInfo->getPosX();
//		int posY = tileInfo->getPosY();
//
//		targetTiles.push_back(std::make_pair(posX, posY));
//	}
//	m_targetTilesGO = targetTiles;
//
//	m_numTargetTiles = m_targetTilesGO.size();
//}