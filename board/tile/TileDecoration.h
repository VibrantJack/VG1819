/*
@Rock 12.27
This class will be a component of decoration game object
It will take a range of scale, rotation, translation and generate a random number
This get a range of texture as well.
*/

#pragma once
#include "kitten/K_Common.h"

class TileDecoration : public kitten::K_Component
{
public:
	TileDecoration();
	~TileDecoration();

	void start() override;

	void setTextureList(std::vector<std::string> p_list);
	void setScaleRange(const glm::vec3 &  p_min, const glm::vec3 &  p_max);
	void setRotationRange(const glm::vec3 &  p_min, const glm::vec3 &  p_max);
	void setTransRange(const glm::vec3 &  p_min, const glm::vec3 &  p_max);
private:
	glm::vec3 m_minScale;
	glm::vec3 m_maxScale;
	glm::vec3 m_minRotation;
	glm::vec3 m_maxRotation;
	glm::vec3 m_minTranslation;
	glm::vec3 m_maxTranslation;
	std::vector<std::string> m_textureList;

	/*
	glm::vec3 m_scale;
	glm::vec3 m_rotation;
	glm::vec3 m_translation;
	std::string m_texture;
	*/

	const std::string& randomTexture();
	int randomInt(int p_a, int p_b);
	float randomFloat(float p_a, float p_b);
	const glm::vec3 & randomScale();
	const glm::vec3 & randomRotation();
	const glm::vec3 & randomTranslation();
};

