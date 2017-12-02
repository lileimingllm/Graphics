#ifndef GRAPHICSVIEW_H
#define GRAPHICSVIEW_H
#include <QGraphicsView>
#include <QScrollBar>

class QWheelEvent;
class QMouseEvent;
class GraphicsScene;

/**
 * @brief The GraphicsView class        视图类
 * @author 毛三
 */
class GraphicsView : public QGraphicsView
{
public:
    GraphicsView(QWidget *parent = Q_NULLPTR);
    GraphicsView(GraphicsScene* scene);

protected:
    /**
     * @brief wheelEvent        滑轮事件（实现滚动缩放）
     * @param event
     */
    void wheelEvent(QWheelEvent * event);

    /**
     * @brief keyPressEvent         按键点击事件
     * @param event
     */
    void keyPressEvent(QKeyEvent * event);

    /**
     * @brief keyReleaseEvent       按键释放事件
     * @param event
     */
    void keyReleaseEvent(QKeyEvent * event);

    /**
     * @brief scaleView         缩放窗口
     * @param selector
     */
    void scaleView(float scaleFactor);
private:

    /**
     * @brief init      初始化
     */
    void init();

    QPoint mCentrePos;       //中心点

    bool mCtrlClicked{ false };      //ctrl被点击
    void scaleView(qreal scaleFactor);
    float scaled{0};    //当前已经放大的倍数
};

#endif // GRAPHICSVIEW_H
