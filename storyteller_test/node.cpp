#include "node.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

// 自定义构造函数，继承自QGraphicsEllipseItem
node::node(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : QGraphicsEllipseItem(x, y, width, height, parent)
{
    // 设置节点可移动和可选择
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

// 当图形项的选择状态发生变化时会调用这个函数
QVariant node::itemChange(GraphicsItemChange change, const QVariant &value)
{
    if (change == QGraphicsItem::ItemSelectedChange)
    {
        // 如果图形项被选中
        if (value.toBool())
        {
            // 设置填充颜色为灰色
            setBrush(QColor(Qt::gray));
        }
        else
        {
            if(type==1){
                // 设置填充颜色为白色
                setBrush(QColor(Qt::white));
            }
            else{
                //设置填充颜色为黑色
                setBrush(QColor(Qt::black));
            }

        }
    }
    return QGraphicsItem::itemChange(change, value);
}

// 鼠标按下事件
void node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // 调用父类的鼠标按下事件
    QGraphicsEllipseItem::mousePressEvent(event);
}

// 鼠标移动事件
void node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 调用父类的鼠标移动事件
    QGraphicsEllipseItem::mouseMoveEvent(event);
    // 更新连接线
    updateConnectLines();
}

// 获取节点是否被选中
bool node::isSelected() const
{
    return QGraphicsEllipseItem::isSelected();
}

// 更新连接线的位置
void node::updateConnectLines()
{
    for (auto line : connectChildLines)
    {
        line->setLine(pos().x() + rect().width() / 2, pos().y() + rect().height() / 2, line->line().x2(), line->line().y2());
    }
    for (auto line : connectParentLines)
    {
        line->setLine(line->line().x1(), line->line().y1(), pos().x() + rect().width() / 2, pos().y() + rect().height() / 2);
    }
}

//更新节点文本内容
void node::setText(const QString& text)
{
    // 在这里实现将节点文本设置为传入的文本内容的逻辑
    this->text=text;
}

//设置节点类型
void node::setType(int t){
    type=t;
    if(type==1){
        setBrush(QColor(Qt::white));
    }
    else{
        setBrush(QColor(Qt::black));
    }
}

//删除属性
void node::deleteNodeAttributes(QString name){
    nodeAttributes.remove(name);
}
