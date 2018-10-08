#pragma once

#include <vector>

#include "pugixml/pugixml.hpp"
#include "../Texture.h"
#include "FontTable.h"

namespace puppy
{
	/*
	Font - Loads data from fnt file and can
	return information for rendering strings
	*/
	class Font
	{
		friend class FontTable;
	private:
		pugi::xml_document m_fontXML;
		pugi::xml_node m_charsNode;
		pugi::xml_node m_lastCharQueried; //For effeciency. Likely that the last charId asked about will be used again directly afterwards
		std::vector<Texture*> m_textures; //Pages of textures needed for font

		bool m_fontLoaded;
		float m_xTexSize, m_yTexSize;
		int m_lineHeight;

		/*
		findCharNode() helper method to search for node containing the specified charId
		sets the passed in node with the possible found node. Returns search success.
		*/
		bool findCharNode(pugi::xml_node& p_nodeToReplace, int p_charId);
	protected:
		Font(const char* p_pathToFont);
		~Font();
	public:

		/*
		setFont() sets the active font and returns the XML
		load status (success or failure)
		*/
		bool setFont(const char* p_pathToFnt);

		/*
		isInFont() returns if the character is in the font
		*/
		bool isInFont(int p_charId);

		/*
		getPxForChar() sets two ints with the width and height
		(int pixels) of the character specified. Returns success status.
		*/
		bool getPxForChar(int p_charId, int& p_widthToSet, int& p_heightToSet);

		/*
		getExtentsForChar() sets four floats with the
		bounds of where a character appears in the font texture

		returns false if the character was not found in the font,
		returns true otherwise.
		*/
		bool getUVsForChar(int p_charId, float& p_uStartToSet, float& p_uEndToSet, float& p_vStartToSet, float& p_vEndToSet);

		/*
		getOffsetsForChar() sets two ints with the amount to offset
		a character, in px. Returns success status.
		*/
		bool getOffsetsForChar(int p_charId, int& p_xToSet, int& p_yToSet);

		/*
		getXAdvanceForChar() sets an int with how space to add after a character, in px.
		Returns success status.
		*/
		bool getXAdvanceForChar(int p_charId, int& p_xToSet);

		/*
		getTexForChar() returns a texture that contains the character
		*/
		Texture* getTexForChar(int p_charId);

		/*
		getLineHeight() returns the height a line should be for the font.
		*/
		int getLineHeight();
	};
}