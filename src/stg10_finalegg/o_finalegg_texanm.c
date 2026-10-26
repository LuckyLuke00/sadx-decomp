#include "decls.h"
static void Disp(struct task *tp);
static void Exec(struct task *tp);
extern struct NJS_TEXLIST texlist_obj_finalegg;
extern struct NJS_TEXLIST texlist_unyo;
void FUN_007d21b0(...);

// FUNCTION: SADX 0x0088e530
void TexMakeInit()
{
	texlist_unyo.textures = (NJS_TEXNAME *)((char *)texlist_obj_finalegg.textures + 0x7f8);
	texlist_unyo.nbTexture = 6;
}

#pragma optimize("", off)
// STUB: SADX 0x0088e550
static void Disp(struct task *tp)
{
}
#pragma optimize("", on)

// FUNCTION: SADX 0x0088e660
static void Exec(struct task *tp)
{
	Disp(tp);
}

// FUNCTION: SADX 0x0088e670
void ObjectFinalEggTexAnime(struct task *tp)
{
	tp->twp->mode = 0;
	texlist_unyo.textures = (NJS_TEXNAME *)((char *)texlist_obj_finalegg.textures + 0x7f8);
	texlist_unyo.nbTexture = 6;
	tp->exec = Exec;
	tp->disp = Disp;
	tp->dest = (void (__cdecl *)(struct task *))FUN_007d21b0;
}
