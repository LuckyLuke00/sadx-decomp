#include "decls.h"
extern struct obj *DAT_060cbc78;
extern struct obj *DAT_060cbca0;
extern struct obj *DAT_060cbca4;
extern struct obj *DAT_060cbc74;
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

// FUNCTION: SADX 0x0079bba0
void FUN_0079bba0()
{
	DAT_060cbc78 = 0;
	DAT_060cbca0 = ((struct obj *)_object_tr1_s_t1_body_s_t1_body[0].child)->sibling->sibling->child;
	DAT_060cbca4 = ((struct obj *)_object_tr1_s_t1_body_s_t1_body[0].child)->sibling->sibling->sibling;
	DAT_060cbcb0 = ((struct obj *)_object_tr1_s_t1_body_s_t1_body[0].child)->sibling->sibling;
	((struct obj *)_object_tr1_s_t1_body_s_t1_body[0].child)->sibling->sibling = (struct obj *)&DAT_060cbc74;
}

// FUNCTION: SADX 0x0079bbf0
void FUN_0079bbf0(void)
{
	((struct obj *)_object_tr1_s_t1_body_s_t1_body[0].child)->sibling->sibling = DAT_060cbcb0;
}
