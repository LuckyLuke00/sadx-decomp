#include "decls.h"

// FUNCTION: SADX 0x004b9c10
void FUN_004b9c10(struct FileSelWk *param_1)
{
	ghSetPvrTexMaterial(-1);
	___njSetTexture(&texlist_ava_vmssel);
	DrawTitleBack(0.0 * ScreenRaitoX, ScreenRaitoX * 38.0, *(float *)((char *)param_1 + 0xc) + -8.0, ScreenRaitoX * 564.0, ScreenRaitoY * 41.0);
	((void (*)(int, float, float, float, float, float))ghDrawPvrTexture)(8, ScreenRaitoX * 42.0, ScreenRaitoY * 46.0, *(float *)((char *)param_1 + 0xc) + -14.0, ScreenRaitoX, ScreenRaitoY);
	ghSetPvrTexMaterial(0x78004fff);
	DrawShadowWindow(ScreenRaitoX * 47.0, ScreenRaitoY * 84.0, *(float *)((char *)param_1 + 0xc) + -6.0, ScreenRaitoX * 200.0, ScreenRaitoX * 340.0);
	AvaDrawInfo(param_1);
}
