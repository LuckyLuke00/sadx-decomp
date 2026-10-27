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

// FUNCTION: SADX 0x00476b30
void AL_Garden00MasterExecutor(struct task *tp)
{
	struct taskwk *var1;

	LoopTaskC(tp);
	var1 = DAT_05baf368[0];
	if (var1->pos.z < -160.0f)
	{
		AL_ChangeStageLater((enum eCHAO_STAGE_NUMBER)2);
	}
	if (var1->pos.z > 160.0f)
	{
		if (var1->pos.x < -40.0f)
		{
			AL_ChangeStageLater((enum eCHAO_STAGE_NUMBER)7);
		}
		else
		{
			SetEntranceNumber(4);
			AL_ExitToStage(0x1a, 4);
		}
	}
	if (var1->pos.y > 56.0)
	{
		var1->pos.y = 56.0f;
	}
	if (var1->pos.y < -16.0f)
	{
		var1->pos.x = 0.0f;
		var1->pos.y = 0.0f;
		var1->pos.z = 0.0f;
	}
}

// FUNCTION: SADX 0x00476be0
void AL_Garden00MasterDestructor(struct task *tp)
{
	FUN_004b6520((int)&texlist_al_dx_tex_xybutton);
	BGM_Stop();
	Serif_Stop();
	AL_MinimalExit();
	AL_ReleaseTex(1);
	syFree((void *)DAT_05b3304c);
	FUN_0044db20();
	AL_ReleaseModule((enum EChaoModuleEntry)2);
}

// FUNCTION: SADX 0x00476fd0
void _alg_garden00_ss_prolog()
{
	___OutputDebugString("ChaoStgGarden00SS Prolog begin\n");
	CreateElementalTask(2, 2, AL_Garden00Master);
	LandChangeLandTable((struct _OBJ_LANDTABLE *)objLandTableGarden00);
	___OutputDebugString("ChaoStgGarden00SS Prolog end\n");
}
