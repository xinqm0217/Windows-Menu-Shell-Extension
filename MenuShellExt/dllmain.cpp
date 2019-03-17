// dllmain.cpp: DllMain 的实现。

#include "stdafx.h"
#include "resource.h"
#include "MenuShellExt_i.h"
#include "MenuInfo.h"
#include "dllmain.h"

CMenuShellExtModule _AtlModule;
HINSTANCE g_hInstance;

// DLL 入口点
extern "C" BOOL WINAPI DllMain(HINSTANCE hInstance, DWORD dwReason, LPVOID lpReserved)
{
	g_hInstance = hInstance;
	if (dwReason == DLL_PROCESS_ATTACH)
	{
		CMenuInfo::InitializeAllMenuItems(hInstance);
	}
	return _AtlModule.DllMain(dwReason, lpReserved);
}
