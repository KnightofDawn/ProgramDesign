#include<iostream.h>
#define   PI   3.1416
main()
{
    int i=100;
#if 1                     //��#if���Ϊ�棬����б��룬Ϊ���򲻱���
    cout<<"i="<<i<<endl;
#endif                    //������������

#ifdef PI                 //����궨����PI�������
    cout<<"1  PI="<<PI<<endl;
#endif

#ifndef PI				  //���û�к궨��PI�������
    cout<<"2  PI="<<PI<<endl;   //����䲻������ִ��
#endif
}
