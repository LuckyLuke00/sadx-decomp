#include "decls.h"

// FUNCTION: SADX 0x0047a770
void _al_odekake_epilog()
{
	___OutputDebugString("ChaoStgOdekake Epilog\n");
	((void (*)(void))FUN_007d21b0)();
	AlgKinderAdExit();
	PauseEnable();
}

// STUB: SADX 0x0047a790
void AL_OdekakeStageExecutor(struct task *tp)
{
}

// STUB: SADX 0x0047a7f0
void AL_OdekakeStageDestructor(struct task *tp)
{
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

// STUB: SADX 0x0047a9c0
void _al_odekake_prolog()
{
}
