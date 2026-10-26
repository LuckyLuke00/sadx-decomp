#include "decls.h"
extern struct obj *DAT_060cbcb0;
extern struct obj _object_tr1_s_t1_body_s_t1_body[1];
extern int DAT_060cbcb8;
extern int DAT_060cbcb4;

// FUNCTION: SADX 0x0079bb60
void FUN_0079bb60(void)
{
	((struct obj *)_object_tr1_s_t1_body_s_t1_body[0].child)->sibling->sibling->sibling = (struct obj *)&DAT_060cbcb8;
}

// FUNCTION: SADX 0x0079bb80
void FUN_0079bb80(void)
{
	((struct obj *)_object_tr1_s_t1_body_s_t1_body[0].child)->sibling->sibling->sibling = (struct obj *)DAT_060cbcb4;
}

// STUB: SADX 0x0079bba0
void FUN_0079bba0()
{
}

// FUNCTION: SADX 0x0079bbf0
void FUN_0079bbf0(void)
{
	((struct obj *)_object_tr1_s_t1_body_s_t1_body[0].child)->sibling->sibling = DAT_060cbcb0;
}
