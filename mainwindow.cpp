#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // //打开摄像头
    // videoCapture.open(0);

    // 创建定时器，用于定时更新图像
    timer = new QTimer(this);
    //定时一到就更新图像
    connect(timer, SIGNAL(timeout()), this, SLOT(updateFrame()));
    // 每隔 30 毫秒更新一次图像
    timer->start(30);

    // 初始化摄像头列表
    updateCameraList();

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::updateFrame()
{
    cv::Mat frame;
    // 从摄像头读取一帧图像
    videoCapture >> frame;

    if (!frame.empty()) {
        // 将 OpenCV 的图像转换为 Qt 的图像格式
        QImage qImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
        qImage = qImage.rgbSwapped();

        // 在 QLabel 上显示图像
        ui->label->setPixmap(QPixmap::fromImage(qImage).scaled(ui->label->size(), Qt::KeepAspectRatio));
    }
}

void MainWindow::updateCameraList()
{
    //清空相机列表
    ui->comboBox->clear();
    //定义摄像头数量变量
    int Camnums = 0;
    // 假设最多有10个摄像头
    for (int i = 0; i < 10; i++)
    {
        cv::VideoCapture videoCapture;
        videoCapture.open(i);
        if (!videoCapture.isOpened())
        {
            break;
        }
        Camnums++;
        videoCapture.release();
    }
    // 添加识别到的摄像头到 ComboBox
    for (int i = 0; i < Camnums; i++) {
        QString cameraName = QString("Camera %1").arg(i);
        // 打印出可用相机
        qDebug() << "Camera Name: " << cameraName;
        ui->comboBox->addItem(cameraName, i);
    }


}



void MainWindow::on_c_btn_open_clicked()
{
    if (ui->c_btn_open->text() == "打开")
    {
        // 找到所选的摄像头
        int camIndex = ui->comboBox->currentIndex();
        videoCapture.open(camIndex);
        if (!videoCapture.isOpened())
        {
            qDebug() << "打开失败";
        }
        else
        {
            ui->c_btn_open->setText("关闭");
            // 停止定时器
            timer->stop();
            // 更新图像
            updateFrame();
            // 开启定时器，刷新图像
            timer->start();
        }
    }
    else if (ui->c_btn_open->text() == "关闭")
    {
        ui->c_btn_open->setText("打开");
        ui->label->clear(); // 清除图像显示
        videoCapture.release();
    }

}

