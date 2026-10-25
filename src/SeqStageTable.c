#include "decls.h"
extern struct SEQ_SECTIONTBL seqSectionSonic[];
extern struct SEQ_SECTIONTBL seqSectionMiles[];
extern struct SEQ_SECTIONTBL seqSectionKnuckles[];
extern struct SEQ_SECTIONTBL seqSectionAmy[];
extern struct SEQ_SECTIONTBL seqSectionE102[];
extern struct SEQ_SECTIONTBL seqSectionBig[];
extern struct SEQ_SECTIONTBL seqSectionLast[];
extern unsigned char DAT_05bb00a8;

// FUNCTION: SADX 0x005b59a0
struct SEQ_SECTIONTBL *SeqGetSectionList(long playerno)
{
	if (DAT_05bb00a8 != 0)
	{
		return seqSectionLast;
	}
	switch (playerno)
	{
	case 0:
		return seqSectionSonic;
	case 2:
		return seqSectionMiles;
	case 3:
		return seqSectionKnuckles;
	case 5:
		return seqSectionAmy;
	case 6:
		return seqSectionE102;
	case 7:
		return seqSectionBig;
	}
	return 0;
}

// FUNCTION: SADX 0x005b5a20
long SeqGetSectionNumber(long playerno)
{
	if (DAT_05bb00a8 != 0)
	{
		return 4;
	}
	switch (playerno)
	{
	case 0:
		return 0x10;
	case 2:
		return 0xc;
	case 3:
		return 0xc;
	case 5:
		return 9;
	case 6:
		return 9;
	case 7:
		return 8;
	}
	return 0;
}
