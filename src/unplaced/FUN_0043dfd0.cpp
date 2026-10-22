#include "decls.h"
enum eCHAO_STAGE_NUMBER;

// FUNCTION: SADX 0x0043dfd0
void FUN_0043dfd0(enum eCHAO_STAGE_NUMBER param_1)
{
	if (ChaoStageNumber != param_1)
	{
		ChaoOldStageNumber = ChaoStageNumber;
		ChaoNextStageNumber = param_1;
	}
}

// FUNCTION: SADX 0x0043dff0
void FUN_0043dff0()
{
	ChaoStageNumber = ChaoNextStageNumber;
}
