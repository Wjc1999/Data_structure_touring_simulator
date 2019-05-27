#ifndef MYMAP_H
#define MYMAP_H

#include <QLabel>
#include <QTimer>
#include <QDebug>
#include <../headers/traveller.h>
#include <../headers/city_graph.h>

class MyMap : public QLabel
{
    Q_OBJECT
public:
    Traveller *traveller_;
    Path traveller_path_;
    CityGraph *citygraph_;
    explicit MyMap(QWidget *parent = nullptr);
    void initialize(CityGraph *cg, Traveller *traveller);//初始化，绑定指针
    void ready_for_simulate();//每次模拟被打开时设置好图片位置等
    bool is_finished() const {return is_finished_;}
    void update();
    void reset();

private:
    QLabel *plane_image_;//飞机图
    QLabel *car_image_;//车图
    QLabel *train_image_;//火车图
    QLabel *current_image_;//当前操作的图
    QTimer timer_flush_;
    std::pair <int, int> city_pos_[31];
    bool is_finished_ = false;
    int last_pathnode_ = -1;
    int hours_overall_in_single_path;
    int flush_cnt_ = 0;
    double distance_;
    double single_distance_;
    double sin_;
    double cos_;
    int origin_x_;
    int origin_y_;

    void initialize_citymap_pos();
    void reset_image();
signals:

public slots:
    void flushImage();
};

#endif // MYMAP_H
