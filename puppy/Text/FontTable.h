#pragma once

#include <assert.h>
#include <string>
#include <unordered_map>

namespace puppy
{
	class Font;

	class FontTable
	{
	private:
		FontTable();
		~FontTable();
		static FontTable* sm_instance;

		std::unordered_map<std::string, Font*> m_createdFonts;
	public:
		static void createInstance() { assert(sm_instance == nullptr); sm_instance = new FontTable(); };
		static void destroyInstance() { assert(sm_instance != nullptr); delete sm_instance; };
		static FontTable* getInstance() { return sm_instance; };

		Font* getFont(const char* p_pathToFont);
	};
}