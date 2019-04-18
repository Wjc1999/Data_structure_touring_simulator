/********************************************************************************
** Form generated from reading UI file 'widget.ui'
**
** Created by: Qt User Interface Compiler version 5.10.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WIDGET_H
#define UI_WIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Widget
{
public:
    QGridLayout *gridLayout;
    QStackedWidget *stackedWidget;
    QWidget *LoginPage;
    QGridLayout *gridLayout_2;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLineEdit *lineEdit;
    QWidget *widget_2;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QSpacerItem *horizontalSpacer;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QLabel *label;
    QTextBrowser *textBrowser;
    QWidget *MainPage;
    QGridLayout *gridLayout_3;
    QPushButton *pushButton_4;
    QPushButton *pushButton_5;
    QPushButton *pushButton_3;
    QPushButton *pushButton_6;
    QSpacerItem *horizontalSpacer_5;
    QSpacerItem *horizontalSpacer_6;
    QSpacerItem *horizontalSpacer_7;
    QSpacerItem *horizontalSpacer_8;
    QSpacerItem *horizontalSpacer_9;
    QSpacerItem *horizontalSpacer_10;
    QSpacerItem *horizontalSpacer_11;
    QSpacerItem *horizontalSpacer_12;
    QWidget *StatePage;
    QGridLayout *gridLayout_5;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_13;
    QPushButton *pushButton_7;
    QSpacerItem *horizontalSpacer_15;
    QWidget *QueryPage;
    QGridLayout *gridLayout_4;
    QSpacerItem *verticalSpacer_4;
    QSpacerItem *horizontalSpacer_14;
    QPushButton *pushButton_8;
    QSpacerItem *horizontalSpacer_16;
    QWidget *OrderPage;
    QGridLayout *gridLayout_6;
    QSpacerItem *verticalSpacer_5;
    QSpacerItem *horizontalSpacer_18;
    QPushButton *pushButton_9;
    QSpacerItem *horizontalSpacer_17;

    void setupUi(QWidget *Widget)
    {
        if (Widget->objectName().isEmpty())
            Widget->setObjectName(QStringLiteral("Widget"));
        Widget->setEnabled(true);
        Widget->resize(1050, 659);
        gridLayout = new QGridLayout(Widget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        stackedWidget = new QStackedWidget(Widget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        stackedWidget->setAutoFillBackground(false);
        LoginPage = new QWidget();
        LoginPage->setObjectName(QStringLiteral("LoginPage"));
        LoginPage->setAutoFillBackground(true);
        gridLayout_2 = new QGridLayout(LoginPage);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        widget = new QWidget(LoginPage);
        widget->setObjectName(QStringLiteral("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(6);
        horizontalLayout->setContentsMargins(11, 11, 11, 11);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        lineEdit = new QLineEdit(widget);
        lineEdit->setObjectName(QStringLiteral("lineEdit"));
        lineEdit->setAutoFillBackground(false);

        horizontalLayout->addWidget(lineEdit);


        gridLayout_2->addWidget(widget, 2, 3, 1, 1);

        widget_2 = new QWidget(LoginPage);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        horizontalLayout_2 = new QHBoxLayout(widget_2);
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        pushButton = new QPushButton(widget_2);
        pushButton->setObjectName(QStringLiteral("pushButton"));

        horizontalLayout_2->addWidget(pushButton);

        pushButton_2 = new QPushButton(widget_2);
        pushButton_2->setObjectName(QStringLiteral("pushButton_2"));

        horizontalLayout_2->addWidget(pushButton_2);


        gridLayout_2->addWidget(widget_2, 3, 3, 1, 1);

        horizontalSpacer = new QSpacerItem(328, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 2, 0, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(328, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_2, 2, 4, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(328, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 3, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(328, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_4, 3, 4, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 236, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 4, 3, 1, 1);

        verticalSpacer = new QSpacerItem(20, 237, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 0, 3, 1, 1);

        label = new QLabel(LoginPage);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        gridLayout_2->addWidget(label, 1, 3, 1, 1);

        textBrowser = new QTextBrowser(LoginPage);
        textBrowser->setObjectName(QStringLiteral("textBrowser"));
        textBrowser->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));

        gridLayout_2->addWidget(textBrowser, 0, 0, 1, 1);

        stackedWidget->addWidget(LoginPage);
        MainPage = new QWidget();
        MainPage->setObjectName(QStringLiteral("MainPage"));
        gridLayout_3 = new QGridLayout(MainPage);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        pushButton_4 = new QPushButton(MainPage);
        pushButton_4->setObjectName(QStringLiteral("pushButton_4"));

        gridLayout_3->addWidget(pushButton_4, 1, 1, 1, 1);

        pushButton_5 = new QPushButton(MainPage);
        pushButton_5->setObjectName(QStringLiteral("pushButton_5"));

        gridLayout_3->addWidget(pushButton_5, 2, 1, 1, 1);

        pushButton_3 = new QPushButton(MainPage);
        pushButton_3->setObjectName(QStringLiteral("pushButton_3"));

        gridLayout_3->addWidget(pushButton_3, 0, 1, 1, 1);

        pushButton_6 = new QPushButton(MainPage);
        pushButton_6->setObjectName(QStringLiteral("pushButton_6"));

        gridLayout_3->addWidget(pushButton_6, 3, 1, 1, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_5, 0, 0, 1, 1);

        horizontalSpacer_6 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_6, 1, 0, 1, 1);

        horizontalSpacer_7 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_7, 0, 2, 1, 1);

        horizontalSpacer_8 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_8, 1, 2, 1, 1);

        horizontalSpacer_9 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_9, 2, 0, 1, 1);

        horizontalSpacer_10 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_10, 2, 2, 1, 1);

        horizontalSpacer_11 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_11, 3, 0, 1, 1);

        horizontalSpacer_12 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_12, 3, 2, 1, 1);

        stackedWidget->addWidget(MainPage);
        StatePage = new QWidget();
        StatePage->setObjectName(QStringLiteral("StatePage"));
        gridLayout_5 = new QGridLayout(StatePage);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_3, 0, 1, 1, 1);

        horizontalSpacer_13 = new QSpacerItem(880, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_13, 1, 0, 1, 1);

        pushButton_7 = new QPushButton(StatePage);
        pushButton_7->setObjectName(QStringLiteral("pushButton_7"));

        gridLayout_5->addWidget(pushButton_7, 1, 1, 1, 1);

        horizontalSpacer_15 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_15, 1, 2, 1, 1);

        stackedWidget->addWidget(StatePage);
        QueryPage = new QWidget();
        QueryPage->setObjectName(QStringLiteral("QueryPage"));
        gridLayout_4 = new QGridLayout(QueryPage);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        verticalSpacer_4 = new QSpacerItem(20, 577, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_4, 0, 1, 1, 1);

        horizontalSpacer_14 = new QSpacerItem(880, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_14, 1, 0, 1, 1);

        pushButton_8 = new QPushButton(QueryPage);
        pushButton_8->setObjectName(QStringLiteral("pushButton_8"));

        gridLayout_4->addWidget(pushButton_8, 1, 1, 1, 1);

        horizontalSpacer_16 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_16, 1, 2, 1, 1);

        stackedWidget->addWidget(QueryPage);
        OrderPage = new QWidget();
        OrderPage->setObjectName(QStringLiteral("OrderPage"));
        gridLayout_6 = new QGridLayout(OrderPage);
        gridLayout_6->setSpacing(6);
        gridLayout_6->setContentsMargins(11, 11, 11, 11);
        gridLayout_6->setObjectName(QStringLiteral("gridLayout_6"));
        verticalSpacer_5 = new QSpacerItem(20, 577, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_6->addItem(verticalSpacer_5, 0, 1, 1, 1);

        horizontalSpacer_18 = new QSpacerItem(880, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_18, 1, 0, 1, 1);

        pushButton_9 = new QPushButton(OrderPage);
        pushButton_9->setObjectName(QStringLiteral("pushButton_9"));

        gridLayout_6->addWidget(pushButton_9, 1, 1, 1, 1);

        horizontalSpacer_17 = new QSpacerItem(13, 20, QSizePolicy::Fixed, QSizePolicy::Minimum);

        gridLayout_6->addItem(horizontalSpacer_17, 1, 2, 1, 1);

        stackedWidget->addWidget(OrderPage);

        gridLayout->addWidget(stackedWidget, 0, 0, 1, 2);


        retranslateUi(Widget);

        QMetaObject::connectSlotsByName(Widget);
    } // setupUi

    void retranslateUi(QWidget *Widget)
    {
        Widget->setWindowTitle(QApplication::translate("Widget", "Touring_Simulator", nullptr));
        pushButton->setText(QApplication::translate("Widget", "\347\231\273\351\231\206", nullptr));
        pushButton_2->setText(QApplication::translate("Widget", "\346\263\250\345\206\214", nullptr));
        label->setText(QApplication::translate("Widget", "\346\254\242\350\277\216\344\275\277\347\224\250", nullptr));
        pushButton_4->setText(QApplication::translate("Widget", "\347\212\266\346\200\201\346\237\245\350\257\242", nullptr));
        pushButton_5->setText(QApplication::translate("Widget", "\350\267\257\347\272\277\346\237\245\350\257\242", nullptr));
        pushButton_3->setText(QApplication::translate("Widget", "\351\242\204\345\256\232\350\241\214\347\250\213", nullptr));
        pushButton_6->setText(QApplication::translate("Widget", "\346\250\241\346\213\237\346\227\205\350\241\214", nullptr));
        pushButton_7->setText(QApplication::translate("Widget", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", nullptr));
        pushButton_8->setText(QApplication::translate("Widget", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", nullptr));
        pushButton_9->setText(QApplication::translate("Widget", "\350\277\224\345\233\236\344\270\273\350\217\234\345\215\225", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Widget: public Ui_Widget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WIDGET_H
