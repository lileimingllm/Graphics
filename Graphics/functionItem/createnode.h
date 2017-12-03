#ifndef CREATENODE_H
#define CREATENODE_H
#include <QObject>
#include <itemwindow.h>
#include <inputoutputitem.h>



class CreateNode
{
public:
    /**
     * @brief CreateNode        构造器,创造一个ITEMWIDGET
     * @param functionName
     * @param type
     */
    static ItemWindow* create(ClassParam param);

private:
};

#endif // CREATENODE_H
