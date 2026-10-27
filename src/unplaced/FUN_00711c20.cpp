#include "decls.h"
extern void *DAT_060c60f0;
extern "C" void *memset(void *param_1, int param_2, unsigned int param_3);
extern int DAT_060c6120;
extern int DAT_060c6124;
extern int DAT_060c6128;
extern int DAT_060c612c;

// FUNCTION: SADX 0x00711c20
void FUN_00711c20()
{
	struct task *var1;
	var1 = CreateElementalTask(0, 2, (void (__cdecl *)(struct task *))FUN_007d21b0);
	var1->awp = (struct anywk *)CAlloc(1, 4);
	memset(&DAT_060c60f0, 0, 0x30);
}

// FUNCTION: SADX 0x00711c50
void FUN_00711c50(int param_1, int param_2, int param_3, int param_4)
{
	DAT_060c6120 = param_1;
	DAT_060c6124 = param_2;
	DAT_060c6128 = param_3;
	DAT_060c612c = param_4;
}
