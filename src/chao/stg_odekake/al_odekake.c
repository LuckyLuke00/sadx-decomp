#include "decls.h"
extern struct NJS_TEXLIST texlist_al_odekake_menu;
extern struct taskwk *DAT_05baf368[8];
extern int DAT_05b33088;

// STUB: SADX 0x0047a770
void _al_odekake_epilog()
{
}

// FUNCTION: SADX 0x0047a790
void AL_OdekakeStageExecutor(struct task *tp)
{
	struct taskwk *var1;

	var1 = DAT_05baf368[0];
	var1->pos.x = 0.0f;
	var1->pos.y = 100.0f;
	var1->pos.z = 0.0f;
	PauseDisable();
	if (DAT_05b33088 != 0)
	{
		___OutputDebugString("another: loading done.\n");
		if (AL_CheckSaveDataCrc2(AL_GetAnotherGardenInfo()) != 0)
		{
			___OutputDebugString("another: crc ok.\n");
			AL_SetAnotherGardenLoaded();
			DAT_05b33088 = 0;
		}
	}
}

// STUB: SADX 0x0047a7f0
void AL_OdekakeStageDestructor(struct task *tp)
{
	FUN_004b6520((int)&texlist_al_odekake_menu);
	BGM_Stop();
	Serif_Stop();
	AlMsgSelectExit();
	AlMsgWarnExit();
	((void (*)(void))FUN_0044db20)();
	AL_ReleaseMessageTable();
	AL_ReleaseTex(1);
}

// FUNCTION: SADX 0x0047a830
void CameraFunc(struct _OBJ_CAMERAPARAM *pParam)
{
	if (*(int *)((char *)pParam + 0x20) == 0)
	{
		*(float *)((char *)camcont_wp + 0xc) = 0.0f;
		*(float *)((char *)camcont_wp + 0x10) = 0.0f;
		*(float *)((char *)camcont_wp + 0x14) = 0.0f;
		*(float *)((char *)camcont_wp + 0x18) = 0.0f;
		*(float *)((char *)camcont_wp + 0x1c) = 0.0f;
		*(float *)((char *)camcont_wp + 0x20) = -1.0f;
		*(int *)((char *)camcont_wp + 0x24) = 0;
		*(int *)((char *)camcont_wp + 0x28) = 0;
		SetViewAngle(0x31c7);
	}
}

// FUNCTION: SADX 0x0047a8a0
void FUN_0047a8a0()
{
	CameraSetCollisionCameraFunc(CameraFunc, 1, 2);
}

// STUB: SADX 0x0047a8c0
void AL_OdekakeStage(struct task *tp)
{
}

// STUB: SADX 0x0047a9c0
void _al_odekake_prolog()
{
}
