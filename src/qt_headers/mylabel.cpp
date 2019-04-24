#ifndef SRC_MYLABEL
#define SRC_WYLABEL

#include "mylabel.h"
#include <QMouseEvent>
#include <QDebug>
#include <QPixmap>
#include <QString>
#include <cmath>
#include <QResizeEvent>

#define r_city 7  //半径

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    
}

MyLabel::MyLabel(QWidget *parent) : QLabel(parent)
{
    this->setScaledContents(true);
    //this->setScaledContents(false);
    //this->setSizePolicy( QSizePolicy::Ignored, QSizePolicy::Ignored );
}

void MyLabel::setOriginPixmap()
{
    if (!hasOriginPixmap())
        origin_pixmap = *pixmap();
}

bool MyLabel::hasOriginPixmap()
{
    return !origin_pixmap.isNull();
}

void MyLabel::mousePressEvent(QMouseEvent *ev)
{
    qDebug() << ev->x() << ev->y();
    if(ev->button() == Qt::LeftButton)
    {
        mouse_x = ev->x();
        mouse_y = ev->y();
        QString temp;
        int i = judge_mouse_pos();
        qDebug() << i;
        //这里打不出对应城市名？
        //if(i!=-1)temp.fromStdString(idmap->GetCityStr(i));
        //qDebug() << temp;
    }
    else if(ev->button() == Qt::RightButton)
    {
        mouse_x = ev->x();
        mouse_y = ev->y();
        QString temp;
        int i = judge_mouse_pos();
        qDebug() << i;
        //if(i!=-1)temp.fromStdString(idmap->GetCityStr(i));
        //qDebug() << temp;
        rightbutton_menu->popup(ev->globalPos());
    }
}

void MyLabel::initializMyLabel(IDMap *a)
{
    idmap = a;

    rightbutton_menu = new QMenu(this);
    QAction *add_origin = new QAction(rightbutton_menu);
    QAction *add_destination = new QAction(rightbutton_menu);
    QAction *add_transfer = new QAction(rightbutton_menu);

    add_origin->setText("起点");
    add_destination->setText("终点");
    add_transfer->setText("途径点");

    rightbutton_menu->addAction(add_origin);
    rightbutton_menu->addAction(add_destination);
    rightbutton_menu->addAction(add_transfer);

    connect(add_origin, SIGNAL(triggered()), this, SLOT(origin_action_triggered()));
    connect(add_destination, SIGNAL(triggered()), this, SLOT(destination_action_triggered()));
    connect(add_transfer, SIGNAL(triggered()), this, SLOT(transfer_action_triggered()));

    mark_origin = new QLabel(this);
    mark_origin->setPixmap(QPixmap(":/image/1.png"));
    mark_origin->setScaledContents(true);
    mark_origin->resize(66,66);
    mark_origin->hide();

    mark_destination = new QLabel(this);
    mark_destination->setPixmap(QPixmap(":/image/2.png"));
    mark_destination->setScaledContents(true);
    mark_destination->resize(66,66);
    mark_destination->hide();


    for(int i=0;i<31;i++)
    {
        mark_transfer[i] = new QLabel(this);
        mark_transfer[i]->setPixmap(QPixmap(":/image/3.png"));
        mark_transfer[i]->setScaledContents(true);
        mark_transfer[i]->resize(66,66);
        mark_transfer[i]->hide();
    }

    initialize_citymap_pos();
}

MyLabel::origin_action_triggered()
{
    mark_origin->move(mouse_x - 33, mouse_y - 63);
    mark_origin->show();
}

MyLabel::destination_action_triggered()
{

}

MyLabel::transfer_action_triggered()
{

}

int MyLabel::judge_mouse_pos()
{
    if(mouse_x > col_map[0])
    {
        if(mouse_x < col_map[1])
        {
            if(mouse_y < row_map[0])
            {
                if(in_city_range(6))return 6;
            }
            else if(mouse_y > row_map[2] && mouse_y < row_map[3])
            {
                if(in_city_range(30))return 30;
            }
        }
        else if(mouse_x > col_map[2] && mouse_x < col_map[3])
        {
            if(mouse_y > row_map[1] && mouse_y < row_map[2])
            {
                if(in_city_range(25))return 25;
                if(in_city_range(7))return 7;
            }
            else if(mouse_y > row_map[2] && mouse_y < row_map[3])
            {
                if(in_city_range(23))return 23;
            }
            else if(mouse_y > row_map[3] && mouse_y < row_map[4])
            {
                if(in_city_range(24))return 24;
            }
        }
        else if(mouse_x > col_map[3] && mouse_x < col_map[4])
        {
            if(mouse_y > row_map[0] && mouse_y < row_map[1])
            {
                if(in_city_range(8))return 8;
            }
            else if(mouse_y > row_map[1] && mouse_y < row_map[2])
            {
                if(in_city_range(10))return 10;
            }
            else if(mouse_y > row_map[2] && mouse_y < row_map[3])
            {
                if(in_city_range(28))return 28;
            }
            else if(mouse_y > row_map[3] && mouse_y < row_map[4])
            {
                if(in_city_range(20))return 20;
            }
            else if(mouse_y > row_map[4])
            {
                if(in_city_range(19))return 19;
            }
        }
        else if(mouse_x > col_map[4] && mouse_x < col_map[5])
        {
            if(mouse_y > row_map[0] && mouse_y < row_map[1])
            {
                if(in_city_range(5))return 5;
                if(in_city_range(9))return 9;
                if(in_city_range(1))return 1;
                if(in_city_range(29))return 29;
                if(in_city_range(26))return 26;
            }
            else if(mouse_y > row_map[1] && mouse_y < row_map[2])
            {
                if(in_city_range(0))return 0;
                if(in_city_range(11))return 11;
            }
            else if(mouse_y > row_map[2] && mouse_y < row_map[3])
            {
                if(in_city_range(12))return 12;
                if(in_city_range(22))return 22;
                if(in_city_range(21))return 21;
                if(in_city_range(17))return 17;
            }
            else if(mouse_y > row_map[4])
            {
                if(in_city_range(16))return 16;
                if(in_city_range(18))return 18;
            }
        }
        else if(mouse_x > col_map[5] && mouse_x < col_map[6])
        {
            if(mouse_y < row_map[0])
            {
                if(in_city_range(3))return 3;
                if(in_city_range(4))return 4;
                if(in_city_range(2))return 2;
            }
            else if(mouse_y > row_map[2] && mouse_y < row_map[3])
            {
                if(in_city_range(13))return 13;
                if(in_city_range(27))return 27;
                if(in_city_range(14))return 14;
            }
            else if(mouse_y > row_map[3] && mouse_y < row_map[4])
            {
                if(in_city_range(15))return 15;
            }
        }
    }
    return -1;
}

void MyLabel::initialize_citymap_pos()
{
    // 900 650图片下
    city_pos[0][0] = 674;city_pos[0][1] = 323;  //济南
    city_pos[1][0] = 631;city_pos[1][1] = 291;  //石家庄
    city_pos[2][0] = 768;city_pos[2][1] = 172;  //长春
    city_pos[3][0] = 778;city_pos[3][1] = 135;  //哈尔滨
    city_pos[4][0] = 749;city_pos[4][1] = 212;  //沈阳
    city_pos[5][0] = 580;city_pos[5][1] = 249;  //呼和浩特
    city_pos[6][0] = 234;city_pos[6][1] = 179;  //乌鲁木齐
    city_pos[7][0] = 465;city_pos[7][1] = 340;  //兰州
    city_pos[8][0] = 500;city_pos[8][1] = 294;  //银川
    city_pos[9][0] = 597;city_pos[9][1] = 301;  //太原
    city_pos[10][0] = 545;city_pos[10][1] = 368;//西安
    city_pos[11][0] = 625;city_pos[11][1] = 356;//郑州
    city_pos[12][0] = 686;city_pos[12][1] = 400;//合肥
    city_pos[13][0] = 718;city_pos[13][1] = 399;//南京
    city_pos[14][0] = 736;city_pos[14][1] = 423;//杭州
    city_pos[15][0] = 734;city_pos[15][1] = 499;//福州
    city_pos[16][0] = 632;city_pos[16][1] = 563;//广州
    city_pos[17][0] = 668;city_pos[17][1] = 459;//南昌
    city_pos[18][0] = 578;city_pos[18][1] = 624;//海口
    city_pos[19][0] = 541;city_pos[19][1] = 571;//南宁
    city_pos[20][0] = 510;city_pos[20][1] = 506;//贵阳
    city_pos[21][0] = 620;city_pos[21][1] = 471;//长沙
    city_pos[22][0] = 641;city_pos[22][1] = 430;//武汉
    city_pos[23][0] = 465;city_pos[23][1] = 433;//成都
    city_pos[24][0] = 440;city_pos[24][1] = 533;//昆明
    city_pos[25][0] = 430;city_pos[25][1] = 326;//西宁
    city_pos[26][0] = 672;city_pos[26][1] = 273;//天津
    city_pos[27][0] = 759;city_pos[27][1] = 407;//上海
    city_pos[28][0] = 505;city_pos[28][1] = 451;//重庆
    city_pos[29][0] = 657;city_pos[29][1] = 254;//北京
    city_pos[30][0] = 246;city_pos[30][1] = 435;//拉萨

    col_map[0] = 218;
    col_map[1] = 267;
    col_map[2] = 414;
    col_map[3] = 487;
    col_map[4] = 559;
    col_map[5] = 702;
    col_map[6] = 799;

    row_map[0] = 230;
    row_map[1] = 310;
    row_map[2] = 382;
    row_map[3] = 485;
    row_map[4] = 550;
}

bool MyLabel::in_city_range(int i)
{
    //qDebug() << sqrt(pow(mouse_x - city_pos[i][0], 2) + pow(mouse_y - city_pos[i][1], 2));
    return sqrt(pow(mouse_x - city_pos[i][0], 2) + pow(mouse_y - city_pos[i][1], 2)) < r_city;
    int x = ev->x();
    int y = ev->y();
    qDebug() << this->size() << endl
             << this->origin_pixmap.size() << endl;

    // qDebug() << x << y;
}

void MyLabel::resizeEvent(QResizeEvent *ev)
{
    this->setPixmap(origin_pixmap.scaled(ev->size().width(),
                                         ev->size().height(),
                                         Qt::KeepAspectRatio,
                                         Qt::FastTransformation));
}
#endif // SRC_MYLABEL
