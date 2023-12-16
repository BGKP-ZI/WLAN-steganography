#include "settings_layout.hh"

#include "moc_settings_layout.cpp"
#include "ui_settings_layout.h"

Settings_layout::Settings_layout(QWidget *parent) : QWidget(parent), ui(new Ui::Settings_layout) {
  ui->setupUi(this);
  hide();

  // set btn for choose interface
  btn_interface_list = new QToolButton(this);
  menu_int = new QMenu(btn_interface_list);
  btn_interface_list->setMenu(menu_int);
  btn_interface_list->setText(tr("Chose interface"));
  btn_interface_list->setPopupMode(QToolButton::InstantPopup);
  ui->gridLayout->addWidget(btn_interface_list, 0, 0);
}

Settings_layout::~Settings_layout() { 
  for(int i = 0; i < list_interfaces.size(); ++i) {
    delete list_interfaces[i];
  }

  delete menu_int;
  delete btn_interface_list;
  delete ui; 
}

void Settings_layout::get_all_interfaces(const std::vector<std::string> &interfaces) {
  for(int i = 0; i < interfaces.size(); ++i) {
    list_interfaces.append(new QAction(QString::fromStdString(interfaces[i]), this));
  }
  menu_int->addActions(list_interfaces);
}
