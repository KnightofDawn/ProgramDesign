#include <string.h>
#include "egg.h"
#include "cmc.h"

extern HEGG main_egg;//�����ľ��
void act_string(char *string,int delay);//����Ҫ��ӡ���ַ����������ֵ�ʱ����,���ַ���̬��ӡ(Ҫ����<string.h>)

void egg_tips2()//���ݽ����и��������ܽ���
{
	HEGG second_egg; 
	char infor3[]="��Ҳ�Ҫ�ļ�����ʹ��֮ǰ�����������˵���ɣ�����������õ�ʹ��201021131603С���ģ�����"; 
	
    second_egg=LayEgg();
    DrawBitmap("bitmap//��ʼ2.bmp");
	ChangeEggLayer(TOP);
    
    MovePen(300,670);
    SetPenColor(BLUE);
    act_string(infor3,50);
    
    //����ѡ����ʹ��˵�� 
    SetPenColor(MAGENTA);
    MovePen(10,650);
    DrawBitmap("bitmap//celue1.bmp");
    MovePen(260,630);
    DrawString("1:�����ȷ������");
	MovePen(260,587);
	DrawString("2:˳��������"); 
	MovePen(260,544);
	DrawString("3:�����Ӧ����");
	MovePen(260,501);
	DrawString("4:���ƽ��ʱ�����");
	MovePen(260,458);
	DrawString("5:�긣����");
	MovePen(260,420);
	SetPenColor(BLACK);
	DrawString("(ע:������ֿ���");
	MovePen(260,400);
	DrawString("�ı�ɶ�Ӧ�Ĳ���)");
	SetPenColor(MAGENTA);
	WaitFor(500);
	
	//�����ڲ���ͷʹ��˵��
	MovePen(10,300);
	DrawBitmap("bitmap//�ڲ�����.bmp");
	MovePen(150,280);
	DrawString("�����ڲ�������������");
	
	MovePen(10,210);
	DrawBitmap("bitmap//�ڲ�����.bmp");
	MovePen(150,190);
	DrawString("�����ڲ�������������"); 
	
	MovePen(10,120);
	DrawBitmap("bitmap//�ڲ�ͣ.bmp");
	MovePen(150,100); 
	DrawString("�����ڲ������ݴ���ֹͣ״̬");
	
	MovePen(10,45);
	DrawBitmap("bitmap//��GO1.bmp");
	MovePen(100,30);
	DrawString("�����ڲ�����ʹ��GO������������");
	WaitFor(500);
	
	//�����ⲿ��ͷ˵��
	SetPenColor(DARK_MAGENTA);
    MovePen(430,650);
    DrawBitmap("bitmap//�ⲿ��1.bmp"); 
    MovePen(500,630);
    DrawString("��ʱδ��������ʾ���ݵ�");
	MovePen(500,610);
	DrawString("ǰ��������(���¼�ͷͬ��)");
    
    MovePen(430,550);
    DrawBitmap("bitmap//�ⲿ��2.bmp");
    MovePen(500,530);
    DrawString("��ʱ�ѵ�������ʾ���ݵ�"); 
	MovePen(500,510);
    DrawString("ǰ��������(���¼�ͷͬ��)"); 

	WaitFor(500);

    MovePen(430,450);
    DrawBitmap("bitmap//�ⲿ����2.bmp");
    MovePen(500,450);
    DrawString("�����ⲿĳһ¥�����������ڿ���״̬");
	
	MovePen(430,400);
	DrawBitmap("bitmap//�ⲿ����2.bmp");
	MovePen(500,400);
	DrawString("�����ⲿĳһ¥�����������ڿ���״̬");
	
	MovePen(430,350);
	DrawBitmap("bitmap//�ⲿ����.bmp");
	MovePen(500,350);
	DrawString("�����ⲿĳһ¥������������");
	
	MovePen(430,300);
	DrawBitmap("bitmap//�ⲿ����.bmp");
	MovePen(500,300);
	DrawString("�����ⲿĳһ¥������������");
	
	MovePen(430,45);
	DrawBitmap("bitmap//GO1.bmp");
	MovePen(500,30);
	DrawString("�����ڲ���ʹ��GO������������"); 
	
	MovePen(400,200);
	DrawBitmap("bitmap//strategy1-1.bmp");
	MovePen(420,130);
	DrawString("ʵʱ��ʾ��������ʹ�õĲ���"); 
	WaitFor(500);
	
	//�����ڲ�����˵��
	SetPenColor(BLACK);
	MovePen(830,650);
	DrawBitmap("bitmap//��1.bmp");
	MovePen(960,620);
	DrawString("�����ڲ���ʾ�ĵ�ǰ��������¥��"); 
	
	MovePen(830,550);
	DrawBitmap("bitmap//�ڲ�1-2.bmp");
	MovePen(905,545);
	DrawString("�����ڲ�������¥��δ������");
	
	MovePen(830,450);
	DrawBitmap("bitmap//�ڲ�1-1.bmp");
	MovePen(905,445);
	DrawString("�����ڲ��ж�ȥ����¥�������"); 
		
	//�����ⲿ����˵��
	MovePen(830,380);
	DrawBitmap("bitmap//�ⲿ1.bmp");
	MovePen(905,360);
	DrawString
	("�����ⲿ��ʾ��ǰ���������ڵ�¥��");
	WaitFor(500);
	
	MovePen(840,310);
	DrawBitmap("bitmap//��ʾ.bmp");

	WaitFor(5000);

	EatEgg();

	return; 
} 

