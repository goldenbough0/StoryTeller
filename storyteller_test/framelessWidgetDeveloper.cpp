#include "framelessWidgetDeveloper.h"
#include "ui_framelessWidgetDeveloper.h"
#include <QMessageBox>
#include <QRandomGenerator>
#include<QDebug>

int NodeNum=0;  // 定义一个全局变量 NodeNum，用于记录节点数量

framelessWidgetDeveloper::framelessWidgetDeveloper(QWidget *parent)
    : QWidget(parent)
    , scene(new QGraphicsScene(this)),selectedNode(nullptr),ui(new Ui::framelessWidgetDeveloper)
{
    ui->setupUi(this);
    ui->mainWidget->setMouseTracking(true); // 允许鼠标跟踪
    ui->mainDisplayWidget->setMouseTracking(true);
    setMouseTracking(true);

    //设置按钮颜色

    ui->new_story->setForegroundColor(QColor("#5ac2c6"));
    ui->new_story->setOverlayColor(QColor("#5ac2c6"));

    ui->new_childstory->setForegroundColor(QColor("#5ac2c6"));
    ui->new_childstory->setOverlayColor(QColor("#5ac2c6"));

    ui->new_choice->setForegroundColor(QColor("#5ac2c6"));
    ui->new_choice->setOverlayColor(QColor("#5ac2c6"));

    ui->new_delete->setForegroundColor(QColor("#5ac2c6"));
    ui->new_delete->setOverlayColor(QColor("##5ac2c6"));




    connect(ui->Button_max, &QPushButton::clicked, this, [=]()  // 点击最大化按钮
    {
        controlWindowScale();
    });
    connect(ui->Button_min, &QPushButton::clicked, this,[=]()   // 点击最小化按钮
    {
        this->showMinimized();
    });
    connect(ui->Button_close,&QPushButton::clicked, this,[=]()  // 点击关闭按钮
    {
        this->close();
    });

    //设置绘图窗口

    //scene = new QGraphicsScene(this);
    ui->graphicsView->setScene(scene);
    ui->graphicsView->show();
    connect(scene,&QGraphicsScene::selectionChanged,this,&framelessWidgetDeveloper::handleSelectionChanged);  // 连接 graphics scene 的 selectionChanged 信号和 handleSelectionChanged 槽

    //连接按钮与函数
    connect(ui->new_story,&QPushButton::clicked,this,&framelessWidgetDeveloper::createStoryNode);  // 连接新建节点按钮的 clicked 信号和 createNode 槽
    connect(ui->new_childstory,&QPushButton::clicked,this,&framelessWidgetDeveloper::addChildNode);  // 连接增加子节点按钮的 clicked 信号和 addChildNode 槽
    connect(ui->new_delete,&QPushButton::clicked,this,&framelessWidgetDeveloper::deleteNode);  // 连接删除节点按钮的 clicked 信号和 deleteNode 槽
    connect(ui->new_choice,&QPushButton::clicked,this,&framelessWidgetDeveloper::addAttributeNode);
    //设置文本内容编辑功能

    connect(ui->save_text_button, &QPushButton::clicked, this, &framelessWidgetDeveloper::saveNodeText);

}

framelessWidgetDeveloper::~framelessWidgetDeveloper()
{
    delete ui;
}

// 鼠标按下事件(记录拉伸窗口或移动窗口时的起始坐标（左上角）)
void framelessWidgetDeveloper::mousePressEvent(QMouseEvent *event)
{
    if(event->button() == Qt::LeftButton){
        mousePressed = true;
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        lastPos = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
#else
        lastPos = event->globalPos() - this->frameGeometry().topLeft();
#endif
    }
}

// 鼠标移动事件
void framelessWidgetDeveloper::mouseMoveEvent(QMouseEvent *event)
{
    if(event->buttons() == Qt::NoButton)
        mousePressed = false;
    if(!mousePressed){ // 鼠标没按下移动，更新鼠标位置状态
        mouseState = 0;
        if(!maximized && abs(event->pos().x() - ui->mainWidget->pos().x()) < 5)
            mouseState |= AT_LEFT;
        if(!maximized && abs(event->pos().y() - ui->mainWidget->pos().y()) < 5)
            mouseState |= AT_TOP;
        if(!maximized && abs(event->pos().x() - ui->mainWidget->pos().x() - ui->mainWidget->width()) < 5)
            mouseState |= AT_RIGHT;
        if(!maximized && abs(event->pos().y() - ui->mainWidget->pos().y() - ui->mainWidget->height()) < 5)
            mouseState |= AT_BOTTOM;
        if(mouseState == AT_TOP_LEFT  || mouseState == AT_BOTTOM_RIGHT)
            setCursor(Qt::SizeFDiagCursor);
        else if(mouseState == AT_TOP_RIGHT || mouseState == AT_BOTTOM_LEFT)
            setCursor(Qt::SizeBDiagCursor);
        else if(mouseState & (AT_LEFT | AT_RIGHT))
            setCursor(Qt::SizeHorCursor);
        else if(mouseState & (AT_TOP | AT_BOTTOM))
            setCursor(Qt::SizeVerCursor);
        else
            unsetCursor();
    }
    else{ //鼠标按下移动
        if(mouseState == 0){
            if(maximized){
                qreal wRatio = (double)event->pos().x() / (double)ui->mainWidget->width();
                controlWindowScale();
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
                this->move(QPoint(event->globalPosition().x() - ui->mainWidget->width() * wRatio, -30));
#else
                this->move(QPoint(event->globalPos().x() - ui->mainWidget->width() * wRatio, -30));
#endif
                lastPos = QPoint(ui->mainWidget->width() * wRatio, event->pos().y());
            }
            else
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
                this->move(event->globalPosition().toPoint() - lastPos);
#else
                this->move(event->globalPos() - lastPos);
#endif
        }
        else{
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
            QPoint d = event->globalPosition().toPoint() - frameGeometry().topLeft() - lastPos;
#else
            QPoint d = event->globalPos() - frameGeometry().topLeft() - lastPos;
#endif
            if(mouseState & AT_LEFT){
                this->move(this->frameGeometry().x() + d.x(), this->frameGeometry().y());
                this->resize(this->width() - d.x(), this->height());
            }
            if(mouseState & AT_RIGHT){
                this->resize(this->width() + d.x(), this->height());
            }
            if(mouseState & AT_TOP){
                this->move(this->frameGeometry().x(), this->frameGeometry().y() + d.y());
                this->resize(this->width(), this->height() - d.y());
            }
            if(mouseState & AT_BOTTOM){
                this->resize(this->width(), this->height() + d.y());
            }
        }
#if (QT_VERSION >= QT_VERSION_CHECK(6,0,0))
        lastPos = event->globalPosition().toPoint() - this->frameGeometry().topLeft();
#else
        lastPos = event->globalPos() - this->frameGeometry().topLeft();
#endif
    }
}


//点击最大化按钮事件
void framelessWidgetDeveloper::controlWindowScale(){
#ifdef Q_OS_WINDOWS
    if(!maximized){
        lastGeometry = this->frameGeometry();
      //  windowShadow->setEnabled(false);
        ui->verticalLayout->setContentsMargins(0, 0, 0, 0);
        //border->hide();
        QString mainStyle = "QWidget#mainWidget{background-color:rgb(251,251,251) border-radius:0px;}";
        ui->mainWidget->setStyleSheet(mainStyle);
        this->showMaximized();
        maximized = true;
    }
    else{
        ui->verticalLayout->setContentsMargins(30, 30, 30, 30);
        this->showNormal();
        QString mainStyle = "QWidget#mainWidget{background-color:rgb(251,251,251)" + QString::asprintf(";border-radius:%dpx", cornerRadius) + "}";
        ui->mainWidget->setStyleSheet(mainStyle);

        this->resize(lastGeometry.width(), lastGeometry.height());
        this->move(lastGeometry.x(), lastGeometry.y());
        maximized = false;
    }
#endif
}

// 创建剧情节点的槽函数
void framelessWidgetDeveloper::createStoryNode()
{
    //初始化节点
    node *n = new node(0,0,50,50);
    //设置节点类型为剧情节点
    n->setType(1);
    // 设置随机坐标
    int x = QRandomGenerator::global()->bounded(scene->width());
    int y = QRandomGenerator::global()->bounded(scene->height());
    n->setPos(QPointF(x, y));
    //qDebug() << "node_n is valid: " << (n != nullptr);
    scene->addItem(n);  // 将节点添加到场景中
    ui->graphicsView->update();
    NodeNum=NodeNum+1;  // 节点数量加一
    QString nodeIndex = "Node" + QString::number(NodeNum);  // 生成节点索引
    nodes.insert(nodeIndex,n);  // 将节点添加到 nodes 容器中

}

// 添加子剧情节点的槽函数
void framelessWidgetDeveloper::addChildNode()
{
    if(selectedNode)  // 如果已经选择了一个父节点
    {
        node *childNode = new node(0,0,50,50);  // 创建子节点对象
        childNode->setType(1);//设置子节点为剧情节点。
        qreal ySpace = selectedNode->childNodes.size()*60;  // 计算子节点与父节点在 y 方向上的间距
        childNode->setPos(selectedNode->pos()+QPointF(150,ySpace));  // 设置子节点的位置
        scene->addItem(childNode);  // 将子节点添加到场景中
        NodeNum=NodeNum+1;
        QString childNodeIndex = "ChildNode" + QString::number(NodeNum);  // 生成子节点索引
        selectedNode->childNodes.append(childNode);  // 将子节点添加到选定节点的子节点链表中
        nodes.insert(childNodeIndex,childNode);  // 将子节点添加到 nodes 容器中

        QGraphicsLineItem *line = new QGraphicsLineItem(selectedNode->pos().x()+selectedNode->rect().width()/2,
                                                        selectedNode->pos().y()+selectedNode->rect().height()/2,
                                                        childNode->pos().x()+childNode->rect().width()/2,
                                                        childNode->pos().y()+childNode->rect().height()/2);  // 创建连接父节点和子节点的线
        scene->addItem(line);  // 将线添加到场景中
        selectedNode->connectChildLines.append(line);  // 将该线添加到选定节点的连接子节点的线链表中
        childNode->connectParentLines.append(line);  // 将该线添加到子节点的连接父节点的线链表中
        childNode->parentNode = selectedNode;  // 设置子节点的父节点为选定节点
    }
    else  // 如果没有选择父节点
    {
        QMessageBox::information(this,"warning","请先选择一个节点作为父节点");  // 弹出警告对话框
    }
}

// 添加选项节点的槽函数
void framelessWidgetDeveloper::addAttributeNode()
{
    if(selectedNode)  // 如果已经选择了一个父节点
    {
        node *childNode = new node(0,0,50,50);  // 创建子节点对象
        childNode->setType(2);//设置节点类型为选项
        qreal ySpace = selectedNode->childNodes.size()*60;  // 计算子节点与父节点在 y 方向上的间距
        childNode->setPos(selectedNode->pos()+QPointF(150,ySpace));  // 设置子节点的位置
        scene->addItem(childNode);  // 将子节点添加到场景中
        NodeNum=NodeNum+1;
        QString childNodeIndex = "ChildNode" + QString::number(NodeNum);  // 生成子节点索引
        selectedNode->childNodes.append(childNode);  // 将子节点添加到选定节点的子节点链表中
        nodes.insert(childNodeIndex,childNode);  // 将子节点添加到 nodes 容器中

        QGraphicsLineItem *line = new QGraphicsLineItem(selectedNode->pos().x()+selectedNode->rect().width()/2,
                                                        selectedNode->pos().y()+selectedNode->rect().height()/2,
                                                        childNode->pos().x()+childNode->rect().width()/2,
                                                        childNode->pos().y()+childNode->rect().height()/2);  // 创建连接父节点和子节点的线
        scene->addItem(line);  // 将线添加到场景中
        selectedNode->connectChildLines.append(line);  // 将该线添加到选定节点的连接子节点的线链表中
        childNode->connectParentLines.append(line);  // 将该线添加到子节点的连接父节点的线链表中
        childNode->parentNode = selectedNode;  // 设置子节点的父节点为选定节点
    }
    else  // 如果没有选择父节点
    {
        QMessageBox::information(this,"warning","请先选择一个节点作为父节点");  // 弹出警告对话框
    }
}

void framelessWidgetDeveloper::deleteNode()  // 删除节点的槽函数
{
    if(selectedNode)  // 如果已经选择了一个节点
    {


        if(selectedNode->childNodes.empty()){
            if (selectedNode->parentNode) {  // 如果选定节点有父节点
                selectedNode->parentNode->childNodes.removeOne(selectedNode);  // 将选定节点从其父节点的子节点链表中移除
                for (QGraphicsLineItem *line : selectedNode->connectParentLines) {  // 遍历选定节点连接父节点的线链表

                    selectedNode->parentNode->connectChildLines.removeOne(line);//从父节点连接子节点的链表中删除该线
                    selectedNode->connectParentLines.removeOne(line);//从子节点连接父节点的链表中删除该线
                    scene->removeItem(line);  // 从场景中删除该线
                    delete line;  // 删除该线的内存
                }

            }

            QString nodeIndex = nodes.key(selectedNode);  // 获取选定节点在 nodes 容器中的索引
            nodes.remove(nodeIndex);  // 从 nodes 容器中删除选定节点

            scene->removeItem(selectedNode);  // 从场景中删除选定节点
            delete selectedNode;  // 删除选定节点的内存

            selectedNode = nullptr;  // 将 selectedNode 变量重置为空指针
        }
        else{
            QMessageBox::information(this,"warning","请选择没有子节点的节点");  // 弹出警告对话框
        }
    }
    else  // 如果没有选择节点
    {
        QMessageBox::information(this,"warning","请先选择一个节点");  // 弹出警告对话框
    }
}

void framelessWidgetDeveloper::handleSelectionChanged()
{
    QList<QGraphicsItem*> items = scene->selectedItems();
    if (items.size() == 1) {
        node *n = static_cast<node*>(items.first());
        selectedNode = n;
        // 将选中节点的文本内容设置到 QTextEdit 中
        QString text = n->text;
        ui->node_text_Edit->setText(text);




    } else {
        selectedNode = nullptr;
        ui->node_text_Edit->clear();
    }
}

void framelessWidgetDeveloper::saveNodeText()
{
    if (selectedNode != nullptr) {
        selectedNode->setText(ui->node_text_Edit->toPlainText());
        // 更新选中节点的文本标签显示
    }
}

void framelessWidgetDeveloper::handleNodeSelected(node(* selectedNode))  // 处理选中节点
{
    this->selectedNode = selectedNode;  // 将选定节点设置为成员变量 selectedNode
}


void framelessWidgetDeveloper::resizeEvent(QResizeEvent *event)
{
    QSize mainWindowSize = size();
    int width = mainWindowSize.width(); // 获取主窗口当前宽度
    int height = mainWindowSize.height(); // 获取主窗口当前高度
    // 进行窗口大小变化后的相关操作
    ui->node_text_Edit->setFixedHeight(height/4);
}

