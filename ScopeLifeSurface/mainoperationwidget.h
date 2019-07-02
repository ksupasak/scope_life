#ifndef MAINOPERATIONWIDGET_H
#define MAINOPERATIONWIDGET_H

#include <QWidget>
#include <QCameraImageCapture>
#include <QCameraInfo>
#include <QMediaRecorder>



namespace Ui {
class MainOperationWidget;
}

class MainOperationWidget : public QWidget
{
    Q_OBJECT

public:
    explicit MainOperationWidget(QWidget *parent = nullptr);
    ~MainOperationWidget();
    QCameraInfo defaultCameraInfo;

    void setCamera(const QCameraInfo &cameraInfo);

    void updateCaptureMode();


public slots:
    void updateRecordTime();
    void updateCameraState(QCamera::State state);
    void updateRecorderState(QMediaRecorder::State state);
    void setExposureCompensation(int index);
    void displayRecorderError();
    void displayCameraError();
    void updateCameraDevice(QAction *action);
    void processCapturedImage(int requestId, const QImage &img);

    void capture();

private slots:
    void on_capture_btn_clicked();

private:
    Ui::MainOperationWidget *ui;



    QScopedPointer<QCamera> m_camera;
    QScopedPointer<QCameraImageCapture> m_imageCapture;
    QScopedPointer<QMediaRecorder> m_mediaRecorder;

    QImageEncoderSettings m_imageSettings;
    QAudioEncoderSettings m_audioSettings;
    QVideoEncoderSettings m_videoSettings;
    QString m_videoContainerFormat;
    bool m_isCapturingImage = false;
    bool m_applicationExiting = false;

};

#endif // MAINOPERATIONWIDGET_H
