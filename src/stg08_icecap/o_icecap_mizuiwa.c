#include "decls.h"
static void Init(struct task *tp, struct obj *pobj);

#pragma optimize("", off)
// STUB: SADX 0x00862b80
static void Init(struct task *tp, struct obj *pobj)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x00862d20
void ObjectIcecapMizuiwaa(struct task *tp)
{
	Init(tp, (struct obj *)&object_obj_mizuiwa_a_obj_mizuiwa_a);
}

// FUNCTION: SADX 0x00862d40
void ObjectIcecapMizuiwab(struct task *tp)
{
	Init(tp, (struct obj *)&object_obj_mizuiwa_b_obj_mizuiwa_b);
}

// FUNCTION: SADX 0x00862d60
void ObjectIcecapMizuiwac(struct task *tp)
{
	Init(tp, (struct obj *)&object_obj_mizuiwa_c_obj_mizuiwa_c);
}
