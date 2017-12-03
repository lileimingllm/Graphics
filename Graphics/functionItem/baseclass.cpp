#include "baseclass.h"
#include <print.h>
#include <printfromui.h>

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
    REGISTER_GCLASS(Print,"Print");
    REGISTER_GCLASS(Print,"Print1");
    REGISTER_GCLASS(PrintFromUI,"PrintFromUI");
}

