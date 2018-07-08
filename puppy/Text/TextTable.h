#pragma once
#include <map>
#include <string>

namespace puppy
{
	/*
	TextTable - String manager, returns localized string
	based on an id.

	Known issues:
	- text.dat format does not allow for unlocalized strings without a special character. e.g.
	it is impossible to have a string, 'str_hello', localized for the second language in the file,
	but not the first, without using an escape or flag character.
	*/

	class TextTable
	{	
	private:
		//map with key of type pair<language, id> and value of localized string
		static std::map<std::pair<std::string, std::string>, std::string> m_activeStrings;
		static std::string m_activeLanguage;

	public:
		static bool setSourceStrings(const char* p_pathToData); //default to text.dat?
		static void setLanguage(const char* p_lang);
		static const std::string getString(const char* p_key);
	};
}