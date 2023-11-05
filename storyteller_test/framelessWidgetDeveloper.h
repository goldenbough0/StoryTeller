#ifndef _FRAMELESSWIDGETDEVELOPER_H
#define _FRAMELESSWIDGETDEVELOPER_H

#include <QMainWindow>
#include <QTimer>
#include <QMouseEvent>
#include <QGraphicsDropShadowEffect>
#include <QDebug>
#include <qpainter.h>
#include <QPainterPath>
#include "node.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QHash>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QStackedWidget>
#include<qgraphicsitem.h>

QT_BEGIN_NAMESPACE
namespace Ui { class framelessWidgetDeveloper; }
QT_END_NAMESPACE

class framelessWidgetDeveloper : public QWidget
{
    Q_OBJECT

public:
    explicit framelessWidgetDeveloper(QWidget *parent = nullptr);
    ~framelessWidgetDeveloper();
    void handleNodeSelected(node* selectedNode);
    void resizeEvent(QResizeEvent *event);

private slots:
    // 创建节点
    void createNode();
    // 增加子节点
    void addChildNode();
    // 删除节点
    void deleteNode();
    // 读取选中节点
    void handleSelectionChanged();
    // 保存文本
    void saveNodeText();

private:
    Ui::framelessWidgetDeveloper *ui;
    int cornerRadius = 20;
    QPoint lastPos;
    //QWidget *border = nullptr;
    QGraphicsDropShadowEffect *windowShadow;

    bool mousePressed = false;
    enum {AT_LEFT = 1, AT_TOP = 2,  AT_RIGHT = 4, AT_BOTTOM = 8,
          AT_TOP_LEFT = 3, AT_TOP_RIGHT = 6, AT_BOTTOM_LEFT = 9, AT_BOTTOM_RIGHT = 12};
    int mouseState;
    bool maximized = false;

    //void Init();
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event){
        mousePressed = false;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        if(event->globalPosition().y() < 2)
            controlWindowScale();
#else
        if(event->globalPos().y() < 2)
            controlWindowScale();
#endif
    }
    void mouseDoubleClickEvent(QMouseEvent *event)
    {
        if(event->y()<60)
            controlWindowScale();
    };
    //void resizeEvent(QResizeEvent *event);

    QRect lastGeometry;
    void controlWindowScale();

    // QLabel *nodeText;
    //QTextEdit* nodeTextEdit;  // 声明 QPlainTextEdit 对象，用于编辑选中节点的文本
    // QPushButton *saveButton;  // 声明 QPushButton 对象，用于保存选中节点的文本
    QGraphicsScene *scene;
    QHash<QString,node*> nodes;
    node* selectedNode;
};
#endif // _FRAMELESSWIDGETDEVELOPER_H
