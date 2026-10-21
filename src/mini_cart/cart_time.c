#include "decls.h"
extern struct NJS_SPRITE DAT_03527f50;

// STUB: SADX 0x007e6270
void CartInitLetter()
{
}

// FUNCTION: SADX 0x007e62d0
void CartTimeDisplayTitle()
{
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	late_DrawSprite2D(&DAT_03527f50, 0, 22046.0, 0x20, 4);
}

// STUB: SADX 0x007e63a0
float drawNumber2(float xPos, float yPos, const float *prio_a, int number)
{
	return (float)0;
}

// STUB: SADX 0x007e6700
void displayDatumTime(long *time)
{
}

// STUB: SADX 0x007e6760
void CartTimeHistoryTime(signed char lap, long *subToal, long *bestSubTotal)
{
}

// STUB: SADX 0x007e68b0
void CartTimeDisplayTimeWithColor(long time, long best)
{
}
