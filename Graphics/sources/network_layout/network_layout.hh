#ifndef __NETWORK_LAYOUT_hh_
#define __NETWORK_LAYOUT_hh_

// include QT
#include <QListWidget>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QAction>

//include Network
#include <WLAN.hh>


namespace Ui {
class Network_layout;
}

class Network_layout : public QWidget {
  Q_OBJECT

public:
  explicit Network_layout(QWidget *parent = nullptr);
  ~Network_layout();

  QPushButton* btn_connect;

public slots:
  void set_wlan(QAction *action);

private slots:
  void show_all_address();
  void address_pressed(QListWidgetItem *item);
  void test();

private:
  Ui::Network_layout *ui;
  Network::WLAN* wlan = nullptr;
  QStringList address_list;
};

#endif // __NETWORK_LAYOUT_hh_
