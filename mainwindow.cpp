#include "mainwindow.h"
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , camera(new CCamera)
    , ui(new Ui::MainWindow)
    , timer(new QTimer(this))
{
    ui->setupUi(this);

    //定时一到就更新图像
    connect(timer, &QTimer::timeout, camera, &CCamera::updateFrame);
    // 每隔 30 毫秒更新一次图像
    timer->start(30);

    connect(camera, &CCamera::frameAvailable, this, &MainWindow::onFrameAvailable);

    // 初始化摄像头列表
    updateCameraList();

    setWindowTitle("PCB_Detection");
    QString styleSheet = "QMainWindow::title {"
                         "    background-color: #f0f0f0;"
                         "    color: #333333;"
                         "    padding: 6px;"
                         "    border-top-left-radius: 5px;"
                         "    border-top-right-radius: 5px;"
                         "    font-weight: bold;"
                         "    font-family: Times New Roman;"
                         "}";
    setStyleSheet(styleSheet);
    // 在构造函数中设置 QLabel 的大小策略和缩放模式
    ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
    ui->label->setScaledContents(true);
}

MainWindow::~MainWindow()
{
    delete ui;

}

void MainWindow::onFrameAvailable(const QImage& qImage)
{
    ui->label->setPixmap(QPixmap::fromImage(qImage));
}

void MainWindow::updateCameraList()
{
    QStringList cameraList = camera->getCameraList();
    // 将摄像头列表添加到 comboBox
    ui->comboBox->addItems(cameraList);
}


void MainWindow::on_c_btn_open_clicked()
{
    if (ui->c_btn_open->text() == "打开")
    {
        int camIndex = ui->comboBox->currentIndex();
        camera->openCamera(camIndex);

        if (camera->isCameraOpened())
        {
            ui->c_btn_open->setText("关闭");
        }
    }
    else if (ui->c_btn_open->text() == "关闭")
    {
        camera->closeCamera();
        ui->c_btn_open->setText("打开");
        ui->label->clear();
    }
}

void MainWindow::on_c_btn_flieopen_clicked()
{
    // 选择文件
    QString filepath = QFileDialog::getOpenFileName(this, "选择文件");
    // 判断文件是否为空
    if (!filepath.isEmpty())
    {
        // 找到文件扩展名并全小写
        QFileInfo fileInfo(filepath);
        QString fileExtenion = fileInfo.suffix().toLower();
        // 判断扩展名
        if (fileExtenion == "jpg" || fileExtenion == "png")
        {
            QPixmap image(filepath);
            // 设置标签的大小策略为自适应图像内容
            ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            // 设置标签的缩放选项为保持纵横比并填充整个标签
            ui->label->setScaledContents(true);
            // 在标签中显示图像
            ui->label->setPixmap(image);
        }
        else if (fileExtenion == "mp4" || fileExtenion == "mov")
        {
            QMovie *video = new QMovie(filepath);
            // 设置标签的大小策略为自适应动画内容
            ui->label->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
            // 设置标签的缩放选项为保持纵横比并填充整个标签
            ui->label->setScaledContents(true);
            // 在标签中显示动画
            ui->label->setMovie(video);
            video->start();
        }
    }
}

void MainWindow::on_pushButton_2_clicked()
{
    ui->label->clear();
}

