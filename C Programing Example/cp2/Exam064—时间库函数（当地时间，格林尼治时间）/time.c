# include <time.h>
# include <stdio.h>

int main()
{
	struct tm *local;
	time_t tm;

	tm = time(NULL);//ϵͳ��ǰ����ʱ��
	local = localtime(&tm);//�ֽ���ʽ��TIME��ʽ
	printf("Local time and date: %s\n", asctime(local));//��ʽ��ʱ�䴮

	local = gmtime(&tm);//����һ����������ʱ��
	printf("UTC time and date: %s\n", asctime(local));

	return 0;
}