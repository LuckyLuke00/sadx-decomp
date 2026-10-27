#include "decls.h"
extern int DAT_05cbef64;
void DisplayBg(struct task *tp);
static void ExecuteBg(struct task *tp);
static void DisplayBg(struct task *tp);
static void DestructBg(struct task *tp);

// STUB: SADX 0x00803e40
void SetTableBg()
{
}

// FUNCTION: SADX 0x00803fa0
static void DestructBg(struct task *tp)
{
	switch (tp->twp->mode - 1)
	{
		case 0:
		case 1:
			late_ReleaseTexture(&texlist_windy_back);
			break;
		case 3:
		case 4:
			late_ReleaseTexture(&texlist_windy_back2);
			break;
		case 7:
			late_ReleaseTexture(&texlist_windy_back3);
			break;
	}
	___njFogDisable();
}

// STUB: SADX 0x00804210
void CheckGravity(struct task *tp)
{
}

// STUB: SADX 0x00804340
void FUN_00804340(struct task *tp)
{
}

// FUNCTION: SADX 0x008043a0
void FUN_008043a0(void)
{
	struct NJS_POINT3 local_14;
	local_14.x = 4136.0f;
	local_14.y = -4460.0f;
	local_14.z = -1620.0f;
	DAT_05cbef64 = (CheckCollisionP(&local_14, 525.0f) == 1) - 1 + 2;
}

// STUB: SADX 0x008044d0
static void DisplayBg(struct task *tp)
{
}

// STUB: SADX 0x00804a50
static void ExecuteBg(struct task *tp)
{
}

// FUNCTION: SADX 0x00804ad0
void Bg_Windy(struct task *tp)
{
	tp->exec = ExecuteBg;
	tp->disp = DisplayBg;
	tp->dest = DestructBg;
}
