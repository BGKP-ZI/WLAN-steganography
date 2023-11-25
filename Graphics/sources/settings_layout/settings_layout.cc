#include "settings_layout.hh"
#include "moc_settings_layout.cpp"
#include "ui_settings_layout.h"

Settings_layout::Settings_layout(QWidget *parent) : QWidget(parent), ui(new Ui::Settings_layout) {
  ui->setupUi(this);
  hide();
}

Settings_layout::~Settings_layout() { 
  delete ui; 
}
