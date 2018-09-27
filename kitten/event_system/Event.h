#pragma once

#define OBJECT_CLICKED_OBJ_KEY "clicked"

#include "kitten/K_GameObject.h"

#include <unordered_map>
#include <string>

namespace kitten
{
	class Event
	{
	public:
		enum EventType { Object_Clicked, Test_Event, MAX_VAL = Test_Event};

		Event(EventType p_event);
		~Event();

		void putInt(const std::string& p_key, int p_value);
		void putFloat(const std::string& p_key, float p_value);
		void putString(const std::string& p_key, const std::string& p_value);
		void putGameObj(const std::string& p_key, K_GameObject* p_value);
		void putConstGameObj(const std::string& p_key, const K_GameObject* p_value);


		int getInt(const std::string& p_key);
		float getFloat(const std::string& p_key);
		std::string getString(const std::string& p_key);
		K_GameObject* getGameObj(const std::string& p_key);
		const K_GameObject* getConstGameObj(const std::string& p_key);

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
		
	};
}