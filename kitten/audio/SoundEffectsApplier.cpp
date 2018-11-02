#include "SoundEffectsApplier.h"

namespace kitten
{
	SoundEffectsApplier::SoundEffectsApplier(irrklang::ISoundEffectControl* p_effectControl) : m_chorusParams(nullptr), m_compressorParams(nullptr), m_distortionParams(nullptr),
		m_echoParams(nullptr), m_flangerParams(nullptr), m_gargleParams(nullptr), m_3DReverbParams(nullptr), m_paramEqParams(nullptr),
		m_wavesReverbParams(nullptr), m_hasEffects(false), m_effectControl(p_effectControl)
	{

	}

	SoundEffectsApplier::~SoundEffectsApplier()
	{
		delete m_chorusParams;
		delete m_compressorParams;
		delete m_distortionParams;
		delete m_echoParams;
		delete m_flangerParams;
		delete m_gargleParams;
		delete m_3DReverbParams;
		delete m_paramEqParams;
		delete m_wavesReverbParams;

		//Controller gets deleted with the attached Sound's lifetime
	}

	void SoundEffectsApplier::updateHasEffects()
	{
		m_hasEffects = (m_chorusParams != nullptr || m_compressorParams != nullptr || m_distortionParams != nullptr || m_echoParams != nullptr
			|| m_flangerParams != nullptr || m_gargleParams != nullptr || m_3DReverbParams != nullptr || m_paramEqParams != nullptr
			|| m_wavesReverbParams != nullptr);

	}

	void SoundEffectsApplier::applyEffects()
	{
		if (m_hasEffects)
		{
			if (m_chorusParams != nullptr)
			{
				m_effectControl->enableChorusSoundEffect(m_chorusParams->wetDyMix, m_chorusParams->depth,
					m_chorusParams->feedback, m_chorusParams->frequency, m_chorusParams->sinusWaveForm, m_chorusParams->delay, m_chorusParams->phase);
			}

			if (m_compressorParams != nullptr)
			{
				m_effectControl->enableCompressorSoundEffect(m_compressorParams->gain, m_compressorParams->attack, m_compressorParams->release,
					m_compressorParams->threshold, m_compressorParams->ratio, m_compressorParams->preDelay);
			}

			if (m_distortionParams != nullptr)
			{
				m_effectControl->enableDistortionSoundEffect(m_distortionParams->gain, m_distortionParams->edge, m_distortionParams->postEqCenterFreq,
					m_distortionParams->postEqBandwidth, m_distortionParams->preLowpassCutoff);
			}

			if (m_echoParams != nullptr)
			{
				m_effectControl->enableEchoSoundEffect(m_echoParams->wetDyMix, m_echoParams->feedback, m_echoParams->leftDelay,
					m_echoParams->rightDelay, m_echoParams->panDelay);
			}

			if (m_flangerParams != nullptr)
			{
				m_effectControl->enableFlangerSoundEffect(m_flangerParams->wetDryMix, m_flangerParams->depth, m_flangerParams->feedback,
					m_flangerParams->frequency, m_flangerParams->triangleWaveForm, m_flangerParams->delay, m_flangerParams->phase);
			}

			if (m_gargleParams != nullptr)
			{
				m_effectControl->enableGargleSoundEffect(m_gargleParams->rateHz, m_gargleParams->sinusWaveForm);
			}

			if (m_3DReverbParams != nullptr)
			{
				m_effectControl->enableI3DL2ReverbSoundEffect(m_3DReverbParams->room, m_3DReverbParams->roomHF, m_3DReverbParams->roomRolloffFactor,
					m_3DReverbParams->decayTime, m_3DReverbParams->decayHFRatio, m_3DReverbParams->reflections, m_3DReverbParams->reflectionsDelay,
					m_3DReverbParams->reverb, m_3DReverbParams->reverbDelay, m_3DReverbParams->diffusion, m_3DReverbParams->density, m_3DReverbParams->hfReference);
			}

			if (m_paramEqParams != nullptr)
			{
				m_effectControl->enableParamEqSoundEffect(m_paramEqParams->center, m_paramEqParams->bandwidth, m_paramEqParams->gain);
			}

			if (m_wavesReverbParams != nullptr)
			{
				m_effectControl->enableWavesReverbSoundEffect(m_wavesReverbParams->gain, m_wavesReverbParams->reverbMix, m_wavesReverbParams->reverbTime,
					m_wavesReverbParams->highFreqRTRatio);
			}
		}
	}

	void SoundEffectsApplier::setController(irrklang::ISoundEffectControl* p_controller)
	{
		m_effectControl = p_controller;
	}

	void SoundEffectsApplier::setChorusEffect(irrklang::ik_f32 p_wetDryMix, irrklang::ik_f32 p_depth, irrklang::ik_f32 p_feedback, irrklang::ik_f32 p_frequency,
		bool p_sinusWaveForm, irrklang::ik_f32 p_delay, irrklang::ik_s32 p_phase)
	{
		if (m_chorusParams == nullptr)
		{
			m_chorusParams = new ChorusEffectParams();
		}

		m_chorusParams->wetDyMix = p_wetDryMix;
		m_chorusParams->depth = p_depth;
		m_chorusParams->feedback = p_feedback;
		m_chorusParams->frequency = p_frequency;
		m_chorusParams->sinusWaveForm = p_sinusWaveForm;
		m_chorusParams->delay = p_delay;
		m_chorusParams->phase = p_phase;

		m_hasEffects = true;

		m_effectControl->enableChorusSoundEffect(m_chorusParams->wetDyMix, m_chorusParams->depth,
			m_chorusParams->feedback, m_chorusParams->frequency, m_chorusParams->sinusWaveForm, m_chorusParams->delay, m_chorusParams->phase);
	}

	void SoundEffectsApplier::setCompressorEffect(irrklang::ik_f32 p_gain, irrklang::ik_f32 p_attack, irrklang::ik_f32 p_release, irrklang::ik_f32 p_threshold, 
		irrklang::ik_f32 p_ratio, irrklang::ik_f32 p_predelay)
	{
		if (m_compressorParams == nullptr)
		{
			m_compressorParams = new CompressorSoundEffectParams();
		}

		m_compressorParams->gain = p_gain;
		m_compressorParams->attack = p_attack;
		m_compressorParams->release = p_release;
		m_compressorParams->threshold = p_threshold;
		m_compressorParams->ratio = p_ratio;
		m_compressorParams->preDelay = p_predelay;

		m_hasEffects = true;

		m_effectControl->enableCompressorSoundEffect(m_compressorParams->gain, m_compressorParams->attack, m_compressorParams->release,
			m_compressorParams->threshold, m_compressorParams->ratio, m_compressorParams->preDelay);
	}

	void SoundEffectsApplier::setDistortionEffect(irrklang::ik_f32 p_gain, irrklang::ik_f32 p_edge, irrklang::ik_f32 p_postEQCenterFrequency, 
		irrklang::ik_f32 p_postEQBandwidth, irrklang::ik_f32 p_preLowpassCutoff)
	{
		if (m_distortionParams == nullptr)
		{
			m_distortionParams = new DistortionSoundEffectParams();
		}

		m_distortionParams->gain = p_gain;
		m_distortionParams->edge = p_edge;
		m_distortionParams->postEqCenterFreq = p_postEQCenterFrequency;
		m_distortionParams->postEqBandwidth = p_postEQBandwidth;
		m_distortionParams->preLowpassCutoff = p_preLowpassCutoff;

		m_hasEffects = true;

		m_effectControl->enableDistortionSoundEffect(m_distortionParams->gain, m_distortionParams->edge, m_distortionParams->postEqCenterFreq,
			m_distortionParams->postEqBandwidth, m_distortionParams->preLowpassCutoff);
	}

	void SoundEffectsApplier::setEchoEffect(irrklang::ik_f32 p_wetDryMix, irrklang::ik_f32 p_feedback, irrklang::ik_f32 p_leftDelay, 
		irrklang::ik_f32 p_rightDelay, irrklang::ik_s32 p_panDelay)
	{
		if (m_echoParams == nullptr)
		{
			m_echoParams = new EchoSoundEffectParams();
		}

		m_echoParams->wetDyMix = p_wetDryMix;
		m_echoParams->feedback = p_feedback;
		m_echoParams->leftDelay = p_leftDelay;
		m_echoParams->rightDelay = p_rightDelay;
		m_echoParams->panDelay = p_panDelay;

		m_hasEffects = true;

		m_effectControl->enableEchoSoundEffect(m_echoParams->wetDyMix, m_echoParams->feedback, m_echoParams->leftDelay,
			m_echoParams->rightDelay, m_echoParams->panDelay);
	}

	void SoundEffectsApplier::setFlangerEffect(irrklang::ik_f32 p_wetDryMix, irrklang::ik_f32 p_depth, irrklang::ik_f32 p_feedback, irrklang::ik_f32 p_frequency,
		bool p_triangleWaveForm, irrklang::ik_f32 p_delay, irrklang::ik_s32 p_phase)
	{
		if (m_flangerParams == nullptr)
		{
			m_flangerParams = new FlangerSoundEffectParams();
		}

		m_flangerParams->wetDryMix = p_wetDryMix;
		m_flangerParams->depth = p_depth;
		m_flangerParams->feedback = p_feedback;
		m_flangerParams->frequency = p_frequency;
		m_flangerParams->triangleWaveForm = p_triangleWaveForm;
		m_flangerParams->delay = p_delay;
		m_flangerParams->phase = p_phase;

		m_hasEffects = true;

		m_effectControl->enableFlangerSoundEffect(m_flangerParams->wetDryMix, m_flangerParams->depth, m_flangerParams->feedback,
			m_flangerParams->frequency, m_flangerParams->triangleWaveForm, m_flangerParams->delay, m_flangerParams->phase);
	}

	void SoundEffectsApplier::setGargleEffect(irrklang::ik_s32 p_rateHz, bool p_sinusWaveForm)
	{
		if (m_gargleParams == nullptr)
		{
			m_gargleParams = new GargleSoundEffectParams();
		}

		m_gargleParams->rateHz = p_rateHz;
		m_gargleParams->sinusWaveForm = p_sinusWaveForm;

		m_hasEffects = true;

		m_effectControl->enableGargleSoundEffect(m_gargleParams->rateHz, m_gargleParams->sinusWaveForm);
	}

	void SoundEffectsApplier::set3DReverbEffect(irrklang::ik_s32 p_room, irrklang::ik_s32 p_roomHF, irrklang::ik_f32 p_roomRolloffFactor, irrklang::ik_f32 p_decayTime, 
		irrklang::ik_f32 p_decayHFRatio, irrklang::ik_s32 p_reflections, irrklang::ik_f32 p_reflectionsDelay, irrklang::ik_s32 p_reverb, irrklang::ik_f32 p_reverbDelay, 
		irrklang::ik_f32 p_diffusion, irrklang::ik_f32 p_density, irrklang::ik_f32 p_hfReference)
	{
		if (m_3DReverbParams == nullptr)
		{
			m_3DReverbParams = new I3DL2ReverbSoundEffectParams();
		}

		m_3DReverbParams->room = p_room;
		m_3DReverbParams->roomHF = p_roomHF;
		m_3DReverbParams->roomRolloffFactor = p_roomRolloffFactor;
		m_3DReverbParams->decayTime = p_decayTime;
		m_3DReverbParams->decayHFRatio = p_decayHFRatio;
		m_3DReverbParams->reflections = p_reflections;
		m_3DReverbParams->reflectionsDelay = p_reflectionsDelay;
		m_3DReverbParams->reverb = p_reverb;
		m_3DReverbParams->reverbDelay = p_reverbDelay;
		m_3DReverbParams->diffusion = p_diffusion;
		m_3DReverbParams->density = p_density;
		m_3DReverbParams->hfReference = p_hfReference;

		m_hasEffects = true;

		m_effectControl->enableI3DL2ReverbSoundEffect(m_3DReverbParams->room, m_3DReverbParams->roomHF, m_3DReverbParams->roomRolloffFactor,
			m_3DReverbParams->decayTime, m_3DReverbParams->decayHFRatio, m_3DReverbParams->reflections, m_3DReverbParams->reflectionsDelay,
			m_3DReverbParams->reverb, m_3DReverbParams->reverbDelay, m_3DReverbParams->diffusion, m_3DReverbParams->density, m_3DReverbParams->hfReference);
	}

	void SoundEffectsApplier::setParamEqEffect(irrklang::ik_f32 p_center, irrklang::ik_f32 p_bandwidth, irrklang::ik_f32 p_gain)
	{
		if (m_paramEqParams == nullptr)
		{
			m_paramEqParams = new ParamEqSoundEffectParams();
		}

		m_paramEqParams->center = p_center;
		m_paramEqParams->bandwidth = p_bandwidth;
		m_paramEqParams->gain = p_gain;

		m_hasEffects = true;

		m_effectControl->enableParamEqSoundEffect(m_paramEqParams->center, m_paramEqParams->bandwidth, m_paramEqParams->gain);
	}

	void SoundEffectsApplier::setWavesReverbEffect(irrklang::ik_f32 p_inGain, irrklang::ik_f32 p_reverbMix, irrklang::ik_f32 p_reverbTime, irrklang::ik_f32 p_highFreqRTRatio)
	{
		if (m_wavesReverbParams == nullptr)
		{
			m_wavesReverbParams = new WavesReverbSoundEffectParams();
		}

		m_wavesReverbParams->gain = p_inGain;
		m_wavesReverbParams->reverbMix = p_reverbMix;
		m_wavesReverbParams->reverbTime = p_reverbTime;
		m_wavesReverbParams->highFreqRTRatio = p_highFreqRTRatio;

		m_hasEffects = true;

		m_effectControl->enableWavesReverbSoundEffect(m_wavesReverbParams->gain, m_wavesReverbParams->reverbMix, m_wavesReverbParams->reverbTime,
			m_wavesReverbParams->highFreqRTRatio);
	}

	void SoundEffectsApplier::disableChorusEffect()
	{
		delete m_chorusParams;
		updateHasEffects();
	}

	void SoundEffectsApplier::disableComppressorEffect()
	{
		delete m_compressorParams;
		updateHasEffects();
	}

	void SoundEffectsApplier::disableDistortionEffect()
	{
		delete m_distortionParams;
		updateHasEffects();
	}

	void SoundEffectsApplier::disableEchoEffect()
	{
		delete m_echoParams;
		updateHasEffects();
	}

	void SoundEffectsApplier::disableFlangerEffect()
	{
		delete m_flangerParams;
		updateHasEffects();
	}

	void SoundEffectsApplier::disableGargleEffect()
	{
		delete m_gargleParams;
		updateHasEffects();
	}

	void SoundEffectsApplier::disable3DReverbEffect()
	{
		delete m_3DReverbParams;
		updateHasEffects();
	}

	void SoundEffectsApplier::disableParamEqEffect()
	{
		delete m_paramEqParams;
		updateHasEffects();
	}

	void SoundEffectsApplier::disableWavesReverbEffect()
	{
		delete m_wavesReverbParams;
		updateHasEffects();
	}
}