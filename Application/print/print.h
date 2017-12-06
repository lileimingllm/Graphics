#ifndef PRINT_H
#define PRINT_H
#include <baseclass.h>

/**
 * @brief The Print class       打印函数        必须继承BaseClass
 * @author 毛三
 */
class Print : public Base
{
    Q_OBJECT
public:
    Print(QObject * parent = nullptr);

public slots:
    /**
     * @brief exec      执行函数
     * @param in
     * @param out
     */
    void exec(IN in, OUT out);

public:
    /**
     * @brief setParam      获取类参数
     * @return
     */
    virtual void setParam(ClassParam * param);

signals:
    void printFinished(IN,OUT);
};

#endif // PRINT_H
