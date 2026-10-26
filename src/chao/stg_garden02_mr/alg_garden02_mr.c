#include "decls.h"
extern struct taskwk *DAT_05baf368[8];
extern struct NJS_TEXLIST texlist_al_dx_tex_xybutton;
void FUN_004b6520(int param_1);
void BGM_Stop();
void Serif_Stop();
void AL_ReleaseMessageTable();
void AL_MinimalExit();
void AL_ReleaseTex(unsigned short lev);
void FUN_0044db20(void);

// FUNCTION: SADX 0x00479e20
void _alg_garden02_mr_epilog()
{
	___OutputDebugString("ChaoStgGarden02MR Epilog begin\n");
	AL_ReleaseModule((enum EChaoModuleEntry)2);
	___OutputDebugString("ChaoStgGarden02MR Epilog end\n");
}

// FUNCTION: SADX 0x00479e40
void AL_Garden02MasterExecutor(struct task *tp)
{
	short *var1;

	LoopTaskC(tp);
	var1 = (short *)DAT_05baf368[0];
	if (((float *)var1)[8] < 10.0f && ((float *)var1)[10] < -150.0f)
	{
		SetEntranceNumber(4);
		AL_ExitToStage(0x21, 0);
	}
	if (((float *)var1)[9] > 200.0)
	{
		((float *)var1)[9] = 200.0f;
	}
	if (((float *)var1)[9] < -40.0f)
	{
		((float *)var1)[8] = 0.0f;
		((float *)var1)[9] = 0.0f;
		((float *)var1)[10] = 0.0f;
	}
	DrawSaltWater3D_39();
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
	FUN_0044db20();
}

// STUB: SADX 0x0047a120
void _alg_garden02_mr_prolog()
{
}
