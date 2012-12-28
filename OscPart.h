#pragma once

#include "Part.h"


enum OscWaveform
{
	WaveformSine   = 1,
	WaveformSaw    = 2,
	WaveformSquare = 3,
	WaveformNoise  = 4
};


class OscPart : public SoundPart
{
public:
	OscPart(OscWaveform _wave);
	
	virtual float OutputLeft();
	virtual float OutputRight();
protected:
	OscWaveform wave;
};


float GENERATE_WAVE (OscWaveform wave, float phase);
