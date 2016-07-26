/*	
  problem:���ڵȴ�ʱ����㲻�Ǻ���ȷ�����ҳ������Ըо������Ǻ��ȶ������׳��ַ�����˼�Ĵ���ϣ����Ҽ�ʱָ����
		  �Ա㷢�ָ�������⣬лл������������Mr.Phoebe coding studio(5-7)
	���ƽ���ȴ�ʱ����ԣ�
	����ÿһ����¥��ȴ���������ÿһĿ��¥���߳����ݵ�������ȡ�������Ӧ��ǰ���к��к�Ŀ��ȫ���˿�����ʱ����ܺ�
	�������ȴ�ʱ��͵�������ʱ�䣬����������ж���δ������ݵĳ˿���ֻ����ȴ�ʱ�䣩��
	�������ֲ��ԣ�������Ҳ��ֻ����3һ��������ѡ�񷽰������ں��к�Ŀ�����ʱ���ӣ�
	����ʵ�������ֲ�����ʱ�����ã������������Ӧʱ����Խ�Ϊ�ȶ��͸�Ч��
	������ʱ�⽫���µ���ͻȻ���෴�ķ������С�
	Ϊ�˷�ֹ�����Եĸı䷽�����ǲ����趨ֻ�е�ԭ���ķ�����������Ĵ��۸�20%��ʱ����л����з���

*/
#include "elevator struct.h"


void least_wait(Input input[],int size,int system_time,int output[],int direction)
/*
	��������:���ƽ���ȴ�ʱ�亯����ͨ���������ݵ�״̬���û����󣬽�ָ�����output[]�����ı�direction
	����˵��:input[]�Ǵ洢�û�������ָ�����char order �� int time����������size�ǵ�ǰ�ṹ������input[]
			 ��ָ�������system_time��ʾ��ǰ��ϵͳʱ�䣬output[]������ݵ�ָ��(�±�Ϊʱ��)��conditon��ʾ
			 ���ݵ�ǰ��״̬��0��ʾֹͣ 1���� -1�½� -2��ʾ����������
	ָ���Ӧ��ϵ:1-9��������ڳ˿Ͱ�Ŀ�갴ť��Q��W��E��R��T��Y��I��O��Ӧ1�㵽8�����������
				A��S��D��F��G��H��J��K��ʾ2�㵽9�����������
*/
{		

	extern void trans(Input input[],int size,C_fast1 inner_ask[10],C_fast2 outer_ask[10],int system_time,int current_floor);
	/*
		��������:���û���ָ��ת��������
		����˵��:inner_ask[10].value(=1��ʾ�Ѿ����� =0��ʾû�а���)
				 outer_ask[10].value(=0��ʾ������ =1��ʾ���������� =-1��ʾ���������� =2��ʾ����������)
	*/
	extern int count_time(C_fast1 inner_ask[10],C_fast2 outer_ask[10],int floor,int direction);
	//��������direction����1->'u' or -1->'d'�������ʱ��
	int waiting_time(C_fast1 inner_ask[10],C_fast2 outer_ask[10],int floor,int direction);
	//����direction����1->'u' or -1->'d'���ϵĵȴ�ʱ��
	extern int max3(int a,int b,int c);//����3���������ֵ
	extern int min3(int a,int b,int c);//����3��������Сֵ

	C_fast1 inner_ask[10]={0,0};//�����ⲿָ��,�±��1��ʼ
	C_fast2 outer_ask[10]={0,0};//�����ڲ�ָ��,�±��1��ʼ
	int current_floor;//��ǰʱ��¥��
	int keep_time,change_time;//�ֱ��ʾ���ֵ�ǰ״̬�͸ı�״̬��������Ҫ�ĵȴ�ʱ��
	

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

	keep_time=count_time(inner_ask,outer_ask,current_floor,-direction)
			  +waiting_time(inner_ask,outer_ask,current_floor,direction);

	change_time=count_time(inner_ask,outer_ask,current_floor,direction)
		        +waiting_time(inner_ask,outer_ask,current_floor,-direction);
		
	if (outer_ask[current_floor].value!=0)//�ⲿ������
	{
		if (outer_ask[current_floor].value==direction)//�ⲿǡ���ҽ���һ��������Ӧ������	
		{
			outer_ask[current_floor].value=0;
			if (direction==1)
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
			if (keep_time*6 < change_time*5) //���۴���20%��ͷ
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
	if (keep_time*6 > change_time*5) 
		output[system_time+1]=current_floor+direction;//���ֵ�ǰ�н�״̬

	else
		output[system_time+1]=current_floor-direction;//��ͷ

	return;
}	

int waiting_time(C_fast1 inner_ask[10],C_fast2 outer_ask[10],int floor,int direction)
{
	int i;
	int time=0;//�÷����ϵĿͻ��ĵȴ�ʱ��
	
	if (direction==1)//����
	{
		for (i=floor;i<=9;i++)
		{
			if (inner_ask[i].value==1)//������
				time+=(inner_ask[i].time+1);
			if (outer_ask[i].value==2)//��������
			{
				time+=(outer_ask[i].time_up+1);
				time+=(outer_ask[i].time_down+1);
			}
			if (outer_ask[i].value==1)//����
				time+=(outer_ask[i].time_up+1);
			if (outer_ask[i].value==-1)//����
				time+=(outer_ask[i].time_down+1);
		}
	}
	else//����
	{
		for (i=floor;i>=1;i--)
		{
			if (inner_ask[i].value==1)//������
				time+=(inner_ask[i].time+1);
			if (outer_ask[i].value==2)//��������
			{
				time+=(outer_ask[i].time_up+1);
				time+=(outer_ask[i].time_down+1);
			}
			if (outer_ask[i].value==1)//����
				time+=(outer_ask[i].time_up+1);
			if (outer_ask[i].value==-1)//����
				time+=(outer_ask[i].time_down+1);
		}
	}

	return time;
}


