#include "decls.h"
void AL_FaceReturnDefaultEye(struct task *tp);
void AL_FaceReturnDefaultMouth(struct task *tp);
void AL_FaceEyeLidControl(struct task *tp);
short FUN_00457a80(struct task *param_1);
void AL_MatChangeObjectTexture(struct al_object *pObject, unsigned short TexId);
short FUN_00457a80(struct task *param_1);

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

#pragma optimize("", off)
// STUB: SADX 0x00457a90
void AL_FaceSetEye(struct task *tp, enum eAL_EYE_NUM EyeNum, long timer)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x00457b90
void AL_FaceSetMouth(struct task *tp, enum eAL_MOUTH_NUM MouthNum, long timer)
{
}
#pragma optimize("", on)

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

// FUNCTION: SADX 0x00457e20
void AL_FaceChangeMouth(struct task *tp, enum eAL_MOUTH_NUM MouthNum)
{
	AL_FaceSetMouth(tp, MouthNum, -1);
}

// FUNCTION: SADX 0x00457e40
void AL_FaceReturnDefaultEye(struct task *tp)
{
	AL_FaceChangeEye(tp, (enum eAL_EYE_NUM)(*(short *)((char *)tp->twp + 0x6a8)));
}

// FUNCTION: SADX 0x00457e60
void AL_FaceReturnDefaultMouth(struct task *tp)
{
	AL_FaceChangeMouth(tp, (enum eAL_MOUTH_NUM)(*(short *)((char *)tp->twp + 0x6b2)));
}

// FUNCTION: SADX 0x00458070
void AL_FaceControl(struct task *tp)
{
	struct taskwk *var1;
	struct anywk *var2;
	int var3;
	unsigned char var4;
	short var5;

	var1 = tp->twp;
	var3 = *(int *)((char *)var1 + 0x6a0);
	if (var3 > 0)
	{
		*(int *)((char *)var1 + 0x6a0) = var3 - 1;
	}
	else if (var3 != -1 && var3 == 0)
	{
		AL_FaceReturnDefaultEye(tp);
	}
	var3 = *(int *)((char *)var1 + 0x6ac);
	if (var3 > 0)
	{
		*(int *)((char *)var1 + 0x6ac) = var3 - 1;
	}
	else if (var3 != -1 && var3 == 0)
	{
		AL_FaceReturnDefaultMouth(tp);
	}
	AL_FaceEyeLidControl(tp);
	var2 = *(struct anywk **)((char *)tp->twp + 0x6c);
	var4 = *(unsigned char *)((char *)var2 + 0x80);
	if (var4 < 0x14 || var4 > 0x16)
	{
		var5 = FUN_00457a80(tp);
		if (var5 == 9 && *(int *)((char *)var1 + 0x6ec) > 0x3c00)
		{
			AL_MatChangeObjectTexture(*(struct al_object **)((char *)var1 + 0x6c8), 0);
			AL_MatChangeObjectTexture(*(struct al_object **)((char *)var1 + 0x6cc), 0);
		}
	}
}
