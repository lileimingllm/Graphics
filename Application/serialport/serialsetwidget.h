#ifndef SERIALSETWIDGET_H
#define SERIALSETWIDGET_H
#include <QSerialPortInfo>
#include <QWidget>
#include <QSerialPort>

/**
 *  the class SerialSetWidget  串口设置
 * @author 毛三
 */
namespace Ui {
class SerialSetWidget;
}

class SerialSetWidget : public QWidget
{
    Q_OBJECT

public:
    explicit SerialSetWidget(QWidget *parent = 0);
    ~SerialSetWidget();

private slots:
    /**
     * @brief on_pB_Open_clicked       打开串口
     */
    void on_pB_Open_clicked();

private:
    Ui::SerialSetWidget *ui;

    QSerialPort port;   //串口
    /**
     * @brief init      初始化
     */
    void init();

    /**
     * @brief openSerialPort            打开串口
     */
    void openSerialPort();

    /**
     * @brief closeSerialPort           关闭串口
     */
    void closeSerialPort();
};

#endif // SERIALSETWIDGET_H
