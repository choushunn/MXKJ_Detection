#include "ccamera.h"

CCamera::CCamera(QObject *parent)
    : QObject{parent}
{}


QImage CCamera::convertToQImage(const cv::Mat& frame)
{
    QImage qImage(frame.data, frame.cols, frame.rows, frame.step, QImage::Format_RGB888);
    return qImage.rgbSwapped();
}

void CCamera::updateFrame()
{
    cv::Mat frame;
    // 从摄像头读取一帧图像
    videoCapture >> frame;
    if (!frame.empty())
    {
        // 将 OpenCV 的图像转换为 Qt 的图像格式
        QImage qImage = convertToQImage(frame);
        // 处理图像的逻辑

        // 发出非空指令给主窗口
        emit frameAvailable(qImage);
    }
}

QStringList CCamera::getCameraList()
{
    QStringList cameraList;
    int camIndex = 0;
    cv::VideoCapture videoCapture;

    while (true)
    {
        videoCapture.open(camIndex);
        if (!videoCapture.isOpened())
        {
            break;
        }

        QString cameraName = QString("Camera %1").arg(camIndex);
        qDebug() << "Camera Name: " << cameraName;
        cameraList.append(cameraName);

        videoCapture.release();
        camIndex++;
    }

    return cameraList;
}

void CCamera::openCamera(int camIndex)
{
    // 打开所选摄像头
    videoCapture.open(camIndex);
}

void CCamera::closeCamera()
{
        // 关闭视频
        videoCapture.release();
}


bool CCamera::isCameraOpened() const
{
    return cameraOpened;
}
