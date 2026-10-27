#include "decls.h"

// STUB: SADX 0x00449b00
void AL_CreateChildGene(struct task *pMotherTask, struct task *pFatherTask, struct AL_GENE *pChildGene)
{
}

// FUNCTION: SADX 0x0044a1e0
void AL_GeneAnalyze2(struct AL_GENE *pGene, struct CHAO_PARAM_GC *pParam)
{
	int var1;

	pParam->place = AL_GetPreStageNumber();
	AL_GeneAnalyzeCommon(pGene, pParam);
	for (var1 = 0; var1 < 8; var1++)
	{
		*(char *)((char *)pParam + 0x4e4 + var1 - 0x3c8) = 0xff;
		*(char *)((char *)pParam + 0x4e4 + var1) = 0xff;
	}
}

// STUB: SADX 0x0044a220
void AL_GeneAnalyze(struct task *tp)
{
}

// STUB: SADX 0x0044a260
void AL_GeneCreatePlane(struct AL_GENE *pGene)
{
}
