#include "decls.h"
extern long DAT_060cae34;
extern float DAT_060cae58;
extern float DAT_060cae5c;
extern float DAT_060cae60;
extern float DAT_060caea0;
extern float DAT_060caea4;
extern float DAT_060caea8;
extern int DAT_060cb31c;

// FUNCTION: SADX 0x00714c00
long ALCAM_SetLookingFlag(long flag)
{
	return DAT_060cae34 = flag;
}

// STUB: SADX 0x00714c10
long AL_NormalCameraCheckSwingingTree()
{
	return (long)0;
}

// FUNCTION: SADX 0x007151f0
void AL_NormalCameraDestructor(struct task *tp)
{
	DAT_060cb31c = 0;
	if (tp->mwp != 0)
	{
		syFree(tp->mwp);
		tp->mwp = 0;
	}
}

// FUNCTION: SADX 0x00715330
void ALCAM_CameraManagerExecutor(struct task *tp)
{
	tp->twp->wtimer++;
}

// FUNCTION: SADX 0x00715340
void ALCAM_ClearCameraWork()
{
	DAT_060cae58 = 0.0;
	DAT_060cae5c = 0.0;
	DAT_060cae60 = 0.0;
	DAT_060caea0 = 0.0;
	DAT_060caea4 = 0.0;
	DAT_060caea8 = -1.0;
}

// STUB: SADX 0x00715370
void ALCAM_ModeSystem(struct _OBJ_CAMERAPARAM *pParam)
{
}

// STUB: SADX 0x00715410
void ALCAM_CreateCameraManager()
{
}
