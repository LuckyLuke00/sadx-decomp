#include "decls.h"

// FUNCTION: SADX 0x006f1d30
void Choas4ArmFlagSet(struct obj *obj, long hide)
{
	do
	{
		if (hide != 0)
		{
			obj->evalflags |= 8;
		}
		else
		{
			obj->evalflags &= 0xfffffff7;
		}
		if (obj->child != 0)
		{
			Choas4ArmFlagSet(obj->child, hide);
		}
		obj = obj->sibling;
	}
	while (obj != 0);
}
