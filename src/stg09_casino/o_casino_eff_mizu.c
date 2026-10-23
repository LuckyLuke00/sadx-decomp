#include "decls.h"

// STUB: SADX 0x0088c400
void ObjectCasinoMizuEnd(struct task *tp)
{
}

// STUB: SADX 0x0088c460
void ObjectCasinoMizuDraw(struct task *tp)
{
}

// STUB: SADX 0x0088c640
void MizuSmoke1(float x, float y, float z, float spd)
{
}

// STUB: SADX 0x0088c720
void MizuSmoke2(float x, float y, float z, float spd)
{
}

// FUNCTION: SADX 0x0088ce20
void ObjectCasinoMizu1(struct task *tp)
{
	tp->disp = ObjectCasinoMizuDraw;
	tp->exec = ObjectCasinoMizuExec;
	tp->dest = ObjectCasinoMizuEnd;
}
