#include "decls.h"

// STUB: SADX 0x0043cd80
unsigned short AL_KW_GetPlayerCharacterNum()
{
	return (unsigned short)0;
}

// STUB: SADX 0x0043cde0
void AL_KW_InitPlayerKnowledgeDX(struct task *pChaoTask)
{
}

// STUB: SADX 0x0043ce60
signed char AL_KW_GetPlayerLike(struct task *pChaoTask)
{
	return (signed char)0;
}

// STUB: SADX 0x0043ce80
unsigned char AL_KW_GetPlayerFear(struct task *pChaoTask)
{
	return (unsigned char)0;
}

// STUB: SADX 0x0043cea0
void AL_KW_AddPlayerFear(struct task *pChaoTask, long add)
{
}

// STUB: SADX 0x0043cf50
unsigned short AL_KW_GetPlayerDistance(struct task *pChaoTask)
{
	return (unsigned short)0;
}

// FUNCTION: SADX 0x0043cf70
unsigned short AL_KW_GetPlayerMeet(struct task *pChaoTask)
{
	struct CHAO_PARAM_GC *var1 = (struct CHAO_PARAM_GC *)(*(int **)((char *)pChaoTask->twp + 0x6c));
	unsigned short var2 = AL_KW_GetPlayerCharacterNum();
	return *(unsigned short *)((char *)var1 + 0x500 + var2 * 6);
}

// STUB: SADX 0x0043cf90
void AL_KW_MeetPlayer(struct task *pChaoTask)
{
}

// FUNCTION: SADX 0x0043d340
void AL_KW_ArtFlagOn(struct task *pChaoTask, long Kind)
{
	struct taskwk *var1 = pChaoTask->twp;
	unsigned char *var2 = (unsigned char *)(*(int *)((char *)var1 + 0x6c) + 0x160);
	*var2 |= (unsigned char)(1 << Kind);
}

// FUNCTION: SADX 0x0043d360
void AL_KW_ArtFlagOff(struct task *pChaoTask, long Kind)
{
	struct taskwk *var1 = pChaoTask->twp;
	void *var2 = *(void **)((char *)var1 + 0x6c);
	*(char *)((char *)var2 + 0x160) &= ~(char)(1 << Kind);
}

// STUB: SADX 0x0043d380
long AL_KW_IsArtFlagOn(struct task *pChaoTask, long Kind)
{
	return (long)0;
}

// FUNCTION: SADX 0x0043d3b0
void AL_KW_DanceFlagOn(struct task *pChaoTask, long Kind)
{
	struct taskwk *var1 = pChaoTask->twp;
	void *var2 = *(void **)((char *)var1 + 0x6c);
	*(char *)((char *)var2 + 0x161) |= (1 << Kind);
}

// FUNCTION: SADX 0x0043d3d0
void AL_KW_DanceFlagOff(struct task *pChaoTask, long Kind)
{
	struct taskwk *var1 = pChaoTask->twp;
	void *var2 = *(void **)((char *)var1 + 0x6c);
	*(char *)((char *)var2 + 0x161) &= ~(char)(1 << Kind);
}

// STUB: SADX 0x0043d3f0
long AL_KW_IsDanceFlagOn(struct task *pChaoTask, long Kind)
{
	return (long)0;
}

// FUNCTION: SADX 0x0043d420
void AL_KW_SongFlagOn(struct task *pChaoTask, long Kind)
{
	struct taskwk *var1 = pChaoTask->twp;
	unsigned char *var2 = (unsigned char *)(*(int *)((char *)var1 + 0x6c) + 0x162);
	*var2 |= (unsigned char)(1 << Kind);
}

// FUNCTION: SADX 0x0043d440
void AL_KW_SongFlagOff(struct task *pChaoTask, long Kind)
{
	struct taskwk *var1 = pChaoTask->twp;
	void *var2 = *(void **)((char *)var1 + 0x6c);
	*(char *)((char *)var2 + 0x162) &= ~(char)(1 << Kind);
}

// STUB: SADX 0x0043d460
long AL_KW_IsSongFlagOn(struct task *pChaoTask, long Kind)
{
	return (long)0;
}

// FUNCTION: SADX 0x0043d490
void AL_KW_MusicFlagOn(struct task *pChaoTask, long Kind)
{
	struct taskwk *var1 = pChaoTask->twp;
	void *var2 = *(void **)((char *)var1 + 0x6c);
	*(char *)((char *)var2 + 0x163) |= (1 << Kind);
}

// FUNCTION: SADX 0x0043d4b0
void AL_KW_MusicFlagOff(struct task *pChaoTask, long Kind)
{
	unsigned char *var1 = (unsigned char *)(*(void **)((char *)pChaoTask->twp + 0x6c)) + 0x163;
	*var1 &= ~(unsigned char)(1 << Kind);
}

// STUB: SADX 0x0043d4d0
long AL_KW_IsMusicFlagOn(struct task *pChaoTask, long Kind)
{
	return (long)0;
}

// FUNCTION: SADX 0x0043d500
void AL_KW_SToyFlagOn(struct task *pChaoTask, long Kind)
{
	*(unsigned short *)((char *)*(void **)((char *)pChaoTask->twp + 0x6c) + 0x164) |= (unsigned short)(1 << Kind);
}

// FUNCTION: SADX 0x0043d520
void AL_KW_SToyFlagOff(struct task *pChaoTask, long Kind)
{
	struct CHAO_PARAM_GC *var1 = (struct CHAO_PARAM_GC *)(*(int **)((char *)pChaoTask->twp + 0x6c));
	*(unsigned short *)((char *)var1 + 0x164) &= ~(1 << Kind);
}

// STUB: SADX 0x0043d550
long AL_KW_IsSToyFlagOn(struct task *pChaoTask, long Kind)
{
	return (long)0;
}
