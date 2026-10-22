#include "decls.h"
extern short DAT_05b9d744;
void SSTwrouka(struct task *tp);
struct task *CreateElementalTask(unsigned short im, long level, void (*exec)(struct task *));

// FUNCTION: SADX 0x00681e30
void ObjectSSTwrouka(struct task *tp)
{
	if (FUN_004c39c0(tp) == 0)
	{
		DeadOut(tp);
	}
}

// FUNCTION: SADX 0x00682040
void CreateSSTwrouka()
{
	if (*(char *)&DAT_05b9d744 == 5)
	{
		CreateElementalTask(2, 3, SSTwrouka);
	}
}
