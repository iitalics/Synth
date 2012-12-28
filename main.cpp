#include "includes.h"
#include "APlay.h"
#include "SynthManager.h"
#include "OscPart.h"
#include "LFOPart.h"
#include "Wire.h"
#include "SynthReader.h"
#include <sstream>
#include <cmath>




#define DURATION 50

int main (int argc, char** args)
{
	fprintf(stderr, "\x1b[1m- started -\x1b[0m\n");
	
	
	
	SynthManager* synth = new SynthManager();
	
	SynthReader reader("\
MainOsc => Osc.sine\n\
 Amp: 0.5\
");
	
	if (reader.Load(synth) == LoadErrored)
	{
		fprintf(stderr, "\x1b[31mError while loading: \x1b[1m%s\x1b[0m\n", reader.GetError().c_str());
		return EXIT_FAILURE;
	}
	
	
	
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
