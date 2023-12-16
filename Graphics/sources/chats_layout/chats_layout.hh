#ifndef __CHATS_LAYOUT_hh__
#define __CHATS_LAYOUT_hh__

#include <QWidget>
#include <QPushButton>
#include <QFileDialog>
#include <QMessageBox>

#include <HICCUPS.hh>

namespace Ui {
class Chats_layout;
}

class Chats_layout : public QWidget {
  Q_OBJECT

public:
  explicit Chats_layout(QWidget *parent = nullptr);
  ~Chats_layout();

  QPushButton* btn_receive;
  QPushButton* btn_load_file;

public slots:
  void set_network(Network::MACAddress &mac, HICCUPS::HICCUPS* wlan_);

private:
  Ui::Chats_layout *ui;
  Network::MACAddress MAC;
  HICCUPS::HICCUPS* hiccups;
  int receive_mod = 1;

private slots:
  void change_mode();
  void load_file();
};

#endif // __CHATS_LAYOUT_hh__
