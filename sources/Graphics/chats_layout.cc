#include <Graphics/chats_layout.hh>

// #include <ui_chats.h>
// #include <moc_chats.cpp>

#include "../../include/Graphics/moc_chats_layout.cpp"
#include "../../include/Graphics/ui_chats_layout.h"

Chats_layout::Chats_layout(QWidget *parent) : QWidget(parent), ui(new Ui::Chats_layout) {
  ui->setupUi(this);
  hide();
}

Chats_layout::~Chats_layout() { 
  delete ui; 
}