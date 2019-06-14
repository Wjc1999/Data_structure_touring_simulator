#ifndef MY_TABLE_WIDGET_ITEM_H
#define MY_TABLE_WIDGET_ITEM_H

#include <QTableWidgetItem>
#include <QString>
#include <QStringList>
#include <QRegExp>

class TimeTableWidgetItem : public QTableWidgetItem
{
public:
    TimeTableWidgetItem(const QString txt = QString("0"))
        : QTableWidgetItem(txt)
    {
    }

    bool operator<(const QTableWidgetItem &other) const
    {
        QString a_str = text();
        QString b_str = other.text();
        int a_hour, b_hour;

        QStringList a_list = a_str.split(QRegExp("[:\\+]"));
        QStringList b_list = b_str.split(QRegExp("[:\\+]"));

        a_hour = a_list[0].toInt();
        b_hour = b_list[0].toInt();

        if (a_list.size() == 3)
        {
            a_hour += a_list[2].toInt() * 24;
        }

        if (b_list.size() == 3)
        {
            b_hour += b_list[2].toInt() * 24;
        }

        return a_hour < b_hour;
    }
};

#endif // MY_TABLE_WIDGET_ITEM_H
