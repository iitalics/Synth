#include "includes.h"
#include "APlay.h"

#if   APLAY_BITS == 8
#define APLAY__TYPE char
#elif APLAY_BITS == 16
#define APLAY__TYPE short
#else//          == 32
#define APLAY__TYPE int
#endif

#ifdef APLAY_SIGNED
#define APLAY_TYPE signed APLAY__TYPE
#else
#define APLAY_TYPE unsigned APLAY__TYPE
#endif


namespace APlay
{

	void ProcessSound (float sample, char* output)
	{
		APLAY_TYPE value = (
#ifndef APLAY_SIGNED
1 +
#endif
			sample
			) * (1 << (APLAY_BITS - 1));
		
		*((APLAY_TYPE*)output) = value;
	}
	void PlaySample (float left, float right)
	{
		char output[APLAY_BITS / 4];
		
		ProcessSound(left, output);
		ProcessSound(right, output + (APLAY_BITS / 8));
		
#if   APLAY_BITS == 8
		putchar(output[0]); // left
		putchar(output[1]);
#elif APLAY_BITS == 16
		putchar(output[0]); // left
		putchar(output[1]);
		putchar(output[2]); // right
		putchar(output[3]);
#else
		putchar(output[0]); // left
		putchar(output[1]);
		putchar(output[2]);
		putchar(output[3]);
		putchar(output[4]); // right
		putchar(output[5]);
		putchar(output[6]);
		putchar(output[7]);
#endif
		fflush(stdout);
	}

};
