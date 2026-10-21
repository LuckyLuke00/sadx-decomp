#include "decls.h"
void FUN_004f5550(int param_1);
extern unsigned char DAT_05bafc2a;
extern unsigned char DAT_05bafc2b;

// FUNCTION: SADX 0x006aa660
void SetPositionK_WhenHeGetCraw(struct task *tp)
{
	SetPositionP(0, 1350.0, 0.0, -256.0);
	FreeTask(tp);
}

// FUNCTION: SADX 0x006aa690
void initSetPositionK_WhenHeGetCraw(struct task *tp)
{
	tp->exec = SetPositionK_WhenHeGetCraw;
}

// FUNCTION: SADX 0x006aa6a0
void initKnucklesMR02()
{
	FUN_004f5550(0x111);
	SeqSetTime(0);
	if (DAT_05bafc2a == 1 && DAT_05bafc2b == 0)
	{
		CreateElementalTask(0, 2, initSetPositionK_WhenHeGetCraw);
	}
}
