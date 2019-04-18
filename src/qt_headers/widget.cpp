#ifndef SRC_WIDGET
#define SRC_WIDGET

#include "widget.h"
#include <QString>
#include <QWidget>
#include <QMessageBox>

Widget::Widget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Widget)
{
    ui->setupUi(this);
    ui->stackedWidget->setCurrentWidget(ui->LoginPage);
}

Widget::~Widget()
{
    delete ui;
}

void Widget::on_pushButton_released()//登陆
{
    QString account_name = ui->lineEdit->text();
    if(!account_name.size())
    {
        QMessageBox::warning(this,"Warning!","输入为空", QMessageBox::Ok);
        return;
    }
    else if(!IsValidName(account_name.toStdString()))
    {
        QMessageBox::warning(this,"Warning!","非法的用户名,请重新输入", QMessageBox::Ok);
        return;
    }
    int account_check = AccountCheck(account_name.toStdString());
    if(account_check != -1)
    {
        traveller_widget.LoadData(account_check, citygraph_widget);
        ui->stackedWidget->setCurrentWidget(ui->MainPage);
    }
    else
    {
        QMessageBox::StandardButton sB = QMessageBox::question(this, "" , "该账号不存在，是否注册:"+account_name, QMessageBox::Yes|QMessageBox::No);
        if(sB == QMessageBox::Yes)
        {
            AddAccount(account_name.toStdString());//?
            traveller_widget.set_id(account_name.toStdString());
            ui->stackedWidget->setCurrentWidget(ui->MainPage);
        }
    }
}

void Widget::on_pushButton_2_released()//注册
{
    QString account_name = ui->lineEdit->text();
    if(!account_name.size())
    {
        QMessageBox::warning(this,"Warning!","输入为空", QMessageBox::Ok);
        return;
    }
    else if(!IsValidName(account_name.toStdString()))
    {
        QMessageBox::warning(this,"Warning!","非法的用户名,请重新输入", QMessageBox::Ok);
        return;

    }
    int account_check = AccountCheck(account_name.toStdString());
    if(account_check != -1)
    {
        QMessageBox::warning(this,"Warning!","该账号已被注册，请重新输入", QMessageBox::Ok);
        return;
    }
    else
    {
        AddAccount(account_name.toStdString());//?
        traveller_widget.set_id(account_name.toStdString());
        ui->stackedWidget->setCurrentWidget(ui->MainPage);
    }
}

void Widget::on_pushButton_3_released()//功能选择
{
    ui->stackedWidget->setCurrentWidget(ui->OrderPage);
}

void Widget::on_pushButton_4_released()//功能选择
{
    ui->stackedWidget->setCurrentWidget(ui->StatePage);
}

void Widget::on_pushButton_5_released()//功能选择
{
    ui->stackedWidget->setCurrentWidget(ui->QueryPage);
    ui->textBrowser->clear();
}

void Widget::on_pushButton_7_released()//返回键
{
    ui->stackedWidget->setCurrentWidget(ui->MainPage);
}

void Widget::on_pushButton_8_released()//返回键
{
    ui->stackedWidget->setCurrentWidget(ui->MainPage);
}

void Widget::on_pushButton_9_released()//返回键
{
    ui->stackedWidget->setCurrentWidget(ui->MainPage);
}




void Widget::on_pushButton_11_released()
{
    City_id start_city = ui->comboBox->currentIndex();
    City_id target_city = ui->comboBox_2->currentIndex();
    if(start_city == target_city)
    {
        QMessageBox::warning(this,"Warning!","始发地不能与目的地一样", QMessageBox::Ok);
        return;
    }

    int size = citygraph_widget.Getsize(start_city, target_city);
    if (!size)
    {
        QMessageBox::warning(this,"Warning!","两城市间无路线", QMessageBox::Ok);
    }
    else
    {
        ui->textBrowser->clear();
        QString qtemp;
        std::string comp("三个字");
        std::string wrap[] = {"\t\t", "\t"};
        qtemp = "序号\t始发地\t\t目的地\t\t方式\t出发时间\t到达时间\t价格\t";
        /*temp += "序号" += "\t"
             += "始发地"
             += "\t\t"
             += "目的地"
             += "\t\t"
             += "方式" += "\t"
             += "出发时间" += "\t"
             += "到达时间" += "\t"
             += "价格" += "\t";*/
        ui->textBrowser->append(qtemp);
        std::string temp;
        for (int k = 0; k < size; k++)
        {
            qtemp.clear();
            temp.clear();
            Route route = citygraph_widget.GetRoute(start_city, target_city, k);

            std::string cityi = idmap_widget.GetCityStr(start_city);
            std::string cityj = idmap_widget.GetCityStr(target_city);
            std::string method = idmap_widget.GetTransStr(route.transport_type);
            temp += std::to_string(k+1) + "\t";
            temp += cityi + wrap[cityi.size() > comp.size()];
            temp += cityj + wrap[cityj.size() > comp.size()];
            temp += method + "\t";
            temp += RouteShow(route.start_time, route.end_time);
            temp += route.price + "\t";
            /*std::cout << k + 1 << '\t'
                      << cityi << wrap[cityi.size() > comp.size()]
                      << cityj << wrap[cityj.size() > comp.size()]
                      << method << '\t';
            RouteShow(route.start_time, route.end_time);
            std::cout << route.price << '\t' << std::endl;*/
            ui->textBrowser->append(qtemp.fromStdString(temp));
        }
    }
}
#endif // SRC_WIDGET
