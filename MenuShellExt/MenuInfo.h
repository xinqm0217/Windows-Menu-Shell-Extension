#ifndef MENUINFO_H
#define MENUINFO_H

#include <vector>
using std::vector;

enum MenuItemType
{
	MenuUpload = 0,//上传
	MenuSend,      //发送
	//...
};

struct MenuItemInfo
{
	LPCTSTR name;
	LPCTSTR cmdString;
	HANDLE icon;
	UINT id;
};

class CMenuInfo
{
public:
	static HRESULT InitializeAllMenuItems(HINSTANCE hInstance);
	static int GetMenuItemNumber();
	static const MenuItemInfo& GetMenuItemInfoByIndex(int index);

private:
	static vector<MenuItemInfo> storeMenuItemsInfo;
};

#endif //MENUINFO_H