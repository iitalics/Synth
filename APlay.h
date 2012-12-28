#pragma once



#define APLAY_SAMPLERATE 44100
#define APLAY_BITS 16
#define APLAY_SIGNED


namespace APlay
{

	void ProcessSound (float sample, char* output);
	void PlaySample (float left, float right);

};
