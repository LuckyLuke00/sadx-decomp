#include "decls.h"
#include "../advertise.h"

// STUB: SADX 0x00424970
SOCInput::SOCInput()
{
}

// FUNCTION: SADX 0x00424a70
int __fastcall FUN_00424a70(void *param_1)
{
	return *(int *)((char *)param_1 + 0x48);
}

// FUNCTION: SADX 0x00424a80
char __fastcall FUN_00424a80(void *param_1)
{
	return (*(int *)((char *)param_1 + 0x48) == 5) + 5;
}

// STUB: SADX 0x00424b40
SOCController* SOCInput::FUN_00424b40()
{
	return 0;
}

// STUB: SADX 0x00424b90
void __fastcall FUN_00424b90(void *param_1, int param_2)
{
}
