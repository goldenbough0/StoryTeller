#include "framelessWidget.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    framelessWidget w;
//    framelessWidgetDeveloper s;
//    framelessWidgetPlayer p;
//    s.setWindowFlag(Qt::FramelessWindowHint);
//    s.setAttribute(Qt::WA_TranslucentBackground);
//    s.show();

    w.setWindowFlag(Qt::FramelessWindowHint);
    //w.setAttribute(Qt::WA_TranslucentBackground);
    w.show();
//    p.setWindowFlag(Qt::FramelessWindowHint);
//    p.setAttribute(Qt::WA_TranslucentBackground);
//    p.show();

    return a.exec();
}
