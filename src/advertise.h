#pragma once

#include <math.h>
#include <stdio.h>
#include <string>
#pragma push_macro("_HAS_TR1")
#pragma push_macro("_HAS_TR1_IMPORTS")
#pragma push_macro("_HAS_CPP0X")
#undef _HAS_TR1
#undef _HAS_TR1_IMPORTS
#undef _HAS_CPP0X
#define _HAS_TR1 0
#define _HAS_TR1_IMPORTS 0
#define _HAS_CPP0X 0
#include <vector>
#include <list>
#include <map>
#pragma pop_macro("_HAS_TR1")
#pragma pop_macro("_HAS_TR1_IMPORTS")
#pragma pop_macro("_HAS_CPP0X")

extern const float DAT_0098fa14;
extern const float DAT_0098fc50;

// VTABLE: SADX 0x00956bb4
class SOCController
{
public:
	enum ControllerButton { AXIS_LX = 11, AXIS_LY = 12 };
	virtual ~SOCController() {}
	virtual void FUN_004321e0();
	virtual bool FUN_00431c60(ControllerButton) const;
	virtual bool FUN_00431d10(ControllerButton) const;
	virtual float FUN_00431e50(ControllerButton) const;
	virtual bool FUN_00432010(int, int);
	virtual bool FUN_00431e90();
	virtual bool FUN_00432100(int, int, double);
	virtual bool FUN_00431ee0();
	virtual void* FUN_00431f00(void*);
	virtual void* FUN_00431fa0(void*);
private:
	char field_0x4[0x24];
};

// VTABLE: SADX 0x00956be4
class SOCControllerAll : public SOCController
{
public:
	virtual void FUN_004321e0() {}
	virtual bool FUN_00431c60(ControllerButton) const;
	virtual bool FUN_00431d10(ControllerButton) const;
	virtual float FUN_00431e50(ControllerButton) const { return 0.0f; }
	virtual bool FUN_00432010(int, int) { return false; }
	virtual bool FUN_00431e90() { return false; }
	virtual bool FUN_00432100(int, int, double) { return false; }
	virtual bool FUN_00431ee0() { return false; }
};

namespace Magic
{
namespace Base
{
template<class T> class Singleton;
}
}

class SOCInput
{
public:
	void FUN_00424a90(int param_1, int param_2);
	void FUN_00424ac0();
	SOCController* FUN_00424b40();
private:
	friend class Magic::Base::Singleton<SOCInput>;
	SOCInput();
	int m_ActiveIndex;
	SOCController* m_pController[8];
	char field_0x24[0x28];
};

class DAT_0629c340_0
{
public:
	void FUN_00425db0();
	void FUN_00425e30();
private:
	friend class Magic::Base::Singleton<DAT_0629c340_0>;
	DAT_0629c340_0();
	bool field_0x0;
	char field_0x4[0x90];
	char field_0x94[0x90];
	char field_0x124[0x90];
	void* field_0x1b4;
};

struct LBOnData
{
	wchar_t strRank[16];
	wchar_t strGameRtag[16];
	wchar_t strData[16];
	wchar_t strScore[16];
};

namespace Magic
{
namespace Base
{
class File
{
public:
	File();
	~File();
	long FUN_009285c0();
	bool Open(const std::string& param_1, int param_2);
	void FUN_00435420();
	bool FUN_00928630(int param_1, int param_2);
	bool FUN_009286c0(void* param_1, size_t param_2, unsigned long* param_3);
private:
	FILE** m_pFile;
	char m_FileName[0x1c];
};
class IniFile
{
public:
	IniFile();
	~IniFile();
	int FUN_0092b1b0(const std::string&, const std::string&, const std::string&);
	int FUN_0092b2b0(const std::string&);
private:
	File* Fini;
	std::map<std::string, std::string> FileMap;
	std::string Filename;
	bool blOpenSuccess;
	bool blChanged;
};

template<class T> class Singleton
{
public:
	T* GetSubject()
	{
		if (m_pSubject == 0)
			m_pSubject = new T;
		return m_pSubject;
	}
private:
	T* m_pSubject;
};

class Timer
{
public:
	Timer();
	double FUN_00929760();
private:
	void* m_pTimer;
};
class App
{
public:
	static int Get(const char* param_1);
};
}

namespace MATH
{
class Math
{
public:
	template<class T> static T AngleUniform(T param_1)
	{
		param_1 = (T)fmod(param_1, DAT_0098fc50);
		return param_1 >= 0.0 ? param_1 : param_1 + DAT_0098fc50;
	}
};
}

namespace RenderCore
{
class Resource
{
public:
	Resource() : m_ResType(11), m_ResPool(1), m_pUserData(0), m_ResMask(0) {}
	virtual ~Resource();
protected:
	int m_ResType;
	int m_ResPool;
	int m_pUserData;
	int m_ResMask;
	std::string m_Name;
	std::string m_Path;
};

// VTABLE: SADX 0x00a5ce08
class Texture : public Resource
{
public:
	Texture();
	virtual ~Texture();
	bool Load(void*, int, int, int, int, int);
	void FUN_00922750();
private:
	int m_TexType;
	int m_TexSize;
	int m_TexFlags;
	int m_Width;
	int m_Height;
	int m_Depth;
	int m_Format;
	int m_Usage;
	int m_MipmapLevelCount;
	bool m_IsLocked;
};
}
}

class SOCFile : public Magic::Base::File
{
public:
	bool Open(const std::string& param_1, int param_2);
};

class SOCAudio
{
public:
	void Stop();
	~SOCAudio();
	bool Open(const std::string& param_1);
	void Play(float param_1, int param_2);
};

class SOCIniFile : public Magic::Base::IniFile
{
public:
	SOCIniFile() {}
	~SOCIniFile() {}
	int FUN_0067edf0(const std::string&);
};

class SOCFileStream
{
public:
	SOCFileStream();
	~SOCFileStream();
	bool ReadFile(const std::string&);
	void* FUN_00424960();
	int FUN_0040b8a0();
private:
	void* field_0x0;
	int field_0x4;
};

class SOCSystem
{
public:
	SOCSystem();
	void* FUN_004035e0(const std::string&);
	void* GetFuncAddress(void*, char*);
};

class SOCTimer : public Magic::Base::Timer
{
public:
	int FUN_004caf80();
};

class SOCRender
{
public:
	void SetSpecularEnable(bool param_1);
	void UIShaderSet();
	void FUN_0041b120(int param_1, int param_2);
	// FUNCTION: SADX 0x00419cf0
	void FUN_00419cf0(int param_1)
	{
		field_0x2798 = param_1;
	}
private:
	char field_0x0[0x2798];
	int field_0x2798;
};

extern void* DAT_0629c344;

// FUNCTION: SADX 0x00405f00
inline class SOCInput* FUN_00405f00()
{
	return ((Magic::Base::Singleton<SOCInput>*)&DAT_0629c344)->GetSubject();
}

extern void* DAT_05ab4304;

// FUNCTION: SADX 0x0041a800
inline class SOCTimer* FUN_0041a800()
{
	return ((Magic::Base::Singleton<SOCTimer>*)&DAT_05ab4304)->GetSubject();
}

struct FUN_0040e170_0
{
	std::string field_0x0;
	int field_0x1c;
	int field_0x20;
	FUN_0040e170_0()
	{
		field_0x0 = "ASCII";
		field_0x1c = 0;
		field_0x20 = 0;
	}
};

struct FUN_0040e170_1
{
	void GetTextSize(const wchar_t *param_1, const FUN_0040e170_0& param_2, int& param_3, int& param_4);
};

namespace Magic
{
namespace RenderCore
{
class VertexBuffer
{
public:
	bool Lock(void **param_1, int param_2, int param_3, int param_4);
	void Unlock();
};
class Material
{
public:
	void CommitDeviceShader();
};
}
}

struct FUN_00420960_0
{
	int field_0x0;
	int field_0x4;
	int field_0x8;
	int field_0xc;
	float field_0x10;
	Magic::RenderCore::Texture *field_0x14;
	float field_0x18;
	float field_0x1c;
	float field_0x20;
	float field_0x24;
	int field_0x28;
};

static_assert(sizeof(Magic::Base::File) == 0x20, "sizeof File");
