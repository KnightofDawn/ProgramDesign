/*
	����Ӧ���Ӧ�����is_done����ֵ�ڲ��Ժ��������޸�
	output[i]=output[i+1]��ʾ��Ӧ��¥���ͣ������
	ÿ�����Ժ���ֻд��һʱ�̵�����
	ָ���Ӧ�Ĵ�Сдͨ��
	���Ժ�����������condition�����������н����Ϊ-2�����ݿ��У�������	
	  ������ȡ�����ݵ�condition=0��ͣ��״̬
    �Զ������ظ�ָ��(��������)
	�涨input[]���±�Ϊ��1��ʼ
	�Զ����Դ���ָ��(��������)
*/
/*
  ָ���Ӧ��ϵ��1-9��������ڳ˿Ͱ�Ŀ�갴ť��Q��W��E��R��T��Y��U��I��Ӧ8�㵽1�����������
				A��S��D��F��G��H��J��K��ʾ9�㵽2�����������
*/

#include "elevator struct.h"
 

/*--------------------------------------------------���Ժ���������------------------------------------------------------------*/
extern int orderServe(int out[],
	Input in[],
	int time,
	int in_size,int*
	);
extern void fastest_respond(Input input[],int size,int system_time,int output[],int condition);
extern int assistServe(int out[],int time,
				int *direction/*-2 for vacant
								0 for pause
								-1,1 respectively for downward and upward*/,
				Input in[],
				int in_size);
extern void least_wait(Input input[],int size,int system_time,int output[],int condition);
/*--------------------------------------------------���Ժ���������------------------------------------------------------------*/


/*--------------------------------------------------main.c�ĺ�������----------------------------------------------------------*/
int is_repeating(char order);//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
void get_input();//�����û����������룬��д�뵽��Ӧ�Ľṹ��������(*size ָ���Ӧ��ǰinput����Ĵ�С)
void respond();//ת���������,������Ӧ�����input�е�is_done����
void print_tips();//��ӡ�û�����ָ����ʾ
void gotoxy(int x, int y);//��λ����y�еĵ�x��
void clear_screen();//XP�µĴ���system("command/ccls")����������
void run_light();//��ӡ���ݵ�����״��
int is_legal(char order);//�ж������Ƿ�Ϸ�,h�Ϸ�����1�����򷵻�0
void main_trans(int inner[],int outer_up[],int outer_down[]);//�����������ڱ���ת�����������
void order_light();//��ӡʣ���ָ��
void print_line(char ch);//��ӡ��Ļ�ָ��У������ַ���ֵ
void deploy();//���е�������
/*--------------------------------------------------main.c�ĺ�������----------------------------------------------------------*/

/*Mr.Phoebe��˳���������ĳ���*/
const char stdCPT[]={"LASDFGHJK123456789QWERTYUIO"};//LKJHGFDSA123456789IUYTREWQO
const char stdSML[]={"lasdfghjk123456789qwertyuio"};//lkjhgfdsa123456789iuytrewqo
/*Mr.Phoebe��˳���������ĳ���*/


/*-------------------------------------------------------ȫ�ֱ���-------------------------------------------------------------*/
//��̬ȫ��ʲô��������
static int system_time=1;//��¼��ǰ����ʱ��
static Input input[500];//��¼�û�����������ָ��,�±��һ��ʼ
static int size=0;//input����ĵ�ǰԪ�ظ���
static int condition=1;//��ʾ���ݵ�ǰ��״̬��/*0ֹͣ*/ 1���� -1�½� -2���У�
static int output[1001]={0};//����ÿ������ʱ�̵ĵ���״̬�����飬�±��ʾʱ�䣨��output[0]=1��ʾ�����ڵ�0�봦�ڵ�һ�㣩
static Output possition[1001];//��¼����1000�ڵ��������
static int is_go=0;//=1��ʾ���ż�������,-1��ʾ���ż�������
static int delay=3000;//ÿ���ж��ȴ�ʱ��
static int ratio=5;//�ȴ�ʱ��������ʱ��ı���
static int Tflag=0;//=0��ʾget_input��������
static int output_way=1;//1��ʾ������ʽ��2��ʾ���ٷ�ʽ��3��ʾ��ȫ��ʽ
static int strategy=1;//��ǰ��ȡ�Ĳ��Ժ�
static FILE* out_fptr=NULL;
/*-------------------------------------------------------ȫ�ֱ���-------------------------------------------------------------*/

int main()
{	
	int i;
	DWORD Thread1;
	HANDLE thread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)get_input,NULL,0,&Thread1);//���߳�1
	
	print_line(3);
	printf("��ӭ������ģ��ѧ��¥����ϵͳ(By����Mr.Phoebe coding studio)\n");
	printf(
			"��дС�飺201321130301��\n"
			"��д��Ա:����С�����𶫺�\n"
			"��дʱ��:2013��5��1��\n");
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
	printf("4�����ƽ���ȴ�ʱ�����\n");
	scanf("%d",&strategy);
	fflush(stdin);

	Tflag=1;//��ʾget_input��������

	output[1]=1;//��ʼ��
	possition[1].floor=1;
	possition[1].statue=-2;

//	system("command/ccls");
	clear_screen();
	order_light();
	print_tips();

	while (1)
	{
	//	get_input(system_time,input,&size,&condition);//�����û����룬ת������
		
		switch (strategy)
		{
			
		case 1://�����ȷ������
			orderServe(output,input,system_time,size,&condition);//�����ȷ�����Ժ���
			break;

		case 2://˳��������
		//	printf("���ò��Ժ�����%dʱ��\n",system_time);
			assistServe(output,system_time,&condition,input,size);
			//˳�������Ժ���
			break;

		case 3://�����Ӧ����
		//	printf("���ò��Ժ�����%dʱ��\n",system_time);
			fastest_respond(input,size,system_time,output,condition);//�����Ӧ���Ժ���
			break;

		case 4://���ƽ��ʱ�����
		//	printf("���ò��Ժ�����%dʱ��\n",system_time);
			least_wait(input,size,system_time,output,condition);//���ƽ��ʱ����Ժ���
			break;

		default:
			break;
		}

/*ת���������*/
		respond();
	//	system("command/ccls");
		clear_screen();
		order_light();
		if (output_way!=2)
			run_light();
		print_tips();
/*ת���������*/

		Sleep(delay);
		system_time++;//����ʱ������ƽ�
	}

	return 0;
}

void get_input()//�����û����������룬��д�뵽��Ӧ�Ľṹ��������(*size ָ���Ӧ��ǰinput����Ĵ�С)
{
		char ch[50];//�����ַ���
		int i=0;

		while (Tflag==0);//�ȴ�����������

	//	Sleep(1000);
		while (1)
		{
			i=0;
			gets(ch);

			gotoxy(0,0);
		//	system("command/ccls");
			clear_screen();
			gotoxy(0,0);
			order_light();	
			if (output_way!=2)
				run_light();
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
				if (ch[i]=='Z'||ch[i]=='z')
					is_go=1;
				if (ch[i]=='X'||ch[i]=='x')
					is_go=-1;
				if (ch[i]!=' ' && is_repeating(ch[i])==0 && is_legal(ch[i])==1)
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
	
	if (output[system_time+1]==output[system_time])//��һ��ʱ�̺͵�ǰʱ�̵ĵ��ݲ�����ͬ�����ƶ���
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
		while (is_go!=1 && flag<=ratio-2)//GO����û�б�����
		{
		
		//	system("command/ccls");
			clear_screen();
			order_light();
			run_light();
			print_tips();

			Sleep(delay);
			system_time++;
			output[system_time+1]=output[system_time];
			possition[system_time].floor=output[system_time];
			possition[system_time].statue=0;
			if(is_go==-1)
			{
				flag=0;
				is_go=0;
			}
			else
				flag++;
		}
		possition[system_time].statue=101;
		is_go=0;
	}

	else if (output[system_time+1]==100*output[system_time] || condition==-2)
	{
		condition=-2;
		output[system_time+1]=output[system_time];
		possition[system_time].statue=-2;
	}
	else if (output[system_time+1] > output[system_time])//����Ҫ����
	{
		condition=1;
		possition[system_time].statue=1;
	}
	else//����Ҫ�½�
	{
		condition=-1;
		possition[system_time].statue=-1;
	}
}

void run_light()//��ӡ���ݵ�����״��
{
	int i;
	int min;

	min=max(1,system_time-10);//��ӡ���10����¼

	for (i=min;i<=system_time;i++)
	{
		if (possition[i].statue==-2 || condition==-2)//��ǰʱ��Ϊ����
			printf("��%dʱ��:������%d¥�����Ҵ��ڿ���״̬\n",i,possition[i].floor);
		else if (possition[i].statue==0)//��ǰʱ�̵��ݿ��ŵȴ�
			printf("��%dʱ��:��%d�㿪�ŵȴ�\n",i,possition[i].floor);
		else if (possition[i].statue==101)//������
			printf("��%dʱ��:��%d����ţ�׼��������~\n",i,possition[i].floor);
		else//��ǰʱ�̵���Ҫ���������½�
			printf("��%dʱ��:%d¥->%d¥\n",i,possition[i].floor,possition[i].floor+possition[i].statue);
	}

	return;
}




void print_tips()//��ӡ�û�����ָ����ʾ
{
	int i;

//	printf("\n");
	for (i=1;i<=80;i++)
		printf("*");
	printf("��ʱ�л�����:O�������ȷ��� P��˳����� L�������Ӧ N����̵ȴ�\n");
	printf("ָ���Ӧ��ϵ��1-9��������ڳ˿Ͱ�Ŀ�갴ť Z������ż� X�����ż�\nQ��W��E��R��T��Y��U��I��Ӧ1�㵽8�����������\n");
	printf("A��S��D��F��G��H��J��K��ʾ2�㵽9�����������\n");
	printf("\t\t\tBY Mr.Phoebe coding studio\n");
	for (i=1;i<=80;i++)
		printf("*");
	printf("��������������ָ����û��س���:\n");
//	printf("\n");

	return;
}

void order_light()//��ӡʣ���ָ��
{
	int inner[10]={0};//���
	int outer_up[10]={0};
	int outer_down[10]={0};
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
	default:
		break;
	}

	printf("\n");
	printf("�����ⲿδ���ָ��:");
	for (i=1;i<=8;i++)
		if (outer_up[i]==1)
			printf("%d¥��  ",i);
	printf("\n");
	printf("                   ");
	for (i=2;i<=9;i++)
		if (outer_down[i]==1)
			printf("%d¥��  ",i);
	printf("\n");
	for (i=1;i<=80;i++)
		printf("#");
//	printf("\n");
	
	return;
}

int is_legal(char order)//�ж������Ƿ�Ϸ�,�Ϸ�����1�����򷵻�0
{
	int i;
	char board[]="oOLl";

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

int is_repeating(char order)//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
{
	int i;
	
	for (i=1;i<=size;i++)
		if (input[i].order==order && input[i].is_done==0)
			return 1;

	return 0;
}

void clear_screen()//XP�µĴ���system("command/ccls")����������,�ù���ƶ�����
{
	int i;
	//system ("cls");
	gotoxy(0,0);
	for (i=1;i<=250;i++)
		printf("\t");
	gotoxy(0,0);

	return;
}

void gotoxy(int x, int y)//����ƶ�����x�еĵ�y��
{
    int xx=0x0b;
    HANDLE hOutput;
    COORD loc;
    loc.X = y;
    loc.Y=x;
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
			if (input[i].order<='9' && input[i].order>='1')//�ڲ�����
				inner[input[i].order-'0']=1;

			else//�ⲿ����
			{
				switch (input[i].order)
				{
				case 'Q':case 'q'://һ������
					outer_up[1]=1;
					break;
				case 'W':case 'w'://��������
					outer_up[2]=1;
					break;
				case 'E':case 'e'://��������
					outer_up[3]=1;
					break;
				case 'R':case 'r'://�Ĳ�����
					outer_up[4]=1;
					break;
				case 'T':case 't'://�������
					outer_up[5]=1;
					break;
				case 'Y':case 'y'://��������
					outer_up[6]=1;
					break;
				case 'U':case 'u'://�߲�����
					outer_up[7]=1;
					break;
				case 'I':case 'i'://�˲�����
					outer_up[8]=1;
					break;
				case 'A':case 'a'://��������
					outer_down[2]=1;
					break;
				case 'S':case 's'://��������
					outer_down[3]=1;
					break;
				case 'D':case 'd'://�Ĳ�����
					outer_down[4]=1;
					break;
				case 'F':case 'f'://�������
					outer_down[5]=1;
					break;
				case 'G':case 'g'://��������
					outer_down[6]=1;
					break;
				case 'H':case 'h'://�߲�����
					outer_down[7]=1;
					break;
				case 'J':case 'j'://�˲�����
					outer_down[8]=1;
					break;
				case 'K':case 'k'://�Ų�����
					outer_down[9]=1;
					break;
				default://�Ų����ϣ�һ������
					break;
				}
		
			}
		}
	}//����ת�����

	return;
}


void print_line(char ch)//��ӡ��Ļ�ָ��У���ӡ���кǺ�
{
	int i;

	for (i=1;i<=80;i++)
		printf("%c",ch);
	//printf("\n");

	return;
}

void deploy()//���е������ã��û����и�������
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

	return;
}


	