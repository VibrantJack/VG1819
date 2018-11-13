#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "networking\ClientNetwork.h"
#include "networking\NetworkData.h"

#include "kitten\K_GameObject.h"
#include <map>

// Ability 
#include "ability\AbilityInfoPackage.h"

namespace networking
{
	class ClientGame
	{
	private:
		static ClientGame* sm_clientGameInstance;
		ClientGame(const std::string &p_strAddr);
		~ClientGame();
	public:

		static void createInstance(const std::string &p_strAddr = "127.0.0.1");
		static void destroyInstance();
		static ClientGame* getInstance();
		static bool isNetworkValid() { return sm_networkValid; }

		void setupNetwork(const std::string &p_strAddr = "127.0.0.1");
		void disconnectFromNetwork(bool p_bServerShutdown = false);
		//void shutdown(bool p_bServerShutdown = false); // Group up disconnectFromNetwork and destroyInstance? 

		void update();

		int getUnitGameObjectIndex(kitten::K_GameObject* p_unit);
		void removeUnitGameObject(int p_iUnitIndex);
		int getClientId() { return m_iClientId; }

		void summonUnit(int p_iClientId, int p_iUnitId, int p_iPosX, int p_iPosY);
		void moveUnit(int p_iUnitIndex, int p_iPosX, int p_iPosY);

		void sendPacket(Packet* p_packet);
		void sendAbilityPacket(const std::string & p_strAbilityName, ability::AbilityInfoPackage * p_info);
		void sendSummonUnitPacket(int p_iClientId, int p_iUnitId, int p_iPosX, int p_iPosY);
		void sendMovementPacket(int p_iUnitIndex, int p_iPosX, int p_iPosY);
		void sendManipulateTilePacket(const std::string & p_strAbilityName, int p_iUnitIndex, int p_iPosX, int p_iPosY);

	private:
		ClientNetwork* m_network;

		char m_network_data[MAX_PACKET_SIZE];

		int m_iClientId = -1;

		// Unit GO list so clients can have a reference to the same unit GO without having the same mem address
		std::map<int, kitten::K_GameObject*> m_unitGOList;
		int m_iUnitIndex = 0;

		static bool sm_networkValid;
	};
}