#ifndef ATTRIBUTENODE_H
#define ATTRIBUTENODE_H
#include<QString>

class attributeNode
{
public:
    attributeNode(QString n,int v);
    //属性名称
    QString name;
    //属性数值
    int value;

    void setValue(int v);
};

#endif // ATTRIBUTENODE_H
