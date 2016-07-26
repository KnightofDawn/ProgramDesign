/*
	��ӭ������������Լ��ĳ���������������������Լ�һЩС�Ĺ��ܺ�����ע���ʶ����Ҫ�ظ�����
	������º�Ŀ��Ѿ����ᱻ�ظ����������ҷ��ġ�
*/

#ifndef CMC_H

#define CMC_H
//��������
typedef struct
{
	int time;//��Ӧ�û�����ķ���ʱ��
	char order;//��Ӧ�û�������ָ��
	int is_done;//1��ʾ�Ѿ�����ɣ�0��ʾû�б����
}Input;
//main�����д����û�ָ��Ľṹ��

typedef struct
{
	int floor;//ǰһ״̬��¥��
	int statue;//��һ��ʱ�����Ҫִ�е�״̬��=0������ =1���� =-1�½� =-2���У�
}Output;
//main�����м�¼��������Ľṹ������

typedef struct
{
	int time;//��¼�������Ѿ��ȴ���ʱ��
	int value;
	int index;//��Ӧָ��input�������ڲ�ָ����±�
}C_INT;
//�����Ӧ���������ڴ���ת������û�ָ��Ľṹ������

typedef struct
{
	int time_up;//��Ӧ����ָ���Ѿ��ȴ���ʱ��
	int time_down;//��Ӧ����ָ���Ѿ��ȴ���ʱ��
	int value;
	int index_up;//��Ӧָ��input����������ָ����±�
	int index_down;//��Ӧָ��input����������ָ����±�
}C_INT2;
//�����Ӧ���������ڴ���ת������û�ָ��Ľṹ������

typedef struct
{
	char order;//��Ӧ�ĵ�һ�汾�е��ַ�
	int leftup_x;//���Ͻ������xֵ
	int leftup_y;//���Ͻ������yֵ
	int rightdown_x;//���½������xֵ
	int rightdown_y;//���½������yֵ
	char bitmap_name1[25];//�����Ӧ��ͼƬ1�����֣���ʼ��
	char bitmap_name2[25];//�����Ӧ��ͼƬ2�����֣�������
}mouse;

extern const mouse key_position[];//�±��0��ʼ����¼ÿ��������Ϣ

extern int system_time;//��¼��ǰ����ʱ��
extern Input input[500];//��¼�û�����������ָ��,�±��һ��ʼ
extern int size;//input����ĵ�ǰԪ�ظ���
extern int delay;//ÿ���ж��ȴ�ʱ��


#define KEY_AMOUNT 32//����
#define NAME1 "bitmap//�ⲿ����2.bmp"
#define NAME2 "bitmap//�ⲿ����2.bmp"
#define NAME3 "bitmap//�ⲿ����.bmp"
#define NAME4 "bitmap//�ⲿ����.bmp"

//��������
#endif

