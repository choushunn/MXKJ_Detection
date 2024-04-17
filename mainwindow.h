#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <opencv2/opencv.hpp>
#include <QTimer>

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
    void updateFrame();

    void updateCameraList();

    void on_c_btn_open_clicked();

private:
    Ui::MainWindow *ui;
    cv::VideoCapture videoCapture;
    QTimer *timer;
};
#endif // MAINWINDOW_H
