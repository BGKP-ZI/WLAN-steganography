#include "include/Graphics/chats.hh"
#include "build/.ui/ui_chats.h"

Chats::Chats(QWidget *parent) : QWidget(parent), ui(new Ui::Chats) {
    ui->setupUi(this);
    this->hide();
}

Chats::~Chats() {
    delete ui;
}
