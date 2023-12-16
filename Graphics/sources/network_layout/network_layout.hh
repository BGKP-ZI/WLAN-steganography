#ifndef __NETWORK_LAYOUT_hh_
#define __NETWORK_LAYOUT_hh_

// include QT
#include <QListWidget>
#include <QWidget>
#include <QPushButton>
#include <QDebug>
#include <QAction>
#include <QListWidget>
#include <QMessageBox>

//include Network
#include <HICCUPS.hh>


namespace Ui {
class Network_layout;
}

class Network_layout : public QWidget {
  Q_OBJECT

public:
  explicit Network_layout(QWidget *parent = nullptr);
  ~Network_layout();

  QPushButton* btn_connect;
  QListWidget* addres_listWidget;

public slots:
  void set_wlan(HICCUPS::HICCUPS *wlan_);

private slots:
  void show_all_address();
  void test();

private:
  Ui::Network_layout *ui;
  HICCUPS::HICCUPS* wlan;
  QStringList address_list;
};

#endif // __NETWORK_LAYOUT_hh_