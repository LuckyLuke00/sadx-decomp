#include "decls.h"

// FUNCTION: SADX 0x008b9f60
void FUN_008b9f60(struct task *param_1)
{
	FreeTaskC(param_1);
}

// FUNCTION: SADX 0x008ba100
void SetLineringEffect(long on)
{
	ring_kiran = on;
}
