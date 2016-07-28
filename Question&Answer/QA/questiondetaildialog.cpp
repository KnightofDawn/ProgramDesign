#include "questiondetaildialog.h"
#include "ui_questiondetaildialog.h"
#include "totalclass.h"
#include <QHBoxLayout>
#include <QFile>
#include <QTextStream>
#include <QMessageBox>

QuestionDetailDialog::QuestionDetailDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::QuestionDetailDialog)
{
    ui->setupUi(this);
    z = QuestionItemList[siz];
    QString temp = QString::fromLocal8Bit("����")+
                   QString::number(QuestionItemList.size()-siz,10)+": "+
                   SumQuestionList[z].getQuestionTitle();
    if(temp.size() > 20)
    {
        temp.resize(23);
        temp[20]=temp[21]=temp[22]='.';
    }
    ui->label->setToolTip(SumQuestionList[z].getQuestionTitle());
    ui->label->setText(temp);
    ui->label->setFixedWidth(300);

    QString temp1=QString::fromLocal8Bit("������: ")+SumQuestionList[z].getCreatUserId();
    ui->label_2->setText(temp1);
    ui->label_2->setAlignment(Qt::AlignCenter);

    QString temp2=QString::fromLocal8Bit("����ʱ��: ")+SumQuestionList[z].getCreatTime();
    ui->label_3->setText(temp2);
    ui->label_3->setAlignment(Qt::AlignCenter);

    ui->FocusBtn->setText(QString::fromLocal8Bit("��ע���û�"));
    QHBoxLayout *hboxlayout=new QHBoxLayout();
    hboxlayout->addWidget(ui->label);
    hboxlayout->addWidget(ui->label_2);
    hboxlayout->addWidget(ui->label_3);
    hboxlayout->addWidget(ui->FocusBtn);
    this->setLayout(hboxlayout);
    if(SumQuestionList[z].getCreatUserId() == MainUser.getUserId())
    {
        ui->FocusBtn->setEnabled(false);
    }
    for(int i=0;i<UserFocusList.size();i++)
    {
        if(UserFocusList[i] == SumQuestionList[z].getCreatUserId())
        {
            ui->FocusBtn->setText(QString::fromLocal8Bit("�ѹ�ע���û�"));
            ui->FocusBtn->setEnabled(false);
            break;
        }
    }
    connect(ui->FocusBtn,SIGNAL(clicked()),this,SLOT(addFocusList()));

}

QuestionDetailDialog::~QuestionDetailDialog()
{
    delete ui;
}

void QuestionDetailDialog::addFocusList()
{
    UserFocusList.push_back(SumQuestionList[z].getCreatUserId());
    for(int h=0;h<SumUserList.size();h++)
        if(SumUserList[h].getUserId()==MainUser.getUserId())
        {
            MainUser.setFocuslist(UserFocusList);
            SumUserList[h].setFocuslist(UserFocusList);
        }
    ui->FocusBtn->setText(QString::fromLocal8Bit("�ѹ�ע���û�"));
    ui->FocusBtn->setEnabled(false);

    this->sendMessage();
}

void QuestionDetailDialog::sendMessage()
{
    client = new QTcpSocket(this);
    client->connectToHost(QHostAddress("127.0.0.1"), 6665);

    QByteArray data;
    QDataStream out(&data,QIODevice::WriteOnly);
    out << FOCUS << SumUserList.size();
    for(int j = 0; j < SumUserList.size(); j++)
    {
        QList<QString> ls = SumUserList[j].getUserFocuslist();
        out << ls.size();
        for(int i = 0; i < ls.size(); i++)
        {
            out << ls[i];
        }
    }
    client->write(data);
}

