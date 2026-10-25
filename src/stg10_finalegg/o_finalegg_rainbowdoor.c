#include "decls.h"
extern int DAT_060dd07c;
extern "C" int rand(void);

// FUNCTION: SADX 0x00890a50
void DoorDestructor(struct task *tp)
{
	dsStop_id((int)tp->twp);
}

// STUB: SADX 0x00890b20
void FUN_00890b20(void)
{
}

// FUNCTION: SADX 0x00890b60
void FEGG_ResetAmysFakeRoot()
{
	int var1;
	float var2;

	var1 = rand();
	var2 = (float)var1 * 3.0517578125e-05f;
	var1 = (long)(var2 * 5.0f);
	DAT_060dd07c = var1;
}
