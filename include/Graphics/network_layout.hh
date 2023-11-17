#ifndef __NETWORK_LAYOUT_hh_
#define __NETWORK_LAYOUT_hh_

#include <QListWidget>
#include <QWidget>

namespace Ui {
class Network_layout;
}

class Network_layout : public QWidget {
  Q_OBJECT

public:
  explicit Network_layout(QWidget *parent = nullptr);
  ~Network_layout();

private slots:
  void show_all_address();
  void address_pressed(QListWidgetItem *item);
  void test();

private:
  Ui::Network_layout *ui;

  QStringList address_list;
};

#endif // __NETWORK_LAYOUT_hh_
