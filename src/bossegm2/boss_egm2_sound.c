#include "decls.h"
extern char DAT_060b9a1c;
extern int DAT_009bf710[5];
extern int DAT_060b9a18;
extern char DAT_060b9a14;

// FUNCTION: SADX 0x006c5830
void Egm2SoundInit()
{
	DAT_060b9a18 = 0;
	DAT_060b9a14 = 0;
}

// FUNCTION: SADX 0x006c5840
void Egm2WeakSESet()
{
	DAT_060b9a14 = 0x3c;
}

// FUNCTION: SADX 0x006c5850
void Egm2WeakSeExe()
{
	if (DAT_060b9a18 != 0)
	{
		DAT_060b9a14--;
		if (DAT_060b9a14 > 0)
			return;
		dsStop_num(0x1de);
		DAT_060b9a18 = 0;
	}
	else
	{
		if (DAT_060b9a14 <= 0)
			return;
		dsPlay_iloop(0x1de, 0, 3, 0);
		DAT_060b9a18 = 1;
	}
}

// FUNCTION: SADX 0x006c58b0
void Egm2MessageSet(unsigned char no)
{
	if (no < 5)
		Serif_Play(DAT_009bf710[no]);
}

// FUNCTION: SADX 0x006c5a10
void Egm2TikalEnd()
{
	TikalBossKill();
}

// FUNCTION: SADX 0x006c5a20
void Egm2TentouCounterSet()
{
	DAT_060b9a1c++;
}
