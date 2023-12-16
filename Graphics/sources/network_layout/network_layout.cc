#include "network_layout.hh"

#include "moc_network_layout.cpp"
#include "ui_network_layout.h"

Network_layout::Network_layout(QWidget *parent) : QWidget(parent), ui(new Ui::Network_layout) {
  ui->setupUi(this);
  hide();

  wlan = nullptr;

  btn_connect = new QPushButton("Connect", this);
  btn_connect->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
  ui->horizontalLayout->addWidget(btn_connect);
  btn_connect->setVisible(false);

  addres_listWidget = new QListWidget(this);
  ui->verticalLayout->addWidget(addres_listWidget);

  connect(ui->btn_showAll, SIGNAL(pressed()), this, SLOT(show_all_address()));
}

Network_layout::~Network_layout() { 
  delete btn_connect;
  delete ui; 
}

void Network_layout::set_wlan(HICCUPS::HICCUPS *wlan_) {
  wlan = wlan_;
}

void Network_layout::show_all_address() {
  if(wlan != nullptr) {
    setCursor(Qt::WaitCursor);

    addres_listWidget->clear();

    // lock app and get address
    wlan->scan_subnet();

    // pars and show address
    std::stringstream out_str;
    wlan->show_ARP_table(out_str);
    QString address(QString::fromStdString(out_str.str()));
    address_list = address.replace("{", "").replace("}", "").split("\n");
    address_list.removeLast();
    addres_listWidget->addItems(address_list);

    // unlock app
    setCursor(Qt::ArrowCursor);
  } else {
    QMessageBox msgBox;
    msgBox.setIcon(QMessageBox::Warning);
    msgBox.setWindowTitle(tr("Warning!"));
    msgBox.setText(tr("You didn't choose the interfes!"));
    msgBox.exec();
  }
}

void Network_layout::test() {
  //TODO:
  // this->parentWidget()->parentWidget()->setEnabled(false);
  // qDebug() << "test";
}
