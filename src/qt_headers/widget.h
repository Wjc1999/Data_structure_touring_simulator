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
    explicit Widget(QWidget *parent = 0);
    ~Widget();

private slots:
    void on_pushButton_released();

private:
    Ui::Widget *ui;
    Traveller traveller;
    CityGraph citygraph;
    IDMap idmap;
    Path path;
    std::vector<City_id> plan;
    Strategy strategy;
    Time limit_time;
    Time init_time;
};

#endif // WIDGET_H
