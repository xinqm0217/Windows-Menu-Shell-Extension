#include <winuser.h>
#include "stdafx.h"
#include "MenuInfo.h"

vector<MenuItemInfo> CMenuInfo::storeMenuItemsInfo;

HRESULT CMenuInfo::InitializeAllMenuItems(HINSTANCE hInstance)
{
	//设置图标
	//HANDLE hbitmap = LoadImage(hInstance, MAKEINTRESOURCE(IDB_BITMAP1),
	//IMAGE_BITMAP, 0, 0, LR_DEFAULTSIZE | LR_LOADTRANSPARENT);

	storeMenuItemsInfo.push_back(MenuItemInfo());
	storeMenuItemsInfo[MenuItemType::MenuUpload].name = L"Upload";
	storeMenuItemsInfo[MenuItemType::MenuUpload].cmdString = L"upload";
	//storeMenuItemsInfo[MenuItemType::MenuUpload].icon = hbitmap;

	return S_OK;
}

int CMenuInfo::GetMenuItemNumber()
{
	return storeMenuItemsInfo.size();
}

const MenuItemInfo& CMenuInfo::GetMenuItemInfoByIndex(int index)
{
	return storeMenuItemsInfo.at(index);
}
