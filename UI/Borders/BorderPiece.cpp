#include "BorderPiece.h"

namespace userinterface
{
	BorderPiece::BorderPiece(BorderPlacement p_bp) : UIElement(DEFAULT_TEXTURE)
	{
		m_borderPlacement = p_bp;
	}


	BorderPiece::~BorderPiece()
	{
	}

	void BorderPiece::defineVerts()
	{
		//quad coords (ortho)
		float xmin, ymin, xmax, ymax, z, u, v;
		z = 0.0;

		//change UV coords to meet type expectation
		switch (m_texBehaviour)
		{

			//TO-DO. 
			/*
			There must be a good way to set the UV's on creation
			of this object so that you can have the texture repeat
			if the object is particularily large to avoid stretching
			the texture out. Maybe just have a param that tells
			the frame how many times to tile the texture in both dimensions
			*/

		case tbh_Stretch: {
			u = 1.0;
			v = 1.0;
			m_tex->setWrapping(GL_CLAMP_TO_EDGE);
			break;
		};

		case tbh_Repeat: {
			u = 1.0;
			v = 1.0;
			m_tex->setWrapping(GL_REPEAT);
			break;
		};

		case tbh_RepeatMirrored: {
			u = 1.0f;
			v = 1.0f;
			m_tex->setWrapping(GL_MIRRORED_REPEAT);
			break;
		};
		}


		//pivot type depends on the position of the border 
		//piece relative to the thing it's surrounding.
		glm::vec3 parentPos = getGameObject().getTransform().getTranslation();
		glm::vec2 parentScale = getGameObject().getTransform().getScale2D();
		switch (m_borderPlacement)
		{
		case bp_Left:
		{
			m_pivotType = piv_Right;
			getGameObject().getTransform().place2D(parentPos.x, parentPos.y + parentScale.y / 2);
			break;
		}
		case bp_Top:
		{
			m_pivotType = piv_Bot;
			break;
		}
		case bp_Right:
		{
			m_pivotType = piv_Left;
			break;
		}
		case bp_Bot:
		{
			m_pivotType = piv_Top;
			break;
		}
		case bp_TopLeft:
		{
			m_pivotType = piv_BotRight;
			break;
		}
		case bp_TopRight:
		{
			m_pivotType = piv_BotLeft;
			break;
		}
		case bp_BotRight:
		{
			m_pivotType = piv_TopLeft;
			break;
		}
		case bp_BotLeft:
		{
			m_pivotType = piv_TopRight;
			break;
		}
		}

		switch (m_pivotType)
		{
		case piv_Left: {
			xmin = 0.0f;
			ymin = -0.5f;
			xmax = 1.0f;
			ymax = 0.5f;
			break;
		}
		case piv_Right: {
			xmin = -1.0f;
			ymin = -0.5f;
			xmax = 0.0f;
			ymax = 0.5f;
			break;
		}
		case piv_Bot: {
			xmin = -0.5f;
			ymin = 0.0f;
			xmax = 0.5f;
			ymax = 1.0f;
			break;
		}
		case piv_Top: {
			xmin = -0.5f;
			ymin = -1.0f;
			xmax = 0.5f;
			ymax = 0.0f;
			break;
		}
		case piv_BotLeft: {
			xmin = 0.0f;
			ymin = 0.0f;
			xmax = 1.0f;
			ymax = 1.0f;
			break;
		}
		case piv_BotRight: {
			xmin = -1.0f;
			ymin = 0.0f;
			xmax = 0.0f;
			ymax = 1.0f;
			break;
		}
		case piv_TopLeft: {
			xmin = 0.0f;
			ymin = -1.0f;
			xmax = 1.0f;
			ymax = 0.0f;
			break;
		}
		case piv_TopRight: {
			xmin = -1.0f;
			ymin = -1.0f;
			xmax = 0.0f;
			ymax = 0.0f;
			break;
		}
		case piv_Center: {
			xmin = -0.5;
			ymin = -0.5;
			xmax = 0.5;
			ymax = 0.5;
			break;
		}
		}

		puppy::TexturedVertex verts[] =
		{
			//a nice lil quad that takes the pivot into account
			{ xmin, ymin, z, 0.0,  0.0 },
			{ xmax, ymin, z, u,    0.0 },
			{ xmax, ymax, z, u,    v },
			{ xmax, ymax, z, u,    v },
			{ xmin,	ymax, z, 0.0f, v },
			{ xmin, ymin, z, 0.0f, 0.0f },
		};

		if (sm_vao[m_pivotType] == nullptr)
		{
			sm_vao[m_pivotType] = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);
		}

		sm_instances[m_pivotType]++;

		this->addToDynamicUIRender();
	}
}
