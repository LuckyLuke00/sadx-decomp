#include "decls.h"
extern float DAT_0629c6e0;
extern float DAT_0629c6ec;
extern float DAT_0629c6f0;

// FUNCTION: SADX 0x0067ee70
void njSetScreen(float *s)
{
	DAT_0629c6e0 = s[0];
	DAT_0629c6ec = s[3];
	DAT_0629c6f0 = s[4];
}
