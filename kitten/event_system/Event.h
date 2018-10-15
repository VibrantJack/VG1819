#pragma once

#define OBJECT_CLICKED_OBJ_KEY "clicked"
#define TILE_POS_X "pos_x"
#define TILE_POS_Y "pos_y"
#define TILE_OWNER_KEY "tile_owner_key"
#define MANIPULATE_TILE_KEY "manip_tile_key"

#include "kitten/K_GameObject.h"

#include <unordered_map>
#include <string>
#include <vector>

namespace kitten
{
	class Event
	{
	public:
		enum EventType 
		{ 
			Object_Clicked, 
			Highlight_Tile, 
			Unhighlight_Tile,
			Manipulate_Tile,
			Summon_Unit,
			Test_Event, 
			MAX_VAL = Test_Event
		};

		typedef std::vector<std::pair<int, int>> TileList;

		Event(EventType p_event);
		~Event();

		void putInt(const std::string& p_key, int p_value);
		void putFloat(const std::string& p_key, float p_value);
		void putString(const std::string& p_key, const std::string& p_value);
		void putGameObj(const std::string& p_key, K_GameObject* p_value);
		void putConstGameObj(const std::string& p_key, const K_GameObject* p_value);

		void putTileList(const TileList* p_tileList);


		int getInt(const std::string& p_key);
		float getFloat(const std::string& p_key);
		std::string getString(const std::string& p_key);
		K_GameObject* getGameObj(const std::string& p_key);
		const K_GameObject* getConstGameObj(const std::string& p_key);

		const TileList* getTileList();

	private:
		//------------------------------------------------------------------------------
		// Private members.
		//------------------------------------------------------------------------------
		EventType m_type; //ID

		//Maps allocated when needed
		std::unordered_map<std::string, int> *m_intMap;
		std::unordered_map<std::string, float> *m_floatMap;
		std::unordered_map<std::string, std::string> *m_stringMap;
		std::unordered_map<std::string, const K_GameObject*> *m_constGameObjMap;
		std::unordered_map<std::string, K_GameObject*> *m_gameObjMap;

		const TileList* m_tileList;
		
	};
}