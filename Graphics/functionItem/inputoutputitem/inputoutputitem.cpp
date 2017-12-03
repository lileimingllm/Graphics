#include "inputoutputitem.h"
#include <QGraphicsProxyWidget>
#include <QPaintEvent>
#include <QPainter>

InputItem::InputItem(FIELD_TYPE type, QStringList fieldParam, QGraphicsWidget *parent, Qt::WindowFlags wFlags) :
    QGraphicsWidget(parent, wFlags),
    parent(parent),
    fieldParam(fieldParam)
{
    init(type);
}

/**
 * @brief init      初始化
 */
void InputItem::init(FIELD_TYPE type)
{
    layout = new QGraphicsLinearLayout(this);
    layout->setOrientation(Qt::Horizontal);
    layout->setSpacing(0);
    layout->setContentsMargins(0,9,0,9);
    mark = new InputMark(this);
    layout->addItem(mark);
    mFieldParam = new InputField(type, fieldParam);
    mFieldParam->setAlignment(Qt::AlignLeft);
    QGraphicsProxyWidget * widgetFieldParam = new QGraphicsProxyWidget;
    widgetFieldParam->setWidget(mFieldParam);
    layout->addItem(widgetFieldParam);
}

/**
  * @brief mouseMoveEvent      屏蔽鼠标
  * @param event
  */
void InputItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

InputMark *InputItem::getMark() const
{
    return mark;
}

QStringList InputItem::getFieldParam()
{
    fieldParam = mFieldParam->getFieldParam();
    return fieldParam;
}

void InputItem::setFieldParam(const QStringList &value)
{
    fieldParam = value;
    mFieldParam->setFieldParam(fieldParam);
}

QGraphicsWidget *InputItem::getParent() const
{
    return parent;
}

InputField *InputItem::getField()
{
    return mFieldParam;
}

/**
 * @brief setWidget     设置窗口
 * @param widget
 */
void InputItem::setWidget(QWidget *widget)
{
    mFieldParam->setWidget(widget);
}

FIELD_TYPE InputItem::getFieldType()
{
    return mFieldParam->getType();
}


OutputItem::OutputItem(FIELD_TYPE type, QStringList fieldParam, QGraphicsWidget *parent, Qt::WindowFlags wFlags) :
    QGraphicsWidget(parent, wFlags),
    parent(parent),
    fieldParam(fieldParam)
{
    init(type);
}

/**
 * @brief init      初始化
 */
void OutputItem::init(FIELD_TYPE type)
{
    layout = new QGraphicsLinearLayout(this);
    layout->setOrientation(Qt::Horizontal);
    layout->setSpacing(0);
    layout->setContentsMargins(0,9,0,9);

    mFieldParam = new OutputField(type, fieldParam);
    mFieldParam->setAlignment(Qt::AlignRight);
    QGraphicsProxyWidget * widgetFieldParam = new QGraphicsProxyWidget;
    widgetFieldParam->setWidget(mFieldParam);
    layout->addItem(widgetFieldParam);
    mark = new OutputMark(this);
    layout->addItem(mark);
}

/**
  * @brief mouseMoveEvent      屏蔽鼠标
  * @param event
  */
void OutputItem::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    Q_UNUSED(event);
}

OutputMark *OutputItem::getMark() const
{
    return mark;
}

QStringList OutputItem::getFieldParam()
{
    fieldParam = mFieldParam->getFieldParam();
    return fieldParam;
}

void OutputItem::setFieldParam(const QStringList &value)
{
    fieldParam = value;
    mFieldParam->setFieldParam(fieldParam);
}

QGraphicsWidget *OutputItem::getParent() const
{
    return parent;
}

/**
 * @brief setWidget     设置显示窗口
 * @param display
 */
void OutputItem::setWidget(QWidget *display)
{
    mFieldParam->setWidget(display);
}

OutputField *OutputItem::getField() const
{
    return mFieldParam;
}

InputWidget::InputWidget(QWidget *parent) :
    QLabel(parent)
{
    init();
}

/**
 * @brief setType       设置显示类型
 * @param type
 */
void InputWidget::setType(DISPLAY_TYPE type)
{
    dType = type;
}

/**
 * @brief getType       获取显示类型
 * @return
 */
DISPLAY_TYPE InputWidget::getType()
{
    return dType;
}

/**
 * @brief paintEvent        绘图事件
 * @param event
 */
void InputWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(penColor, 1));
    if (fill){
        painter.setBrush(QBrush(penColor));
    }
    getDrawPolygon(&painter);
    QLabel::paintEvent(event);
}

/**
 * @brief init      初始化
 */
void InputWidget::init()
{
    setStyleSheet("background:rgb(42,43,42)");
    setFixedSize(16,14);
}


/**
 * @brief getDrawPolygon        根据类型画图
 */
void InputWidget::getDrawPolygon(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    if (dType== DISPLAY_TYPE::INPUT || dType==DISPLAY_TYPE::OUTPUT)
    {
        QPoint polygon[6];
        polygon[0] = QPoint(0.5*width(), 0.1*height());
        polygon[1] = QPoint(0.9*width(), 0.5*height());
        polygon[2] = QPoint(0.5*width(), 0.9*height());
        polygon[3] = QPoint(0.1*width(), 0.9*height());
        polygon[4] = QPoint(0.1*width(), 0.1*height());
        polygon[5] = QPoint(0.5*width(), 0.1*height());
        painter->drawPolygon(polygon, 6);
    }
    else if (dType == DISPLAY_TYPE::EVENT )
    {
        painter->drawEllipse(QPoint(0.5*height(),0.5*height()), 0.4*height(), 0.4*height());
    }
    else if (dType == DISPLAY_TYPE::FIELD)
    {
        QPoint polygonTr[3];
        polygonTr[0] = QPoint(0.3*width(), 0.1*height());
        polygonTr[1] = QPoint(0.8*width(), 0.5*height());
        polygonTr[2] = QPoint(0.3*width(), 0.9*height());
        painter->drawPolygon(polygonTr, 3);
    }
    else if (dType ==  DISPLAY_TYPE::TARGET)
    {
        painter->drawEllipse(QPoint(0.5*height(),0.5*height()), 0.4*height(), 0.4*height());
        painter->drawEllipse(QPoint(0.5*height(),0.5*height()), 0.25*height(), 0.25*height());
    }
    else if (dType == DISPLAY_TYPE::SIG)
    {
        painter->drawRect(0.1*width(), 0.1*height(), 0.8*width(), 0.8*height());
        painter->drawRect(0.2*width(), 0.2*height(), 0.5*width(), 0.5*height());
        painter->drawRect(0.3*width(), 0.3*height(), 0.2*width(), 0.2*height());
    }
    else if (dType ==  DISPLAY_TYPE::ITEM)
    {
//        QPoint polygonItem[4];
//        polygonItem[0] = QPoint(0.5*width(), 0.1*height());
//        polygonItem[1] = QPoint(0.8*width(), 0.5*height());
//        polygonItem[2] = QPoint(0.5*width(), 0.9*height());
//        polygonItem[3] = QPoint(0.1*width(), 0.5*height());
//        painter->drawPolygon(polygonItem, 4);
        painter->save();
        painter->setPen(QPen(QColor(200,25,24),2));
        painter->drawEllipse(QPoint(0.5*height(),0.5*height()), 0.45*height(), 0.45*height());
        painter->setPen(QPen(QColor(255,126,0),1));
        painter->drawLine(QPoint(0.3*height(),0.5*height()), QPoint(0.75*height(), 0.5*height()));
        painter->drawLine(QPoint(0.5*height(),0.3*height()), QPoint(0.5*height(), 0.75*height()));
        painter->restore();
    }
    else {

    }
}

QColor InputWidget::getPenColor() const
{
    return penColor;
}

void InputWidget::setPenColor(const QColor &value)
{
    penColor = value;
}

bool InputWidget::getFill() const
{
    return fill;
}

void InputWidget::setFill(bool value)
{
    fill = value;
}



OutputWidget::OutputWidget(QWidget *parent) :
    QLabel(parent)
{
    init();
}

/**
 * @brief setType       设置显示类型
 * @param type
 */
void OutputWidget::setType(DISPLAY_TYPE type)
{
    dType = type;
}

/**
 * @brief getType       获取显示类型
 * @return
 */
DISPLAY_TYPE OutputWidget::getType()
{
    return dType;
}

/**
 * @brief paintEvent        绘图事件
 * @param event
 */
void OutputWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    painter.setPen(QPen(penColor, 1));
    if (fill){
        painter.setBrush(QBrush(penColor));
    }
    getDrawPolygon(&painter);
    QLabel::paintEvent(event);
}

/**
 * @brief init      初始化
 */
void OutputWidget::init()
{
    setStyleSheet("background:rgb(42,43,42)");
    setFixedSize(16,14);
}


/**
 * @brief getDrawPolygon        根据类型画图
 */
void OutputWidget::getDrawPolygon(QPainter* painter)
{
    painter->setRenderHint(QPainter::Antialiasing);
    if (dType== DISPLAY_TYPE::INPUT || dType==DISPLAY_TYPE::OUTPUT)
    {
        QPoint polygon[6];
        polygon[0] = QPoint(0.5*width(), 0.1*height());
        polygon[1] = QPoint(0.9*width(), 0.5*height());
        polygon[2] = QPoint(0.5*width(), 0.9*height());
        polygon[3] = QPoint(0.1*width(), 0.9*height());
        polygon[4] = QPoint(0.1*width(), 0.1*height());
        polygon[5] = QPoint(0.5*width(), 0.1*height());
        painter->drawPolygon(polygon, 6);
    }
    else if (dType == DISPLAY_TYPE::EVENT )
    {
        painter->drawEllipse(QPoint(0.5*height(),0.5*height()), 0.4*height(), 0.4*height());
    }
    else if (dType == DISPLAY_TYPE::FIELD)
    {
        QPoint polygonTr[3];
        polygonTr[0] = QPoint(0.3*width(), 0.1*height());
        polygonTr[1] = QPoint(0.8*width(), 0.5*height());
        polygonTr[2] = QPoint(0.3*width(), 0.9*height());
        painter->drawPolygon(polygonTr, 3);
    }
    else if (dType ==  DISPLAY_TYPE::TARGET)
    {
        painter->drawEllipse(QPoint(0.5*height(),0.5*height()), 0.4*height(), 0.4*height());
        painter->drawEllipse(QPoint(0.5*height(),0.5*height()), 0.25*height(), 0.25*height());
    }
    else if (dType == DISPLAY_TYPE::SIG)
    {
        painter->drawRect(0.1*width(), 0.1*height(), 0.8*width(), 0.8*height());
        painter->drawRect(0.2*width(), 0.2*height(), 0.5*width(), 0.5*height());
        painter->drawRect(0.3*width(), 0.3*height(), 0.2*width(), 0.2*height());
    }
    else if (dType ==  DISPLAY_TYPE::ITEM)
    {
//        QPoint polygonItem[4];
//        polygonItem[0] = QPoint(0.5*width(), 0.1*height());
//        polygonItem[1] = QPoint(0.8*width(), 0.5*height());
//        polygonItem[2] = QPoint(0.5*width(), 0.9*height());
//        polygonItem[3] = QPoint(0.1*width(), 0.5*height());
//        painter->drawPolygon(polygonItem, 4);
        painter->save();
        painter->setPen(QPen(QColor(200,25,24),2));
        painter->drawEllipse(QPoint(0.5*height(),0.5*height()), 0.45*height(), 0.45*height());
        painter->setPen(QPen(QColor(255,126,0),1));
        painter->drawLine(QPoint(0.3*height(),0.5*height()), QPoint(0.75*height(), 0.5*height()));
        painter->drawLine(QPoint(0.5*height(),0.3*height()), QPoint(0.5*height(), 0.75*height()));
        painter->restore();
    }
    else {

    }
}

QColor OutputWidget::getPenColor() const
{
    return penColor;
}

void OutputWidget::setPenColor(const QColor &value)
{
    penColor = value;
}

bool OutputWidget::getFill() const
{
    return fill;
}

void OutputWidget::setFill(bool value)
{
    fill = value;
}



InputField::InputField(FIELD_TYPE type, const QStringList &field, QWidget *parent) :
    QWidget(parent),
    mFields(field),
    dType(type)
{
    init();
}

/**
 * @brief setFieldParam     设置参数
 * @param value
 */
void InputField::setFieldParam(const QStringList &value)
{
    mFields = value;
    if (FIELD_TYPE::CHECKBOX == dType){
        QCheckBox * c = dynamic_cast<QCheckBox*>(widget);
        if (c){
            c->setText(mFields.size()?mFields.at(0):"");
        }
    }else  if (FIELD_TYPE::COMBOBOX == dType){
        QComboBox * c = dynamic_cast<QComboBox*>(widget);
        if (c){
            c->clear();
            c->addItems(mFields);
        }
    }else  if (FIELD_TYPE::LABEL == dType){
        QLabel * c = dynamic_cast<QLabel*>(widget);
        if (c){
             c->setText(mFields.size()?mFields.at(0):"");
        }
    }else  if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * c = dynamic_cast<QLineEdit*>(widget);
        if (c){
             c->setText(mFields.size()?mFields.at(0):"");
        }
    }else{

    }
}

/**
 * @brief getFieldValue
 * @return
 */
QVariant InputField::getFieldValue()
{
    QVariant v;
    if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * lineEdit = dynamic_cast<QLineEdit*>(widget);
        v.setValue(lineEdit->text());
    } else if (FIELD_TYPE::CHECKBOX == dType) {
        QCheckBox * checkBox = dynamic_cast<QCheckBox*>(widget);
        v.setValue(checkBox->isChecked());
    } else if (FIELD_TYPE::COMBOBOX == dType){
        QComboBox * combobox = dynamic_cast<QComboBox*>(widget);
        v.setValue(combobox->currentText());
    } else if (FIELD_TYPE::LABEL == dType){
        QLabel * label = dynamic_cast<QLabel*>(widget);
        v.setValue(label->text());
    }else{

    }
    return v;
}

/**
 * @brief getFieldParam     获取参数
 * @return
 */
QStringList InputField::getFieldParam()
{
    if (FIELD_TYPE::COMBOBOX == dType)
        return mFields;
    else if (FIELD_TYPE::CUSTOM == dType){
        return QStringList();
    }
    else {
        return QStringList()<<((mFields.size()>0)?mFields.at(0):"");
    }
}

/**
 * @brief setWidget     设置显示窗口
 * @param display
 */
void InputField::setWidget(QWidget *display)
{
    if (display)
    {
        layout->removeWidget(widget);
        widget = display;
        layout->addWidget(widget);
        dType = FIELD_TYPE::CUSTOM;
    }
}

/**
 * @brief setReg        设置正则
 * @param reg
 */
void InputField::setReg(QRegExpValidator* reg)
{
    if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * lineeidt = dynamic_cast<QLineEdit*>(widget);
        if (lineeidt){
            lineeidt->setValidator(reg);
        }
    }
}

/**
 * @brief init      初始化
 */
void InputField::init()
{
    layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    createField();
    setLayout(layout);
}

/**
 * @brief createField       创建字段
 */
void InputField::createField()
{
    if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * lineEdit = new QLineEdit(this);
        widget = lineEdit;
        lineEdit->setFixedWidth(60);
        layout->addWidget(lineEdit);
        lineEdit->setText(mFields.size()?mFields.at(0):"");
    } else if (FIELD_TYPE::CHECKBOX == dType) {
        QCheckBox * checkBox = new QCheckBox(this);
        if (mFields.size()){
            checkBox->setText(mFields.at(0));
        }
        widget = checkBox;
        layout->addWidget(checkBox);
    } else if (FIELD_TYPE::COMBOBOX == dType){
        QComboBox * combobox = new QComboBox(this);
        combobox->addItems(mFields);
        widget = combobox;
        combobox->setStyleSheet("QComboBox QAbstractItemView{color: rgb(224,82,22);selection-color:rgb(224,224,224);background:rgb(48,48,48); selection-background-color:rgb(48,48,48)}");
        layout->addWidget(combobox);
    } else if (FIELD_TYPE::LABEL == dType){
        QLabel * label = new QLabel(this);
        if (mFields.size()){
            label->setText(mFields.at(0));
        }
        widget = label;
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignLeft);
        layout->addWidget(label);
    }else{
        widget = new QWidget;
    }
    widget->setStyleSheet("background:rgba(30, 30, 30,0.92); color:rgb(224,224,224); border: 1px solid rgb(42,43,42)");;
}

/**
 * @brief getType       获取类型
 * @return
 */
FIELD_TYPE InputField::getType()
{
    return dType;
}

/**
 * @brief setAlignment      设置布局
 * @param aligment
 */
void InputField::setAlignment(Qt::Alignment aligment)
{

    Qt::LayoutDirection dir = Qt::LeftToRight;
    if (Qt::AlignLeft == aligment){
        dir = Qt::RightToLeft;
    }
    if (FIELD_TYPE::CHECKBOX == dType){
        QCheckBox * c = dynamic_cast<QCheckBox*>(widget);
        if (c){
            c->setLayoutDirection(dir);
        }
    }else  if (FIELD_TYPE::LABEL == dType){
        QLabel * c = dynamic_cast<QLabel*>(widget);
        if (c){
             c->setAlignment(aligment);
        }
    }else  if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * c = dynamic_cast<QLineEdit*>(widget);
        if (c){
             c->setAlignment(aligment);
        }
    }else{

    }
}


OutputField::OutputField(FIELD_TYPE type, const QStringList &field, QWidget *parent) :
    QWidget(parent),
    mFields(field),
    dType(type)
{
    init();
}

/**
 * @brief setFieldParam     设置参数
 * @param value
 */
void OutputField::setFieldParam(const QStringList &value)
{
    mFields = value;
    if (FIELD_TYPE::CHECKBOX == dType){
        QCheckBox * c = dynamic_cast<QCheckBox*>(widget);
        if (c){
            c->setText(mFields.size()?mFields.at(0):"");
        }
    }else  if (FIELD_TYPE::COMBOBOX == dType){
        QComboBox * c = dynamic_cast<QComboBox*>(widget);
        if (c){
            c->clear();
            c->addItems(mFields);
        }
    }else  if (FIELD_TYPE::LABEL == dType){
        QLabel * c = dynamic_cast<QLabel*>(widget);
        if (c){
             c->setText(mFields.size()?mFields.at(0):"");
        }
    }else  if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * c = dynamic_cast<QLineEdit*>(widget);
        if (c){
             c->setText(mFields.size()?mFields.at(0):"");
        }
    }else {

    }
}

/**
 * @brief getFieldParam     获取参数
 * @return
 */
QStringList OutputField::getFieldParam()
{
    if (FIELD_TYPE::COMBOBOX == dType)
        return mFields;
    else if (FIELD_TYPE::CUSTOM == dType) {
        return QStringList();
    }
    else {
        return QStringList()<<((mFields.size()>0)?mFields.at(0):"");
    }
}

/**
 * @brief setWidget     设置显示窗口
 * @param display
 */
void OutputField::setWidget(QWidget *display)
{
    if (display){
        layout->removeWidget(widget);
        widget = display;
        layout->addWidget(display);
        dType = FIELD_TYPE::CUSTOM;
    }
}

/**
 * @brief setReg        设置正则
 * @param reg
 */
void OutputField::setReg(QRegExpValidator* reg)
{
    if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * lineeidt = dynamic_cast<QLineEdit*>(widget);
        if (lineeidt){
            lineeidt->setValidator(reg);
        }
    }
}

/**
 * @brief init      初始化
 */
void OutputField::init()
{
    layout = new QGridLayout(this);
    layout->setMargin(0);
    layout->setContentsMargins(0,0,0,0);
    layout->setSpacing(0);
    createField();
    setLayout(layout);
}

/**
 * @brief createField       创建字段
 */
void OutputField::createField()
{
    if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * lineEdit = new QLineEdit(this);
        widget = lineEdit;
        lineEdit->setFixedWidth(60);
        lineEdit->setText(mFields.size()?mFields.at(0):"");
        layout->addWidget(lineEdit);
    } else if (FIELD_TYPE::CHECKBOX == dType) {
        QCheckBox * checkBox = new QCheckBox(this);
        if (mFields.size()){
            checkBox->setText(mFields.at(0));
        }
        widget = checkBox;
        layout->addWidget(checkBox);
    } else if (FIELD_TYPE::COMBOBOX == dType){
        QComboBox * combobox = new QComboBox(this);
        combobox->addItems(mFields);        
        combobox->setStyleSheet("QComboBox QAbstractItemView{color: rgb(224,82,22);selection-color:rgb(224,224,224);background:rgb(48,48,48); selection-background-color:rgb(48,48,48)}");
        widget = combobox;
        layout->addWidget(combobox);
    } else if (FIELD_TYPE::LABEL == dType){
        QLabel * label = new QLabel(this);
        if (mFields.size()){
            label->setText(mFields.at(0));
        }
        widget = label;
        label->setWordWrap(true);
        label->setAlignment(Qt::AlignLeft);
        layout->addWidget(label);
    }else{
        widget = new QWidget;
    }
    widget->setStyleSheet("background:rgba(30, 30, 30,0.92); color:rgb(224,224,224);border: 1px solid rgb(42,43,42)");
}


/**
 * @brief getType       获取类型
 * @return
 */
FIELD_TYPE OutputField::getType()
{
    return dType;
}

/**
 * @brief setAlignment      设置布局
 * @param aligment
 */
void OutputField::setAlignment(Qt::Alignment aligment)
{
    Qt::LayoutDirection dir = Qt::LeftToRight;
    if (Qt::AlignLeft == aligment){
        dir = Qt::RightToLeft;
    }
    if (FIELD_TYPE::CHECKBOX == dType){
        QCheckBox * c = dynamic_cast<QCheckBox*>(widget);
        if (c){
            c->setLayoutDirection(dir);
        }
    }else  if (FIELD_TYPE::LABEL == dType){
        QLabel * c = dynamic_cast<QLabel*>(widget);
        if (c){
             c->setAlignment(aligment);
        }
    }else  if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * c = dynamic_cast<QLineEdit*>(widget);
        if (c){
             c->setAlignment(aligment);
        }
    }else{

    }
}

/**
 * @brief getFieldValue
 * @return
 */
QVariant OutputField::getFieldValue()
{
    QVariant v;
    if (FIELD_TYPE::LINEEDIT == dType){
        QLineEdit * lineEdit = dynamic_cast<QLineEdit*>(widget);
        v.setValue(lineEdit->text());
    } else if (FIELD_TYPE::CHECKBOX == dType) {
        QCheckBox * checkBox = dynamic_cast<QCheckBox*>(widget);
        v.setValue(checkBox->isChecked());
    } else if (FIELD_TYPE::COMBOBOX == dType){
        QComboBox * combobox = dynamic_cast<QComboBox*>(widget);
        v.setValue(combobox->currentText());
    } else if (FIELD_TYPE::LABEL == dType){
        QLabel * label = dynamic_cast<QLabel*>(widget);
        v.setValue(label->text());
    }else{

    }
    return v;
}


InputMark::InputMark(QGraphicsWidget *parent, Qt::WindowFlags wFlags) :
    QGraphicsProxyWidget(parent, wFlags),
    parent(parent)
{
    init();
}

void InputMark::init()
{
    widget = new InputWidget;
    setWidget(widget);
}

int InputMark::getConnected() const
{
    return connected;
}

void InputMark::setConnected(bool value)
{
    if (value){
        ++connected;
    }else {
        --connected;
    }
    if (connected < 0){
        connected = 0;
    }
    if (connected == 0){
        setFill(false);
    } else {
        setFill(true);
    }
}

/**
 * @brief setType       设置显示类型
 * @param type
 */
void InputMark::setType(DISPLAY_TYPE type)
{
    widget->setType(type);
}

/**
 * @brief getType       获取显示类型
 * @return
 */
DISPLAY_TYPE InputMark::getType()
{
    return widget->getType();
}


/**
 * @brief getFill       是否填满背景
 * @return
 */
bool InputMark::getFill() const
{
    return widget->getFill();
}

void InputMark::setFill(bool value)
{
    widget->setFill(value);
}

QColor InputMark::getPenColor() const
{
    return widget->getPenColor();
}

void InputMark::setPenColor(const QColor &value)
{
    widget->setPenColor(value);
}

QGraphicsWidget *InputMark::getParent() const
{
    return parent;
}

OutputMark::OutputMark(QGraphicsWidget *parent, Qt::WindowFlags wFlags) :
    QGraphicsProxyWidget(parent, wFlags),
    parent(parent)
{
    init();
}

/**
 * @brief init      初始化
 */
void OutputMark::init()
{
    widget = new OutputWidget;
    setWidget(widget);
}

bool OutputMark::getCanConnectMoreLines() const
{
    return canConnectMoreLines;
}

void OutputMark::setCanConnectMoreLines(bool value)
{
    canConnectMoreLines = value;
}

/**
 * @brief setType       设置显示类型
 * @param type
 */
void OutputMark::setType(DISPLAY_TYPE type)
{
    widget->setType(type);
}

/**
 * @brief getType       获取显示类型
 * @return
 */
DISPLAY_TYPE OutputMark::getType()
{
    return widget->getType();
}


/**
 * @brief getFill       是否填满背景
 * @return
 */
bool OutputMark::getFill() const
{
    return widget->getFill();
}

void OutputMark::setFill(bool value)
{
    widget->setFill(value);
}

QColor OutputMark::getPenColor() const
{
    return widget->getPenColor();
}

void OutputMark::setPenColor(const QColor &value)
{
    widget->setPenColor(value);
}

int OutputMark::getConnected() const
{
    return connected;
}

void OutputMark::setConnected(bool value)
{
    if (value){
        ++connected;
    }else {
        --connected;
    }
    if (connected < 0){
        connected = 0;
    }
    if (connected == 0){
        setFill(false);
    } else {
        setFill(true);
    }
}

QGraphicsWidget *OutputMark::getParent() const
{
    return parent;
}
