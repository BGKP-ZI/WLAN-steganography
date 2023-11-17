#ifndef __MAINWINDOW_hh_
#define __MAINWINDOW_hh_

#include <QMainWindow>
#include <QWidget>
#include <QtGui>
#include <QVBoxLayout>

#include "Graphics/chats_layout.hh"
#include "Graphics/network_layout.hh"
#include "Graphics/settings_layout.hh"

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
  Chats_layout *chats_layout;
  Network_layout *network_layout;
  Settings_layout *settings_layout;

private slots:
  void void_slot();
  void run_chats();
  void run_network();
  void run_settings();

  void test_slot();
};
#endif // __MAINWINDOW_hh_
