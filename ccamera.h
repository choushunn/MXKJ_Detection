#ifndef CCAMERA_H
#define CCAMERA_H

#include "qdatetime.h"
#include <QObject>
#include <opencv2/opencv.hpp>
#include <QImage>
#include <QDebug>
#include <QTimer>

class CCamera : public QObject
{
    Q_OBJECT


public:
    explicit CCamera(QObject *parent = nullptr);
    void updateFrame();
    QStringList getCameraList();
    bool isCameraOpened() const;
    QString getTimestamp() const;
    void openCamera(int camIndex);
    void closeCamera();




private slots:




private:
    cv::VideoCapture videoCapture;
    bool cameraOpened;
    QDateTime currentDateTime = QDateTime::currentDateTime();
    int camIndex = 0;
    QImage convertToQImage(const cv::Mat &frame);
signals:
    void frameAvailable(const QImage& qImage);
};

#endif // CCAMERA_H
