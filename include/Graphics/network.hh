#ifndef NETWORK_H
#define NETWORK_H

#include <QListWidget>
#include <QWidget>

namespace Ui {
class Network;
}

class Network : public QWidget {
  Q_OBJECT

public:
  explicit Network(QWidget *parent = nullptr);
  ~Network();

private slots:
  void show_all_address();
  void address_pressed(QListWidgetItem *item);
  void test();

private:
  Ui::Network *ui;

  QStringList address_list;
};

#endif // NETWORK_H
