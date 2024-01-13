#include "widget.h"
#include "developer.h"
#include <QApplication>
#include <QPushButton>
#include <QObject>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Widget w;

    w.show();
    return a.exec();
}
