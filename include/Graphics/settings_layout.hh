#ifndef __SETTINGS_LAYOUT_hh__
#define __SETTINGS_LAYOUT_hh__

#include <QWidget>

namespace Ui {
class Settings_layout;
}

class Settings_layout : public QWidget {
  Q_OBJECT

public:
  explicit Settings_layout(QWidget *parent = nullptr);
  ~Settings_layout();

private:
  Ui::Settings_layout *ui;
};

#endif // SETTINGS_LAYOUT_HH
