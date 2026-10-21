#include "decls.h"
#include <stdarg.h>
#include <stdio.h>
extern int zcompflag;

void FUN_00422560(int param_1);

// GLOBAL: SADX 0x05ab1564
int zcompflag;

// STUB: SADX 0x00404ef0
void ___OutputDebugString(char *str, ...)
{
}

// STUB: SADX 0x00404f10
void CalcScreenRaito_SPR2D_CR(struct NJS_SPRITE *spr)
{
}

// STUB: SADX 0x00404f50
void FUN_00404f50(float *param_1)
{
}

// FUNCTION: SADX 0x00405350
void npSetZCompareMode(int flag)
{
	zcompflag = flag;
}

// FUNCTION: SADX 0x00405360
void npSetZCompare()
{
	FUN_00422560(zcompflag);
}

// FUNCTION: SADX 0x00405370
long dsSimpleDrawModel(struct NJS_MODEL *model)
{
	njDrawModel(model);
	return 0;
}
