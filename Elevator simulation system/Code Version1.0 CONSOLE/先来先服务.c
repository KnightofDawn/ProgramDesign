#include"elevator struct.h"


int orderServe(int out[],
	Input in[],
	int time,
	int in_size,
	int *condition)//size�洢ָ��
{
	int floor=out[time],
		target=0;//floor��ǰ������out������¼��һʱ�̲���
	Input *Ptr=NULL;

	int scanInput(Input in[],int,Input**);//ȷ��target¥��

	if((target=scanInput(in,in_size,&Ptr))==0)
	{
		out[time+1]=out[time];
		*condition=-2;
	}
	else if(target==floor)
	{
		out[time+1]=out[time];
		if(Ptr!=NULL){
			Ptr->is_done=1;
			Ptr=NULL;
		}
	}
	else
	{
		*condition=(target>floor?1:-1);
		out[time+1]=out[time]+*condition;
	}

	return 0;

}

int scanInput(Input in[],int size,Input **nPtr)//����ȷ��Ŀ��¥��
{
	int i/*ѭ������*/,minTime=0,isFirst=0/*���ǵ�һ��*/,Tgt;//mintime��¼�������ʱ���ָ��
	int returnFloor(char);
	for(i=1;i<=size;i++) if(in[i].is_done==0)
	{
		if(isFirst==0){
			minTime=in[i].time;
			Tgt=returnFloor(in[i].order);
			*nPtr=&in[i];
			isFirst=1;
		}
		else if(minTime>in[i].time){
			minTime=in[i].time;
			Tgt=returnFloor(in[i].order);
			*nPtr=&in[i];
		}
	}

	if(minTime==0)
		return 0;
	else return Tgt;
}

int returnFloor(char order)//���ַ���ָ��ת��������¥��
{
	extern char stdCPT[];//��׼��д��ĸ
	extern char stdSML[];//��׼Сд��ĸ
	int j/*ѭ������*/;
	for(j=0;j<27;j++)
		if(stdCPT[j]==order || stdSML[j]==order)
//		{
//			printf("%d\n",)
			return j%9+1;//ת��Ϊ����¥��
//		}
	return 0;
}