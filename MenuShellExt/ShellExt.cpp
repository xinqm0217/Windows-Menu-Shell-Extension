// ShellExt.cpp : CShellExt 的实现

#include "stdafx.h"
#include "MenuInfo.h"
#include "ShellExt.h"

// CShellExt
extern HINSTANCE g_hInstance;

HRESULT STDMETHODCALLTYPE CShellExt::Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pdtobj, HKEY hkeyProgID)
{
	if (NULL == pdtobj)
	{
		return S_OK;
	}

	STGMEDIUM stm;
	FORMATETC fe = { CF_HDROP, NULL, DVASPECT_CONTENT, -1, TYMED_HGLOBAL };
	HRESULT hresult = S_OK;

	if (pdtobj->GetData(&fe, &stm) >= 0)
	{
		HDROP hDrop = static_cast<HDROP>(GlobalLock(stm.hGlobal));

		if (NULL != hDrop)
		{
			UINT nFiles = DragQueryFile(hDrop, 0xFFFFFFFF, NULL, 0);
			for (size_t i = 0; i < nFiles; i++)
			{
				wchar_t szSelectedFile[MAX_PATH] = { 0 };

				if (0 != DragQueryFile(hDrop, i, szSelectedFile, ARRAYSIZE(szSelectedFile)))
				{
					selectedFiles.push_back(szSelectedFile);
				}
				else
				{
					hresult = E_FAIL;
					break;
				}
			}
		}

		GlobalUnlock(stm.hGlobal);
	}

	ReleaseStgMedium(&stm);
	return hresult;
}

HRESULT STDMETHODCALLTYPE CShellExt::QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags)
{
	if (CMF_DEFAULTONLY & uFlags)
	{
		return MAKE_HRESULT(SEVERITY_SUCCESS, FACILITY_NULL, USHORT(0));
	}

	InsertMenuItem(hmenu, 0, TRUE, &GenerateMenuItemInfo(CMenuInfo::GetMenuItemInfoByIndex(MenuItemType::MenuUpload), idCmdFirst));
	return MAKE_HRESULT(SEVERITY_SUCCESS, 0, USHORT(CMenuInfo::GetMenuItemNumber()));
}

HRESULT STDMETHODCALLTYPE CShellExt::InvokeCommand(CMINVOKECOMMANDINFO *pici)
{
	switch (LOWORD(pici->lpVerb))
	{
	case MenuItemType::MenuUpload:
		OnUploadClick();
		break;
	default:
		break;
	}
	return S_OK;
}

HRESULT CShellExt::GetCommandString(UINT_PTR idCmd, UINT uType, UINT *pReserved, CHAR *pszName, UINT cchMax)
{
	return S_OK;
}

MENUITEMINFO CShellExt::GenerateMenuItemInfo(const MenuItemInfo &info, UINT cmdId)
{
	MENUITEMINFO menuItemInfo = { sizeof(menuItemInfo) };
	menuItemInfo.wID = cmdId + info.id;
	menuItemInfo.fType = MFT_STRING | MFT_RIGHTJUSTIFY;
	menuItemInfo.dwTypeData = (LPWSTR)info.name;
	menuItemInfo.fState = MFS_ENABLED;
	menuItemInfo.fMask = MIIM_STRING | MIIM_FTYPE | MIIM_ID | MIIM_STATE;
	if (NULL != info.icon)
	{
		menuItemInfo.fMask |= MIIM_CHECKMARKS;
		menuItemInfo.hbmpChecked = static_cast<HBITMAP>(info.icon);
		menuItemInfo.hbmpUnchecked = static_cast<HBITMAP>(info.icon);
	}

	return menuItemInfo;
}

void CShellExt::OnUploadClick()
{
	if (selectedFiles.empty())
	{
		return;
	}

	SHELLEXECUTEINFO sei = { sizeof(SHELLEXECUTEINFO) };
	sei.lpVerb = TEXT("open");
	sei.lpFile = TEXT("xxx.exe");
	sei.nShow = SW_SHOW;

	//获取dll所在目录(xxx.exe和MenuShellExt.dll安装在同一目录下)
	TCHAR dllPath[_MAX_PATH] = TEXT("");
	GetModuleFileName(g_hInstance, dllPath, sizeof(dllPath));
	PathRemoveFileSpec(dllPath);
	sei.lpDirectory = dllPath;

	//生成传入的参数
	wstring parameters;
	for (const auto&path : selectedFiles)
	{
		for (auto c : path)
		{
			//对路径中的特殊字符进行处理
			if (' ' == c)
			{
				parameters += L"\" \"";
			}
			else
			{
				parameters += c;
			}
		}
		parameters += L" ";
	}

	sei.lpParameters = parameters.c_str();
	//MessageBox(NULL, sei.lpParameters, TEXT("Upload"), MB_OK);
	ShellExecuteEx(&sei);
}