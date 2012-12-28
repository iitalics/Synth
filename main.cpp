#include "includes.h"
#include "APlay.h"
#include "SynthManager.h"
#include "OscPart.h"
#include "LFOPart.h"
#include "Wire.h"
#include <sstream>
#include <cmath>




#define DURATION 50

int main (int argc, char** args)
{
	fprintf(stderr, "\x1b[1m- started -\x1b[0m\n");
	
	
	
	while (!ss.eof())
	{
		std::string line;
		std::getline(ss, line);
		std::cerr << "[" << line << "]" << std::endl;
	}
	
	
	SynthManager* synth = new SynthManager();
	
	OscPart* osc = new OscPart(WaveformSaw);
	LFOPart* lfo = new LFOPart(WaveformSine, 2);
	
	osc->SetBase("Freq", 440);
	osc->SetBase("Amp", 0.4f);
	
	Wire(lfo, "Output", osc, "Pan", 0.5f);
	
	synth->AddPart(osc);
	synth->AddPart(lfo);
	
	
	float left, right;
	
	for (int i = 0; i < APLAY_SAMPLERATE * DURATION; i++)
	{
		synth->Time = ((float)i) / APLAY_SAMPLERATE;
		
		synth->GetOutput(&left, &right);
		APlay::PlaySample(left, right);
	}
	
	delete synth;
	
	fprintf(stderr, "\x1b[1m- done -\x1b[0m\n");
	return EXIT_SUCCESS;
}
