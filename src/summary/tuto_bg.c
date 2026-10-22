#include "decls.h"
extern unsigned char DAT_05cd14ea;
extern char *TutorialBgFilenameTbl[7];
extern struct NJS_TEXLIST *TutorialBgTexlistTbl[7];

// FUNCTION: SADX 0x004969e0
void SetTutorialBgColor()
{
	___njSetBackColor(0xffffffff, 0xffffffff, 0xffffffff);
}

// FUNCTION: SADX 0x004969f0
struct NJS_TEXLIST *LoadTutorialBgTexture(int advplno)
{
	int var1;
	struct NJS_TEXLIST *var2;

	if (DAT_05cd14ea == 2)
	{
		var1 = 6;
	}
	else
	{
		var1 = advplno;
	}

	var2 = TutorialBgTexlistTbl[var1];
	texLoadTexturePvmFile(TutorialBgFilenameTbl[var1], var2);
	return var2;
}

// STUB: SADX 0x00496a20
void TutorialBgTask(struct task *tp)
{
}

// FUNCTION: SADX 0x00496a80
void SetTutoBgFadeMode(struct task *tp)
{
	tp->twp->mode = 1;
}
