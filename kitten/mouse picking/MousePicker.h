#pragma once

#include <tuple>
#include "Ray.h"
#include "Clickable.h"

namespace MousePicker
{
	bool rayHits(const kitten::Ray& p_ray, const kitten::Clickable* p_clickable, double* p_hitOutput);	
	kitten::Clickable* getClosestHit(const kitten::Ray& p_ray);
}