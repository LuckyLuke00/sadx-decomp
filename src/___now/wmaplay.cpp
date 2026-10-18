#include "decls.h"

extern int DAT_05b3dfc4;
extern int DAT_05b3dfd0;
extern int DAT_05b3dfe0;
extern int DAT_05b3dfe4;
extern int DAT_05b3dfec;

// FUNCTION: SADX 0x004ab380
void voicevolchange(int volume)
{
	DAT_05b3dfc4 = VOICE_VOLUME;
	if (VOICE_VOLUME > volume)
	{
		VOICE_VOLUME = VOICE_VOLUME - volume;
	}
}

// FUNCTION: SADX 0x004ab3b0
void voicevolresume()
{
	VOICE_VOLUME = DAT_05b3dfc4;
}

// FUNCTION: SADX 0x004abae0
int wmaplaystat()
{
	return DAT_05b3dfd0;
}

// FUNCTION: SADX 0x004abe50
void setPreflagstat()
{
	DAT_05b3dfe0 = DAT_05b3dfe4;
	DAT_05b3dfd0 = DAT_05b3dfec;
}
