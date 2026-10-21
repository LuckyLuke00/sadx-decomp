#include "decls.h"
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

// STUB: SADX 0x00597a80
void SetVibTask(unsigned long u32Time)
{
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
