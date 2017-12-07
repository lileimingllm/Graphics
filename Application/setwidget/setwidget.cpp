#include "setwidget.h"

SetWidget::SetWidget(QList<QPushButton *> buttons,
                     bool column,
                     QWidget *parent) :
    QWidget(parent),
    column(column)
{
    init(buttons);
}

SetWidget::SetWidget(QWidget *widget)
{
    layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(0,0,0,0);
    layout->addWidget(widget);
}

/**
 * @brief init      初始化
 */
void SetWidget::init(QList<QPushButton *> buttons)
{
    layout = new QGridLayout(this);
    layout->setSpacing(0);
    layout->setContentsMargins(2,2,2,2);
    int row=0,col=0;
    for(QPushButton* button : buttons)
    {
        if(column)
        {
            layout->addWidget(button,row++,0);
        }
        else
        {
            if(3==col)
            {
                ++row;col=0;
            }
            layout->addWidget(button,row,col++);
        }
        button->setParent(this);
    }
}
