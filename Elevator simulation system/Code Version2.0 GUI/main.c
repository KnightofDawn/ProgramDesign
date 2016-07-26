/*
	����Ӧ���Ӧ�����is_done����ֵ�ڲ��Ժ��������޸�
	output[i]=output[i+1]��ʾ��Ӧ��¥���ͣ������
	ÿ�����Ժ���ֻд��һʱ�̵�����
	ָ���Ӧ��ϵ��
		1-9��������ڳ˿Ͱ�Ŀ�갴ť��
		Q��W��E��R��T��Y��U��I��Ӧ1�㵽8�����������
		A��S��D��F��G��H��J��K��ʾ2�㵽9�����������
		��ָ���Ӧ�Ĵ�Сдͨ�ã�
	�������ܣ�
		�Զ������ظ�ָ��
		�Զ����Դ���ָ��
*/

#include "elevator struct.h"



/*--------------------------------------------------main.c�ĺ�������----------------------------------------------------------*/
int is_repeating(char order);//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1��ɾ�����񣬷��򷵻�0
void get_input();//�����û����������룬��д�뵽��Ӧ�Ľṹ��������(*size ָ���Ӧ��ǰinput����Ĵ�С)
void respond();//ת���������,������Ӧ�����input�е�is_done����
void print_tips();//��ӡ�û�����ָ����ʾ
void gotoxy(int x, int y);//��λ����x�еĵ�y��
void clear_screen();//XP�µĴ���system("command/ccls")����������
void run_light();//��ӡ���ݵ�����״��
int is_legal(char order);//�ж������Ƿ�Ϸ�,h�Ϸ�����1�����򷵻�0
void main_trans(int inner[],int outer_up[],int outer_down[]);//�����������ڱ���ת�����������
void order_light();//��ӡʣ���ָ��
void print_line(char ch);//��ӡ��Ļ�ָ��У������ַ���ֵ
void deploy();//���е�������
/*--------------------------------------------------main.c�ĺ�������----------------------------------------------------------*/




/*-------------------------------------------------------ȫ�ֱ���-------------------------------------------------------------*/
int system_time=1;//��¼��ǰ����ʱ��
Input input[500];//��¼�û�����������ָ��,�±��һ��ʼ
int size=0;//input����ĵ�ǰԪ�ظ���
int dir=-2;//��ʾ���ݵ�ǰ��״̬��/*0ֹͣ*/ 1���� -1�½� -2���У�
int output[1001]={0};//����ÿ������ʱ�̵ĵ���״̬�����飬�±��ʾʱ�䣨��output[0]=1��ʾ�����ڵ�0�봦�ڵ�һ�㣩
static Output possition[1001];//��¼����1000�ڵ��������
int is_go=0;//=1��ʾGO��������
int delay=1000;//ÿ���ж��ȴ�ʱ��
int ratio=5;//�ȴ�ʱ��������ʱ��ı���
static int Tflag=0;//=0��ʾget_input��������
static int output_way=1;//1��ʾ������ʽ��2��ʾ���ٷ�ʽ��3��ʾ��ȫ��ʽ
int strategy=1;//��ǰ��ȡ�Ĳ��Ժ�
static FILE* out_fptr=NULL;
HEGG main_egg;//�����ľ��
int initial=0;
int ng=0;
const char stdCPT[]={"LASDFGHJK123456789QWERTYUIO"};//��׼��д��ĸ
const char stdSML[]={"lasdfghjk123456789qwertyuio"};//��׼Сд��ĸ
const mouse click_position[KEY_AMOUNT]={
										{'Q',317,105,342,78,NAME1,NAME3},
										{'W',317,169,342,142,NAME1,NAME3},{'A',317,141,342,114,NAME2,NAME4},
										{'E',317,232,342,205,NAME1,NAME3},{'S',317,204,342,177,NAME2,NAME4},
										{'R',317,298,342,271,NAME1,NAME3},{'D',317,270,342,243,NAME2,NAME4},
										{'T',317,363,342,336,NAME1,NAME3},{'F',317,335,342,308,NAME2,NAME4},
										{'Y',317,425,342,396,NAME1,NAME3},{'G',317,397,342,370,NAME2,NAME4},
										{'U',317,492,342,465,NAME1,NAME3},{'H',317,464,342,437,NAME2,NAME4},
										{'I',317,557,342,530,NAME1,NAME3},{'J',317,529,342,502,NAME2,NAME4}
																		 ,{'K',317,594,342,567,NAME2,NAME4},


										{'1',1122,157,1157,119,"bitmap//�ڲ�1-2.bmp","bitmap//�ڲ�1-1.bmp"},
										{'2',1122,219,1157,101,"bitmap//�ڲ�2-2.bmp","bitmap//�ڲ�2-1.bmp"},
										{'3',1122,273,1157,235,"bitmap//�ڲ�3-2.bmp","bitmap//�ڲ�3-1.bmp"},
										{'4',1122,328,1157,290,"bitmap//�ڲ�4-2.bmp","bitmap//�ڲ�4-1.bmp"},
										{'5',1044,155,1079,118,"bitmap//�ڲ�5-2.bmp","bitmap//�ڲ�5-1.bmp"},
										{'6',1044,218,1079,180,"bitmap//�ڲ�6-2.bmp","bitmap//�ڲ�6-1.bmp"},
										{'7',1044,274,1079,236,"bitmap//�ڲ�7-2.bmp","bitmap//�ڲ�7-1.bmp"},
										{'8',1044,329,1079,291,"bitmap//�ڲ�8-2.bmp","bitmap//�ڲ�8-1.bmp"},
										{'9',1044,388,1079,350,"bitmap//�ڲ�9-2.bmp","bitmap//�ڲ�9-1.bmp"},

										{'X',1116,460,1165,418,"bitmap//GO2.bmp","bitmap//GO1.bmp"},/*GO��*/
										{'Z',1047,457,1100,417,"bitmap//��GO2","bitmap//��GO1"},/*��GO��*/


										{'O',572,699,628,657,"",""},//�ȵ�����
										{'P',479,656,535,614,"",""},//˳�����
										{'L',502,557,558,515,"",""},//�����Ӧ
										{'N',640,557,696,515,"",""},//��̵ȴ�
														};
/*
 ָ���Ӧ��ϵ��
				1-9��������ڳ˿Ͱ�Ŀ�갴ť��
				Q��W��E��R��T��Y��U��I��Ӧ1�㵽8�����������
 				A��S��D��F��G��H��J��K��ʾ2�㵽9�����������
 				O�������ȷ��� P��˳����� L�������Ӧ N����̵ȴ�
 */

/*-------------------------------------------------------ȫ�ֱ���-------------------------------------------------------------*/

/*-------------------------------------------------------ͼ�λ�����-----------------------------------------------------------*/
extern int egg_tips();//��ӡegg��汾�ĳ�ʼ����ʾ��Ϣ
extern void egg_tips2();//���ݽ����и��������ܽ���
extern int egg_order();//����egg��״̬�µ�������ʾ
extern void egg_celue();//�ı���Ե�ͼƬ
extern void egg_inner_condition(int floor,int dir);//��ӡegg��汾�����ڲ�������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ)
extern void egg_outer_condition(int floor,int dir);//��ӡegg��汾�����ⲿ������״̬��ʾ(floorΪ¥�� dirΪ���� 1�� -1�� 0ͣ -2����)
extern void move_lift(int act);//ʵ�ֵ��ݵĶ�������(act=1 ��ʾ����һ�� act=-1��ʾ�½�1�� act=0ͣ�����л�ͼƬ act=2��ʾ����׼������)
extern int mouse_input();//egg�������
/*-------------------------------------------------------ͼ�λ�����-----------------------------------------------------------*/

int main()
{
	int i;
	DWORD Thread1;
	HANDLE thread1=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)get_input,NULL,0,&Thread1);//��һ�汾����
	DWORD Thread2;
	HANDLE thread2=CreateThread(NULL,0,(LPTHREAD_START_ROUTINE)mouse_input,NULL,0,&Thread2);//�ڶ��汾����

	EggStart(1200,700);
	main_egg=LayEgg();
	ShowConsoleWindow(0);
	if(egg_tips()==-1)
		egg_tips2();
    initial=1;//��ɳ�ʼ��

    DrawBitmap("bitmap//����2.bmp");
    Sleep(1000);
    MovePen(0,700);
    DrawBitmap("bitmap//����.bmp");

/*
	print_line(3);
	printf("��ӭ������ģ��ѧ��¥����ϵͳ(By����Mr.Phoebe coding studio)\n");
	printf(
			"��дС�飺201321130301��\n"
			"��д��Ա:����С�����𶫺�\n"
			"��дʱ��:2014��5��1��\n");
	print_line(3);
	printf("\n");

	printf("��ѡ���Ƿ���е��ݲ�������:\n");
	printf("1����������\n2��ʹ��Ĭ�ϲ���\n");
	scanf("%d",&i);
	fflush(stdin);
	clear_screen();
	if (i==1)
		deploy();

	printf("��������׼�����õĲ��Ժţ�\n1�������ȷ������\n2��˳��������\n3�������Ӧ����\n4�����ƽ���ȴ�ʱ�����\n");
	scanf("%d",&strategy);
	fflush(stdin);
*/
	ShowConsoleWindow(1);
	Tflag=1;//��ʾget_input��������

	output[1]=1;//��ʼ��
	possition[1].floor=1;
	possition[1].statue=-2;


//	system("command/ccls");
	clear_screen();
	order_light();
	print_tips();

	while(1)
	{
	//	get_input(system_time,input,&size,&dir);//�����û����룬ת������

		switch(strategy)
		{

		case 1://�����ȷ������
			orderServe(output,input,system_time,size,&dir);//�����ȷ�����Ժ���
			break;

		case 2://˳��������
		//	printf("���ò��Ժ�����%dʱ��\n",system_time);
			assistServe(output,system_time,&dir,input,size);
			//˳�������Ժ���
			break;

		case 3://�����Ӧ����
		//	printf("���ò��Ժ�����%dʱ��\n",system_time);
			fastest_respond(input,size,system_time,output,dir);//�����Ӧ���Ժ���
			break;

		case 4://���ƽ��ʱ�����
		//	printf("���ò��Ժ�����%dʱ��\n",system_time);
			least_wait(input,size,system_time,output,dir);//���ƽ��ʱ����Ժ���
			break;

		default:
			break;
		}

/*ת���������*/
		respond();
	//	system("command/ccls");
		clear_screen();
		order_light();

		egg_celue();
		egg_order();

		if (output_way!=2)
			run_light();
		print_tips();
/*ת���������*/

//		Sleep(delay);
		system_time++;//����ʱ������ƽ�
	}

	return 0;
}

void get_input()//�����û����������룬��д�뵽��Ӧ�Ľṹ��������(*size ָ���Ӧ��ǰinput����Ĵ�С)
{
		char ch[50];//�����ַ���
		int i=0;

		while (Tflag==0);
		while (initial==0);//�ȴ�����������

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
					if (dir==-2)
						dir=1;//��ʼ��Ϊ����
				}

				i++;
			}
		}
}

void respond()//ת���������,������Ӧ�����input�е�is_done����
{

	possition[system_time].floor=output[system_time];

	if (output[system_time+1]==output[system_time] && dir!=-2)//��һ��ʱ�̺͵�ǰʱ�̵ĵ��ݲ�����ͬ�����ƶ���
	{
		int flag=0;//�ȴ�GO��ʱ��
		is_go=0;
		possition[system_time].statue=0;

not_go:
        egg_outer_condition(output[system_time],0);
        egg_inner_condition(output[system_time],0);
        move_lift(0);
        SetActiveEgg(main_egg);
        while (bitmap==1);
		while (animation==1);
		ng=1;
		MovePen(1047,457);
		DrawBitmap("bitmap//��GO2.bmp");
		ng=0;

		while(is_go==0 && flag<=ratio-2)//GO����û�б�����
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
			flag++;
		}
		if(is_go==1)
		{
			while (bitmap==1);
			while (animation==1);
			ng=1;
			MovePen(1116,460);
			DrawBitmap("bitmap//GO1.bmp");
			ng=0;
			move_lift(2);
			while (bitmap==1);
			while (animation==1);
			ng=1;
			SetActiveEgg(main_egg);
			MovePen(1116,460);
			DrawBitmap("bitmap//GO2.bmp");
			ng=0;
		}
		else//û��GO��initial=1;//��ɳ�ʼ��
		{
			move_lift(2);
			is_go=1;
		}
		if (is_go!=1)//���˲�GO��
		{
			while (bitmap==1);
			while (animation==1);
			ng=1;
			SetActiveEgg(main_egg);
			MovePen(1047,457);
			DrawBitmap("bitmap//��GO1.bmp");
			ng=0;
			goto not_go;
		}
		possition[system_time].statue=11;
		is_go=0;
	}

	else if(output[system_time+1]==100*output[system_time] || dir==-2)
	{
	    egg_outer_condition(output[system_time],-2);
		egg_inner_condition(output[system_time],-2);
		move_lift(-2);

		dir=-2;
		output[system_time+1]=output[system_time];
		possition[system_time].statue=-2;
	}
	else if (output[system_time+1] > output[system_time])//����Ҫ����
	{
	    egg_outer_condition(output[system_time],1);
		egg_inner_condition(output[system_time],1);
		move_lift(1);

		dir=1;
		possition[system_time].statue=1;
	}
	else//����Ҫ�½�
	{
	    egg_outer_condition(output[system_time],-1);
		egg_inner_condition(output[system_time],-1);
		move_lift(-1);

		dir=-1;
		possition[system_time].statue=-1;
	}
}

void run_light()//��ӡ���ݵ�����״��
{
	int i=max(1,system_time-10);//��ӡ���10����¼

	for (;i<=system_time;i++)
	{
		if (possition[i].statue==-2 || dir==-2)//��ǰʱ��Ϊ����
			printf("��%dʱ��:������%d¥�����Ҵ��ڿ���״̬\n",i,possition[i].floor);
		else if (possition[i].statue==0)//��ǰʱ�̵��ݿ��ŵȴ�
			printf("��%dʱ��:��%d�㿪�ŵȴ�\n",i,possition[i].floor);
		else if (possition[i].statue==11)//������
			printf("��%dʱ��:��%d����ţ�׼��������~\n",i,possition[i].floor);
		else//��ǰʱ�̵���Ҫ���������½�
			printf("��%dʱ��:%d¥->%d¥\n",i,possition[i].floor,possition[i].floor+possition[i].statue);
	}
	i--;
	if (output_way!=1 && out_fptr==NULL)
			if ( (out_fptr=fopen("output.txt","a+"))==NULL)
			{
				printf("���ļ�ʧ�ܣ�\n");
				Sleep(5555);
			}
		if (output_way!=1)
		{
			if (possition[i].statue==-2 || dir==-2)//��ǰʱ��Ϊ����
				fprintf(out_fptr,"��%dʱ��:������%d¥�����Ҵ��ڿ���״̬\n",i,possition[i].floor);
			else if (possition[i].statue==0)//��ǰʱ�̵��ݿ��ŵȴ�
				fprintf(out_fptr,"��%dʱ��:��%d�㿪�ŵȴ�\n",i,possition[i].floor);
			else if (possition[i].statue==11)//������
				fprintf(out_fptr,"��%dʱ��:��%d����ţ�׼��������~\n",i,possition[i].floor);
			else//��ǰʱ�̵���Ҫ���������½�
				fprintf(out_fptr,"��%dʱ��:%d¥->%d¥\n",i,possition[i].floor,possition[i].floor+possition[i].statue);
			fclose(out_fptr);
			out_fptr=NULL;
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

	for (i=0;stdSML[i]!='\0' && stdCPT[i]!='\0';i++)
		if (order==stdSML[i] || order==stdCPT[i])
			return 1;

	return 0;
}

int is_repeating(char order)//�����û��������ָ��ж��Ƿ����ظ���ָ��,�ظ�����1�����򷵻�0
{
	int i;
	for(i=1;i<=size;i++)
		if(input[i].is_done==0 && input[i].order==order)
			return 1;
	return 0;
}

void clear_screen()//�ù���ƶ�������XP�µĴ���system("command/ccls")����������
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
    loc.Y = x;
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


