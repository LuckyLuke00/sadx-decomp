#include "decls.h"
extern int DAT_04c7c0c0;
extern void *DAT_05b39bb4;
extern void *DAT_05b42898;
extern void *DAT_05b4296c;
int LoadFileWithMalloc(char *pcFileName, void **pBuff);
extern "C" int sprintf(char *param_1, const char *param_2, ...);

// FUNCTION: SADX 0x0049a4e0
void FUN_0049a4e0(int param_1, int param_2)
{
	char local_108[256];
	sprintf(local_108, "CamMi%04d%s.bin", param_1 * 100 + param_2, GetFnamesPlayerStr());
	if (LoadFileWithMalloc(local_108, &DAT_05b39bb4) != 0)
	{
		DAT_05b39bb4 = 0;
		return;
	}
	DAT_05b4296c = DAT_05b39bb4;
	DAT_05b42898 = (void *)((char *)DAT_05b39bb4 + 0x40);
}
