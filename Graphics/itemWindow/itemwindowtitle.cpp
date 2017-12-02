#include "itemwindowtitle.h"

ItemWindowTitle::ItemWindowTitle(QGraphicsItem *parent, Qt::WindowFlags wFlags) :
    QGraphicsProxyWidget(parent, wFlags),
    mIcon (new QLabel()),
    mTitle(new QLabel()),
    layout(new QHBoxLayout()),
    mWidget (new QWidget())
{
    init();
}

/**
 * @brief setIcon       设置图标
 * @param pix
 */
void ItemWindowTitle::setIcon(QPixmap pix)
{
    mIcon->setPixmap(pix);
}


/**
 * @brief setTitleTextStyle      设置显示样式
 * @param style
 */
void ItemWindowTitle::setTitleTextStyle(const QString &style)
{
    mTitle->setStyleSheet(style);
}

/**
 * @brief setTitle      设置标题显示字符串
 * @param title
 */
void ItemWindowTitle::setTitle(const QString &title)
{
    mTitle->setText(title);
}

/**
 * @brief setIconText       设置icon text
 * @param text
 */
void ItemWindowTitle::setIconText(const QString &text)
{
    mIcon->setText(text);
}


/**
 * @brief setStyle      设置标题栏样式
 * @param style
 */
void ItemWindowTitle::setStyle(const QString &style)
{
    mWidget->setStyleSheet(style);
}

/**
 * @brief setTitleBarSvg        设置标题栏图形
 * @param bitmap
 */
void ItemWindowTitle::setTitleBarSvg(const QBitmap& bitmap)
{
    mWidget->setMask(bitmap);
}

/**
 * @brief init      初始化
 */
void ItemWindowTitle::init()
{
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);

    mIcon->setFixedSize(20,20);
    mIcon->setScaledContents(true);
    mIcon->setAlignment(Qt::AlignCenter);
    mWidget->setLayout(layout);
    mWidget->setFixedSize(155, 20);
    mTitle->setText("new function");
    layout->addWidget(mIcon);
    layout->addWidget(mTitle);

    mIcon->setText("f");
    mIcon->setStyleSheet("font: 75 18pt");
    setWidget(mWidget);
    mWidget->setStyleSheet("QWidget{background-color:rgba(77,120,148, 0.5);border-radius:15px;}QLabel{color:white;}");
}
