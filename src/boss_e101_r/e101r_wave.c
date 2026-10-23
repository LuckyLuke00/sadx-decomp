#include "decls.h"
extern struct NJS_TEXLIST _texlist_e101r;
extern struct GHSPRITE_ANIM_TABLE animtable_wave[1];
extern struct WIDELINE_TEXDATA wline_pulse;
void ghSpriteAnimTableInit(struct NJS_TEXLIST *pList, struct GHSPRITE_ANIM_TABLE *pTable, int flag);

// FUNCTION: SADX 0x0070e750
void E101R_WaveShotInit()
{
	ghSpriteAnimTableInit(&_texlist_e101r, &animtable_wave[0], 0);
	wline_pulse.index = *(int *)*(int **)((char *)_texlist_e101r.textures + 0x1ac);
}

// FUNCTION: SADX 0x0070e9e0
void E101R_WaveShotSetMode(struct task *pTask, enum E101R_WAVE_MODE nMode)
{
	pTask->awp->work.ul[0] = nMode;
}

// FUNCTION: SADX 0x0070e9f0
void E101R_WaveShotSetValue(struct task *pTask, struct NJS_POINT3 *pVec, float fSize)
{
	struct anywk *var1 = pTask->awp;
	*(float *)((char *)var1 + 0x64) = pVec->x * 10.0f;
	*(float *)((char *)var1 + 0x68) = pVec->y * 10.0f;
	*(float *)((char *)var1 + 0x6c) = pVec->z * 10.0f;
	*(float *)((char *)var1 + 0x78) = fSize;
}
