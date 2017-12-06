#include "baseclass.h"
#include <print.h>
#include <printfromui.h>
#include <serialport.h>

Base::Base(QObject *parent) : QObject(parent)
{

}

ClassParam &Base::getParam()
{
    return param;
}

QList<ClassParam> globalParam::allParams;

/**
 * @brief globalParam::init     注册类
 */
void globalParam::init()
{
    REGISTER_GCLASS(Print,"打印信息");
    REGISTER_GCLASS(PrintFromUI,"打印信息fromUI");
    REGISTER_GCLASS(Serialport,"串口");
}

