#include "decls.h"
extern struct NJS_POINT3 DAT_060b9d58[1];
extern float DAT_060b9f38[16];
extern struct CCL_INFO colli_info[20];

// FUNCTION: SADX 0x006c9a30
void Egm2ColisionInit(struct task *tp)
{
	CCL_Init(tp, (struct CCL_INFO *)&colli_info, 0x14, 3);
	SET_COLLI_RANGE(tp->twp->cwp, 150.0);
}

// FUNCTION: SADX 0x006c9b50
float *Egm2BaseMatrix()
{
	return DAT_060b9f38;
}

// FUNCTION: SADX 0x006c9d00
struct NJS_POINT3 *Egm2CollisionPos(unsigned char no)
{
	return &DAT_060b9d58[no];
}
