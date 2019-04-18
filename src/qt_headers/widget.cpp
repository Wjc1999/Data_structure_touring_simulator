#ifndef SRC_WIDGET
#define SRC_WIDGET

#include "widget.h"
#include <QString>
#include <QWidget>

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

void Widget::on_pushButton_released()
{
    QString accout_name = ui->lineEdit->text();
}

void Widget::on_pushButton_3_released()
{
    ui->stackedWidget->setCurrentWidget(ui->OrderPage);
}

void Widget::on_pushButton_4_released()
{
    ui->stackedWidget->setCurrentWidget(ui->StatePage);
}

void Widget::on_pushButton_5_released()
{
    ui->stackedWidget->setCurrentWidget(ui->QueryPage);
}

void Widget::on_pushButton_7_released()
{
    ui->stackedWidget->setCurrentWidget(ui->MainPage);
}

void Widget::on_pushButton_8_released()
{
    ui->stackedWidget->setCurrentWidget(ui->MainPage);
}

void Widget::on_pushButton_9_released()
{
    ui->stackedWidget->setCurrentWidget(ui->MainPage);
}
#endif // SRC_WIDGET
