#include "decls.h"
extern struct NJS_POINT3 player_pos[1];
extern short *DAT_05baf368;
extern signed char DAT_060c369c;
extern float DAT_060c36a0;
extern float DAT_060c36a4;
extern char DAT_060c3691;
extern short DAT_060c36ac;
extern short DAT_060c36b0;
extern struct task *DAT_060c368c;
extern int DAT_060c36a8;

// FUNCTION: SADX 0x006fdd20
void Chaos7_0GameManager_dest(struct task *tp)
{
	FreeTask(DAT_060c368c);
	DAT_060c36a8 = 0;
}

// FUNCTION: SADX 0x006fde10
void ChaosFadeScreen(int sa, int ea, int color, int time, int distime)
{
	if (DAT_060c36b0 <= 0)
	{
		DAT_060c36a0 = (float)sa;
		DAT_060c3691 = (char)color;
		DAT_060c36a4 = (float)(ea - sa) / (float)time;
		DAT_060c36ac = (short)time;
		DAT_060c36b0 = (short)distime;
	}
}

// STUB: SADX 0x006fde60
void SetChaos7Pos()
{
}

// FUNCTION: SADX 0x006fdeb0
void FUN_006fdeb0(void)
{
	int var1 = DAT_060c369c;
	struct NJS_POINT3 *var2 = &player_pos[var1];
	short *var3 = DAT_05baf368;

	*(int *)((char *)var3 + 0x20) = *(int *)((char *)var2 + 0x0);
	*(int *)((char *)var3 + 0x24) = *(int *)((char *)var2 + 0x4);
	*(int *)((char *)var3 + 0x28) = *(int *)((char *)var2 + 0x8);
}

// STUB: SADX 0x006fdee0
void SetChaos7Pos2(struct task *tp, int num)
{
}

// STUB: SADX 0x006fe0b0
int CheckPathEnable(int num)
{
	return (int)0;
}
