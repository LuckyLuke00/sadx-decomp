#include "decls.h"
void njPrintD(int, int, int);
void AL__EditCancelMode(struct task *tp);
extern signed char DAT_05b92ea0;
extern unsigned char DAT_05b92e4c;

// FUNCTION: SADX 0x004443f0
void AL_EnvEdit(struct task *tp)
{
	struct task *var1;
	struct taskwk *var2;
	void *var3;

	var2 = tp->twp;
	var1 = ALW_GetTaskCount(0, *(unsigned short *)((char *)var2 + 0x14));
	var3 = *(void **)((char *)var1->twp + 0x6c);
	if (DAT_05b92e4c & 2)
	{
		AL__EditCancelMode(tp);
	}
	if (DAT_05b92e4c & 0x40)
	{
		if (*(unsigned char *)((char *)var3 + 0xda) != 0)
		{
			*(unsigned char *)((char *)var3 + 0xda) = *(unsigned char *)((char *)var3 + 0xda) - 1;
		}
		else
		{
			*(unsigned char *)((char *)var3 + 0xda) = 0x10;
		}
	}
	if (DAT_05b92e4c & 0x80)
	{
		if (*(unsigned char *)((char *)var3 + 0xda) < 0x10)
		{
			*(unsigned char *)((char *)var3 + 0xda) = *(unsigned char *)((char *)var3 + 0xda) + 1;
		}
		else
		{
			*(unsigned char *)((char *)var3 + 0xda) = 0;
		}
	}
	njPrintD(0x1a000a, *(unsigned char *)((char *)var3 + 0xda), 2);
	if (*(unsigned char *)((char *)var3 + 0xda) == 0)
	{
		AL_MatDisableChaoEnvironmentMapping(var1);
	}
	else
	{
		AL_MaterialInit(var1);
	}
}

// FUNCTION: SADX 0x004444b0
void AL_ColorEdit(struct task *tp)
{
	struct task *var1;
	struct taskwk *var2;
	void *var3;

	var2 = tp->twp;
	var1 = ALW_GetTaskCount(0, *(unsigned short *)((char *)var2 + 0x14));
	var3 = *(void **)((char *)var1->twp + 0x6c);
	if (DAT_05b92e4c & 2)
	{
		AL__EditCancelMode(tp);
	}
	if (DAT_05b92e4c & 0x80)
	{
		if (*(unsigned char *)((char *)var3 + 0xd8) < 0xd)
		{
			*(unsigned char *)((char *)var3 + 0xd8) = *(unsigned char *)((char *)var3 + 0xd8) + 1;
		}
		else
		{
			*(unsigned char *)((char *)var3 + 0xd8) = 0;
		}
	}
	if (DAT_05b92e4c & 0x40)
	{
		if (*(unsigned char *)((char *)var3 + 0xd8) != 0)
		{
			*(unsigned char *)((char *)var3 + 0xd8) = *(unsigned char *)((char *)var3 + 0xd8) - 1;
			AL_MaterialInit(var1);
			return;
		}
		*(unsigned char *)((char *)var3 + 0xd8) = 0xd;
	}
	AL_MaterialInit(var1);
}

// STUB: SADX 0x00444930
void AL_PartsBTLEdit(struct task *tp)
{
}

// STUB: SADX 0x00445e40
void AL_LandmarkEdit(struct task *tp)
{
}

// FUNCTION: SADX 0x00445ea0
void AL_MotionEdit(struct task *tp)
{
	struct task *var1;
	struct taskwk *var2;
	long var3;
	float var4;
	int var5;

	var2 = tp->twp;
	var1 = ALW_GetTaskCount(0, *(unsigned short *)((char *)var2 + 0x14));
	if (DAT_05b92e4c & 2)
	{
		AL__EditCancelMode(tp);
	}
	var4 = AL_GetMotionFrame(var1);
	var3 = AL_GetMotionNum(var1);
	if (DAT_05b92ea0 & 0x40)
	{
		var4 = var4 - 0.05f;
		AL_SetMotionFrame(var1, var4);
	}
	else if (DAT_05b92ea0 < 0)
	{
		var4 = var4 + 0.05f;
		AL_SetMotionFrame(var1, var4);
	}
	if (DAT_05b92e4c & 0x10)
	{
		var3 = var3 - 1;
		if (var3 < 0)
		{
			var3 = 0x270;
		}
		AL_SetMotionSkip(var1, var3);
	}
	else if (DAT_05b92e4c & 0x20)
	{
		var3 = var3 + 1;
		if (var3 > 0x270)
		{
			var3 = 0;
		}
		AL_SetMotionSkip(var1, var3);
	}
	var5 = 0;
	do
	{
		if (var5 != 5)
		{
			njPrintColor(0xffafafaf);
		}
		else
		{
			njPrintColor(0xffffffff);
		}
		var5 = var5 + 1;
	}
	while (var5 < 0xb);
	AL_ShapeControl(var1);
	AL_IconControl(var1);
}

// STUB: SADX 0x00445f80
void AL_LifeEdit(struct task *tp)
{
}

// STUB: SADX 0x004463e0
void AL_JingleEdit(struct task *tp)
{
}
