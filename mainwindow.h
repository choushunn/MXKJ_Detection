#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>
#include <QFileDialog>//>打开失败
#include <QMessageBox>
#include <QMovie>
#include "ccamera.h"
#include "ncnn_export.h"


QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();





private slots:
    void onFrameAvailable(const QImage& qImage);

    void updateCameraList();

    void on_c_btn_open_clicked();

    void on_c_btn_flieopen_clicked();

    void on_pushButton_2_clicked();

private:
    CCamera *camera=nullptr;
    Ui::MainWindow *ui;
    cv::VideoCapture videoCapture;
    QTimer *timer;
    QPixmap *image;
    QMovie *video;
    QDateTime currentDateTime = QDateTime::currentDateTime();
};
#endif // MAINWINDOW_H
