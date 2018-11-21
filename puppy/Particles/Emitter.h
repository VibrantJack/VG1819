#pragma once


#include "Particle.h"
#include "Affector.h"
#include "SpawnAffector.h"

#include "puppy\P_Common.h"
#include "puppy\VertexEnvironment.h"
#include "puppy\Texture.h"
#include "expressions\parser.h"

#include <list>
#include <string>

namespace puppy
{
	class Emitter
	{
	private:
		bool m_isBurst;
		bool m_canRepeat;
		bool m_hasBursted;

		std::list<Particle*> m_activeParticles;
		std::list<Particle*> m_freeParticles;

		std::list<Affector*> m_affectors;
		std::list<SpawnAffector*> m_spawnProperties;

		std::string m_xmlPath;

		float m_spawnRate;
		float m_lastSpawn;
		float m_maxLife;
		float m_lived;

		parser::Parser* m_parser;

		VertexEnvironment* m_vao;
		Texture* m_tex;
	public:
		virtual ~Emitter();
		Emitter(const char* p_pathToXML, const glm::vec3& p_offset);

		void update(float p_delta, bool p_canSpawn);
		void render(const glm::mat4& p_viewInverse, const glm::mat4& p_viewProj, const glm::vec3& p_position, const glm::vec3& p_scale);

		void resetBurst() { m_hasBursted = false; };

		void setSpawnRate(float p_spawnRate);
		void refreshXML();
	};
}