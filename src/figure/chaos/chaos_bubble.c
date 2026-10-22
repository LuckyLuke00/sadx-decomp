#include "decls.h"
extern void *DAT_060dfb48;
extern float DAT_060dfb58;

// STUB: SADX 0x008c67b0
void CreateBubble()
{
}

// STUB: SADX 0x008c6970
void DisplayBubble()
{
}

// STUB: SADX 0x008c6aa0
void setChaosBubble(struct taskwk *twp, struct chaoswk *cwp, struct BUBBLE_DATA *tbl)
{
}

// FUNCTION: SADX 0x008c6ba0
void deleteBubbleChaos()
{
	Free(DAT_060dfb48);
}

// FUNCTION: SADX 0x008c6bc0
void ChaosBubbleAdd(float num)
{
	DAT_060dfb58 = num;
}
