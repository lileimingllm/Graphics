#include "connectline.h"
#include <QPainter>


ConnectLine::ConnectLine(QPointF start, QPointF end, QGraphicsItem *parent) :
    QGraphicsPathItem(parent),
    start(start),
    end(end)
{
    init();
}

/**
 * @brief setPos        设置点
 * @param start
 * @param end
 */
void ConnectLine::setPos(QPointF start, QPointF end)
{
    this->start = start;
    this->end = end;
    update();
}

/**
 * @brief setPen        设置笔
 * @param pen
 */
void ConnectLine::setPen(const QPen &pen)
{
    this->pen = pen;
}

/**
 * @brief paint     画线
 * @param painter
 * @param option
 * @param widget
 */
void ConnectLine::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->save();

    painter->setRenderHint(QPainter::Antialiasing);
    painter->setPen(pen);
    if (isSelected ()){
        painter->setPen(QPen(pen.color (), 4));
    }

    this->start = mapFromScene(start);
    this->end = mapFromScene(end);

    QPainterPath path;
    path.moveTo(start);

    QPointF c1((start+end).x()/2,start.y());
    QPointF c2((start+end).x()/2,end.y());

    path.cubicTo(c1, c2, end);

    painter->drawPath(path);
    painter->restore();

    QGraphicsPathItem::paint(painter, option, widget);
}

/**
 * @brief init      初始化
 */
void ConnectLine::init()
{
    setZValue (-1);
    setFlags (ItemIsSelectable | ItemIsFocusable);
    pen = QPen(QColor(242,231,37), 4, Qt::SolidLine, Qt::RoundCap);
}

