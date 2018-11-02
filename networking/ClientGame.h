#pragma once
#include <winsock2.h>
#include <Windows.h>
#include "networking\ClientNetwork.h"
#include "networking\NetworkData.h"

#include "kitten\K_GameObject.h"
#include <map>

namespace networking
{
	class ClientGame
	{
	private:
		static ClientGame* sm_clientGameInstance;
		ClientGame();
		~ClientGame();
	public:

		static void createInstance();
		static void destroyInstance();
		static ClientGame* getInstance();
		static int getClientId() { return sm_iClientId; }

		bool setupNetwork(const std::string &p_strAddr = "127.0.0.1");
		void sendPacket(Packet* p_packet);

		void summonUnit(int p_iClientId, int p_iUnitId, int p_iPosX, int p_iPosY);
		void moveUnit(int p_iUnitIndex, int p_iPosX, int p_iPosY);
		int getUnitGameObjectIndex(kitten::K_GameObject* p_unit);

		void update();

	private:
		ClientNetwork* m_network;

		char m_network_data[MAX_PACKET_SIZE];

		static int sm_iClientId;

		// Unit GO list so clients can have a reference to the same unit GO without having the same mem address
		std::map<int, kitten::K_GameObject*> m_unitGOList;
		int m_iUnitIndex = 0;
	};
}