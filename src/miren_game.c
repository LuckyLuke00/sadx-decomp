#include "decls.h"

// FUNCTION: SADX 0x008cb810
void MirenGameChangeAct(int actDiff, int bgmId)
{
	MirenSoundFinishBgm();
	LandChangeStage((short)actDiff);
	AddSetStage((short)actDiff);
	AddCameraStage((short)actDiff);
	AdvanceAct((short)actDiff);
	MirenPlyInitPlayerPos(0);
	if (bgmId >= 0)
	{
		MirenSoundInitBgm(bgmId);
	}
}
