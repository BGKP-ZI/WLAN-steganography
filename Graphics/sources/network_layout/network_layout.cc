#include "network_layout.hh"
// #include "Network/include/WLAN.hh"

#include "moc_network_layout.cpp"
#include "ui_network_layout.h"

Network_layout::Network_layout(QWidget *parent) : QWidget(parent), ui(new Ui::Network_layout) {
  ui->setupUi(this);
  hide();

  connect(ui->btn_showAll, SIGNAL(pressed()), this, SLOT(show_all_address()));
  connect(ui->btn_connect, SIGNAL(pressed()), this, SLOT(test()));
  connect(ui->addres_listWidget, SIGNAL(itemPressed(QListWidgetItem *)), this,
          SLOT(address_pressed(QListWidgetItem *)));
}

Network_layout::~Network_layout() { 
  delete ui; 
}

void Network_layout::show_all_address() {
  setCursor(Qt::WaitCursor);

  ui->addres_listWidget->clear();
  //    dupm(std::stringbuffer);
  //    pars std::stringbuffer to address_list


  // get intreface
  // std::vector<std::string> interfaces = Network::WLAN::get_all_interfaces();
  // Network::WLAN wlan(interfaces[interfaces.size() - 1]); // TODO: maybe need get interface from settings???

  // // lock app and get address
  // wlan.scan_subnet();

  // pars and show address
  // std::stringstream out_str;
  // // wlan.show_ARP_table(out_str);
  // QString address(QString::fromStdString(out_str.str()));
  // address_list = address.replace("{", "").replace("}", "").split("\n");
  // ui->addres_listWidget->addItems(address_list);

  // unlock app
  setCursor(Qt::ArrowCursor);
}

void Network_layout::address_pressed(QListWidgetItem *item) {
  //qDebug() << "test" << item->text();
}

void Network_layout::test() {
  //TODO:
  // this->parentWidget()->parentWidget()->setEnabled(false);
  //qDebug() << "test";
}
