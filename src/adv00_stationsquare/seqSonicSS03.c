#include "decls.h"
extern int DAT_05b3ea28;
extern char DAT_05bafb83;
extern char DAT_05bafb84;
extern char DAT_05bafb8d;
void initSetPositionS_WhenHeGetShoes(struct task *tp);

// FUNCTION: SADX 0x00680e80
void SetPositionS_WhenHeGetShoes(struct task *tp)
{
	SetPositionP(0, 504.0, -93.0, 803.0);
	FreeTask(tp);
}

// FUNCTION: SADX 0x00680eb0
void initSetPositionS_WhenHeGetShoes(struct task *tp)
{
	tp->exec = SetPositionS_WhenHeGetShoes;
}

// FUNCTION: SADX 0x00680ec0
void initSonicSS03()
{
	if (*(short *)((char *)DAT_05b3ea28 + 0x2) == 0)
	{
		SeqSetTime(1);
	}
	else if (*(short *)((char *)DAT_05b3ea28 + 0x2) >= 3)
	{
		SeqSetTime(2);
	}
	if (DAT_05bafb83 == 1 && DAT_05bafb84 == 0 && DAT_05bafb8d == 1)
	{
		CreateElementalTask(0, 2, initSetPositionS_WhenHeGetShoes);
	}
}
