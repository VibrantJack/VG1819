#include "TextTable.h"

#include <fstream>
#include <sstream>
#include <iostream>
#include <vector>

namespace puppy
{
	/*
		TextTable class
	*/

	std::map<std::pair<std::string, std::string>, std::string> TextTable::m_activeStrings;
	std::string TextTable::m_activeLanguage = "";

	bool TextTable::setSourceStrings(const char* p_pathToData)
	{
		//Open the file
		std::ifstream sourceData;
		sourceData.open(p_pathToData);

		//Ensure file opened
		if (!sourceData.is_open())
		{
			std::cerr << "Unable to open file: " << p_pathToData << std::endl;
			return false;
		}
		//else

		std::string next;
		std::string nextLine;

		std::getline(sourceData, nextLine); //get the ID line
		std::istringstream iss(nextLine); //create a stream from the line
		iss >> next; //get the first word
		//ensure the first word is ID
		if (next != "ID")
		{
			std::cerr << "'" << p_pathToData << "' was not of proper format. ID row not at start of file." << std::endl;
			return false;
		}
		//else
		
		//populate a vector with the language keys
		std::vector<std::string> languages;
		while (iss >> next)
		{
			if (m_activeLanguage == "") //Set active language if not set
			{
				m_activeLanguage = next;
			}

			languages.push_back(std::string(next));
		}

		//process the strings, line by line
		while (std::getline(sourceData, nextLine))
		{
			std::stringstream lineStream(nextLine);
			std::string stringName;
			//read the string name, delimited by tab.
			std::getline(lineStream, stringName, '\t');

			//read the string values for the languages
			std::string stringValue;
			unsigned int langNumber = 0; //needed in case a language does not have a localized string yet
			while (std::getline(lineStream, stringValue, '\t'))
			{
				//insert value into map
				m_activeStrings.insert(std::make_pair(std::make_pair(languages.at(langNumber), stringName), stringValue));
				++langNumber;
			}

			//populate remaining languages that do not have values with the string name as the value
			for (langNumber; langNumber < languages.size(); ++langNumber)
			{
				m_activeStrings.insert(std::make_pair(std::make_pair(languages.at(langNumber), stringName), stringName));
			}

		}
		return true;
	}

	void TextTable::setLanguage(const char* p_lang)
	{
		m_activeLanguage = (std::string) p_lang;
	}

	const std::string TextTable::getString(const char* p_key) //If you got an error here it is likely that
	{															//the key was not in the table. Check the source
																//file and ensure the name is what you expect
		return m_activeStrings.at(std::make_pair(m_activeLanguage, p_key));
	}

}