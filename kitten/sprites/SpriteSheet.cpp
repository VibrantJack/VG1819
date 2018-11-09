#include "SpriteSheet.h"
#include "util\MathUtil.h"

namespace sprites
{
	SpriteSheet::SpriteSheet(const std::string& p_characterName, const std::string& p_pathToTex, int p_sheetWidth, int p_sheetHeight, int p_characterWidth, int p_characterHeight) : 
		m_characterName(p_characterName),m_sheetWidth(p_sheetWidth), m_sheetHeight(p_sheetHeight), m_characterWidth(p_characterWidth), m_characterHeight(p_characterHeight), 
		m_gridWidth(p_sheetWidth/p_characterWidth), m_gridHeight(p_sheetHeight/p_characterHeight), m_defaultAnimation(nullptr)
	{
		m_material = new puppy::Material(puppy::ShaderType::sprite);
		m_material->setTexture(p_pathToTex.c_str());

		m_material->getTexture()->setWrapping(GL_CLAMP_TO_EDGE);
		m_material->getTexture()->setMagFiltering(GL_NEAREST);
		m_material->getTexture()->setMinFiltering(GL_NEAREST);
	}

	SpriteSheet::~SpriteSheet()
	{
		delete m_material;

		auto end = m_animations.cend();
		for (auto it = m_animations.begin(); it != end; ++it)
		{
			auto currentAnimFrame = (*it).second;
			AnimationFrame* nextFrame = currentAnimFrame->next;

			bool lastFrame = currentAnimFrame->isLastFrame;
			while (!lastFrame)
			{
				nextFrame = currentAnimFrame->next;
				lastFrame = nextFrame->isLastFrame;

				delete currentAnimFrame;
				currentAnimFrame = nextFrame;
			}

			//delete last frame
			delete currentAnimFrame;
		}
	}

	const std::string& SpriteSheet::getCharacterName() const
	{
		return m_characterName;
	}

	void SpriteSheet::setAnimation(const std::string& p_name, const GridPosition& p_startPosition, const GridPosition& p_endPosition, float p_animationTime)
	{	
		assert(p_startPosition.first <= m_gridWidth && p_startPosition.first >= 0);
		assert(p_startPosition.second <= m_gridHeight && p_startPosition.second >= 0);

		assert(p_endPosition.first <= m_gridWidth && p_endPosition.first >= 0);
		assert(p_endPosition.second <= m_gridHeight && p_endPosition.second >= 0);

		int firstFrameToEndOfLine = m_gridWidth - p_startPosition.first;
		int lastFrameToBeginningOfLine = p_endPosition.first+1;
		int framesInBetween = ((p_endPosition.second - 1) - p_startPosition.second)  * m_gridWidth;

		int totalFrames = firstFrameToEndOfLine + framesInBetween + lastFrameToBeginningOfLine;
		
		float frameTime = p_animationTime / (float)totalFrames;

		//Chain together frames from startPosition to endPosition

		//Do the first frame
		glm::vec2 firstOffset((float)(p_startPosition.first*m_characterWidth) / m_sheetWidth, -((float)(p_startPosition.second*m_characterHeight) / m_sheetHeight));
		AnimationFrame* firstFrame = new AnimationFrame(firstOffset, frameTime, true);

		AnimationFrame* previousFrame = firstFrame;
		AnimationFrame* nextFrame = nullptr;

		GridPosition currentPos = p_startPosition;
		currentPos.first++;
		if (currentPos.first > m_gridWidth)
		{
			currentPos.first = 0;
			currentPos.second++;
		}

		bool ranOnce = false;

		GridPosition nextPosition = currentPos;

		while (currentPos != p_endPosition)
		{
			currentPos.first++;
			if (currentPos.first > m_gridWidth)
			{
				currentPos.first = 0;
				currentPos.second++;
			}

			glm::vec2 offset((float)(currentPos.first*m_characterWidth) / m_sheetWidth, -(float)(currentPos.second*m_characterHeight) / m_sheetHeight);
			nextFrame = new AnimationFrame(offset,frameTime);
			previousFrame->next = nextFrame;
			previousFrame = nextFrame;
		}

		//set the last frame to point to the first so it circles back
		previousFrame->next = firstFrame;
		previousFrame->isLastFrame = true;

		m_animations.insert(std::make_pair(p_name, firstFrame));
	}

	void SpriteSheet::setDefaultAnimation(const std::string& p_name)
	{
		auto found = m_animations.find(p_name);
		if (found != m_animations.cend())
		{
			m_defaultAnimation = ((*found).second);
		}
	}

	const SpriteSheet::AnimationFrame* SpriteSheet::getAnimation(const std::string& p_name) const
	{
		auto found = m_animations.find(p_name);
		if (found != m_animations.cend())
		{
			return (*found).second;
		}
		return nullptr;
	}

	const SpriteSheet::AnimationFrame* SpriteSheet::getDefaultAnimation() const
	{
		return m_defaultAnimation;
	}
}