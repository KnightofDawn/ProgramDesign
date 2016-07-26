/*
  problem:���Ҫ�����ⲿ�����������У�����������ʲô��ͬ��Ӱ���أ�ò�ƶԱ�����û��Ӱ�졭��
		  ���⻶ӭ��λָ�����Թ����еĸ���Bug~���˲�ʤ�м�~ ����Mr.Phoebe coding studio(4-27)
		  �����Ӧ���ԣ�
		��Ӧ�������ڴ��ڵ����к��к�Ŀ������ʱ�䣨���ò�ͬ��������ͣ��ʱ����ͬ�����Բ��ؿ��ǣ���̵Ĳ��ԡ�
		��ѡ����һ�ǵ���������������Ӧ���������Ŀ������Ϻ��У�������������Ӧ�������º����Լ�;�������Ŀ�꣬
		�����������Ӧʣ������Ϻ��С�����ǡ���෴�������£������ϣ�������������С�
		���ں��к�Ŀ�����ʱ���ӣ�����ʵ������ʱ���ֲ��Բ����á�������ʱ�⽫���µ���ͻȻ���෴�ķ������С�
		Ϊ�˷�ֹ�����Եĸı䷽�����ǲ����趨ֻ�е�ԭ�������з�����෴����Ĵ��۸�20%��ʱ����л����� 

*/
#include "elevator struct.h"


void fastest_respond(Input input[],int size,int system_time,int output[],int direction)
/*
	��������:�����Ӧ���Ժ�����ͨ���������ݵ�״̬���û����󣬽�ָ�����output[]�����ı�direction
	����˵��:input[]�Ǵ洢�û�������ָ�����char order �� int time����������size�ǵ�ǰ�ṹ������input[]
			 ��ָ�������system_time��ʾ��ǰ��ϵͳʱ�䣬output[]������ݵ�ָ��(�±�Ϊʱ��)��conditon��ʾ
			 ���ݵ�ǰ��״̬��0��ʾֹͣ 1���� -1�½� -2��ʾ����������
	ָ���Ӧ��ϵ:1-9��������ڳ˿Ͱ�Ŀ�갴ť��Q��W��E��R��T��Y��I��O��Ӧ1�㵽8�����������
				A��S��D��F��G��H��J��K��ʾ2�㵽9�����������
*/
{		

	void trans(Input input[],int size,C_fast1 inner_ask[10],C_fast2 outer_ask[10],int system_time,int current_floor);
	/*
		��������:���û���ָ��ת��������
		����˵��:inner_ask[10].value(=1��ʾ�Ѿ����� =0��ʾû�а���)
				 outer_ask[10].value(=0��ʾ������ =1��ʾ���������� =-1��ʾ���������� =2��ʾ����������)
	*/
	int count_time(C_fast1 inner_ask[10],C_fast2 outer_ask[10],int floor,int direction);
	//��������direction����1��ʾ'up'��-1��ʾ'down'�������ʱ��

	int max_3(int a,int b,int c);//����3���������ֵ
	int min_3(int a,int b,int c);//����3��������Сֵ

	C_fast1 inner_ask[10]={0,0};//�����ⲿָ��,�±��1��ʼ
	C_fast2 outer_ask[10]={0,0};//�����ڲ�ָ��,�±��1��ʼ
	int current_floor;
	

	current_floor=output[system_time];
	trans(input,size,inner_ask,outer_ask,system_time,current_floor);//ת���û�������
	if (inner_ask[0].value==-2)//directionΪ����
	{
		output[system_time+1]=output[system_time]*100;
		return;
	}
//�ж��Ƿ�Ҫͣ
	if (inner_ask[current_floor].value==1)//�ڲ�������
	{
		output[system_time+1]=current_floor;
		input[ inner_ask[current_floor].index ].is_done=1;

		inner_ask[current_floor].value=0;
		inner_ask[current_floor].index=0;

		return;
	}
		
	if (outer_ask[current_floor].value!=0)//�ⲿ������
	{
		if (outer_ask[current_floor].value==direction)//�ⲿǡ���ҽ���һ��������Ӧ������	
		{
			outer_ask[current_floor].value=0;
			if (direction==1)//������ͬ����Ӧ���
			{
				input[ outer_ask[current_floor].index_up ].is_done=1;
				outer_ask[current_floor].index_up=0;//���ָ��
			}
			else
			{
				input[ outer_ask[current_floor].index_down ].is_done=1;
				outer_ask[current_floor].index_down=0;//���ָ��
			}

			output[system_time+1]=current_floor;

			return;
		}
		else if (outer_ask[current_floor].value==2)//����������
		{
			outer_ask[current_floor].value=(-direction);
	
			if (direction==1)
			{
				input[ outer_ask[current_floor].index_up ].is_done=1;
				outer_ask[current_floor].index_up=-1;//����ָ��
			}
			else
			{				
				input[ outer_ask[current_floor].index_down ].is_done=1;
				outer_ask[current_floor].index_down=1;//ָ��
			}

			output[system_time+1]=current_floor;

			return;
		}
		else//��һ���෴���������
		{
			if (count_time(inner_ask,outer_ask,current_floor+direction,direction)*5 > count_time(inner_ask,outer_ask,current_floor+direction,-direction)*6) //20%���ͷ
			//��Ҫ��Ӧ�����󲢵�ͷ
			{
				outer_ask[current_floor].value=0;
				if (direction==1)
				{
					input[ outer_ask[current_floor].index_down ].is_done=1;
					outer_ask[current_floor].index_down=0;//���ָ��
				}
				else
				{
					input[ outer_ask[current_floor].index_up].is_done=1;
					outer_ask[current_floor].index_up=0;//���ָ��
				}

				output[system_time+1]=current_floor;

				return;
			}	
		}
	}
//�ж��Ƿ�Ҫͣ


//��ǰ¥��û����Ҫͣ��������
	if (count_time(inner_ask,outer_ask,current_floor,direction)*5 < count_time(inner_ask,outer_ask,current_floor,-direction)*6) 
		output[system_time+1]=current_floor+direction;//���ֵ�ǰ�н�״̬

	else
		output[system_time+1]=current_floor-direction;//��ͷ

	return;
}

int max_3(int a,int b,int c)//����3���������ֵ
{
	int maxn=max(a,b);
	return max(maxn,c);
}

int min_3(int a,int b,int c)//����3��������Сֵ
{
	int mi=min(a,b);
	return min(mi,c);
}

 void trans(Input input[],int size,C_fast1 inner_ask[10],C_fast2 outer_ask[10],int system_time,int current_floor)
/*
	��������:���û���ָ��ת��������
	����˵��:inner_ask[10].value(=1��ʾ�Ѿ����� =0��ʾû�а���)
			 outer_ask[10].value(=0��ʾ������ =1��ʾ���������� =-1��ʾ���������� =2��ʾ����������)
*/
{
	int i;
	int floor=0;
	int flag=0;

	for (i=1;i<=size;i++)
	{
		if (!input[i].is_done)//û�б���Ӧ������
		{
			flag=1;
			if (input[i].order<='9' && input[i].order>='1' && !(input[i].time==system_time-1 && input[i].order==current_floor+48) )//�ڲ�����
			{
				inner_ask[input[i].order-48].time=system_time-input[i].time;
				inner_ask[input[i].order-48].value=1;
				inner_ask[input[i].order-48].index=i;
			}

			else//�ⲿ����
			{
				switch (input[i].order)
				{
					case 'Q':case 'q'://һ������
						floor=1;
						break;
					case 'W':case 'w'://��������
						floor=2;
						break;
					case 'E':case 'e'://��������
						floor=3;
						break;
					case 'R':case 'r'://�Ĳ�����
						floor=4;
						break;
					case 'T':case 't'://�������
						floor=5;
						break;
					case 'Y':case 'y'://��������
						floor=6;
						break;
					case 'U':case 'u'://�߲�����
						floor=7;
						break;
					case 'I':case 'i'://�˲�����
						floor=8;
						break;
					case 'A':case 'a'://��������
						floor=-2;
						break;
					case 'S':case 's'://��������
						floor=-3;
						break;
					case 'D':case 'd'://�Ĳ�����
						floor=-4;
						break;
					case 'F':case 'f'://�������
						floor=-5;
						break;
					case 'G':case 'g'://��������
						floor=-6;
						break;
					case 'H':case 'h'://�߲�����
						floor=-7;
						break;
					case 'J':case 'j'://�˲�����
						floor=-8;
						break;
					case 'K':case 'k'://�Ų�����
						floor=-9;
						break;
					default:
						break;
				}
				if (floor<0 && !(current_floor==(-floor) && input[i].time==system_time-1))
				{
					if (outer_ask[-floor].value==1)//�Ѿ�����������
						outer_ask[-floor].value=2;			
					else
						outer_ask[-floor].value=-1;

					outer_ask[-floor].time_down=system_time-input[i].time;
					outer_ask[-floor].index_down=i;
				}
				else if (floor>0 && !(current_floor==floor && input[i].time==system_time-1))
				{
					if (outer_ask[floor].value==-1)//�Ѿ�����������
						outer_ask[floor].value=2;
					else
						outer_ask[floor].value=1;

					outer_ask[-floor].time_up=system_time-input[i].time;
					outer_ask[floor].index_up=i;
				}
			}
		}
	}//����ת�����
	if (!flag)
		inner_ask[0].value=-2;

	return;
}	

int count_time(C_fast1 inner_ask[10],C_fast2 outer_ask[10],int current_floor,int direction)
	//��������direction����1->'u' or -1->'d'�������ʱ��
{
	int max_in=0,min_in=10;//���浱ǰ����¥���ڲ����ⲿ�������С¥��
	int i,time=0;
	int high_up=0,high_down=0,low_up=10,low_down=10;
	
	for (i=1;i<=9;i++)
	{
		if (inner_ask[i].value==1 && min_in > i)
			min_in=i;
		if (inner_ask[i].value==1 && max_in < i)
			max_in=i;
	}//Ѱ���ڲ���ֵ

	for (i=1;i<=current_floor-1;i++)
	{
		if ((outer_ask[i].value==1 || outer_ask[i].value==2) && (low_up < i || low_up==10))//������У���ǰ¥�����棩
			low_up=i;
		if ((outer_ask[i].value==-1 || outer_ask[i].value==2) && (low_down < i || low_down==10))//������У���ǰ¥�����棩
			low_down=i;
	}	
	for (i=current_floor+1;i<=9;i++)
	{
		if ((outer_ask[i].value==1 || outer_ask[i].value==2) && high_up < i)//������У���ǰ¥�����棩
			high_up=i;
		if ((outer_ask[i].value==-1 || outer_ask[i].value==2) && high_down < i)//������У���ǰ¥�����棩
			high_down=i;
	}//Ѱ���ⲿ��ֵ

	if (direction==1)
	{
		if (max_3(max_in,high_up,high_down) > current_floor)//��Ҫ����
		{
			time+=max_3(max_in,high_up,high_down)-current_floor;

			if (min_3(min_in,low_up,low_down) >= current_floor)//����Ҫ������
				return high_down==0?time:time+max_3(max_in,high_up,high_down)-high_down;//û�����µ�����ͣ����ߵ㣩�������µ�����ͣ�������������ߵ㣩
			else
			{
				time*=2;//���е�ԭλ��(����)
				time+=current_floor-min_3(min_in,low_up,low_down);

				return low_up==10?time:time+low_up-min_3(min_in,low_up,low_down);
			}
		}
		else
			return 360;//��Դ˲��Ա�Ȼ�����в��У���˷������ֵ
	}	
	else 
	{
		if (min_3(min_in,low_up,low_down) < current_floor)//��Ҫ����
		{
			time+=current_floor-min_3(min_in,low_up,low_down);

			if (max_3(max_in,high_up,high_down) <= current_floor)//����Ҫ����
				return low_up==10?time:time+low_up-min_3(min_in,low_up,low_down);
			else
			{
				time*=2;//���е�ԭλ��
				time+=max_3(max_in,high_up,high_down)-current_floor;

				return high_down==0?time:time+max_3(max_in,high_up,high_down)-high_down;
			}
		}	
		else
			return 360;
	}
	
}


