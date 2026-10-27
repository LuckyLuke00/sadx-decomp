#include "decls.h"

// STUB: SADX 0x0087ee30
void ObjectCasinoTutuADraw(struct task *tp)
{
}

// STUB: SADX 0x0087ef00
void ObjectCasinoTutuBDraw(struct task *tp)
{
}

// STUB: SADX 0x0087efc0
void ObjectCasinoTutuCDraw(struct task *tp)
{
}

#pragma optimize("", off)
// STUB: SADX 0x0087f530
void ObjectCasinoTutuAInit(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0087f590
void ObjectCasinoTutuA(struct task *tp)
{
	if (CheckRangeOutWithR(tp, 62510.0f) == 0)
	{
		ObjectCasinoTutuAInit(tp);
	}
}

// STUB: SADX 0x0087f5c0
void ObjectCasinoTutuB(struct task *tp)
{
}

// STUB: SADX 0x0087f610
void ObjectCasinoTutuC(struct task *tp)
{
}
