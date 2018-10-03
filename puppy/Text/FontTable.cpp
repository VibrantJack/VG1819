#include "FontTable.h"
#include "Font.h"

namespace puppy
{
	FontTable* FontTable::sm_instance = nullptr;

	FontTable::FontTable()
	{

	}

	FontTable::~FontTable()
	{
		auto end = m_createdFonts.end();
		for (auto it = m_createdFonts.begin(); it != end; ++it)
		{
			delete it->second;
		}
	}

	Font* FontTable::getFont(const char* p_pathToFont)
	{
		auto found = m_createdFonts.find(std::string(p_pathToFont));
		if (found != m_createdFonts.end())
		{
			return found->second;
		}

		//We need to create this font
		Font* created = new Font(p_pathToFont);
		m_createdFonts.insert(std::make_pair(std::string(p_pathToFont), created));

		return created;
	}
}