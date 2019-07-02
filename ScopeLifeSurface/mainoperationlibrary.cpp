#include "mainoperationlibrary.h"
#include "ui_mainoperationlibrary.h"

MainOperationLibrary::MainOperationLibrary(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::MainOperationLibrary)
{
    ui->setupUi(this);
}

MainOperationLibrary::~MainOperationLibrary()
{
    delete ui;
}
