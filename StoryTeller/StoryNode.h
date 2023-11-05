#ifndef STORYNODE_H
#define STORYNODE_H
#include<QGraphicsEllipseItem>
#include<QGraphicsLineItem>
#include<QGraphicsScene>
#include<choicenode.h>
#include<node.h>

class StoryNode : public Node
{
public:
    StoryNode(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
signals:

};

#endif // STORYNODE_H
