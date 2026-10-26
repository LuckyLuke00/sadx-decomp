#include "decls.h"
extern struct obj _object_tr2a_s_t2b_body_s_t2b_body[1];
extern int DAT_060cbbbc;

// FUNCTION: SADX 0x00794ec0
void FUN_00794ec0(void)
{
	struct obj *var1 = _object_tr2a_s_t2b_body_s_t2b_body[0].child;
	*(int *)((char *)var1->sibling + 0x30) = (int)&DAT_060cbbbc;
}

// STUB: SADX 0x00794ed0
void FUN_00794ed0()
{
}
