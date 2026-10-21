#include "decls.h"
#include <stdlib.h>
extern int DAT_05b9d838;
extern struct obj object_sphere01;

// FUNCTION: SADX 0x0056e7a0
void DispSphere(struct NJS_POINT3 *bp, float scale)
{
	if (DAT_05b9d838 != 0)
		return;
	scale = scale * 0.1f;
	njPushMatrix(0);
	njTranslateV(0, bp);
	FUN_0067d2d0(0, scale, scale, scale);
	___dsDrawObject(&object_sphere01);
	njPopMatrix(1);
}

// STUB: SADX 0x0056e810
long ChkItemInPercent(float *tbl)
{
	return (long)0;
}

// STUB: SADX 0x0056eb30
void CharColliOn(struct taskwk *twp)
{
}

// STUB: SADX 0x0056eb90
void CharColliOff(struct taskwk *twp)
{
}
