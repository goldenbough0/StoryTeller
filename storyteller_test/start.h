#ifndef START_H
#define START_H
#include <QWidget>

QT_BEGIN_NAMESPACE
namespace Ui { class Start; }
QT_END_NAMESPACE

class Start : public QWidget
{
    Q_OBJECT

public:
    Start(QWidget *parent = nullptr);
    ~Start();

private:
    Ui::Start *ui;
};
#endif // START_H
