#include "decls.h"
void FUN_0056bcd0();
extern int DAT_05ccdd28;

// FUNCTION: SADX 0x0056bcd0
void FUN_0056bcd0()
{
	int *local_8g = (int *)TH_GetWork(0);
	int *local_cg = (int *)&DAT_05ccdd28;
	if (*(int *)((char *)local_cg + 0xcc) == *local_8g)
	{
		*(int *)((char *)local_cg + 0xcc) = 0;
		CameraReleaseEventCamera();
	}
}
