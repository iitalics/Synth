#include "includes.h"
#include "SynthReader.h"

#include "Part.h"
#include "OscPart.h"
#include "LFOPart.h"
#include "SynthManager.h"



#define COMMENT_SEQ "#"
#define CREATE_SEQ "=>"
#define ATTR_SEQ ":"
#define WIRE_SEQ "->"




static inline std::string strip (std::string s)
{
	if (s.size() == 0) return s;
	int i = 0; int len = s.size();
	while (i < len && std::isspace(s[i])) i++;
	if (i >= len) return "";
	while (std::isspace(s[len - 1])) len--;
	return s.substr(i, len - i);
}



SynthReader::SynthReader (std::fstream file) : ss()
{
	std::string line;
	while (!file.eof())
	{
		std::getline(file, line);
		ss << line << std::endl;
	}
	init();
}
SynthReader::SynthReader (std::string data) : ss(data)
{
	init();
}

void SynthReader::init ()
{
	inuse = true;
	currentPart = NULL;
	target = NULL;
}

bool SynthReader::Load (SynthManager* _target)
{
	if (!inuse)
	{
		// error
	}
	
	target = _target;
	errored = false;
	
	std::string line;
	while (!ss.eof() && !errored)
	{
		std::getline(ss, line);
		if (line.find(COMMENT_SEQ) != std::string::npos) line = line.substr(line.find(COMMENT_SEQ) + 1);
		
		line = strip(line);
		if (line.size() == 0) continue;
		processLine(line);
	}
	inuse = false;
	
	return errored;
}
std::string SynthReader::GetError ()
{
	if (!errored) return "";
	return errorMessage;
}
void SynthReader::die (std::string x)
{
	errored = true;
	errorMessage = x;
}

static Part* CreatePart (std::string type);


static inline void beforeAfter (std::string& a, std::string& b, std::string seq, std::string f)
{
	a = strip(seq.substr(0, seq.find(f)));
	b = strip(seq.substr(seq.find(f) + f.size()));
}

void SynthReader::processLine (std::string line)
{
	if (line.find(CREATE_SEQ) != std::string::npos)
	{
		std::string name, type;
		beforeAfter(name, type, line, CREATE_SEQ);
		
		if (name.size() == 0 || type.size() == 0)
		{
			die("Invalid syntax");
			return;
		}
		
		Part* p = CreatePart(type);
		if (p == NULL)
		{
			die("Invalid part type '" + type + "'");
			return;
		}
		p->Name = name;
		target->AddPart(p);
		currentPart = p;
	}
	else if (line.find(ATTR_SEQ) != std::string::npos)
	{
		if (currentPart == NULL)
		{
			die("Cannot apply setting to undefined part");
			return;
		}
		
		std::string attr, value;
		beforeAfter(attr, value, line, ATTR_SEQ);
		
		if (attr.size() == 0 || value.size() == 0)
		{
			die("Invalid syntax");
			return;
		}
		
		if (std::isdigit(value[0]) || value[0] == '-')
		{
			currentPart->SetBase(attr, atof(value.c_str()));
		}
		else
		{
			die("String/token values not supported");
			return;
		}
	}
	else if (line.find(WIRE_SEQ) != std::string::npos)
	{
		
	}
}


static inline OscWaveform getWave (std::string s)
{
	if (s == "sine")   return WaveformSine;
	if (s == "saw")    return WaveformSaw;
	if (s == "square") return WaveformSquare;
	if (s == "noise")  return WaveformNoise;
	return WaveformInvalid;
}
static Part* CreatePart (std::string type)
{
	if (type.substr(0, 4) == "LFO.")
	{
		OscWaveform wave = getWave(type.substr(4));
		if (wave < 0) return NULL;
		return new LFOPart(wave);
	}
	else if (type.substr(0, 4) == "Osc.")
	{
		OscWaveform wave = getWave(type.substr(4));
		if (wave < 0) return NULL;
		return new OscPart(wave);
	}
	
	
	return NULL;
}
