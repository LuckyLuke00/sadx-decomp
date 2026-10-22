#include "decls.h"
extern int DAT_060b9ab4;
extern int DAT_060b9a8c;
extern int DAT_060b9ae4;
extern float DAT_060b9b2c;
extern int DAT_060b9b34;

// FUNCTION: SADX 0x006c7e80
void Egm2CameraYurashi(unsigned char level)
{
	DAT_060b9b2c += (float)level * 0.5;
}

// FUNCTION: SADX 0x006c7f70
long Egm2CameraHumiCameraGet()
{
	return DAT_060b9b34;
}

// FUNCTION: SADX 0x006c7f80
void Egm2CameraTaoreSet()
{
	DAT_060b9ab4 = 1;
	DAT_060b9a8c = 1;
	DAT_060b9ae4 = 1;
}

// STUB: SADX 0x006c8330
struct task *Egm2StartPositionTask(struct NJS_POINT3 *pos)
{
	return (struct task *)0;
}
