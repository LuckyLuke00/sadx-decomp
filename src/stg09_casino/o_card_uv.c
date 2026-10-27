#include "decls.h"
static void Normal(struct task *tp);
static void Exit(struct task *tp);
extern short DAT_060dc444;
static void Disp(struct task *tp);
extern struct TEXUVINFO2 texuv2info[];

// FUNCTION: SADX 0x0087fde0
static void Exit(struct task *tp)
{
	FUN_007d21b0(&texuv2info[0], 7);
}

#pragma optimize("", off)
// STUB: SADX 0x0087fdf0
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

#pragma optimize("", off)
// STUB: SADX 0x0087ff90
static void Normal(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0087ffb0
void ObjectCardUV(struct task *tp)
{
	DAT_060dc444 = 0;
	ObjCasino_InitTexUvInfo2((struct TEXUVINFO2 *)&texuv2info, 7);
	tp->exec = Normal;
	tp->disp = Disp;
	tp->dest = Exit;
}
