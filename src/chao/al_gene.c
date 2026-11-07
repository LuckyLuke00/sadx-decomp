#include "decls.h"
extern "C" int rand(void);

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

// FUNCTION: SADX 0x0044a260
void AL_GeneCreatePlane(struct AL_GENE *pGene)
{
	int var1;
	int var2;
	int var3;
	int var4;
	float var5;
	float var6;
	float var7;
	AL_GeneCreate(pGene);
	var1 = rand();
	var5 = (float)var1 * 3.0517578e-5f;
	var6 = var5 - 0.5f;
	var7 = var6 * 0.9f;
	var2 = (int)(var7 * 45.0f);
	pGene->Personality[1][1] = (signed char)var2;
	pGene->Personality[1][0] = (signed char)var2;
	var3 = rand();
	var5 = (float)var3 * 3.0517578e-5f;
	var6 = var5 - 0.5f;
	var7 = var6 * 0.9f;
	var4 = (int)(var7 * 45.0f);
	pGene->Personality[2][1] = (signed char)var4;
	pGene->Personality[2][0] = (signed char)var4;
	var1 = rand();
	var5 = (float)var1 * 3.0517578e-5f;
	var6 = var5 - 0.5f;
	var7 = var6 * 0.9f;
	var2 = (int)(var7 * 45.0f);
	pGene->Personality[0][1] = (signed char)var2;
	pGene->Personality[0][0] = (signed char)var2;
}
