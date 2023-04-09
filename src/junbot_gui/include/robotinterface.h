#ifndef ROBOTINTERFACE_H
#define ROBOTINTERFACE_H

#include <QMainWindow>

namespace Ui {
class RobotInterface;
}

class RobotInterface : public QMainWindow
{
  Q_OBJECT

public:
  explicit RobotInterface(QWidget *parent = nullptr);
  ~RobotInterface();

private:
  Ui::RobotInterface *ui;
};

#endif // ROBOTINTERFACE_H
