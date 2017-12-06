#ifndef SERIALPORT_H
#define SERIALPORT_H

#include<baseclass.h>

class Serialport : public Base
{
    Q_OBJECT
public:
    Serialport(QObject* parent=nullptr);

public slots:
    /**
     * @brief exec      执行体
     * @param in
     * @param out
     */
    void exec(IN in, OUT out);

    /**
     * @brief setParam      设置参数
     * @param param
     */
    void setParam(ClassParam* param);
};

#endif // SERIALPORT_H
