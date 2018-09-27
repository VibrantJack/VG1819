#pragma once

#include <tuple>
#include "Ray.h"
#include "ClickableBox.h"

namespace MousePicker
{
	bool rayHits(const kitten::Ray& p_ray, const kitten::ClickableBox* p_clickable, double* p_hitOutput);	
	kitten::ClickableBox* getClosestHit(const kitten::Ray& p_ray);
}