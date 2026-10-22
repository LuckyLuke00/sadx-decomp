#include "decls.h"
extern struct task *DAT_060b99f8;
void egm1ground_smoke_exec(struct task *tp);

// FUNCTION: SADX 0x006c4730
void SetEgm1GroundSmoke(struct NJS_POINT3 *posp)
{
	struct task *var1;
	struct anywk *var2;

	var1 = CreateElementalTask(0, 3, egm1ground_smoke_exec);
	DAT_060b99f8 = var1;
	if (var1 != NULL)
	{
		var2 = (struct anywk *)CAlloc(1, 0x10);
		var1->awp = var2;
		*(int *)&var2->work.ul[0] = *(int *)&posp->x;
		*(int *)&var2->work.ul[1] = *(int *)&posp->y;
		*(int *)&var2->work.ul[2] = *(int *)&posp->z;
		var2->work.ub[12] = 0;
		var1->exec = egm1ground_smoke_exec;
	}
}

// FUNCTION: SADX 0x006c4780
void ChgEgm1SmokeStat(unsigned char mode)
{
	*(unsigned char *)((char *)DAT_060b99f8->awp + 0xc) = mode;
}

// STUB: SADX 0x006c4830
void egm1one_clay_disp(struct task *tp)
{
}

// STUB: SADX 0x006c48b0
void ChgEgm1ClayStat(unsigned char mode)
{
}

// STUB: SADX 0x006c48c0
void egm1one_clay_exec(struct task *tp)
{
}

// STUB: SADX 0x006c4b20
void SetEgm1GroundClay(struct NJS_POINT3 *posp)
{
}
