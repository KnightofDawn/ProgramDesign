#include <iostream>
using namespace std;
main()
{
    int a=3, b=2;

    //�����ϵ���ʽ
    cout<<(a<b)<<endl;
    cout<<(a<b)<<(a>b)<<(a>=b)<<(a==b)<<(a!=b)<<endl;

    bool flag=2*a<b+10; //���Ϊ1
    cout<<"flag="<<flag;
}
