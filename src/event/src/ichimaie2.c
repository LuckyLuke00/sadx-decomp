#include "decls.h"

// STUB: SADX 0x007d4e40
void CIchimaie2_Exec(struct task *_this)
{
}

// STUB: SADX 0x007d4ea0
struct task *CIchimaie2_Create(struct NJS_TEXLIST *texlistp, unsigned char mode)
{
	return (struct task *)0;
}

// FUNCTION: SADX 0x007d4f10
void FUN_007d4f10(struct task *param_1, float param_2, void *param_3)
{
	struct taskwk *var1 = param_1->twp;
	var1->pos.y = param_2;
	*(void **)((char *)var1 + 0x14) = param_3;
}

// FUNCTION: SADX 0x007d4f30
void CIchimaie2_SetPriority(struct task *_this, float pri)
{
	_this->twp->pos.z = pri;
}

// FUNCTION: SADX 0x007d4f40
void FUN_007d4f40(struct task *param_1, int param_2)
{
	param_1->twp->ang.z = param_2;
}

// FUNCTION: SADX 0x007d4f50
void CIchimaie2_SetBlendingMode(struct task *_this, int index, long mode)
{
	((char *)_this->twp)[index + 8] = (char)mode;
}
