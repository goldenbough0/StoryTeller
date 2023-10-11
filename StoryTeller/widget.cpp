#include "widget.h"
#include "developer.h"
#include <QDebug>
#include <QPushButton>
#include <QObject>
#include <QLabel>
Widget::Widget(QWidget *parent)
    : QWidget(parent)
{
    Developer* developer = new Developer;

    QLabel *titleLabel = new QLabel("--StoryTeller--",this);
    titleLabel->setGeometry(width()/2-150,50,200,30);
    titleLabel->setFont(QFont("Arial",14));
//    titleLabel->setAlignment(Qt::AlignCenter);
    QLabel *label2 = new QLabel("模式选择",this);
    label2->setGeometry(width()/2-110,100,100,30);
    label2->setFont(QFont("Arial",10));
//    label2->setAlignment(Qt::AlignCenter);
    QPushButton *btn1 = new QPushButton("开发者",this);
    btn1->move(100,200);
    QPushButton *btn2 = new QPushButton("玩家",this);
    btn2->move(300,200);

    setWindowTitle("StoryTeller");
    developer->setWindowTitle("DeveloperMode");

    connect(btn1,&QPushButton::clicked,developer,[=]()
    {
        developer->show();
    });
}

Widget::~Widget()
{
}

