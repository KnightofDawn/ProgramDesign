/*
  problem:���Ҫ�����ⲿ�����������У�����������ʲô��ͬ��Ӱ���أ�ò�ƶԱ�����û��Ӱ�졭��
		  ���⻶ӭ��λָ�����Թ����еĸ���Bug~���˲�ʤ�м�~ ����Map.Blair(4-27)
*/
#include "cmc.h"
#include <stdio.h>

void fastest_respond(Input input[],int size,int system_time,int output[],int condition)
/*
	��������:�����Ӧ���Ժ�����ͨ���������ݵ�״̬���û����󣬽�ָ�����output[]�����ı�condition
	����˵��:input[]�Ǵ洢�û�������ָ�����char order �� int time����������size�ǵ�ǰ�ṹ������input[]
			 ��ָ�������system_time��ʾ��ǰ��ϵͳʱ�䣬output[]������ݵ�ָ��(�±�Ϊʱ��)��conditon��ʾ
			 ���ݵ�ǰ��״̬��0��ʾֹͣ 1���� -1�½� -2��ʾ����������
	ָ���Ӧ��ϵ:1-9��������ڳ˿Ͱ�Ŀ�갴ť��Q��W��E��R��T��Y��I��O��Ӧ8�㵽1�����������
				A��S��D��F��G��H��J��K��ʾ9�㵽2�����������
*/
{		

	void trans(Input input[],int size,C_INT inner_ask[10],C_INT2 outer_ask[10],int system_time,int current_floor);
	/*
		��������:���û���ָ��ת��������
		����˵��:inner_ask[10].value(=1��ʾ�Ѿ����� =0��ʾû�а���)
				 outer_ask[10].value(=0��ʾ������ =1��ʾ���������� =-1��ʾ���������� =2��ʾ����������)
	*/
	int count_time(C_INT inner_ask[10],C_INT2 outer_ask[10],int floor,int condition);
	//��������condition����1->'u' or -1->'d'�������ʱ��

	int max3(int a,int b,int c);//����3���������ֵ
	int min3(int a,int b,int c);//����3��������Сֵ

	C_INT inner_ask[10]={0,0};//�����ⲿָ��,�±��1��ʼ
	C_INT2 outer_ask[10]={0,0};//�����ڲ�ָ��,�±��1��ʼ
	int current_floor;
	

	current_floor=output[system_time];
	trans(input,size,inner_ask,outer_ask,system_time,current_floor);//ת���û�������
	if (inner_ask[0].value==-2)//conditionΪ����
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
		if (outer_ask[current_floor].value==condition)//�ⲿǡ���ҽ���һ��������Ӧ������	
		{
			outer_ask[current_floor].value=0;
			if (condition==1)
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
			outer_ask[current_floor].value=(-condition);
	
			if (condition==1)
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
			if (count_time(inner_ask,outer_ask,current_floor+condition,condition)*5 > count_time(inner_ask,outer_ask,current_floor+condition,-condition)*6) 
			//��Ҫ��Ӧ�����󲢵�ͷ
			{
				outer_ask[current_floor].value=0;
				if (condition==1)
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
	if (count_time(inner_ask,outer_ask,current_floor,condition)*5 < count_time(inner_ask,outer_ask,current_floor,-condition)*6) 
		output[system_time+1]=current_floor+condition;//���ֵ�ǰ�н�״̬

	else
		output[system_time+1]=current_floor-condition;//��ͷ

	return;
}

 void trans(Input input[],int size,C_INT inner_ask[10],C_INT2 outer_ask[10],int system_time,int current_floor)
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
		if (input[i].is_done==0)//û�б���Ӧ������
		{
			flag=1;
			if (input[i].order<='9' && input[i].order>=1 && !(input[i].time==system_time-1 && input[i].order==current_floor+48) )//�ڲ�����
			{
				inner_ask[input[i].order-48].time=system_time-input[i].time;
				inner_ask[input[i].order-48].value=1;
				inner_ask[input[i].order-48].index=i;
			}

			else//�ⲿ����
			{
				switch (input[i].order)
				{
				case 'Q':case 'q'://�˲�����
					floor=8;
					break;
				case 'W':case 'w'://�߲�����
					floor=7;
					break;
				case 'E':case 'e'://��������
					floor=6;
					break;
				case 'R':case 'r'://�������
					floor=5;
					break;
				case 'T':case 't'://�Ĳ�����
					floor=4;
					break;
				case 'Y':case 'y'://��������
					floor=3;
					break;
				case 'U':case 'u'://��������
					floor=2;
					break;
				case 'I':case 'i'://һ������
					floor=1;
					break;
				case 'A':case 'a'://�Ų�����
					floor=-9;
					break;
				case 'S':case 's'://�˲�����
					floor=-8;
					break;
				case 'D':case 'd'://�߲�����
					floor=-7;
					break;
				case 'F':case 'f'://��������
					floor=-6;
					break;
				case 'G':case 'g'://�������
					floor=-5;
					break;
				case 'H':case 'h'://�Ĳ�����
					floor=-4;
					break;
				case 'J':case 'j'://��������
					floor=-3;
					break;
				case 'K':case 'k'://��������
					floor=-2;
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
	if (flag==0)
		inner_ask[0].value=-2;

	return;
}	

int count_time(C_INT inner_ask[10],C_INT2 outer_ask[10],int floor,int condition)
	//��������condition����1->'u' or -1->'d'�������ʱ��
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

	for (i=1;i<=floor-1;i++)
	{
		if ((outer_ask[i].value==1 || outer_ask[i].value==2) && (low_up < i || low_up==10))//������У���ǰ¥�����棩
			low_up=i;
		if ((outer_ask[i].value==-1 || outer_ask[i].value==2) && (low_down < i || low_down==10))//������У���ǰ¥�����棩
			low_down=i;
	}	
	for (i=floor+1;i<=9;i++)
	{
		if ((outer_ask[i].value==1 || outer_ask[i].value==2) && high_up < i)//������У���ǰ¥�����棩
			high_up=i;
		if ((outer_ask[i].value==-1 || outer_ask[i].value==2) && high_down < i)//������У���ǰ¥�����棩
			high_down=i;
	}

	if (condition==1)
	{
		if (max3(max_in,high_up,high_down) > floor)//��Ҫ����
		{
			time+=max3(max_in,high_up,high_down)-floor;

			if (min3(min_in,low_up,low_down) >= floor)//����Ҫ������
				return high_down==0?time:time+max3(max_in,high_up,high_down)-high_down;
			else
			{
				time*=2;//���е�ԭλ��
				time+=floor-min3(min_in,low_up,low_down);

				return low_up==10?time:time+low_up-min3(min_in,low_up,low_down);
			}
		}
		else
			return 360;//��Դ˲��Ա�Ȼ�����в��У���˷������ֵ
	}	
	else 
	{
		if (min3(min_in,low_up,low_down) < floor)//��Ҫ����
		{
			time+=floor-min3(min_in,low_up,low_down);

			if (max3(max_in,high_up,high_down) <= floor)//����Ҫ����
				return low_up==10?time:time+low_up-min3(min_in,low_up,low_down);
			else
			{
				time*=2;//���е�ԭλ��
				time+=max3(max_in,high_up,high_down)-floor;

				return high_down==0?time:time+max3(max_in,high_up,high_down)-high_down;
			}
		}	
		else
			return 360;
	}
	
}

int max3(int a,int b,int c)//����3���������ֵ
{
	int max;

	max=a;
	if (max<b)
		max=b;
	if (max<c)
		max=c;

	return max;
}

int min3(int a,int b,int c)//����3��������Сֵ
{
	int min;

	min=a;
	if (min>b)
		min=b;
	if (min>c)
		min=c;

	return min;
}
