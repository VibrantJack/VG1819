#pragma once

#include <assert.h>
#include <string>
#include <unordered_map>

namespace puppy
{
	class Font;
	class P_Instance;

	class FontTable
	{
		friend class P_Instance;
	private:
		FontTable();
		~FontTable();
		static FontTable* sm_instance;
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new FontTable(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete sm_instance; };

		std::unordered_map<std::string, Font*> m_createdFonts;
	public:
		static FontTable* getInstance() { return sm_instance; };

		Font* getFont(const char* p_pathToFont);
	};
}