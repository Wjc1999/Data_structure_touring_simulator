#include "mymap.h"
#include <cmath>
#include <windows.h>

MyMap::MyMap(QWidget *parent) : QLabel(parent)
{
}

void MyMap::initialize(CityGraph *cg, Traveller *t)
{
    traveller_ = t;
    citygraph_ = cg;
    traveller_path_ = traveller_->get_path();
    initialize_citymap_pos();

    plane_image_ = new QLabel(this);
    car_image_ = new QLabel(this);
    train_image_ = new QLabel(this);

    plane_image_->setPixmap(QPixmap(":/image/plane.png"));
    plane_image_->setScaledContents(true);
    plane_image_->resize(66, 66);
    plane_image_->hide();

    car_image_->setPixmap(QPixmap(":/image/car.png"));
    car_image_->setScaledContents(true);
    car_image_->resize(66, 66);
    car_image_->hide();

    train_image_->setPixmap(QPixmap(":/image/train.png"));
    train_image_->setScaledContents(true);
    train_image_->resize(66, 66);
    train_image_->hide();

    //timer_flush_.setInterval(20);
    //connect(&timer_flush_, SIGNAL(timeout()), this, SLOT(flushImage()));
}

void MyMap::ready_for_simulate()
{
    traveller_->InitState(*citygraph_);
    traveller_path_ = traveller_->get_path();
    reset_image();
    is_finished_ = false;
}

void MyMap::reset()
{
    traveller_->InitState(*citygraph_);
    reset_image();
    is_finished_ = false;
}

/*void MyMap::flushImage()
{
    qDebug() << flush_cnt_;
    flush_cnt_++;
    int new_x = round(origin_x_ + flush_cnt_/50*single_distance_*cos_);
    int new_y = round(origin_y_ + flush_cnt_/50*single_distance_*sin_);
    current_image_->move(new_x, new_y);
    if(flush_cnt_==50)
    {
        timer_flush_.stop();
        flush_cnt_ = 0;
    }
}*/

void MyMap::update()
{
    if(traveller_->get_state() == OFF)
    {
        if(traveller_->get_position() != last_pathnode_)
        {
            last_pathnode_ = traveller_->get_position();
            //reset_image();
            PathNode temp = traveller_path_.GetNode(last_pathnode_);
            std::pair <int, int> cityA = city_pos_[temp.former_city];
            std::pair <int, int> cityB = city_pos_[temp.current_city];

            distance_ = sqrt(pow(cityB.first-cityA.first, 2) + pow(cityB.second-cityA.second, 2));
            sin_ = (cityB.second - cityA.second)/distance_;
            cos_ = (cityB.first - cityA.first)/distance_;
            hours_overall_in_single_path = traveller_->get_left_hour();
            single_distance_ = distance_/hours_overall_in_single_path;
            origin_x_ = current_image_->x();
            origin_y_ = current_image_->y();
        }
        //int new_x = round(1/hours_overall_in_single_path*distance_*cos_);
        //int new_y = round(1/hours_overall_in_single_path*distance_*sin_);
        //timer_flush_.start();
        //current_image_->move(current_image_->x()+new_x, current_image_->y()+new_y);
    }
    if(traveller_->get_position()==-1)
    {
        //reset_image();
        is_finished_ = true;
    }
    traveller_->UpdateState(*citygraph_);
}

void MyMap::reset_image()
{
    PathNode first_node;
    if(traveller_->get_position()==-1)first_node = traveller_path_.GetNode(traveller_path_.GetLen()-1);
    else first_node = traveller_path_.GetNode(traveller_->get_position());

    Trans_id type = citygraph_->GetRoute(first_node.former_city, first_node.current_city, first_node.kth_way).transport_type;
    int first_x, first_y;
    if(traveller_->get_position()==-1)
    {
        first_x = city_pos_[first_node.current_city].first;
        first_y = city_pos_[first_node.current_city].second;
    }
    else
    {
        first_x = city_pos_[first_node.former_city].first;
        first_y = city_pos_[first_node.former_city].second;
    }
    switch (type) {
    case 0://car
        car_image_->show();
        train_image_->hide();
        plane_image_->hide();
        first_x -= 33;
        first_y -= 44;
        car_image_->move(first_x, first_y);
        current_image_ = car_image_;
        break;
    case 1://train
        train_image_->show();
        car_image_->hide();
        plane_image_->hide();
        first_x -= 33;
        first_y -= 50;
        train_image_->move(first_x, first_y);
        current_image_ = train_image_;
        break;
    case 2://plane
        plane_image_->show();
        train_image_->hide();
        car_image_->hide();
        first_x -= 33;
        first_y -= 44;
        plane_image_->move(first_x, first_y);
        current_image_ = plane_image_;
        break;
    default:
        break;
    }
}

void MyMap::initialize_citymap_pos()
{
    // 900 650图片下
    city_pos_[0] = std::make_pair(674, 323);  //济南
    city_pos_[1] = std::make_pair(631, 291);  //石家庄
    city_pos_[2] = std::make_pair(768, 172);  //长春
    city_pos_[3] = std::make_pair(778, 135);  //哈尔滨
    city_pos_[4] = std::make_pair(749, 212);  //沈阳
    city_pos_[5] = std::make_pair(580, 249);  //呼和浩特
    city_pos_[6] = std::make_pair(234, 179);  //乌鲁木齐
    city_pos_[7] = std::make_pair(465, 340);  //兰州
    city_pos_[8] = std::make_pair(500, 294);  //银川
    city_pos_[9] = std::make_pair(597, 301);  //太原
    city_pos_[10] = std::make_pair(545, 368); //西安
    city_pos_[11] = std::make_pair(625, 356); //郑州
    city_pos_[12] = std::make_pair(686, 400); //合肥
    city_pos_[13] = std::make_pair(718, 399); //南京
    city_pos_[14] = std::make_pair(736, 423); //杭州
    city_pos_[15] = std::make_pair(734, 499); //福州
    city_pos_[16] = std::make_pair(632, 563); //广州
    city_pos_[17] = std::make_pair(668, 459); //南昌
    city_pos_[18] = std::make_pair(578, 624); //海口
    city_pos_[19] = std::make_pair(541, 571); //南宁
    city_pos_[20] = std::make_pair(510, 506); //贵阳
    city_pos_[21] = std::make_pair(620, 471); //长沙
    city_pos_[22] = std::make_pair(641, 430); //武汉
    city_pos_[23] = std::make_pair(465, 433); //成都
    city_pos_[24] = std::make_pair(440, 533); //昆明
    city_pos_[25] = std::make_pair(430, 326); //西宁
    city_pos_[26] = std::make_pair(672, 273); //天津
    city_pos_[27] = std::make_pair(759, 407); //上海
    city_pos_[28] = std::make_pair(505, 451); //重庆
    city_pos_[29] = std::make_pair(657, 254); //北京
    city_pos_[30] = std::make_pair(246, 435); //拉萨
}
