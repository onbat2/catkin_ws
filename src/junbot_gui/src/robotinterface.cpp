#include "robotinterface.h"
#include "ui_robotinterface.h"

RobotInterface::RobotInterface(QWidget *parent) :
  QMainWindow(parent),
  ui(new Ui::RobotInterface)
{
  ui->setupUi(this);
}

RobotInterface::~RobotInterface()
{
  delete ui;
}
