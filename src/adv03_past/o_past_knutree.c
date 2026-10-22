#include "decls.h"
extern struct CCL_INFO cinfo_tree[1];

// FUNCTION: SADX 0x006c0b40
void ObjectPastKnucklesTree(struct task *tp)
{
	struct taskwk *var1 = tp->twp;
	if (FUN_004c39c0(tp) != 0)
	{
		KnucklesTreeDisplayer(tp);
		return;
	}
	if (var1->mode == 0)
	{
		CCL_Init(tp, &cinfo_tree[0], 1, 4);
		tp->disp = KnucklesTreeDisplayer;
		tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
		var1->mode = 1;
	}
	KnucklesTreeDisplayer(tp);
	EntryColliList(var1);
}
