#include "include/Graphics/settings.hh"
#include "build/.ui/ui_settings.h"

Settings::Settings(QWidget *parent) : QWidget(parent), ui(new Ui::Settings) {
    ui->setupUi(this);
    this->hide();
}

Settings::~Settings() {
    delete ui;
}
