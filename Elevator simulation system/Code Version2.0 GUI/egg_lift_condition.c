#include <string.h>
#include "egg.h"
#include "cmc.h"

#define DEFAULT_DELAY 1000
#define DEFAULT_RATIO 5
#define DEFAULT_STRATEGY 1

int is_showed=0;//0 for haven't showed the staffs

typedef struct key_situ
{
	int leftup_x;
	int leftup_y;
	int rightdown_x;
	int rightdown_y;
	char bitmapR_name[27];
	char bitmapB_name[27];
} KEY;

extern HEGG main_egg;//�����ľ��

KEY key[20]=	{
		{231,547,314,518,"bitmap//��ʹ��Ĭ�ϲ���.bmp","bitmap//��ʹ��Ĭ�ϲ���.bmp"},
		{386,547,529,518,"",""},
		{542,547,633,518,"",""},

		{244,470,304,426,"bitmap//��0.5��.bmp","bitmap//��0.5��.bmp"},
		{319,470,379,426,"bitmap//��1��.bmp","bitmap//��1��.bmp"},
		{398,470,458,426,"bitmap//��1.5��.bmp","bitmap//��1.5��.bmp"},
		{476,470,536,426,"bitmap//��2��.bmp","bitmap//��2��.bmp"},
		{556,470,616,426,"bitmap//��3��.bmp","bitmap//��3��.bmp"},
		
		{245,372,305,328,"bitmap//��һ��.bmp","bitmap//��һ��.bmp"},
		{320,372,380,328,"bitmap//�����.bmp","bitmap//������.bmp"},
		{398,372,458,328,"bitmap//������.bmp","bitmap//������.bmp"},
		{476,372,536,328,"bitmap//������.bmp","bitmap//������.bmp"},
		{556,372,616,328,"bitmap//������.bmp","bitmap//������.bmp"},

		{674,521,906,493,"bitmap//�����1.bmp","bitmap//������1.bmp"},
		{674,481,906,453,"bitmap//�����2.bmp","bitmap//������2.bmp"},
		{674,442,906,414,"bitmap//�����3.bmp","bitmap//������3.bmp"},
		{674,405,906,377,"bitmap//�����4.bmp","bitmap//������4.bmp"},
		{674,367,906,339,"bitmap//�����5.bmp","bitmap//������5.bmp"},

		{936,554,969,428,"",""},
		{936,418,969,310,"",""}
		};

void act_string(char *string,int delay);//����Ҫ��ӡ���ַ����������ֵ�ʱ����,���ַ���̬��ӡ(Ҫ����<string.h>)

void egg_inner_condition(int floor,int dir)//��ӡegg��汾�����ڲ�������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ -2����)
{

	while (bitmap==1);
	ng=1;
	SetActiveEgg(main_egg);
	while (bitmap==1);
	MovePen(1046,609);
	if (dir!=-2)//���ǿ���
	{
		switch (floor)
		{
		case 1:
			DrawBitmap("bitmap//��1.bmp");
			break;
		case 2:
			DrawBitmap("bitmap//��2.bmp");
			break;
		case 3:
			DrawBitmap("bitmap//��3.bmp");
			break;
		case 4:
			DrawBitmap("bitmap//��4.bmp");
			break;
		case 5:
			DrawBitmap("bitmap//��5.bmp");
			break;
		case 6:
			DrawBitmap("bitmap//��6.bmp");
			break;
		case 7:
			DrawBitmap("bitmap//��7.bmp");
			break;
		case 8:
			DrawBitmap("bitmap//��8.bmp");
			break;
		case 9:
			DrawBitmap("bitmap//��9.bmp");
			break;
		default:
			break;
		}
	}
	ng=0;
	
	while (bitmap==1);
	ng=0;
	MovePen(1046,542);
	if (dir==1)
		DrawBitmap("bitmap//�ڲ�����.bmp");
	else if (dir==-1)
		DrawBitmap("bitmap//�ڲ�����.bmp");
	else if (dir==-2)
	{
		MovePen(1046,609);
		DrawBitmap("bitmap//�ڲ�����.bmp");
	}
	else//=0
		DrawBitmap("bitmap//�ڲ�ͣ.bmp");
	ng=1;

	return;
	
}
/*(1046��609)    (1170,475)		��ֵ(124,136)*/
/*(1075,609)*/

void egg_outer_condition(int floor,int dir)//��ӡegg��汾�����ⲿ������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ -2����)
{
	//static int step=0;

	while (bitmap==1);

	ng=1;
	SetActiveEgg(main_egg);
	
	if (dir==1)
	{
		MovePen(843,348);
		DrawBitmap("bitmap//�ⲿ��2.bmp");
		MovePen(843,282);
		DrawBitmap("bitmap//�ⲿ��1.bmp");
	}
	else if (dir==-1)
	{
		MovePen(843,348);
		DrawBitmap("bitmap//�ⲿ��1.bmp");
		MovePen(843,282);
		DrawBitmap("bitmap//�ⲿ��2.bmp");
	}
	else
	{
		MovePen(843,348);
		DrawBitmap("bitmap//�ⲿ��1.bmp");
		MovePen(843,282);
		DrawBitmap("bitmap//�ⲿ��1.bmp");
	}
	ng=0;

	while (bitmap==1);
	ng=1;
	MovePen(843,216);
	switch (floor)
	{
	case 1:	
		DrawBitmap("bitmap//�ⲿ1.bmp");
		break;
	case 2:	
		DrawBitmap("bitmap//�ⲿ2.bmp");
		break;
	case 3:	
		DrawBitmap("bitmap//�ⲿ3.bmp");
		break;
	case 4:	
		DrawBitmap("bitmap//�ⲿ4.bmp");
		break;
	case 5:	
		DrawBitmap("bitmap//�ⲿ5.bmp");
		break;
	case 6:	
		DrawBitmap("bitmap//�ⲿ6.bmp");
		break;
	case 7:	
		DrawBitmap("bitmap//�ⲿ7.bmp");
		break;
	case 8:	
		DrawBitmap("bitmap//�ⲿ8.bmp");
		break;
	case 9:	
		DrawBitmap("bitmap//�ⲿ9.bmp");
		break;
	default:
		break;
	}
	ng=0;

	return;
}
/*(843,348)     (902,149)    dx=59    dy=199*/
/*(843,216)*/


int egg_tips()//��ӡegg��汾�ĳ�ʼ����ʾ��Ϣ
{
	
	HEGG first_egg;//��ӡ��ʼ��Ϣ��egg
	char infor1[]="�����������ε������˰ɣ�ѧ�嵽�ˣ��Ͻ�ʹ��201021131603С���ģ�������¥��~~";
	char infor2[]="����������ܲ���ˣ�������������Ϊ��ʹ������;��족�����Ƚ���һ�µ��ݲ����Ĳ�������:";
	
	int situ,i/*counter*/;
	int mouseX,mouseY;

	void show_staff(void);
	int dealwith_key(int num);

	first_egg=LayEgg();
	DrawBitmap("bitmap//��ʼ.bmp");

	MovePen(200,670);
	SetPenColor(RED);
	act_string(infor1,70);

	MovePen(200,650);
	SetPenColor(DARK_MAGENTA);
	act_string(infor2,60);

	//initialization
	MovePen(200,590);
	DrawBitmap("bitmap//scale.bmp");
	if(delay==DEFAULT_DELAY && ratio==DEFAULT_RATIO && strategy==DEFAULT_STRATEGY)
	{
		MovePen(key[0].leftup_x,key[0].leftup_y);
		DrawBitmap(key[0].bitmapB_name);
	}
	switch(delay)
	{
	case 500:
		MovePen(key[3].leftup_x,key[3].leftup_y);
		DrawBitmap(key[3].bitmapR_name);
		break;
	case 1000:
		MovePen(key[4].leftup_x,key[4].leftup_y);
		DrawBitmap(key[4].bitmapR_name);
		break;
	case 1500:
		MovePen(key[5].leftup_x,key[5].leftup_y);
		DrawBitmap(key[5].bitmapR_name);
		break;
	case 2000:
		MovePen(key[6].leftup_x,key[6].leftup_y);
		DrawBitmap(key[6].bitmapR_name);
		break;
	case 3000:
		MovePen(key[7].leftup_x,key[7].leftup_y);
		DrawBitmap(key[7].bitmapR_name);
		break;
	}
	MovePen(key[7+ratio].leftup_x,key[7+ratio].leftup_y);
	DrawBitmap(key[7+ratio].bitmapR_name);
	MovePen(key[12+strategy].leftup_x,key[12+strategy].leftup_y);
	DrawBitmap(key[12+strategy].bitmapR_name);

	while((situ=WaitForEvent())!=0)
	{
		mouseX=(int)GetMouseX();
		mouseY=(int)GetMouseY();

		if(situ==KEYDOWN)
		{
			for(i=0;i<20;i++)
			{
				if(key[i].leftup_x<=mouseX &&
					key[i].leftup_y>=mouseY &&
					key[i].rightdown_x>=mouseX &&
					key[i].rightdown_y<=mouseY)
				{
					int r;
					if((r=dealwith_key(i))==1)
					{
						EatEgg();
						return 1;
					}
					else if(r==-1)
					{
						EatEgg();
						return -1;
					}
					break;
				}
			}

		}
	}

	EatEgg();

	return 0;

}

void act_string(char *string,int delay)//����Ҫ��ӡ���ַ����������ֵ�ʱ����,���ַ���̬��ӡ(Ҫ����<string.h>)
{
	char ch[3];//�����ַ���
	int i;

	for (i=1;i<=(int)strlen(string)/2+1;i++)
	{	
		ch[0]=string[2*i-2];
		ch[1]=string[2*i-1];
		ch[2]='\0';
		DrawString(ch);
		WaitFor(delay);
	}

	return;
}

void show_staff(void)
{
	MovePen(0,250);
	SetPenColor(DARK_BLUE);
	act_string("����С���Ա:",40);

	MovePen(130,240);
	DrawBitmap("bitmap//����.bmp");

	WaitFor(300);

	MovePen(480,240);
	DrawBitmap("bitmap//������.bmp");

	WaitFor(300);

	MovePen(830,240);
	DrawBitmap("bitmap//˾��.bmp");

	WaitFor(2000);

	MovePen(130,240);
	DrawBitmap("bitmap//���γ�.bmp");

	WaitFor(300);

	MovePen(480,240);
	DrawBitmap("bitmap//������.bmp");

	WaitFor(300);

	MovePen(830,240);
	DrawBitmap("bitmap//�θ�.bmp");

	return;
}

int dealwith_key(int num)
{
	void clean(int order);

	switch(num)
	{
	case 0:
		delay=1000;
		ratio=5;
		strategy=1;

		clean(0);clean(1);clean(2);	//unvalue all keys
		MovePen(key[0].leftup_x,key[0].leftup_y);
		DrawBitmap(key[0].bitmapR_name);
		MovePen(key[4].leftup_x,key[4].leftup_y);
		DrawBitmap(key[4].bitmapR_name);
		MovePen(key[12].leftup_x,key[12].leftup_y);
		DrawBitmap(key[12].bitmapR_name);
		MovePen(key[13].leftup_x,key[13].leftup_y);
		DrawBitmap(key[13].bitmapR_name);

		break;

	case 1: break;
	case 2:
		is_showed=1;
		show_staff();
		break;

	//change delay
	case 3:
	case 4:
	case 5:
	case 6:
	case 7:
		switch(num)
		{
		case 3: delay=500; break;
		case 4:	delay=1000; break;
		case 5: delay=1500; break;
		case 6: delay=2000; break;
		case 7: delay=3000; break;
		}
		clean(0);
		MovePen(key[num].leftup_x,key[num].leftup_y);
		DrawBitmap(key[num].bitmapR_name);
		//unvalue default
		MovePen(key[0].leftup_x,key[0].leftup_y);
		DrawBitmap(key[0].bitmapB_name);

		break;

	//change ratio
	case 8:
	case 9:
	case 10:
	case 11:
	case 12:
		ratio=num-7;
		clean(1);
		MovePen(key[num].leftup_x,key[num].leftup_y);
		DrawBitmap(key[num].bitmapR_name);
		//unvalue default
		MovePen(key[0].leftup_x,key[0].leftup_y);
		DrawBitmap(key[0].bitmapB_name);

		break;

	//change strategy
	case 13:
	case 14:
	case 15:
	case 16:
	case 17:
		strategy=num-12;
		clean(2);
		MovePen(key[num].leftup_x,key[num].leftup_y);
		DrawBitmap(key[num].bitmapR_name);
		//unvalue default
		MovePen(key[0].leftup_x,key[0].leftup_y);
		DrawBitmap(key[0].bitmapB_name);

		break;

	case 18: return -1;
	
	case 19: return 1;
	}
	return 0;
}

void clean(int order)
{
	const int sort[3]={2,7,12};
	int i;/*counter*/

	for(i=1;i<=5;i++)
	{
		MovePen(key[sort[order]+i].leftup_x,key[sort[order]+i].leftup_y);
		DrawBitmap(key[sort[order]+i].bitmapB_name);
	}
}