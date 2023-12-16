#include "chats_layout.hh"

#include "moc_chats_layout.cpp"
#include "ui_chats_layout.h"

Chats_layout::Chats_layout(QWidget *parent) : QWidget(parent), ui(new Ui::Chats_layout) {
  ui->setupUi(this);
  hide();

  btn_receive   = new QPushButton(tr("To Sender mode"), this);
  btn_load_file = new QPushButton(tr("Load file"), this);
  ui->horizontalLayout->addWidget(btn_receive);
  ui->horizontalLayout->addWidget(btn_load_file);
  btn_load_file->setVisible(false);

  connect(btn_receive,   SIGNAL(pressed()), this, SLOT(change_mode()));
  connect(btn_load_file, SIGNAL(pressed()), this, SLOT(load_file()));
}

Chats_layout::~Chats_layout() { 
  delete btn_receive;
  delete btn_load_file;
  delete ui; 
}

void Chats_layout::change_mode() {
  if(MAC.to_string(true) != "00.00.00.00.00.00") {
    if(!receive_mod) {
      receive_mod = 1;
      btn_receive->setText(tr("To Sender mode"));
      btn_load_file->setVisible(false);
    } else {
      receive_mod = 0;
      btn_receive->setText(tr("To Receive mode"));
      btn_load_file->setVisible(true);
    }
  } else {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle(tr("Warning!"));
    msgBox.setText(tr("You didn't choose MAC!"));
    msgBox.exec();
  }
}




void Chats_layout::load_file() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt *.pdf);;Image Files (*.jpg *.png)"));

  if (fileName != "") {
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly)) {
      QMessageBox::critical(this, tr("Error"), tr("Could not open file"));
    }
    QTextStream in(&file);
    // ui->textEdit->setText(in.readAll());
    file.close();
  } 
}

void Chats_layout::set_mac_addres(Network::MACAddress &mac) {
  MAC = mac;
}