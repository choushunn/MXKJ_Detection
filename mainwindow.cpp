#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    //初始化串口信息
    updateSerialPortList();

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::updateSerialPortList()
{
    //清空列表中的内容
    ui->m_SPcombobox->clear();

    //查找现有能使用的串口
    const auto infos=QSerialPortInfo::availablePorts();
    //添加串口信息进入列表中
    for (const QSerialPortInfo &info : infos)
    {
        ui->m_SPcombobox->addItem(info.portName() + ":" + info.description());
    }


}

void MainWindow::on_c_openSPBtn_clicked()
{
    //获取当前的串口信息
    QString portName = ui->m_SPcombobox->currentText().split(":").first().trimmed();

    // 根据串口名创建串口对象
    serial.setPortName(portName);
    serial.setBaudRate(115200);

    //打开串口
    if(!serial.open(QIODevice::ReadWrite))

}

