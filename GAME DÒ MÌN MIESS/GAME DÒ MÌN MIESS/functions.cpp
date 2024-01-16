#include "main.h"
#include "functions.h"
#include "Console.h"
#include <windows.h>
#include <mmsystem.h>
using namespace std;
CauTrucBang CTBang;
CauTrucO **CTO;


//Vị trí con trỏ hiện tại.
COORD CViTriConTro;
//Sử dụng phím
bool BSuDungPhim = false;
// Tọa độ X,y vẽ bảng
short SToaDoX;
short SToaDoY;

//Cập nhật trang thái chơi game
bool BTrangThaiChoiGame = false;



void taoMang2ChieuDong()
{
	CTO = new CauTrucO * [CTBang.SDong];
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		CTO[i] = new CauTrucO[CTBang.SCot];

	}
}
void xoaMang2ChieuDong()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		delete[] CTO[i];
	}
	delete[] CTO;
}

void luuToaDoBang()
{
	SToaDoX = ((ConsoleWidth/2 ) - (CTBang.SDong));
	SToaDoY = (((ConsoleHeight- 1) - CTBang.SCot )/2)+2;
}


void khoiTao(short SDong, short SCot, short SSoBom)
{
	CTBang.SDong = SDong;
	CTBang.SCot = SCot;
	CTBang.SSoBom = SSoBom;
	CTBang.SSoODaMo = 0;
	CTBang.SSoCo = 0;

	taoMang2ChieuDong();
	taoBomNgauNhien();
	luuToaDoBang();
	CViTriConTro = { 0,0 };
	BTrangThaiChoiGame = true;
	veBang();
	veTrangThaiChoiGame(1,0,0);
}
short toaDoX(short SX) // Tọa độ  x vẽ bảng
{
	return((SX * 2)+SToaDoX);
}

short toaDoY(short SY) // Tọa độ  y vẽ bảng
{
	return (SY + SToaDoY);
}

void veO(short SX,short SY,short SKieu)
{
		switch (SKieu)
		{
		case 0: // rỗng 
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 0, 10, "  ");
			break;
		case 1: // số 1 chữ màu xanh dương.Từ 1-->8 có nền là màu trắng
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 9, 15,"1 ");
			break;
		case 2:// số 2 là màu xanh lá
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 2, 15,"2 ");
			break;
		case 3:// số 3 đỏ
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 12, 15,"3 ");
			break;
		case 4:// số 4 xanh dương đậm
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 1, 15,"4 ");
			break;
		case 5: //số 5 đỏ đậm
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 4, 15,"5 ");
			break;
		case 6:// số 6 CYAN dam
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 3, 15, "6 ");
			break;
		case 7://số 7 đen
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 0, 15, "7 ");
			break;
		case 8://số 8 hồng
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 12, 15,"8 ");
			break;
		case 9://Bom.Nền đỏ,chữ đen
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 0, 12,"B ");
			break;
		case 10:// 0 chan
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 0, 8,"  ");
			break;
		case 11://0 le
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 0, 7,"  ");
			break;
		case 12://theo dõi con trỏ
			Tao_mau_o(toaDoX(SX)+1, toaDoY(SY), 0, 13," ");
			break;
		case 13://Cấm cờ.Nền vàng nhạt,chữ màu đỏ
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 12, 14,"P ");
			break;
		case 14: //Cấm cờ ko có bom --> Cấm cờ sai.Nền Cam,chữ trắng
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 15, 6,"S ");
			break;
		case 15://Cấm cờ có bom-->cấm cờ đúng 
			Tao_mau_o(toaDoX(SX), toaDoY(SY), 12, 14,"D ");
			break;
		}
	}


void veBang()
{
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)
				veO(j, i, 13);
			else if (CTO[i][j].SBomLanCan)
				veO(j, i, CTO[i][j].SBomLanCan);
			else if (CTO[i][j].BDaMo)// ô rỗng
				veO(j, i, 0);
		  else if ((i+j)%2)
				veO(j, i, 11);
			else
				veO(j, i, 10);
			if (BSuDungPhim)
				veO(CViTriConTro.X, CViTriConTro.Y,12);
		}
	}
}

void taoBomNgauNhien()
{
	short SSoBom = CTBang.SSoBom;
	short SI, SJ; //SI là vị trí dòng,SJ là vị trí cột ta sẽ random
	srand(time(NULL));//reset time
	while (SSoBom)
	{
		SI = rand() % CTBang.SDong;
		SJ = rand() % CTBang.SCot;
		if (CTO[SI][SJ].BCoBom)
			continue;

		CTO[SI][SJ].BCoBom = true;
		--SSoBom; // Cập nhật lại số lượng bom
	}
}

void clickPhai(short SX, short SY) //Cấm cờ
{    
	if((CTBang.SSoBom - CTBang.SSoCo) > 0){
		if (!CTO[SX][SY].BDaMo)
		{
			if (CTO[SX][SY].BCamCo)
			{
				CTO[SX][SY].BCamCo = false;
				CTBang.SSoCo--;
			}
			else
			{
				CTO[SX][SY].BCamCo = true;
				CTBang.SSoCo++;
			}
			PlaySound(TEXT("C:\\Users\\GYGABYTE\\Downloads\\KTLT\\GAME DÒ MÌN MIESS-20240111T031436Z-001\\GAME DÒ MÌN MIESS\\amThanh\\3.wav"), NULL, SND_ASYNC);
		}
		veBang();

		deleteRow(3, 1);
		veTrangThaiChoiGame(1, 0, 0);
	}
}

short demBomLanCan(short SX, short SY)
{
	short SDem = 0;
	for (int i = SX - 1; i <= SX + 1; ++i) {
		for (int j = SY - 1; j <= SY+1; ++j)
		{
		//Xet những vị trí ko hợp lệ-->tiếp tục lặp
			if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
				continue;

			//Xet xem ô có bom hay khong.Có tawg lên 1
			if (CTO[i][j].BCoBom)
				++SDem;
		}
	}
	return SDem;
}

void moO(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		CTO[SX][SY].BDaMo = true;
		if (CTO[SX][SY].BCoBom)//Có bom
			thua(); //-->thua
		else
		{
			CTBang.SSoODaMo++;
			short SSoBomLanCan = demBomLanCan(SX, SY);
			if (SSoBomLanCan) //Có Bom Lân Cận
				CTO[SX][SY].SBomLanCan = SSoBomLanCan;
			else // ô rỗng
			{
				//Duyệt Các ô lân cận và gọi đệ quy.
				for (int i = SX - 1; i <= SX + 1; ++i) {
					for (int j = SY - 1; j <= SY+1; ++j)
					{
						//Xet những vị trí ko hợp lệ-->tiếp tục lặp
						if (i < 0 || i >= CTBang.SDong || j < 0 || j >= CTBang.SCot || (i == SX && j == SY))
							continue;

						//Gọi đệ quy
						moO(i, j);
					}
				}
			}
		}
	}
 }

bool thongKeCo()
{
	if ((CTBang.SSoODaMo + CTBang.SSoBom) == (CTBang.SDong * CTBang.SCot))
		return true;
	return false;

	
}

void clickTrai(short SX, short SY)
{
	if (!CTO[SX][SY].BDaMo && !CTO[SX][SY].BCamCo)
	{
		moO(SX, SY);
		if (BTrangThaiChoiGame)
		{
			veBang();

			if (thongKeCo())
				thang();
			else
			{
			
				PlaySound(TEXT("C:\\Users\\GYGABYTE\\Downloads\\KTLT\\GAME DÒ MÌN MIESS-20240111T031436Z-001\\GAME DÒ MÌN MIESS\\amThanh\\1-wav"), NULL, SND_ASYNC);
			}
		}
	}
}

void thang() {
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();//giải phóng con trỏ
	STrang = 5;
	deleteRow(3, 1);
	veTrangThaiChoiGame(2,2,0); // cập nhật lại trạng thái thắng
	PlaySound(TEXT("C:\\Users\\GYGABYTE\\Downloads\\KTLT\\GAME DÒ MÌN MIESS-20240111T031436Z-001\\GAME DÒ MÌN MIESS\\amThanh\\4.wav"), NULL, SND_ASYNC);
}
void thua()
{
	//Hiện bom ẩn và kiểm tra cấm cờ
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)// có cấm cờ
			{
				if (CTO[i][j].BCoBom)
					veO(j, i, 15);//Cấm cờ đúng(cẤM cờ có bom)
				else
					veO(j, i,14 );//Cấm cờ sai (cấm cờ ko có bom)
			}
			else //ko cấm cờ
			{
				if (CTO[i][j].BCoBom)//Có bom--> hiện bom
					veO(j, i, 9); //Hiện bom ẩn
			}
		}
	}
	BTrangThaiChoiGame = false;
	xoaMang2ChieuDong();//Giair phóng bộ nhớ
	STrang = 4;
	deleteRow(3, 1);
	veTrangThaiChoiGame(3,3,0);//trạng thái thua
	PlaySound(TEXT("C:\\Users\\GYGABYTE\\Downloads\\KTLT\\GAME DÒ MÌN MIESS-20240111T031436Z-001\\GAME DÒ MÌN MIESS\\amThanh\\2.wav"), NULL, SND_ASYNC);
}

/*Ý tưởng xử lí menu :
* 1)  trang là menu chính
* 2) trang menu chọn cấp độ
* 3)trang chơi game
* 4) trang thua
* 5)trang thắng
* 6) trang lưu game
* 7) trang thoong tin
*/

void xuLyPhim(KEY_EVENT_RECORD key)
{
	if (key.bKeyDown)// Có nhấn phím
	{
		switch (key.wVirtualKeyCode)
		{
		 case VK_UP://Mũi tên lên.
			 switch (STrang)
			 {
			 case 1://menu chính
				 if (STongMuc == 4)
				 {
					 if (SViTriChon == 0)
						 SViTriChon = STongMuc - 1;
					 else
						 SViTriChon -= 1;
					 veMenuChinh(SViTriChon);
					 
				 }
				 break;
			 case 2://menu chọn cấp độ
				 if (STongMuc == 4)
				 {
					 if (SViTriChon == 0)
						 SViTriChon = STongMuc - 1;
					 else
						 SViTriChon -= 1;
					 veMenuCapDo(SViTriChon);
				 }
				 break;
			 case 3://trang chơi game
				 if (BTrangThaiChoiGame)
				 {
					 BSuDungPhim = true;
					 CViTriConTro.Y = ((CViTriConTro.Y == 0) ? CTBang.SDong - 1 : CViTriConTro.Y - 1);
					 veBang();
				 }
				 break;
			 case 4://trang thua
				 veTrangThaiChoiGame(3, 3,(SViTriChon==0)?1:0);
				 break;
			 case 5://trang thắng 
				 veTrangThaiChoiGame(2, 2, (SViTriChon == 0) ? 1 : 0);
				 break;
			 }
			break;
		 case VK_DOWN://Mũi tên xuống.
			 switch (STrang)
			 {
			 case 1://menu chính
				 if (STongMuc == 4)
				 {
					 if (SViTriChon == STongMuc-1)
						 SViTriChon = 0;
					 else
						 SViTriChon += 1;
					 veMenuChinh(SViTriChon);
				 }
				 break;
			 case 2://menu chọn cấp độ
				 if (STongMuc == 4)
				 {
					 if (SViTriChon == STongMuc-1)
						 SViTriChon = 0;
					 else
						 SViTriChon += 1;
					 veMenuCapDo(SViTriChon);
				 }
				 break;
			 case 3://trang chơi game
				 if (BTrangThaiChoiGame)
				 {
					 BSuDungPhim = true;
					 CViTriConTro.Y = ((CViTriConTro.Y == CTBang.SDong - 1) ? 0 : CViTriConTro.Y + 1);
					 veBang();
				 }
				 break;
			 case 4://trang thua
				 veTrangThaiChoiGame(3, 3, (SViTriChon == 0)? 1 : 0);
				 break;
			 case 5://trang thắng
				 veTrangThaiChoiGame(2, 2, (SViTriChon == 0) ? 1 : 0);
				 break;
			 }
			 break;
		 case VK_LEFT://Mũi tên trái.
			 if (BTrangThaiChoiGame)
			 {
				 BSuDungPhim = true;
				 CViTriConTro.X = ((CViTriConTro.X == 0) ? CTBang.SCot - 1 : CViTriConTro.X - 1);
				 veBang();
			}
			 break;
		 case VK_RIGHT://Mũi tên phải.
			 if (BTrangThaiChoiGame)
			 {
				 BSuDungPhim = true;
				 CViTriConTro.X = ((CViTriConTro.X == CTBang.SCot - 1) ? 0 : CViTriConTro.X + 1);
				 veBang();
			 }
			 break;
		 case VK_RETURN://Phím Enter
			 switch(STrang)
			 {
			 case 1://menu chính
				 if (SViTriChon == 0)
				 {
					 STrang = 2;
					 deleteRow(2, 10);
					 VeTieuDeGame();
					 veMenuCapDo(0);
				 }
				 else if(SViTriChon==1)// Trang bảng điểm
				 {
					 STrang = 8;
					deleteRow(2, 10);
				     VeTieuDeGame();
					 TrangBangDiem();

				 }
				 else if (SViTriChon == 2)//Trang thông tin
				 {
					 STrang = 7;
					 deleteRow(2, 10);
					 VeTieuDeGame();
					 TrangThongTin(0);
				 }
				 else
				 {
					 exit(0);
				 }
				 break;
			 case 2://menu chọn cấp độ
				 if (SViTriChon == 0)//Cấp độ dễ 
				 {   
					 STrang = 3;//Cập nhật lại đang chơi gaem
					 deleteRow(2, 10);
					 khoiTao(9, 9, 10);
				 }
				 else if (SViTriChon == 1)//Cấp độ trung bình
				 {
					 STrang = 3;//Cập nhật lại đang chơi gaem
					 deleteRow(2, 10);
					 khoiTao(16, 16, 40);
				 }
				 else if (SViTriChon == 2)//Cấp độ khó
				 {
					 STrang = 3;//Cập nhật lại đang chơi gaem
					 deleteRow(3, 10);
					 khoiTao(24, 24, 99);
				 }
				 else
				 {
					 STrang = 1;//Cập nhật lại menuchinhs
					 deleteRow(3, 10);
					 veMenuChinh(0);
				 }
				 break;
			 case 4://trang thua
				 if (SViTriChon)
				 {
					 STrang = 1; //Trở về menu chính
					 deleteRow(2, ConsoleHeight-6);
					 veMenuChinh(0);
			     }
				 else
				 {
					 STrang = 3; //Trang chơi game
					 deleteRow(3, ConsoleHeight-13);
					 khoiTao(CTBang.SDong, CTBang.SCot, CTBang.SSoBom); 
				 }
				 break;
			 case 5://trang thắng 
				 STrang = 1; //Trở về menu chính
				 deleteRow(2, ConsoleHeight - 6);
				 veMenuChinh(0);
				 break;
			 case 6://Trang phụ trang lưu game
				 if (SViTriChon)
				 {
					 STrang = 1; //Trở về menu chính
					 deleteRow(2, ConsoleHeight - 6);
					 veMenuChinh(0);
				 }
				 else
				 {
					 //luuq gaem --->xử lí game
				 }
				 break;
			 }
			 break;
		 case  VK_ESCAPE://Phím ESC(thoát)
			 switch (STrang)
			 {
			 case 1:
				 exit(0);
				 break;
			 case 2://menu chọn cấp độ 
				 STrang = 1;//Cập nhật lại thành trang menu chính
				 deleteRow(2, 10);
				 veMenuChinh(0);
				 break;
			 case 3:
				 STrang = 6;
				 veTrangThaiChoiGame(1, 1, 0);
				 exit(0);
				 break;
			 case 4://trang thua
				 break;
			 case 5://trang thắng 
				 STrang = 2;
				 deleteRow(2, ConsoleHeight-13);
				 veMenuCapDo(0);
				 break;
			 case 7:
				 deleteRow(4, 12);
				 STrang = 1;
				 veMenuChinh(0);
				 break;
			 }
			 break;
		 case ClickTrai:// Phím Z-Mở ô
			 clickTrai(CViTriConTro.Y, CViTriConTro.X);
			 break;
		 case ClickPhai:// Phím X -Cấm cờ
			 clickPhai(CViTriConTro.Y, CViTriConTro.X);
			 break;
		}
	}
}


void xuLySuKien()
{
	while (1)
	{
		DWORD DWNumberOfEvents = 0;//Lưu lại sự kiện hiện tại
		DWORD DWNumberOfEventsRead = 0; //Lưu lại số lượng sự kiện đã được lọc

		HANDLE HConsoleInput = GetStdHandle(STD_INPUT_HANDLE);//Thiết bị đầu vào.
		GetNumberOfConsoleInputEvents(HConsoleInput, &DWNumberOfEvents);//Dặt sự kiện đầu vào của giao diện cho biến  DWNumberOfEvents 

		if (DWNumberOfEvents)
		{
			INPUT_RECORD* IREvenBuffer = new INPUT_RECORD[DWNumberOfEvents];//Con trỏ evenbuffer.
			ReadConsoleInput(HConsoleInput, IREvenBuffer, DWNumberOfEvents, &DWNumberOfEventsRead);// Dặt các sự kiện lưu trữ vào con trỏ

			//Chạy vòng lặp để đọc sự kiện
			for (DWORD i = 0; i < DWNumberOfEvents; ++i)
			{
				if (IREvenBuffer[i].EventType == KEY_EVENT)// Nếu là sự kiện phím. 
				{
					xuLyPhim(IREvenBuffer[i].Event.KeyEvent);
				}
				
			}
		}
	}
}
void VeTieuDeGame()
{
	Tao_mau_o((ConsoleWidth/2.5+3),0,12,14, "*GAME DO MIN MIES*\n");
	Tao_mau_o((ConsoleWidth/3 ), 1, 2, 14, "(BT86-Ho Phat Dat,Do Trung Lap,Mai Liem Truc)\n");
	Tao_mau_o(0, 3, 10, 0, "------------------------------------------------------------------------------------------------------------------------");
}
void veTrangThaiChoiGame(short STrangThai,short SCheDo,short SIndex)
{   
	SViTriChon = SIndex;
	STongMuc = 2;
	if ((CTBang.SSoBom - CTBang.SSoCo) >= 0) {
		Tao_mau_o(1, 2, 6, 0, "MAP: ");
		printf("%d x %d\n", CTBang.SDong, CTBang.SCot);
		Tao_mau_o(1, 3, 6, 0, "SO BOM :", CTBang.SSoBom);
		printf(" %d\n", CTBang.SSoBom - CTBang.SSoCo);
		
	}
	else
	{
		Tao_mau_o(1, 3, 6, 0, "SO BOM :", CTBang.SSoBom);
		cout << "0";
	}
	
	// Vẽ menu thắng thua 
	string STRTextMenuCheDo;
	if (SCheDo == 2)
	{
		STRTextMenuCheDo = "  LUU TEN  ";
		Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuCheDo.length() / 2), 3, 13, ((SIndex == 0) ? 11 : 0), STRTextMenuCheDo);
	}
	if (SCheDo == 3)
	{
		STRTextMenuCheDo = "  CHOI LAI  ";
		Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuCheDo.length() / 2), 3, 13, ((SIndex == 0) ? 11 : 0), STRTextMenuCheDo);
	}

	if (SCheDo >= 1)
	{
		STRTextMenuCheDo = "  THOAT  ";
		Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuCheDo.length() / 2), 4, 13, ((SIndex == 1) ? 11 : 0), STRTextMenuCheDo);
	}

	
	//Vẽ text trang thai
	if (STrangThai == 1)//Đang chơi game
		Tao_mau_o(ConsoleWidth-20, 3, 6, 0, "TRANG THAI:Dang Choi");
	if (STrangThai == 2)//Thắng 
		Tao_mau_o(ConsoleWidth - 20, 3, 14, 0, "TRANG THAI: Thang   ");
	if (STrangThai == 3)//thua
		Tao_mau_o(ConsoleWidth - 20, 3, 4, 0, "TRANG THAI: Thua    ");
	cout << endl;
	Tao_mau_o(0, 5, 10, 0, "------------------------------------------------------------------------------------------------------------------------");
}

void veMenuChinh(short SIndex)
{
	// Cap nhat lại vị trí đang chọn và tổng mục của menu
	SViTriChon = SIndex;
	STongMuc = 4;

	//vẽ menu
	string STRTextMenuChinh = "  GAME MOI  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 6, 13, ((SIndex == 0) ? 11 : 0), STRTextMenuChinh);
	STRTextMenuChinh = "  BANG DIEM  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 7, 13, ((SIndex == 1) ? 11 : 0), STRTextMenuChinh);
	STRTextMenuChinh = "  THONG TIN  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 8, 13, ((SIndex == 2) ? 11 : 0), STRTextMenuChinh);
	STRTextMenuChinh = "  THOAT  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 9, 13, ((SIndex == 3) ? 11 : 0), STRTextMenuChinh);
	PlaySound(TEXT("C:\\Users\\GYGABYTE\\Downloads\\KTLT\\GAME DÒ MÌN MIESS-20240111T031436Z-001\\GAME DÒ MÌN MIESS\\amThanh\\5.wav"), NULL, SND_ASYNC);
}


void veMenuCapDo(short SIndex)
{

	// Cap nhat lại vị trí đang chọn và tổng mục của menu
	SViTriChon = SIndex;
	STongMuc = 4;
	string STRTextMenuChinh = " CHON CAP DO  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 4, 4, ((SIndex == 0) ? 0 : 0), STRTextMenuChinh);
	//vẽ menu
	STRTextMenuChinh = "  DE (9 x 9 VA 10 BOM)  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 6, 13, ((SIndex == 0) ? 11 : 0), STRTextMenuChinh);
	STRTextMenuChinh = "  TRUNG BINH (16 x 16 VA 40 BOM)  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 7, 13, ((SIndex == 1) ? 11 : 0), STRTextMenuChinh);
	STRTextMenuChinh = "  KHO (24 x 24 VA 99 BOM)  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 8, 13, ((SIndex == 2) ? 11 : 0), STRTextMenuChinh);
	STRTextMenuChinh = "  QUAY LAI  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRTextMenuChinh.length() / 2), 9, 13, ((SIndex == 3) ? 11 : 0), STRTextMenuChinh);

}
void TrangThongTin(short SIndex)
{
	string STRtextThongTin = "  LUAT CHOI  ";
	Tao_mau_o((ConsoleWidth / 2) - (STRtextThongTin.length() / 2), 4, 14, ((SIndex == 0) ? 2 : 0), STRtextThongTin);
	Tao_mau_o(0, 5, 15, 0, "* Ban phai dung thanh dieu huong tren ban phim de di chuyen tren cac o sau do tien hanh mo o.");
	Tao_mau_o(0, 6, 15, 0, "* Nhan phim Z tren ban phim de mo o,nhan phim X tren ban phim de danh dau vi tri ban nghi ngo co bom.");
	Tao_mau_o(0, 7, 15, 0, "* Neu o ban mo co cac so hien ra nghia la co cac so bom tuong ung lan can tai vi tri cua ban,nguoc lai man hinh se loan ra cac vung xanh nghia la vi tri do khong co bom xung quanh.");
	Tao_mau_o(0, 9, 15, 0, "* Neu ban mo ngay o co bom ban se thua ngay lap tuc hoac khi ban mo den o cuoi cung nhung ban danh dau sai vi tri co bom thi ban cung se thua.");
	Tao_mau_o(0, 11, 15, 0, "* Ban chi thang khi ban mo o den vi tri cuoi cung nhung khong ngay o co bom hoac ban mo o den vi tri cuoi cung nhung ban danh dau dung tat ca cac vi tri co bom thi ban se thang.");
}

void TrangBangDiem()
{ 
	string  a = "  DIEM  ";
	Tao_mau_o((ConsoleWidth / 2) - (a.length() / 2), 4, 11, 12, a);
	int dem = 0;
	for (int i = 0; i < CTBang.SDong; ++i)
	{
		for (int j = 0; j < CTBang.SCot; ++j)
		{
			if (CTO[i][j].BCamCo)// có cấm cờ
			{
				if (CTO[i][j].BCoBom)
					dem =dem+ 15;//Cấm cờ đúng(cẤM cờ có bom)
			}
		}
	}
	cout << endl;
	Tao_mau_o(0, 5, 0, 0, "                                                           ");
	cout << dem;
}
