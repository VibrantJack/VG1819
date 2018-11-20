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

		void testNewPacket(const std::string & p_strAbilityName, ability::AbilityInfoPackage * p_info);
		void sendAbilityPacket(const std::string & p_strAbilityName, ability::AbilityInfoPackage * p_info);

		void singleTargetAbility(const std::string &p_strAbilityName, int p_iSourceUnitIndex, int p_iTargetUnitIndex, int p_iDur, int p_iPow);
		void sendSingleTargetPacket(const std::string &p_strAbilityName, int p_iSourceUnitIndex, int p_iTargetUnitIndex, int p_iDur, int p_iPow);

		void singleTileAbility(const std::string &p_strAbilityName, int p_iPosX, int p_iPosY);
		void sendSingleTilePacket(const std::string &p_strAbilityName, int p_iPosX, int p_iPosY);

		void sourceTargetDamageAbility(const std::string &p_strAbilityName, int p_iSourceUnitIndex, int p_iTargetUnitIndex, int p_iPower);
		void sendSourceTargetDamagePacket(const std::string &p_strAbilityName, int p_iSourceUnitIndex, int p_iTargetUnitIndex, int p_iPower);

		void manipulateTile(const std::string & p_strAbilityName, int p_iUnitIndex, int p_iPosX, int p_iPosY);
		void sendManipulateTilePacket(const std::string & p_strAbilityName, int p_iUnitIndex, int p_iPosX, int p_iPosY);

		void summonUnit(int p_iClientId, int p_iUnitId, int p_iPosX, int p_iPosY);
		void sendSummonUnitPacket(int p_iClientId, int p_iUnitId, int p_iPosX, int p_iPosY);

		void moveUnit(int p_iUnitIndex, int p_iPosX, int p_iPosY);
		void sendMovementPacket(int p_iUnitIndex, int p_iPosX, int p_iPosY);		

		void sendPacket(Packet* p_packet);				

		int getUnitGameObjectIndex(kitten::K_GameObject* p_unit);
		kitten::K_GameObject* getUnitGameObject(int p_iIndex);
		void removeUnitGameObject(int p_iUnitIndex);
		int getClientId() { return m_iClientId; }

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