#ifndef DATAFILTER_H
#define DATAFILTER_H

#include <QObject>
#include <baseclass.h>

/**
 * @brief The Regulation enum      规则类型
 */
enum class Regulation{
    REGULAR,        //正则匹配
    INCLUDE,        //包含匹配
    LENGTH,         //长度匹配
    CALCULATEMATCH, //计算匹配
    CALCULATE,      //只计算，然后返回
};

/**
 * @brief The ReturnType enum       匹配成功返回类型
 */
enum class ReturnType {
    RAW,        //源
    VALUE,      //过滤后的值（比如：在CALCULATE匹配中，返回计算后的值）
};

/**
 * @brief The FilterRegular struct      过滤设置
 */
struct FilterRegular
{
    Regulation regular{Regulation::LENGTH};     //过滤规则
    ReturnType type{ReturnType::RAW};           //返回类型
    bool hasSignal{false};                      //匹配成功是否有信号
    QList<QString> match;                       /*匹配规则，如果是REGULAR(字符串)、INCLUDE（字符）、LENGTH，
                                                  则填对应值的toString，CALCULATEMATCH是"参数1的下标:运算符:参数2:=:值"
                                                  如果是CALCULATE，
                                                  依次填入“参数1的下标:运算符:参数2的下标:运算符:参数3的下标...”*/
};

/**
 * @brief The DataFilter class      设置数据过滤规则
 */
class DataFilter : public QObject
{
    Q_OBJECT
public:
    DataFilter(QObject* parent=nullptr);

    /**
     * @brief filter        数据过滤处理，如果是CALCULATE，将会把计算结果按照低到高的字节序回传
     * @param source        过滤源数据
     */
    void filter(QByteArray &source, bool& match);

    /**
     * @brief getReglar        得到和设置规则
     * @return
     */
    FilterRegular getReglar() const;
    void setReglar(const FilterRegular &value);

private:
    //匹配规则
    FilterRegular reg;
    QList<QVariant> in;    //发送数据
    QVariant value;         //保存发送数据

    /**
     * @brief cal           计算
     * @param paramOne
     * @param paramTwo
     * @param c
     * @return
     */
    double cal(double paramOne, double paramTwo, QString c);

    /**
     * @brief convertValue      转换值
     * @param source
     */
    void convertValue(QByteArray& source, double val);
signals:
    /**
     * @brief matched       匹配成功的信号，当hasSignal位true的时候，才发生
     */
    void matched(IN,OUT);
};

#endif // DATAFILTER_H
