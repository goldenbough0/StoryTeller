#include "node.h"
#include <QGraphicsSceneMouseEvent>
#include <QPainter>
#include <QDebug>

// 自定义构造函数，继承自QGraphicsEllipseItem
Node::Node(qreal x, qreal y, qreal width, qreal height, QGraphicsItem *parent) : QGraphicsEllipseItem(x, y, width, height, parent)
{
    // 设置节点可移动和可选择
    setFlag(QGraphicsItem::ItemIsMovable);
    setFlag(QGraphicsItem::ItemIsSelectable, true);
}

// 当图形项的选择状态发生变化时会调用这个函数
QVariant Node::itemChange(GraphicsItemChange change, const QVariant &value)
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
            // 设置填充颜色为白色
            setBrush(QColor(Qt::white));
        }
    }
    return QGraphicsItem::itemChange(change, value);
}

// 鼠标按下事件
void Node::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    // 调用父类的鼠标按下事件
    QGraphicsEllipseItem::mousePressEvent(event);
}

// 鼠标移动事件
void Node::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    // 调用父类的鼠标移动事件
    QGraphicsEllipseItem::mouseMoveEvent(event);
    // 更新连接线
    updateConnectLines();
}

// 获取节点是否被选中
bool Node::isSelected() const
{
    return QGraphicsEllipseItem::isSelected();
}

// 更新连接线的位置
void Node::updateConnectLines()
{
    for (auto line : connectParentLines)
    {
        line->setLine(pos().x() + rect().width() / 2, pos().y() + rect().height() / 2, line->line().x2(), line->line().y2());
    }
    for (auto line : connectChildLines)
    {
        line->setLine(line->line().x1(), line->line().y1(), pos().x() + rect().width() / 2, pos().y() + rect().height() / 2);
    }
}

//更新节点文本内容
void Node::setText(const QString& text)
{
    // 在这里实现将节点文本设置为传入的文本内容的逻辑
    this->text=text;
}
