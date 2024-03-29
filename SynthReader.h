#pragma once

#include <fstream>
#include <sstream>



enum LoadStatus
{
	LoadErrored = 0,
	LoadSuccess = 1
};

class SynthManager;
class Part;


class SynthReader
{
public:
	SynthReader (std::fstream file);
	SynthReader (std::string data);
	~SynthReader ();
	
	LoadStatus Load (SynthManager* target);
	std::string GetError ();
private:
	bool errored;
	std::string errorMessage;
	
	void die (std::string x);
	
	void init ();
	bool inuse;
	void processLine(std::string line);
	std::stringstream ss;
	
	
	SynthManager* target;
	Part* currentPart;
};
