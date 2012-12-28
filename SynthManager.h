#pragma once


class Part;

class SynthManager;
class SynthManager
{
public:
	SynthManager();
	~SynthManager();
	
	void AddPart (Part* part);
	void GetOutput (float* left, float* right);
	
	float Time;
protected:
	
	
	std::vector<Part*> parts;
};
