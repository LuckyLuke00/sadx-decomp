#include "decls.h"
extern unsigned long DAT_05edbcfc;

// FUNCTION: SADX 0x005a6b00
void InitRing()
{
	DAT_05edbcfc = 0;
}

// FUNCTION: SADX 0x005a7160
void RingDoneDisplayer(struct task *tp)
{
	RingDone(tp->twp);
}

// STUB: SADX 0x005a73c0
void DamegeRingScatter(unsigned char pno)
{
}

// FUNCTION: SADX 0x005a7d60
void dispTobitiri0(struct task *tp)
{
	struct NJS_POINT3 v;
	struct anywk *local_18;
	local_18 = tp->awp;
	v.x = 0.0;
	v.y = 3.44;
	v.z = 0.0;
	njCalcVector(0, &v, &v);
	RingDrawShadow(tp, *(float *)local_18, v.x, v.z);
}

// STUB: SADX 0x005a7dd0
void dispTobitiri1(struct task *tp)
{
}

// STUB: SADX 0x005a7e10
void FUN_005a7e10(struct NJS_TEXLIST *texlist)
{
}

// STUB: SADX 0x005a7e50
void RingDrawShadow(struct task *tp, float tempy, float pushx, float pushz)
{
}

// STUB: SADX 0x005a82d0
void RingNumRunning(float xpos, float ypos, float zpos, int num)
{
}
