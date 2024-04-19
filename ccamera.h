#ifndef CCAMERA_H
#define CCAMERA_H

#include <QObject>

class CCamera : public QObject
{
    Q_OBJECT
public:
    explicit CCamera(QObject *parent = nullptr);

signals:
};

#endif // CCAMERA_H
