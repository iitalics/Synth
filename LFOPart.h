#pragma once

#include "OscPart.h"

class LFOPart : public Part
{
public:
	LFOPart(OscWaveform wave = WaveformSine, int speed = 1);
	
	virtual void Update ();
	
protected:
	OscWaveform waveform;
};
