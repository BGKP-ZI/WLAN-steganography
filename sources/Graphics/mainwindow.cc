#include "include/Graphics/mainwindow.hh"
#include "build/.ui/ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)    : QMainWindow(parent), ui(new Ui::MainWindow) {
    ui->setupUi(this);
}

MainWindow::~MainWindow() {
    delete ui;
}

