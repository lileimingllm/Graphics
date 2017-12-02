#include "print.h"
#include <QDebug>
#include <thread>
#include <chrono>
#include <itemwindow.h>
Print::Print(QObject *parent) :
    Base(parent)
{
    setParam(&param);
}


/**
 * @brief exec      执行函数
 * @param in
 * @param out
 */
void Print::exec(IN in, OUT out)
{
    if (in){
        for (QVariant v : *in){
            qDebug() << v.toString();
        }
    }
    param.window->getTitle()->setTitle("hello");
    IN i = out;
    OUT o = in;
    this_thread::sleep_for(chrono::milliseconds(200));
    emit printFinished(i, o);
}


/**
 * @brief setParam      获取类参数
 * @return
 */
void Print::setParam(ClassParam *param)
{
    param->className = "Print";
    param->infielddsc = QStringList()<<"输入打印";
    param->outfielddsc = QStringList()<<"无输出";
    param->object = this;
    param->signalNames = QStringList() <<"printFinished";
    param->Signals = QStringList()<<SIGNAL(printFinished(IN,OUT));
    param->slot = SLOT(exec(IN,OUT));

}

