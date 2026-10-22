#include "decls.h"
extern struct _camcontwk *camcont_wp;
extern short *DAT_05baf368;

// FUNCTION: SADX 0x006fd550
void CameraChaos7_0Normal(struct _OBJ_CAMERAPARAM *pParam)
{
	CameraChaos7_0Normal_sub(pParam);
}

// STUB: SADX 0x006fd780
void SetCameraChaos7_0Adv(struct C7ACAM_PARAM *cp)
{
}

// FUNCTION: SADX 0x006fd7b0
void CameraChaos7_0Path(struct _OBJ_CAMERAPARAM *pParam)
{
	short *var1 = DAT_05baf368;
	*(float *)((char *)camcont_wp + 0x18) = *(float *)((char *)var1 + 0x20);
	*(float *)((char *)camcont_wp + 0x1c) = *(float *)((char *)var1 + 0x24);
	*(float *)((char *)camcont_wp + 0x20) = *(float *)((char *)var1 + 0x28);
	*(float *)((char *)pParam + 8) = *(float *)((char *)var1 + 0x24);
	*(float *)((char *)camcont_wp + 0xc) = *(float *)((char *)pParam + 4);
	*(float *)((char *)camcont_wp + 0x10) = *(float *)((char *)pParam + 8);
	*(float *)((char *)camcont_wp + 0x14) = *(float *)((char *)pParam + 0xc);
}
