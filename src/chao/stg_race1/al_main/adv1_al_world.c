#include "decls.h"
extern long DAT_05b36090;
extern struct chao_colliwk *DAT_05b36068;

// FUNCTION: SADX 0x00493700
struct chao_colliwk *AL_GetObjectEntryList()
{
	return DAT_05b36068;
}

// FUNCTION: SADX 0x00493710
long AL_GetChaoEntryNum()
{
	return DAT_05b36090;
}
