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
	
	
	
	SynthManager* synth = new SynthManager();
	
	
	
	
	
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
