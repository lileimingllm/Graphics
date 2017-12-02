#ifndef ITEMWINDOW_H
#define ITEMWINDOW_H

#include <QGraphicsGridLayout>
#include <QGraphicsWidget>
#include <inputoutputitem.h>
#include <QGraphicsSceneMouseEvent>
#include <QGraphicsSceneMoveEvent>
#include <itemwindowtitle.h>
#include <functional>
#include <baseclass.h>


using namespace std;

class QPainter;
class QWidget;
class QStyleOptionGraphicsItem;
/**
 * @brief The ItemWindow class      每个节点的窗口
 * @author 毛三
 */
class ItemWindow : public QGraphicsWidget
{
    Q_OBJECT
public:
    ItemWindow(ClassParam param, QGraphicsItem *parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags());

    /**
     * @brief saveSelf      保存自己
     * @param window
     */
    void saveSelf(ItemWindow* window);

    /**
     * @brief addInput      增加一个输入项
     * @param inputItem
     */
    void addInput(InputItem *inputItem);

    /**
     * @brief addOutput     增加一个输出项
     * @param outputItem
     */
    void addOutput(OutputItem *outputItem);


    /**
     * @brief setFuncName   设置函数名
     * @param name
     */
    void setFuncName(const QString& name);

    /**
     * @brief setTitleStyle     设置标题样式
     * @param style
     */
    void setTitleStyle(const QString& style);

    /**
     * @brief setNoAddButton        设置添加按钮
     * @param no
     */
    void setNoAddButton(bool no);

    /**
     * @brief getLayout     获取layout
     * @return
     */
    QGraphicsGridLayout *getLayout();

    QList<InputItem*> getInputs() const;

    QList<OutputItem*> getOutputs() const;

    /**
     * @brief exec      执行
     */
    void exec(IN in, OUT out);

    ClassParam getParam() const;

    ItemWindowTitle *getTitle() const;

protected:

private:
    /**
     * @init    初始化
     * */
    void init();

    /**
     * @brief paint     绘制一个矩形（黑色的）
     * @param painter
     * @param option
     * @param widget
     */
    virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    /**
     * @brief mouseMoveEvent        鼠标移动事件
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);


    /**
     * @brief mousePressEvent   鼠标点击事件
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief mouseReleaseEvent     鼠标释放事件
     * @param event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);

    /**
     * @brief moveEvent     移动事件
     * @param event
     */
    void moveEvent(QGraphicsSceneMoveEvent * event);

    QGraphicsGridLayout * layout { nullptr };   //布局

    bool isPressed { nullptr };         //鼠标点击

    unsigned mInputCount { 1 };           //布局管理器中的输入个数
    unsigned mOutputCount{ 0 };           //布局管理器中的输出个数

    QList<InputItem *> Inputs;  //输入项
    QList<OutputItem *> Outputs;    //输出项

    ClassParam param;   //函数

    ItemWindowTitle* title { nullptr };

    InputItem * add { nullptr };    //添加项
signals:
    void moved();
};



#endif // ITEMWINDOW_H
