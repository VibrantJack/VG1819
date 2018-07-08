#include "Font.h"
#include <iostream>

namespace puppy
{
	/*
	Font Class
	*/

	bool Font::setFont(const char* p_pathToFnt)
	{
		//XML Loading
		pugi::xml_parse_result loadResult = m_fontXML.load_file(p_pathToFnt);

		if (!loadResult)
		{
			std::cerr << "Error Loading Font: " << p_pathToFnt << " : " << loadResult.description() << std::endl;

			m_fontLoaded = false;
			return false; //Load failed
		}
		//else

		pugi::xml_node fontNode = m_fontXML.child("font");
		pugi::xml_node commonNode = fontNode.child("common");
		m_charsNode = fontNode.child("chars");
		
		m_xTexSize = commonNode.attribute("scaleW").as_int();
		m_yTexSize = commonNode.attribute("scaleH").as_int();
		m_lineHeight = commonNode.attribute("lineHeight").as_int();

		//Load the texture pages into the vector
		//Iterate through pages
		for (pugi::xml_node child : fontNode.child("pages").children("page"))
		{
			std::string texName = child.attribute("file").as_string();
			texName = "fonts/" + texName;
			//push texture into vector
			m_textures.push_back(new Texture(texName.c_str()));
		}


		m_fontLoaded = true;
		return true;
	}

	bool Font::isInFont(int p_charId)
	{
		pugi::xml_node n;
		return findCharNode(n, p_charId);
	}

	struct id_match_predicate
	{
		int toCompare;

		bool operator()(pugi::xml_node p_node)
		{
			return p_node.attribute("id").as_int() == toCompare;
		}
	};

	bool Font::findCharNode(pugi::xml_node& p_nodeToReplace, int p_charId)
	{
		if (!m_fontLoaded)
		{
			return false;
		}
		//else

		//Check if we just searched for this node
		if (m_lastCharQueried.attribute("id").as_int() == p_charId)
		{
			//We have already found this node, no need to search again.
			p_nodeToReplace = m_lastCharQueried;
			return true;
		}
		else
		{
			//We must search for the node needed
			id_match_predicate query = id_match_predicate();
			query.toCompare = p_charId;

			p_nodeToReplace = m_charsNode.find_child(query);
			//If char not found in table
			if (p_nodeToReplace.attribute("id").as_int() == 0)
			{
				return false;
			}
			//else

			//update last node
			m_lastCharQueried = p_nodeToReplace;
			return true;
		}
	}

	bool Font::getPxForChar(int p_charId, int& p_widthToSet, int& p_heightToSet)
	{
		pugi::xml_node thisCharNode;
		if (!findCharNode(thisCharNode, p_charId))
		{
			return false;
		}
		//else

		p_widthToSet = thisCharNode.attribute("width").as_int();
		p_heightToSet = thisCharNode.attribute("height").as_int();

		return true;
	}

	//@TODO: Rigorously test below method
	bool Font::getUVsForChar(int p_charId, float& p_uStartToSet, float& p_uEndToSet, float& p_vStartToSet, float& p_vEndToSet)
	{
		pugi::xml_node thisCharNode;
		if (!findCharNode(thisCharNode, p_charId))
		{
			return false;
		}
		//else

		p_uStartToSet = (float)thisCharNode.attribute("x").as_int() / m_xTexSize;
		p_vStartToSet = (m_yTexSize - (thisCharNode.attribute("y").as_int() + thisCharNode.attribute("height").as_int())) / m_yTexSize;
			

		//below might be wrong
		p_uEndToSet = (float)(thisCharNode.attribute("x").as_int() + thisCharNode.attribute("width").as_int()) / m_xTexSize;
		p_vEndToSet = (m_yTexSize - thisCharNode.attribute("y").as_int()) / m_yTexSize;

		return true;
	}

	bool Font::getOffsetsForChar(int p_charId, int& p_xToSet, int& p_yToSet) 
	{
		pugi::xml_node thisCharNode;
		if (!findCharNode(thisCharNode, p_charId))
		{
			return false;
		}
		//else

		p_xToSet = thisCharNode.attribute("xoffset").as_int();
		p_yToSet = thisCharNode.attribute("yoffset").as_int();

		return true;
	}

	bool Font::getXAdvanceForChar(int p_charId, int& p_xToSet) 
	{
		pugi::xml_node thisCharNode;
		if (!findCharNode(thisCharNode, p_charId))
		{
			return false;
		}
		//else

		p_xToSet = thisCharNode.attribute("xadvance").as_int();
		
		return true;
	}

	Texture* Font::getTexForChar(int p_charId) 
	{
		//Search for the node that contains the information we need
		pugi::xml_node thisCharNode;
		if (!findCharNode(thisCharNode, p_charId)) //could not find node
		{
			return nullptr;
		}
		//else

		return m_textures[thisCharNode.attribute("page").as_int()];
	}

	int Font::getLineHeight()
	{
		return m_lineHeight;
	}
}