#ifndef NODE_H
#define NODE_H
#include<QGraphicsEllipseItem>
#include<QGraphicsLineItem>
#include<QGraphicsScene>
#include<choicenode.h>
class Node : public QGraphicsEllipseItem
{
public:
    Node(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    //剧情文本
    QString text;
    //索引
    int index;

    //设置文本
    void setText(const QString& text);
    //设置索引
    void setIndex(const int& index);

    //子节点哈希表
    QHash<QString, Node*>childNodes;
    //父节点
    Node *parentNode=nullptr;
    Node* getParentNode() const {return parentNode;}
    bool isSelected() const;


    //和父节点的连接线
    QList<QGraphicsLineItem*>connectParentLines;
    //和子节点的连接线
    QList<QGraphicsLineItem*>connectChildLines;
    //更新连接线
    void updateConnectLines();



protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
signals:

};

#endif // NODE_H
