#include "decls.h"
extern char objLandTableGarden01[36];

// STUB: SADX 0x00479ae0
void AL_G01_SeaScrollExec(struct task *tp)
{
}

// FUNCTION: SADX 0x00479b30
void FUN_00479b30()
{
	CreateElementalTask(8, 6, AL_G01_SeaScrollExec);
}

// FUNCTION: SADX 0x00479b50
void _alg_garden01_ec_epilog()
{
	___OutputDebugString("ChaoStgGarden01EC Epilog begin\n");
	___OutputDebugString("ChaoStgGarden01EC Epilog end\n");
}

// FUNCTION: SADX 0x00479b70
void AL_Garden01MasterExecutor(struct task *tp)
{
}

// STUB: SADX 0x00479bb0
void AL_Garden01MasterDestructor(struct task *tp)
{
}

// FUNCTION: SADX 0x00479df0
void _alg_garden01_ec_prolog()
{
	___OutputDebugString("ChaoStgGarden01EC Prolog begin\n");
	CreateElementalTask(2, 2, AL_Garden01Master);
	LandChangeLandTable((struct _OBJ_LANDTABLE *)&objLandTableGarden01);
	___OutputDebugString("ChaoStgGarden01EC Prolog end\n");
}
