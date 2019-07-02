#ifndef MAINOPERATIONLIBRARY_H
#define MAINOPERATIONLIBRARY_H

#include <QWidget>

namespace Ui {
class MainOperationLibrary;
}

class MainOperationLibrary : public QWidget
{
    Q_OBJECT

public:
    explicit MainOperationLibrary(QWidget *parent = nullptr);
    ~MainOperationLibrary();

private:
    Ui::MainOperationLibrary *ui;
};

#endif // MAINOPERATIONLIBRARY_H
