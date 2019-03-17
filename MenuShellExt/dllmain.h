// dllmain.h: 模块类的声明。

class CMenuShellExtModule : public ATL::CAtlDllModuleT< CMenuShellExtModule >
{
public :
	DECLARE_LIBID(LIBID_MenuShellExtLib)
	DECLARE_REGISTRY_APPID_RESOURCEID(IDR_MENUSHELLEXT, "{7FF76B08-5587-408F-B54B-41A703343DF3}")
};

extern class CMenuShellExtModule _AtlModule;
