#include "decls.h"
extern int DAT_060c4aac;
extern int DAT_060c462c;
extern float DAT_060c4ab0;
extern int DAT_05b9d838;
extern struct NJS_TEXLIST _texlist_e101r;
extern int DAT_060c4aa8;
extern int DAT_060c4ab4;

// FUNCTION: SADX 0x0070ee40
void E101R_BarrierInit()
{
	DAT_060c4aa8 = 0;
	DAT_060c4ab0 = 0.0f;
	DAT_060c4aac = 0;
	DAT_060c4ab4 = DAT_060c462c + 0xa19c;
}

// FUNCTION: SADX 0x0070ee70
void E101R_BarrierExit()
{
	DAT_060c4ab4 = 0;
}

// FUNCTION: SADX 0x0070ee80
void E101R_BarrierSetMode(int mode)
{
	DAT_060c4aa8 = mode;
}

// STUB: SADX 0x0070ee90
void E101R_BarrierExec()
{
}

// FUNCTION: SADX 0x0070ef40
void E101R_BarrierDisp()
{
	if (DAT_060c4ab0 == 0.0f)
	{
		return;
	}
	if (DAT_05b9d838 == 0 && DAT_060c4ab4 != 0)
	{
		njControl3D(0x14);
		njSetConstantAttr(0x3ffffff, 0x86000000);
		SetMaterial(DAT_060c4ab0 * 0.5, 1.0f, 1.0f, 1.0f);
		___njSetTexture(&_texlist_e101r);
		late_DrawObject((struct obj *)DAT_060c4ab4, 4);
	}
	ResetMaterial();
}
