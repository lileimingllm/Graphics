#include "itemwindow.h"
#include <QPainter>
#include <QGraphicsGridLayout>
#include <QStyle>
#include <QWidget>
#include <QGraphicsScene>
#include <QtDebug>
#include <QSpacerItem>
#include <baseclass.h>

ItemWindow::ItemWindow(ClassParam param, QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QGraphicsWidget(parent, wFlags),
    param(param)
{
    init();

    setLayout(layout);
    setFlag(ItemIsMovable);
}

/**
 * @brief saveSelf      保存自己
 * @param window
 */
void ItemWindow::saveSelf(ItemWindow *window)
{
    if (param.object)
        param.object->getParam().window = window;
}

/**
 * @brief addInput      增加一个输入项
 * @param inputItem
 */
void ItemWindow::addInput(InputItem *inputItem)
{
    if (Inputs.contains (inputItem))
    {
        return;
    }
    Inputs.append (inputItem);
    QGraphicsLayoutItem* item = layout->itemAt(mInputCount, 0);
    layout->addItem(inputItem, mInputCount, 0);
    layout->addItem(item, ++mInputCount, 0);
    update();
}


/**
 * @brief addOutput     增加一个输出项
 * @param outputItem
 */
void ItemWindow::addOutput(OutputItem *outputItem)
{
    if (Outputs.contains (outputItem))
    {
        return;
    }
    Outputs.append (outputItem);
    layout->addItem(outputItem, ++mOutputCount, 2);
    update();
}

/**
 * @brief setFuncName   设置函数名
 * @param name
 */
void ItemWindow::setFuncName(const QString &name)
{
    title->setTitle(name);
}

/**
 * @brief setTitleStyle     设置标题样式
 * @param style
 */
void ItemWindow::setTitleStyle(const QString &style)
{
    title->setStyle (style);
}

/**
 * @brief setNoAddButton        设置添加按钮
 * @param no
 */
void ItemWindow::setNoAddButton(bool no)
{
    if (no){
        add->setVisible(false);
    } else {
        add->setVisible(true);
    }
}

/**
 * @brief getLayout     获取layout
 * @return
 */
QGraphicsGridLayout *ItemWindow::getLayout()
{
    return layout;
}

QList<InputItem *> ItemWindow::getInputs() const
{
    return Inputs;
}

QList<OutputItem *> ItemWindow::getOutputs() const
{
    return Outputs;
}

/**
 * @brief exec      执行
 */
void ItemWindow::exec(IN in, OUT out)
{
    if (param.object){
        param.object->exec(in, out);
    }
}


/**
 * @brief mouseMoveEvent        鼠标移动事件
 * @param event
 */
void ItemWindow::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    QGraphicsWidget::mouseMoveEvent(event);
    if (isPressed)
    {
        this->scene()->update();
    }
}


/**
 * @brief mousePressEvent   鼠标点击事件
 * @param event
 */
void ItemWindow::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    isPressed = true;
    QGraphicsWidget::mousePressEvent(event);
}

/**
 * @brief mouseReleaseEvent     鼠标释放事件
 * @param event
 */
void ItemWindow::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    isPressed = false;
    QGraphicsWidget::mouseReleaseEvent(event);
}

/**
 * @brief moveEvent     移动事件
 * @param event
 */
void ItemWindow::moveEvent(QGraphicsSceneMoveEvent *event)
{
    emit moved();
    QGraphicsWidget::moveEvent(event);
}

ItemWindowTitle *ItemWindow::getTitle() const
{
    return title;
}

ClassParam ItemWindow::getParam() const
{
    return param;
}


/**
 * @brief paint     绘制一个矩形（黑色的）
 * @param painter
 * @param option
 * @param widget
 */
void ItemWindow::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setRenderHints(QPainter::Antialiasing);
    painter->setBrush(QBrush(QColor(15, 17, 15, 170)));
    int height {0};
    int maxCount = mOutputCount>mInputCount?mOutputCount:mInputCount;
    height = (maxCount-1)*32;
    int width { 0 };
    if (param.InFieldtype==FIELD_TYPE::CUSTOM)
    {
        height += 90;
        width = 20;
        static bool widthalset = false;
        if (!widthalset){
            title->widget()->setFixedWidth(155+width);
            widthalset = true;
        }
    }
    if (param.OutFieldtype == FIELD_TYPE::CUSTOM)
    {
        width = 80;
        static bool alreadySet = false;
        if (!alreadySet)
        {
            title->widget()->setFixedWidth(155+width);
            alreadySet = true;
        }
    }
    if (isSelected ())
    {
        painter->save ();
        painter->setPen(QPen(QColor(255,255,0,170), 4));
        painter->drawRoundRect(QRect(-4, -4, width+164, height+58), 5, 5);
        painter->restore ();
    }
    painter->drawRoundRect(QRect(0, 0, width+156, height+50), 5, 5);
    QGraphicsWidget::paint(painter, option, widget);
}

/**
 * @init    初始化
 * */
void ItemWindow::init()
{
    setFlag (QGraphicsItem::ItemIsSelectable);
    layout =  new QGraphicsGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    title = new ItemWindowTitle(this);
    layout->addItem(title, 0, 0, 1, 3);
    add = new InputItem(FIELD_TYPE::LABEL,QStringList()<<"增加信号", this);
    add->getMark()->setType(DISPLAY_TYPE::ITEM);
    layout->addItem(add, 1, 0);
}
