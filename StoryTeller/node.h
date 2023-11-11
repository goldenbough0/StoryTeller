#ifndef NODE_H
#define NODE_H
#include<QGraphicsEllipseItem>
#include<QGraphicsLineItem>
#include<QGraphicsScene>
#include <QFileDialog>
#include <QJsonDocument>
#include <QJsonArray>
#include <QJsonObject>


class node : public QGraphicsEllipseItem
{
public:
    node(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent = nullptr);
    void mousePressEvent(QGraphicsSceneMouseEvent *event) override;
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event) override;

    //子节点列表
    QVector<node*>childNodes;
    //父节点
    node *parentNode=nullptr;
    //获取父节点
    node* getParentNode() const {return parentNode;}

    //是否被选中
    bool isSelected() const;

    //和父节点的连接线
    QList<QGraphicsLineItem*>connectChildLines;
    //和子节点的连接线
    QList<QGraphicsLineItem*>connectParentLines;
    //更新连接线
    void updateConnectLines();

    //文本内容
    QString text;
    //设置文本内容
    void setText(const QString& text);

    //节点类型
    int type;//1为剧情节点，2为选项节点
    //设置节点类型
    void setType(int t);

    //属性
    QHash<QString,int> nodeAttributes;
    //删除属性
    void deleteNodeAttributes(QString name);

    //改了*************************************************
    QJsonObject exportNode() const;

protected:
    QVariant itemChange(GraphicsItemChange change, const QVariant &value) override;
signals:

};

#endif // NODE_H
