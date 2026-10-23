#include "decls.h"
extern char objLandTableChaoEntrance[36];
extern struct NJS_TEXLIST texlist_al_ent_common_tex;
void FUN_004b6520(int param_1);
void BGM_Stop();
void Serif_Stop();
void AL_GBAManagerSleep();
void AL_ReleaseTex(unsigned short lev);

// FUNCTION: SADX 0x00471cd0
void AL_EntranceMasterDest(struct task *tp)
{
	FUN_004b6520((int)&texlist_al_ent_common_tex);
	BGM_Stop();
	Serif_Stop();
	AL_GBAManagerSleep();
	AL_ReleaseTex(1);
}

// STUB: SADX 0x00471d00
void AL_EntranceMasterExec(struct task *tp)
{
}

// FUNCTION: SADX 0x00471ee0
void _alg_entrance_prolog()
{
	___OutputDebugString("ChaoStgEntrance _prolog begin.\n");
	CreateElementalTask(2, 5, AL_EntranceMaster);
	LandChangeLandTable((struct _OBJ_LANDTABLE *)&objLandTableChaoEntrance);
	___OutputDebugString("ChaoStgEntrance _prolog end.\n");
}

// FUNCTION: SADX 0x00471f10
void _alg_entrance_epilog()
{
	PauseEnable();
	___OutputDebugString("ChaoStgEntrance _epilog begin.\n");
	___OutputDebugString("ChaoStgEntrance _epilog end.\n");
}
