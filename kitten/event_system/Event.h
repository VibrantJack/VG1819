#pragma once

#include "kitten/K_GameObject.h"

#include <map>
#include <string>

namespace kitten
{
	class Event
	{
	public:
		enum EventType {Test_Event, MAX_VAL = Test_Event};

		Event(EventType p_event);
		~Event();

		void putInt(const std::string& m_key, int m_value);
		void putFloat(const std::string& m_key, float m_value);
		void putString(const std::string& m_key, const std::string& m_value);
		void putGameObj(const std::string& m_key, K_GameObject* m_value);
		void putConstGameObj(const std::string& m_key, const K_GameObject* m_value);


		int getInt(const std::string& m_key);
		float getFloat(const std::string& m_key);
		std::string getString(const std::string& m_key);
		K_GameObject* getGameObj(const std::string& m_key);
		const K_GameObject* getConstGameObj(const std::string& m_key);

	private:
		//------------------------------------------------------------------------------
		// Private members.
		//------------------------------------------------------------------------------
		EventType m_type; //ID

		//Maps allocated when needed
		std::map<std::string, int> *m_intMap;
		std::map<std::string, float> *m_floatMap;
		std::map<std::string, std::string> *m_stringMap;
		std::map<std::string, const K_GameObject*> *m_constGameObjMap;
		std::map<std::string, K_GameObject*> *m_gameObjMap;
		
	};
}