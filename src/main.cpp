#ifndef SRC_MAIN
#define SRC_MAIN

#include "qt_headers/widget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;
    w.show();

    return a.exec();
}
#endif // SRC_MAIN
