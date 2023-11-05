#ifndef NODE_H
#define NODE_H
#include<QGraphicsEllipseItem>
#include<QGraphicsLineItem>
#include<QGraphicsScene>

class node : public QGraphicsEllipseItem
{
public:
    node(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;
    void setText(const QString& text);
    //子节点列表
    QVector<node*>childNodes;
    //父节点
    node *parentNode=nullptr;
    node* getParentNode() const {return parentNode;}
    bool isSelected() const;
    //和父节点的连接线
    QList<QGraphicsLineItem*>connectChildLines;
    //和子节点的连接线
    QList<QGraphicsLineItem*>connectParentLines;
    QString text;
    void updateConnectLines();
protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
signals:

};

#endif // NODE_H
