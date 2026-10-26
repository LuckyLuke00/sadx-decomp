#include "decls.h"
void BookDisplayer(struct task *tp);

// STUB: SADX 0x004543a0
void ALO_ShabonDisplayer(struct task *tp)
{
}

// STUB: SADX 0x00454480
void ALO_ShabonExecutor(struct task *tp)
{
}

// FUNCTION: SADX 0x00454540
void ALO_ShabonDestructor(struct task *tp)
{
	if (tp->mwp != 0)
	{
		syFree(tp->mwp);
		tp->mwp = 0;
	}
}

// STUB: SADX 0x00454560
struct task *ALO_CreateShabon(struct NJS_POINT3 *pPos, struct NJS_POINT3 *pVelo)
{
	return (struct task *)0;
}

// STUB: SADX 0x004548a0
long ALBHV_Houki(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00454970
long ALBHV_Garagara(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00454a40
long ALBHV_Hanabi(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x00454b10
void BookExecutor(struct task *tp)
{
}

// STUB: SADX 0x00454c10
void BookDisplayer(struct task *tp)
{
}

// STUB: SADX 0x00455110
long ALBHV_Doll(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x004551f0
long ALBHV_Hopping(struct task *tp)
{
	return (long)0;
}

// STUB: SADX 0x004552c0
long AL_DecideBehaviorSToy(struct task *tp)
{
	return (long)0;
}
