#include "../P_Common.h"
#include "TextBox.h"
#include "../Texture.h"
#include "../ShaderManager.h"
#include "puppy\Renderer.h"

#include <iostream>
#include <vector>

namespace puppy
{
	TextBox::TextBox(Font* p_fontToUse, std::string p_text, float p_boxWidth, float p_boxHeight, Alignment p_alignment)
	{
		assert(p_fontToUse != nullptr);
		
		m_alignment = p_alignment;
		m_text = p_text;
		m_font = p_fontToUse;
		m_boxHeight = p_boxHeight;
		m_boxWidth = p_boxWidth;
		m_color[3] = 0; //alpha addition

		switch (p_alignment)
		{
		case left:
			constructLeftAlignVertices();
		case right:
			constructRightOrCenterAlignVertices(true);
		case center:
			constructRightOrCenterAlignVertices(false);
		}

		addToDynamicRender();
	}

	TextBox::TextBox(Font* p_fontToUse, std::string p_text, float p_boxWidth, float p_boxHeight)
	{
		m_alignment = left;
		m_text = p_text;
		m_font = p_fontToUse;
		m_boxHeight = p_boxHeight;
		m_boxWidth = p_boxWidth;
		m_color[3] = 0; //alpha addition

		constructLeftAlignVertices();
	}

	puppy::TextBox::~TextBox()
	{
		removeOldText();
		if (m_isEnabled)
		{
			removeFromDynamicRender();
		}
	}

	void TextBox::removeOldText()
	{
		auto end = m_textMap.end();
		for (auto it = m_textMap.begin(); it != end; ++it)
		{
			delete (*it).second;
		}
		m_textMap.clear();
	}

	void TextBox::constructQuad(int p_charId, int p_xPos, int p_yPos, TexturedVertex p_toSet[])
	{
		int width, height, xAdvance, xOff, yOff;
		GLfloat uStart, uEnd, vStart, vEnd;

		m_font->getPxForChar(p_charId, width, height);
		m_font->getXAdvanceForChar(p_charId, xAdvance);
		m_font->getUVsForChar(p_charId, uStart, uEnd, vStart, vEnd);
		m_font->getOffsetsForChar(p_charId, xOff, yOff);

		//Bottom left
		p_toSet[0] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff - height,	0,	uStart,vStart };
		//Top left
		p_toSet[1] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff,				0,	uStart, vEnd };
		//Bottom right
		p_toSet[2] = { (GLfloat)p_xPos + xOff + width,	(GLfloat)p_yPos - yOff - height,	0,	uEnd, vStart };
		//Bottom right
		p_toSet[3] = { (GLfloat)p_xPos + xOff + width,	(GLfloat)p_yPos - yOff - height,	0,	uEnd, vStart };
		//Top right
		p_toSet[4] = { (GLfloat)p_xPos + xOff + width,	(GLfloat)p_yPos - yOff,				0,	uEnd, vEnd };
		//Top left
		p_toSet[5] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff,				0,	uStart, vEnd };
	}

	void TextBox::constructLeftAlignVertices()
	{
		//Construct vertex data for string based on font.
		//Data is sorted by texture (font sheet) to minimize draw calls
		std::map<const Texture*, std::vector<TexturedVertex>> data;

		int xPos = 0, yPos = 0, xAdvance,
			wordLength = 0;
		std::string lastWord = "";

		//Iterate through the chars of the string
		for (unsigned int i = 0; i<m_text.length(); ++i)
		{
			//Characters not in the font get skipped.
			if (m_font->isInFont(m_text[i]))
			{
				//Check if this character is whitespace
				if (m_text[i] == ' ')
				{
					//construct the vertices to go into the buffer
					for (char c : lastWord)
					{
						TexturedVertex quad[6];
						constructQuad(c, xPos, yPos, quad);

						//insert into vector
						auto* vec = &data[m_font->getTexForChar(c)];
						vec->insert(vec->end(), quad, quad + 6);

						m_font->getXAdvanceForChar(c, xAdvance);
						//Increase xPos by char amount
						xPos += xAdvance;
					}

					//increase xPos by space amount
					m_font->getXAdvanceForChar(' ', xAdvance);
					xPos += xAdvance;
					lastWord = "";
					wordLength = 0;
				}
				else
				{
					lastWord += m_text[i];
					m_font->getXAdvanceForChar(m_text[i], xAdvance);
					wordLength += xAdvance;

					//Check if we need to go down a line because of width restrictions
					if (xPos + wordLength> m_boxWidth)
					{
						//go down a line
						yPos -= m_font->getLineHeight();
						xPos = 0;
						//check if we are still too long
						if (xPos + wordLength > m_boxWidth)
						{
							lastWord = "";
							break;
						}
					}

					//Check if we ran out of vertical space
					if (yPos*-1 > m_boxHeight)
					{
						lastWord = "";
						break;
					}		
				}
			}	
		}

		//construct last word if needed
		if (lastWord != "")
		{
			for (char c : lastWord)
			{
				TexturedVertex quad[6];
				constructQuad(c, xPos, yPos, quad);

				//insert into vector
				auto* vec = &data[m_font->getTexForChar(c)];
				vec->insert(vec->end(), quad, quad + 6);

				m_font->getXAdvanceForChar(c, xAdvance);
				//Increase xPos by char amount
				xPos += xAdvance;
			}
		}

		//construct buffers based on font sheets
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			m_textMap.insert(std::make_pair(it->first,
				new VertexEnvironment(it->second.data(), ShaderManager::getShaderProgram(ShaderType::colorTint_alphaTest), it->second.size())));
		}

	}

	void TextBox::constructRightOrCenterAlignVertices(bool p_isRight)
	{
		std::map<const Texture*, std::vector<TexturedVertex>> data;

		int xPos = m_boxWidth, yPos = 0, xAdvance,
			lineLength = 0, wordLength=0;
		std::string currentLine = "", lastWord = "";

		for (unsigned int i = 0; i < m_text.length(); ++i)
		{
			//ensure char is in font
			if (m_font->isInFont(m_text[i]))
			{
				m_font->getXAdvanceForChar(m_text[i], xAdvance);

				if (m_text[i] == ' ')
				{
					//add the last word to the line
					currentLine += lastWord + ' ';
					lineLength += wordLength + xAdvance;
					//reset word
					lastWord = "";
					wordLength = 0;
				}
				else
				{
					lastWord += m_text[i];
					wordLength += xAdvance;
				}

				//check if this line is too long with the word
				if (lineLength + wordLength > m_boxWidth)
				{
					//construct this line minus the word
					if (p_isRight)
					{
						xPos = m_boxWidth - lineLength;
					}
					else
					{
						xPos = (m_boxWidth - lineLength) / 2;
					}

					for (char c : currentLine)
					{
						m_font->getXAdvanceForChar(c, xAdvance);
						if (c != ' ')
						{
							TexturedVertex quad[6];
							constructQuad(c, xPos, yPos, quad);

							//insert into vector
							auto* vec = &data[m_font->getTexForChar(c)];
							vec->insert(vec->end(), quad, quad + 6);
						}
						//Increase xPos by char amount
						xPos += xAdvance;
					}
					
					//reset the line, increase yPos
					currentLine = "";
					lineLength = 0;
					yPos -= m_font->getLineHeight();

					if (yPos *-1 > m_boxHeight)
					{
						lastWord = "";
						break;
					}
				}


			}
		}

		currentLine += lastWord;
		lineLength += wordLength;
		//check if we need to construct the last line
		if (currentLine != "")
		{
			//construct this line minus the word
			if (p_isRight)
			{
				xPos = m_boxWidth - lineLength;
			}
			else
			{
				xPos = (m_boxWidth - lineLength) / 2;
			}

			for (char c : currentLine)
			{
				m_font->getXAdvanceForChar(c, xAdvance);
				if (c != ' ')
				{
					TexturedVertex quad[6];
					constructQuad(c, xPos, yPos, quad);

					//insert into vector
					auto* vec = &data[m_font->getTexForChar(c)];
					vec->insert(vec->end(), quad, quad + 6);
				}
				//Increase xPos by char amount
				xPos += xAdvance;
			}
		}

		//construct buffers based on font sheets
		for (auto it = data.begin(); it != data.end(); ++it)
		{
			m_textMap.insert(std::make_pair(it->first,
				new VertexEnvironment(it->second.data(), ShaderManager::getShaderProgram(ShaderType::colorTint_alphaTest), it->second.size())));
		}
	}

	void TextBox::setAlignment(Alignment p_alignment)
	{
		if (m_alignment != p_alignment)
		{
			m_alignment = p_alignment;
			m_isDirty = true;
			removeOldText();
		}
	}

	void TextBox::setText(const std::string& p_text)
	{
		if (m_text != p_text)
		{
			m_text = p_text;
			m_isDirty = true;
			removeOldText();
		}
	}

	const std::string& TextBox::getText() const
	{
		return m_text;
	}

	const int& TextBox::getBoxHeight() const
	{
		return m_boxHeight;
	}

	const int& TextBox::getBoxWidth() const
	{
		return m_boxWidth;
	}

	void TextBox::setColor(GLfloat p_redVal, GLfloat p_greenVal, GLfloat p_blueVal)
	{
		m_color[0] = p_redVal;
		m_color[1] = p_greenVal;
		m_color[2] = p_blueVal;
		
	}

	void TextBox::start()
	{
		addToDynamicRender();
	}

	void TextBox::onDisabled()
	{
		removeFromDynamicRender();
	}

	void TextBox::onEnabled()
	{
		addToDynamicRender();
	}

	void TextBox::render(const glm::mat4& p_ortho)
	{
		if (m_isDirty)
		{
			if (m_alignment == Alignment::left)
			{
				constructLeftAlignVertices();
			}
			else
			{
				if (m_alignment == Alignment::right)
				{
					constructRightOrCenterAlignVertices(true);
				}
				else
				{
					constructRightOrCenterAlignVertices(false);
				}
			}
			m_isDirty = false;
		}


		//apply shader & uniforms
		ShaderManager::applyShader(ShaderType::colorTint_alphaTest);
		glUniformMatrix4fv(ShaderManager::getShaderProgram(ShaderType::colorTint_alphaTest)->getUniformPlace(WORLD_VIEW_PROJ_UNIFORM_NAME), 1, GL_FALSE,
			glm::value_ptr(p_ortho * getTransform().getWorldTransform()));
		glUniform4fv(ShaderManager::getShaderProgram(ShaderType::colorTint_alphaTest)->getUniformPlace("colorTint"), 1, m_color);

		//render vertices
		for (auto it = m_textMap.begin(); it != m_textMap.end(); ++it)
		{
			//apply texture
			it->first->apply();
			//render
			it->second->drawArrays(GL_TRIANGLES);
		}
	}
}