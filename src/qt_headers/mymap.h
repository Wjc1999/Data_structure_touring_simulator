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
    explicit MyMap(QWidget *parent = nullptr);
    Traveller *traveller_;
    Path traveller_path_;
    CityGraph *citygraph_;

    void initialize(CityGraph *cg, Traveller *traveller); //初始化，绑定指针
    void ready_for_simulate();                            //每次模拟被打开时设置好图片位置等
    void reset();
    void set_flush_per_hour(int i) { flush_per_hour_ = i; }
    void move(int path_node, int hour_left, int cnt);
    QLabel *current_image_; //当前操作的图

private:
    QLabel *plane_image_; //飞机图
    QLabel *car_image_;   //车图
    QLabel *train_image_; //火车图

    std::pair<int, int> city_pos_[31];
    int flush_per_hour_ = 50;         //不要手动更改
    int last_pathnode_ = -1;          //记录上个点
    int hours_overall_in_single_path; //记录小时总数
    double tan_;
    double speed_;
    int origin_x_;
    int origin_y_;

    void initialize_citymap_pos();
    void reset_image(int i);
    void move_image(int x, int y);
signals:

public slots:
    //void flushImage();
};

#endif // MYMAP_H
