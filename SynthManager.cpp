#include "includes.h"
#include "Part.h"
#include "SynthManager.h"




SynthManager::SynthManager ()
{
	parts.clear();
	Time = 0;
}

SynthManager::~SynthManager ()
{
	for (std::vector<Part*>::iterator i = parts.begin(); i != parts.end(); i++)
		delete *i;
}



void SynthManager::AddPart (Part* part)
{
	part->Manager = this;
	parts.push_back(part);
}

void SynthManager::GetOutput (float* left, float* right)
{
	*left = *right = 0;
	for (std::vector<Part*>::iterator i = parts.begin(); i != parts.end(); i++)
	{
		(*i)->Update();
		if ((*i)->GeneratesSound)
		{
			SoundPart* soundPart = (SoundPart*)*i;
			
			*left = soundPart->OutputLeft();
			*right = soundPart->OutputRight();
		}
	}
}
