#ifndef ITEMWINDOWTITLE_H
#define ITEMWINDOWTITLE_H

#include <QWidget>
#include <QHBoxLayout>
#include <QLabel>
#include <QGraphicsProxyWidget>

/**
 * @brief The ItemWindowTitle class     标题栏
 * @author 毛三
 */
class ItemWindowTitle : public QGraphicsProxyWidget
{
public:
    ItemWindowTitle(QGraphicsItem *parent = Q_NULLPTR, Qt::WindowFlags wFlags = Qt::WindowFlags());

    /**
     * @brief setIcon       设置图标
     * @param pix
     */
    void setIcon(QPixmap pix);

    /**
     * @brief setTitleTextStyle      设置显示样式
     * @param style
     */
    void setTitleTextStyle(const QString& style);

    /**
     * @brief setTitle      设置标题显示字符串
     * @param title
     */
    void setTitle(const QString& title);

    /**
     * @brief setIconText       设置icon text
     * @param text
     */
    void setIconText(const QString& text);

    /**
     * @brief setStyle      设置标题栏样式
     * @param style
     */
    void setStyle(const QString& style);

    /**
     * @brief setTitleBarSvg        设置标题栏图形
     * @param bitmap
     */
    void setTitleBarSvg(const QBitmap &bitmap);
private:
    /**
     * @brief init      初始化
     */
    void init();

    QWidget * mWidget { nullptr }; //标题栏显示框图

    QLabel * mIcon{ nullptr };  //图标
    QLabel * mTitle{ nullptr }; //标题栏

    QHBoxLayout * layout{ nullptr };
};

#endif // ITEMWINDOWTITLE_H
