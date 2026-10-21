#include "decls.h"
extern float DAT_04c2ea78;

// FUNCTION: SADX 0x008c1e50
void MirenEffSaveState()
{
	SaveControl3D();
	SaveConstantAttr();
}

// FUNCTION: SADX 0x008c1e60
void MirenEffLoadState()
{
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	LoadControl3D();
	LoadConstantAttr();
	ResetMaterial();
}

// FUNCTION: SADX 0x008c1e90
void MirenEffSetConstantAttr(unsigned long offAttr, unsigned long onAttr)
{
	OnControl3D(4);
	njSetConstantAttr(~offAttr, onAttr);
}

// FUNCTION: SADX 0x008c1ec0
void MirenEffChangeAlpha(float alpha)
{
	___njColorBlendingMode(0, 8);
	___njColorBlendingMode(1, 6);
	OffControl3D(0x20);
	OnControl3D(0x10);
	MirenEffSetConstantAttr(0, 0x100000);
	DAT_04c2ea78 = alpha;
	___njSetConstantMaterial((struct NJS_ARGB *)&DAT_04c2ea78);
}
