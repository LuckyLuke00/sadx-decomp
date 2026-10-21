#include "decls.h"
extern unsigned char DAT_05bafc87;
extern unsigned char DAT_05bafc89;
void initSetPositionS_WhenHeGetBooster(struct task *tp);

// FUNCTION: SADX 0x006a6eb0
void SetPositionS_WhenHeGetBooster(struct task *tp)
{
	SetPositionP(0, -73.0, 1.0, -36.79999923706055);
	FreeTask(tp);
}

// FUNCTION: SADX 0x006a6ee0
void initSetPositionS_WhenHeGetBooster(struct task *tp)
{
	tp->exec = SetPositionS_WhenHeGetBooster;
}

// FUNCTION: SADX 0x006a6ef0
void initE102EC02()
{
	if (DAT_05bafc87 == 0 && DAT_05bafc89 == 1)
	{
		CreateElementalTask(0, 2, initSetPositionS_WhenHeGetBooster);
	}
}
