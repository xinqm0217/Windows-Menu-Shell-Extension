// ShellExt.h : CShellExt 的声明

#ifndef SHELLEXT_H
#define SHELLEXT_H

#include <shobjidl.h>
#include <functional>
#include <vector>
#include "resource.h"       // 主符号
#include "MenuShellExt_i.h"

#if defined(_WIN32_WCE) && !defined(_CE_DCOM) && !defined(_CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA)
#error "Windows CE 平台(如不提供完全 DCOM 支持的 Windows Mobile 平台)上无法正确支持单线程 COM 对象。定义 _CE_ALLOW_SINGLE_THREADED_OBJECTS_IN_MTA 可强制 ATL 支持创建单线程 COM 对象实现并允许使用其单线程 COM 对象实现。rgs 文件中的线程模型已被设置为“Free”，原因是该模型是非 DCOM Windows CE 平台支持的唯一线程模型。"
#endif

using namespace ATL;
using std::vector;
using std::wstring;

// CShellExt

class menuInfo;
class ATL_NO_VTABLE CShellExt :
	public CComObjectRootEx<CComSingleThreadModel>,
	public CComCoClass<CShellExt, &CLSID_ShellExt>,
	public IDispatchImpl<IShellExt, &IID_IShellExt, &LIBID_MenuShellExtLib, /*wMajor =*/ 1, /*wMinor =*/ 0>,
	public IContextMenu,
	public IShellExtInit
{
public:
	CShellExt()
	{}

	DECLARE_REGISTRY_RESOURCEID(IDR_SHELLEXT)

	BEGIN_COM_MAP(CShellExt)
		COM_INTERFACE_ENTRY(IShellExt)
		COM_INTERFACE_ENTRY(IDispatch)
		COM_INTERFACE_ENTRY(IContextMenu)
		COM_INTERFACE_ENTRY(IShellExtInit)
	END_COM_MAP()

	DECLARE_PROTECT_FINAL_CONSTRUCT()

	HRESULT FinalConstruct()
	{
		return S_OK;
	}

	void FinalRelease()
	{}

public:
	HRESULT STDMETHODCALLTYPE Initialize(PCIDLIST_ABSOLUTE pidlFolder, IDataObject *pdtobj, HKEY hkeyProgID);
	HRESULT STDMETHODCALLTYPE QueryContextMenu(HMENU hmenu, UINT indexMenu, UINT idCmdFirst, UINT idCmdLast, UINT uFlags);
	HRESULT STDMETHODCALLTYPE InvokeCommand(CMINVOKECOMMANDINFO *pici);
	HRESULT STDMETHODCALLTYPE GetCommandString(UINT_PTR idCmd, UINT uType, UINT *pReserved, CHAR *pszName, UINT cchMax);

private:
	MENUITEMINFO GenerateMenuItemInfo(const MenuItemInfo &info, UINT cmdId);
	void OnUploadClick();

private:
	vector<wstring> selectedFiles;
};

OBJECT_ENTRY_AUTO(__uuidof(ShellExt), CShellExt)

#endif //SHELLEXT_H