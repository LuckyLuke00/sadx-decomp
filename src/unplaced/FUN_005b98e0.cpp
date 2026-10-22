#include "decls.h"
struct GHPARTICLE_INFO;
extern struct task *DAT_05edc12c;
extern struct GHSPRITE_ANIM_TABLE animtable_part[1];
void ghSpriteAnimTableInit(struct NJS_TEXLIST *pList, struct GHSPRITE_ANIM_TABLE *pTable, int flag);
struct task *ghParticleControlSet(int nMax, struct GHPARTICLE_INFO *pInfo, struct GHSPRITE_ANIM_TABLE *pAnimTable, long (*exec)(struct GHPARTICLE *, struct GHPARTICLE_INFO *, struct GHSPRITE_ANIM_TABLE *));
void FUN_005b9900(void);
extern struct NJS_TEXLIST texlist_e102hit;
extern struct GHSPRITE_ANIM_TABLE animtable_hit[1];

// FUNCTION: SADX 0x005b98e0
void FUN_005b98e0(void)
{
	ghSpriteAnimTableInit(&texlist_e102hit, &animtable_hit[0], 0);
	FUN_005b9900();
}

// FUNCTION: SADX 0x005b9900
void FUN_005b9900(void)
{
	float local_cg;
	float local_8g;
	if (DAT_05edc12c == 0)
	{
		ghSpriteAnimTableInit(&texlist_e102hit, &animtable_part[0], 0);
		local_cg = 0.03f;
		local_8g = 0.0f;
		DAT_05edc12c = ghParticleControlSet(0x28, (struct GHPARTICLE_INFO *)&local_cg, &animtable_part[0], 0);
	}
}
