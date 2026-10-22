#include "decls.h"
extern float DAT_0629c6e0;
extern float DAT_0629c6ec;
extern float DAT_0629c6f0;

// FUNCTION: SADX 0x0067ee70
void njSetScreen(float *param_1)
{
	DAT_0629c6e0 = param_1[0];
	DAT_0629c6ec = param_1[3];
	DAT_0629c6f0 = param_1[4];
}
