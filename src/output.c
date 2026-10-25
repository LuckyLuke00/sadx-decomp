#include "decls.h"
extern struct PDS_VIBPARAM *DAT_05cd3014;
extern int DAT_05cd0f24;
extern unsigned char gu8Vibration;
void SetVibTask(unsigned long u32Time);

// FUNCTION: SADX 0x00597a20
void VibShot(long pno, long Time)
{
	if (DAT_05cd0f24 != 0)
	{
		return;
	}
	if (gu8Vibration == 0)
	{
		return;
	}
	if (pno != 0)
	{
		return;
	}
	if (Time > 0xff)
	{
		Time = 0xff;
	}
	else if (Time < 0)
	{
		Time = 0;
	}
	if (Time < 1)
	{
		Time = 1;
	}
	SetVibTask((unsigned long)Time);
}

// FUNCTION: SADX 0x00597a80
void SetVibTask(unsigned long u32Time)
{
	struct task *local_8 = CreateElementalTask(8, 0, VibTask);
	if (local_8 == 0)
	{
		return;
	}
	*(int *)((char *)local_8->awp + 0) = u32Time << 2;
	DAT_05cd3014 = (struct PDS_VIBPARAM *)MAlloc(8);
	if (DAT_05cd3014 != 0)
	{
		*(char *)((char *)DAT_05cd3014 + 0) = 0;
		*(char *)((char *)DAT_05cd3014 + 1) = 1;
		*(char *)((char *)DAT_05cd3014 + 2) = 0xa;
		*(char *)((char *)DAT_05cd3014 + 3) = 0x32;
		*(char *)((char *)DAT_05cd3014 + 4) = 0;
		local_8->fwp = (struct forcewk *)DAT_05cd3014;
	}
	else
	{
		DestroyTask(local_8);
	}
}

// STUB: SADX 0x00597b20
void VibTask(struct task *tp)
{
}

// FUNCTION: SADX 0x00597b70
void VibConvergence(long pno, long Power, long Freq, long Time)
{
	if (DAT_05cd0f24 != 0)
	{
		return;
	}
	if (gu8Vibration == 0)
	{
		return;
	}
	if (pno != 0)
	{
		return;
	}
	if (Power > 4)
	{
		Power = 4;
	}
	else if (Power < -4)
	{
		Power = -4;
	}
	if (Power == 1)
	{
		Power = 2;
	}
	else if (Power == -1)
	{
		Power = -2;
	}
	if (Freq > 0x3b)
	{
		Freq = 0x3b;
	}
	else if (Freq < 7)
	{
		Freq = 7;
	}
	Time = (Freq * Time) / (Power << 2);
	if (Time <= 0)
	{
		Time = 1;
	}
	SetVibTask((unsigned long)Time);
}
