#include "decls.h"
extern char DAT_060d0db8[0x3c];
extern char DAT_060d0df8[0x4b0];
void ObjectSkydeck_OCM(struct task *tp);
extern struct task *DAT_060d12a8;

// FUNCTION: SADX 0x0084c050
void ObjectSkydeck_OCM(struct task *tp)
{
	if (DAT_060d12a8 == tp)
	{
		DAT_060d12a8 = NULL;
	}
}

// STUB: SADX 0x0084c070
void OCMref(struct task *tp)
{
}

// STUB: SADX 0x0084c0a0
struct OCMDATA *OCMregister(struct taskwk *otwp)
{
	return (struct OCMDATA *)0;
}

// STUB: SADX 0x0084c110
long OCMunregister(struct OCMDATA *ocmdata)
{
	return (long)0;
}

// FUNCTION: SADX 0x0084c130
struct OCMDATA *OCMsearchRideobj()
{
    int var1;
    struct OCMDATA *var2;
    var2 = (struct OCMDATA *)DAT_060d0df8;
    for (var1 = 0; var1 < 100; var1++)
    {
        if (*(int *)var2 != 0)
        {
            if ((*(unsigned char *)((char *)var2 + 9) & 1) != 0)
                return var2;
        }
        var2 = (struct OCMDATA *)((char *)var2 + 0xc);
    }
    return NULL;
}

// STUB: SADX 0x0084c3e0
struct OCMDATA *OCMsearchNearobjByTypePosRangeFlagmask(signed char stype, struct NJS_POINT3 *spos, float range, float rangey, signed char sflag, signed char mask)
{
	return (struct OCMDATA *)0;
}

// FUNCTION: SADX 0x0084c4d0
struct OCMDATA *OCMsearchObjByTypeFlagmaskNum(signed char stype, signed char sflag, signed char mask, signed char snum)
{
	struct OCMDATA *var1 = (struct OCMDATA *)DAT_060d0df8;
	int var2;

	for (var2 = 0; var2 < 0x64; var2++)
	{
		if (*(int *)var1 != 0)
		{
			if (*(char *)((char *)var1 + 0xa) == stype)
			{
				if ((*(char *)((char *)var1 + 9) & mask) == (sflag & mask))
				{
					if (*(char *)((char *)var1 + 8) == snum)
					{
						return var1;
					}
				}
			}
		}
		var1 = (struct OCMDATA *)((char *)var1 + 0xc);
	}
	return 0;
}

// FUNCTION: SADX 0x0084c520
long RegisterAnimCallbackFunc(long (*pfunc)(void *, int, long *), void *phint)
{
	if (pfunc != 0)
	{
		int var1;
		long *var2 = (long *)DAT_060d0db8;
		for (var1 = 0; var1 < 5; var1++)
		{
			if (var2[0] == 0)
			{
				var2[0] = (long)pfunc;
				var2[1] = 0;
				var2[2] = (long)phint;
				return 1;
			}
			var2 += 3;
		}
	}
	return 0;
}
