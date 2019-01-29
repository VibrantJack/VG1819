#include "BorderPiece.h"
#include "kitten\InputManager.h"
#define BORDER_WIDTH  1
#define BORDER_HEIGHT  (1.0f / 5.0f)
#define CORNER_HEIGHT  (40.0f / 199.0f)
#define CORNER_WIDTH  (40.0f / 498.0f)

namespace userinterface
{
	BorderPiece::BorderPiece(BorderPlacement p_bp) : UIElement(DEFAULT_TEXTURE)
	{
		m_borderPlacement = p_bp;
		m_texBehaviour = tbh_Stretch;
		m_tex->setWrapping(GL_CLAMP_TO_EDGE);
	}


	BorderPiece::~BorderPiece()
	{
	}

	void BorderPiece::start()
	{
		//empty to stop defineVerts from getting called on start.
	}

	void BorderPiece::setFramedObject(kitten::K_GameObject* p_GO)
	{
		m_framedObject = p_GO;
		defineVerts();
	}

	void BorderPiece::defineVerts()
	{
		//get framed object data
		const glm::vec3 trans = m_framedObject->getTransform().getTranslation();
		const glm::vec2 scale = m_framedObject->getTransform().getScale2D();

		//quad coords (ortho)
		float xmin, ymin, xmax, ymax, z, uMin, vMin, uMax, vMax;
		int xIndex = 0;
	    int yIndex = 0;
		int winY = input::InputManager::getInstance()->getWindowHeight();
		z = 0.0;

		//pivot type depends on the position of the border 
		//piece relative to the thing it's surrounding.
		switch (m_borderPlacement)
		{
		case bp_Left:
		{
			m_pivotType = piv_Top;
			yIndex = 4;
			break;
		}
		case bp_Top:
		{
			m_pivotType = piv_Bot;
			yIndex = 3;
			break;
		}
		case bp_Right:
		{
			m_pivotType = piv_Top;
			yIndex = 2;
			break;
		}
		case bp_Bot:
		{
			m_pivotType = piv_Top;
			yIndex = 1;
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
			xIndex = 1;
			break;
		}
		case bp_BotRight:
		{
			m_pivotType = piv_TopLeft;
			xIndex = 2;
			break;
		}
		case bp_BotLeft:
		{
			m_pivotType = piv_TopRight;
			xIndex = 3;
			break;
		}
		}

		//pivot depends on placement
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

		//build UVs using atlas indeces
		if (yIndex == 0)
		{
			uMin = CORNER_WIDTH * xIndex;
			uMax = uMin + CORNER_WIDTH;
			vMin = 0;
			vMax = CORNER_HEIGHT;
		}
		else {
			uMin = 0;
			uMax = 1;
			vMin = BORDER_HEIGHT * yIndex;
			vMax = vMin + BORDER_HEIGHT;
		}

		puppy::TexturedVertex verts[] =
		{
			//a nice lil quad that takes the pivot into account
			{ xmin, ymin, z, uMin, vMin },
			{ xmax, ymin, z, uMax, vMin },
			{ xmax, ymax, z, uMax, vMax },
			{ xmax, ymax, z, uMax, vMax },
			{ xmin,	ymax, z, uMin, vMax },
			{ xmin, ymin, z, uMin, vMin },
		};

		if (BorderPiece::m_vao[m_pivotType] == nullptr)
		{
			BorderPiece::m_vao[m_pivotType] = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);
		}

		//move it back a bit
		getTransform().place(0.0f, 0.0f, -0.01);

		//depending on placement, scale and rotate the border to snap to the edge with the right scale
		switch (m_borderPlacement)
		{
		case bp_Left:
		{
			getTransform().rotate2D(-90);
			getTransform().place2D(trans.x, trans.y - scale.y / 2);
			getTransform().scale2D(scale.y, 20);
			break;
		}
		case bp_Top:
		{
			getTransform().place2D(trans.x + scale.x / 2, trans.y);
			getTransform().scale2D(scale.x, 20);
			break;
		}
		case bp_Right:
		{
			getTransform().rotate2D(90);
			getTransform().place2D(trans.x + scale.x, trans.y - scale.y / 2);
			getTransform().scale2D(scale.y, 20);
			break;
		}
		case bp_Bot:
		{
			getTransform().place2D(trans.x + scale.x / 2, trans.y - scale.y);
			getTransform().scale2D(scale.x, 20);
			break;
		}
		case bp_TopLeft:
		{
			getTransform().place2D(trans.x, trans.y);
			getTransform().scale2D(20, 20);
			break;
		}
		case bp_TopRight:
		{
			getTransform().place2D(trans.x + scale.x, trans.y);
			getTransform().scale2D(20, 20);
			break;
		}
		case bp_BotRight:
		{
			getGameObject().getTransform().place2D(trans.x + scale.x, trans.y - scale.y);
			getGameObject().getTransform().scale2D(20, 20);
			break;
		}
		case bp_BotLeft:
		{
			getGameObject().getTransform().place2D(trans.x, trans.y - scale.y);
			getGameObject().getTransform().scale2D(20, 20);
			break;
		}
		}

		this->addToDynamicUIRender();
	}

	void BorderPiece::uiRender(kitten::Camera* p_cam)
	{
		m_mat->apply();

		glm::mat4 wvp = p_cam->getOrtho() * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

		m_vao[m_pivotType]->drawArrays(GL_TRIANGLES);
	}
}

