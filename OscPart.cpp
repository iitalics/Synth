#include "includes.h"
#include "OscPart.h"
#include "SynthManager.h"
#include <cmath>



#define GENERATE_SINE(x) (sinf((x) * (3.1415f * 2)))
static inline float GENERATE_SAW (float x)
{
	while (x > 1) x--;
	return 1 - (x * 2);
}
static inline float GENERATE_SQUARE (float x)
{
	return ((int)(x + 0.5f) > (int)x) ? 1 : -1;
}
#define GENERATE_NOISE(x) (((float)rand())/((float)RAND_MAX / 2) + 1)

float GENERATE_WAVE (OscWaveform wave, float phase)
{
	switch (wave)
	{
		case WaveformSine:
			return GENERATE_SINE(phase);
		case WaveformSaw:
			return GENERATE_SAW(phase);
		case WaveformSquare:
			return GENERATE_SQUARE(phase);
		case WaveformNoise:
			return GENERATE_NOISE(phase);
	}
	return 0;
}


OscPart::OscPart (OscWaveform _wave) : wave(_wave)
{
	PartSetting s[] = 
	{
		PartSetting("Freq", 0),
		PartSetting("Amp", 1),
		PartSetting("Pan", 0)
	};
	setSettings(s, 4);
}


template <typename T>
static inline T mathMin (T a, T b)
{
	return a < b ? a : b;
}
#define floatMin mathMin<float>

float OscPart::OutputLeft()
{
	// pan  =  -1         0           1
	// amp  =   1    1    1    0.5    0
	float amp = (floatMin(-Get("Pan"), 0) + 1) * Get("Amp");
	return GENERATE_WAVE(wave, Manager->Time * Get("Freq")) * amp;
}
float OscPart::OutputRight()
{
	// pan  =  -1         0           1
	// amp  =   0   0.5   1     1     1
	float amp = (floatMin(Get("Pan"), 0) + 1) * Get("Amp");
	return GENERATE_WAVE(wave, Manager->Time * Get("Freq")) * amp;
}
