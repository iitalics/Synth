#pragma once


class Wire;

class PartSetting
{
public:
	PartSetting (std::string name, float base = 0);
	PartSetting ();
	
	float Value();
	void AddWire (Wire* wire);
	
	std::string Name;
	float BaseValue;
	
	void Dispose();
	
protected:
	int numWires;
	Wire** wires;
};



