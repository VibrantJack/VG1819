#include "PlayerPrefs.h"

#include "kitten\util\AsyncFileOperations.h"
#include "_Project\UniversalSounds.h"

#include <fstream>

PlayerPrefs* PlayerPrefs::sm_instance = nullptr;

PlayerPrefs::PlayerPrefs() : m_bgmVolume(1), m_sfxVolume(1), m_fullscreen(false), m_resolution(1280,720)
{
	assert(sm_instance == nullptr);
	sm_instance = this;
}

PlayerPrefs::~PlayerPrefs()
{
	sm_instance = nullptr;
}

void PlayerPrefs::start()
{
	// Load the file
	std::ifstream stream(PLAYER_PREFS_FILE_PATH);
	
	if (stream.is_open())
	{
		nlohmann::json jsonFile;

		stream >> jsonFile;
		stream.close();

		// Load settings from json

		auto foundBGM = jsonFile.find("BGM_Volume");
		auto foundSFX = jsonFile.find("SFX_Volume");
		auto foundFullscreen = jsonFile.find("Fullscreen");
		auto foundRes = jsonFile.find("Resolution");

		if (foundBGM != jsonFile.end())
		{
			m_bgmVolume = (*foundBGM);
		}

		if (foundSFX != jsonFile.end())
		{
			m_sfxVolume = (*foundSFX);
		}

		if (foundFullscreen != jsonFile.end())
		{
			m_fullscreen = (*foundFullscreen);
		}

		if (foundRes != jsonFile.end())
		{
			int windowX = (*foundRes)[0];
			int windowY = (*foundRes)[1];

			m_resolution = std::make_pair(windowX, windowY);

			glfwSetWindowSize(windowX, windowY);
		}
	}
	else 
	{
		// No file to open, make a default one
		privateSaveAllSettings();
	}
}

void PlayerPrefs::setSFXVolume(float p_volume)
{
	sm_instance->privateSetSFXVolume(p_volume);
}

void PlayerPrefs::privateSetSFXVolume(float p_volume)
{
	m_sfxVolume = p_volume;
}

float PlayerPrefs::getSFXVolume()
{
	return sm_instance->m_sfxVolume;
}

void PlayerPrefs::setBGMVolume(float p_volume)
{
	sm_instance->privateSetBGMVolume(p_volume);
}

void PlayerPrefs::privateSetBGMVolume(float p_volume)
{
	m_bgmVolume = p_volume;
	UniversalSounds::setVolume(p_volume);
}

float PlayerPrefs::getBGMVolume()
{
	return sm_instance->m_bgmVolume;
}

// Doesn't go anything yet --
// GLFW does not support switching
void PlayerPrefs::setFullscreen(bool p_isFullscreen)
{
	sm_instance->privateSetFullscreen(p_isFullscreen);
}

void PlayerPrefs::privateSetFullscreen(bool p_isFullscreen)
{
	m_fullscreen = p_isFullscreen;
}

// Our GLFW version does not support switching modes at runtime,
// So we are always windowed
bool PlayerPrefs::getFullscreen()
{
	return false;
}

void PlayerPrefs::setResolution(int p_windowX, int p_windowY)
{
	sm_instance->privateSetResolution(p_windowX, p_windowY);
}

void PlayerPrefs::privateSetResolution(int p_windowX, int p_windowY)
{
	m_resolution = std::make_pair(p_windowX, p_windowY);

	glfwSetWindowSize(p_windowX, p_windowY);
}

std::pair<int, int> PlayerPrefs::getResolution()
{
	return sm_instance->m_resolution;
}

void PlayerPrefs::saveAllSettings()
{
	sm_instance->privateSaveAllSettings();
}

void PlayerPrefs::privateSaveAllSettings()
{
	std::string fileContents = toJsonString();

	std::ofstream outStream(PLAYER_PREFS_FILE_PATH);
	outStream << fileContents;
	outStream.close();
}

void PlayerPrefs::asyncSaveAllSettings()
{
	sm_instance->privateAsyncSaveAllSettings();
}

void PlayerPrefs::privateAsyncSaveAllSettings()
{
	std::string fileContents = toJsonString();

	kitten::AsyncFileOperations::saveToFile(PLAYER_PREFS_FILE_PATH, true, fileContents.c_str());
}

// C++ strings still painful  -Callum
#define st(thing) std::string(thing)
#define ts(thing) std::to_string(thing)

std::string PlayerPrefs::toJsonString()
{
	std::string jsonString =
		"{\n" +
			st("BGM_Volume : ") + ts(m_bgmVolume) + st("\n") +
			st("SFX_Volume : ") + ts(m_sfxVolume) + st("\n") +
			st("Fullscreen : ") + (m_fullscreen ? st("true") : st("false")) + st("\n") +
			st("Resolution : [") + ts(m_resolution.first) + ", " + ts(m_resolution.second) + "]\n" +
		st("}\n");

	return jsonString;
}