#include <conio.h>
#include "egg.h"
#include "cmc.h"

//void egg_main()
int main()
{
	HEGG egg1;

	EggStart(1200,700);
	DrawBitmap("bitmap//����.bmp");

//	ShowConsoleWindow(0);

	Sleep(1000);
	egg1=LayEgg();
	MovePen(317,105);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,169);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,232);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,298);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,363);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,425);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,492);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,557);
	DrawBitmap("bitmap//�ⲿ����.bmp");


	MovePen(317,141);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,204);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,270);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,335);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,397);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,464);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,529);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(317,594);
	DrawBitmap("bitmap//�ⲿ����.bmp");

	MovePen(1122,157);
	DrawBitmap("bitmap//�ڲ�1-1.bmp");

	MovePen(1122,219);
	DrawBitmap("bitmap//�ڲ�2-1.bmp");

	MovePen(1122,273);
	DrawBitmap("bitmap//�ڲ�3-1.bmp");

	MovePen(1122,328);
	DrawBitmap("bitmap//�ڲ�4-1.bmp");

	MovePen(1044,155);
	DrawBitmap("bitmap//�ڲ�5-1.bmp");

	MovePen(1044,218);
	DrawBitmap("bitmap//�ڲ�6-1.bmp");

	MovePen(1044,274);
	DrawBitmap("bitmap//�ڲ�7-1.bmp");

	MovePen(1044,329);
	DrawBitmap("bitmap//�ڲ�8-1.bmp");

	MovePen(1044,388);
	DrawBitmap("bitmap//�ڲ�9-1.bmp");

	MovePen(1116,460);
	DrawBitmap("bitmap//GO2.bmp");

	MovePen(1047,457);
	DrawBitmap("bitmap//��GO2.bmp");

	Sleep(15000);
	EatEgg();
	

	getch();
	return 0;
}