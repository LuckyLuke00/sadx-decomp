#include "decls.h"
extern struct NJS_SPRITE DAT_060eea04;

// FUNCTION: SADX 0x007e6a60
void CartLapDisplayLap(signed char lap)
{
	LapBoardSprite.p.y = 96.0f;
	LapNumberSprite.p.y = 99.0f;
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	DAT_060eea04 = LapBoardSprite;
	DAT_060eea04.p.x = ScreenRaitoX * 640.0 - 16.0 - 96.0 - 35.0;
	late_DrawSprite2D(&DAT_060eea04, 0, 22045.998f, 0x20, 4);
	DAT_060eea04 = LapNumberSprite;
	DAT_060eea04.p.x = ScreenRaitoX * 640.0 - 16.0 - 96.0 + 39.0 - 35.0;
	late_DrawSprite2D(&DAT_060eea04, lap, 22046.0f, 0x20, 4);
}
