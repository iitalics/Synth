#include "includes.h"
#include "SynthReader.h"


static inline std::string strip (std::string s)
{
	if (s.size() == 0) return s;
	
	int i, len;
	
	i = 0;
	while (std::isspace(s[i])) i++;
	
	len = s.size();
	if (i == len) return "";
	while (std::isspace(s[len - 1])) len--;
	
	return s.substr(i, len - i);
}


SynthReader::SynthReader (std::fstream file)
{
	
}
SynthReader::SynthReader (std::string data)
{
	std::stringstream* ss = new std::stringstream(data);
	
	stream = (std::istream)ss;
}


void SynthReader::Load (SynthManager* target)
{
	
}


std::string readLine()
{
	std::string line;
	std::getline(stream, line);
	return line;
}
