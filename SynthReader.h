#pragma once

#include <fstream>

			class SynthManager;



class SynthReader
{
public:
	SynthReader (std::fstream file);
	SynthReader (std::string data);
	~SynthReader ();
	
	void Load (SynthManager* target);
private:
	bool usingStreamstream;
	
	std::istream* stream;
	
	std::string readLine();
	
	
	SynthManager* target;
};
