#include "decls.h"
void CreateSayounaraWindow(float xpos, float ypos, unsigned short WaitTime);
extern void *DAT_05b330fc;

// FUNCTION: SADX 0x0047f000
void SayounaraWindowDestructor(struct task *tp)
{
	Free(tp->awp);
	tp->awp = 0;
	DAT_05b330fc = 0;
}

// STUB: SADX 0x0047f020
void CreateSayounaraWindow(float xpos, float ypos, unsigned short WaitTime)
{
}
