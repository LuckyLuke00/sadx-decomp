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

// FUNCTION: SADX 0x007d4f30
void CIchimaie2_SetPriority(struct task *_this, float pri)
{
	*(float *)((char *)_this->twp + 0x28) = pri;
}

// FUNCTION: SADX 0x007d4f50
void CIchimaie2_SetBlendingMode(struct task *_this, int index, long mode)
{
	((char *)_this->twp)[index + 8] = (char)mode;
}
