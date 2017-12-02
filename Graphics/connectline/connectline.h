#ifndef CONNECTLINE_H
#define CONNECTLINE_H
#include <QGraphicsLineItem>
#include <QPen>
#include <QPointF>
#include <QtDebug>

class ConnectLine : public QGraphicsPathItem
{
public:
    ConnectLine(QPointF start, QPointF end, QGraphicsItem* parent=nullptr);

    /**
     * @brief setPos        设置点
     * @param start
     * @param end
     */
    void setPos(QPointF start, QPointF end);

    /**
     * @brief setPen        设置笔
     * @param pen
     */
    void setPen(const QPen& pen );
private:
    /**
     * @brief paint     画线
     * @param painter
     * @param option
     * @param widget
     */
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

    /**
     * @brief init      初始化
     */
    void init();


    QPointF start;
    QPointF end;
    QPen pen;
};

#endif // CONNECTLINE_H
