#include "serialport.h"

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

}
