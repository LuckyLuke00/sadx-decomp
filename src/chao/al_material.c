#include "decls.h"

// STUB: SADX 0x00450310
void AL_MatSetChaoColor(struct task *tp, short ColorNum)
{
}

// STUB: SADX 0x004506e0
void AL_MaterialInit(struct task *tp)
{
}

// FUNCTION: SADX 0x00450710
void AL_MatChangeObjectTexture(struct al_object *pObject, unsigned short TexId)
{
	if (pObject != NULL && pObject->pModel != NULL)
	{
		AL_MatChangeModelTexture(pObject->pModel, TexId);
	}
}

// FUNCTION: SADX 0x00450730
void FUN_00450730(struct al_model *param_1)
{
	if (param_1 != 0 && param_1->PList != 0)
	{
		AL_MatResetModelTexture((struct al_model *)param_1->PList);
	}
}

// FUNCTION: SADX 0x00450750
void AL_MatChangeObjectTexture2(struct al_object *pObject, const unsigned short *TexIdList, long nbTex)
{
	if ((pObject != 0) && (pObject->pModel != 0))
	{
		AL_MatChangeModelTexture2(pObject->pModel, TexIdList, nbTex);
	}
}

// STUB: SADX 0x00450770
void FUN_00450770(struct al_model *pModel)
{
}

// STUB: SADX 0x00450790
void AL_MatDisableChaoEnvironmentMapping(struct task *tp)
{
}
