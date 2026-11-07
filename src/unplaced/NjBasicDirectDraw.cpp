#include "decls.h"

// FUNCTION: SADX 0x00421370
void njDrawObject(NJS_OBJECT *param_1)
{
	_njBeginModel();
	_njTransformObject(param_1, _njDirectDrawModel);
	_njEndModel();
}

// FUNCTION: SADX 0x00421390
void njDrawModel(NJS_MODEL *param_1)
{
	_njBeginModel();
	_njDirectDrawModel(param_1);
	_njEndModel();
}
