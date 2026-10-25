#include "decls.h"
void AL__EditCancelMode(struct task *tp);
extern signed char DAT_05b92ea0;
extern unsigned char DAT_05b92e4c;

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

// STUB: SADX 0x004463e0
void AL_JingleEdit(struct task *tp)
{
}
