#include "decls.h"

// FUNCTION: SADX 0x00421370
void njDrawObject(struct obj *obj)
{
	_njBeginModel();
	_njTransformObject(obj, _njDirectDrawModel);
	_njEndModel();
}

// FUNCTION: SADX 0x00421390
void njDrawModel(struct NJS_MODEL *model)
{
	_njBeginModel();
	_njDirectDrawModel(model);
	_njEndModel();
}
