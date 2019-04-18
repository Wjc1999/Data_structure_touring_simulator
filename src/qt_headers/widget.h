#ifndef WIDGET_H
#define WIDGET_H

#include "../headers/id_map.h"
#include "../headers/city_graph.h"
#include "../headers/io.h"
#include "../headers/log.h"
#include "../headers/path.h"
#include "../headers/save_at_exit.h"
#include "../headers/simulation.h"
#include "../headers/time_format.h"
#include "../headers/traveller.h"
#include "../headers/user_type.h"

#include "ui_widget.h"
#include <QDebug>

namespace Ui {
class Widget;
}

class Widget : public QWidget
{
    Q_OBJECT

public:
    explicit Widget(QWidget *parent = nullptr);
    ~Widget();
    Traveller traveller_widget;
    CityGraph citygraph_widget;
    IDMap idmap_widget;
    Path path_widget;
    std::vector <City_id> plan_widget;
    Strategy strategy_widget;
    Time limit_time_widget;
    Time init_time_widget;

private slots:
    void on_pushButton_released();

    void on_pushButton_3_released();

    void on_pushButton_4_released();

    void on_pushButton_5_released();

    void on_pushButton_7_released();

    void on_pushButton_8_released();

    void on_pushButton_9_released();

private:
    Ui::Widget *ui;
};

#endif // WIDGET_H
