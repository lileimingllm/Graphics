#ifndef SERIALPORT_H
#define SERIALPORT_H

#include<baseclass.h>
#include<setwidget.h>

/**
 * @brief The Serialport class      串口
 * @author 毛三
 */
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
public:
    /**
     * @brief setParam      设置参数
     * @param param
     */
    void setParam(ClassParam* param);

signals:
    /**
     * @brief sendfinished      当数据送成功时，emit此信号
     */
    void sendfinished();

    /**
     * @brief received      当接收到数据的时候，发送此信号
     */
    void received(IN,OUT);
};
#endif // SERIALPORT_H
