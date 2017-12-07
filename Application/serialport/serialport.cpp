#include "serialport.h"
#include <serialsetwidget.h>

Serialport::Serialport(QObject *parent) :
    Base(parent)
{
    setParam(&param);
}

/**
 * @brief exec      执行体
 * @param in
 * @param out
 */
void Serialport::exec(IN in, OUT out)
{

}

/**
 * @brief setParam      设置参数
 * @param param
 */
void Serialport::setParam(ClassParam *param)
{
//    param->infielddsc = QStringList()<<"请输入";
    param->object = this;
    param->InFieldtype = FIELD_TYPE::CUSTOM;
    param->outfielddsc = QStringList() << "数据";
    param->signalNames = QStringList()<<"sendfinished"<<"received";
    param->Signals = QStringList()<<SIGNAL(sendfinished())<<SIGNAL(received(IN,OUT));
    param->InCustomWidget = new SetWidget(new SerialSetWidget);
    param->slot = SLOT(exec(IN,OUT));
}
