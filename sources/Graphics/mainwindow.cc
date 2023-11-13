#include "Graphics/mainwindow.hh"
#include "../../include/Graphics/moc_mainwindow.cpp"
#include "../../include/Graphics/ui_mainwindow.h"

#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent), ui(new Ui::MainWindow) {
  this->ui->setupUi(this);
  this->setup_MainWindow(); // Widget settings
  this->setup_ToolBar();    // TolBar settings

  this->chats_layout = new Chats();
  ui->horizontalLayout->addWidget(this->chats_layout);

  this->network_layout = new Network();
  ui->horizontalLayout->addWidget(this->network_layout);

  this->settings_layout = new Settings();
  ui->horizontalLayout->addWidget(this->settings_layout);
}

MainWindow::~MainWindow() { delete ui; }

void MainWindow::setup_MainWindow() {
  // set icon
  this->setWindowTitle(APP_NAME);
  this->setWindowFlags(Qt::Window);
  QString path_icon{"images/klimanov.ico"};
  this->setWindowIcon(QIcon{path_icon});

  // set size
  QSize screen_size = qApp->screens().at(0)->size();
  double scale_width = 0.2;
  double scale_height = 0.3;
  unsigned int new_ui_width = screen_size.width() * scale_width;
  unsigned int new_ui_height = screen_size.height() * scale_height;
  this->setGeometry((screen_size.width() - new_ui_width) / 2,
                    (screen_size.height() - new_ui_height) / 2, new_ui_width,
                    new_ui_height);

  // For fast close by CTRL+Q key sequence
  this->addAction(ui->actionClose);
  connect(ui->actionClose, SIGNAL(triggered()), qApp, SLOT(quit()));
}

void MainWindow::setup_ToolBar() {
  ui->toolBar->setContextMenuPolicy(Qt::CustomContextMenu);
  connect(ui->toolBar, SIGNAL(customContextMenuRequested(QPoint)), this,
          SLOT(void_slot()));

  // Show Chats widget by CTRL+SHIFT+C
  connect(ui->actionChats, SIGNAL(triggered()), this, SLOT(run_chats()));
  ui->toolBar->addAction(ui->actionChats);

  // Show Newtwork widget by CTRL+SHIFT+N
  connect(ui->actionNetwork, SIGNAL(triggered()), this, SLOT(run_network()));
  ui->toolBar->addAction(ui->actionNetwork);

  // Show Settings widget by CTRL+SHIFT+S
  connect(ui->actionSettings, SIGNAL(triggered()), this, SLOT(run_settings()));
  ui->toolBar->addAction(ui->actionSettings);
}

void MainWindow::run_chats() {
  qDebug() << "run_chats";

  if (!this->network_layout->isHidden()) {
    this->network_layout->hide();
  }
  if (!this->settings_layout->isHidden()) {
    this->settings_layout->hide();
  }

  this->chats_layout->show();
}

void MainWindow::run_network() {
  qDebug() << "run_network";

  if (!this->chats_layout->isHidden()) {
    this->chats_layout->hide();
  }
  if (!this->settings_layout->isHidden()) {
    this->settings_layout->hide();
  }

  this->network_layout->show();
}

void MainWindow::run_settings() {
  qDebug() << "run_settings";

  if (!this->chats_layout->isHidden()) {
    this->chats_layout->hide();
  }
  if (!this->network_layout->isHidden()) {
    this->network_layout->hide();
  }

  this->settings_layout->show();
}

void MainWindow::void_slot() {}

// for debug
void MainWindow::test_slot() { qDebug() << "test slot"; }