#include "robotinterface.h"
#include "ui_robotinterface.h"

RobotInterface::RobotInterface(int argc, char **argv, QWidget *parent)
  :QMainWindow(parent)
  ,ui(new Ui::RobotInterface)
  ,m_qnode(argc, argv)
{
  ui->setupUi(this);
}

RobotInterface::~RobotInterface()
{
  delete ui;
}
