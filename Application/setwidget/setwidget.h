#ifndef SETWIDGET_H
#define SETWIDGET_H

#include <QWidget>
#include <QGridLayout>
#include <QPushButton>

/**
 * @brief The SetWidget class       节点在自定义显示的窗口
 * @author 毛三
 */
class SetWidget : public QWidget
{
    Q_OBJECT
public:
    explicit SetWidget(QList<QPushButton*> buttons,     //要放置的button
                       bool column=false,               //是否纵向排列
                       QWidget *parent = 0);
    SetWidget(QWidget* widget);
private:
    bool column;        //是否纵向排列、
    QGridLayout *layout{ nullptr };    //布局管理器
    /**
     * @brief init      初始化
     */
    void init(QList<QPushButton*> buttons);
};

#endif // SETWIDGET_H
