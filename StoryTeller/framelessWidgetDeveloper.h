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
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QHash>
#include <QLabel>
#include <QTextEdit>
#include <QPushButton>
#include <QStackedWidget>
#include<qgraphicsitem.h>
#include<QList>
#include"attributenode.h"
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
    //void resizeEvent(QResizeEvent *event);

private slots:
    // 创建剧情节点
    void createStoryNode();
    // 增加子剧情节点
    void addChildNode();
    //增加选项节点
    void addChoiceNode();
    // 删除节点
    void deleteNode();
    // 读取选中节点
    void handleSelectionChanged();
    // 保存文本
    void saveNodeText();

    //全局属性编辑函数
    //增加属性
    void addAttribute();
    //删除属性
    void deleteAttribute();
    //选中属性
    void selectAttribute();


    //节点属性编辑函数
    //增加属性
    void addNodeAttribute();
    void on_clear_all_clicked();

    //删除属性
    void deleteNodeAttribute();
    //选中属性
    void selectNodeAttribute();
    //导入导出文件 一键清除
    void on_file_out_clicked();
    void on_file_in_clicked();
    void exportToFile(const QString& filename);
    void importFromFile(const QString& filename);
    void clearAllNodesAndAttributes();

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

    //节点显示界面
    QGraphicsScene *scene;
    //节点哈希表
    QHash<QString,node*> nodes;
    //选中节点
    node* selectedNode;

    //属性
    QHash<QString,int> attributes;

};
#endif // _FRAMELESSWIDGETDEVELOPER_H
