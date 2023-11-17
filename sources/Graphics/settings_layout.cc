#include "Graphics/settings_layout.hh"
#include "../../include/Graphics/moc_settings_layout.cpp"
#include "../../include/Graphics/ui_settings_layout.h"

Settings_layout::Settings_layout(QWidget *parent) : QWidget(parent), ui(new Ui::Settings_layout) {
  ui->setupUi(this);
  hide();
}

Settings_layout::~Settings_layout() { 
  delete ui; 
}
