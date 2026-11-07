#include "decls.h"
extern struct PDS_PERIPHERAL *DAT_05b93264[4];

// FUNCTION: SADX 0x008d57b0
int FUN_008d57b0()
{
	return DAT_05b93264[3]->on;
}

// FUNCTION: SADX 0x008d57c0
long FUN_008d57c0()
{
	return DAT_05b93264[3]->press;
}

// FUNCTION: SADX 0x008d57d0
long FUN_008d57d0()
{
	return DAT_05b92e44;
}
