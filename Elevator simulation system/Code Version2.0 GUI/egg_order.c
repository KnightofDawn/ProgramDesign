#include "elevator struct.h"

extern HEGG main_egg;//�����ľ��
int bitmap=0;

typedef struct
{
	char order;//��Ӧ����������ַ�
	int value;//0��ʾ������ 1��ʾ������
}Order;

mouse find_order(char order);//�����Ӧָ����ض�Ӧָ�����Ϣ��mouse�������ݣ�
void reversal_bitmap(Order current);//����ָ���Ӧ���ַ�������ı��ָ���Ӧ��ͼƬ��0��1��1��0��
void egg_order_change(Order current[],Order previous[],int size);
/*������ǰʱ�̺�ǰһʱ�̵�ָ�����(�±��0��ʼ)���Լ�ָ������Ĵ�С(size),����ָ������л�*/

void egg_order()
{
	const char ask_ch[]={"0123456789IUYTREWQKJHGFDSA"};

	static Order previous[26];//��һʱ�̵�ָ��״��(�±��0��ʼ)
	static Order current[26];//��ǰʱ�̵�ָ��״��(�±��0��ʼ)
	static int flag=0;//flag=0��ʾ��һ�ε��ñ�����
	int i;

	void egg_trans(Order current[26]);//egg_order.c�����ڱ���ת�����������

	if(!flag)
		for (i=0;i<26;i++)
		{
			previous[i].order=ask_ch[i];
			current[i].order=ask_ch[i];
			flag=1;
		}//ָ���ַ���ʼ��

	for (i=1;i<26;i++)
		current[i].value=0;

	egg_trans(current);//ת������
	egg_order_change(current,previous,26);

	for (i=0;i<=25;i++)
		previous[i]=current[i];
	return;
}

void egg_order_change(Order current[],Order previous[],int size)
/*������ǰʱ�̺�ǰһʱ�̵�ָ�����(�±��0��ʼ)���Լ�ָ������Ĵ�С(size),����ָ������л�*/
{
	int i;

	for (i=0;i<size;i++)
		if (current[i].value!=previous[i].value)//ָ������б仯
		//	while (main_egg!=GetActiveEgg());
			reversal_bitmap(current[i]);//�ı��ָ���Ӧ��ͼƬ

	return;
}

mouse find_order(char order)//�����Ӧָ����ض�Ӧָ�����Ϣ��mouse�������ݣ�
{
	int i;
	for (i=0;i<KEY_AMOUNT;i++)
		if (click_position[i].order==order)
			return click_position[i];
	return click_position[i-1];
}

void reversal_bitmap(Order current)//����ָ���Ӧ���ַ�������ı��ָ���Ӧ��ͼƬ��0��1��1��0��
{
	mouse click;//��ǰ�ļ�

	click=find_order(current.order);//������Ҫ�ı�ļ�

	if(current.value==1)//��Ҫ0��1,�ĳɴ���Ӧ
	{
		while(animation==1);

		bitmap=1;
		SetActiveEgg(main_egg);
		MovePen(click.leftup_x,click.leftup_y);
		DrawBitmap(click.bitmap_name2);
		bitmap=0;
	}
	else//��Ҫ1��0���ĳ�������
	{
		while (animation==1);

		bitmap=1;
		SetActiveEgg(main_egg);
		MovePen(click.leftup_x,click.leftup_y);
		DrawBitmap(click.bitmap_name1);
		bitmap=0;
	}

	return;
}

void egg_trans(Order current[26])//egg_order.c�����ڱ���ת�����������
{
	int i;
	int floor=0;

	for (i=1;i<=size;i++)
	{
		if (input[i].is_done==0)//û�б���Ӧ������
		{
			if (input[i].order<='9' && input[i].order>=1)//�ڲ�����(0 ~ 9)
				current[input[i].order-48].value=1;

			else//�ⲿ����
			{
				switch (input[i].order)
				{
				case 'I':case 'i'://�˲�����
					current[10].value=1;
					break;
				case 'U':case 'u'://�߲�����
					current[11].value=1;
					break;
				case 'Y':case 'y'://��������
					current[12].value=1;
					break;
				case 'T':case 't'://�������
					current[13].value=1;
					break;
				case 'R':case 'r'://�Ĳ�����
					current[14].value=1;
					break;
				case 'E':case 'e'://��������
					current[15].value=1;
					break;
				case 'W':case 'w'://��������
					current[16].value=1;
					break;
				case 'Q':case 'q'://һ������
					current[17].value=1;
					break;
				case 'K':case 'k'://�Ų�����
					current[18].value=1;
					break;
				case 'J':case 'j'://�˲�����
					current[19].value=1;
					break;
				case 'H':case 'h'://�߲�����
					current[20].value=1;
					break;
				case 'G':case 'g'://��������
					current[21].value=1;
					break;
				case 'F':case 'f'://�������
					current[22].value=1;
					break;
				case 'D':case 'd'://�Ĳ�����
					current[23].value=1;
					break;
				case 'S':case 's'://��������
					current[24].value=1;
					break;
				case 'A':case 'a'://��������
					current[25].value=1;
					break;
				default:
					break;
				}

			}
		}
	}//����ת�����

	return;
}
