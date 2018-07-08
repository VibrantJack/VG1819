#include "Effect.h"
namespace puppy
{
	Effect::Effect(const char* p_pathToXml)
	{
		m_state = paused;
		m_xmlPath = p_pathToXml;
		refreshXML();
	}

	Effect::~Effect()
	{
		//delete emitters
		for (Emitter* e : m_emitters)
		{
			delete e;
		}
	}

	void Effect::refreshXML()
	{
		pugi::xml_document xmlDoc;
		pugi::xml_parse_result loadResult = xmlDoc.load_file(m_xmlPath.c_str());
		if (!loadResult)
		{
			//invalid xml / file not opened correct
			return;
		}

		//delete old emitters
		for (Emitter* e : m_emitters)
		{
			delete e;
		}
		m_emitters.clear();

		//Load new emitters
		pugi::xml_node effectNode = xmlDoc.child("Effect");
		for (pugi::xml_node child : effectNode.children())
		{
			assert(strcmp(child.name(), "Emitter") == 0);
			const char* emitterPath = child.attribute("path").as_string();
			float xOff = child.attribute("x").as_float();
			float yOff = child.attribute("y").as_float();
			float zOff = child.attribute("z").as_float();
			m_emitters.push_back(new Emitter(emitterPath, glm::vec3(xOff,yOff,zOff)));
		}
	}

	void Effect::update(float p_delta)
	{
		if (m_state == playing)
		{
			for (auto it = m_emitters.begin(); it != m_emitters.end(); ++it)
			{
				//Update emitters
				(*it)->update(p_delta, true);
			}
		}
		else
		{
			if (m_state == paused)
			{
				for (auto it = m_emitters.begin(); it != m_emitters.end(); ++it)
				{
					//Update emitters
					(*it)->update(p_delta, false);
				}
			}
		}
	}

	void Effect::render(scene::Camera* p_cam)
	{
		if (m_state != stopped)
		{
			for (auto it = m_emitters.begin(); it != m_emitters.end(); ++it)
			{
				//Render emitters
				(*it)->render(p_cam);
			}
		}

	}

	void Effect::play()
	{
		if (m_state != stopped)
		{
			m_state = playing;
		}
	}

	void Effect::pause()
	{
		if (m_state != stopped)
		{
			m_state = paused;
		}
	}

	void Effect::stop()
	{
		m_state = stopped;
	}
}