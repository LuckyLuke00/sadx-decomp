#include "decls.h"

// FUNCTION: SADX 0x007e9730
void SandOutVibrate(const struct NJS_POINT3 *pos_p, float range)
{
	struct taskwk *var1;
	float var2;

	if (pos_p == NULL)
	{
		return;
	}
	var1 = DAT_05b42a7c;
	if (var1 == NULL)
	{
		return;
	}
	var2 = njSqrt((pos_p->x - var1->pos.x) * (pos_p->x - var1->pos.x) + (pos_p->y - var1->pos.y) * (pos_p->y - var1->pos.y) + (pos_p->z - var1->pos.z) * (pos_p->z - var1->pos.z));
	if (var2 <= range)
	{
		VibShot(0, 0);
	}
}
