#include "decls.h"
struct sp_link *SpCreateLinkW(struct sp_info *info, unsigned long wksize);
extern short DAT_05b9d724;
extern short DAT_05b9d744;

// FUNCTION: SADX 0x005a6a40
void SetParticle()
{
	unsigned short local_8g;
	struct particle_entry ** local_cg;
	EntryParticle((struct particle_entry **)&ListofParticleFixed);
	local_8g = (unsigned short)((((int)((short)DAT_05b9d724 << 8) | (int)(short)DAT_05b9d744) & 0xff00) >> 8);
	local_cg = ListofListofParticle[local_8g];
	if (local_cg != 0)
	{
		EntryParticle(local_cg);
	}
	return;
}

// FUNCTION: SADX 0x005a6aa0
void EntryParticle(struct particle_entry **plistlist)
{
	struct particle_entry *local_8;

	while (*plistlist != 0)
	{
		local_8 = *plistlist;
		local_8->link = SpCreateLinkW((struct sp_info *)local_8, *(unsigned long *)((char *)local_8 + 4));
		if (*(int *)((char *)local_8 + 8) != 0)
		{
			(*(void (**)(struct sp_link *))(int *)local_8)(local_8->link);
		}
		plistlist = plistlist + 1;
	}
}
