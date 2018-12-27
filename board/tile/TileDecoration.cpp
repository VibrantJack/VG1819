#include "TileDecoration.h"
#include "kitten/QuadRenderable.h"

TileDecoration::TileDecoration()
	:
	m_minScale(glm::vec3(1, 1, 1)),
	m_maxScale(glm::vec3(1, 1, 1)),
	m_minRotation(glm::vec3(45, 0, 0)),
	m_maxRotation(glm::vec3(45, 0, 0)),
	m_minTranslation(glm::vec3(0, 0, 0)),
	m_maxTranslation(glm::vec3(0, 0, 0))
{
}

TileDecoration::~TileDecoration()
{
}

void TileDecoration::start()
{
	//get renderable
	kitten::QuadRenderable* quad = m_attachedObject->getComponent<kitten::QuadRenderable>();
	assert(quad != nullptr);

	//set texture
	quad->setTexture(randomTexture().c_str());

	//set vector
	glm::vec3 scale = randomScale();
	glm::vec3 rot = randomRotation();
	glm::vec3 trans = randomTranslation();
	getTransform().scaleAbsolute(scale.x, scale.y, scale.z);
	getTransform().rotateAbsolute(rot);
	getTransform().place(trans.x, trans.y, trans.z);
}

void TileDecoration::setTextureList(std::vector<std::string> p_list)
{
	m_textureList = p_list;
}

void TileDecoration::setScaleRange(const glm::vec3 &  p_min, const glm::vec3 &  p_max)
{
	m_minScale = p_min;
	m_maxScale = p_max;
}

void TileDecoration::setRotationRange(const glm::vec3 &  p_min, const glm::vec3 &  p_max)
{
	m_minRotation = p_min;
	m_maxRotation = p_max;
}

void TileDecoration::setTransRange(const glm::vec3 &  p_min, const glm::vec3 &  p_max)
{
	m_minTranslation = p_min;
	m_maxTranslation = p_max;
}

const std::string & TileDecoration::randomTexture()
{
	assert(m_textureList.size() > 0);

	int index = rand() % m_textureList.size();

	return m_textureList[index];
}

int TileDecoration::randomInt(int p_a, int p_b)
{
	int delta = abs(p_a - p_b);
	int i = rand() % delta + (p_a < p_b ? p_a : p_b);
	return i;
}

float TileDecoration::randomFloat(float p_a, float p_b)
{
	float random = ((float)rand()) / (float)RAND_MAX;//random float between 0, and 1
	float delta = abs(p_a - p_b);
	float f = random * delta + (p_a < p_b ? p_a : p_b);
	return f;
}

const glm::vec3 & TileDecoration::randomScale()
{
	float x = randomFloat(m_minScale.x, m_maxScale.x);
	float y = randomFloat(m_minScale.y, m_maxScale.y);
	float z = randomFloat(m_minScale.z, m_maxScale.z);

	return glm::vec3(x, y, z);
}

const glm::vec3 & TileDecoration::randomRotation()
{
	int x = randomInt(m_minRotation.x, m_maxRotation.x);
	int y = randomInt(m_minRotation.y, m_maxRotation.y);
	int z = randomInt(m_minRotation.z, m_maxRotation.z);

	return glm::vec3(x, y, z);
}

const glm::vec3 & TileDecoration::randomTranslation()
{
	float x = randomFloat(m_minTranslation.x, m_maxTranslation.x);
	float y = randomFloat(m_minTranslation.y, m_maxTranslation.y);
	float z = randomFloat(m_minTranslation.z, m_maxTranslation.z);

	return glm::vec3(x, y, z);
}
