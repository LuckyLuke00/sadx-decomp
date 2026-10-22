#include "decls.h"
extern struct NJS_TEXLIST texlist_al_dx_tex_xybutton;
void FUN_004b6520(int param_1);
void BGM_Stop();
void Serif_Stop();
void AL_ReleaseMessageTable();
void AL_MinimalExit();
void AL_ReleaseTex(unsigned short lev);
void FUN_0044db20(struct task *);

// FUNCTION: SADX 0x00479e20
void _alg_garden02_mr_epilog()
{
	___OutputDebugString("ChaoStgGarden02MR Epilog begin\n");
	AL_ReleaseModule((enum EChaoModuleEntry)2);
	___OutputDebugString("ChaoStgGarden02MR Epilog end\n");
}

// FUNCTION: SADX 0x00479ed0
void AL_Garden02MasterDisplayer(struct task *tp)
{
	DrawSaltWater3D_39();
}

// FUNCTION: SADX 0x00479ee0
void AL_Garden02MasterDestructor(struct task *tp)
{
	FUN_004b6520((int)&texlist_al_dx_tex_xybutton);
	BGM_Stop();
	Serif_Stop();
	AL_ReleaseMessageTable();
	AL_MinimalExit();
	AL_ReleaseTex(1);
	FUN_0044db20(tp);
}
