#include "elevator struct.h"

int is_repeating(char order);//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
void egg_order();


int mouse_input()
{
	int i,mx,my,event;

	while(initial==0);
	while((event=WaitForEvent()) !=EXIT)
	{
		if(event==KEYDOWN)
		{
			mx=(int)GetMouseX();
			my=(int)GetMouseY();
			for(i=0;i<KEY_AMOUNT;i++)
				if(mx>=click_position[i].leftup_x &&
					mx<=click_position[i].rightdown_x &&
					my>=click_position[i].rightdown_y &&
					my<=click_position[i].leftup_y  &&
					is_repeating(click_position[i].order)==0)
				{
					if (click_position[i].order=='O' ||
						click_position[i].order=='P' ||
						click_position[i].order=='L' ||
						click_position[i].order=='N' ||
						click_position[i].order=='X' ||
						click_position[i].order=='Z')
					{
					    switch(click_position[i].order)
					    {
					        case 'O'://�����ȷ���
                                strategy=1;
                                break;
                            case 'P'://˳�����
                                strategy=2;
                                break;
                            case 'L'://�����Ӧ
                                strategy=3;
                                break;
                            case 'N'://���ƽ���ȴ�ʱ��
                                strategy=4;
                                 break;
                            case 'X'://GO��
                                is_go=1;
                                break;
                            case 'Z'://��GO��
                                is_go=0;
                                break;
					    }

					}
					else
					{
						input[++size].order=click_position[i].order;
						input[size].time=system_time;
						input[size].is_done=0;

						if (dir==-2)
							dir=1;//��ʼ��Ϊ����
					}
					break;
				}
				egg_order();
		}

	}
	return 0;
}
