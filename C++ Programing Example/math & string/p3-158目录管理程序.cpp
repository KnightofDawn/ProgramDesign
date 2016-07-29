#include<iostream.h>
#include<direct.h>
#include<errno.h>
#define MAX_PATH 250
main()
{
    //��������
    char *p,str[MAX_PATH];

    //������Ŀ¼
    if (mkdir("d:\\ABC")){
        cout<<"mkdir Error!"<<endl;
    }

    //���ù���Ŀ¼
    if (chdir("d:\\ABC")){
        cout<<"chdir Error!"<<endl;
    }

    //��ȡ��ǰĿ¼
    if ((p=getcwd(str,MAX_PATH))==NULL) {
        cout<<"getcwd Error!"<<endl;
    }
    else
    {
        cout<<"p:"<<p<<endl;
        cout<<"str:"<<str<<endl;
    }

    //���ù���Ŀ¼
    if (chdir("d:\\")){
        cout<<"chdir Error!"<<endl;
    }

    //ɾ��ָ��Ŀ¼
    if (rmdir("d:\\ABC")==-1) 
        cout<<"rmdir Error!"<<endl;
}


/*chdir()�ı䵱ǰĿ¼�ĺ���
ԭ�Σ�int chdir(const char *path)
���ܣ�����pathָ����Ŀ¼��Ϊ��ǰĿ¼��path�����п���ָ���������ţ��硰a:\\ddd��, ��ֻ�Ǹı���������ϵĵ�ǰĿ¼���Ե�ǰ��������ϵĵ�ǰĿ¼��Ӱ�졣
����ֵ��0(�ɹ�)��-1(ʧ��)
ͷ�ļ���dir.h
=======================================================================================
findfirst()������findnext()����
���÷�ʽ��������=findfirst(�ļ���,&�ṹ������,���Գ������(��0x26));���ж���struct ffblk �ṹ������;
ԭ�Σ�int findfirst(path,buffer,attr)��int findnext(buffer)
   char *path;//Ҫ�������ļ���
   struct ffblk
    {
    char ff_reserved[21];
    char ff_attrib;//���������ļ�����
    unsigned ff_ftime;//����޸ĵ�ʱ��
     //(0-4λ:����/2��5-10λ:������11-15λ:Сʱ��)
    unsigned ff_fdate;//����޸ĵ�����
     //(0-4λ���գ�5-8λ���£�9-15λ�����1980)
    long ff_fsize;//�ļ���С
    char ff_name[13];//����
    }*buffer;
   int attr;//Ҫ�������ļ�����
���ܣ�������path��attrָ�����ļ����ѽ�����ص�buffer��findfirst���ع��ڵ�һ��ָ���ļ�����Ϣ��findnext����������
����ֵ��0(�����ɹ�),-1(û���ҵ�ָ�����ļ�)
���Գ�����
  FA_NORMAL(0x00)  ���⣺Normal file, no attributes 
  FA_RDONLY(0x01)  ���⣺ֻ��
  FA_HIDDEN(0x02)  ���⣺�����ļ�
  FA_SYSTEM(0x04)  ���⣺ϵͳ�ļ�
  FA_LABEL(0x08)   ���⣺���
  FA_DIREC(0x10)   ���⣺��Ŀ¼
  FA_ARCH(0x20)   ���⣺�޸ĵ��ļ�Archive
ͷ�ļ���dir.h(dos.h)
====================================================================================
fnmerge()�����ļ�·������
ԭ�Σ�void fnmerge(char *path,const char *drive,const char *dir, const char *name,const char *ext)
���ܣ��ϳ�drive:\dir\name.ext������path
ͷ�ļ���dir.h

fnsplit()�ֽ�������·��������
ԭ��:int fnsplit(char *path,const char *drive,const char *dir,const char *name,const char *ext)
���ܣ����ļ���·��path�ֳ�4�����ִ�š�
  ����drive����ð�ţ�dir���п�ʼ�ͽ�β�ķ�б�ܣ�ext������ʼԲ��
����ֵ���������չ������ ����ֵ&EXTENSION!=0
    ������ļ������� ����ֵ&FILENAME!=0
    �����Ŀ¼������ ����ֵ&DIRECTORY!=0
    ������������ţ��򷵻�ֵ&DIRVE!=0
ͷ�ļ���dir.h 
====================================================================================
getcurdir()��ȡָ���������ĵ�ǰĿ¼�ĺ���
ԭ�Σ�int getcurdir(int drive,char directory)
   drive=0(ȱʡ);1(A������)��...
   directory�������Ŀ¼�����������������������Է�б�ܿ�ʼ��
����ֵ��0(���óɹ�);1(����)
ͷ�ļ���dir.h

getcwd()��ȡ��ǰĿ¼�ĺ���
ԭ�Σ�char *getcwd(char *buf,int buflen)
���ܣ���ȡ��ǰĿ¼������·����(������������)���Ϊbuflen���ֽڣ������buf�С����bufΪNULL������������һ��buflen�ֽڳ��Ļ��������Ժ�ɽ��������ķ���ֵ��Ϊfree�����Ĳ������ͷŸû�������
����ֵ����buf�ǿգ����óɹ�����buf,������NULL;��bufΪNULL,����ָ���Ѿ�������ڴ滺������ַ��
ͷ�ļ���dir.h

getdisk()��ȡ��ǰ�����������ź���
ԭ�Σ�int getdisk(void)
���ܣ�ȡ�õ�ǰ�������ţ�0=A;1=B;....��
ͷ�ļ���dir.h
======================================================================================
mkdir()����Ŀ¼����
ԭ�Σ�int mkdir(const char *path)
���ܣ���������·������һ���µ�Ŀ¼
ͷ�ļ���dir.h
����ֵ��0(�ɹ�);-1(ʧ��)

mktemp()����һ��Ψһ���ļ����ĺ���
ԭ�Σ�char *mktemp(char *template)
���ܣ�ʹ��һ��Ψһ���ļ������滻�ַ���template,������template��
ͷ�ļ���dir.h
======================================================================================
rmdir()ɾ��Ŀ¼����
ԭ�Σ�int rmdir(const char *path)
ע�⣺ɾ����Ŀ¼�����ǵ�ǰĿ¼�����Ǹ�Ŀ¼���ǿ�Ŀ¼
����ֵ��0(�ɹ�);-1(��������) 
ͷ�ļ���dir.h

searchpath()��dos·������һ���ļ��ĺ���
ԭ�Σ�char *searchpath(const char *file) 
�÷���p=searchpath("�ļ���"); �ȶ���char *p;
���ܣ�����dos·��(���������е�path=....)����λ��file�������ļ���
����ֵ��ָ������·�����ַ�����ָ�롣��λʧ�ܷ���NULL��
ͷ�ļ���dir.h

segread()���μĴ�������
ԭ�Σ�void segread(struct SREGS *segp)
���ã��ѵ�ǰ�Ĵ�����ֵ���浽SREGS�ͻ�������segp�С�
   segs.cs=����μĴ�����ֵ;
   segs.ds=���ݶμĴ�����ֵ��
   segs.es=���ӶμĴ�����ֵ��
   segs.ss=��ջ�μĴ�����ֵ��

setdisk()���õ�ǰ�������ĺ���
ԭ�Σ�int setdisk(int drive)
���ܣ�����driveָ�����������޸ĳɵ�ǰ�����������ؿ�ʹ�õ�����������
ͷ�ļ���dir.h

settextstyle()��ʾ�ַ��ĵ�ǰ���ú���
���ܣ����õ�ǰ���Ӣ���ַ������塢��С�ͷ���
���÷�ʽ��
void far settextstyle(int font,int direction,int charsize)
  ���Тٲ���fontȷ����ѡ����������״��
     DEFAULT_FONT ��0 ��8��8λͼ����
     TRIPLEX_FONT ��1 ������ʸ������
     SMALL_FONT ��2 ��С��ʸ������
     SANS_SERIF_FONT��3 ���޳���ʸ������
     GOTHIC_FONT ��4 �Ǹ���ʸ������
    �ڲ���durection�ַ�����ʾ����
     HORIZ_DIR ��0 ��ˮƽ����
     VERT_DIR ��1 �Ǵ�ֱ����
    �۲���charsize��ʾ�ַ��Ŵ�ı�������ֵΪ0��10��

setvect()�����ж���������
setvect(int �жϺ�,void interrupt(*�жϺ�����)) 
���ܣ����жϷ������ĵ�ַװ���ж��������С�
���÷�����setvect(�жϺţ��жϺ���������ַ);
 (1)��Ԥ�ȶ���Ҫ����ԭ�������º���
  void interrupt �жϺ�����(void)
   {......}
 (2)���ȱ���ԭ�жϺ�����ַ
  void interrupt (*����������)(void);
  ����������=getvect(�жϺ�);
 (3)�º�ý�ԭ�жϺ�����ַװ����������
  setvect(�жϺţ�����������);

setviewport()�����ӿڵĺ���
ԭ�Σ� void far setviewport(int left,int top,int right,int bottom,int clip)
���ܣ������Ͻ�����left,top�����½�����right,bottom����һ���ӿڣ����clipΪ1���򳬳��ӿڵ�����Զ������õ������clipΪ0���򲻱����á�
����setviewport(0,0,100,100,1)�����Խ���Ϊ0��0��100��100���ӿڣ������м��ù��ܡ�
ע��Ҫ�����ǰ�ӿڣ��ú���clearnviewport()��
 