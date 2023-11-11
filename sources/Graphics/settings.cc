#include "Graphics/settings.hh"
#include "../../include/Graphics/moc_settings.cpp"
#include "../../include/Graphics/ui_settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent), ui(new Ui::Settings) {
  ui->setupUi(this);
  this->hide();
}

Settings::~Settings() { delete ui; }
