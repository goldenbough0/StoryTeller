#ifndef MYELLIPSEITEM_H
#define MYELLIPSEITEM_H
#include<QGraphicsEllipseItem>
#include<QGraphicsLineItem>
#include<QGraphicsScene>

class StoryNode : public QGraphicsEllipseItem
{
public:
    StoryNode(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void setText(const QString& text);
    //子节点哈希表
    QHash<QString, StoryNode*>childNodes;
    //父节点
    StoryNode *parentNode=nullptr;
    StoryNode* getParentNode() const {return parentNode;}
    bool isSelected() const;
    //和父节点的连接线
    QList<QGraphicsLineItem*>connectParentLines;
    //和子节点的连接线
    QList<QGraphicsLineItem*>connectChildLines;
    QString text;
    void updateConnectLines();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
signals:

};

#endif // MYELLIPSEITEM_H
