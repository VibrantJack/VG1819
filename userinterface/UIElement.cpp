#include "UIElement.h"
#include "puppy\Renderer.h"
#include "puppy\StaticRenderables.h"

namespace userinterface
{ 
	puppy::VertexEnvironment* UIElement::sm_vao = nullptr;
	int UIElement::sm_instances = 0;

	UIElement::UIElement(const char* p_pathToTex)
	{
		m_tex = new puppy::Texture(p_pathToTex);
		m_mat = new puppy::Material(puppy::ShaderType::basic);
		if (p_pathToTex != nullptr)
		{
			m_mat->setTexture(p_pathToTex);
		}
		else {
			m_mat->setTexture("textures/ui/blankFrame.tga");
		}
		m_texBehaviour = tbh_Stretch;
		m_pivotType = piv_BotLeft;

		m_isEnabled = true;

		start();
	}

	UIElement::UIElement(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBehaviour)
	{
		m_tex = new puppy::Texture(p_pathToTex);
		m_mat = new puppy::Material(puppy::ShaderType::basic);
		if (p_pathToTex != nullptr)
		{
			m_mat->setTexture(p_pathToTex);
		}
		else {
			m_mat->setTexture("textures/ui/blankFrame.tga");
		}

		m_isEnabled = true;

		start();
	}

	UIElement::~UIElement()
	{
		delete m_mat;
		if (--sm_instances == 0)
		{
			delete sm_vao;
		}

		if (!m_isEnabled)
		{
			removeFromDynamicRender();
		}
	}

	void UIElement::start()
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
			{ xmin, ymin, z, 0.0,  0.0	},
			{ xmax, ymin, z, u,    0.0	},
			{ xmax, ymax, z, u,    v	},
			{ xmax, ymax, z, u,    v	},
			{ xmin,	ymax, z, 0.0f, v	},
			{ xmin, ymin, z, 0.0f, 0.0f },
		};

		if (sm_vao == nullptr)
		{
			sm_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::basic), 6);
		}

		++sm_instances;

		addToDynamicRender();

	}
	

		void UIElement::onDisabled()
		{
			removeFromDynamicRender();
		}

		void UIElement::onEnabled()
		{
			addToDynamicRender();
		}

		void UIElement::render(const glm::mat4& p_ortho)
		{
			m_mat->apply();

			glm::mat4 wvp = p_ortho * getTransform().getWorldTransform();
			m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);

			sm_vao->drawArrays(GL_TRIANGLES);
		}

		void UIElement::setTexture(const char* p_pathToTex)
		{
			//delete m_tex;
			//m_tex = new puppy::Texture(p_pathToTex);

			m_mat->setTexture(p_pathToTex);
		}
	}
