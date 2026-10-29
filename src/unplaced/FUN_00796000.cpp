#include "decls.h"
extern int DAT_060cbc00;
extern struct obj DAT_060cbc04;
extern struct obj _object_tr2a_s_t2b_body_s_t2b_body[1];

// FUNCTION: SADX 0x00796000
void FUN_00796000(void)
{
	struct obj *var1 = _object_tr2a_s_t2b_body_s_t2b_body[0].child;
	var1->sibling->sibling = &DAT_060cbc04;
}

// FUNCTION: SADX 0x00796010
void FUN_00796010()
{
	struct obj *var1 = _object_tr2a_s_t2b_body_s_t2b_body[0].child;
	*(int *)((char *)var1->sibling + 0x30) = DAT_060cbc00;
}
