#ifndef DEVELOPER_H
#define DEVELOPER_H
#include"myellipseitem.h"
#include <QMainWindow>
#include <QGraphicsScene>
#include <QGraphicsEllipseItem>
#include <QHash>
#include<QLabel>
#include<QPlainTextEdit>
#include<QPushButton>
class Developer : public QMainWindow
{
    Q_OBJECT
public:
    explicit Developer(QWidget *parent = nullptr);
    void handleNodeSelected(StoryNode* selectedNode);
    void resizeEvent(QResizeEvent *event);
private slots:
    //创建节点
    void createNode();
    //增加子节点
    void addChildNode();
    //删除节点
    void deleteNode();
    //读取选中节点
    void handleSelectionChanged();
    //保存文本
    void saveNodeText();
private:
    //QLabel *nodeText;
    QPlainTextEdit* nodeTextEdit;  // 声明 QPlainTextEdit 对象，用于编辑选中节点的文本
    QPushButton *saveButton;  // 声明 QPushButton 对象，用于保存选中节点的文本
    QGraphicsScene *scene;
    QHash<QString,StoryNode*> nodes;
    StoryNode* selectedNode;
signals:

};

#endif // DEVELOPER_H
