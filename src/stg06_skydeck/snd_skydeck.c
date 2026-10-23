#include "decls.h"

// FUNCTION: SADX 0x00840030
void SoundSkydeck_engine(struct task *tp)
{
	dsPlay_timer_v(0x3d8, (int)tp, 1, 0x30, 2, tp->twp->pos.x, tp->twp->pos.y, tp->twp->pos.z);
}
