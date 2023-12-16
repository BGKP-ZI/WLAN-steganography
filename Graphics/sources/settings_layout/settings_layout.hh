#ifndef __SETTINGS_LAYOUT_hh__
#define __SETTINGS_LAYOUT_hh__

#include <QWidget>
#include <QPushButton>
#include <QToolButton>
#include <QMenu>
#include <QDebug>
#include <QAction>

#include <WLAN.hh> 

namespace Ui {
class Settings_layout;
}

class Settings_layout : public QWidget {
  Q_OBJECT

public:
  explicit Settings_layout(QWidget *parent = nullptr);
  ~Settings_layout();

  QToolButton*    btn_interface_list;
  QMenu*          menu_int;
  QList<QAction*>  list_interfaces; 

  void get_all_interfaces(const std::vector<std::string> &interfaces);

private:
  Ui::Settings_layout *ui;
  QString all_interfaces;


};

#endif // SETTINGS_LAYOUT_HH
