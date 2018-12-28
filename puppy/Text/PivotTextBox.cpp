#include "PivotTextBox.h"

//austin's textbox with pivots

namespace puppy
{
	PivotTextBox::PivotTextBox(Font* p_fontToUse, const std::string& p_text, float p_boxWidth, float p_boxHeight, userinterface::UIElement::pivotType p_piv, bool p_is3D = false) :
		TextBox(p_fontToUse, p_text, p_boxWidth, p_boxHeight)
	{
		m_piv = p_piv;
	}


	PivotTextBox::~PivotTextBox()
	{
	}

	void PivotTextBox::constructQuad(int p_charId, int p_xPos, int p_yPos, TexturedVertex p_toSet[])
	{
		int width, height, xAdvance, xOff, yOff;
		GLfloat uStart, uEnd, vStart, vEnd;

		m_font->getPxForChar(p_charId, width, height);
		m_font->getXAdvanceForChar(p_charId, xAdvance);
		m_font->getUVsForChar(p_charId, uStart, uEnd, vStart, vEnd);
		m_font->getOffsetsForChar(p_charId, xOff, yOff);
		int halfHeight = height / 2;
		int halfWidth = width / 2;

		switch(m_piv)
		{ 
			case userinterface::UIElement::piv_BotLeft:
			{
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
				break;
			}
			case userinterface::UIElement::piv_Left:
			{
				//Bottom left
				p_toSet[0] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff - halfHeight,	0,	uStart,vStart };
				//Top left
				p_toSet[1] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff + halfHeight,	0,	uStart, vEnd };
				//Bottom right
				p_toSet[2] = { (GLfloat)p_xPos + xOff + width,	(GLfloat)p_yPos - yOff - halfHeight,	0,	uEnd, vStart };
				//Bottom right
				p_toSet[3] = { (GLfloat)p_xPos + xOff + width,	(GLfloat)p_yPos - yOff - halfHeight,	0,	uEnd, vStart };
				//Top right
				p_toSet[4] = { (GLfloat)p_xPos + xOff + width,	(GLfloat)p_yPos - yOff + halfHeight,	0,	uEnd, vEnd };
				//Top left
				p_toSet[5] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff + halfHeight,	0,	uStart, vEnd };
				break;	
			}
			case userinterface::UIElement::piv_TopLeft:
			{
				//Bottom left	
				p_toSet[0] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff,					0,	uStart,vStart };
				//Top left
				p_toSet[1] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff + height,		0,	uStart, vEnd };
				//Bottom right
				p_toSet[2] = { (GLfloat)p_xPos + xOff + width,	(GLfloat)p_yPos - yOff,					0,	uEnd, vStart };
				//Bottom right
				p_toSet[3] = { (GLfloat)p_xPos + xOff + width,	(GLfloat)p_yPos - yOff,					0,	uEnd, vStart };
				//Top right
				p_toSet[4] = { (GLfloat)p_xPos + xOff + width,	(GLfloat)p_yPos - yOff + height,		0,	uEnd, vEnd };
				//Top left
				p_toSet[5] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff + height,		0,	uStart, vEnd };
				break;
			}
			case userinterface::UIElement::piv_Top:
			{
				//Bottom left
				p_toSet[0] = { (GLfloat)p_xPos + xOff - halfWidth,	(GLfloat)p_yPos - yOff - height,	0,	uStart,vStart };
				//Top left
				p_toSet[1] = { (GLfloat)p_xPos + xOff - halfWidth,	(GLfloat)p_yPos - yOff,				0,	uStart, vEnd };
				//Bottom right
				p_toSet[2] = { (GLfloat)p_xPos + xOff + halfWidth,	(GLfloat)p_yPos - yOff - height,	0,	uEnd, vStart };
				//Bottom right
				p_toSet[3] = { (GLfloat)p_xPos + xOff + halfWidth,	(GLfloat)p_yPos - yOff - height,	0,	uEnd, vStart };
				//Top right
				p_toSet[4] = { (GLfloat)p_xPos + xOff + halfWidth,	(GLfloat)p_yPos - yOff,				0,	uEnd, vEnd };
				//Top left
				p_toSet[5] = { (GLfloat)p_xPos + xOff - halfWidth,	(GLfloat)p_yPos - yOff,				0,	uStart, vEnd };
				break;
			}
			case userinterface::UIElement::piv_TopRight:
			{
				//Bottom left	
				p_toSet[0] = { (GLfloat)p_xPos + xOff - width,	(GLfloat)p_yPos - yOff - height,	0,	uStart,vStart };
				//Top left
				p_toSet[1] = { (GLfloat)p_xPos + xOff - width,	(GLfloat)p_yPos - yOff,				0,	uStart, vEnd };
				//Bottom right
				p_toSet[2] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff - height,	0,	uEnd, vStart };
				//Bottom right
				p_toSet[3] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff - height,0,	uEnd, vStart };
				//Top right
				p_toSet[4] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff,				0,	uEnd, vEnd };
				//Top left
				p_toSet[5] = { (GLfloat)p_xPos + xOff - width,	(GLfloat)p_yPos - yOff,				0,	uStart, vEnd };
				break;
			}
			case userinterface::UIElement::piv_Right:
			{
				//Bottom left	
				p_toSet[0] = { (GLfloat)p_xPos + xOff - width,	(GLfloat)p_yPos - yOff - halfHeight,	0,	uStart,vStart };
				//Top left
				p_toSet[1] = { (GLfloat)p_xPos + xOff - width,	(GLfloat)p_yPos - yOff + halfHeight,	0,	uStart, vEnd };
				//Bottom right
				p_toSet[2] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff - halfHeight,	0,	uEnd, vStart };
				//Bottom right
				p_toSet[3] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff - halfHeight,	0,	uEnd, vStart };
				//Top right
				p_toSet[4] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff + halfHeight,	0,	uEnd, vEnd };
				//Top left
				p_toSet[5] = { (GLfloat)p_xPos + xOff - width,	(GLfloat)p_yPos - yOff + halfHeight,	0,	uStart, vEnd };
				break;
			}
			case userinterface::UIElement::piv_BotRight:
			{
				//Bottom left	
				p_toSet[0] = { (GLfloat)p_xPos + xOff - width,	(GLfloat)p_yPos - yOff,				0,	uStart,vStart };
				//Top left
				p_toSet[1] = { (GLfloat)p_xPos + xOff - width,	(GLfloat)p_yPos - yOff + height,	0,	uStart, vEnd };
				//Bottom right
				p_toSet[2] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff,				0,	uEnd, vStart };
				//Bottom right
				p_toSet[3] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff,				0,	uEnd, vStart };
				//Top right
				p_toSet[4] = { (GLfloat)p_xPos + xOff,			(GLfloat)p_yPos - yOff + height,	0,	uEnd, vEnd };
				//Top left
				p_toSet[5] = { (GLfloat)p_xPos + xOff - width,	(GLfloat)p_yPos - yOff + height,	0,	uStart, vEnd };
				break;
			}
			case userinterface::UIElement::piv_Bot:
			{
				//Bottom left	
				p_toSet[0] = { (GLfloat)p_xPos + xOff - halfWidth,	(GLfloat)p_yPos - yOff,				0,	uStart,vStart };
				//Top left
				p_toSet[1] = { (GLfloat)p_xPos + xOff - halfWidth,	(GLfloat)p_yPos - yOff + height,	0,	uStart, vEnd };
				//Bottom right
				p_toSet[2] = { (GLfloat)p_xPos + xOff + halfWidth,	(GLfloat)p_yPos - yOff,				0,	uEnd, vStart };
				//Bottom right
				p_toSet[3] = { (GLfloat)p_xPos + xOff + halfWidth,	(GLfloat)p_yPos - yOff,				0,	uEnd, vStart };
				//Top right
				p_toSet[4] = { (GLfloat)p_xPos + xOff + halfWidth,	(GLfloat)p_yPos - yOff + height,	0,	uEnd, vEnd };
				//Top left
				p_toSet[5] = { (GLfloat)p_xPos + xOff - halfWidth,	(GLfloat)p_yPos - yOff + height,	0,	uStart, vEnd };
				break;
			}

		}
	}
}