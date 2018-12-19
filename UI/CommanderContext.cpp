#include "CommanderContext.h"
#include "kitten\K_ComponentManager.h"
#include "kitten\K_GameObjectManager.h"
#include "kitten\K_GameObject.h"
#include "puppy\Text\Font.h"
#include "puppy\Text\FontTable.h"
#include "puppy\Text\TextBox.h"
#include "puppy\Text\TextTable.h"
#include "kibble\kibble.hpp"
#include "kitten\InputManager.h"


namespace userinterface
{
	CommanderContext::CommanderContext(): ContextMenu()
	{
	}

	CommanderContext::~CommanderContext()
	{
	}

	void CommanderContext::start()
	{
		input::InputManager* inMan = input::InputManager::getInstance();
		int posX, posY;
		posY = inMan->getWindowHeight();
		int posY2 = posY - 50;
		getTransform().place2D(50, posY2);
		getTransform().scale2D(100, 100);
		setPivotType(piv_BotLeft);
		setTexBehaviour(tbh_Repeat);
		setEnabled(true);

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

		if (sm_vao == nullptr)
		{
			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);
		}

		++sm_instances;

		addToDynamicRender();
	}
}
