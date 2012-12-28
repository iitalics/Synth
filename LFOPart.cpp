#include "includes.h"
#include "LFOPart.h"
#include "SynthManager.h"




LFOPart::LFOPart (OscWaveform _wave, int speed)
{
	PartSetting s[] =
	{
		PartSetting("Output", 0),
		PartSetting("Speed", speed)
	};
	setSettings(s, 2);
	
	waveform = _wave;
}



void LFOPart::Update ()
{
	
	float q = GENERATE_WAVE(waveform, Manager->Time * Get("Speed"));
	settings[0].BaseValue = q;
}
