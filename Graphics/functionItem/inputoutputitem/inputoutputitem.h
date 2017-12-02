#ifndef INPUTITEM_H
#define INPUTITEM_H

#include <QGraphicsWidget>
#include <QGraphicsLinearLayout>
#include <QLabel>
#include <QGraphicsProxyWidget>
#include <QLineEdit>
#include <QComboBox>
#include <QCheckBox>
#include <QGridLayout>
#include <QMouseEvent>

class QPaintEvent;
class InputField;
class OutputField;
enum class FIELD_TYPE;
class InputMark;
class OutputMark;

/**
 * @brief The InputItem class    输入项
 * @author 毛三
 */
class InputItem : public QGraphicsWidget
{
public:
    InputItem(FIELD_TYPE type, QStringList fieldParam, QGraphicsWidget *parent, Qt::WindowFlags wFlags = Qt::WindowFlags());

    QGraphicsWidget *getParent() const;

    InputField *getField();

    /**
     * @brief setWidget     设置窗口
     * @param widget
     */
    void setWidget(QWidget * widget);

    FIELD_TYPE getFieldType();

    QStringList getFieldParam();
    void setFieldParam(const QStringList &value);

    InputMark *getMark() const;

protected:

    /**
     * @brief init      初始化
     */
    void init(FIELD_TYPE type);

    QGraphicsLinearLayout * layout { nullptr }; //布局管理器

    InputField * mFieldParam{ nullptr };

    /**
      * @brief mouseMoveEvent      屏蔽鼠标
      * @param event
      */
    void mousePressEvent(QGraphicsSceneMouseEvent* event);

private:
    QGraphicsWidget * parent{ nullptr };    //父级窗口

    QStringList fieldParam;        //字段参数

    InputMark * mark { nullptr  };
};


class OutputItem : public QGraphicsWidget
{
public:
    OutputItem(FIELD_TYPE type, QStringList fieldParam, QGraphicsWidget *parent, Qt::WindowFlags wFlags = Qt::WindowFlags());

    QGraphicsWidget *getParent() const;

    /**
     * @brief setWidget     设置显示窗口
     * @param display
     */
    void setWidget(QWidget* display);

    OutputField* getField() const;

    QStringList getFieldParam();
    void setFieldParam(const QStringList &value);

    OutputMark *getMark() const;

protected:

    /**
     * @brief init      初始化
     */
    void init(FIELD_TYPE type);

    QGraphicsLinearLayout * layout { nullptr }; //布局管理器

    OutputField * mFieldParam{ nullptr };

    /**
      * @brief mouseMoveEvent      屏蔽鼠标
      * @param event
      */
     void mousePressEvent(QGraphicsSceneMouseEvent* event);

     QStringList fieldParam;        //字段参数
private:
     QGraphicsWidget * parent{ nullptr };    //父级窗口
     OutputMark * mark{ nullptr };
};


/**
 * @brief The DISPLAY_TYPE enum     inputwidgetm outputwidget的显示图形
 */
enum class DISPLAY_TYPE {
    INPUT,
    OUTPUT,
    EVENT,
    FIELD,
    TARGET,
    SIG,
    ITEM
};

class InputWidget : public QLabel
{
public:
    InputWidget(QWidget* parent=nullptr);

    /**
     * @brief setType       设置显示类型
     * @param type
     */
    void setType(DISPLAY_TYPE type);

    /**
     * @brief getType       获取显示类型
     * @return
     */
    DISPLAY_TYPE getType();

    /**
     * @brief getFill       是否填满背景
     * @return
     */
    bool getFill() const;
    void setFill(bool value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

protected:
    /**
     * @brief paintEvent        绘图事件
     * @param event
     */
    void paintEvent(QPaintEvent * event);

private:

    /**
     * @brief init      初始化
     */
    void init();

    /**
     * @brief getDrawPolygon        根据类型画图
     */
    void getDrawPolygon(QPainter *painter);

    QColor penColor{0, 153, 153};

    DISPLAY_TYPE dType { DISPLAY_TYPE::INPUT };  //显示类型
    bool fill { false };    //是否填满背景
};

/**
 * @brief The FIELD_TYPE enum   字段的样式
 */
enum class FIELD_TYPE{
    LINEEDIT,
    COMBOBOX,
    CHECKBOX,
    LABEL,
    CUSTOM
};

class InputField : public QWidget
{
public:
    InputField(FIELD_TYPE type, const QStringList& field = QStringList(),QWidget* parent = nullptr);

    /**
     * @brief setFieldParam     设置参数
     * @param value
     */
    void setFieldParam(const QStringList& value);

    /**
     * @brief getFieldParam     获取参数
     * @return
     */
    QStringList getFieldParam();

    /**
     * @brief setWidget     设置显示窗口
     * @param display
     */
    void setWidget(QWidget * display);

    /**
     * @brief setReg        设置正则
     * @param reg
     */
    void setReg(QRegExpValidator *reg);

    /**
     * @brief getType       获取类型
     * @return
     */
    FIELD_TYPE getType();

    /**
     * @brief setAlignment      设置布局
     * @param aligment
     */
    void setAlignment(Qt::Alignment aligment);

    /**
     * @brief getFieldValue
     * @return
     */
    QVariant getFieldValue();

private:
    /**
     * @brief init      初始化
     */
    void init();

    /**
     * @brief createField       创建字段
     */
    void createField();

    QGridLayout * layout { nullptr };       //布局管理器

    FIELD_TYPE dType{ FIELD_TYPE::LABEL };   //字段样式

    QStringList mFields;     //字段内容
    QWidget * widget { nullptr };
};

class InputMark : public QGraphicsProxyWidget
{
    Q_OBJECT
public :
    InputMark(QGraphicsWidget *parent, Qt::WindowFlags wFlags = Qt::WindowFlags());

    QGraphicsWidget *getParent() const;

    int getConnected() const;
    void setConnected(bool value);

    bool getCanConnectMoreLines() const;
    void setCanConnectMoreLines(bool value);


    /**
     * @brief setType       设置显示类型
     * @param type
     */
    void setType(DISPLAY_TYPE type);

    /**
     * @brief getType       获取显示类型
     * @return
     */
    DISPLAY_TYPE getType();

    /**
     * @brief getFill       是否填满背景
     * @return
     */
    bool getFill() const;
    void setFill(bool value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

private:
    /**
     * @brief init  初始化
     */
    void init();

    QGraphicsWidget * parent{ nullptr };    //父级窗口

    int connected{ 0 }; //是否已经连接

    InputWidget * widget { nullptr };       //显示窗口
};

class OutputWidget : public QLabel
{
public:
    OutputWidget(QWidget* parent=nullptr);

    /**
     * @brief setType       设置显示类型
     * @param type
     */
    void setType(DISPLAY_TYPE type);

    /**
     * @brief getType       获取显示类型
     * @return
     */
    DISPLAY_TYPE getType();

    /**
     * @brief getFill       是否填满背景
     * @return
     */
    bool getFill() const;
    void setFill(bool value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

protected:
    /**
     * @brief paintEvent        绘图事件
     * @param event
     */
    void paintEvent(QPaintEvent * event);

private:

    /**
     * @brief init      初始化
     */
    void init();

    /**
     * @brief getDrawPolygon        根据类型画图
     */
    void getDrawPolygon(QPainter *painter);

    QColor penColor{255, 126, 0};

    DISPLAY_TYPE dType { DISPLAY_TYPE::OUTPUT };  //显示类型
    bool fill { false };    //是否填满背景

};

class OutputField : public QWidget
{
public:
    OutputField(FIELD_TYPE type, const QStringList& field = QStringList(),QWidget* parent = nullptr);

    /**
     * @brief setFieldParam     设置参数
     * @param value
     */
    void setFieldParam(const QStringList& value);

    /**
     * @brief getFieldParam     获取参数
     * @return
     */
    QStringList getFieldParam();

    /**
     * @brief setWidget     设置显示窗口
     * @param display
     */
    void setWidget(QWidget* display);

    /**
     * @brief setReg        设置正则
     * @param reg
     */
    void setReg(QRegExpValidator *reg);

    FIELD_TYPE getType();

    /**
     * @brief setAlignment      设置布局
     * @param aligment
     */
    void setAlignment(Qt::Alignment aligment);

    /**
     * @brief getFieldValue
     * @return
     */
    QVariant getFieldValue();

private:
    /**
     * @brief init      初始化
     */
    void init();

    /**
     * @brief createField       创建字段
     */
    void createField();

    QGridLayout * layout { nullptr };       //布局管理器

    FIELD_TYPE dType{ FIELD_TYPE::LABEL };   //字段样式

    QStringList mFields;     //字段内容
    QWidget * widget { nullptr };
};


class OutputMark : public QGraphicsProxyWidget
{
    Q_OBJECT
public:
    OutputMark(QGraphicsWidget *parent, Qt::WindowFlags wFlags = Qt::WindowFlags());

    QGraphicsWidget *getParent() const;

    int getConnected() const;
    void setConnected(bool value);

    bool getCanConnectMoreLines() const;
    void setCanConnectMoreLines(bool value);

    /**
     * @brief setType       设置显示类型
     * @param type
     */
    void setType(DISPLAY_TYPE type);

    /**
     * @brief getType       获取显示类型
     * @return
     */
    DISPLAY_TYPE getType();

    /**
     * @brief getFill       是否填满背景
     * @return
     */
    bool getFill() const;
    void setFill(bool value);

    QColor getPenColor() const;
    void setPenColor(const QColor &value);

private:
    /**
     * @brief init      初始化
     */
    void init();

    QGraphicsWidget * parent{ nullptr };    //父级窗口

    int connected { 0 };       //是否已经连接

    bool canConnectMoreLines{false};            //能连接多条线

    OutputWidget * widget { nullptr } ; //显示窗口
};

#endif // INPUTITEM_H
