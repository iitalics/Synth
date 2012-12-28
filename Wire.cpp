#include "includes.h"
#include "Wire.h"
#include "Part.h"

Wire::Wire(Part* _source, std::string _sourceAttr, Part* _dest, std::string _destAttr, float _amount)
	: source(_source)
{
	amount = _amount;
	
	if (_source == NULL)
	{
		source = NULL;
		sourceAttr = NULL;
	}
	else
	{
		sourceAttr = source->GetSetting(_sourceAttr);
		
		if (_source == _dest && _destAttr == _sourceAttr)
		{
			// well it looks like we have a problem here folks
			fprintf(stderr, "problem\n");
		}
		else
		{
			PartSetting* destAttr = _dest->GetSetting(_destAttr);
			if (destAttr != NULL)
				destAttr->AddWire(this);
		}
	
		std::cerr << "\x1b[34mwired " << _source->Name << "." << _sourceAttr << " -> " <<
				_dest->Name << "." << _destAttr << " " << (_amount * 100) << "%\x1b[0m" << std::endl;
	}
}
Wire::Wire(Wire& old)
{
	source = old.source;
	sourceAttr = old.sourceAttr;
	amount = old.amount;
}
Wire::Wire ()
{
	source = NULL;
	sourceAttr = NULL;
	amount = 0;
}


void Wire::Modify (float* what)
{
	if (!(sourceAttr == NULL || source == NULL))
	{
		*what += sourceAttr->Value() * amount;
	}
}
