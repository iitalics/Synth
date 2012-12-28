#pragma once



class Part;
class PartSetting;

class Wire
{
public:
	Wire(Part* _source, std::string _sourceAttr, Part* _dest, std::string _destAttr, float _amount = 1);
	Wire(Wire& old);
	Wire();
	
	void Modify (float* what);
	
protected:
	float amount;
	Part* source;
	PartSetting* sourceAttr;
};
