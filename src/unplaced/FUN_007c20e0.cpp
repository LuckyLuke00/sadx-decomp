#include "decls.h"
extern int DAT_060cbeec;
extern struct obj _object_tr1_s_t1_body_s_t1_body[1];

// FUNCTION: SADX 0x007c20e0
void FUN_007c20e0(void)
{
	struct obj *var1 = _object_tr1_s_t1_body_s_t1_body[0].child;
	var1->sibling->sibling->sibling = 0;
}

// FUNCTION: SADX 0x007c2100
void FUN_007c2100(void)
{
	((struct obj *)_object_tr1_s_t1_body_s_t1_body[0].child)->sibling->sibling->sibling = (struct obj *)DAT_060cbeec;
}
