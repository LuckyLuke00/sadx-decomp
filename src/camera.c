#include "decls.h"
extern int DAT_05b42a74;
extern int DAT_05b42860;
void FUN_004bee10(void);
void SetAdjustMode(long AdjustType);
extern struct _CameraSystemWork *pCameraSystemWork;
extern short DAT_05b42998;
extern int DAT_05b42894;
extern int DAT_05b42974;
extern int DAT_05b428e8;
extern unsigned long DAT_05cda1b0;
extern struct taskwk *DAT_05b42a7c;
extern int DAT_05b42a80;
extern int DAT_05b42a78;
extern int DAT_05b42994;
extern unsigned long DAT_05b429a0;
extern int DAT_05b42968;

extern int DAT_05b42978;

// FUNCTION: SADX 0x004bade0
void SetStartCameraMode(signed char mode)
{
	DAT_05b42978 = mode;
}

// FUNCTION: SADX 0x004badf0
void SetDefaultNormalCameraMode(signed char mode, signed char adjust)
{
	DAT_05b42a78 = mode;
	DAT_05b42994 = adjust;
}

// FUNCTION: SADX 0x004bae10
long GetViewAngle()
{
	return DAT_05b42968;
}

// FUNCTION: SADX 0x004bafb0
void FUN_004bafb0(void)
{
	DAT_05b42968 = 0x31c7;
	___njSetPerspective(DAT_05b42968);
	DAT_05b42a80 = DAT_05b42968;
}

// FUNCTION: SADX 0x004bb090
void CameraEnd(struct task *pTask)
{
	DAT_05b42a7c = 0;
}

// FUNCTION: SADX 0x004bb0a0
void CameraPause(struct task *pTask)
{
	struct taskwk *local_8;
	local_8 = pTask->twp;
	CameraViewSet(local_8);
}

// FUNCTION: SADX 0x004bb0c0
void AddCameraStage(short ssStep)
{
	if (ChkGameMode() == 0)
	{
		return;
	}
	DAT_05b42998 += ssStep;
	DAT_05b42894 = ((unsigned long *)&DAT_05cda1b0)[DAT_05b42998];
	DAT_05b42974 = ((unsigned long *)&DAT_05cda1b0)[DAT_05b42998] + 0x40;
	cameraModeInit();
	DAT_05b429a0 = 0;
	DAT_05b428e8 = 0;
}

// FUNCTION: SADX 0x004bbcf0
void CameraReleaseCollisionCamera()
{
	if (*(signed char *)((char *)pCameraSystemWork + 6) == 0x40 || *(signed char *)((char *)pCameraSystemWork + 6) == 0x4c)
	{
		FUN_004bee10();
		SetAdjustMode(5);
	}
}

// FUNCTION: SADX 0x004bc160
void InitFreeCamera()
{
	DAT_05b42a74 |= 0x8000000c;
	DAT_05b42860 = 0x3c;
}

// FUNCTION: SADX 0x004bc180
void ResetFreeCamera()
{
	DAT_05b42a74 = DAT_05b42a74 | 0x80000008;
	DAT_05b42860 = 0x3c;
}

// FUNCTION: SADX 0x004beff0
unsigned long GetCameraTimer()
{
	return DAT_05b429a0;
}
