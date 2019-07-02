#include "mainoperationwidget.h"
#include "ui_mainoperationwidget.h"
#include <QMessageBox>

#include <QMediaMetaData>
MainOperationWidget::MainOperationWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainOperationWidget)
{
    ui->setupUi(this);



    // init camera

    const QList<QCameraInfo> availableCameras = QCameraInfo::availableCameras();

    QCameraInfo last;
    qDebug()<< "Number of Camera : "<< availableCameras.length();

    for (const QCameraInfo &cameraInfo : availableCameras) {

        qDebug()<< "Camera : "<< cameraInfo.description();

//        QAction *videoDeviceAction = new QAction(cameraInfo.description(), videoDevicesGroup);
//        videoDeviceAction->setCheckable(true);
//        videoDeviceAction->setData(QVariant::fromValue(cameraInfo));
        if (cameraInfo == QCameraInfo::defaultCamera()){

            defaultCameraInfo = cameraInfo;

        }

        last = cameraInfo;
//            videoDeviceAction->setChecked(true);

//        ui->menuDevices->addAction(videoDeviceAction);
    }

    qDebug()<< "Camera Default : "<< defaultCameraInfo.description();

//    setCamera(QCameraInfo::defaultCamera());
       setCamera(availableCameras.at(0));


}

MainOperationWidget::~MainOperationWidget()
{
    delete ui;
}


void MainOperationWidget::setCamera(const QCameraInfo &cameraInfo)
{
    m_camera.reset(new QCamera(cameraInfo));

    connect(m_camera.data(), &QCamera::stateChanged, this, &MainOperationWidget::updateCameraState);
    connect(m_camera.data(), QOverload<QCamera::Error>::of(&QCamera::error), this, &MainOperationWidget::displayCameraError);

    m_mediaRecorder.reset(new QMediaRecorder(m_camera.data()));
    connect(m_mediaRecorder.data(), &QMediaRecorder::stateChanged, this, &MainOperationWidget::updateRecorderState);

    m_imageCapture.reset(new QCameraImageCapture(m_camera.data()));

    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &MainOperationWidget::updateRecordTime);
    connect(m_mediaRecorder.data(), QOverload<QMediaRecorder::Error>::of(&QMediaRecorder::error),
            this, &MainOperationWidget::displayRecorderError);

    m_mediaRecorder->setMetaData(QMediaMetaData::Title, QVariant(QLatin1String("Test Title")));

//    connect(ui->exposureCompensation, &QAbstractSlider::valueChanged, this, &MainWindow::setExposureCompensation);

    m_camera->setViewfinder(ui->live);

    updateCameraState(m_camera->state());
//    updateLockStatus(m_camera->lockStatus(), QCamera::UserRequest);
    updateRecorderState(m_mediaRecorder->state());

//    connect(m_imageCapture.data(), &QCameraImageCapture::readyForCaptureChanged, this, &MainWindow::readyForCapture);
    connect(m_imageCapture.data(), &QCameraImageCapture::imageCaptured, this, &MainOperationWidget::processCapturedImage);
//    connect(m_imageCapture.data(), &QCameraImageCapture::imageSaved, this, &MainWindow::imageSaved);
//    connect(m_imageCapture.data(), QOverload<int, QCameraImageCapture::Error, const QString &>::of(&QCameraImageCapture::error),
//            this, &MainWindow::displayCaptureError);

//    connect(m_camera.data(), QOverload<QCamera::LockStatus, QCamera::LockChangeReason>::of(&QCamera::lockStatusChanged),
//            this, &MainWindow::updateLockStatus);

//    ui->captureWidget->setTabEnabled(0, (m_camera->isCaptureModeSupported(QCamera::CaptureStillImage)));
//    ui->captureWidget->setTabEnabled(1, (m_camera->isCaptureModeSupported(QCamera::CaptureVideo)));

    updateCaptureMode();

    m_camera->start();
}



void MainOperationWidget::updateCameraState(QCamera::State state)
{
//    switch (state) {
//    case QCamera::ActiveState:
//        ui->actionStartCamera->setEnabled(false);
//        ui->actionStopCamera->setEnabled(true);
//        ui->captureWidget->setEnabled(true);
//        ui->actionSettings->setEnabled(true);
//        break;
//    case QCamera::UnloadedState:
//    case QCamera::LoadedState:
//        ui->actionStartCamera->setEnabled(true);
//        ui->actionStopCamera->setEnabled(false);
//        ui->captureWidget->setEnabled(false);
//        ui->actionSettings->setEnabled(false);
//    }
}

void MainOperationWidget::updateRecorderState(QMediaRecorder::State state)
{
//    switch (state) {
//    case QMediaRecorder::StoppedState:
//        ui->recordButton->setEnabled(true);
//        ui->pauseButton->setEnabled(true);
//        ui->stopButton->setEnabled(false);
//        break;
//    case QMediaRecorder::PausedState:
//        ui->recordButton->setEnabled(true);
//        ui->pauseButton->setEnabled(false);
//        ui->stopButton->setEnabled(true);
//        break;
//    case QMediaRecorder::RecordingState:
//        ui->recordButton->setEnabled(false);
//        ui->pauseButton->setEnabled(true);
//        ui->stopButton->setEnabled(true);
//        break;
//    }
}

void MainOperationWidget::setExposureCompensation(int index)
{
    m_camera->exposure()->setExposureCompensation(index*0.5);
}

void MainOperationWidget::displayRecorderError()
{
    QMessageBox::warning(this, tr("Capture Error"), m_mediaRecorder->errorString());
}

void MainOperationWidget::displayCameraError()
{
    QMessageBox::warning(this, tr("Camera Error"), m_camera->errorString());
}

void MainOperationWidget::updateCameraDevice(QAction *action)
{
//    setCamera(qvariant_cast<QCameraInfo>(action->data()));
}
void MainOperationWidget::updateRecordTime()
{
    QString str = QString("Recorded %1 sec").arg(m_mediaRecorder->duration()/1000);
//    ui->statusbar->showMessage(str);
}

void MainOperationWidget::updateCaptureMode()
{
//    int tabIndex = ui->captureWidget->currentIndex();
    int tabIndex = 0;
    QCamera::CaptureModes captureMode = tabIndex == 0 ? QCamera::CaptureStillImage : QCamera::CaptureVideo;

    if (m_camera->isCaptureModeSupported(captureMode))
        m_camera->setCaptureMode(captureMode);
}

void MainOperationWidget::on_capture_btn_clicked()
{
    m_imageCapture->capture();
}
void MainOperationWidget::processCapturedImage(int requestId, const QImage& img)
{
    Q_UNUSED(requestId);

    QImage scaledImage = img.scaled(ui->preview->size(),
                                    Qt::KeepAspectRatio,
                                    Qt::SmoothTransformation);

    ui->preview->setPixmap(QPixmap::fromImage(scaledImage));

    // Display captured image for 4 seconds.
//    displayCapturedImage();
//    QTimer::singleShot(4000, this, &Camera::displayViewfinder);

}

void MainOperationWidget::capture()
{
     m_imageCapture->capture();
}
