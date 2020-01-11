#pragma once
#include "SoundResources.h"
/*#include "Fmod/fmod.h"
#include "Fmod/fmod.hpp"
#include "Fmod/fmod_codec.h"
#include "Fmod/fmod_common.h"
#include "Fmod/fmod_dsp.h"
#include "Fmod/fmod_dsp_effects.h"
#include "Fmod/fmod_errors.h"
#include "Fmod/fmod_output.h"
#include "Fmod/fmod_uwp.h"*/
#include "Fmod/fmod_studio.hpp"
#include "Fmod/fmod.hpp"


class SoundManager
{
public:
	SoundResources* sr;
	GLuint soundId;
	FMOD::Sound* sound;

	SoundManager();
	~SoundManager();
};

