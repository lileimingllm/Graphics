#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <inputoutputitem.h>
#include <QList>
#include <itemwindow.h>
#include <QMenu>
#include <QAction>
#include <connectline.h>
#include <createnode.h>
#include <QMessageBox>
#include <Thread>
#include <QThreadPool>

class QPainter;
class QGraphicsSceneMouseEvent;
class OutputMarkRelation;
class InputMarkRelation;

/**
 * @brief The SIGNAL_SLOT struct    已经连接好的信号和槽
 */
struct SIGNALSLOT{
    QObject* sender{ nullptr };     //发送者
    QObject* recever{ nullptr };    //接收者
    QString Signal;                 //信号
    QString Slot;                   //槽
};

/**
 * @brief The GraphicsScene class       图形场景类，配合GraphicsView用
 * @author 毛三
 */


class GraphicsScene : public QGraphicsScene
{
    Q_OBJECT
public:
    GraphicsScene(QObject *parent = Q_NULLPTR);

    ~GraphicsScene();
    /**
     * @brief addItem       添加window
     * @param window
     */
    void addItem(ItemWindow * window);

    /**
     * @brief addItem       添加普通item
     * @param item
     */
    void addItem(QGraphicsItem* item);

    QList<ItemWindow*> getItems();

public slots:
    /**
     * @brief exec      运行
     */
    void exec();
protected:

    /**
     * @brief drawBackground        绘制事件
     * @param event
     */
    void drawBackground(QPainter *painter, const QRectF &rect);

    /**
     * @brief mousePressEvent       鼠标点击事件
     * @param event
     */
    void mousePressEvent(QGraphicsSceneMouseEvent * event);

    /**
     * @brief mouseMoveEvent        鼠标移动事件
     * @param event
     */
    void mouseMoveEvent(QGraphicsSceneMouseEvent * event);

    /**
     * @brief mouseReleaseEvent     鼠标释放事件
     * @param event
     */
    void mouseReleaseEvent(QGraphicsSceneMouseEvent * event);

    /**
     * @brief keyPressEvent         键盘按下事件
     * @param keyEvent
     */
    void keyPressEvent(QKeyEvent *keyEvent);

private:

    /**
     * @brief init      初始化
     */
    void init();

    /**
     * @brief initFunction      初始化函数
     */
    void initFunction();

    /**
     * @brief deleteItem        删除一个节点
     * @param window
     */
    void deleteItem(ItemWindow* window);

    /**
     * @brief excute        函数的执行
     */
    void excute(ItemWindow *window, IN in, OUT out);

    /**
     * @brief deleteOutMarkLine     删除一个mark上的线
     * @param mark
     */
    void deleteOutMarkLine(OutputMark* mark);

    /**
     * @brief deleteInMarkLine  删除一个mark上的线
     * @param mark
     */
    void deleteInMarkLine(InputMark * mark);

    /**
     * @brief addAInputSignal        增加一个输入信号
     * @param mark
     */
    void addAInputSignal(InputMark* mark);

    /**
     * @brief signalConnect     信号的连接
     */
    void signalConnect();

    /**
     * @brief funIO     函数的输入输出处理
     */
    void funIO(InputMark *mark, QGraphicsSceneMouseEvent *event);

    bool mBCanDrawLine { false };       //可以画线

    QPointF mPos;            //当前点
    ConnectLine * line{ nullptr };     //连接线

    OutputMark * outputMark{ nullptr };   //输出mark

    QList<OutputMarkRelation*> mConnectedRelative;   //输入输出关系图

    QList<ItemWindow *> mAllWindow;     //保存所有的window

    QMenu menu;     //目录
    QAction *createIOFunction{ nullptr };   //创建输入输出
    QAction *actionexec{ nullptr };     //执行
    QAction *deleteAction { nullptr };  //删除
    QAction *firstAction{ nullptr };    //第一个节点
    QAction *createSignal { nullptr };    //创建信号


    QPointF menuPos;    //弹出menu的位置

    QMenu deleteLine;   //删除线
    QAction * deleteLineAction { nullptr } ;    //删除线
    QMap<QAction*, ClassParam> createInfo;       //所有创建的action

    QPointF deletePos;  //删除点    

    QMap<QString, ClassParam> SignalMap;     //所有的信号
    QList<SIGNALSLOT> AConnected;            //连接上的信号和槽

    unsigned int FirstNodeCount{ 0 };            //开始节点的个数

private slots:
    /**
     * @brief repaint       重绘
     */
    void repaint();

    /**
     * @brief createFunctionSlot        创建函数节点
     */
    void createFunctionSlot();

    /**
     * @brief createFirstNode       创建开始节点
     */
    void createFirstNode();

    /**
     * @brief deleteLineSlot        删除节点上的线
     */
    void deleteLineSlot();

    /**
     * @brief createSignalSlot      创建信号
     */
    void createSignalSlot();
};


/**
 * @brief The OutputMarkRelation class        与mark相关的关系
 */
class OutputMarkRelation
{
public:
    OutputMark *outputmark { nullptr };     //输出mark
    QWidget * field{ nullptr };     //字段
    ItemWindow * window{ nullptr };         //移动项
    QList<InputMark*> Inputs;             //所有与之相连的点
    QList<ItemWindow*> inputWindows;      //输入的mark的window
    QList<ConnectLine*> lines; //连接线 list装的是所有与mark连接的输出mark
};

#endif // GRAPHICSSCENE_H
