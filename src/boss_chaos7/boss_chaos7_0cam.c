#include "decls.h"
extern float DAT_060c365c;
extern struct C7ACAM_PARAM *DAT_060c3654;
extern unsigned char DAT_060c3645;
extern struct _camcontwk *camcont_wp;
extern struct taskwk *DAT_05baf368[8];

// FUNCTION: SADX 0x006fd550
void CameraChaos7_0Normal(struct _OBJ_CAMERAPARAM *pParam)
{
	CameraChaos7_0Normal_sub(pParam);
}

// FUNCTION: SADX 0x006fd780
void SetCameraChaos7_0Adv(struct C7ACAM_PARAM *cp)
{
	DAT_060c3654 = cp;
	DAT_060c365c = 0.0f;
	CameraSetCollisionCameraFunc(CameraChaos7_0Adv, 0, 2);
	DAT_060c3645 = 0;
}

// FUNCTION: SADX 0x006fd7b0
void CameraChaos7_0Path(struct _OBJ_CAMERAPARAM *pParam)
{
	short *var1 = (short *)DAT_05baf368[0];
	*(float *)((char *)camcont_wp + 0x18) = *(float *)((char *)var1 + 0x20);
	*(float *)((char *)camcont_wp + 0x1c) = *(float *)((char *)var1 + 0x24);
	*(float *)((char *)camcont_wp + 0x20) = *(float *)((char *)var1 + 0x28);
	*(float *)((char *)pParam + 8) = *(float *)((char *)var1 + 0x24);
	*(float *)((char *)camcont_wp + 0xc) = *(float *)((char *)pParam + 4);
	*(float *)((char *)camcont_wp + 0x10) = *(float *)((char *)pParam + 8);
	*(float *)((char *)camcont_wp + 0x14) = *(float *)((char *)pParam + 0xc);
}
