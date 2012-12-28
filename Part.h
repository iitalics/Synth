#pragma once

#include "PartSetting.h"


class SynthManager;
class Part
{
public:
	static float DefaultValue;
	
	
	Part();
	virtual ~Part();
	
	
	PartSetting* GetSetting (std::string name);
	float Get (std::string settingName);
	void SetBase (std::string setting, float base);
	virtual void Update ();
	
	std::string Name;
	bool GeneratesSound;
	
	SynthManager* Manager;
	
protected:
	int numSettings;
	PartSetting* settings;
	
	void setSettings (std::vector<PartSetting> _settings);
	void setSettings (PartSetting* settings, int len);
};

class SoundPart : public Part
{
public:
	SoundPart();
	virtual float OutputLeft ();
	virtual float OutputRight ();
};
