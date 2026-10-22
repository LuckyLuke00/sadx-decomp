#include "decls.h"
void FUN_008d9be0(void *param_1, float param_2, float param_3);

// STUB: SADX 0x008d9000
void FUN_008d9000(struct taskwk *param_1, float param_2)
{
}

// FUNCTION: SADX 0x008d9050
void FUN_008d9050(void *param_1, unsigned char param_2)
{
	void *local_cg;
	void *local_8g;
	local_cg = *(void **)((char *)(*(void **)((char *)param_1 + 8)) + 0x20);
	local_8g = *(void **)((char *)param_1 + 0x20);
	SetInputP(param_2, 0x24);
	FUN_008d9be0((char *)local_8g + 0x20, *(float *)((char *)local_8g + 0x2c), *(float *)((char *)local_cg + 8));
}
