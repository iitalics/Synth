#include "includes.h"
#include "Part.h"
#include "PartSetting.h"
#include "Wire.h"

PartSetting::PartSetting (std::string name, float base)
	: Name(name), BaseValue(base), numWires(0)
{
	wires = NULL;
}
PartSetting::PartSetting () : Name (""), BaseValue(0), numWires (0) {}

float PartSetting::Value ()
{
	if (numWires == 0)
		return BaseValue;
	
	float v = BaseValue;
	
	for (int i = 0; i < numWires; i++)
		wires[i]->Modify(&v);
		
	return v;
}

void PartSetting::AddWire (Wire* w)
{
	fprintf(stderr, "adding wire\n");
	if (numWires == 0)
	{
		wires = new Wire*[1];
		*wires = new Wire(*w);
	}
	else
	{
		Wire** newWires = new Wire*[numWires + 1];
		for (int i = 0; i < numWires; i++)
			newWires[i] = wires[i];
		
		newWires[numWires] = new Wire(*w);
		
		delete[] wires;
		wires = newWires;
	}
	numWires++;
}
void PartSetting::Dispose ()
{
	if (numWires > 0)
	{
		for (int i = 0; i < numWires; i++)
			delete wires[i];
		delete[] wires;
	}
}


