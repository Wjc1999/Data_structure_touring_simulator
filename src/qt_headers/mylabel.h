#ifndef MYLABEL_H
#define MYLABEL_H

#include <QLabel>
#include <QMenu>
#include <QAction>
#include <QLabel>
#include <../headers/id_map.h>
#include <QResizeEvent>
#include <utility>

class MyLabel : public QLabel
{
    Q_OBJECT
public:
    explicit MyLabel(QWidget *parent = 0);
    void initializMyLabel(IDMap *a);
    void setOriginPixmap();
    bool hasOriginPixmap();
protected:
    void mousePressEvent(QMouseEvent *ev);
    void resizeEvent(QResizeEvent *ev);
signals:

public slots:
    void origin_action_triggered();
    void destination_action_triggered();
    void transfer_action_triggered();
private:
    int mouse_x_;
    int mouse_y_;

    QMenu *rightbutton_menu;
    QLabel *mark_origin;
    QRect rect_mark_origin;
    QLabel *mark_destination;
    QLabel *mark_transfer[31];

    std::pair<int, int> city_pos_[31];      //在图片大小为900x650情况下
    double origin_col_map_[7];
    double col_map_[7];
    double origin_row_map_[5];
    double row_map_[5];
    void UpdateColAndRowMap();
    QSize origin_qsize_;
    QSize current_qsize_;

    IDMap *idmap;

    void initialize_citymap_pos();
    bool in_city_range(int i);
    int judge_mouse_pos();

    QPixmap origin_pixmap;
};

#endif // MYLABEL_H
