#include "decls.h"
#include "../advertise.h"
#include <stdlib.h>
#include <string.h>

// FUNCTION: SADX 0x005f37e0
void FUN_005f37e0(struct TitleMenuWk *param_1)
{
	signed char local_18[5];
	signed char local_5i = 0;
	signed char local_cj[3];
	local_18[local_5i] = -1;
	switch (param_1->SubMode)
	{
	case 0:
		param_1->SubMode = (TitleMenuSbMdEnum)1;
	case 1:
		if (Magic::Base::App::Get("NextMode"))
		{
		if (FUN_00405f00()->FUN_00424b40()->FUN_00431c60((SOCController::ControllerButton)FUN_00405f00()->FUN_00424a70()) ||
			 FUN_00405f00()->FUN_00424b40()->FUN_00431c60((SOCController::ControllerButton)0))
		{
			if (Magic::Base::App::Get("NextMode") == -1)
				exit(1);
			if (Magic::Base::App::Get("NextMode") == 1)
				CharSelAdvaModeProcedure((AdvaModeEnum)8);
			else
				CmnAdvaModeProcedure((AdvaModeEnum)Magic::Base::App::Get("NextMode"));
			param_1->SubMode = (TitleMenuSbMdEnum)6;
		}
		}
		if (Magic::Base::App::Get("PreMode") && FUN_00405f00()->FUN_00424b40()->FUN_00431c60((SOCController::ControllerButton)FUN_00405f00()->FUN_00424a80()))
		{
			CmnAdvaModeProcedure((AdvaModeEnum)Magic::Base::App::Get("PreMode"));
			param_1->SubMode = (TitleMenuSbMdEnum)6;
		}
		if (GetStatAdvaBGM() == 5)
		{
			if (GetDialogNoKeyTime() >= 480)
			{
				DAT_05ccca18.lastPlayer = 0;
				AvaExtractFile();
				DAT_05cd0f30 = DAT_05ccca18;
				param_1->SubMode = (TitleMenuSbMdEnum)3;
			}
		}
		else
			SetDialogNoKeyTime(0);
		break;
	case 2:
	{
		signed char local_19 = GetDialogStat();
		if (local_19 >= 0)
		{
			switch (local_19)
			{
			case 0:
				CharSelAdvaModeProcedure((AdvaModeEnum)3);
				DAT_05cd14e1 = 0;
				param_1->SubMode = (TitleMenuSbMdEnum)6;
				break;
			case 1:
				CharSelAdvaModeProcedure((AdvaModeEnum)9);
				DAT_05cd14e1 = 1;
				param_1->SubMode = (TitleMenuSbMdEnum)6;
				break;
			case 2:
				CmnAdvaModeProcedure(param_1->NextModeSub);
				param_1->SubMode = (TitleMenuSbMdEnum)6;
				break;
			default:
				param_1->SubMode = (TitleMenuSbMdEnum)5;
				break;
			}
		}
		else if (GetStatAdvaBGM() == 5)
		{
			if (GetDialogNoKeyTime() >= 480)
				param_1->SubMode = (TitleMenuSbMdEnum)3;
		}
		else
			SetDialogNoKeyTime(0);
		break;
	}
	case 3:
		if (CloseDialog())
		{
			param_1->Cnt = 0;
			param_1->SubMode = (TitleMenuSbMdEnum)4;
		}
		break;
	case 4:
		if (param_1->Cnt++ >= 20)
		{
			*(int *)((char *)DAT_05cda18c->awp + 0x10) = 107;
			CmnAdvaModeProcedure((AdvaModeEnum)0);
			param_1->SubMode = (TitleMenuSbMdEnum)6;
		}
		break;
	case 5:
		if (AvaGetPutiEnable())
			AdvaOpenDialogCsrLet((DiaTypeEnum)3, (signed char)param_1->SelMenu, local_18);
		else
			AdvaOpenDialogCsrLet((DiaTypeEnum)3, (signed char)param_1->SelMenu, local_18);
		param_1->SubMode = (TitleMenuSbMdEnum)1;
		break;
	}
}

