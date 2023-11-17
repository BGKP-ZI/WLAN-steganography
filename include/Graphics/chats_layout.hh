#ifndef __CHATS_LAYOUT_hh__
#define __CHATS_LAYOUT_hh__

#include <QWidget>

namespace Ui {
class Chats_layout;
}

class Chats_layout : public QWidget {
  Q_OBJECT

public:
  explicit Chats_layout(QWidget *parent = nullptr);
  ~Chats_layout();

private:
  Ui::Chats_layout *ui;
};

#endif // __CHATS_LAYOUT_hh__
