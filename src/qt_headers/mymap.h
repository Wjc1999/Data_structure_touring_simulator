#ifndef MYMAP_H
#define MYMAP_H

#include <QLabel>
#include <../headers/traveller.h>

class MyMap : public QLabel
{
    Q_OBJECT
public:
    explicit MyMap(QWidget *parent = nullptr);
    void initialize(Traveller *traveller);
private:
    QLabel *plane;
    QLabel *car;
    QLabel *train;
    Traveller *traveller;

    std::pair<int, int> city_pos_[31];

    void initialize_citymap_pos();
    void update();
signals:

public slots:
};

#endif // MYMAP_H
