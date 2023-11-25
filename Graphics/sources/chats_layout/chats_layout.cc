#include "chats_layout.hh"

#include "moc_chats_layout.cpp"
#include "ui_chats_layout.h"

Chats_layout::Chats_layout(QWidget *parent) : QWidget(parent), ui(new Ui::Chats_layout) {
  ui->setupUi(this);
  hide();
}

Chats_layout::~Chats_layout() { 
  delete ui; 
}