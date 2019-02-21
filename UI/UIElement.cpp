#include "UIElement.h"
#include "puppy\Renderer.h"
#include "puppy\StaticRenderables.h"
#include "UI/UIFrame.h"


namespace userinterface
{ 
	std::map<UIElement::pivotType, puppy::VertexEnvironment*> UIElement::sm_vao;
	std::map<UIElement::pivotType, int> UIElement::sm_instances;

	UIElement::UIElement(const char* p_pathToTex) : m_hasSetVerts(false), m_vao(nullptr)
	{
		m_texPath = p_pathToTex;
		m_tex = new puppy::Texture(p_pathToTex);
		m_mat = new puppy::Material(puppy::ShaderType::gAlpha_alphaTest);
		if (p_pathToTex != nullptr)
		{
			m_mat->setTexture(p_pathToTex);
		}
		else 
		{
			m_mat->setTexture(DEFAULT_TEXTURE);
			m_texPath = DEFAULT_TEXTURE;
		}
		m_texBehaviour = tbh_Stretch;
		m_pivotType = piv_BotLeft;

		m_isEnabled = true;

	}

	UIElement::UIElement(nlohmann::json & p_json) : kitten::K_UIRenderable(p_json), m_hasSetVerts(false), m_vao(nullptr)
	{
		m_texPath = LOOKUPSTRDEF("texture", DEFAULT_TEXTURE);
		m_tex = new puppy::Texture(m_texPath);
		m_mat = new puppy::Material(puppy::ShaderType::alphaTest);
		m_mat->setTexture(m_tex);
		m_texBehaviour = tbh_Stretch;

		std::string temp = LOOKUPSTRDEF("pivot","");
		if (temp == "left")
			m_pivotType = userinterface::UIElement::piv_Left;
		else if (temp == "right")
			m_pivotType = userinterface::UIElement::piv_Right;
		else if (temp == "center")
			m_pivotType = userinterface::UIElement::piv_Center;
		else if (temp == "top")
			m_pivotType = userinterface::UIElement::piv_Top;
		else if (temp == "bottom")
			m_pivotType = userinterface::UIElement::piv_Bot;
		else if (temp == "botleft")
			m_pivotType = userinterface::UIElement::piv_BotLeft;
		else if (temp == "botright")
			m_pivotType = userinterface::UIElement::piv_BotRight;
		else if (temp == "topleft")
			m_pivotType = userinterface::UIElement::piv_TopLeft;
		else if (temp == "topright")
			m_pivotType = userinterface::UIElement::piv_TopRight;
		else
			m_pivotType = userinterface::UIElement::piv_BotLeft;

		temp = LOOKUPSTRDEF("behaviour", "");
		if (temp == "repeat")
			m_texBehaviour = userinterface::UIElement::tbh_Repeat;
		else if (temp == "mirror_repeat")
			m_texBehaviour = userinterface::UIElement::tbh_RepeatMirrored;
		else 
			m_texBehaviour = userinterface::UIElement::tbh_Stretch;

	}

	UIElement::UIElement(const char* p_pathToTex, pivotType p_pivot, textureBehaviour p_texBehaviour) : m_hasSetVerts(false), m_vao(nullptr)
	{
		m_texPath = p_pathToTex;
		m_tex = new puppy::Texture(p_pathToTex);
		m_mat = new puppy::Material(puppy::ShaderType::gAlpha_alphaTest);
		if (p_pathToTex != nullptr)
		{
			m_mat->setTexture(p_pathToTex);
		}
		else 
		{
			m_mat->setTexture(DEFAULT_TEXTURE);
			m_texPath = DEFAULT_TEXTURE;
		}

		m_texBehaviour = p_texBehaviour;
		m_pivotType = p_pivot;

		m_isEnabled = true;

	}

	UIElement::~UIElement()
	{
		delete m_mat;
		
		if(m_hasSetVerts)
		{
			if (--sm_instances[m_pivotType] == 0)
			{
				delete sm_vao[m_pivotType];
				sm_vao[m_pivotType] = nullptr;
			}
		}
		//m_vao is part of the map above, don't need to delete

		if (m_isEnabled)
		{
			if (m_hasTransparency)
			{
				removeFromDynamicTransparentUIRender();
			}
			else
			{
				removeFromDynamicUIRender();
			}
		}
	}

	void UIElement::start()
	{
		defineVerts();
		if (m_isEnabled) {
			if (m_hasTransparency) {
				this->addToDynamicTransparentUIRender();
			}
			else 
			{
				this->addToDynamicUIRender();
			}
		}
	}
	
	void UIElement::defineVerts()
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
				const glm::vec2 scale = getTransform().getScale2D();
				u = scale.x / 100.0f;
				if (u < 1)
				{
					u = 1.0f;
				}
				v = scale.y / 100.0f;
				if (v < 1)
				{
					v = 1.0f;
				}
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

		
		if (m_texBehaviour == tbh_Repeat || m_texBehaviour == tbh_RepeatMirrored)
		{
			m_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);
		}
		else 
		{
			auto found = sm_vao.find(m_pivotType);
			if (found != sm_vao.end())
			{
				if ((*found).second == nullptr)
				{
					m_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);
					sm_vao.insert(std::make_pair(m_pivotType, m_vao));
				}
				else
				{
					m_vao = (*found).second;
				}
			}
			else
			{
				m_vao = new puppy::VertexEnvironment(verts, puppy::ShaderManager::getShaderProgram(puppy::ShaderType::alphaTest), 6);
				sm_vao.insert(std::make_pair(m_pivotType, m_vao));
			}
		}

		sm_instances[m_pivotType]++;
		m_hasSetVerts = true;
	}

	void UIElement::setTransparency(bool p_hasTransparency)
	{
		m_hasTransparency = p_hasTransparency;
		if (m_hasStarted && m_isEnabled) {
			if (m_hasTransparency)
			{
				removeFromDynamicUIRender();
				addToDynamicTransparentUIRender();
			}
			else 
			{
				removeFromDynamicTransparentUIRender();
				addToDynamicUIRender();
			}
		}
	}

	void UIElement::onDisabled()
	{
		if (m_hasTransparency)
		{
			removeFromDynamicTransparentUIRender();
		}
		else
		{
			removeFromDynamicUIRender();
		}
	}

	void UIElement::onEnabled()
	{
		if (m_hasTransparency)
		{
			addToDynamicTransparentUIRender();
		} 
		else
		{
			addToDynamicUIRender();
		}
	}

	void UIElement::uiRender(kitten::Camera* p_cam)
	{
		m_mat->apply();

		glm::mat4 wvp = p_cam->getOrtho() * getTransform().getWorldTransform();
		m_mat->setUniform(WORLD_VIEW_PROJ_UNIFORM_NAME, wvp);
		m_mat->setUniform(GENERAL_ALPHA_UNIFORM_NAME, m_gAlpha);

		m_vao->drawArrays(GL_TRIANGLES);

	}

	void UIElement::setTexture(const char* p_pathToTex)
	{
		//delete m_tex;
		//m_tex = new puppy::Texture(p_pathToTex);

		m_mat->setTexture(p_pathToTex);
		m_texPath = p_pathToTex;
	}

	void UIElement::setPivotType(const pivotType p_piv)
	{
		m_pivotType = p_piv;
	}

	void UIElement::setTexBehaviour(const textureBehaviour p_tb)
	{
		m_texBehaviour = p_tb;
	}
}
