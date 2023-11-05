#include "include/Graphics/network.hh"
#include "build/.ui/ui_network.h"

Network::Network(QWidget *parent) : QWidget(parent), ui(new Ui::Network) {
    ui->setupUi(this);
    this->hide();

    connect(ui->btn_showAll, SIGNAL(pressed()), this, SLOT(show_all_address()));
    connect(ui->btn_connetc, SIGNAL(pressed()), this, SLOT(test()));
    connect(ui->addres_listWidget, SIGNAL(itemPressed(QListWidgetItem*)), this, SLOT(address_pressed(QListWidgetItem*)));
}

Network::~Network() {
    delete ui;
}

void Network::show_all_address() {
    ui->addres_listWidget->clear();
    //    dupm(std::stringbuffer);
    //    pars std::stringbuffer to address_list
    ui->addres_listWidget->addItems(address_list);
}

void Network::address_pressed(QListWidgetItem* item) {
    qDebug() << "test" << item->text();
}

void Network::test() {
    this->parentWidget()->parentWidget()->setEnabled(false);
}
