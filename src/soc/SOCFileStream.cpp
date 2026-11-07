#include "decls.h"
#include "../advertise.h"

// FUNCTION: SADX 0x0042b420
SOCFileStream::SOCFileStream()
{
	field_0x0 = 0;
	field_0x4 = 0;
}

// FUNCTION: SADX 0x0042b430
SOCFileStream::~SOCFileStream()
{
	if (field_0x0 != 0)
	{
		_SOCFree(field_0x0, "..\\src\\soc\\SOCFileStream.cpp", 17);
		field_0x0 = 0;
	}
}

// FUNCTION: SADX 0x0042b460
bool SOCFileStream::ReadFile(const std::string& param_1)
{
	std::string local_30 = FUN_0092cd20(param_1);
	Magic::Base::File local_50;
	char var1 = local_50.Open(local_30, 1);
	if (var1 == 0)
	{
		return false;
	}
	field_0x4 = local_50.FUN_009285c0();
	if (field_0x0 != 0)
	{
		_SOCFree(field_0x0, "..\\src\\soc\\SOCFileStream.cpp", 32);
		field_0x0 = 0;
	}
	field_0x0 = _SOCMalloc(field_0x4, "..\\src\\soc\\SOCFileStream.cpp", 33);
	var1 = local_50.FUN_009286c0(field_0x0, field_0x4, 0);
	if (var1 == 0)
	{
		return false;
	}
	return true;
}
