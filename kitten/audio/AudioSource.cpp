#include "AudioSource.h"
#include "AudioEngineWrapper.h"
#include "util\MathUtil.h"
#include <iostream>

namespace kitten
{
	AudioSource::AudioSource(nlohmann::json & p_json): K_Component(p_json),
		m_clipPath(LOOKUPSTR("clippath")),
		m_is3D(LOOKUPDEF("is3d",false)), 
		m_effectsEnabled(LOOKUPDEF("enableeffects", false)),
		m_causesDuck(LOOKUPDEF("causesduck", false)),
		m_beingDucked(false), 
		m_getsDucked(LOOKUPDEF("getsducked", false))
	{
		m_audioClip = AudioEngineWrapper::sm_instance->getSound(m_clipPath, m_is3D, m_effectsEnabled);
		assert(m_audioClip != nullptr);

		m_sfxController = new SoundEffectsApplier(m_audioClip->getSoundEffectControl());

		setupMemberVars();

		if (m_getsDucked)
		{
			//AudioEngineWrapper::sm_instance->addToDuck(this);
		}

		if (m_is3D) {
			if (JSONHAS("mindistance")) {
				setMinDistance(LOOKUP("mindistance"));
			}

			if (JSONHAS("maxdistance")) {
				setMaxDistance(LOOKUP("maxdistance"));
			}
		}

		if (JSONHAS("loop")) {
			setLooped(LOOKUP("loop"));
		}

		if (JSONHAS("volume")) {
			setVolume(LOOKUP("volume"));
		}

		if (JSONHAS("playprogress")) {
			setPlayProgress(LOOKUP("playprogress"));
		}

		if (m_effectsEnabled) {
			//Effects parsing here

#define innerJsonHas(str) innerJson.find(str) != innerJson.end()
#define setInnerVar(varName,jsonName) if(innerJsonHas(jsonName)) varName = innerJson[jsonName]

			auto sfx = getSFXControl();

			if (JSONHAS("choruseffect")) {
				irrklang::ik_f32 wetDryMix = 50, depth = 10, feedback = 25, frequency = 1.1;
				bool sinusWaveForm = true;
				irrklang::ik_f32 delay = 16, phase = 90;

				auto innerJson = p_json["choruseffect"];

				setInnerVar(wetDryMix, "wetdrymix");
				setInnerVar(depth, "depth");
				setInnerVar(feedback, "feedback");
				setInnerVar(frequency, "frequency");
				setInnerVar(sinusWaveForm, "sinuswaveform");
				setInnerVar(delay, "delay");
				setInnerVar(phase, "phase");

				sfx->setChorusEffect(wetDryMix, depth, feedback, frequency, sinusWaveForm, delay, phase);
			}

			if (JSONHAS("compressoreffect")) {
				irrklang::ik_f32 gain = 0, attack = 10, release = 200, threshold = -20,
					ratio = 3, preDelay = 4;

				auto innerJson = LOOKUP("compressoreffect");

				setInnerVar(gain, "gain");
				setInnerVar(attack, "attack");
				setInnerVar(release, "release");
				setInnerVar(threshold, "threshold");
				setInnerVar(ratio, "ratio");
				setInnerVar(preDelay, "predelay");

				sfx->setCompressorEffect(gain, attack, release, threshold, ratio, preDelay);
			}

			if (JSONHAS("distortioneffect")) {
				irrklang::ik_f32 gain = -18, edge = 15, postEQCenterFrequency = 2400,
					postEQBandwidth = 2400, preLowpassCutoff = 8000;

				auto innerJson = LOOKUP("distortioneffect");

				setInnerVar(gain, "gain");
				setInnerVar(edge, "edge");
				setInnerVar(postEQCenterFrequency, "posteqcenterfrequency");
				setInnerVar(postEQBandwidth, "posteqbandwidth");
				setInnerVar(preLowpassCutoff, "prelowpasscutoff");

				sfx->setDistortionEffect(gain, edge, postEQCenterFrequency, postEQBandwidth, preLowpassCutoff);
			}

			if (JSONHAS("echoeffect")) {
				irrklang::ik_f32 wetDryMix = 50, feedback = 50,
					leftDelay = 500, rightDelay = 500, panDelay = 0;

				auto innerJson = LOOKUP("echoeffect");

				setInnerVar(wetDryMix, "wetdrymix");
				setInnerVar(feedback, "feedback");
				setInnerVar(leftDelay, "leftdelay");
				setInnerVar(rightDelay, "rightdelay");
				setInnerVar(panDelay, "pandelay");

				sfx->setEchoEffect(wetDryMix, feedback, leftDelay, rightDelay, panDelay);
			}

			if (JSONHAS("flangereffect")) {
				irrklang::ik_f32 wetDryMix = 50, depth = 100,
					feedback = -50, frequency = 0.25f, delay = 2;
				irrklang::ik_s32 phase = 0;
				bool triangleWaveForm = true;

				auto innerJson = LOOKUP("flangereffect");

				setInnerVar(wetDryMix, "wetdrymix");
				setInnerVar(depth, "depth");
				setInnerVar(feedback, "feedback");
				setInnerVar(frequency, "frequency");
				setInnerVar(delay, "delay");
				setInnerVar(phase, "phase");
				setInnerVar(triangleWaveForm, "trianglewaveform");

				sfx->setFlangerEffect(wetDryMix, depth, feedback, frequency, triangleWaveForm, delay, phase);
			}

			if (JSONHAS("gargleeffect")) {
				irrklang::ik_s32 rateHz = 20;
				bool sinusWaveForm = true;

				auto innerJson = LOOKUP("gargleffect");

				setInnerVar(rateHz, "ratehz");
				setInnerVar(sinusWaveForm, "sinuswaveform");

				sfx->setGargleEffect(rateHz, sinusWaveForm);
			}

			if (JSONHAS("3dreverbeffect")) {
				irrklang::ik_s32 room = -1000, roomHF = -100,
					reflections = -2602, reverb = 200;
				irrklang::ik_f32 roomRolloffFactor = 0, decayTime = 1.49f, decayHFRatio = 0.83f,
					reflectionsDelay = 0.007f, reverbDelay = 0.011f, diffusion = 100,
					density = 100, hfReference = 5000;

				auto innerJson = LOOKUP("3dreverbeffect");

				setInnerVar(room, "room");
				setInnerVar(roomHF, "roomHF");
				setInnerVar(reflections, "reflections");
				setInnerVar(reverb, "reverb");
				setInnerVar(roomRolloffFactor, "roomrollofffactor");
				setInnerVar(decayTime, "decaytime");
				setInnerVar(decayHFRatio, "decayhfratio");
				setInnerVar(reflectionsDelay, "reflectionsdelay");
				setInnerVar(reverbDelay, "reverbdelay");
				setInnerVar(diffusion, "diffusion");
				setInnerVar(density, "density");
				setInnerVar(hfReference, "hfReference");

				sfx->set3DReverbEffect(room, roomHF, roomRolloffFactor, decayTime, decayHFRatio, reflections, reflectionsDelay, reverb, reverbDelay, diffusion, density, hfReference);
			}

			if (JSONHAS("parameqeffect")) {
				irrklang::ik_f32 center = 8000, bandwidth = 12,
					gain = 0;

				auto innerJson = LOOKUP("parameqeffect");

				setInnerVar(center, "center");
				setInnerVar(bandwidth, "bandwidth");
				setInnerVar(gain, "gain");

				sfx->setParamEqEffect(center, bandwidth, gain);
			}

			if (JSONHAS("wavesreverbeffect")) {
				irrklang::ik_f32 gain = 0, reverbMix = 0,
					reverbTime = 1000, highFreqRTRatio = 0.001f;

				auto innerJson = LOOKUP("wavesreverbeffect");

				setInnerVar(gain, "gain");
				setInnerVar(reverbMix, "reverbmix");
				setInnerVar(reverbTime, "reverbtime");
				setInnerVar(highFreqRTRatio, "highfreqrtratio");

				sfx->setWavesReverbEffect(gain, reverbMix, reverbTime, highFreqRTRatio);
			}
		}
	}


	AudioSource::AudioSource(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects, bool p_causesDuck, bool p_getsDucked) : m_clipPath(p_pathToClip),
		m_is3D(p_is3D),  m_effectsEnabled(p_enableEffects), m_causesDuck(p_causesDuck), m_beingDucked(false), m_getsDucked(p_getsDucked)
	{
		m_audioClip = AudioEngineWrapper::sm_instance->getSound(p_pathToClip, p_is3D, p_enableEffects);
		assert(m_audioClip != nullptr);
		
		m_sfxController = new SoundEffectsApplier(m_audioClip->getSoundEffectControl());

		setupMemberVars();

		if (p_getsDucked)
		{
			//AudioEngineWrapper::sm_instance->addToDuck(this);
		}
	}

	AudioSource::~AudioSource()
	{
		m_audioClip->stop();
		m_audioClip->drop();
		//m_audioClip->andRoll();

		if (m_getsDucked)
		{
			//AudioEngineWrapper::sm_instance->removeFromDuck(this);
		}

		delete m_sfxController;
	}

	void AudioSource::start()
	{
		if (m_is3D)
		{
			Transform& transform = getTransform();
			const glm::vec3& vecPos = transform.getTranslation();
			transform.addPositionListener(this);

			onPosChanged(vecPos);
		}
	}

	void AudioSource::onDisabled()
	{
		m_wasPaused = m_audioClip->getIsPaused();
		setPaused(true);
	}

	void AudioSource::onEnabled()
	{
		setPaused(m_wasPaused);
	}

	void AudioSource::onPosChanged(const glm::vec3& p_newPos)
	{
		irrklang::vec3df pos(p_newPos.x, p_newPos.y, p_newPos.z);

		m_audioClip->setPosition(pos);
	}

	//Private helper
	void AudioSource::setupMemberVars() //Sets things that could be different from defaults because the audio source has custom defaults
	{
		m_clipLength = m_audioClip->getPlayLength();
		m_isLooped = m_audioClip->isLooped();
		m_volume = m_audioClip->getVolume();
		m_minDist = m_audioClip->getMinDistance();
		m_maxDist = m_audioClip->getMaxDistance();
		m_causingDuckFactor = (m_volume / 1.0f) - 0.75f;

		if (m_causesDuck)
		{
			//m_audioClip->setSoundStopEventReceiver(this);
		}
	}

	void AudioSource::play()
	{	
		if (m_audioClip->isFinished())
		{
			//remake audio source
			m_audioClip->stop(); // stop needed? 
			m_audioClip->drop();

			m_audioClip = AudioEngineWrapper::sm_instance->getSound(m_clipPath, m_is3D, m_effectsEnabled);
			m_audioClip->setMinDistance(m_minDist);
			m_audioClip->setMaxDistance(m_maxDist);
			m_audioClip->setIsLooped(m_isLooped);
			m_sfxController->setController(m_audioClip->getSoundEffectControl());
			m_sfxController->applyEffects();

			if (m_is3D)
			{
				onPosChanged(getTransform().getTranslation());
			}

			if (m_beingDucked)
			{
				m_audioClip->setVolume(m_volume * m_beingDuckedFactor);
			}
			else
			{
				m_audioClip->setVolume(m_volume);
			}

			if (m_causesDuck)
			{
				//m_audioClip->setSoundStopEventReceiver(this);
			}

			m_audioClip->setIsPaused(false);
		}
		else
		{
			m_audioClip->setPlayPosition(0);
			m_audioClip->setIsPaused(false);
		}

		if (m_causesDuck)
		{
			tryDuckOthers(true);
		}
	}

	void AudioSource::setClip(const std::string& p_pathToClip, bool p_is3D, bool p_enableEffects)
	{
		if (m_causesDuck)
		{
			tryDuckOthers(false);
		}

		m_audioClip->stop();
		m_audioClip->drop();
		
		m_clipPath = p_pathToClip;

		m_audioClip = AudioEngineWrapper::sm_instance->getSound(p_pathToClip, p_is3D, p_enableEffects);
		assert(m_audioClip != nullptr);

		m_is3D = p_is3D;
		m_effectsEnabled = p_enableEffects;
		setupMemberVars();
	}

	void AudioSource::setPaused(bool p_paused)
	{
		m_audioClip->setIsPaused(p_paused);
		
		if (m_causesDuck)
		{
			tryDuckOthers(!p_paused);
		}
	}

	bool AudioSource::isPaused() const
	{
		return m_audioClip->getIsPaused();
	}

	bool AudioSource::isFinished() const
	{
		return m_audioClip->isFinished();
	}

	void AudioSource::setLooped(bool p_looped)
	{
		m_audioClip->setIsLooped(p_looped);
		m_isLooped = p_looped;
	}

	bool AudioSource::isLooped()
	{
		return m_isLooped;
	}

	void AudioSource::setVolume(const float& p_volume)
	{
		m_volume = p_volume;
		//m_causingDuckFactor = (m_volume / 1.0f) - 0.75f;

		if (m_beingDucked)
		{
			m_audioClip->setVolume(p_volume * m_beingDuckedFactor);
		}
		else
		{
			m_audioClip->setVolume(p_volume);
		}

		if (m_causesDuck)
		{
			tryDuckOthers(true);
		}
	}

	float AudioSource::getVolume() const
	{
		return m_volume;
	}

	void AudioSource::setMinDistance(const float& p_dist)
	{
		m_audioClip->setMinDistance(p_dist);
		m_minDist = p_dist;
	}

	float AudioSource::getMinDistance() const
	{
		return m_minDist;
	}

	void AudioSource::setMaxDistance(const float& p_dist)
	{
		m_audioClip->setMaxDistance(p_dist);
		m_maxDist = p_dist;
	}

	float AudioSource::getMaxDistance() const
	{
		return m_maxDist;
	}

	void AudioSource::setPlayProgress(const float& p_place)
	{
		irrklang::ik_u32 toSet = m_clipLength / p_place;
		m_audioClip->setPlayPosition(toSet);
	}

	float AudioSource::getPlayProgress()
	{
		return m_audioClip->getPlayPosition() / m_clipLength;
	}

	SoundEffectsApplier* AudioSource::getSFXControl()
	{
		return m_sfxController;
	}

	void AudioSource::startDucking(const float& p_factor)
	{
		m_beingDucked = true;
		m_beingDuckedFactor = p_factor;
		m_audioClip->setVolume(m_volume * p_factor);
	}

	void AudioSource::stopDucking()
	{
		m_beingDucked = false;
		m_audioClip->setVolume(m_volume);
	}

	void AudioSource::tryDuckOthers(bool p_startDuck)
	{
		if (p_startDuck)
		{
			if (!m_audioClip->getIsPaused()) //Does this work if the audioClip is finished as well?
			{
				AudioEngineWrapper::sm_instance->startDuck(m_causingDuckFactor);
			}
		}
		else
		{
			if (m_audioClip->getIsPaused() || m_audioClip->isFinished())
			{
				AudioEngineWrapper::sm_instance->stopDuck(m_causingDuckFactor);
			}
		}
	}

	void AudioSource::OnSoundStopped(irrklang::ISound* p_sound, irrklang::E_STOP_EVENT_CAUSE p_reason, void* p_userData)
	{
		if (m_causesDuck)
		{
			tryDuckOthers(false);
		}
	}
}