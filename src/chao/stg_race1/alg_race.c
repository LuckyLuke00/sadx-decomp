#include "decls.h"
extern struct NJS_POINT2 DAT_05b3e050;
extern struct NJS_POINT2 DAT_05b3e080;
extern void FUN_00441fb0();
extern void FUN_00711c20();
extern char objLandTableChaoRace[36];

// FUNCTION: SADX 0x00482130
void AL_RaceMasterDest(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	AL_GBAManagerSleep();
	AL_ReleaseTex(1);
	AlrReal_Destructor((struct AlrReal *)var1->value.l);
}

// STUB: SADX 0x00482160
void AL_RaceMasterExec(struct task *tp)
{
}

// FUNCTION: SADX 0x004821b0
void AL_RaceMaster(struct task *tp)
{
	struct taskwk *var1;
	var1 = tp->twp;
	tp->exec = AL_RaceMasterExec;
	tp->disp = (void (__cdecl *)(struct task *))FUN_007d21b0;
	tp->dest = AL_RaceMasterDest;
	ADV1_AL_InitChaoList();
	var1->value.ptr = FUN_004822c0();
	var1->mode = 1;
	MirenSoundSetStartBgmTask(0x13, 0xa);
	___njSetBackColor(0xff000000, 0xff000000, 0xff000000);
	ALW_Create();
	AlrReal_changeAct_for_Entrance((struct AlrReal *)var1->value.ptr);
	DAT_05b3e050.x = -1.0f;
	DAT_05b3e050.y = -5000.0f;
	DAT_05b3e080.y = -5000.0f;
	DAT_05b3e080.x = -1.0f;
	AL_LoadTex("OBJ_AL_RACE", &texlist_obj_al_race, 1);
	AL_LoadTex("AL_TOY", &texlist_al_toy, 1);
	FUN_00441fb0();
	FUN_00711c20();
}

// FUNCTION: SADX 0x00482260
void _alg_race_prolog()
{
	___OutputDebugString("ChaoStgRace _prolog begin.\n");
	CreateElementalTask(2, 2, AL_RaceMaster);
	LandChangeLandTable((struct _OBJ_LANDTABLE *)&objLandTableChaoRace);
	___OutputDebugString("ChaoStgRace _prolog end.\n");
	PauseDisable();
}

// FUNCTION: SADX 0x004822a0
void _alg_race_epilog()
{
	PauseEnable();
	___OutputDebugString("ChaoStgRace _epilog begin.\n");
	___OutputDebugString("ChaoStgRace _epilog end.\n");
}
