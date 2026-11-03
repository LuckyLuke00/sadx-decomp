#include "decls.h"
#include "../advertise.h"

// FUNCTION: SADX 0x0042b420
SOCFileStream::SOCFileStream()
{
	local_0 = 0;
	local_4 = 0;
}

// FUNCTION: SADX 0x0042b430
SOCFileStream::~SOCFileStream()
{
	if (local_0 != 0)
	{
		_SOCFree(local_0, "..\\src\\soc\\SOCFileStream.cpp", 17);
		local_0 = 0;
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
	local_4 = local_50.FUN_009285c0();
	if (local_0 != 0)
	{
		_SOCFree(local_0, "..\\src\\soc\\SOCFileStream.cpp", 32);
		local_0 = 0;
	}
	local_0 = _SOCMalloc(local_4, "..\\src\\soc\\SOCFileStream.cpp", 33);
	var1 = local_50.FUN_009286c0(local_0, local_4, 0);
	if (var1 == 0)
	{
		return false;
	}
	return true;
}
