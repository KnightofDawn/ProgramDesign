/*
	����Ӧ���Ӧ�����is_done����ֵ�ڲ��Ժ��������޸�
	output[i]=output[i+1]��ʾ��Ӧ��¥���ͣ������
	ÿ�����Ժ���ֻд��һʱ�̵�����
	ָ���Ӧ�Ĵ�Сдͨ��
	���Ժ�����������condition�����������н����Ϊ-2�����ݿ��У�������	
	  ������ȡ�����ݵ�condition=0��ͣ��״̬
    �Զ������ظ�ָ��(��������)
	�涨input[]���±�Ϊ��1��ʼ
	!!!������get_input�����Ĵ���!!!
	�Զ����Դ���ָ��(��������)
*/
/*
  ָ���Ӧ��ϵ��1-9��������ڳ˿Ͱ�Ŀ�갴ť��Q��W��E��R��T��Y��U��I��Ӧ8�㵽1�����������
				A��S��D��F��G��H��J��K��ʾ9�㵽2�����������
*/
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <windows.h>
#include "egg.h"
#include "cmc.h"


  

/*--------------------------------------------------�ⲿ�ļ�����������------------------------------------------------------------*/
extern int orderServe(int out[],
	Input in[],
	int time,
	int in_size,
	int *condition);
extern void fastest_respond(Input input[],int size,int system_time,int output[],int condition);
extern int assistServe(int out[],int time,
				int *direction/*-2 for vacant
								0 for pause
								-1,1 respectively for downward and upward*/,
				Input in[],
				int in_size);
extern void least_wait(Input input[],int size,int system_time,int output[],int condition);
extern int hongfu(int out[],int T,
				int *direction/*-2 for vacant
								0 for pause
								-1,1 respectively for downward and upward*/,
				Input in[],
				int in_size,int*);

extern egg_order();//����egg��״̬�µ�������ʾ
extern void move_lift(int act);//ʵ�ֵ��ݵĶ�������(act=1 ��ʾ����һ�� act=-1��ʾ�½�1�� act=0ͣ�����л�ͼƬ act=2��ʾ����׼������)
extern void egg_celue();//�ı���Ե�ͼƬ
extern int mouse_input();//egg�������
extern void egg_inner_condition(int floor,int dir);//��ӡegg��汾�����ڲ�������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ)
extern void egg_outer_condition(int floor,int dir);//��ӡegg��汾�����ⲿ������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ -2����)
extern int egg_tips();//��ӡegg��汾�ĳ�ʼ����ʾ��Ϣ
extern void egg_tips2();//���ݽ����и��������ܽ���
/*--------------------------------------------------�ⲿ�ļ�����������------------------------------------------------------------*/

/*-------------------------------------------------------ȫ�ֱ���-------------------------------------------------------------*/
int system_time=1;//��¼��ǰ����ʱ��
Input input[500];//��¼�û�����������ָ��,�±��һ��ʼ
int size=0;//input����ĵ�ǰԪ�ظ���
int condition=1;//��ʾ���ݵ�ǰ��״̬��/*0ֹͣ*/ 1���� -1�½� -2���У�
int output[1001]={0};//����ÿ������ʱ�̵ĵ���״̬�����飬�±��ʾʱ�䣨��output[0]=1��ʾ�����ڵ�0�봦�ڵ�һ�㣩
static Output possition[1001];//��¼����1000�ڵ��������
static int is_baing=0;//�긣�еı���,��ʾ�Ƿ񱻰���,=1��ʾ���ǣ�-1��ʾ������
int is_go=0;//=1��ʾGO�������� 
int delay=1000;//ÿ���ж��ȴ�ʱ��
int ratio=5;//�ȴ�ʱ��������ʱ��ı���
static int Tflag=0;//=0��ʾget_input��������
static int output_way=1;//1��ʾ������ʽ��2��ʾ���ٷ�ʽ��3��ʾ��ȫ��ʽ
int strategy=1;//��ǰ��ȡ�Ĳ��Ժ�
static FILE* out_fptr=NULL;
HEGG main_egg;//�����ľ��
int step=0;//��Χ1-CUT ���߶���
int initial=0;
int ng=0;
/*-------------------------------------------------------ȫ�ֱ���-------------------------------------------------------------*/

/*--------------------------------------------------main.c�ĺ�������----------------------------------------------------------*/
int is_asked(char order);//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
void get_input();//�����û����������룬��д�뵽��Ӧ�Ľṹ��������(*size ָ���Ӧ��ǰinput����Ĵ�С)
void respond();//ת���������,������Ӧ�����input�е�is_done����
void print_tips();//��ӡ�û�����ָ����ʾ
void gotoxy(int x, int y);//��λ����y�еĵ�x��
void clear_screen();//XP�µĴ���system("command/ccls")����������
void print_possition();//��ӡ���ݵ�����״��
int is_legal(char order);//�ж������Ƿ�Ϸ�,h�Ϸ�����1�����򷵻�0
void main_trans(int inner[],int outer_up[],int outer_down[]);//�����������ڱ���ת�����������
void print_order();//��ӡʣ���ָ��
void print_line(char ch);//��ӡ��Ļ�ָ��У������ַ���ֵ
void deploy();//���е�������
/*--------------------------------------------------main.c�ĺ�������----------------------------------------------------------*/

/*������ͯЬ��˳���������ĳ���*/
const char stdCPT[]={"LKJHGFDSA123456789IUYTREWQO"};
const char stdSML[]={"lkjhgfdsa123456789iuytrewqo"};
/*������ͯЬ��˳���������ĳ���*/

/*--------------------------------------------------�ڶ��汾��ȫ�ֱ���----------------------------------------------------------*/

const mouse key_position[KEY_AMOUNT]={	
										{'I',317,105,342,78,NAME1,NAME3},
										{'U',317,169,342,142,NAME1,NAME3},{'K',317,141,342,114,NAME2,NAME4},
										{'Y',317,232,342,205,NAME1,NAME3},{'J',317,204,342,177,NAME2,NAME4},
										{'T',317,298,342,271,NAME1,NAME3},{'H',317,270,342,243,NAME2,NAME4},
										{'R',317,363,342,336,NAME1,NAME3},{'G',317,335,342,308,NAME2,NAME4},
										{'E',317,425,342,396,NAME1,NAME3},{'F',317,397,342,370,NAME2,NAME4},
										{'W',317,492,342,465,NAME1,NAME3},{'D',317,464,342,437,NAME2,NAME4},
										{'Q',317,557,342,530,NAME1,NAME3},{'S',317,529,342,502,NAME2,NAME4}
																		 ,{'A',317,594,342,567,NAME2,NAME4},

										{'B',550,350,650,20,"",""},/*door*/

										{'1',1122,157,1157,119,"bitmap//�ڲ�1-2.bmp","bitmap//�ڲ�1-1.bmp"},
										{'2',1122,219,1157,101,"bitmap//�ڲ�2-2.bmp","bitmap//�ڲ�2-1.bmp"},
										{'3',1122,273,1157,235,"bitmap//�ڲ�3-2.bmp","bitmap//�ڲ�3-1.bmp"},
										{'4',1122,328,1157,290,"bitmap//�ڲ�4-2.bmp","bitmap//�ڲ�4-1.bmp"},
										{'5',1044,155,1079,118,"bitmap//�ڲ�5-2.bmp","bitmap//�ڲ�5-1.bmp"},
										{'6',1044,218,1079,180,"bitmap//�ڲ�6-2.bmp","bitmap//�ڲ�6-1.bmp"},
										{'7',1044,274,1079,236,"bitmap//�ڲ�7-2.bmp","bitmap//�ڲ�7-1.bmp"},
										{'8',1044,329,1079,291,"bitmap//�ڲ�8-2.bmp","bitmap//�ڲ�8-1.bmp"},
										{'9',1044,388,1079,350,"bitmap//�ڲ�9-2.bmp","bitmap//�ڲ�9-1.bmp"},

										{'0',1116,460,1165,418,"bitmap//GO2.bmp","bitmap//GO1.bmp"},/*GO��*/
										{'Z',1047,457,1100,417,"bitmap//��GO2","bitmap//��GO1"},/*��GO��*/


										{'O',572,699,628,657,"",""},/*S1*/
										{'P',479,656,535,614,"",""},/*S2*/
										{'L',502,557,558,515,"",""},/*S3*/
										{'N',640,557,696,515,"",""},/*S4*/
										{'M',666,656,722,614,"",""}/*S5*/
														};
/*
 * ָ���Ӧ��ϵ��1-9��������ڳ˿Ͱ�Ŀ�갴ť��Q��W��E��R��T��Y��U��I��Ӧ8�㵽1�����������
 *				A��S��D��F��G��H��J��K��ʾ9�㵽2�����������
 *				O�������ȷ��� P��˳����� L�������Ӧ N����̵ȴ� M���긣����
 * ע��һ��ĵ������Ͻ�����(11,114)
 */

/*--------------------------------------------------�ڶ��汾��ȫ�ֱ���----------------------------------------------------------*/


int main()
{	
//	int i;
	DWORD Thread1;
	HANDLE thread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)get_input,NULL,0,&Thread1);//���߳�1

	DWORD Thread2;
	HANDLE thread2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)mouse_input,NULL,0,&Thread2);//���߳�2(egg����)
	


	EggStart(1200,700);
	main_egg = LayEgg();
	ShowConsoleWindow(0);
	if (egg_tips()==-1)
		egg_tips2();
	initial=1;//��ɳ�ʼ��
	
	DrawBitmap("bitmap//����.bmp");

//	printf("\a\a\a\a\a\a\a\a\a\a\a\a");
	
//	MovePen(11,114);
//	DrawBitmap("bitmap//����2.bmp");
//	Sleep(10000);

	
/*
	print_line(3);
	printf("��ӭ������ģ�����ϵͳ��һ�汾~(By����201021131603��)\n");
	printf("��д��Ա:���γ��������衢����\n"
		   "��дʱ��:2010��5��19��\n");
	print_line(3);
	printf("\n");

	printf("��ѡ���Ƿ���е��ݲ�������:\n");
	printf("1����������\n2��ʹ��Ĭ�ϲ���\n");
	scanf("%d",&i);
	fflush(stdin);
	clear_screen();
	if (i==1)
		deploy();

	printf("��������׼�����õĲ��Ժţ�\n1�������ȷ������\n2��˳��������\n3�������Ӧ����\n");
	printf("4�����ƽ���ȴ�ʱ�����\n5���긣ѧ��¥���ݲ���\n");
	scanf("%d",&strategy);
	fflush(stdin);
*/
//	egg_tips();//��ӡegg��汾�ĳ�ʼ����ʾ��Ϣ
	
	ShowConsoleWindow(1);
	Tflag=1;//��ʾget_input��������

	output[1]=1;//������ݳ�ʼ״̬
	possition[1].floor=1;
	possition[1].statue=-2;

//	system("command/ccls");
	clear_screen();
	print_order();
	print_tips();

	while (1)
	{
	//	get_input(system_time,input,&size,&condition);//�����û�����
		
		switch (strategy)
		{
			
		case 1://�����ȷ������
			{
				int i;

				printf("������! size=%d\n",size);
				for (i=1;i<=size;i++)
				{
					printf("%d %c %d %d %d\n",input[i].time,input[i].order,input[i].is_done,system_time,condition);
				}
			}
			orderServe(output,input,system_time,size,&condition);
		//�����ȷ�����Ժ���
			break;

		case 2://˳��������
		//	printf("���ò��Ժ�����%dʱ��\n",system_time);
		//	Sleep(4000);
			{
				int i;

				printf("������! size=%d\n",size);
				for (i=1;i<=size;i++)
				{
					printf("%d %c %d\n",input[i].time,input[i].order,input[i].is_done);
				}
			}
			assistServe(output,system_time,&condition,input,size);
			//˳�������Ժ���
			break;

		case 3://�����Ӧ����
			fastest_respond(input,size,system_time,output,condition);
			
			//�����Ӧ���Ժ���
			break;

		case 4://���ƽ��ʱ�����
			least_wait(input,size,system_time,output,condition);
			//���ƽ��ʱ����Ժ���
			break;

		case 5://�긣ѧ��¥���ݲ���
			hongfu(output,system_time,&condition,input,size,&is_baing);
		//	�긣ѧ��¥���ݲ��Ժ���
			break;

		default:
			break;
		}

/*ת���������*/
		respond();
	//	system("command/ccls");
		clear_screen();
		print_order();
		
		egg_celue();
		egg_order();

		if (output_way!=2)
			print_possition();
		print_tips();


	//	Sleep(delay);
		system_time++;//����ʱ������ƽ�
		
/*ת���������*/
	}

	return 0;
}

void get_input()//�����û����������룬��д�뵽��Ӧ�Ľṹ��������(*size ָ���Ӧ��ǰinput����Ĵ�С)
{
		char ch[50];//�����ַ���
		int i=0;

		while (Tflag==0);//�ȴ�����������
		while (initial==0);

	//	Sleep(1000);
		while (1)
		{
			i=0;
			gets(ch);

			gotoxy(0,0);
		//	system("command/ccls");
			clear_screen();
			gotoxy(0,0);
			print_order();	
			if (output_way!=2)
				print_possition();
			print_tips();

			while (ch[i]!='\0')//'\0'��ʾ�������
			{
				if (ch[i]=='O' || ch[i]=='o')//�����ȷ���
					strategy=1;
				if (ch[i]=='P' || ch[i]=='p')//˳�����
					strategy=2;
				if (ch[i]=='L' || ch[i]=='l')//�����Ӧ
					strategy=3;
				if (ch[i]=='N' || ch[i]=='n')//���ƽ���ȴ�ʱ��
					strategy=4;
				if (ch[i]=='M' || ch[i]=='m')//�긣����
					strategy=5;

				if (ch[i]=='0')
					is_go=1;
				if (ch[i]!=' ' && is_asked(ch[i])==0 && is_legal(ch[i])==1)
				{
					size++;
					input[size].order=ch[i];
					input[size].is_done=0;
					input[size].time=system_time;	
			//		printf("��%dʱ�̣������%cָ��",input[size].time,input[size].order);
					if (condition==-2)
						condition=1;//��ʼ��Ϊ����
				}
				i++;
			}
		}
}

void respond()//ת���������,������Ӧ�����input�е�is_done����
{

	possition[system_time].floor=output[system_time];
	
	if (output[system_time+1]==output[system_time] && condition!=-2)//��һ��ʱ�̺͵�ǰʱ�̵ĵ��ݲ�����ͬ�����ƶ���
	{
		int flag=0;//�ȴ�GO��ʱ��		
		
		if (output_way!=1 && out_fptr==NULL)
			if ( (out_fptr=fopen("output.txt","a+"))==NULL)
			{
				printf("���ļ�ʧ�ܣ�\n");
				Sleep(5555);
			}
		if (output_way!=1)
		{
			fprintf(out_fptr,"%d %d\n",system_time,output[system_time]);
			fclose(out_fptr);
			out_fptr=NULL;
		}

		is_go=0;
		possition[system_time].statue=0;

not_go://���²�GO��
		egg_outer_condition(output[system_time],0);
		egg_inner_condition(output[system_time],0);
		move_lift(0);
		SetActiveEgg(main_egg);
		while (bitmap==1);
		while (action==1);
		ng=1;
		MovePen(1047,457);
		DrawBitmap("bitmap//��GO2.bmp");
		ng=0;

		while (is_go==0 && flag<=ratio-2)//GO����û�б�����
		{
		
		//	system("command/ccls");
			clear_screen();
			print_order();
			print_possition();
			print_tips();
	
			Sleep(delay);
			system_time++;
			output[system_time+1]=output[system_time];
			possition[system_time].floor=output[system_time];
			possition[system_time].statue=0;
			flag++;
		}
		if (is_go==1)
		{	
			while (bitmap==1);
			while (action==1);
			ng=1;
			MovePen(1116,460);
			DrawBitmap("bitmap//GO1.bmp");//͵����
			ng=0;
			move_lift(2);
			while (bitmap==1);
			while (action==1);
			ng=1;
			SetActiveEgg(main_egg);
			MovePen(1116,460);
			DrawBitmap("bitmap//GO2.bmp");//͵����
			ng=0;
		}
		else//û��GO��
		{
			move_lift(2);
			is_go=1;
		}

		if (is_go!=1)//���˲�GO��
		{
			while (bitmap==1);
			while (action==1);
			ng=1;
			SetActiveEgg(main_egg);
			MovePen(1047,457);
			DrawBitmap("bitmap//��GO1.bmp");
			ng=0;
			goto not_go;
		}

		possition[system_time].statue=101;
		is_go=0;
	}

	else if (output[system_time+1]==100*output[system_time] || condition==-2)//����
	{
		egg_outer_condition(output[system_time],-2);
		egg_inner_condition(output[system_time],-2);
		move_lift(-2);
		

//		condition=-2;
		output[system_time+1]=output[system_time];
		possition[system_time].statue=-2;
	}
	else if (output[system_time+1] > output[system_time])//����Ҫ����
	{
		egg_outer_condition(output[system_time],1);
		egg_inner_condition(output[system_time],1);
		move_lift(1);
		

		condition=1;
		possition[system_time].statue=1;
	}
	else//����Ҫ�½�
	{
		egg_outer_condition(output[system_time],-1);
		egg_inner_condition(output[system_time],-1);
	//	move_lift(-1);

		
		condition=-1;
		if (is_baing==1)//��������
		{
			while (action==1);
			possition[system_time].statue=11;
			bitmap=1;
			SetActiveEgg(main_egg);
			MovePen(1046,609);
			DrawBitmap("bitmap//����.bmp");
			MovePen(843,348);
			DrawBitmap("bitmap//������ʾ.bmp");
			bitmap=0;
			move_lift(-1);
		}
		else if (is_baing==-1)//����������
		{
			while (action==1);
			possition[system_time].statue=22;
			bitmap=1;
			SetActiveEgg(main_egg);
			MovePen(1046,609);
			DrawBitmap("bitmap//����.bmp");
			MovePen(843,348);
			DrawBitmap("bitmap//�긣��ʾ.bmp");
			bitmap=0;
			if (output[system_time]==2)
				move_lift(-1);
			else//=3
				move_lift(-11);//�긣�е������½�
		}
		else//��������
		{
			possition[system_time].statue=-1;
			move_lift(-1);
		}
	}
}

void print_possition()//��ӡ���ݵ�����״��
{
	int i;
	int min;

	min=max(1,system_time-10);//��ӡ���10����¼

	for (i=min;i<=system_time;i++)
	{
		if (possition[i].statue==-2 || condition==-2)//��ǰʱ��Ϊ����
		{	
		//	move_lift(-2);
			printf("��%dʱ��:������%d¥�����Ҵ��ڿ���״̬\n",i,possition[i].floor);
		}
		else if (possition[i].statue==0)//��ǰʱ�̵��ݿ��ŵȴ�
		{
		//	move_lift(0);
			printf("��%dʱ��:��%d�㿪�ŵȴ�\n",i,possition[i].floor);
		}
		else if (possition[i].statue==101)//������
		{
		//	move_lift(2);
			printf("��%dʱ��:��%d����ţ�׼��������~\n",i,possition[i].floor);
		}
		else//��ǰʱ�̵���Ҫ���������½�
		{
			if (possition[i].statue==11)//����״̬
			{
				printf("��%dʱ��:���ŵ��µ���ʧ���С���o(����)o ����",i);
				printf("%d¥->%d¥\n",possition[i].floor,possition[i].floor-1);
			}
			else if (possition[i].statue==22)//������״̬
			{
				printf("��%dʱ��:���ݳ��������ˣ�o(����)o ",i);
				printf("%d¥->%d¥\n",possition[i].floor,1);
			}
			else
			{
				printf("��%dʱ��:%d¥->%d¥\n",i,possition[i].floor,possition[i].floor+possition[i].statue);
		/*		if (possition[i].floor > possition[i].floor+possition[i].statue)//�½�
					move_lift(-1);
				else
					move_lift(1);
					*/
			}
		}
	}

	return;
}


int is_asked(char order)//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
{
	int i;
	
	for (i=1;i<=size;i++)
		if (input[i].order==order && input[i].is_done==0)
			return 1;

	return 0;
}

void print_tips()//��ӡ�û�����ָ����ʾ
{
	int i;

//	printf("\n");
	for (i=1;i<=80;i++)
		printf("*");
	printf("��ʱ�л�����:O�������ȷ��� P��˳����� L�������Ӧ N����̵ȴ� M���긣����\n");
	printf("ָ���Ӧ��ϵ��1-9��������ڳ˿Ͱ�Ŀ�갴ť 0����GO����B����긣���Եİ��ż�\nQ��W��E��R��T��Y��U��I��Ӧ8�㵽1�����������\n");
	printf("A��S��D��F��G��H��J��K��ʾ9�㵽2�����������\n");
	for (i=1;i<=80;i++)
		printf("*");
	printf("��������������ָ����û��س���:\n");
//	printf("\n");

	return;
}

int is_legal(char order)//�ж������Ƿ�Ϸ�,�Ϸ�����1�����򷵻�0
{
	int i;
	char board[]="oOLl";//������ͯЬ�ı߽��ַ�
	char hongfu[]="2345KJHGUYTRkjhguytr";//�긣������û�е�ָ��

	if (strategy==5)
		for (i=0;i<=19;i++)
			if (order==hongfu[i])
				return 0;

	for (i=0;i<=3;i++)
		if (order==board[i])
			return 0;
	
	if (order=='b' || order=='B')
		return 1;
	
	for (i=0;stdSML[i]!='\0' && stdCPT[i]!='\0';i++)
		if (order==stdSML[i] || order==stdCPT[i])
			return 1;

	
	return 0;
}

void clear_screen()//XP�µĴ���system("command/ccls")����������
{
	int i;

	gotoxy(0,0);
	for (i=1;i<=250;i++)
		printf("\t");
	gotoxy(0,0);

	return;
}

void gotoxy(int x, int y)//��λ����y�еĵ�x��
{
    int xx=0x0b;
    HANDLE hOutput;
    COORD loc;
    loc.X = x;
    loc.Y=y;
    hOutput = GetStdHandle(STD_OUTPUT_HANDLE);
    SetConsoleCursorPosition(hOutput, loc);
    return;
}

void main_trans(int inner[],int outer_up[],int outer_down[])//�����������ڱ���ת�����������
{  
	int i;
	int floor=0;
/*
	memset(inner,0,sizeof(inner));
	memset(outer_up,0,sizeof(outer_up));
	memset(outer_down,0,sizeof(outer_down));
*/
	for (i=1;i<=size;i++)
	{
		if (input[i].is_done==0)//û�б���Ӧ������
		{
			if (input[i].order<='9' && input[i].order>=1)//�ڲ�����
				inner[input[i].order-48]=1;

			else//�ⲿ����
			{
				switch (input[i].order)
				{
				case 'Q':case 'q'://�˲�����
					outer_up[8]=1;
					break;
				case 'W':case 'w'://�߲�����
					outer_up[7]=1;
					break;
				case 'E':case 'e'://��������
					outer_up[6]=1;
					break;
				case 'R':case 'r'://�������
					outer_up[5]=1;
					break;
				case 'T':case 't'://�Ĳ�����
					outer_up[4]=1;
					break;
				case 'Y':case 'y'://��������
					outer_up[3]=1;
					break;
				case 'U':case 'u'://��������
					outer_up[2]=1;
					break;
				case 'I':case 'i'://һ������
					outer_up[1]=1;
					break;
				case 'A':case 'a'://�Ų�����
					outer_down[9]=1;
					break;
				case 'S':case 's'://�˲�����
					outer_down[8]=1;
					break;
				case 'D':case 'd'://�߲�����
					outer_down[7]=1;
					break;
				case 'F':case 'f'://��������
					outer_down[6]=1;
					break;
				case 'G':case 'g'://�������
					outer_down[5]=1;
					break;
				case 'H':case 'h'://�Ĳ�����
					outer_down[4]=1;
					break;
				case 'J':case 'j'://��������
					outer_down[3]=1;
					break;
				case 'K':case 'k'://��������
					outer_down[2]=1;
					break;
				default:
					break;
				}
		
			}
		}
	}//����ת�����

	return;
}

void print_order()//��ӡʣ���ָ��
{
	int inner[10]={0};//1��9¥���ڲ�����0�� 1�У�
	int outer_up[10]={0};//1��8¥���ⲿ��������0�� 1�У�
	int outer_down[10]={0};//2��9¥���ⲿ��������0�� 1�У�
	int i;

	main_trans(inner,outer_up,outer_down);//ת��ʣ��ָ��

//	printf("\n");
	for (i=1;i<=80;i++)
		printf("#");
	printf("�����ڲ�δ���ָ��:");
	for (i=1;i<=9;i++)
		if (inner[i]==1)
			printf("%d  ",i);
	printf("\t\t��ǰ���õĲ���Ϊ:");
	switch (strategy)
	{
	case 1:
		printf("�����ȷ������");
		break;
	case 2:
		printf("˳��������");
		break;
	case 3:
		printf("�����Ӧ����");
		break;
	case 4:
		printf("���ƽ���ȴ�ʱ�����");
		break;
	case 5:
		printf("�긣����");
		break;
	default:
		break;
	}

	printf("\n");
	printf("�����ⲿδ���ָ��:");
	for (i=1;i<=8;i++)
		if (outer_up[i]==1)
			printf("%d¥��  ",i);
	printf("\n");
	printf("\t\t");
	for (i=2;i<=9;i++)
		if (outer_down[i]==1)
			printf("%d¥��  ",i);
	printf("\n");
	for (i=1;i<=80;i++)
		printf("#");
//	printf("\n");
	
	return;
}

void print_line(char ch)//��ӡ��Ļ�ָ��У������ַ���ֵ
{
	int i;

	for (i=1;i<=80;i++)
		printf("%c",ch);
	//printf("\n");

	return;
}

void deploy()//���е�������
{
	int flag=0;

	while (flag==0)//���벻��ȷ
	{
		printf("������һ��������������ÿ���ж���������Ҫ��ʱ��(��λ��):\n");
		scanf("%d",&delay);
		flag=1;
		if (delay<=0)
		{
			flag=0;
			printf("�����������������0��������\n");
		}
	}
	delay*=1000;
	flag=0;

	while (flag==0)
	{
		printf("������һ�������������õ���ͣ������Ҫ�ķ���ʱ����:\n");
		scanf("%d",&ratio);
		flag=1;
		if (ratio<=0)
		{
			flag=0;
			printf("�����������������0��������\n");
		}
	}
	flag=0;

	while (flag==0)
	{
		printf("��ѡ��������з�ʽ:\n"
			"1����Ļ���\n2�����ٷ�ʽ\n3����ȫ��ʽ\n");
		scanf("%d",&output_way);
		flag=1;
		if (!(output_way<=3 && output_way>=0))
		{
			printf("�Բ�������ȷ����!\n");
			flag=0;
		}
	}
/**/
	return;
}
