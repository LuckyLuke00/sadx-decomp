#include "decls.h"
extern float DAT_060dfb58;

// STUB: SADX 0x008c6aa0
void setChaosBubble(struct taskwk *twp, struct chaoswk *cwp, struct BUBBLE_DATA *tbl)
{
}

// FUNCTION: SADX 0x008c6bc0
void ChaosBubbleAdd(float num)
{
	DAT_060dfb58 = num;
}
