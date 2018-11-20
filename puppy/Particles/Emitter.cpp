#include "Emitter.h"

#include "AccelerationAff.h"
#include "ColorChangeAff.h"
#include "ColorSpawnAff.h"
#include "FadeChangeAff.h"
#include "FadeSpawnAff.h"
#include "LifetimeSpawnAff.h"
#include "OffsetSpawnAff.h"
#include "PathAff.h"
#include "SizeChangeAff.h"
#include "SizeSpawnAff.h"
#include "SpawnAffector.h"
#include "VelocitySpawnAff.h"
#include "RotationChangeAff.h"
#include "DirectionSpawnAff.h"

#include "puppy\ShaderManager.h"
#include "puppy\ShaderProgram.h"
#include "pugixml\pugixml.hpp"
#include "expressions\PostfixEval.h"

#include <iostream>

namespace puppy
{
	Emitter::Emitter(const char* p_pathToXML, const glm::vec3& p_offset) : m_vao(nullptr), m_tex(nullptr), m_isBurst(false), m_lastSpawn(0)
	{
		m_xmlPath = p_pathToXML;
		m_parser = new parser::Parser();

		refreshXML();
	}

	Emitter::~Emitter()
	{
		//delete affectors
		for (auto it = m_affectors.begin(); it != m_affectors.end(); ++it)
		{
			delete *it;
		}

		//delete spawn properties
		for (auto it = m_spawnProperties.begin(); it != m_spawnProperties.end(); ++it)
		{
			delete *it;
		}

		//delete particles
		for (auto it = m_activeParticles.begin(); it != m_activeParticles.end(); ++it)
		{
			delete *it;
		}
		for (auto it = m_freeParticles.begin(); it != m_freeParticles.end(); ++it)
		{
			delete *it;
		}

		//delete parser
		delete m_parser;

		//delete vao and texture
		delete m_vao;
		delete m_tex;
	}

	void Emitter::refreshXML()
	{
		int maxParticles = 0;
		
		//load xml
		pugi::xml_document xmlDoc;
		pugi::xml_parse_result loadResult = xmlDoc.load_file(m_xmlPath.c_str());
		if (!loadResult)
		{
			//invalid xml / file not opened correct
			return;
		}

		//delete old affectors
		for (Affector* a : m_affectors)
		{
			delete a;
		}
		m_affectors.clear();
		for (SpawnAffector* sa : m_spawnProperties)
		{
			delete sa;
		}
		m_spawnProperties.clear();

		pugi::xml_node emitNode = xmlDoc.child("Emitter");
		pugi::xml_node affectors = emitNode.child("Affectors");
		pugi::xml_node spawnProperties = emitNode.child("SpawnProperties");
		pugi::xml_node miscNode = emitNode.child("Misc");

		bool hasShape = false;

		//Read spawn properties
		for (pugi::xml_node child : spawnProperties.children())
		{
			std::string propName = child.name();
			//switch propName to find what property this is
			if (propName == "velocity")
			{
				bool isRand = child.attribute("random").as_bool();
				if (!isRand)
				{
					float vel = child.attribute("velocity").as_float();
					m_spawnProperties.push_back(new VelocitySpawnAff(vel));
				}
				else
				{
					float min = child.attribute("min").as_float();
					float max = child.attribute("max").as_float();
					m_spawnProperties.push_back(new VelocitySpawnAff(min, max));
				}
			}
			else if (propName == "lifetime")
			{
				bool isRand = child.attribute("random").as_bool();
				if (!isRand)
				{
					float killlength = child.attribute("length").as_float();
					m_spawnProperties.push_back(new LifetimeSpawnAff(killlength));
				}
				else
				{
					float min = child.attribute("min").as_float();
					float max = child.attribute("max").as_float();
					m_spawnProperties.push_back(new LifetimeSpawnAff(min, max));
				}
			}
			else if (propName == "color")
			{
				bool isRand = child.attribute("random").as_bool();
				if (!isRand)
				{
					float r = child.attribute("r").as_float();
					float g = child.attribute("g").as_float();
					float b = child.attribute("b").as_float();

					m_spawnProperties.push_back(new ColorSpawnAff(glm::vec3(r,g,b)));
				}
				else
				{
					float minR = child.attribute("minR").as_float();
					float minG = child.attribute("minG").as_float();
					float minB = child.attribute("minB").as_float();

					float maxR = child.attribute("maxR").as_float();
					float maxG = child.attribute("maxG").as_float();
					float maxB = child.attribute("maxB").as_float();

					m_spawnProperties.push_back(new ColorSpawnAff(glm::vec3(minR, minG, minB), glm::vec3(maxR, maxG, maxB)));
				}
			}
			else if (propName == "fade")
			{
				bool isRand = child.attribute("random").as_bool();
				if (!isRand)
				{
					float fade = child.attribute("fade").as_float();
					m_spawnProperties.push_back(new FadeSpawnAff(fade));
				}
				else
				{
					float min = child.attribute("min").as_float();
					float max = child.attribute("max").as_float();
					m_spawnProperties.push_back(new FadeSpawnAff(min, max));
				}
			}
			else if (propName == "size")
			{
				bool isRand = child.attribute("random").as_bool();
				if (!isRand)
				{
					float x = child.attribute("x").as_float();
					float y = child.attribute("y").as_float();
					m_spawnProperties.push_back(new SizeSpawnAff(glm::vec2(x, y)));
				}
				else
				{
					float minX = child.attribute("minX").as_float();
					float minY = child.attribute("minY").as_float();

					float maxX = child.attribute("maxX").as_float();
					float maxY = child.attribute("maxY").as_float();

					m_spawnProperties.push_back(new SizeSpawnAff(glm::vec2(minX, minY), glm::vec2(maxX, maxY)));
				}
			}
			else if (propName == "offset")
			{
				hasShape = true;

				OffsetType shape;

				bool isRand = false;
				float radius = 0;
				glm::vec3 topLeft, bottomRight;

				std::string type = child.attribute("type").as_string();
				if (type == "point")
				{
					shape = point;
				}
				else if (type == "disc")
				{
					shape = disc;

					radius = child.attribute("radius").as_float();
				}
				else if (type == "box")
				{
					shape = box;
				}
				else if (type == "sphere")
				{
					shape = sphere;

					radius = child.attribute("radius").as_float();
				}

				OffsetSpawnAff* osa = new OffsetSpawnAff(glm::vec3(0,0,0), shape);
				osa->setBoxBounds(topLeft, bottomRight);
				osa->setRadius(radius);

				m_spawnProperties.push_back(osa);
			}
			else if (propName == "direction")
			{
				bool useOff = child.attribute("useOffset").as_bool();
				m_spawnProperties.push_back(new DirectionSpawnAff(useOff));
			}
			else if (propName == "burst")
			{
				m_isBurst = child.attribute("isBurst").as_bool();
				if (m_isBurst)
				{
					m_canRepeat = child.attribute("repeat").as_bool();
					m_hasBursted = false;
				}
				
			}
			else if (propName == "maxParticles")
			{
				maxParticles = child.attribute("numParticles").as_int();
			}
		}

		//set emitter shape to default (point) if not defined in xml
		if (!hasShape)
		{
			OffsetSpawnAff* osa = new OffsetSpawnAff(glm::vec3(0,0,0), point);
			m_spawnProperties.push_back(osa);
		}

		//Load affectors
		for (pugi::xml_node child : affectors.children())
		{
			std::string affName = child.name();
			//switch affName to find proper type
			//setup specific to that type

			if (affName == "path")
			{
				//get type
				bool isPreset = child.attribute("isPreset").as_bool();
				if (isPreset)
				{
					std::string type = child.attribute("type").as_string();
					float scalar = child.attribute("scalar").as_float();
					if (type == "direction")
					{
						m_affectors.push_back(new PathAff(PathAff::direction, scalar));
					}
				}
				else
				{
					//get formulas for x,y,z
					std::string xPath = child.attribute("xPath").as_string();
					std::string yPath = child.attribute("yPath").as_string();
					std::string zPath = child.attribute("zPath").as_string();

					//Convert to postfix expressions
					std::vector<postfix::PostfixItem*> xStack = m_parser->parse(xPath);
					std::vector<postfix::PostfixItem*> yStack = m_parser->parse(yPath);
					std::vector<postfix::PostfixItem*> zStack = m_parser->parse(zPath);

					//create class to evaluate expressions 
					postfix::PostfixEval* xEval = new postfix::PostfixEval(xStack);
					postfix::PostfixEval* yEval = new postfix::PostfixEval(yStack);
					postfix::PostfixEval* zEval = new postfix::PostfixEval(zStack);

					m_affectors.push_back(new PathAff(xEval, yEval, zEval));
				}
			}
			else if (affName == "colorChange")
			{
				std::string mode = child.attribute("mode").as_string();
				if (mode == "over_life")
				{
					float rMin = child.attribute("startR").as_float();
					float gMin = child.attribute("startG").as_float();
					float bMin = child.attribute("startB").as_float();

					float rMax = child.attribute("endR").as_float();
					float gMax = child.attribute("endG").as_float();
					float bMax = child.attribute("endB").as_float();

					m_affectors.push_back(new ColorChangeAff(true, glm::vec3(rMin, gMin, bMin), glm::vec3(rMax, gMax, bMax)));
				}
				else if (mode == "random")
				{
					float rMin = child.attribute("minR").as_float();
					float gMin = child.attribute("minG").as_float();
					float bMin = child.attribute("minB").as_float();

					float rMax = child.attribute("maxR").as_float();
					float gMax = child.attribute("maxG").as_float();
					float bMax = child.attribute("maxB").as_float();

					m_affectors.push_back(new ColorChangeAff(false,glm::vec3(rMin, gMin, bMin), glm::vec3(rMax, gMax, bMax)));
				}
				else
				{
					float rChange = child.attribute("r").as_float();
					float gChange = child.attribute("g").as_float();
					float bChange = child.attribute("b").as_float();

					m_affectors.push_back(new ColorChangeAff(glm::vec3(rChange, gChange, bChange)));
				}
			}
			else if (affName == "fadeChange")
			{
				std::string mode = child.attribute("mode").as_string();
				if (mode == "over_life")
				{
					float min = child.attribute("start").as_float();
					float max = child.attribute("end").as_float();

					m_affectors.push_back(new FadeChangeAff(true,min, max));
				}
				else if (mode == "random")
				{
					float min = child.attribute("min").as_float();
					float max = child.attribute("max").as_float();

					m_affectors.push_back(new FadeChangeAff(false,min, max));
				}
				else
				{
					float change = child.attribute("change").as_float();
					m_affectors.push_back(new FadeChangeAff(change));
				}
			}
			else if (affName == "sizeChange")
			{
				std::string mode = child.attribute("mode").as_string();
				if (mode == "over_life")
				{
					float minX = child.attribute("startX").as_float();
					float minY = child.attribute("startY").as_float();

					float maxX = child.attribute("endX").as_float();
					float maxY = child.attribute("endY").as_float();

					m_affectors.push_back(new SizeChangeAff(true,glm::vec2(minX, minY), glm::vec2(maxX, maxY)));
				}
				else if (mode == "random")
				{
					float minX = child.attribute("minX").as_float();
					float minY = child.attribute("minY").as_float();

					float maxX = child.attribute("maxX").as_float();
					float maxY = child.attribute("maxY").as_float();

					m_affectors.push_back(new SizeChangeAff(false,glm::vec2(minX, minY), glm::vec2(maxX, maxY)));
				}
				else
				{
					float x = child.attribute("x").as_float();
					float y = child.attribute("y").as_float();

					m_affectors.push_back(new SizeChangeAff(glm::vec2(x, y)));
				}
			}
			else if (affName == "acceleration")
			{
				std::string mode = child.attribute("mode").as_string();
				if (mode == "over_life")
				{
					float min = child.attribute("min").as_float();
					float max = child.attribute("max").as_float();

					m_affectors.push_back(new AccelerationAff(true, min, max));
				}
				else if (mode == "random")
				{
					float min = child.attribute("min").as_float();
					float max = child.attribute("max").as_float();

					m_affectors.push_back(new AccelerationAff(false, min, max));
				}
				else
				{
					float accel = child.attribute("change").as_float();
					m_affectors.push_back(new AccelerationAff(accel));
				}
			}
			else if (affName == "rotationChange")
			{
				std::string mode = child.attribute("mode").as_string();
				if (mode == "over_life")
				{
					float min = child.attribute("min").as_float();
					float max = child.attribute("max").as_float();

					m_affectors.push_back(new RotationChangeAff(true, min, max));
				}
				else if (mode == "random")
				{
					float min = child.attribute("min").as_float();
					float max = child.attribute("max").as_float();

					m_affectors.push_back(new RotationChangeAff(false, min, max));
				}
				else
				{
					float accel = child.attribute("change").as_float();
					m_affectors.push_back(new RotationChangeAff(accel));
				}
			}
		}

		if (m_vao != nullptr)
		{
			delete(m_vao);
		}
		
		ParticleVertex* data = (ParticleVertex*) (malloc(sizeof(ParticleVertex)*maxParticles*6));
		ParticleVertex* dataStart = data;
		assert(data != NULL);
		//set uvs for each particle (always the same)
		for (int i = 0; i < maxParticles; ++i)
		{
			//bottom left
			data[0].u = 0;
			data[0].v = 0;
			data[0].x = 0;
			data[0].y = 0;
			data[0].z = 0;
			data[0].r = 0;
			data[0].g = 0;
			data[0].b = 0;
			data[0].a = 0;

			//bottom right
			data[1].u = 1;
			data[1].v = 0;
			data[1].x = 0;
			data[1].y = 0;
			data[1].z = 0;
			data[1].r = 0;
			data[1].g = 0;
			data[1].b = 0;
			data[1].a = 0;

			//top left
			data[2].u = 0;
			data[2].v = 1;
			data[2].x = 0;
			data[2].y = 0;
			data[2].z = 0;
			data[2].r = 0;
			data[2].g = 0;
			data[2].b = 0;
			data[2].a = 0;

			//top left
			data[3].u = 0;
			data[3].v = 1;
			data[3].x = 0;
			data[3].y = 0;
			data[3].z = 0;
			data[3].r = 0;
			data[3].g = 0;
			data[3].b = 0;
			data[3].a = 0;

			//bottom right
			data[4].u = 1;
			data[4].v = 0;
			data[4].x = 0;
			data[4].y = 0;
			data[4].z = 0;
			data[4].r = 0;
			data[4].g = 0;
			data[4].b = 0;
			data[4].a = 0;

			//top right
			data[5].u = 1;
			data[5].v = 1;
			data[5].x = 0;
			data[5].y = 0;
			data[5].z = 0;
			data[5].r = 0;
			data[5].g = 0;
			data[5].b = 0;
			data[5].a = 0;

			data += 6;
		}
		m_vao = new VertexEnvironment(dataStart, ShaderManager::getShaderProgram(ShaderType::particles), maxParticles*6);
		free(dataStart);
		data = nullptr;

		//Set texture
		if (m_tex != nullptr)
		{
			delete(m_tex);
		}
		m_tex = new Texture(miscNode.attribute("path").as_string());
		m_spawnRate = miscNode.attribute("spawnRate").as_float();
	
		m_maxLife = miscNode.attribute("lifetime").as_float();
		if (m_maxLife > 0)
		{
			m_lived = 0;
		}
		
		//Set particle lists
		//Put all active particles to free
		m_freeParticles.insert(m_freeParticles.begin(),m_activeParticles.begin(), m_activeParticles.end());
		m_activeParticles.clear();
		
		if (maxParticles > m_freeParticles.size())
		{
			//Create more particles
			for (int i = m_freeParticles.size(); i < maxParticles; ++i)
			{
				Particle* newParticle = new Particle();

				m_freeParticles.push_back(newParticle);
			}
		}
		else
		{
			//Delete particles
			if (maxParticles < m_freeParticles.size())
			{
				for (int i = m_freeParticles.size(); i > maxParticles; --i)
				{
					delete (*m_freeParticles.begin());
					m_freeParticles.erase(m_freeParticles.begin());
				}
			}
		}
	}

	void Emitter::update(float p_delta, bool p_canSpawn)
	{
		//If we are able to spawn, and this emitter has not lived its life
		if (p_canSpawn && ((m_maxLife < 0 || m_lived < m_maxLife) || !m_hasBursted))
		{
			m_lived += p_delta;

			m_lastSpawn += p_delta;

			if (m_lastSpawn > m_spawnRate) //Should we spawn particles? 
			{
				//We are spawning particles, how many do we spawn?
				unsigned int numPartToSpawn = 0;

				if (!m_isBurst) 
				{
					//Continuous mode

					numPartToSpawn = m_lastSpawn / m_spawnRate;
					m_lastSpawn -= numPartToSpawn * m_spawnRate;

					//spawn particle from free list
					//not enough in free list?
					if (numPartToSpawn > m_freeParticles.size())
					{
						unsigned int neededParticles = numPartToSpawn - m_freeParticles.size();
						//we want the minimum of (neededParticles, particlesWeCanTakeFromActive)
						unsigned int particlesCanAcquire = (neededParticles < m_activeParticles.size()) ? neededParticles : m_activeParticles.size();

						for (unsigned int i = 0; i < particlesCanAcquire; ++i)
						{
							m_freeParticles.push_front(m_activeParticles.back());
							//reset attributes
							m_activeParticles.back()->m_lived = 0;
							m_activeParticles.back()->m_pathProgress = 0;
							m_activeParticles.back()->m_centerPoint.x = 0;
							m_activeParticles.back()->m_centerPoint.y = 0;
							m_activeParticles.back()->m_centerPoint.z = 0;
							m_activeParticles.back()->m_colorTint.r = 0;
							m_activeParticles.back()->m_colorTint.g = 0;
							m_activeParticles.back()->m_colorTint.b = 0;
							m_activeParticles.back()->m_colorTint.a = 0;
							m_activeParticles.back()->m_velocity = 0;
							m_activeParticles.back()->m_scale.x = 1;
							m_activeParticles.back()->m_scale.y = 1;
							m_activeParticles.pop_back();
						}

						numPartToSpawn = numPartToSpawn - (neededParticles - particlesCanAcquire);
					}
				}
				else
				{
					//Burst mode
					if (!m_canRepeat)
					{
						m_hasBursted = true;
					}
					m_lastSpawn = 0;


					//put all active particles into free list
					for (auto it = m_activeParticles.begin(); it != m_activeParticles.end(); ++it)
					{
						//reset attributes
						(*it)->m_lived = 0;
						(*it)->m_pathProgress = 0;
						(*it)->m_centerPoint.x = 0;
						(*it)->m_centerPoint.y = 0;
						(*it)->m_centerPoint.z = 0;
						(*it)->m_colorTint.r = 0;
						(*it)->m_colorTint.g = 0;
						(*it)->m_colorTint.b = 0;
						(*it)->m_colorTint.a = 0;
						(*it)->m_velocity = 0;
						(*it)->m_scale.x = 1;
						(*it)->m_scale.y = 1;

						m_freeParticles.push_back(*it);
					}
					m_activeParticles.clear();

					numPartToSpawn = m_freeParticles.size();
					
				}

				std::list<Particle*> newSpawns;

				//Spawn particles from free list
				for (int i = 0; i < numPartToSpawn; ++i)
				{
					//Get next particle
					Particle* toSpawn = m_freeParticles.back();
					m_freeParticles.pop_back();

					//Push to newspawn list
					newSpawns.push_back(toSpawn);
					//Push to active list
					m_activeParticles.push_front(toSpawn);

					//set randoms
					for (int n = 0; n < AffRandKeys::AFF_RAND_SIZE_MAX; ++n)
					{
						toSpawn->m_randFactor[n] = (float)rand() / (float)RAND_MAX;
					}
				}

				//Set other spawn properties
				for (SpawnAffector* spa : m_spawnProperties)
				{
					spa->apply(newSpawns);
				}
			}
		}

		//Do we apply affectors to any active particles?
		if (m_activeParticles.size() > 0)
		{
			//Apply affectors on active particles
			for (Affector* aff : m_affectors)
			{
				aff->apply(m_activeParticles, p_delta);
			}

			//Kill particles that need to die
			for (auto it = m_activeParticles.begin(); it != m_activeParticles.end();)
			{
				(*it)->m_lived += p_delta;

				if ((*it)->m_lifetime > 0 && ((*it)->m_lifetime < (*it)->m_lived)) //This particle needs to be killed
				{
					//reset attributes
					(*it)->m_lived = 0;
					(*it)->m_pathProgress = 0;
					(*it)->m_centerPoint.x = 0;
					(*it)->m_centerPoint.y = 0;
					(*it)->m_centerPoint.z = 0;
					(*it)->m_colorTint.r = 0;
					(*it)->m_colorTint.g = 0;
					(*it)->m_colorTint.b = 0;
					(*it)->m_colorTint.a = 0;
					(*it)->m_velocity = 0;
					(*it)->m_scale.x = 1;
					(*it)->m_scale.y = 1;
					
					
					//move to free list
					m_freeParticles.push_back(*it);
					//remove from active list
					it = m_activeParticles.erase(it);
				}
				else
				{
					//this particle may live, continue
					++it;
				}
			}	
		}
	}

	void Emitter::render(const glm::mat4& p_viewInverse, const glm::mat4& p_viewProj, const glm::vec3& p_position, const glm::vec3& p_scale)
	{
		if (m_activeParticles.size() > 0) //Do we have particles to render?
		{	
			//map data
			ParticleVertex* data = (ParticleVertex*)(m_vao->map(GL_WRITE_ONLY));
			ParticleVertex d0 = data[0];
			
			//construct vertices for each active particle
			for (Particle* p : m_activeParticles)
			{
				//Construct a world matrix to multiply each vertex by
				glm::mat4 worldMat = 
					glm::translate(glm::vec3(p->m_centerPoint.x + p_position.x, p->m_centerPoint.y + p_position.y, p->m_centerPoint.z + p_position.z)) *
					p_viewInverse *
					glm::rotate(p->m_rotation, glm::vec3(0, 0, 1)) *
					glm::scale(glm::vec3(p->m_scale.x * p_scale.x, p->m_scale.y * p_scale.y, 1));

				//Bottom left
				glm::vec4 pos = glm::vec4(-0.5, -0.5, 0, 1);
				pos = worldMat * pos;
				data[0].x = pos.x;
				data[0].y = pos.y;
				data[0].z = pos.z;
				data[0].r = p->m_colorTint.r;
				data[0].g = p->m_colorTint.g;
				data[0].b = p->m_colorTint.b;
				data[0].a = p->m_colorTint.a;

				//Bottom right
				pos = glm::vec4(0.5,-0.5, 0, 1);
				pos = worldMat * pos;
				data[1].x = pos.x;
				data[1].y = pos.y;
				data[1].z = pos.z;
				data[1].r = p->m_colorTint.r;
				data[1].g = p->m_colorTint.g;
				data[1].b = p->m_colorTint.b;
				data[1].a = p->m_colorTint.a;

				//Bottom right
				data[4].x = pos.x;
				data[4].y = pos.y;
				data[4].z = pos.z;
				data[4].r = p->m_colorTint.r;
				data[4].g = p->m_colorTint.g;
				data[4].b = p->m_colorTint.b;
				data[4].a = p->m_colorTint.a;

				//Top left
				pos = glm::vec4(-0.5,0.5, 0, 1);
				pos = worldMat * pos;
				data[2].x = pos.x;
				data[2].y = pos.y;
				data[2].z = pos.z;
				data[2].r = p->m_colorTint.r;
				data[2].g = p->m_colorTint.g;
				data[2].b = p->m_colorTint.b;
				data[2].a = p->m_colorTint.a;


				//Top left
				data[3].x = pos.x;
				data[3].y = pos.y;
				data[3].z = pos.z;
				data[3].r = p->m_colorTint.r;
				data[3].g = p->m_colorTint.g;
				data[3].b = p->m_colorTint.b;
				data[3].a = p->m_colorTint.a;

				//Top  right
				pos = glm::vec4(0.5,0.5, 0, 1);
				pos = worldMat * pos;
				data[5].x = pos.x;
				data[5].y = pos.y;
				data[5].z = pos.z;
				data[5].r = p->m_colorTint.r;
				data[5].g = p->m_colorTint.g;
				data[5].b = p->m_colorTint.b;
				data[5].a = p->m_colorTint.a;

				data += 6;
			}

			//unmap data
			GLenum result = m_vao->unmap();

			//render particles

			//apply shader
			puppy::ShaderManager::applyShader(ShaderType::particles);

			//set uniforms
			glUniformMatrix4fv(puppy::ShaderManager::getShaderProgram(ShaderType::particles)->getUniformPlace(WORLD_VIEW_PROJ_UNIFORM_NAME),
				1, GL_FALSE, glm::value_ptr(p_viewProj));

			//bind texture
			m_tex->apply();

			//Draw!
			m_vao->drawArrays(GL_TRIANGLES, 0, m_activeParticles.size() * 6);
		}
	}

	void Emitter::setSpawnRate(float p_spawnRate)
	{
		m_spawnRate = p_spawnRate;
	}
}