#include "serialsetwidget.h"
#include "ui_serialsetwidget.h"
#include <QMessageBox>

SerialSetWidget::SerialSetWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::SerialSetWidget)
{
    ui->setupUi(this);
    init();
}

SerialSetWidget::~SerialSetWidget()
{
    delete ui;
}

/**
 * @brief init      初始化
 */
void SerialSetWidget::init()
{
    QList<QSerialPortInfo> info = QSerialPortInfo::availablePorts();
    QStringList portName;
    for (QSerialPortInfo i: info){
        portName.append(i.portName());
    }
    ui->cB_PortName->addItems(portName);
}

/**
 * @brief openSerialPort            打开串口
 */
void SerialSetWidget::openSerialPort()
{
    port.close();
    port.clear();
    QString portName = ui->cB_PortName->currentText();
    QString buadrate = ui->cB_BuandRate->currentText();
    QString databit = ui->cB_DataBits->currentText();
    QString stopbit = ui->cB_StopBits->currentText();
    int verifytype = ui->cB_VirifyT->currentIndex();
    if (portName.isEmpty()){
        QMessageBox::warning(NULL, "警告","串口不存在，打开失败!");
        return;
    }
    port.setPortName(portName);
    //设置波特率
    bool ok;
    port.setBaudRate(buadrate.toUInt(&ok));
    port.setDataBits(QSerialPort::DataBits(databit.toUInt(&ok)));
    if ("1.5"==stopbit)
    {
        port.setStopBits(QSerialPort::OneAndHalfStop);
    }else if ("1"==stopbit)
    {
        port.setStopBits(QSerialPort::OneStop);
    }else
    {
        port.setStopBits(QSerialPort::TwoStop);
    }
    //设置校验
    if (0!=verifytype){
        port.setParity(QSerialPort::Parity(verifytype+1));
    }else{
        port.setParity(QSerialPort::NoParity);
    }
    if (port.open(QSerialPort::ReadWrite)){
        ui->pB_Open->setText("关闭");
    }else{
        QMessageBox::warning(NULL, "警告","打开串口失败!");
    }
}

/**
 * @brief closeSerialPort           关闭串口
 */
void SerialSetWidget::closeSerialPort()
{
    if (port.isOpen()){
        port.close();
    }
    port.clear();
    ui->pB_Open->setText("打开");
}

/**
 * @brief SerialSetWidget::on_pB_Open_clicked       打开串口
 */
void SerialSetWidget::on_pB_Open_clicked()
{
    if ("打开" == ui->pB_Open->text()) {
        this->openSerialPort();
    }else{
        this->closeSerialPort();
    }
}
