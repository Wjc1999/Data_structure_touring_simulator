#ifndef WIDGET_H
#define WIDGET_H
#pragma execution_character_set("utf-8")

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
#include "simulator.h"

#include "ui_widget.h"
#include <QDebug>

namespace Ui
{
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
    std::vector<City_id> plan_widget;
    Strategy strategy_widget;
    Time limit_time_widget;
    Time init_time_widget;

  private slots:
    void on_LogInButton_released();

    void on_SignUpButton_released();

    void on_OrderPageButton_released();

    void on_StatePageButton_released();

    void on_QueryPathPageButton_released();

    void on_SimulationPageButton_released();

    void on_StatePageToMenuButton_released();

    void on_OrderPageToMenuButton_released();

    void on_QueryPathButton_released();

    void on_QueryPageToMenuButton_released();

    void on_strategy_comboBox_currentIndexChanged(int index);

    void on_OrderPathButton_released();

    void on_SimuToMenuButton_released();

    void on_StartButton_released();

    void on_StopButton_released();

    void on_ContinueButton_released();

    void on_ResetButton_released();

private:
    Ui::Widget *ui;
    void UpdateTable(QTableWidget *table, int row, City_id start_city, City_id target_city, int k);
    Simulator simulator;
};

#endif // WIDGET_H
