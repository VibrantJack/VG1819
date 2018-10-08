#pragma once

#include "Font.h"
#include "../VertexEnvironment.h"
#include "../Texture.h"
#include "kitten\UIRenderable.h"

#include <map>
#include <string>
/*
	Callum MacKenzie
*/

namespace puppy
{
	/*
	TextBox - Renderable thing that shows text
	@TODO: Have a UI element abstract class for this to extend instead ? Wait for Austin UI
	*/
	class TextBox : public kitten::UIRenderable
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
		void removeOldText();
	public:
		TextBox(Font* p_fontToUse, std::string p_text, float p_boxWidth, float p_boxHeight);
		TextBox(Font* p_fontToUse, std::string p_text, float p_boxWidth, float p_boxHeight, Alignment p_alignment);
		~TextBox();

		void setColor(GLfloat p_redVal, GLfloat p_greenVal, GLfloat p_blueVal);
		void setText(const std::string& p_text);
		void setAlignment(Alignment p_alignment);

		const std::string& getText() const;

		virtual void render(const glm::mat4& p_ortho) override;
	};
}