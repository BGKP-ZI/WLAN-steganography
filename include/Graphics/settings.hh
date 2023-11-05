#ifndef SETTINGS_HH
#define SETTINGS_HH

#include <QWidget>

namespace Ui {class Settings;}

class Settings : public QWidget {
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = nullptr);
    ~Settings();

private:
    Ui::Settings *ui;
};

#endif // SETTINGS_HH
