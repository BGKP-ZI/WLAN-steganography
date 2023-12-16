#include "mainwindow.hh"

#include "moc_mainwindow.cpp"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  ui->setupUi(this);
  setup_MainWindow(); // Widget settings
  setup_ToolBar();    // TolBar settings

  chats_layout = new Chats_layout();
  ui->horizontalLayout->addWidget(chats_layout);

  network_layout = new Network_layout();
  ui->horizontalLayout->addWidget(network_layout);

  settings_layout = new Settings_layout();
  ui->horizontalLayout->addWidget(settings_layout);


  // TODO: вынести в отдельную функию
  all_interfaces = HICCUPS::HICCUPS::get_all_interfaces();
  settings_layout->get_all_interfaces(all_interfaces);

  connect(settings_layout->menu_int, SIGNAL(triggered(QAction *)), this,
         SLOT(get_wlan(QAction *)));  

  connect(network_layout->addres_listWidget, SIGNAL(itemPressed(QListWidgetItem *)), this,
          SLOT(get_mac_addres(QListWidgetItem *)));
}

MainWindow::~MainWindow() { 
  delete wlan;
  delete chats_layout;
  delete network_layout;
  delete settings_layout;
  delete ui; 
}

void MainWindow::setup_MainWindow() {
  // set icon
  setWindowTitle(APP_NAME);
  setWindowFlags(Qt::Window);
  QString path_icon{":/klimanov.ico"};
  if(!QFile(":/klimanov.ico").exists()) {
    qWarning() << "Icon file not found";
  }
  setWindowIcon(QIcon{":/klimanov.ico"});

  // set size
  QSize screen_size = qApp->screens().at(0)->size();
  double scale_width = 0.2;
  double scale_height = 0.3;
  unsigned int new_ui_width = screen_size.width() * scale_width;
  unsigned int new_ui_height = screen_size.height() * scale_height;
  setGeometry((screen_size.width() - new_ui_width) / 2,
                    (screen_size.height() - new_ui_height) / 2, new_ui_width,
                    new_ui_height);

  // For fast close by CTRL+Q key sequence
  addAction(ui->actionClose);
  connect(ui->actionClose, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::setup_ToolBar() {
  ui->toolBar->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->toolBar, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(void_slot()));

  // Show Newtwork_layout widget by CTRL+SHIFT+N
  connect(ui->actionNetwork, SIGNAL(triggered()), this, SLOT(run_network()));
  ui->toolBar->addAction(ui->actionNetwork);

  // Show Chats_layout widget by CTRL+SHIFT+C
  connect(ui->actionChats, SIGNAL(triggered()), this, SLOT(run_chats()));
  ui->toolBar->addAction(ui->actionChats);

  // Show Settings_layout widget by CTRL+SHIFT+S
  connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(run_settings()));
  ui->toolBar->addAction(ui->actionSettings);
}

void MainWindow::run_chats() {
  if (!network_layout->isHidden()) {
    network_layout->hide();
  }
  if (!settings_layout->isHidden()) {
    settings_layout->hide();
  }

  chats_layout->set_network(MAC, wlan);
  chats_layout->show();
}

void MainWindow::run_network() {
  if (!chats_layout->isHidden()) {
    chats_layout->hide();
  }
  if (!settings_layout->isHidden()) {
    settings_layout->hide();
  }

  network_layout->show();
}

void MainWindow::run_settings() {
  if (!chats_layout->isHidden()) {
    chats_layout->hide();
  }
  if (!network_layout->isHidden()) {
    network_layout->hide();
  }

  settings_layout->show();
}

void MainWindow::get_mac_addres(QListWidgetItem *item) {
  QString tmp = item->text().split(": ").at(1);
  tmp.replace(".", ":");
  MAC = Network::MACAddress(tmp.toStdString(), true);
}

void MainWindow::get_wlan(QAction *action) {
  wlan = new HICCUPS::HICCUPS((action->text()).toStdString());
  network_layout->set_wlan(wlan);
  QMessageBox msgBox;
  msgBox.setIcon(QMessageBox::Information);
  msgBox.setWindowTitle(tr("Interfaces is selected."));
  msgBox.setText(tr("Interfaces ") + action->text() + tr(" is selected."));
  msgBox.exec();
}

void MainWindow::void_slot() {}

// for debug
void MainWindow::test_slot() { qDebug() << "test slot"; }