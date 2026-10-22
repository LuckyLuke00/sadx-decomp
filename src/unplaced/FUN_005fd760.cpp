#include "decls.h"
struct task;
struct TvSettingWk;
void FUN_005fd7e0(struct TvSettingWk *param_1);

// FUNCTION: SADX 0x005fd760
void FUN_005fd760(struct task *param_1)
{
	struct TvSettingWk *local_8;

	local_8 = (struct TvSettingWk *)param_1->awp;
	if (*(int *)((char *)local_8 + 0x14) == 0)
	{
		return;
	}
	ghDefaultBlendingMode();
	ghSetPvrTexBaseColor(*(unsigned long *)((char *)local_8 + 0x14));
	if (*(int *)((char *)local_8 + 0x18) != 4)
	{
		DrawSkyBg(*(float *)((char *)local_8 + 0xc) + -2.0);
	}
	FUN_005fd7e0(local_8);
	DrawTvSettingWnd(local_8);
}
