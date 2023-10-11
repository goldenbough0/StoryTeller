#include "developer.h"
#include "myellipseitem.h"
#include <QGraphicsView>
#include <QGraphicsEllipseItem>
#include <QVBoxLayout>
#include <QPushButton>
#include <QDebug>
#include <QMessageBox>

int NodeNum=0;  // 定义一个全局变量 NodeNum，用于记录节点数量

Developer::Developer(QWidget *parent) : QMainWindow(parent),scene(new QGraphicsScene(this)),selectedNode(nullptr)
{
    this->resize(800,600);  // 设置主窗口的大小为 800*600
    QGraphicsView *view = new QGraphicsView(scene);  // 创建 QGraphicsView 对象，用于显示 scene 中的图形项
    view->resize(800,600);
    connect(scene,&QGraphicsScene::selectionChanged,this,&Developer::handleSelectionChanged);  // 连接 graphics scene 的 selectionChanged 信号和 handleSelectionChanged 槽
    QPushButton *btn1 = new QPushButton("新建节点",this);  // 创建 QPushButton 对象，用于新建节点
    btn1->setFixedSize(100,30);  // 设置按钮的大小为 100*30
    QPushButton *btn2 = new QPushButton("增加子节点",this);  // 创建 QPushButton 对象，用于增加子节点
    btn2->setFixedSize(100,30);  // 设置按钮的大小为 100*30
    QPushButton *btn3 = new QPushButton("删除节点",this);  // 创建 QPushButton 对象，用于删除节点
    btn3->setFixedSize(100,30);  // 设置按钮的大小为 100*30
    connect(btn1,&QPushButton::clicked,this,&Developer::createNode);  // 连接新建节点按钮的 clicked 信号和 createNode 槽
    QHBoxLayout *buttonLayout = new QHBoxLayout;  // 创建水平布局对象
    connect(btn2,&QPushButton::clicked,this,&Developer::addChildNode);  // 连接增加子节点按钮的 clicked 信号和 addChildNode 槽
    connect(btn3,&QPushButton::clicked,this,&Developer::deleteNode);  // 连接删除节点按钮的 clicked 信号和 deleteNode 槽
    buttonLayout->addWidget(btn1);  // 将新建节点按钮添加到水平布局中
    buttonLayout->addWidget(btn2);  // 将增加子节点按钮添加到水平布局中
    buttonLayout->addWidget(btn3);  // 将删除节点按钮添加到水平布局中
    buttonLayout->setAlignment(Qt::AlignLeft);  // 设置水平布局中的对齐方式为左对齐

//    nodeText = new QLabel(this);  // 创建 QLabel 对象，用于显示选中节点的文本
//    nodeText->setAlignment(Qt::AlignCenter);  // 设置文本居中对齐
//    nodeText->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding); // 设置大小策略
//    nodeText->setMaximumWidth(800); // 设置最大宽度
//    nodeText->setWordWrap(true); // 设置自动换行


    nodeTextEdit = new QPlainTextEdit(this);  // 创建 QLineEdit 对象，用于编辑选中节点的文本
    //nodeTextEdit->setFixedHeight(height/3);


    saveButton = new QPushButton("保存", this);  // 创建 QPushButton 对象，用于保存选中节点的文本
    saveButton->setFixedSize(100,30);
    connect(saveButton, &QPushButton::clicked, this, &Developer::saveNodeText);

    QHBoxLayout *rightLayout = new QHBoxLayout;  // 创建水平布局对象
    //rightLayout->addWidget(view);  // 将 QGraphicsView 添加到右侧水平布局

    QVBoxLayout *textLayout = new QVBoxLayout;  // 创建垂直布局对象，用于添加节点文本编辑框和保存按钮
    textLayout->addWidget(nodeTextEdit);  // 将 文本编辑框 添加到垂直布局
    textLayout->addWidget(saveButton);// 将 保存按钮 添加到垂直布局
    //textLayout->addWidget(nodeText);//将文本显示框添加到textLayout
    rightLayout->addLayout(textLayout);  // 将垂直布局添加到右侧水平布局

    QVBoxLayout *layout = new QVBoxLayout;  // 创建垂直布局对象
    layout->addLayout(buttonLayout);  // 将水平布局添加到垂直布局中

    layout->addLayout(rightLayout);  // 将右侧水平布局添加到垂直布局中


    layout->addWidget(view);  // 将 QGraphicsView 对象添加到垂直布局中
    QWidget *container = new QWidget;  // 创建 QWidget 对象，用于容纳垂直布局
    container->setLayout(layout);  // 将垂直布局设置为 QWidget 的布局
    setCentralWidget(container);  // 将 QWidget 设置为主窗口的中心窗口部件

}

void Developer::createNode()  // 创建节点的槽函数
{
    StoryNode *node = new StoryNode(0,0,50,50);  // 创建 StoryNode 对象，用于表示故事节点
    node->setPos(QPointF(qrand()%300,qrand()%300));  // 设置节点位置
    scene->addItem(node);  // 将节点添加到场景中
    NodeNum=NodeNum+1;  // 节点数量加一
    QString nodeIndex = "Node" + QString::number(NodeNum);  // 生成节点索引
    node->parentNode = nullptr;  // 设置初始节点的父节点为空
    nodes.insert(nodeIndex,node);  // 将节点添加到 nodes 容器中
}

void Developer::addChildNode()  // 添加子节点的槽函数
{
    if(selectedNode)  // 如果已经选择了一个父节点
    {
        StoryNode *childNode = new StoryNode(0,0,50,50);  // 创建子节点对象
        qreal ySpace = selectedNode->childNodes.size()*60;  // 计算子节点与父节点在 y 方向上的间距
        childNode->setPos(selectedNode->pos()+QPointF(150,ySpace));  // 设置子节点的位置
        childNode->parentNode = selectedNode;  // 设置添加的子节点的父节点为当前选中节点
        scene->addItem(childNode);  // 将子节点添加到场景中
        NodeNum=NodeNum+1;
        QString childNodeIndex = "ChildNode" + QString::number(NodeNum);  // 生成子节点索引
        selectedNode->childNodes.insert(childNodeIndex, childNode);  // 将子节点添加到选定节点的子节点哈希表中
        nodes.insert(childNodeIndex,childNode);  // 将子节点添加到 nodes 容器中

        QGraphicsLineItem *line = new QGraphicsLineItem(selectedNode->pos().x()+selectedNode->rect().width()/2,
                                                        selectedNode->pos().y()+selectedNode->rect().height()/2,
                                                        childNode->pos().x()+childNode->rect().width()/2,
                                                        childNode->pos().y()+childNode->rect().height()/2);  // 创建连接父节点和子节点的线
        scene->addItem(line);  // 将线添加到场景中
        selectedNode->connectParentLines.append(line);  // 将该线添加到选定节点的连接父节点的线链表中
        childNode->connectChildLines.append(line);  // 将该线添加到子节点的连接子节点的线链表中
        childNode->parentNode = selectedNode;  // 设置子节点的父节点为选定节点
    }
    else  // 如果没有选择父节点
    {
        QMessageBox::information(this,"warning","请先选择一个节点作为父节点");  // 弹出警告对话框
    }
}
void Developer::deleteNode()
{
    QList<QGraphicsLineItem*> linesToRemove;
    if (selectedNode)  // 判断当前是否有节点被选中
    {
        QString nodeIndex = nodes.key(selectedNode);  // 获取当前选中节点的索引
        // qDebug()<<"deleted node:"<<selectedNode;   // 调试信息
        if (selectedNode->parentNode)  // 若当前选中节点有父节点
        {
            // qDebug()<<"parent node:"<<selectedNode->parentNode;  // 调试信息
            // 删除连接线
            for (QGraphicsLineItem *line : selectedNode->connectParentLines) {  // 遍历选定节点作为父节点的连线链表
                // qDebug()<<"removed parentLine";  // 调试信息
                scene->removeItem(line);  // 从场景中删除该线
                linesToRemove.append(line);  // 存储该线到等待被移除的线的列表中
            }

            for (QGraphicsLineItem *line : selectedNode->connectChildLines) {  // 遍历选定节点作为子节点的连线列表
                // qDebug()<<"removed childLine";  // 调试信息
                scene->removeItem(line);  // 从场景中删除该线
                linesToRemove.append(line);  // 存储该线到等待被移除的线的列表中
            }

            // 删除连接线
            for (QGraphicsLineItem *line : linesToRemove) {  // 进行线的移除
                // qDebug()<<"remove linesToRemove";  // 调试信息
                selectedNode->connectParentLines.removeOne(line);
                selectedNode->connectChildLines.removeOne(line);
                selectedNode->parentNode->connectParentLines.removeOne(line);  // 为避免悬空指针等导致程序异常结束，需移除当前节点的所有连接线
                delete line;  // 删除该线的内存
            }
            for (StoryNode* childNode:selectedNode->childNodes)  // 遍历当前节点的子节点
            {
                childNode->parentNode = nullptr;  // 设置子节点的父节点为空
            }
            // 从父节点的子节点哈希表中删除节点
            selectedNode->parentNode->childNodes.remove(nodeIndex);
            selectedNode->parentNode = nullptr;
        }
        // 当前节点的父节点为空的情况
       if (!selectedNode->childNodes.isEmpty())  // 若当前节点有子节点
       {
           for (QGraphicsLineItem *line : selectedNode->connectParentLines)  // 删除线
                {
                     scene->removeItem(line);
                     delete line;
                }
           for (StoryNode* childNode:selectedNode->childNodes)
           {
               childNode->parentNode = nullptr;
           }
       }
        // 从场景中移除节点
        scene->removeItem(selectedNode);
        delete selectedNode;
        nodes.remove(nodeIndex);

        qDebug() << "Node removed:" << nodeIndex;
        selectedNode = nullptr;
    }
    else
    {
        QMessageBox::information(this, "warning", "请先选择一个节点");  // 未选择节点，弹出提示信息
    }
}
//void Developer::deleteNode()  // 删除节点的槽函数
//{
//    if(selectedNode)  // 如果已经选择了一个节点
//    {


//        if(selectedNode->childNodes.empty()){
//            if (selectedNode->parentNode) {  // 如果选定节点有父节点
//                selectedNode->parentNode->childNodes.removeOne(selectedNode);  // 将选定节点从其父节点的子节点链表中移除

//                for (QGraphicsLineItem *line : selectedNode->connectParentLines) {  // 遍历选定节点连接父节点的线链表
//                    scene->removeItem(line);  // 从场景中删除该线
//                    delete line;  // 删除该线的内存
//                }

//                for (QGraphicsLineItem *line : selectedNode->connectChildLines) {  // 遍历选定节点连接子节点的线链表
//                    scene->removeItem(line);  // 从场景中删除该线
//                    delete line;  // 删除该线的内存
//                }
//            }

//            scene->removeItem(selectedNode);  // 从场景中删除选定节点
//            delete selectedNode;  // 删除选定节点的内存

//            QString nodeIndex = nodes.key(selectedNode);  // 获取选定节点在 nodes 容器中的索引
//            nodes.remove(nodeIndex);  // 从 nodes 容器中删除选定节点

//            selectedNode = nullptr;  // 将 selectedNode 变量重置为空指针
//        }
//        else{
//            QMessageBox::information(this,"warning","请选择没有子节点的节点");  // 弹出警告对话框
//        }
//    }
//    else  // 如果没有选择节点
//    {
//        QMessageBox::information(this,"warning","请先选择一个节点");  // 弹出警告对话框
//    }
//}

void Developer::handleSelectionChanged()
{
    QList<QGraphicsItem*> items = scene->selectedItems();
    if (items.size() == 1) {
        StoryNode *node = static_cast<StoryNode*>(items.first());
        selectedNode = node;
        QString text = node->text;
        nodeTextEdit->setPlainText(text);// 将选中节点的文本内容设置到 QPlainLineEdit 中

        //nodeText->setText(text);  // 将选中节点的文本显示在 QLabel 中

    } else {
        selectedNode = nullptr;
        nodeTextEdit->clear();
        //nodeText->setText("");
    }
}

void Developer::saveNodeText()
{
    if (selectedNode != nullptr) {
        selectedNode->setText(nodeTextEdit->toPlainText());
        //nodeText->setText(nodeTextEdit->toPlainText());  // 更新选中节点的文本标签显示
    }
}

void Developer::handleNodeSelected(StoryNode(* selectedNode))  // 处理选中节点
{
    this->selectedNode = selectedNode;  // 将选定节点设置为成员变量 selectedNode
}


void Developer::resizeEvent(QResizeEvent *event)
{
    QSize mainWindowSize = size();
    int width = mainWindowSize.width(); // 获取主窗口当前宽度
    int height = mainWindowSize.height(); // 获取主窗口当前高度
    // 进行窗口大小变化后的相关操作
    nodeTextEdit->setFixedHeight(height/4);
}
