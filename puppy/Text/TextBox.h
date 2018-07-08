#pragma once

#include "Font.h"
#include "../VertexEnvironment.h"
#include "../Texture.h"
#include "../Renderable.h"
#include "../Transformable.h"

#include <map>
#include <string>
/*
	Callum MacKenzie
*/

namespace puppy
{
	/*
	TextBox - Renderable thing that shows text
	*/
	class TextBox : public Transformable
	{
	public:
		enum Alignment { left, right, center };

	private:
		std::map<const Texture*, VertexEnvironment*> m_textMap;

		std::string m_text;
		float m_boxWidth, m_boxHeight;
		
		GLfloat m_color[4];
		Alignment m_alignment;
		Font* m_font;

		bool m_isDirty;


		void constructLeftAlignVertices();
		void constructRightOrCenterAlignVertices(bool p_isRight);

		void constructQuad(int p_charId, int p_xPos, int p_yPos, TexturedVertex p_toSet[]);
	public:
		
		TextBox(Font* p_fontToUse, std::string p_text, float p_boxWidth, float p_boxHeight);
		TextBox(Font* p_fontToUse, std::string p_text, float p_boxWidth, float p_boxHeight, Alignment p_alignment);
		~TextBox();

		void setColor(GLfloat p_redVal, GLfloat p_greenVal, GLfloat p_blueVal);
		void setText(const std::string& p_text);
		void setAlignment(Alignment p_alignment);

		const std::string& getText() const;

		virtual void render(const glm::mat4& p_wvp);
	};
}