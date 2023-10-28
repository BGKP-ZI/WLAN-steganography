#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtGui>
#include <QWidget>
#include <QToolBar>

#define APP_NAME "WLAN-steganography"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    void setup_ToolBar();
    void setup_MainWindow();


    Ui::MainWindow *ui;

    QAction* close_act;

private slots:
    void void_slot();
    void run_chats();
    void run_network();
    void run_settings();

    void test_slot();
};
#endif // MAINWINDOW_H
