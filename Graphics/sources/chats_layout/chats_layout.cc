#include "chats_layout.hh"

#include "moc_chats_layout.cpp"
#include "ui_chats_layout.h"

Chats_layout::Chats_layout(QWidget *parent) : QWidget(parent), ui(new Ui::Chats_layout) {
  ui->setupUi(this);
  hide();

  hiccups = nullptr;

  btn_receive   = new QPushButton(tr("To Sender mode"), this);
  btn_load_file = new QPushButton(tr("Load file"), this);
  btn_get_file  = new QPushButton(tr("Get file"), this);
  ui->horizontalLayout->addWidget(btn_receive);
  ui->horizontalLayout->addWidget(btn_load_file);
  ui->horizontalLayout->addWidget(btn_get_file);
  btn_load_file->setVisible(false);

  connect(btn_receive,   SIGNAL(pressed()), this, SLOT(change_mode()));
  connect(btn_load_file, SIGNAL(pressed()), this, SLOT(load_file()));
  connect(btn_get_file,  SIGNAL(pressed()), this, SLOT(get_file()));
}

Chats_layout::~Chats_layout() { 
  delete btn_receive;
  delete btn_load_file;
  delete ui; 
}

void Chats_layout::set_network(Network::MACAddress &mac, HICCUPS::HICCUPS* wlan_) {
  MAC = mac;
  hiccups = wlan_;
}

void Chats_layout::change_mode() {
  // if(MAC.to_string(true) != "00.00.00.00.00.00") {
    if(!receive_mod) {
      receive_mod = 1;
      btn_receive->setText(tr("To Sender mode"));
      btn_load_file->setVisible(false);
      btn_get_file->setVisible(true);
    } else {
      receive_mod = 0;
      btn_receive->setText(tr("To Receive mode"));
      btn_load_file->setVisible(true);
      btn_get_file->setVisible(false);
    }
  // } else {
  //   QMessageBox msgBox;
  //   msgBox.setIcon(QMessageBox::Warning);
  //   msgBox.setWindowTitle(tr("Warning!"));
  //   msgBox.setText(tr("You didn't choose MAC!"));
  //   msgBox.exec();
  // }
}


void Chats_layout::load_file() {
  QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt *.pdf);;Image Files (*.jpg *.png)"));

  if (fileName != "") {
    setCursor(Qt::WaitCursor);

    Crypto::DataLoader cdataloader(Crypto::ChipperT::SimpleXOR, Crypto::KeyGenerators::BBS_Keygen, {2, 997}); //TODO: seed ned get from settings
    hiccups->HDC2_send(MAC, cdataloader, fileName.toStdString());

    setCursor(Qt::ArrowCursor);
  } 
}

void Chats_layout::get_file() {
  // QString fileName = QFileDialog::getOpenFileName(this, tr("Open File"), "", tr("Text Files (*.txt *.pdf);;Image Files (*.jpg *.png)"));

  // if (fileName != "") {
  QString fileName = "file";
  setCursor(Qt::WaitCursor);

  Crypto::DataLoader cdataloader(Crypto::ChipperT::SimpleXOR, Crypto::KeyGenerators::BBS_Keygen, {2, 997}); //TODO: seed ned get from settings
  hiccups->HDC2_recv(MAC, cdataloader, fileName.toStdString());

  setCursor(Qt::ArrowCursor);
  // } 
}