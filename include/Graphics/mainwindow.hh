#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QWidget>
#include <QtGui>

#include "Graphics/chats.hh"
#include "Graphics/network.hh"
#include "Graphics/settings.hh"

#define APP_NAME "WLAN-steganography"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
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
  Chats *chats_layout;
  Network *network_layout;
  Settings *settings_layout;

private slots:
  void void_slot();
  void run_chats();
  void run_network();
  void run_settings();

  void test_slot();
};
#endif // MAINWINDOW_H
