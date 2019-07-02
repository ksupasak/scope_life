#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "mainoperationwidget.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

//    ESMBoxConfig *config = ui->main_panel;

    operation_controller = ui->operation_controller;

    connect(ui->actionCapture, &QAction::triggered,  operation_controller, &MainOperationWidget::capture);

//    connect(m_mediaRecorder.data(), &QMediaRecorder::durationChanged, this, &MainOperationWidget::updateRecordTime);


}

MainWindow::~MainWindow()
{
    delete ui;
}
