#include "decls.h"
void FUN_0084e4b0(int param_1);
void FUN_0084e430(int param_1);

// STUB: SADX 0x0084e430
void FUN_0084e430(int param_1)
{
}

// FUNCTION: SADX 0x0084e780
void FUN_0084e780(int param_1)
{
	*(void (**)(int))(param_1 + 0x10) = FUN_0084e4b0;
	*(void (**)(int))(param_1 + 0x18) = FUN_0084e430;
}
