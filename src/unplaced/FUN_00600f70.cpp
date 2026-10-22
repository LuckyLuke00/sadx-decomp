#include "decls.h"
void FUN_00600fc0(void *param_1);
void GetMiniGameNowAvaStgActPrm(struct AvaStgActPrmT *stgactprmptr);

// FUNCTION: SADX 0x00600f70
void FUN_00600f70(void *param_1)
{
	GetMiniGameNowAvaStgActPrm((struct AvaStgActPrmT *)((char *)param_1 + 0x30));
	FUN_00600fc0(param_1);
	*(int *)((char *)param_1 + 0xc8) = 0;
	*(float *)((char *)param_1 + 0xc4) = 1.0f;
	*(char *)((char *)param_1 + 0xcc) = 0xff;
	*(int *)((char *)param_1 + 0x18) = 0;
}
