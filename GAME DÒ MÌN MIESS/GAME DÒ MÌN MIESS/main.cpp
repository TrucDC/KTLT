#include "main.h"
#include "Console.h"
#include "functions.h"
using namespace std; 
//Trang,vị trí đang chọn tổn mục
short STrang, SViTriChon, STongMuc;
int main() {
	resizeConsole(ConsoleWidth, ConsoleHeight);//thay đổi kích thước màn hình console.
	SetConsoleTitle(TEXT("Game Do Min Mies-BT86 "));
	VeTieuDeGame();
	Cursor(false);//ẩn con trỏ
	veMenuChinh(0);
	STrang = 1;
	xuLySuKien();
   // cout << endl << endl;
	//system("pause");
	return 0;
}