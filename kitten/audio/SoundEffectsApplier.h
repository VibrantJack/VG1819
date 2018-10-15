#pragma once
#include "AudioEngineWrapper.h"

namespace kitten
{
	// Needed to apply sound effects over the lifetime of the audio source
	// - Callum

	class AudioSource;

	class SoundEffectsApplier
	{
		friend class AudioSource;
	private:
		struct ChorusEffectParams
		{
			irrklang::ik_f32 wetDyMix = 50, depth = 10,
				feedback = 25, frequency = 1.1f, delay = 16;
			irrklang::ik_s32 phase = 90;
			bool sinusWaveForm = true;
		};

		struct CompressorSoundEffectParams
		{
			irrklang::ik_f32 gain = 0, attack = 10,
				release = 200, threshold = -20, ratio = 3,
				preDelay = 4;
		};

		struct DistortionSoundEffectParams
		{
			irrklang::ik_f32 gain = -18, edge = 15,
				postEqCenterFreq = 2400, postEqBandwidth = 2400,
				preLowpassCutoff = 8000;
		};

		struct EchoSoundEffectParams
		{
			irrklang::ik_f32 wetDyMix = 50, feedback = 50,
				leftDelay = 500, rightDelay = 500, panDelay = 0;
		};

		struct FlangerSoundEffectParams
		{
			irrklang::ik_f32 wetDryMix = 50, depth = 100,
				feedback = -50, frequency = 0.25f, delay = 2;
			irrklang::ik_s32 phase = 0;
			bool triangleWaveForm = true;
		};

		struct GargleSoundEffectParams
		{
			irrklang::ik_s32 rateHz = 20;
			bool sinusWaveForm = true;
		};

		struct I3DL2ReverbSoundEffectParams
		{
			irrklang::ik_s32 room = -1000, roomHF = -100,
				reflections = -2602, reverb = 200;
			irrklang::ik_f32 roomRolloffFactor = 0, decayTime = 1.49f,decayHFRatio = 0.83f,
				reflectionsDelay = 0.007f, reverbDelay = 0.011f, diffusion = 100,
				density = 100, hfReference = 5000;
		};

		struct ParamEqSoundEffectParams
		{
			irrklang::ik_f32 center = 8000, bandwidth = 12,
				gain = 0;
		};

		struct WavesReverbSoundEffectParams
		{
			irrklang::ik_f32 gain = 0, reverbMix = 0,
				reverbTime = 1000, highFreqRTRatio = 0.001f;
		};

	private:
		ChorusEffectParams* m_chorusParams;
		CompressorSoundEffectParams* m_compressorParams;
		DistortionSoundEffectParams* m_distortionParams;
		EchoSoundEffectParams* m_echoParams;
		FlangerSoundEffectParams* m_flangerParams;
		GargleSoundEffectParams* m_gargleParams;
		I3DL2ReverbSoundEffectParams* m_3DReverbParams;
		ParamEqSoundEffectParams* m_paramEqParams;
		WavesReverbSoundEffectParams* m_wavesReverbParams;

		irrklang::ISoundEffectControl* m_effectControl;

		bool m_hasEffects = false;

		void updateHasEffects();
		void applyEffects();
		void setController(irrklang::ISoundEffectControl* p_effectControl);
	public:
		SoundEffectsApplier(irrklang::ISoundEffectControl* p_effectControl);
		~SoundEffectsApplier();
		
		//@TODO: Change these from p_UpperCase to p_lowerCase

		void setChorusEffect(irrklang::ik_f32 p_WetDryMix = 50, irrklang::ik_f32 p_Depth = 10, irrklang::ik_f32 p_Feedback = 25, irrklang::ik_f32 p_Frequency = 1.1, 
			bool sinusWaveForm = true, irrklang::ik_f32 p_Delay = 16, irrklang::ik_s32 p_Phase = 90);

		void setCompressorEffect(irrklang::ik_f32 p_Gain = 0, irrklang::ik_f32 p_Attack = 10, irrklang::ik_f32 p_Release = 200, irrklang::ik_f32 p_Threshold = -20, 
			irrklang::ik_f32 p_Ratio = 3, irrklang::ik_f32 p_Predelay = 4);

		void setDistortionEffect(irrklang::ik_f32 p_Gain = -18, irrklang::ik_f32 p_Edge = 15, irrklang::ik_f32 p_PostEQCenterFrequency = 2400, 
			irrklang::ik_f32 p_PostEQBandwidth = 2400, irrklang::ik_f32 p_PreLowpassCutoff = 8000);

		void setEchoEffect(irrklang::ik_f32 p_WetDryMix = 50, irrklang::ik_f32 p_Feedback = 50, irrklang::ik_f32 p_LeftDelay = 500, 
			irrklang::ik_f32 p_RightDelay = 500, irrklang::ik_s32 p_PanDelay = 0);

		void setFlangerEffect(irrklang::ik_f32 p_WetDryMix = 50, irrklang::ik_f32 p_Depth = 100, irrklang::ik_f32 p_Feedback = -50, 
			irrklang::ik_f32 p_Frequency = 0.25f, 
			bool p_triangleWaveForm = true, irrklang::ik_f32 p_Delay = 2, irrklang::ik_s32 p_Phase = 0);

		void setGargleEffect(irrklang::ik_s32 p_rateHz = 20, bool p_sinusWaveForm = true);

		void set3DReverbEffect(irrklang::ik_s32 p_Room = -1000, irrklang::ik_s32 p_RoomHF = -100, irrklang::ik_f32 p_lRoomRolloffFactor = 0, 
			irrklang::ik_f32 p_decayTime = 1.49f, irrklang::ik_f32 p_lDecayHFRatio = 0.83f, irrklang::ik_s32 p_Reflections = -2602, irrklang::ik_f32 p_lReflectionsDelay = 0.007f, 
			irrklang::ik_s32 p_Reverb = 200, irrklang::ik_f32 p_lReverbDelay = 0.011f, irrklang::ik_f32 p_lDiffusion = 100.0f, irrklang::ik_f32 p_lDensity = 100.0f, irrklang::ik_f32 p_lHFReference = 5000.0f);

		void setParamEqEffect(irrklang::ik_f32 p_Center = 8000, irrklang::ik_f32 p_Bandwidth = 12, irrklang::ik_f32 p_Gain = 0);

		void setWavesReverbEffect(irrklang::ik_f32 p_InGain = 0, irrklang::ik_f32 p_ReverbMix = 0, irrklang::ik_f32 p_ReverbTime = 1000, irrklang::ik_f32 p_HighFreqRTRatio = 0.001f);

		void disableChorusEffect();
		void disableComppressorEffect();
		void disableDistortionEffect();
		void disableEchoEffect();
		void disableFlangerEffect();
		void disableGargleEffect();
		void disable3DReverbEffect();
		void disableParamEqEffect();
		void disableWavesReverbEffect();
	};
}