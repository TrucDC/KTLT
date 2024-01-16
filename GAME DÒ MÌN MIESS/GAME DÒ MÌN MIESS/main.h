#pragma once
#include <iostream>
#include <ctime>
#pragma comment(lib,"winmm.lib")
#define ConsoleWidth 120
#define ConsoleHeight 34

#define ClickTrai 0x5A
#define ClickPhai 0x58
struct CauTrucBang
{
	short SDong = 0;
	short SCot = 0;
	short SSoBom = 0;
	short SSoODaMo = 0;
	short SSoCo = 0;
};
struct CauTrucO
{
	bool BCoBom = false;
	bool BDaMo = false;
	bool BCamCo = false;
	short SBomLanCan = 0;
};

//Trang,vị trí đang chọn tổn mục
 extern short STrang, SViTriChon, STongMuc;