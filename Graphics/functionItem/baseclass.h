#ifndef BASECLASS_H
#define BASECLASS_H
#include <QObject>
#include <functional>
#include <inputoutputitem.h>
#include <QMessageBox>

using namespace std;
enum CREATETYPE{
    ONLY_OUTPUT,
    ONLY_INPUT,
    INPUT_OUTPUT,
    UNINPUT_UNOUTPUT,
    EVENT,
    FIRST,
    OTHER
};

using IN = QList<QVariant>*;
using OUT = QList<QVariant>*;
class Base;
class ItemWindow;
struct ClassParam {
    QString ObjectName;  //类名
    QStringList Signals;//信号
    QStringList signalNames;    //信号名
    QString slot;               //槽
    Base* object{nullptr};   //对象
    //QString funcName{ "exec" };   //函数名
    CREATETYPE type {INPUT_OUTPUT};    //函数类型
    FIELD_TYPE InFieldtype{FIELD_TYPE::LABEL};           //输入字段类型
    FIELD_TYPE OutFieldtype{FIELD_TYPE::LABEL};           //字段类型
    QStringList infielddsc;       //输入字段描述
    QStringList outfielddsc;       //输出字段描述
    QRegExpValidator *reg { nullptr };    //正则
    QWidget* InCustomWidget{ nullptr };      //自定义窗口，在field_type==CUSTOM的时候填充窗体
    QWidget* OutCustomWidget{ nullptr };      //自定义窗口，在field_type==CUSTOM的时候填充窗体
    ItemWindow * window{ nullptr };         //承载的窗体
};




/**
 * @brief The BaseClass class       所有图形化类的基类(用户不用)
 * @author  毛三
 */
class Base : public QObject
{
    Q_OBJECT
public:
    explicit Base(QObject *parent = 0);

    /**
     * @brief setParam      设置参数
     */
    virtual void setParam(ClassParam * param) = 0;

    ClassParam& getParam();
public slots:
    /**
     * @brief exec      执行函数
     * @param in
     * @param out
     */
    virtual void exec(IN in, OUT out) = 0;
protected:
    ClassParam param;    //参数
signals:

public slots:
};


class globalParam
{
public:
    static QList<ClassParam> allParams;

    static void init();
};

#define REGISTER_GCLASS(Class,objectName) {for(ClassParam p:globalParam::allParams){\
    if(p.ObjectName==objectName){QMessageBox::critical(nullptr,"编译错误",QString("存在多个").append(objectName).append("对象!"));exit(0);}}\
    Base*c=new Class;ClassParam& param=c->getParam();\
    if(param.InCustomWidget)param.InCustomWidget->setFixedSize(100,100);\
    if(param.OutCustomWidget)param.OutCustomWidget->setFixedSize(100,100);\
    param.ObjectName=objectName;globalParam::allParams.append(param);}

#endif // BASECLASS_H
