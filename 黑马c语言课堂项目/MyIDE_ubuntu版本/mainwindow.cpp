#include "mainwindow.h"
#include "ui_mainwindow.h"
#include<QMessageBox>
#include<QTextCodec>
#include<QFileDialog>
#include<QFile>
#include<stdio.h>
#include<string.h>

//这个是编码枚举，方便表示编码
enum MyCode
{
    utf_8,gbk
};

//声明全局变量
enum MyCode flag;
//声明一个路径全局变量，用于编译代码
QString path;
//创建字符编码指针
QTextCodec* pcodec;

void init(Ui::MainWindow* ui){
    ui->label->setText("encoding format:utf-8");
    QString str=ui->label->text();
    QMessageBox::information(NULL,"info",str,0);
    str=ui->textEdit->toPlainText();
    QMessageBox::information(NULL,"say hello",str,0);
}
void MainWindow::SayHello(){
    ui->label->setText("encoding format:utf-8");
    QString str=ui->label->text();
    QMessageBox::information(NULL,"info",str,0);
    str=ui->textEdit->toPlainText();
    QMessageBox::information(NULL,"say hello",str,0);
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //清空path
    path="";
    this->setWindowTitle("MyIde");
    //初始化编码码，默认utf-8编码
    flag = utf_8;
    //符编码指针初始化
    pcodec=QTextCodec::codecForName("GBK");

    //init(ui);
    //SayHello();

}

MainWindow::~MainWindow()
{
    delete ui;
}

//utf-8菜单命令处理函数
void MainWindow::on_actionUtf_8_triggered()
{
    flag = utf_8;
    ui->label->setText(pcodec->toUnicode("current encoding:utf-8"));


}

//gbk菜单命令处理函数
void MainWindow::on_actionGbk_triggered()
{
    flag = gbk;
     ui->label->setText(pcodec->toUnicode("current encoding:gbk"));

}

void MainWindow::on_actionOpen_triggered()
{
    //弹出一个打开文件对话框
  // QString path=QFileDialog::getOpenFileName(NULL,"Open file",".",tr("Source Files(*.c *.cpp)"));
    path=QFileDialog::getOpenFileName();
  // if(path==NULL)
   if(path.isEmpty())
   {
       return;
   }
   this->setWindowTitle("MyIde:"+path);
   //Qt方式打开文件
//    QFile file(path);
//    file.open(QIODevice::ReadWrite);
//    ui->textEdit->setText(file.readAll());
   //标准c语言方式打开文件
   //fopen打开文件需要gbk编码，而qt获取的路径是utf-8编码，需要转换

   char *filename=pcodec->fromUnicode(path).data();
    FILE*fp=fopen(filename,"rb");
    if(NULL==fp)
    {
        return;
    }
   //循环读取文件内容
    QString content=" ";
   char buf[1024];
   while (1)
   {
       memset(buf,0,sizeof(buf));
       fgets(buf,1024,fp);
       // content.append(buf);
       if(flag==utf_8)
       {
         content=content+buf;
       }
       else if(flag==gbk)
       {
         //这里需要将gbk转换为utf-8编码
           content=content+pcodec->toUnicode(buf);
       }

       if(feof(fp))
       {
           break;
       }

   }
   //将内容显示在文本编辑器中
    ui->textEdit->setText(content);
   //关闭文件
    fclose(fp);

}
//另存为菜单项点击处理
void MainWindow::on_actionSava_as_triggered()
{
   //弹出另存为对话框,是utf-8编码
     path=QFileDialog::getSaveFileName();
    //如果path为空，表示用户没有选择文件，直接推出
    if(path.isEmpty())
    {
        return;
    }
    //把utf-8编码转换为gbk，标准c语言需要这个编码
    char*filename=pcodec->fromUnicode(path).data();

    //以写的模式打开文件
    FILE*fp=fopen(filename,"w");
    if(NULL==fp){
        return;
    }
    //获取文本框控件打内容，是utf-8编码的
    QString content=ui->textEdit->toPlainText();
    //将获取到的内容转换为gbk然后保存
    //fputs(pcodec->fromUnicode(content).data(),fp);
    fputs(content.toStdString().data(),fp);
    fclose(fp);
}


void MainWindow::SaveFile(char* filename){
    if(filename==NULL)
    {
        return;
    }
    FILE* fp=fopen(filename,"wb");
    QString content=ui->textEdit->toPlainText();
    fputs(content.toStdString().data(),fp);
    fclose(fp);
}


void MainWindow::on_actionNew_triggered()
{
   this->setWindowTitle("MyIde: untitled");
    if(ui->textEdit->toPlainText()!=" ")
    {
      int result= QMessageBox::information(this,"保存提示","保存文件？(y/n)",QMessageBox::Yes | QMessageBox::No);

         if(result==QMessageBox::Yes)
         {

           QString path=QFileDialog::getSaveFileName();
           char* filename=pcodec->fromUnicode(path).data();
           SaveFile(filename);
          }
    }
    //清空编辑器
    //ui->textEdit->setText("");
    ui->textEdit->clear();
    //需要将path清空
    //path="";
    path.clear();
    ui->textEdit->setFocus();
}

//撤销菜单项的处理函数
void MainWindow::on_actionUndo_triggered()
{
    ui->textEdit->undo();
}

//拷贝菜单项的处理函数
void MainWindow::on_actionCopy_triggered()
{
     ui->textEdit->copy();
}
//粘贴菜单项的处理函数
void MainWindow::on_actionPaste_triggered()
{
     ui->textEdit->paste();
}

//剪切菜单项的处理函数
void MainWindow::on_actionCut_triggered()
{
     ui->textEdit->cut();
}

//compile菜单项的处理函数
void MainWindow::on_actionCompile_triggered()
{
   if(path.isEmpty())
   {
       return;
   }
   QString execParh=path;
   execParh.replace(".c","");
  // QString cmdstr="gcc " +path+" "+"-o "+execParh;
    QString cmdstr=QString("gcc %1 -o %2").arg(path).arg(execParh);
    //system函数如果正常执行，返回值为0,否则为1
   int ret=system(pcodec->fromUnicode(cmdstr).data());
    if(ret!=0){
        printf("编译错误，请检查代码");
        return;
    }
    //编译成功，可以运行可执行文件
   //system(execParh.toStdString().data());
   system(pcodec->fromUnicode(execParh).data());


}

void MainWindow::on_actionExit_triggered()
{
    exit(0);
}

void MainWindow::on_actionSave_triggered()
{
    if(path.isEmpty()){
        path=QFileDialog::getSaveFileName();
        if(path.isEmpty())
        {
            return;
        }
       }
    //把utf-8编码转换为gbk，标准c语言需要这个编码
    char*filename=pcodec->fromUnicode(path).data();
    SaveFile(filename);
}

