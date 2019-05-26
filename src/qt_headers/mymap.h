#ifndef MYMAP_H
#define MYMAP_H

#include <QLabel>
#include <../headers/traveller.h>
#include <../headers/city_graph.h>

class MyMap : public QLabel
{
    Q_OBJECT
public:
    Traveller* traveller_;
    const Path traveller_path_;
    CityGraph* citygraph_;
    explicit MyMap(QWidget *parent = nullptr);
    void initialize(CityGraph *cg, Traveller *traveller);
    void update();
    void reset();
private:
    QLabel* plane_image_;
    QLabel* car_image_;
    QLabel* train_image_;
    std::pair<int, int> city_pos_[31];

    void initialize_citymap_pos();
signals:

public slots:
};

#endif // MYMAP_H
