#include <stdlib.h>
#include "decls.h"

extern unsigned short DAT_05b9d724;
extern unsigned short DAT_05b9d744;
extern unsigned char DAT_05b42c1c;
extern unsigned char DAT_05b3ea25;

int FUN_005030d0();
void FUN_004c38e0();

// FUNCTION: SADX 0x004c4fa0
void PauseEnable()
{
	ssPauseEnable = 1;
}

// FUNCTION: SADX 0x004c4fb0
void PauseDisable()
{
	ssPauseEnable = 0;
}

// FUNCTION: SADX 0x004c4fc0
void StartTheFirstGame()
{
	int local;

	InitGCMemocaState();
	SetPlayerNumberForGame(0);
	InitTime();
	InitScore();
	SeqInit();
	DAT_05b42c1c = 0;
	InitGame();
	local = FUN_005030d0();
	DAT_05b3ea25 = 0;
	srand(0xdead0cab);
}

// FUNCTION: SADX 0x004c5120
void GM_WaitEventS(struct task *tp)
{
	ADX_Close();
	EV_Load2(((struct taskwk *)tp->twp)->wtimer);
	EV_Exec2();
	tp->exec = GM_WaitEvent;
}

// FUNCTION: SADX 0x004c5150
void GM_WaitEvent(struct task *tp)
{
	if (EV_CheckCansel() == 0)
	{
		DestroyTask(tp);
		PadReadOn();
		if ((short)DAT_05b9d724 != 0x13)
		{
			PauseEnable();
		}
		WakeTimer();
	}
}

// FUNCTION: SADX 0x004c9c90
void FUN_004c9c90()
{
	GM_SetNextAdventureStage(DAT_05b9d724, DAT_05b9d744);
}
