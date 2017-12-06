#ifndef PRINTFROMUI_H
#define PRINTFROMUI_H
#include <baseclass.h>

class PrintFromUI : public Base
{
    Q_OBJECT
public:
    PrintFromUI(QObject *parent = nullptr);

public slots:
    /**
     * @brief exec      执行函数
     * @param in
     * @param out
     */
    void exec(IN in, OUT out);

    /**
     * @brief setParam      设置参数
     * @param param
     */
    void setParam(ClassParam *param);
signals:
    void printFinished(IN,OUT);
};

#endif // PRINTFROMUI_H
