#include<iostream.h>
#include <string.h>

void main( void )
{
    //�����ַ���
    char string[] = "Fill the string with something";
    cout<<"string:"<<string<<endl;
    char *p=strset(string,'*');  //��string����Ϊ*
    cout<<"p     :"<<p<<endl;
    cout<<"string:"<<string<<endl;

    //��ָ���ַ���ָ����Ŀ�����ַ�����
    char string1[] = "Fill the string with something";
    cout<<"string1:"<<string1<<endl;
    p=strnset(string1,'*',5);   //��string1��ǰ5���ַ�����Ϊ*
    cout<<"p    :"<<p<<endl;
    cout<<"string1:"<<string1<<endl;
}
