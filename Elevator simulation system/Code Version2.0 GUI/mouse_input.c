#include <stdio.h>
#include "egg.h"
#include "cmc.h"

extern int is_asked(char order);//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
extern void egg_order();
int hongfu_legal(char order);//�ж������Ƿ�Ϸ�,�Ϸ�����1�����򷵻�0


int mouse_input()
{
	int i,mx,my,event;
//	EVENT_TYPE WaitForEvent();
//	double GetMouseX(void);
//	double GetMouseY(void);

	while (initial==0);
	while( (event=WaitForEvent()) !=EXIT)
	{
		if (strategy==5 && event==MOUSEMOVE && (GetMouseX()<=610 && GetMouseX()>=590) && (GetMouseY()<=350 && GetMouseY()>=20))//���ŷ�Χ��
		{
			printf("\a");

			continue;
		}

		if (event==KEYDOWN)
		{
			mx=(int)GetMouseX();
			my=(int)GetMouseY();
			for(i=0;i<KEY_AMOUNT;i++)
				if(mx>=key_position[i].leftup_x &&
					mx<=key_position[i].rightdown_x &&
					my>=key_position[i].rightdown_y &&
					my<=key_position[i].leftup_y  &&
					is_asked(key_position[i].order)==0 &&
					(strategy!=5 || hongfu_legal(key_position[i].order)==1) )
				{
					if (key_position[i].order=='O' ||
						key_position[i].order=='P' ||
						key_position[i].order=='L' ||
						key_position[i].order=='N' ||
						key_position[i].order=='M' ||
						key_position[i].order=='0' ||
						key_position[i].order=='Z' ||
						key_position[i].order=='B')
					{
						if (key_position[i].order=='O')//�����ȷ���
							strategy=1;
						if (key_position[i].order=='P')//˳�����
							strategy=2;
						if (key_position[i].order=='L')//�����Ӧ
							strategy=3;
						if (key_position[i].order=='N')//���ƽ���ȴ�ʱ��
							strategy=4;
						if (key_position[i].order=='M')//�긣����
							strategy=5;
						if (key_position[i].order=='0')//GO��
							is_go=1;
						if (key_position[i].order=='Z')//��GO��
							is_go=0;
						if (key_position[i].order=='B')//���ż�
						{
							if (!(strategy==5))
								break;
							else
							{
								input[++size].order=key_position[i].order;
								input[size].time=system_time;
								input[size].is_done=0;

							}
						}
					}
					else
					{
						input[++size].order=key_position[i].order;
						input[size].time=system_time;
						input[size].is_done=0;

						
						if (condition==-2)
							condition=1;//��ʼ��Ϊ����
					}
					break;
				}
				egg_order();
		}
		
	}
	return 0;
}

int hongfu_legal(char order)//�ж������Ƿ�Ϸ�,�Ϸ�����1�����򷵻�0
{
	int i;
	char hongfu[]="2345KJHGUYTRkjhguytr";//�긣������û�е�ָ��
	
	for (i=0;i<=19;i++)
		if (order==hongfu[i])
			return 0;
	
	return 1;
}
