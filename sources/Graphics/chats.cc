#include <Graphics/chats.hh>

// #include <ui_chats.h>
// #include <moc_chats.cpp>

#include "../../include/Graphics/moc_chats.cpp"
#include "../../include/Graphics/ui_chats.h"

Chats::Chats(QWidget *parent) : QWidget(parent), ui(new Ui::Chats) {
  ui->setupUi(this);
  this->hide();
}

Chats::~Chats() { delete ui; }