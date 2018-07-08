#pragma once

#include <vector>
#include "../P_Common.h"
//-----------------------------------------------------------------------------
// File:			CollisionManager.h
// Original Author:	Callum MacKenzie
//
// Abandonded, but included so I don't forget I already made
// The basics for collisions when I inevitably use all the
// puppy code for something else
//
// Beta only supports one point (used with camera pos)
//
//-----------------------------------------------------------------------------

namespace puppy
{
	//Uses point vs AABB
	class Collidable
	{
	public:
		virtual bool collides(const glm::vec3* p_toCheck) const;

		virtual glm::vec3 getMax() const = 0;
		virtual glm::vec3 getMin() const = 0;
	};

	class CollisionManager
	{
	private:
		static std::vector<Collidable*> sm_toCheck;
	public:
		static void addCollidable(Collidable* p_toAdd);
		static void removeCollidable(Collidable* p_toRemove);
		static bool checkCollision(const glm::vec3* p_pos);

		static void removeAll();
	};
}