#include<iostream.h>
#include <stdlib.h>
#include <math.h>

//main()�����Ķ���
void main( void )
{
    double x;

    //ѭ���������ݼ������
    do {
        cout<<"x=";
        cin>>x;
        if (x<=0) break;
        cout<<"log("<<x<<")="<<log(x)<<endl;      //  ln(x)
        cout<<"log10("<<x<<")="<<log10(x)<<endl;  //  lg(x)
    } while(1);
}
