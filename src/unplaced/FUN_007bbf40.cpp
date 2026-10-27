#include "decls.h"
extern int DAT_060cbe74;
extern struct obj _object_tr2a_s_t2b_body_s_t2b_body[1];

// FUNCTION: SADX 0x007bbf40
void FUN_007bbf40(void)
{
	struct obj *var1 = _object_tr2a_s_t2b_body_s_t2b_body[0].child;
	*(int *)((char *)var1->sibling + 0x30) = 0x60cbe78;
}

// FUNCTION: SADX 0x007bbf50
void FUN_007bbf50(void)
{
	struct obj *var1 = _object_tr2a_s_t2b_body_s_t2b_body[0].child;
	*(int *)((char *)var1->sibling + 0x30) = DAT_060cbe74;
}
