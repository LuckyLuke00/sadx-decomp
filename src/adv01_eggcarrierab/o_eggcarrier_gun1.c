#include "decls.h"

// FUNCTION: SADX 0x00698100
void Object_EgaGun1Draw(struct task *tp)
{
	Object_EgaGun1DrawStat(tp);
}

// STUB: SADX 0x00698110
void Object_EgaGun1Init(struct task *tp)
{
}

// FUNCTION: SADX 0x00698170
void ObjectEgaGun1(struct task *tp)
{
	if (CheckRangeOut(tp) == 0)
	{
		Object_EgaGun1Init(tp);
	}
}
