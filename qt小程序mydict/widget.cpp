#include "widget.h"
#include "ui_widget.h"
#include<stdio.h>
#include<QDebug>
#include "mydict.h"
#include<QTextCodec>

//定义一个全局变量
Dic* p,*p_rev;
int len;
QTextCodec* pCode;

Widget::Widget(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::Widget)
{
    ui->setupUi(this);
   //初始化
    load_dic(&p);
    //字符编码初始化
    pCode=QTextCodec::codecForName("GBK");
    QString path="../dic.txt";
    QByteArray ba = path.toLatin1();
    char * filename=ba.data();
    len=getrowscount(filename);
     //print_dic(p_rev,len);
     qDebug()<<len;
     //print_dic(p,len);
}

Widget::~Widget()
{
    if(p!=NULL){
        free(p);
        p=NULL;
    }

    delete ui;
}

void Widget::on_btn_etoc_clicked()//英译中功能
{
    //1.获取编辑框的内容
    QString keystr=ui->edit_etoc->text();
    //2.判断内容是否有效
    if(keystr.isEmpty())
    {
         ui->lbl_result->setText("内容不能为空");
         return;
    }
    //3.编码转换
    char *key=pCode->fromUnicode(keystr).data();
    char value[100];
    //4.查询并且显示结果
    qDebug()<<key;
    int flag=search_from_dic(p,len,key,value);
     qDebug()<<flag;
    if(!flag){
         ui->lbl_result->setText("查无此词");
    }
      ui->lbl_result->setText(pCode->toUnicode(value));


}
