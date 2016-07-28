#include "showqadialog.h"
#include "ui_showqadialog.h"
#include <QTextCodec>
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include "totalclass.h"
#include "mywidget.h"
#include "showquestiondialog.h"
#include "askforquestiondialog.h"
#include "showfocuslistdialog.h"

ShowQADialog::ShowQADialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowQADialog)
{
    ui->setupUi(this);
    ui->label->setText(QString::fromLocal8Bit("��ӭ�����ʴ�ϵͳ,") + temp);
}

ShowQADialog::~ShowQADialog()
{
    delete ui;
}

void ShowQADialog::on_ExitButton_clicked()//�˳���ť����
{
    MyWidget *my = new MyWidget();
    my->show();
    this->close();
    UserFocusList.clear();
    AnswerPriseList.clear();
}

void ShowQADialog::on_LookoverQButton_clicked()//�鿴���ⰴť����
{

    if(SumQuestionList.size()!=0)
    {
        currentpage = 0;
        ShowQuestionDialog *sh = new ShowQuestionDialog();
        sh->show();
        this->close();
    }
    else
    {
         QMessageBox::critical(NULL, QString::fromLocal8Bit("��ʾ"),
                               QString::fromLocal8Bit("��ʱû�����⣬��ȥ���ʰ�"));
    }
}

void ShowQADialog::on_AskQButton_clicked()// ���ʲ���
{
    AskForQuestionDialog *as = new AskForQuestionDialog();
    as->show();
    this->close();
}

void ShowQADialog::on_LookFocusBtn_clicked()// �鿴��ע����
{
    ShowFocusListDialog *sh = new ShowFocusListDialog();
    sh->show();
    this->close();
}
