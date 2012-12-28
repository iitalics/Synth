#include "includes.h"
#include "Part.h"



float Part::DefaultValue = 0;

Part::Part ()
{
	settings = NULL;
}
Part::~Part ()
{
	if (settings != NULL)
	{
		for (int i = 0; i < numSettings; i++)
			settings[i].Dispose();
		delete[] settings;
	}
}
PartSetting* Part::GetSetting (std::string name)
{
	if (settings == NULL)
		return NULL;
	for (int i = 0; i < numSettings; i++)
	{
		PartSetting* s = settings + i;
		if (s->Name == name)
			return s;
	}
	return NULL;
}
float Part::Get (std::string settingName)
{
	if (settings == NULL)
		return DefaultValue;
	
	for (int i = 0; i < numSettings; i++)
	{
		PartSetting* s = settings + i;
		if (s->Name == settingName)
			return s->Value();
	}
	return DefaultValue;
}
void Part::SetBase (std::string settingName, float base)
{
	if (settings == NULL)
		return;
	
	for (int i = 0; i < numSettings; i++)
	{
		PartSetting* s = settings + i;
		if (s->Name == settingName)
		{
			s->BaseValue = base;
			break;
		}
	}
}

void Part::setSettings (std::vector<PartSetting> _settings)
{
	if (settings != NULL) delete[] settings;
	
	numSettings = _settings.size();
	settings = new PartSetting[numSettings];
	
	for (int i = 0; i < numSettings; i++)
		settings[i] = _settings[i];
}
void Part::setSettings (PartSetting* _settings, int len)
{
	if (settings != NULL) delete[] settings;
	
	numSettings = len;
	settings = new PartSetting[numSettings];
	
	for (int i = 0; i < len; i++)
		settings[i] = _settings[i];
}
void Part::Update () { }



SoundPart::SoundPart ()
{
	GeneratesSound = true;
}
float SoundPart::OutputLeft () { return 0; }
float SoundPart::OutputRight () { return OutputLeft(); }
