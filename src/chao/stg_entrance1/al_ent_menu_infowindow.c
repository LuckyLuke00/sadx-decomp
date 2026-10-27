#include "decls.h"
void FUN_00473940(struct task *param_1, float param_2, float param_3);

// STUB: SADX 0x00473940
void FUN_00473940(struct task *tp, float param_2, float param_3)
{
}

// FUNCTION: SADX 0x00473cb0
void PersonalRecordWindowDestructor(struct task *tp)
{
	Free(tp->twp);
	tp->twp = 0;
}

// STUB: SADX 0x00473cd0
void CreateInfoBaseWindow(struct task *tp)
{
}
