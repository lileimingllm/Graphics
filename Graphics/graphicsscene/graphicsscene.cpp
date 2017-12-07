#include "graphicsscene.h"
#include <QPainter>
#include <QGraphicsSceneMouseEvent>
#include <createnode.h>
#include <QString>

//默认的menu样式
const QString defaultMenuStyle = "QMenu {\
        background-color: black;\
        border-radius: 6px;\
        border: 1px solid black;/*整个菜单区域的边框粗细、样式、颜色*/\
    }\
    QMenu::item {\
        background-color: transparent;\
        border-radius:6px;\
        padding:4px 12px;/*设置菜单项文字上下和左右的内边距，效果就是菜单中的条目左右上下有了间隔*/\
        margin:0px 4px;/*设置菜单项的外边距*/\
        border-bottom:1px solid rgb(140,19,19);/*为菜单项之间添加横线间隔*/\
        color: rgb(224,131,8);\
    }\
    QMenu::item:selected {\
        background-color: rgb(21,21,21);\
        color:rgb(226,17,0);\
    }";

GraphicsScene::GraphicsScene(QObject *parent) :
    QGraphicsScene(parent)
{
    init();
}

GraphicsScene::~GraphicsScene()
{
    //释放资源
    for(ItemWindow* item : mAllWindow)
    {
        if (item){
            ClassParam p = item->getParam();
            if (p.object){
                delete p.object;
            }
            delete item;
        }
    }
}

/**
 * @brief addItem       添加window
 * @param window
 */
void GraphicsScene::addItem(ItemWindow *window)
{
    if (mAllWindow.contains(window))
    {
        return;
    }
    connect(window, SIGNAL(moved()), this, SLOT(repaint()));
    mAllWindow.append(window);
    QGraphicsScene::addItem(window);
}

/**
 * @brief addItem       添加普通item
 * @param item
 */
void GraphicsScene::addItem(QGraphicsItem *item)
{
    QGraphicsScene::addItem(item);
}

QList<ItemWindow *> GraphicsScene::getItems()
{
    return mAllWindow;
}

/**
 * @brief exec      运行
 */
void GraphicsScene::exec()
{
    ItemWindow* first{nullptr}; //记录第一个函数节点
    for (ItemWindow* window : mAllWindow){
        //找到第一个函数
        if (window->getParam ().type == FIRST){
            first = window;
            break;
        }
    }
    signalConnect();
    excute(first, nullptr, nullptr);
}

/**
 * @brief paintEvent        绘制事件
 * @param event
 */
void GraphicsScene::drawBackground(QPainter *painter, const QRectF &rect)
{
    QGraphicsScene::drawBackground(painter, rect);
    painter->setPen(QPen(QColor(220, 220, 220), 1));
    for (int row=-200; row<200; ++row)
    {
        painter->drawLine(QPoint(row*50, -10000), QPoint(row*50, 10000));
    }
    for (int col=-200; col<200; ++col)
    {
        painter->drawLine(QPoint(-10000, col*50), QPoint(10000, col*50));
    }
}

/**
 * @brief mousePressEvent       鼠标点击事件
 * @param event
 */
void GraphicsScene::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    if (event->button() == Qt::RightButton)
    {
        QGraphicsItem * item = itemAt(event->scenePos(), QTransform());
        if (!item)
        {
            menuPos = event->scenePos();
            menu.exec(QCursor::pos());
        }else {
            OutputMark * out = dynamic_cast<OutputMark*>(item);
            InputMark * in = dynamic_cast<InputMark*>(item);
            if (out){
                if (out->getConnected()){
                    deletePos = event->scenePos();
                    deleteLine.exec(QCursor::pos());
                }
            }else if (in){
                if (in->getConnected()){
                    deletePos = event->scenePos();
                    deleteLine.exec(QCursor::pos());
                }
            }
        }
    }
    else
    {
        QGraphicsItem * item = itemAt(event->scenePos(), QTransform());
        if (item)
        {
            outputMark = dynamic_cast<OutputMark*>(item);
            if (outputMark)
            {
                if (outputMark->getConnected() && !outputMark->getCanConnectMoreLines()){
                    //只能连接一条线
                }else {
                    mPos = outputMark->mapToScene(5, 5);
                    mBCanDrawLine = true;
                }
            }
        }
    }
    QGraphicsScene::mousePressEvent(event);
}

/**
 * @brief mouseMoveEvent        鼠标移动事件
 * @param event
 */
void GraphicsScene::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    if (mBCanDrawLine)
    {
        if (line)
        {
            removeItem(line);
            delete line;
            line = nullptr;
        }
        line = new ConnectLine(mPos, event->scenePos());
        addItem(line);
        update();
    }
    QGraphicsScene::mouseMoveEvent(event);
}

/**
 * @brief mouseReleaseEvent     鼠标释放事件
 * @param event
 */
void GraphicsScene::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    mBCanDrawLine = false;
    QGraphicsItem * item = itemAt(event->scenePos(), QTransform());
    InputMark * mark = dynamic_cast<InputMark*>(item);
    //含数的输入输出
    if (mark && outputMark) {
        if (mark->getType() == outputMark->getType()){
            funIO(mark, event);
        }else if (mark->getType()==DISPLAY_TYPE::TARGET &&
                  (outputMark->getType()==DISPLAY_TYPE::EVENT|| outputMark->getType()==DISPLAY_TYPE::SIG)) {
            funIO(mark, event);
        } else if (mark->getType()==DISPLAY_TYPE::INPUT && outputMark->getType()==DISPLAY_TYPE::OUTPUT){
            funIO(mark, event);
        }
    }
    //创建一个输入（信号或事件）
    else if (!outputMark && mark && mark->getType()==DISPLAY_TYPE::ITEM){
        addAInputSignal(mark);
    }
    if (line)
    {
        removeItem(line);
        delete line;
        line = nullptr;
    }
    update();
    outputMark = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
}

/**
 * @brief keyPressEvent         键盘按下事件
 * @param keyEvent
 */
void GraphicsScene::keyPressEvent(QKeyEvent *keyEvent)
{
    if (keyEvent->key() == Qt::Key_Delete){
        for (ItemWindow * window : mAllWindow){
            if (window->isSelected ()){
                deleteItem(window);
            }
        }
    }
    QGraphicsScene::keyPressEvent (keyEvent);
}

/**
 * @brief init      初始化
 */
void GraphicsScene::init()
{
    setBackgroundBrush(QBrush(QColor(51,51,51, 200)));
    createIOFunction = new QAction ("输入输出函数");
    createIOFunction->setIcon (QIcon(":/image/function.png"));

    createSignal = new QAction("创建信号");
    connect(createSignal, SIGNAL(triggered(bool)),this, SLOT(createSignalSlot()));
    menu.addAction(createSignal);
    initFunction();
    menu.setStyleSheet(defaultMenuStyle);
    setItemIndexMethod(QGraphicsScene::NoIndex);
}

/**
 * @brief initFunction      初始化函数
 */
void GraphicsScene::initFunction()
{
    globalParam::init();
    QString sig;
    for(ClassParam para : globalParam::allParams){
        for (QString signalName : para.signalNames){
            sig = para.ObjectName+":"+signalName;
            SignalMap.insert(sig, para);
        }
    }
    QList<ClassParam> IOs = globalParam::allParams;
    if (IOs.size ()>0){
        QMenu * m = new QMenu;
        for (ClassParam p : IOs){
            QAction * action = new QAction(p.ObjectName);
            action->setIcon (QIcon(":/image/function.png"));
            m->addAction(action);
            createInfo.insert (action, p);
            action->setObjectName("FUN:0");
            connect(action, SIGNAL(triggered(bool)), this, SLOT(createFunctionSlot()));
        }
        m->setStyleSheet (defaultMenuStyle);
        createIOFunction->setMenu (m);
    } else {
        createIOFunction->setEnabled (false);
    }

    actionexec = new QAction("开始运行");
    connect(actionexec, SIGNAL(triggered(bool)), this, SLOT(exec()));
    firstAction = new QAction("创建开始函数");
    connect(firstAction,SIGNAL(triggered(bool)),SLOT(createFirstNode()));
    menu.addAction(firstAction);

    menu.addAction(createIOFunction);
    menu.addAction(actionexec);
    deleteLineAction = new QAction("删除节点上的线");
    deleteLine.setStyleSheet(defaultMenuStyle);
    deleteLine.addAction(deleteLineAction);
    connect(deleteLineAction, SIGNAL(triggered(bool)),SLOT(deleteLineSlot()));
}

/**
 * @brief deleteItem        删除一个节点
 * @param window
 */
void GraphicsScene::deleteItem(ItemWindow *window)
{
    if (window){
        //确保能够有一个开始节点
        if (window->getParam().type == FIRST){
            --FirstNodeCount;
        }
    }
    for (int i=mConnectedRelative.size ()-1; i>=0; --i)
    {
        if(mConnectedRelative.at (i)->window == window)
        {
            for(int t=mConnectedRelative.at (i)->lines.size ()-1; t>=0; --t)
            {
                mConnectedRelative[i]->Inputs[t]->setConnected(false);
                removeItem(mConnectedRelative[i]->lines[t]);
                delete mConnectedRelative[i]->lines[t];
            }
            mConnectedRelative.removeAt(i);
        }
    }
    {
        for (int i=0; i<mConnectedRelative.size (); ++i) {
            for (int j=mConnectedRelative.at (i)->inputWindows.size ()-1; j>=0; --j){
                if (mConnectedRelative.at (i)->inputWindows.at (j) == window){
                    mConnectedRelative[i]->Inputs[j]->setConnected(false);
                    mConnectedRelative[i]->outputmark->setConnected(false);
                    removeItem(mConnectedRelative[i]->lines[j]);
                    delete mConnectedRelative[i]->lines[j];
                    mConnectedRelative.at (i)->lines.removeAt (j);
                    mConnectedRelative.at (i)->Inputs.removeAt (j);
                    mConnectedRelative.at (i)->inputWindows.removeAt (j);
                }
            }
        }
    }
    //使对象能够被创建
    QMap<QAction*, ClassParam>::iterator iter = createInfo.begin();
    for (; iter != createInfo.end(); ++iter)
    {
        if (iter.value().ObjectName == window->getParam().ObjectName){
            iter.key()->setObjectName("FUNC:0");
            break;
        }
    }
    mAllWindow.removeOne (window);
    removeItem(window);
    //这里如果是自定义窗口，不能释放，应为layout在回收时会将自定义显示窗口资源一起回收了
    if (window->getParam().InFieldtype != FIELD_TYPE::CUSTOM &&
            window->getParam().OutFieldtype!=FIELD_TYPE::CUSTOM)
        delete window;
    update();
}

/**
 * @brief excute        函数的执行
 */
void GraphicsScene::excute(ItemWindow* window, IN in, OUT out)
{
    if (window){
        window->exec(in,out);
        for(OutputMarkRelation* o : mConnectedRelative) {
            if (o->window == window){
               if (o->Inputs.size()){
                   excute(o->inputWindows.at(0), in, out);
               }
            }
        }
    }
}

/**
 * @brief deleteOutMarkLine     删除一个mark上的线
 * @param mark
 */
void GraphicsScene::deleteOutMarkLine(OutputMark *mark)
{
    if (mark){
        for (int i=mConnectedRelative.size ()-1; i>=0; --i)
        {
            if(mConnectedRelative.at (i)->outputmark == mark)
            {
                for(int t=mConnectedRelative.at (i)->lines.size ()-1; t>=0; --t)
                {
                    mConnectedRelative.at (i)->outputmark->setConnected(false);
                    mConnectedRelative[i]->Inputs[t]->setConnected(false);
                    removeItem(mConnectedRelative[i]->lines[t]);
                    delete mConnectedRelative[i]->lines[t];
                }
                mConnectedRelative.removeAt(i);
                update();
            }
        }
    }
}


/**
 * @brief deleteInMarkLine  删除一个mark上的线
 * @param mark
 */
void GraphicsScene::deleteInMarkLine(InputMark *mark)
{
    if (mark){
        for (int i=0; i<mConnectedRelative.size (); ++i) {
            for (int j=mConnectedRelative.at (i)->Inputs.size ()-1; j>=0; --j){
                if (mConnectedRelative.at (i)->Inputs.at (j) == mark){
                    mConnectedRelative[i]->Inputs[j]->setConnected(false);
                    mConnectedRelative[i]->outputmark->setConnected(false);
                    removeItem(mConnectedRelative[i]->lines[j]);
                    delete mConnectedRelative[i]->lines[j];
                    mConnectedRelative.at (i)->lines.removeAt (j);
                    mConnectedRelative.at (i)->Inputs.removeAt (j);
                    mConnectedRelative.at (i)->inputWindows.removeAt (j);
                    update();
                    return;
                }
            }
        }
    }
}

/**
 * @brief addAInputSignal        增加一个输入信号
 * @param mark
 */
void GraphicsScene::addAInputSignal(InputMark *mark)
{
    if (mark){
        InputItem * item = dynamic_cast<InputItem*>(mark->getParent());
        if (item){
            ItemWindow * window = dynamic_cast<ItemWindow*>(item->getParent());
            if (window){
                InputItem * in = new InputItem(FIELD_TYPE::LABEL,QStringList()<<"事件输入", window);
                in->getMark()->setType(DISPLAY_TYPE::TARGET);
                window->addInput(in);
            }
        }
    }
}

/**
 * @brief signalConnect     信号的连接
 */
void GraphicsScene::signalConnect()
{
    //先断开以前的连接
    for(int i=AConnected.size()-1; i>=0; --i){
        disconnect(AConnected.at(i).sender,AConnected.at(i).Signal.toStdString().c_str(),
                   AConnected.at(i).recever, AConnected.at(i).Slot.toStdString().c_str());
        AConnected.removeAt(i);
    }
    AConnected.clear();
    //添加
    for (OutputMarkRelation* o : mConnectedRelative){
        if (o->outputmark->getType() == DISPLAY_TYPE::SIG){
            OutputItem * item = dynamic_cast<OutputItem*>(o->outputmark->getParent());
            ClassParam param;
            if (item){
                //获取信号类型
                QString value = item->getField()->getFieldValue().toString();
                //找到信号
                if (SignalMap.contains(value)){
                    param = SignalMap[value];
                    value = value.split(":").at(1);
                    for (int t=0; t<param.signalNames.size(); ++t){
                        //找到信号
                        if (param.signalNames.at(t)==value){
                            //连接的另一方
                            for (ItemWindow* w : o->inputWindows){
                                connect(param.object,param.Signals.at(t).toStdString().c_str(),
                                        w->getParam().object, w->getParam().slot.toStdString().c_str());
                                //将连接保存起来
                                SIGNALSLOT s;
                                s.sender = param.object;
                                s.recever = w->getParam().object;
                                s.Signal = param.Signals.at(t);
                                s.Slot = w->getParam().slot;
                                AConnected.append(s);
                            }
                            break;
                        }
                    }

                }

            }
        }
    }
}

/**
 * @brief funIO     函数的输入输出处理
 */
void GraphicsScene::funIO(InputMark* mark, QGraphicsSceneMouseEvent* event)
{
    //一个输入只能对应一个输出
    for(OutputMarkRelation* out: mConnectedRelative){
        if (out->Inputs.contains (mark)){
            if (line)
            {
                removeItem(line);
                delete line;
                line = nullptr;
            }
            QGraphicsScene::mouseReleaseEvent(event);
            update();
            return;
        }
    }
    QList<OutputMarkRelation*>::iterator iter = mConnectedRelative.begin ();
    for(; iter!=mConnectedRelative.end (); ++iter)
    {
        if((*iter)->outputmark == outputMark){
            if ((*iter)->Inputs.contains (mark)){  //已经存在了，就不重复添加
                if (line)
                {
                    removeItem(line);
                    delete line;
                    line = nullptr;
                }

            }else
            {
                mark->setConnected(true);
                outputMark->setConnected(true);
                (*iter)->Inputs.append (mark);
                (*iter)->lines.append (line);
                InputItem * items = dynamic_cast<InputItem*>(mark->getParent ());
                if (items){
                    (*iter)->inputWindows.append(dynamic_cast<ItemWindow*>(items->getParent ()));
                }
                line = nullptr;
            }
            QGraphicsScene::mouseReleaseEvent(event);
            update();
            return;
        }
    } //不存在就添加
    OutputMarkRelation * out = new OutputMarkRelation;
    out->outputmark = outputMark;
    outputMark->setConnected(true);
    OutputItem * item = dynamic_cast<OutputItem*>(outputMark->getParent ());
    if (item){
        out->field = item->getField ();
        out->window = dynamic_cast<ItemWindow*>(item->getParent ());
    }
    out->Inputs = QList<InputMark*>() << mark;
    mark->setConnected(true);
    out->lines = QList<ConnectLine*>() << line;
    InputItem * items = dynamic_cast<InputItem*>(mark->getParent ());
    if (items){
        out->inputWindows = QList<ItemWindow*>() <<dynamic_cast<ItemWindow*>(items->getParent ());
    }
    mConnectedRelative.append (out);
    line = nullptr;
    QGraphicsScene::mouseReleaseEvent(event);
    update();
    return;
}

/**
 * @brief repaint       重绘
 */
void GraphicsScene::repaint()
{
    ItemWindow* item = dynamic_cast<ItemWindow*>(sender());
    // bool isOutputMoved = false;
    if (item) {
        for (int i=0; i<mConnectedRelative.size (); ++i){
            if(mConnectedRelative.at (i)->window == item){
               // isOutputMoved = true;
                for(int t=0; t<mConnectedRelative.at (i)->lines.size (); ++t){
                    mConnectedRelative[i]->lines[t]->setPos (mConnectedRelative.at (i)->outputmark->mapToScene (5,5),mConnectedRelative.at (i)->Inputs.at (t)->mapToScene (5,5));
                }
            }

        }
        //if (!isOutputMoved)
        {
            for (int i=0; i<mConnectedRelative.size (); ++i) {
                for (int j=0; j<mConnectedRelative.at (i)->inputWindows.size (); ++j){
                    if (mConnectedRelative.at (i)->inputWindows.at (j) == item){
                        mConnectedRelative[i]->lines[j]->setPos(mConnectedRelative.at (i)->outputmark->mapToScene (5,5), mConnectedRelative.at (i)->Inputs.at (j)->mapToScene (5,5));
                    }
                }
            }
        }
    }
    update();
}

/**
 * @brief createFunctionSlot        创建函数节点
 */
void GraphicsScene::createFunctionSlot()
{
    QAction* action = dynamic_cast<QAction*>(sender());
    if (action){
        QString on = action->objectName();
        if (on.contains("FUN:1")){
            QMessageBox::warning(nullptr, "警告", "该对象已经存在");
            return;
        }else {
            action->setObjectName("FUN:1");
        }
        if (createInfo.contains (action)){
             ItemWindow * window = CreateNode::create (createInfo[action]);
             window->moveBy(menuPos.x(), menuPos.y());
             addItem(window);
        }
    }
}

/**
 * @brief createFirstNode       创建开始节点
 */
void GraphicsScene::createFirstNode()
{
    //只能有一个开始节点
    if (FirstNodeCount){
        QMessageBox::warning(nullptr, "警告","只能有一个开始函数");
        return ;
    }
    ClassParam param;
    param.type = FIRST;
    param.ObjectName = "开始";
    param.outfielddsc = QStringList()<<"执行";
    ItemWindow * window = CreateNode::create (param);
    window->setNoAddButton(true);
    window->moveBy(menuPos.x(), menuPos.y());
    addItem(window);
    //只能有一个开始节点
    FirstNodeCount++;
}

/**
 * @brief deleteLineSlot        删除节点上的线
 */
void GraphicsScene::deleteLineSlot()
{
    QGraphicsItem* item = itemAt(deletePos, QTransform());
    if (item){
        InputMark * in = dynamic_cast<InputMark*>(item);
        OutputMark * out = dynamic_cast<OutputMark*>(item);
        if (out){
            deleteOutMarkLine(out);
        } else if (in) {
            deleteInMarkLine(in);
        }
    }
}

/**
 * @brief createSignalSlot      创建信号
 */
void GraphicsScene::createSignalSlot()
{
    ClassParam param;
    param.ObjectName = "信号";
    param.type = ONLY_OUTPUT;
    param.OutFieldtype = FIELD_TYPE::COMBOBOX;
    ItemWindow * window = CreateNode::create(param);
    //设置为信号
    window->getOutputs().at(0)->getMark()->setType(DISPLAY_TYPE::SIG);
    //设置输出信号
    window->getOutputs().at(0)->setFieldParam(SignalMap.keys());
    //设置标题
    window->getTitle()->setIconText("S");
    //无add按钮
    window->setNoAddButton(true);
    window->getOutputs().at(0)->getField()->setFixedWidth(140);
    window->getLayout()->addItem(window->getOutputs().at(0),1,0,1,3);
    //设置样式
    window->setTitleStyle("background:green; color:white");
    //设置可以连接多条线
    window->getOutputs().at(0)->getMark()->setCanConnectMoreLines(true);
    window->moveBy(menuPos.x(), menuPos.y());
    addItem(window);
}
