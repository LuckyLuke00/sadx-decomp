#include "decls.h"
struct thread;
void FUN_0056aea0(int param_1);
void FUN_0056b810(int param_1, unsigned char *param_2);
void FUN_0056b8b0(void);
struct thread *TH_CreateChild(struct thread *parent, void (*func)(void *), void *pParam, unsigned int stack_size);
void *TH_GetWork(struct thread *tp);
extern unsigned char DAT_0098b338;

// FUNCTION: SADX 0x0056b7a0
void FUN_0056b7a0(int param_1, int param_2)
{
	void *local_cg;
	struct thread *local_8g;

	FUN_0056aea0(1);
	local_8g = TH_CreateChild(0, (void (__cdecl *)(void *))FUN_0056b8b0, 0, 0);
	if (local_8g != 0)
	{
		local_cg = TH_GetWork(local_8g);
		*(char *)local_cg = (char)param_1;
		*(int *)((char *)local_cg + 4) = param_2;
	}
	FUN_0056b810(param_1, &DAT_0098b338);
	FUN_0056aea0(1);
}
