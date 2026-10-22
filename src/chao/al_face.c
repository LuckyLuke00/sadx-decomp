#include "decls.h"

// FUNCTION: SADX 0x00457a50
long AL_FaceEyelidGetCloseAng(struct task *tp)
{
	return *(long *)((char *)tp->twp + 0x6ec) + *(long *)((char *)tp->twp + 0x6dc) - 0x4000;
}

// FUNCTION: SADX 0x00457a70
long AL_FaceEyelidGetSlopeAng(struct task *tp)
{
	return *(long *)((char *)tp->twp + 0x6f8);
}

// FUNCTION: SADX 0x00457a80
short FUN_00457a80(struct task *param_1)
{
	return *(short *)((char *)param_1->twp + 0x6a6);
}

// STUB: SADX 0x00457b90
void AL_FaceSetMouth(struct task *tp, enum eAL_MOUTH_NUM MouthNum, long timer)
{
}

// FUNCTION: SADX 0x00457bf0
short AL_FaceGetMouthDefaultNum(struct task *tp)
{
	return *(short *)((char *)tp->twp + 0x6b2);
}

// FUNCTION: SADX 0x00457e00
void AL_FaceChangeEye(struct task *tp, enum eAL_EYE_NUM EyeNum)
{
	AL_FaceSetEye(tp, EyeNum, -1);
}

// STUB: SADX 0x00457e20
void AL_FaceChangeMouth(struct task *tp, enum eAL_MOUTH_NUM MouthNum)
{
}

// STUB: SADX 0x00457e40
void AL_FaceReturnDefaultEye(struct task *tp)
{
}

// STUB: SADX 0x00457e60
void AL_FaceReturnDefaultMouth(struct task *tp)
{
}
