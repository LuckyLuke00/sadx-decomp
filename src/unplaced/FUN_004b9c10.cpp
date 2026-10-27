#include "decls.h"

// FUNCTION: SADX 0x004b9c10
void FUN_004b9c10(struct FileSelWk *param_1)
{
	ghSetPvrTexMaterial(-1);
	___njSetTexture(&texlist_ava_vmssel);
	DrawTitleBack(0.0f * ScreenRaitoX, ScreenRaitoX * 38.0f, param_1->BaseZ + -8.0f, ScreenRaitoX * 564.0f, ScreenRaitoY * 41.0f);
	ghDrawPvrTextureS(8, ScreenRaitoX * 42.0f, ScreenRaitoY * 46.0f, param_1->BaseZ + -14.0f, ScreenRaitoX, ScreenRaitoY);
	ghSetPvrTexMaterial(0x78004fff);
	DrawShadowWindow(ScreenRaitoX * 47.0f, ScreenRaitoY * 84.0f, param_1->BaseZ + -6.0f, ScreenRaitoX * 200.0f, ScreenRaitoX * 340.0f);
	AvaDrawInfo(param_1);
}
