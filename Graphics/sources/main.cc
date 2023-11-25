#include <mainwindow/mainwindow.hh>

#include <QApplication>

// TODO: change path icon. Add to source file

int main(int argc, char **argv) {
  QApplication a(argc, argv);
  MainWindow w;
  w.show();
  return a.exec();
}
