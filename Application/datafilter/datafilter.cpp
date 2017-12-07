#include "datafilter.h"

DataFilter::DataFilter(QObject *parent) :
    QObject(parent)
{

}

/**
 * @brief filter        数据过滤处理，如果是CALCULATE，将会把计算结果按照低到高的字节序回传
 * @param source        过滤源数据
 */
void DataFilter::filter(QByteArray& source, bool &match)
{
    match = false;
    if (!reg.match.size()){
        return;
    }
    if (!source.length())
    {
        return;
    }
    //正则匹配
    if (Regulation::REGULAR == reg.regular)
    {
        QString s  = QString(source);
        //替换成几率比较小重复的字符串，然后再比较
        if (s.contains(QRegularExpression(reg.match.at(0))))
        {
           match = true;
           //如果有信号，就发送
           if (reg.hasSignal){
               in.clear();
               value.setValue(source);
               in.append(value);
               matched(&in,NULL);
           }
           return;
        }
    } else if (Regulation::INCLUDE == reg.regular){
        QString s = QString(source);
        for (QString m : reg.match){
            if (!s.contains(m)){
                return;
            }
        }
        match = true;
        if (reg.hasSignal){
            in.clear();
            value.setValue(source);
            in.append(value);
            matched(&in,nullptr);
        }
    } else if (Regulation::LENGTH == reg.regular){
        bool ok;
        if (source.size() == reg.match.at(0).toUInt(&ok)){
            match = true;
            //如果有信号，就发送
            if (reg.hasSignal){
                in.clear();
                value.setValue(source);
                in.append(value);
                matched(&in,nullptr);
            }
            return;
        }
    } else if (Regulation::CALCULATEMATCH == reg.regular){
        if (reg.match.at(0).contains(":") && reg.match.at(0).contains("=")){
            QList<QString> v = reg.match.at(0).split(":");
            if (5==v.length()){
                bool ok;
                double va = cal((double)source.at(v.at(0).toInt(&ok)),(double)source.at(v.at(2).toInt(&ok)), v.at(1));
                if (va == v.at(4).toDouble(&ok)){
                    match = true;
                    if (reg.type == ReturnType::VALUE){
                        convertValue(source, va);
                    }
                    //如果有信号，就发送
                    if (reg.hasSignal){
                        in.clear();
                        value.setValue(source);
                        in.append(value);
                        matched(&in,nullptr);
                    }
                    return;
                }
            }
        }
    }else if (Regulation::CALCULATE == reg.regular)
    {
        if (reg.match.at(0).contains(":")){
            QList<QString> v = reg.match.at(0).split(":");
            if(v.size() > 1){
                double sv;
                for(QString id : v){
//                    sv = cal(source.at(reg.match.at()))
                }
            }
        }

    }
}

/**
 * @brief getReglar        得到和设置规则
 * @return
 */
FilterRegular DataFilter::getReglar() const
{
    return reg;
}

void DataFilter::setReglar(const FilterRegular &value)
{
    reg = value;
}

/**
 * @brief cal           计算
 * @param paramOne
 * @param paramTwo
 * @param c
 * @return
 */
double DataFilter::cal(double paramOne, double paramTwo, QString c)
{
    if ("+" == c){
        return paramOne + paramTwo;
    }else if ("-" == c){
        return paramOne - paramTwo;
    }else if ("*" == c){
        return paramOne * paramTwo;
    }else if ("/" == c){
        return paramOne / paramTwo;
    }else{
        return 0;
    }
}


/**
 * @brief convertValue      转换值
 * @param source
 */
void DataFilter::convertValue(QByteArray &source, double val)
{
    source = QString::number(val).toLocal8Bit();
}
