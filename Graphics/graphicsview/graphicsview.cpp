#include "graphicsview.h"
#include <QWheelEvent>
#include <graphicsscene.h>

GraphicsView::GraphicsView(QWidget *parent) :
    QGraphicsView(parent)
{
    init();
}

GraphicsView::GraphicsView(GraphicsScene *scene) :
    QGraphicsView(scene)
{
    init();
}

/**
 * @brief wheelEvent        滑轮事件（实现滚动缩放）
 * @param event
 */
void GraphicsView::wheelEvent(QWheelEvent *event)
{
    if (mCtrlClicked)
    {
        scaleView(pow((double)2, event->delta() / 440.0));
        centerOn(mapToScene(QCursor::pos()));
    }
    QGraphicsView::wheelEvent(event);
}

/**
 * @brief keyPressEvent         按键点击事件
 * @param event
 */
void GraphicsView::keyPressEvent(QKeyEvent *event)
{
    mCtrlClicked = true;
    QGraphicsView::keyPressEvent(event);
}

/**
 * @brief keyReleaseEvent       按键释放事件
 * @param event
 */
void GraphicsView::keyReleaseEvent(QKeyEvent *event)
{
    mCtrlClicked = false;
    QGraphicsView::keyReleaseEvent(event);
}

/**
 * @brief init      初始化
 */
void GraphicsView::init()
{
    setResizeAnchor(AnchorViewCenter);
}

void GraphicsView::scaleView(qreal scaleFactor)
{
    qreal factor = transform().scale(scaleFactor, scaleFactor).mapRect(QRectF(0, 0, 1, 1)).width();
    if (factor < 0.07 || factor > 100)
        return;

    scale(scaleFactor, scaleFactor);
}
