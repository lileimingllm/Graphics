#include "printfromui.h"
#include <itemwindow.h>
#include <QDebug>

PrintFromUI::PrintFromUI(QObject * parent) :
    Base(parent)
{
    setParam(&param);
}

/**
 * @brief exec      执行函数
 * @param in
 * @param out
 */
void PrintFromUI::exec(IN in, OUT out)
{
    qDebug() << param.window->getInputs().at(0)->getField()->getFieldValue().toString();
    printFinished(out,in);
}

/**
 * @brief setParam      设置参数
 * @param param
 */
void PrintFromUI::setParam(ClassParam *param)
{
    param->infielddsc = QStringList()<<"请输入";
    param->object = this;
    param->InFieldtype = FIELD_TYPE::LINEEDIT;
    param->outfielddsc = QStringList() << "无输出";
    param->signalNames = QStringList()<<"printFinished";
    param->Signals = QStringList()<<SIGNAL(printFinished(IN,OUT));
    param->slot = SLOT(exec(IN,OUT));
}
