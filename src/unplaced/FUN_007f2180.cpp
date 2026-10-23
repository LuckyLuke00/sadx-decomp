#include "decls.h"
extern unsigned char DAT_05ccceb8[60];
extern char DAT_05ccca18;

// FUNCTION: SADX 0x007f2180
int FUN_007f2180()
{
	return FUN_0049e130((SAVE_DATA *)&DAT_05ccca18);
}

// FUNCTION: SADX 0x007f2190
int FUN_007f2190()
{
	int var1;
	int var2;

	var1 = 0;
	var2 = 0;
	do
	{
		if ((DAT_05ccceb8[var2] & 0x80) != 0)
			var1++;
		if ((DAT_05ccceb8[var2 + 1] & 0x80) != 0)
			var1++;
		if ((DAT_05ccceb8[var2 + 2] & 0x80) != 0)
			var1++;
		if ((DAT_05ccceb8[var2 + 3] & 0x80) != 0)
			var1++;
		if ((DAT_05ccceb8[var2 + 4] & 0x80) != 0)
			var1++;
		if ((DAT_05ccceb8[var2 + 5] & 0x80) != 0)
			var1++;
		var2 += 6;
	}
	while (var2 < 0x3c);
	return var1;
}

// FUNCTION: SADX 0x007f21e0
void FUN_007f21e0()
{
	dsPlay_oneshot(2, 0, 0, 0);
	dsPlay_oneshot(0x16, 0, 0, 0);
}

// FUNCTION: SADX 0x007f2200
void FUN_007f2200()
{
	dsPlay_oneshot(1, 0, 0, 0);
}

// FUNCTION: SADX 0x007f2220
void FUN_007f2220()
{
	dsPlay_oneshot(3, 0, 0, 0);
	dsPlay_oneshot(0x15, 0, 0, 0);
}

// FUNCTION: SADX 0x007f2240
void FUN_007f2240()
{
	SetAdvaBGM(0x48);
}
