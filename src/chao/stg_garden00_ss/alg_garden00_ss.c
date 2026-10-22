#include "decls.h"
extern char objLandTableGarden00[36];
extern const unsigned long *DAT_05b3304c;

// FUNCTION: SADX 0x00476b00
const unsigned long *AL_G00_MsgListGet()
{
	return DAT_05b3304c;
}

// FUNCTION: SADX 0x00476b10
void _alg_garden00_ss_epilog()
{
	___OutputDebugString("ChaoStgGarden00SS Epilog begin\n");
	___OutputDebugString("ChaoStgGarden00SS Epilog end\n");
}

// STUB: SADX 0x00476be0
void AL_Garden00MasterDestructor(struct task *tp)
{
}

// FUNCTION: SADX 0x00476fd0
void _alg_garden00_ss_prolog()
{
	___OutputDebugString("ChaoStgGarden00SS Prolog begin\n");
	CreateElementalTask(2, 2, AL_Garden00Master);
	LandChangeLandTable((struct _OBJ_LANDTABLE *)objLandTableGarden00);
	___OutputDebugString("ChaoStgGarden00SS Prolog end\n");
}
