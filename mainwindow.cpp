#include "mainwindow.h"
#include <QGraphicsItemAnimation>
#include <QMouseEvent>
#include <QTimeLine>
#include "./ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    _view = new View();

    QHBoxLayout *layout = new QHBoxLayout(ui->scrollAreaWidgetContents);
    layout->addWidget(_view);
}

MainWindow::~MainWindow()
{
    delete ui;
}
